/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/
#include "QDDatabase.h"


namespace Qedo
{

QDDatabase::QDDatabase() :
	hDbc_(SQL_NULL_HDBC),
	hEnv_(SQL_NULL_HENV),
	iRecordsAffected_(0),
	lLoginTimeout_(DEFAULT_TIMEOUT),
	lQueryTimeout_(DEFAULT_TIMEOUT),
	bIsConnected_(FALSE)
{
	szODBCVersion_ = new char[MAX_INFO_LEN];
	szConnString_ = new char[MAX_CONNSTR_LEN];
	memset(szODBCVersion_, '\0', MAX_INFO_LEN);
	memset(szConnString_, '\0', MAX_CONNSTR_LEN);
}

QDDatabase::~QDDatabase()
{
	Destroy();

	lLoginTimeout_ = 0;
	lQueryTimeout_ = 0;
	iRecordsAffected_ = 0;
	bIsConnected_ = FALSE;

	delete [] szODBCVersion_;
	delete [] szConnString_;
	szODBCVersion_ = NULL;
	szConnString_ = NULL;
}

bool 
QDDatabase::Init()
{
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &hEnv_);
	
	if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
        ret = SQLSetEnvAttr(hEnv_, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	
		if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv_, &hDbc_);
			return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

void 
QDDatabase::close()
{
	if(IsConnected())
	{
		bIsConnected_ = FALSE;

		if(hDbc_ == NULL)
			return;

		SQLDisconnect(hDbc_);
	}
}

void 
QDDatabase::Destroy()
{
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc_);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv_);

	hDbc_ = SQL_NULL_HDBC;
	hEnv_ = SQL_NULL_HENV;
}

bool 
QDDatabase::DriverConnect(const char* szConnStr, char* szConnStrOut, HWND hWnd, const int nDrvConn)
{
	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;

	if(nDrvConn == SQL_DRIVER_PROMPT && hWnd == NULL)
		return FALSE;

	SQLSetConnectAttr(hDbc_, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)lLoginTimeout_, 0);
	SQLSetConnectAttr(hDbc_, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)lQueryTimeout_, 0);
	
	ret = SQLDriverConnect(hDbc_, 
							hWnd, 
							(SQLCHAR*)szConnStr, 
							SQL_NTS, 
							(SQLCHAR*)szConnStrOut,
							sizeof(szConnStrOut), 
							&pcbConnStrOut, 
							(SQLUSMALLINT)nDrvConn);

	bIsConnected_ = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	
	return bIsConnected_;
}

void 
QDDatabase::SetLoginTimeout(const long nSeconds)
{
	lLoginTimeout_ = nSeconds;
}

void 
QDDatabase::SetQueryTimeout(const long nSeconds)
{
	lQueryTimeout_ = nSeconds;
}

int 
QDDatabase::GetRecordsAffected()
{
	return iRecordsAffected_;
}

int
QDDatabase::GetMaxDriverConnections()
{
	SQLUSMALLINT nMaxConn = 0;
	SQLGetInfo(hDbc_, SQL_MAX_DRIVER_CONNECTIONS, (SQLPOINTER)&nMaxConn, sizeof(nMaxConn), NULL);

	return nMaxConn;
}

char* 
QDDatabase::GetODBCVersion()
{
	if(!IsConnected())
		return NULL;

	SQLRETURN ret;
	
	ret = SQLGetInfo(hDbc_, SQL_ODBC_VER, szODBCVersion_, MAX_INFO_LEN, NULL);

	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return NULL;

	return szODBCVersion_;
}

bool 
QDDatabase::ExecuteSQL(const char* szSqlStr)
{
	if(!IsConnected())
		return FALSE;

	SQLRETURN ret;
	SQLHSTMT hStmt = NULL;
	SQLINTEGER nRowCount;

	SQLAllocHandle(SQL_HANDLE_STMT, hDbc_, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);
	
	SQLRowCount(hStmt, &nRowCount);
	SQLFreeHandle(SQL_HANDLE_STMT , hStmt);
	hStmt = NULL;
	
	iRecordsAffected_ = nRowCount;
	
	if( ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO )
        std::cout << "ExecuteSQL return true.\n";
	else
		std::cout << "ExecuteSQL return false!\n";

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDDatabase::CanTransact()
{
	if(!IsConnected())
		return FALSE;

	SQLUSMALLINT nTxn;

	SQLGetInfo(hDbc_, SQL_TXN_CAPABLE, (SQLPOINTER)&nTxn, sizeof(nTxn), NULL);

	if(nTxn==SQL_TC_NONE)
		return FALSE;

	return TRUE;
}

bool 
QDDatabase::CanUpdate()
{
	if(!IsConnected())
		return FALSE;

	SQLUINTEGER nTxn;

	SQLGetConnectAttr(hDbc_, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)&nTxn, NULL, 0);

	if(nTxn==SQL_MODE_READ_ONLY)
		return FALSE;

	return TRUE;
}

bool 
QDDatabase::IsConnected()
{
	return bIsConnected_;
}

bool 
QDDatabase::IsTableExist(const char* szTableName)
{
	if(!IsConnected())
		return FALSE;

	SQLRETURN ret;
	SQLHSTMT hStmt = NULL;
	SQLSMALLINT nFieldCount = 0;
	char szTable[6] = "TABLE";

	SQLAllocHandle(SQL_HANDLE_STMT, hDbc_, &hStmt);

	ret = SQLTables(hStmt,
					NULL, 0,    // All catalogs
					NULL, 0,    // All schemas
					//NULL, 0,	// All tables 
					(unsigned char*)szTableName, strlen(szTableName),
					NULL, 0);   // All table types 
					//(unsigned char*)szTable, strlen(szTable)); // only TABLE

	// fetch and close the current cursor
	ret = SQLFetch(hStmt);
	SQLCloseCursor(hStmt);

	// free SQLHSTMT
	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	hStmt = NULL;

	if(ret!=SQL_NO_DATA)
		return TRUE;

	return FALSE;
}

SQLHDBC 
QDDatabase::getHDBC()
{
	return hDbc_;
}

} // namespace Qedo
