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

#ifndef __QDRECORDSET_H__
#define __QDRECORDSET_H__

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include <sys/types.h>
#endif
#include <sqlext.h>
#include <time.h>
#include <string>

#define MAX_COL_NAME_LEN 512

using namespace std;

namespace Qedo
{

class QDRecordset
{
	public:

		QDRecordset();

		~QDRecordset(){};

		void Init(SQLHDBC hDbc);

		bool Open(const char* szSqlStr);

		void Close();

		void Destroy();

		void AllocStmt();

		int GetFieldCount();

		int GetFieldIndex(const char* szFieldName);
		
		long GetFieldLength(const int nField);

		// give the field number, get the field name, type and length
		bool GetFieldAttributes(const int nField, unsigned char* szFieldName, int& nType, int& nLength);

		// for SQL_C_CHAR, SQL_C_BINARY and SQL_C_VARBOOKMARK
		bool GetFieldValue(const int nField, unsigned char* szData);
		bool GetFieldValue(const char* szFieldName, unsigned char *szData);

		// for SQL_C_BIT
		bool GetFieldValue(const int nField, unsigned char& cData);
		bool GetFieldValue(const char* szFieldName, unsigned char& cData);

		// for SQL_C_NUMERIC
		//bool GetFieldValue(const int nField, float& fltData);
		//bool GetFieldValue(const char* szFieldName, float& fltData);

		// for SQL_C_TINYINT
		bool GetFieldValue(const int nField, char& cData);
		bool GetFieldValue(const char* szFieldName, char& cData);

		// for SQL_C_SHORT
		bool GetFieldValue(const int nField, short* sData);
		bool GetFieldValue(const char* szFieldName, short* sData);

		// for SQL_C_LONG
		bool GetFieldValue(const int nField, long* lData);
		bool GetFieldValue(const char* szFieldName, long* lData);

		// for SQL_C_FLOAT
		bool GetFieldValue(const int nField, float* fltData);
		bool GetFieldValue(const char* szFieldName, float* fltData);

		// for SQL_C_DOUBLE
		bool GetFieldValue(const int nField, double* dblData);
		bool GetFieldValue(const char* szFieldName, double* dblData);

		// for SQL_C_TYPE_TIMESTAMP(3.x) and SQL_C_TIMESTAMP(2.x)
		bool GetFieldValue(const int nField, struct tm* time);
		bool GetFieldValue(const char* szFieldName, struct tm* time);

	private:
		
		SQLHDBC m_hDbc;
		SQLHSTMT m_hStmt;
		unsigned int m_nNumRowsFetched;
};

}; // namespace Qedo

#endif
