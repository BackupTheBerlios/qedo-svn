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

#ifndef __ODBCCORE_H__
#define __ODBCCORE_H__

#include <windows.h>
//#include <sql.h>
#include <sqlext.h>
#include <time.h>


#define DEFAULT_TIMEOUT 15
#define MAX_COL_NAME_LEN 32
#define MAX_INFO_LEN 64
#define MAX_BUFFER 256
#define MAX_CONNSTR_LEN 1024

//++++++++++++++++++++
// SQLHENV (ENV) for CODBCDatabase
// SQLHDBC (DBC) for CODBCDatabase
//
// SQLHSTMT (STMT) for CODBCRecordset
//++++++++++++++++++++
namespace CosPersistentState
{

class CODBCDatabase
{
	public:

		CODBCDatabase();
		~CODBCDatabase();

		bool Connect(char* lpstrDSN, char* lpstrUser = NULL, char* lpstrPass = NULL);
		bool DriverConnect(char* szConnStr, char* szConnStrOut = NULL, HWND hWnd = NULL, int nDrvConn = SQL_DRIVER_NOPROMPT);
		bool BrowseConnect(char* lpstrConnStrIn, char* lpstrConnStrOut);
		void Close();

		void SetReadOnly(bool bReadOnly = TRUE); //???
		void SetLoginTimeout(long nSeconds); //???
		void SetQueryTimeout(long nSeconds); //???
		long GetQueryTimeout(); //??? delete this in end-version

		int GetRecordsAffected();
		bool IsConnected();
		bool ExecuteSQL(char* szSqlStr);
		
		int GetMaxDriverConnections(); //???
		char* GetDBMSName();
		char* GetVersion();
		char* GetDatabaseName();
		char* GetConnect();
		bool CanTransact(); //???
		bool CanUpdate(); //???
		
	protected:

		void SQLAlloc();
		void SQLFree();
		
	public:
		
		SQLHDBC m_hDbc;

	protected:

		char* m_szDBMSName;
		char* m_szDBName;
		char* m_szVersion;
		char* m_szConnString;

		int m_nRecordsAffected;
		long m_lLoginTimeout;
		long m_lQueryTimeout;
		bool m_bIsConnected;
		SQLHENV m_hEnv;
};

class CODBCRecordset
{
	public:
		/*
		enum datatypeEnum
		{
			typeChar = SQL_CHAR, 
			typeVarChar = SQL_VARCHAR, 
			typeLongVarChar = SQL_LONGVARCHAR, 
			typeWChar = SQL_WCHAR, 
			typeWVarChar = SQL_WVARCHAR,
			typeWLongVarChar = SQL_WLONGVARCHAR,
			typeDecimal = SQL_DECIMAL,
			typeNumeric = SQL_NUMERIC,
			typeSmallint = SQL_SMALLINT,
			typeInteger = SQL_INTEGER,
			typeReal = SQL_REAL,
			typeFloat = SQL_FLOAT,
			typeDouble = SQL_DOUBLE,
			typeBit = SQL_BIT,
			typeTinyint = SQL_TINYINT,
			typeBigInt = SQL_BIGINT,
			typeBinary = SQL_BINARY,
			typeVarBinary = SQL_VARBINARY,
			typeLongVarBinary =  SQL_LONGVARBINARY,
			typeDate = SQL_TYPE_DATE,
			typeTime = SQL_TYPE_TIME,
			typeTimeStamp = SQL_TYPE_TIMESTAMP,
			typeIntervalMonth = SQL_INTERVAL_MONTH,
			typeIntervalYear = SQL_INTERVAL_YEAR,
			typeIntervalYearToMonth = SQL_INTERVAL_YEAR_TO_MONTH,
			typeIntervalDay = SQL_INTERVAL_DAY,
			typeIntervalHour = SQL_INTERVAL_HOUR,
			typeIntervalMinute = SQL_INTERVAL_MINUTE,
			typeIntervalSecond = SQL_INTERVAL_SECOND,
			typeIntervalDayToHour = SQL_INTERVAL_DAY_TO_HOUR,
			typeIntervalDayToMinute = SQL_INTERVAL_DAY_TO_MINUTE,
			typeIntervalDayToSecond = SQL_INTERVAL_DAY_TO_SECOND,
			typeIntervalHourToMinute = SQL_INTERVAL_HOUR_TO_MINUTE,
			typeIntervalHourToSecond = SQL_INTERVAL_HOUR_TO_SECOND,
			typeIntervalMinuteToSecond = SQL_INTERVAL_MINUTE_TO_SECOND,
			typeGUID = SQL_GUID		
		};
		*/
				
		CODBCRecordset(CODBCDatabase* pDb);
		~CODBCRecordset();

		bool Open(char* szSqlStr);
		void Close();

		int GetFieldCount();
		int GetFieldIndex(char* szFieldName);
		long GetFieldLength(int nField);
		bool GetFieldName(int nField, char* szFieldName);
		bool GetFieldAttributes(int nField, char* szFieldName, int& nType, int& nLength);
		bool GetFieldValue(int nField, char* szData);
		bool GetFieldValue(char* szFieldName, char *szData);
		bool GetFieldValue(int nField, long *lData);
		bool GetFieldValue(char* szFieldName, long *lData);
		bool GetFieldValue(int nField, double *dblData);
		bool GetFieldValue(char* szFieldName, double *dblData);	
		bool GetFieldValue(int nField, struct tm* time);
		bool GetFieldValue(char* szFieldName, struct tm* time);
		
		bool MoveFirst();
		bool MovePrevious();
		bool MoveNext();
		bool MoveLast();
		bool IsEof() {return m_bIsEOF;};
		bool IsBof() {return m_bIsBOF;};
		
	protected:

		void AllocStmt();
		void FreeStmt();

	protected:
		
		unsigned int m_nNumRowsFetched;
		bool m_bIsEOF;
		bool m_bIsBOF;
		SQLHDBC m_hDbc;
		SQLHSTMT m_hStmt;
};

};

#endif
