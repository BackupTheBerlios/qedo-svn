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

#include "ODBCCore.h"

/////////////////////////////////////////////////////////////
//
// CODBCDatabase Class
//
/////////////////////////////////////////////////////////////
namespace CosPersistentState
{

CODBCDatabase::CODBCDatabase()
{
	m_hEnv = NULL;
	m_hDbc = NULL;
	m_lLoginTimeout = DEFAULT_TIMEOUT;
	m_lQueryTimeout = DEFAULT_TIMEOUT;
	m_nRecordsAffected = 0;
	m_bIsConnected = FALSE;

	m_szDBMSName = new char[MAX_INFO_LEN];
	m_szDBName = new char[MAX_INFO_LEN];
	m_szVersion = new char[MAX_INFO_LEN];
	m_szConnString = new char[MAX_CONNSTR_LEN];

	SQLAlloc();
}

CODBCDatabase::~CODBCDatabase()
{
	Close();

	m_lLoginTimeout = 0;
	m_lQueryTimeout = 0;
	m_nRecordsAffected = 0;
	m_bIsConnected = FALSE;

	delete m_szDBMSName;
	delete m_szDBName;
	delete m_szVersion;
	delete m_szConnString;
	m_szDBMSName = NULL;
	m_szDBName = NULL;
	m_szVersion = NULL;
	m_szConnString = NULL;
}

void CODBCDatabase::SQLAlloc()
{
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
	SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc); 
}

void CODBCDatabase::SQLFree()
{
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);

	m_hDbc = NULL;
	m_hEnv = NULL;
}

//++++++++++++++++++++++++++++++
//Option 1 (simplest): SQLConnect
//(Core interface conformance level)
//++++++++++++++++++++++++++++++
bool CODBCDatabase::Connect(char* szDSN, char* szUser, char* szPass)
{
	SQLRETURN ret;
	
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lQueryTimeout, 0);	

	// here can use SQLDataSources to collect information for SQLConncet
	ret = SQLConnect(m_hDbc, 
					(SQLCHAR*)szDSN, 
					(SWORD)strlen(szDSN), //sizeof(szDSN), 
					(SQLCHAR*)szUser, 
					(SWORD)strlen(szUser), //sizeof(szUser), 
					(SQLCHAR*)szPass, 
					(SWORD)strlen(szPass));//sizeof(szPass));

	//DSN=myodbc3-test;SERVER=haw;UID=root;PWD=;DATABASE=test;
	memset(m_szConnString, '\0', MAX_CONNSTR_LEN);
	strcat(m_szConnString, "DSN=");
	strcpy(m_szConnString, szDSN);
	strcat(m_szConnString, "; UID=");
	strcat(m_szConnString, szUser);
	strcat(m_szConnString, "; PWD=");
	strcat(m_szConnString, szPass);
	strcat(m_szConnString, ";");

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;

	return m_bIsConnected;
}

//++++++++++++++++++++++++++++++
//Option 2: SQLDriverConnect
//(Core) completes the connection string by interaction with the user
//++++++++++++++++++++++++++++++
bool CODBCDatabase::DriverConnect(char* szConnStr, char* szConnStrOut, HWND hWnd, int nDrvConn)
{
	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;

	if(nDrvConn == SQL_DRIVER_PROMPT && hWnd == NULL)
		return FALSE;

	ret=SQLSetConnectAttr(m_hDbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)m_lLoginTimeout, 0);
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)m_lQueryTimeout, 0);
	
	ret = SQLDriverConnect(m_hDbc, 
							hWnd, 
							(SQLCHAR*)szConnStr, 
							SQL_NTS, 
							(SQLCHAR*)szConnStrOut,
							sizeof(szConnStrOut), 
							&pcbConnStrOut, 
							(SQLUSMALLINT)nDrvConn);

	memset(m_szConnString, '\0', MAX_CONNSTR_LEN);
	strcpy(m_szConnString, szConnStr);
	
	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	
	return m_bIsConnected;
}

//++++++++++++++++++++++++++++++
//Option 3: SQLBrowseConnect
//(Level 1) completes the connection string iteratively with the data source
//++++++++++++++++++++++++++++++
bool CODBCDatabase::BrowseConnect(char* szConnStrIn, char* szConnStrOut)
{
	SQLRETURN ret;
	SWORD swLenOut = 0;

	ret = SQLBrowseConnect(m_hDbc, 
							(SQLCHAR*)szConnStrIn, 
							(SWORD)strlen((const char*)szConnStrIn), //sizeof(szConnStrIn), 
							(SQLCHAR*)szConnStrOut, 
							MAX_BUFFER, 
							&swLenOut);

	memset(m_szConnString, '\0', MAX_CONNSTR_LEN);
	strcpy(m_szConnString, szConnStrOut);

	m_bIsConnected = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	
	return m_bIsConnected;
}

void CODBCDatabase::Close()
{
	m_bIsConnected = FALSE;
	
	if(m_hDbc == NULL)
		return;

	SQLDisconnect(m_hDbc);
	SQLFree();
}

//++++++++++++++++++++++++++++++
//specify whether a data source is read-only or read-write
//++++++++++++++++++++++++++++++
void CODBCDatabase::SetReadOnly(bool bReadOnly)
{
	SQLSetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)(bReadOnly? SQL_MODE_READ_ONLY : SQL_MODE_READ_WRITE), 0);
}

void CODBCDatabase::SetLoginTimeout(long nSeconds)
{
	m_lLoginTimeout = nSeconds;
}

void CODBCDatabase::SetQueryTimeout(long nSeconds)
{
	m_lQueryTimeout = nSeconds;
}

long CODBCDatabase::GetQueryTimeout()
{
	long nSeconds;

	SQLGetConnectAttr(m_hDbc, SQL_ATTR_CONNECTION_TIMEOUT, &nSeconds, NULL, 0);

	return nSeconds;
}

int CODBCDatabase::GetMaxDriverConnections()
{
	SQLRETURN ret;
	SQLSMALLINT nMaxConn;

	ret = SQLGetInfo(m_hDbc, SQL_MAX_DRIVER_CONNECTIONS, (SQLPOINTER)&nMaxConn, sizeof(nMaxConn), NULL);

	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 0;

	return nMaxConn;
}

char* CODBCDatabase::GetDBMSName()
{
	SQLRETURN ret;

	ret = SQLGetInfo(m_hDbc, SQL_DBMS_NAME, m_szDBMSName, MAX_INFO_LEN, NULL);

	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 0;

	return m_szDBMSName;
}

char* CODBCDatabase::GetVersion()
{
	SQLRETURN ret;
	
	ret = SQLGetInfo(m_hDbc, SQL_DBMS_VER, m_szVersion, MAX_INFO_LEN, NULL);

	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 0;

	return m_szVersion;
}

char* CODBCDatabase::GetDatabaseName()
{
	SQLRETURN ret;

	ret = SQLGetInfo(m_hDbc, SQL_DATABASE_NAME, m_szDBName, MAX_INFO_LEN, NULL);

	if(ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 0;

	return m_szDBName;
}

char* CODBCDatabase::GetConnect()
{
	return m_szConnString;
}

int CODBCDatabase::GetRecordsAffected()
{
	return m_nRecordsAffected;
}

bool CODBCDatabase::IsConnected()
{
	return m_bIsConnected;
}

bool CODBCDatabase::CanTransact()
{
	SQLRETURN ret;
	SQLUSMALLINT nTxn;

	ret = SQLGetInfo(m_hDbc, SQL_TXN_CAPABLE, (SQLPOINTER)&nTxn, sizeof(nTxn), NULL);

	if(ret==SQL_TC_NONE)
		return FALSE;

	return TRUE;
}

bool CODBCDatabase::CanUpdate()
{
	SQLRETURN ret;
	SQLUINTEGER nTxn;

	ret = SQLGetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)&nTxn, NULL, 0);

	if(ret==SQL_MODE_READ_ONLY)
		return FALSE;

	return TRUE;
}

//++++++++++++++++++++++++++++++
//CODBCDatabase's execute operation
//++++++++++++++++++++++++++++++
bool CODBCDatabase::ExecuteSQL(char* szSqlStr)
{
	SQLRETURN ret;
	SQLHSTMT hStmt = NULL;
	SQLINTEGER nRowCount;

	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &hStmt);
	ret = SQLExecDirect(hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);
	
	SQLRowCount(hStmt, &nRowCount);
	SQLFreeHandle(SQL_HANDLE_STMT , hStmt);
	
	m_nRecordsAffected = nRowCount;

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}


/////////////////////////////////////////////////////////////
//
// CODBCRecordset Class
//
/////////////////////////////////////////////////////////////

CODBCRecordset::CODBCRecordset(CODBCDatabase* pDb)
{
	m_hDbc = pDb->m_hDbc;
	m_hStmt = NULL;
	m_bIsBOF = FALSE;
	m_bIsEOF = FALSE;
	m_nNumRowsFetched = 0;
	
	AllocStmt();
}

CODBCRecordset::~CODBCRecordset()
{
	//FreeStmt();

	//m_hStmt = NULL;
	m_bIsBOF = FALSE;
	m_bIsEOF = FALSE;
}

void CODBCRecordset::AllocStmt()
{
	SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);
}

void CODBCRecordset::FreeStmt()
{
	if(m_hStmt != NULL)
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	
	m_hStmt = NULL;
}

bool CODBCRecordset::Open(char* szSqlStr)
{
	SQLRETURN ret;
	
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER)SQL_SCROLLABLE, SQL_IS_INTEGER);
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_DYNAMIC, SQL_IS_INTEGER);
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_ROWS_FETCHED_PTR, &m_nNumRowsFetched, 0);
	ret = SQLExecDirect(m_hStmt, (SQLCHAR*)szSqlStr, SQL_NTS);

	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		/*ret = SQLFetch(m_hStmt);

		if(ret==SQL_NO_DATA_FOUND)
			m_bIsBOF = m_bIsEOF = TRUE;

		return TRUE;*/
		
		return MoveFirst();
	}
	
	return FALSE;
}

void CODBCRecordset::Close()
{
	SQLCloseCursor(m_hStmt);
	FreeStmt();
}

//********** GetFieldValue **********//
bool CODBCRecordset::GetFieldValue(int nField, char* szData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_CHAR, szData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(char* szFieldName, char* szData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), szData);	
}

bool CODBCRecordset::GetFieldValue(int nField, long* lData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_LONG, lData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(char* szFieldName, long* lData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), lData);	
}

bool CODBCRecordset::GetFieldValue(int nField, double* dblData)
{
	SQLINTEGER cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_DOUBLE, dblData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::GetFieldValue(char* szFieldName, double* dblData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), dblData);	
}

bool CODBCRecordset::GetFieldValue(int nField, struct tm* time)
{
	SQLINTEGER cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	SQL_TIMESTAMP_STRUCT* sqltm = new SQL_TIMESTAMP_STRUCT;
	
	ret = SQLGetData(m_hStmt, (SQLUSMALLINT)nField + 1, SQL_C_TYPE_TIMESTAMP, sqltm, nLength, &cbValue) == SQL_SUCCESS;
	
	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{	
		time->tm_year = sqltm->year;
		time->tm_mon = sqltm->month - 1; //January must be = 0		
		time->tm_mday = sqltm->day;
		time->tm_hour = sqltm->hour;
		time->tm_min = sqltm->minute;
		time->tm_sec = sqltm->second;
		delete sqltm; // new added by me

		return TRUE;
	}

	delete sqltm; // new added by me
	
	return FALSE;
}

bool CODBCRecordset::GetFieldValue(char* szFieldName, struct tm* time)
{
	return GetFieldValue(GetFieldIndex(szFieldName), time);	
}
//********** end of GetFieldValue **********//

bool CODBCRecordset::GetFieldName(int nField, char* szFieldName)
{
	int nType, nLength;

	return GetFieldAttributes(nField, szFieldName, nType, nLength);
}

int CODBCRecordset::GetFieldIndex(char* szFieldName)
{
	SQLSMALLINT nCols;
	int nCol = 1;
	char szColName[MAX_COL_NAME_LEN];
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
	SQLUINTEGER cbColDef;

	SQLNumResultCols(m_hStmt, &nCols);
	
	while(nCol < nCols)
	{
		//memset(szColName, 0, 32 * sizeof(char));
		memset(szColName, 0, MAX_COL_NAME_LEN);
		SQLDescribeCol(m_hStmt, nCol, (SQLCHAR*)szColName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);

		if(_stricmp(szColName, szFieldName) == 0)
			return nCol - 1;
		nCol++;
	}

	return -1;
}

long CODBCRecordset::GetFieldLength(int nField)
{
	SQLSMALLINT fSqlType, ibScale, fNullable;
	SQLUINTEGER cbColDef;
	
	SQLDescribeCol(m_hStmt, nField + 1, NULL, 0, 0, &fSqlType, &cbColDef, &ibScale, &fNullable);

	return cbColDef;	
}

bool CODBCRecordset::GetFieldAttributes(int nField, char* szFieldName, int& nType, int& nLength)
{
	SQLRETURN ret;
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
	SQLUINTEGER cbColDef;
	
	ret = SQLDescribeCol(m_hStmt, nField + 1, (SQLCHAR*)szFieldName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);
	
	nType = fSqlType;
	nLength = cbColDef;

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;	
}

int CODBCRecordset::GetFieldCount()
{
	SQLSMALLINT nFieldCount = 0;
	SQLNumResultCols(m_hStmt, &nFieldCount);

	return nFieldCount;
}

bool CODBCRecordset::MoveFirst()
{
	SQLRETURN ret;

	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_FIRST, 0);
	
	m_bIsBOF = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	
	if(m_bIsBOF)
		m_bIsEOF = FALSE;

	return m_bIsBOF;
}

bool CODBCRecordset::MovePrevious()
{
	SQLRETURN ret;
	
	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_PRIOR, 0);
	m_bIsBOF = ret == SQL_NO_DATA;
	m_bIsEOF = FALSE;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::MoveNext()
{
	SQLRETURN ret;
	
	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_NEXT, 0);
	
	m_bIsEOF = ret == SQL_NO_DATA;
	m_bIsBOF = FALSE;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool CODBCRecordset::MoveLast()
{
	SQLRETURN ret;
	
	ret = SQLFetchScroll(m_hStmt, SQL_FETCH_LAST, 0);

	m_bIsEOF = ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
	
	if(m_bIsEOF)
		m_bIsBOF = FALSE;

	return m_bIsEOF;
}

}