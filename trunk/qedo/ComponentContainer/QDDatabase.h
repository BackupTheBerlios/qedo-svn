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
#ifndef __QDDATABASE_H__
#define __QDDATABASE_H__


#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include <sys/types.h>
#endif
#include <sqlext.h>
#include "Util.h"

#define DEFAULT_TIMEOUT 15
#define MAX_INFO_LEN 64
#define MAX_COL_SIZE 256
#define MAX_CONNSTR_LEN 1024


namespace Qedo
{

class CONTAINERDLL_API QDDatabase
{
	public:

		QDDatabase() ;

		virtual ~QDDatabase() ;

		virtual bool Init();

		void close();

		void Destroy();

		bool DriverConnect( const char* szConnStr,
							char* szConnStrOut = NULL,
							HWND hWnd = NULL,
							const int nDrvConn = SQL_DRIVER_NOPROMPT);

		void SetLoginTimeout(const long nSeconds); //???

		void SetQueryTimeout(const long nSeconds); //???

		int GetRecordsAffected();

		int GetMaxDriverConnections();

		char* GetODBCVersion();

		bool ExecuteSQL(const char* szSqlStr);

		bool CanTransact();

		bool CanUpdate();

		bool IsConnected();

		bool IsTableExist(const char* szTableName);

		SQLHDBC getHDBC();

	protected:

		SQLHDBC hDbc_;
		SQLHENV hEnv_;
		int iRecordsAffected_;
		long lLoginTimeout_;
		long lQueryTimeout_;
		bool bIsConnected_;
		char* szODBCVersion_;
		char* szConnString_;
};

}; // namespace Qedo
#endif
