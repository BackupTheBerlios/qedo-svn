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
#include "QDRecordset.h"


namespace Qedo
{

QDRecordset::QDRecordset() :
	hDbc_(SQL_NULL_HDBC),
	hStmt_(SQL_NULL_HSTMT),
	uiNumRowsFetched_(0)
{
}

QDRecordset::~QDRecordset()
{
}

void
QDRecordset::Init(SQLHDBC hDbc)
{
	hDbc_ = hDbc;
	hStmt_ = SQL_NULL_HSTMT;
	uiNumRowsFetched_ = 0;
	AllocStmt();
}

void 
QDRecordset::AllocStmt()
{
	SQLAllocHandle(SQL_HANDLE_STMT, hDbc_, &hStmt_);
}

void 
QDRecordset::Destroy()
{
	if(hStmt_ != SQL_NULL_HSTMT)
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt_);
	
	hStmt_ = SQL_NULL_HSTMT;
}

bool 
QDRecordset::Open(const char* szSqlStr)
{
	SQLRETURN ret;
	
	SQLSetStmtAttr(hStmt_, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER)SQL_SCROLLABLE, SQL_IS_INTEGER);
	SQLSetStmtAttr(hStmt_, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_DYNAMIC, SQL_IS_INTEGER);
	SQLSetStmtAttr(hStmt_, SQL_ATTR_ROWS_FETCHED_PTR, &uiNumRowsFetched_, 0);
	ret = SQLExecDirect(hStmt_, (SQLCHAR*)szSqlStr, SQL_NTS);

	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		ret = SQLFetch(hStmt_);

		if(ret==SQL_NO_DATA_FOUND)
			return FALSE;
		else
			return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void 
QDRecordset::Close()
{
	SQLCloseCursor(hStmt_);
}

//********** GetFieldValue **********//

// for SQL_C_CHAR, SQL_C_BINARY and SQL_C_VARBOOKMARK
bool 
QDRecordset::GetFieldValue(const int nField, unsigned char* szData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_CHAR, szData, nLength, &cbValue) == SQL_SUCCESS;
	//..................................................SQL_C_BINARY..........................................
	//..................................................SQL_C_VARBOOKMARK.....................................

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, unsigned char* szData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), szData);	
}

// for SQL_C_BIT
bool 
QDRecordset::GetFieldValue(const int nField, unsigned char& cData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_BIT, &cData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, unsigned char& cData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), cData);	
}

// for SQL_C_NUMERIC
/*
bool 
QDRecordset::GetFieldValue(const int nField, float& fltData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	SQLHDESC hDesc = NULL;
	SQL_NUMERIC_STRUCT NumStr;
	char szTmp[16];
	int i=0, iSign=1;
	int nLength = GetFieldLength(nField) + 1;
	long temp_val=0, divisor=1;

	SQLGetStmtAttr(hStmt_, SQL_ATTR_APP_ROW_DESC, &hDesc, 0, NULL); // wozu?

	SQLSetDescField (hDesc, 1, SQL_DESC_TYPE, (VOID*)SQL_C_NUMERIC, 0); // 1->column account
    SQLSetDescField (hDesc, 1, SQL_DESC_PRECISION, (VOID*)5, 0);
    SQLSetDescField (hDesc, 1, SQL_DESC_SCALE, (VOID*)3, 0);

	memset(NumStr.val, 0, 16);
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_ARD_TYPE, &NumStr, nLength, &cbValue) == SQL_SUCCESS;

	//Call to convert the little endian mode data into numeric data.
	for(i=0; i<16; i++)
	{
		szTmp[i] = NumStr.val[i];
	}

	//temp_val = atol(szTmp);
	
	if( NumStr.scale>0 )
	{
		for( i=0; i<NumStr.scale; i++ )	
			divisor *= 10;
	}

	fltData = (float)temp_val / (float)divisor;

	if(!NumStr.sign) 
		iSign = -1;
	else 
		iSign = 1;

	fltData *= iSign;

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, float& fltData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), fltData);	
}
*/
// for SQL_C_TINYINT
bool 
QDRecordset::GetFieldValue(const int nField, char& cData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_TINYINT, &cData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool
QDRecordset::GetFieldValue(const char* szFieldName, char& cData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), cData);
}

// for SQL_C_SHORT
bool 
QDRecordset::GetFieldValue(const int nField, short* sData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_SHORT, sData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, short* sData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), sData);	
}

// for SQL_C_LONG
bool 
QDRecordset::GetFieldValue(const int nField, long* lData)
{
	SQLRETURN ret;
	SQLINTEGER cbValue;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_LONG, lData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, long* lData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), lData);	
}

// for SQL_C_FLOAT
bool 
QDRecordset::GetFieldValue(const int nField, float* fltData)
{
	SQLINTEGER cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_FLOAT, fltData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, float* fltData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), fltData);	
}

// for SQL_C_DOUBLE
bool 
QDRecordset::GetFieldValue(const int nField, double* dblData)
{
	SQLINTEGER cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_DOUBLE, dblData, nLength, &cbValue) == SQL_SUCCESS;
	
	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, double* dblData)
{
	return GetFieldValue(GetFieldIndex(szFieldName), dblData);	
}

// for SQL_C_TYPE_TIMESTAMP(3.x) and SQL_C_TIMESTAMP(2.x)
/*
bool 
QDRecordset::GetFieldValue(const int nField, struct tm* time)
{
	SQLINTEGER cbValue;
	SQLRETURN ret;
	int nLength = GetFieldLength(nField) + 1;
	SQL_TIMESTAMP_STRUCT* sqltm = new SQL_TIMESTAMP_STRUCT;
	
	ret = SQLGetData(hStmt_, (SQLUSMALLINT)nField + 1, SQL_C_TYPE_TIMESTAMP, sqltm, nLength, &cbValue) == SQL_SUCCESS;
	
	if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{	
		time->tm_year = sqltm->year;
		time->tm_mon = sqltm->month - 1; //January must be = 0		
		time->tm_mday = sqltm->day;
		time->tm_hour = sqltm->hour;
		time->tm_min = sqltm->minute;
		time->tm_sec = sqltm->second;
		delete sqltm;

		return TRUE;
	}

	delete sqltm;
	
	return FALSE;
}

bool 
QDRecordset::GetFieldValue(const char* szFieldName, struct tm* time)
{
	return GetFieldValue(GetFieldIndex(szFieldName), time);	
}
*/
//********** end of GetFieldValue **********//

int 
QDRecordset::GetFieldIndex(const char* szFieldName)
{
	int nCol = 0;
	char szColName[MAX_COL_NAME_LEN];
	SQLSMALLINT nCols;
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
	SQLUINTEGER cbColDef;

	SQLNumResultCols(hStmt_, &nCols);
	
	while(nCol < nCols)
	{
		memset(szColName, 0, MAX_COL_NAME_LEN);
		SQLDescribeCol(hStmt_, nCol+1, (SQLCHAR*)szColName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);

		if(_stricmp(szColName, szFieldName) == 0)
			return nCol;
		nCol++;
	}

	return -1;
}

long 
QDRecordset::GetFieldLength(const int nField)
{
	SQLSMALLINT fSqlType, ibScale, fNullable;
	SQLUINTEGER cbColDef;
	
	SQLDescribeCol(hStmt_, nField + 1, NULL, 0, 0, &fSqlType, &cbColDef, &ibScale, &fNullable);

	return cbColDef;	
}

bool 
QDRecordset::GetFieldAttributes(const int nField, unsigned char* szFieldName, int& nType, int& nLength)
{
	SQLRETURN ret;
	SQLSMALLINT cbColNameLen, fSqlType, ibScale, fNullable;
	SQLUINTEGER cbColDef;
	
	ret = SQLDescribeCol(hStmt_, nField + 1, szFieldName, MAX_COL_NAME_LEN, &cbColNameLen, &fSqlType, &cbColDef, &ibScale, &fNullable);
	
	nType = fSqlType;
	nLength = cbColDef;

	return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO;	
}

int 
QDRecordset::GetFieldCount()
{
	SQLSMALLINT nFieldCount = 0;
	SQLNumResultCols(hStmt_, &nFieldCount);

	return nFieldCount;
}

} // namespace Qedo
