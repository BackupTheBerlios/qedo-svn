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

#include "Catalog.h"

namespace Qedo
{

CatalogBase::CatalogBase(const AccessMode eAM, const char* szConnString) :
	m_hEnv(SQL_NULL_HENV),
	m_hDbc(SQL_NULL_HDBC),
	m_lLoginTimeout(DEFAULT_TIMEOUT),
	m_lQueryTimeout(DEFAULT_TIMEOUT),
	m_nRecordsAffected(0),
	m_bIsConnected(FALSE),
	m_eAM(eAM)
{
	m_szODBCVersion = new char[MAX_INFO_LEN];
	m_szConnString = new char[MAX_CONNSTR_LEN];
	memset(m_szODBCVersion, '\0', MAX_INFO_LEN);
	memset(m_szConnString, '\0', MAX_CONNSTR_LEN);
	strcpy(m_szConnString, szConnString);
}

CatalogBase::~CatalogBase()
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

void 
CatalogBase::Init()
{
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HENV, &m_hEnv);
	SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0); 
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc);
}

void 
CatalogBase::Destroy()
{
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);

	m_hDbc = SQL_NULL_HDBC;
	m_hEnv = SQL_NULL_HENV;
}

bool 
CatalogBase::DriverConnect(const char* szConnStr, char* szConnStrOut, HWND hWnd, const int nDrvConn)
{
	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;

	if(nDrvConn == SQL_DRIVER_PROMPT && hWnd == NULL)
		return FALSE;

	SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lQueryTimeout, 0);
	
	if(m_eAM==READ_ONLY)
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)SQL_MODE_READ_ONLY, 0);
	else
		SQLSetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)SQL_MODE_READ_WRITE, 0);

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
CatalogBase::SetLoginTimeout(const long nSeconds)
{
	m_lLoginTimeout = nSeconds;
}

void 
CatalogBase::SetQueryTimeout(const long nSeconds)
{
	m_lQueryTimeout = nSeconds;
}

int 
CatalogBase::GetRecordsAffected()
{
	return m_nRecordsAffected;
}

char* 
CatalogBase::GetODBCVersion()
{
	SQLRETURN ret;
	
	ret = SQLGetInfo(m_hDbc, SQL_ODBC_VER, m_szODBCVersion, MAX_INFO_LEN, NULL);

	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return NULL;

	return m_szODBCVersion;
}

bool 
CatalogBase::ExecuteSQL(const char* szSqlStr)
{
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
CatalogBase::CanTransact()
{
	SQLUSMALLINT nTxn;

	SQLGetInfo(m_hDbc, SQL_TXN_CAPABLE, (SQLPOINTER)&nTxn, sizeof(nTxn), NULL);

	if(nTxn==SQL_TC_NONE)
		return FALSE;

	return TRUE;
}

bool 
CatalogBase::CanUpdate()
{
	SQLUINTEGER nTxn;

	SQLGetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)&nTxn, NULL, 0);

	if(nTxn==SQL_MODE_READ_ONLY)
		return FALSE;

	return TRUE;
}

bool 
CatalogBase::IsConnected()
{
	return m_bIsConnected;
}

bool 
CatalogBase::IsTableExist(const char* szTableName)
{
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
					//NULL, 0);   // All table types 
					(unsigned char*)szTable, strlen(szTable)); // only TABLE

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

AccessMode 
CatalogBase::access_mode()
{
	int nAccessMode;

	SQLGetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, &nAccessMode, SQL_IS_INTEGER, NULL);

	if(nAccessMode == SQL_MODE_READ_ONLY)
		return READ_ONLY;
	else
		return READ_WRITE;
}

StorageHomeBase_ptr 
CatalogBase::find_storage_home(const char* storage_home_id)
{
	if(IsTableExist(storage_home_id))
	{
		return NULL;
	}
	else
		return NULL;
}

StorageObjectBase_ptr 
CatalogBase::find_by_pid(const Pid& the_pid)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//The flush operation instructs the PSS implementation to write to disk any 
//cached modifications of storage object incarnations managed by this catalog.
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBase::flush()
{
	// call the execute() for update
}

////////////////////////////////////////////////////////////////////////////////
//Calling refresh is unusual: most applications will never use this operation
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBase::refresh()
{

}

////////////////////////////////////////////////////////////////////////////////
//The operation free_all instructs the catalog implementation to set the 
//reference count of all its PSDL storage object instances to 0
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBase::free_all()
{

}

////////////////////////////////////////////////////////////////////////////////
//The operation close terminates the catalog. When closed, the catalog is also 
//flushed. If the catalog is associated with one or more transactions when close
//is called, these transactions are marked roll-back only.
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBase::close()
{
	if(IsConnected())
	{
		flush();

		m_bIsConnected = FALSE;

		if(m_hDbc == NULL)
			return;

		SQLDisconnect(m_hDbc);
	}
}

SessionPool::~SessionPool()
{

}

void 
SessionPool::Init()
{
	SQLSetEnvAttr( SQL_NULL_HENV, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_DRIVER, 0 );
    SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HENV, &m_hEnv );
	SQLSetEnvAttr( m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER );
	SQLAllocHandle ( SQL_HANDLE_DBC, m_hEnv, &m_hDbc );
}

void 
SessionPool::flush_by_pids(const PidList& pids)
{

}

void 
SessionPool::refresh_by_pids(const PidList& pids)
{

}

TransactionPolicy 
SessionPool::transaction_policy()
{
	return 0;
}

} // namespace Qedo
