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
	m_hEnv(SQL_NULL_HENV),
	m_hDbc(SQL_NULL_HDBC),
	m_lLoginTimeout(DEFAULT_TIMEOUT),
	m_lQueryTimeout(DEFAULT_TIMEOUT),
	m_nRecordsAffected(0),
	m_bIsConnected(FALSE)
{
	m_szODBCVersion = new char[MAX_INFO_LEN];
	m_szConnString = new char[MAX_CONNSTR_LEN];
	memset(m_szODBCVersion, '\0', MAX_INFO_LEN);
	memset(m_szConnString, '\0', MAX_CONNSTR_LEN);
}

QDDatabase::~QDDatabase()
{
	Destroy();

	m_lLoginTimeout = 0;
	m_lQueryTimeout = 0;
	m_nRecordsAffected = 0;
	m_bIsConnected = FALSE;

	delete m_szODBCVersion;
	delete m_szConnString;
	m_szODBCVersion = NULL;
	m_szConnString = NULL;
}

bool 
QDDatabase::Init()
{
	SQLRETURN ret;

	ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &m_hEnv);
	
	if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
        ret = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	
		if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			ret = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc);
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
		m_bIsConnected = FALSE;

		if(m_hDbc == NULL)
			return;

		SQLDisconnect(m_hDbc);
	}
}

void 
QDDatabase::Destroy()
{
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);

	m_hDbc = SQL_NULL_HDBC;
	m_hEnv = SQL_NULL_HENV;
}

bool 
QDDatabase::DriverConnect(const char* szConnStr, char* szConnStrOut, HWND hWnd, const int nDrvConn)
{
	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;

	if(nDrvConn == SQL_DRIVER_PROMPT && hWnd == NULL)
		return FALSE;

	SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lQueryTimeout, 0);
	
	ret = SQLDriverConnect(m_hDbc, 
							hWnd, 
							(SQLCHAR*)szConnStr, 
							SQL_NTS, 
							(SQLCHAR*)szConnStrOut,
							sizeof(szConnStrOut), 
							&pcbConnStrOut, 
							(SQLUSMALLINT)nDrvConn);

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	
	return m_bIsConnected;
}

void 
QDDatabase::SetLoginTimeout(const long nSeconds)
{
	m_lLoginTimeout = nSeconds;
}

void 
QDDatabase::SetQueryTimeout(const long nSeconds)
{
	m_lQueryTimeout = nSeconds;
}

int 
QDDatabase::GetRecordsAffected()
{
	return m_nRecordsAffected;
}

char* 
QDDatabase::GetODBCVersion()
{
	if(!IsConnected())
		return NULL;

	SQLRETURN ret;
	
	ret = SQLGetInfo(m_hDbc, SQL_ODBC_VER, m_szODBCVersion, MAX_INFO_LEN, NULL);

	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return NULL;

	return m_szODBCVersion;
}

bool 
QDDatabase::ExecuteSQL(const char* szSqlStr)
{
	if(!IsConnected())
		return FALSE;

	SQLRETURN ret;
	SQLHSTMT hStmt = NULL;
	SQLINTEGER nRowCount;

	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);
	
	SQLRowCount(hStmt, &nRowCount);
	SQLFreeHandle(SQL_HANDLE_STMT , hStmt);
	hStmt = NULL;
	
	m_nRecordsAffected = nRowCount;

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDDatabase::CanTransact()
{
	if(!IsConnected())
		return FALSE;

	SQLUSMALLINT nTxn;

	SQLGetInfo(m_hDbc, SQL_TXN_CAPABLE, (SQLPOINTER)&nTxn, sizeof(nTxn), NULL);

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

	SQLGetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)&nTxn, NULL, 0);

	if(nTxn==SQL_MODE_READ_ONLY)
		return FALSE;

	return TRUE;
}

bool 
QDDatabase::IsConnected()
{
	return m_bIsConnected;
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

	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &hStmt);

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
	return m_hDbc;
}

} // namespace Qedo
