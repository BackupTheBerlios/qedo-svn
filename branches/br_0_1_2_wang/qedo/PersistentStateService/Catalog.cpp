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

CatalogBaseImpl::CatalogBaseImpl(const AccessMode eAM, const char* szConnString)
{
	QDDatabase::QDDatabase();

	m_eAM = eAM;
	strcpy(m_szConnString, szConnString);
}

CatalogBaseImpl::~CatalogBaseImpl()
{
}

bool 
CatalogBaseImpl::Init()
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

bool 
CatalogBaseImpl::DriverConnect(const char* szConnStr, char* szConnStrOut, HWND hWnd, const int nDrvConn)
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

////////////////////////////////////////////////////////////////////////////////
//returns the accsss mode of this catalog
////////////////////////////////////////////////////////////////////////////////
AccessMode 
CatalogBaseImpl::access_mode()
{
	if(!IsConnected())
		return 0;
	
	int nAccessMode;

	SQLGetConnectAttr(m_hDbc, SQL_ATTR_ACCESS_MODE, &nAccessMode, SQL_IS_INTEGER, NULL);

	if(nAccessMode == SQL_MODE_READ_ONLY)
		return READ_ONLY;
	else
		return READ_WRITE;
}

////////////////////////////////////////////////////////////////////////////////
//to obtain a storage home instance, it raises NotFound if it cannot find a 
//storage home that matches the given storage_home_id
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
CatalogBaseImpl::find_storage_home(const char* storage_home_id)
{
	if(!IsConnected())
		return NULL;

	//
	//ToDo: add a function to find the base-home-name of storage_home_id
	//If not found, raises the exception NotFound()
	//
	char* base_home_id = NULL;

	if(!IsTableExist(storage_home_id))
		throw CosPersistentState::NotFound();

	list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	
	for (storageHomeBase_iter = m_lStorageHomeBases.begin();
		 storageHomeBase_iter != m_lStorageHomeBases.end();
		 storageHomeBase_iter++)
	{
		const char* szName = (*storageHomeBase_iter)->getOwnStorageHomeName();
		
		if(strcmp(szName, storage_home_id)==0)
			return *storageHomeBase_iter;
	}

	StorageHomeBaseImpl* pStorageHomeBase = 
		new StorageHomeBaseImpl((dynamic_cast <CatalogBase_ptr> (this)), base_home_id, storage_home_id);

	m_lStorageHomeBases.push_back(pStorageHomeBase);

	//return (CosPersistentState::StorageHomeBase::_narrow(pStorageHomeBase));
	return (dynamic_cast <StorageHomeBase_ptr> (pStorageHomeBase));
}

////////////////////////////////////////////////////////////////////////////////
//to locate a storage object with the given PID in the storage homes provided by
//the target catalog. It raises NotFound if it cannot find a storage object with
//this pid; otherwise, it returns an incarnation of this storage object
////////////////////////////////////////////////////////////////////////////////
StorageObjectBase_ptr 
CatalogBaseImpl::find_by_pid(const Pid& the_pid)
{
	int iLength = the_pid.length();

	unsigned char* sz_Pid = new unsigned char[iLength];
	
	for(int i=0; i<iLength; i++)
	{
		sz_Pid[i] = the_pid[i];
	}

	// fetch the table name where pid can be found
	string strToExecute;
	unsigned char szBaseHome[MAX_COL_SIZE];
	unsigned char szOwnHome[MAX_COL_SIZE];
	unsigned char szSpid[MAX_COL_SIZE];

	QDRecordset prs = QDRecordset(&m_hDbc);

	strToExecute = "select basehome, ownhome from pid_content where pid like ";
	strToExecute.append((const char*)sz_Pid);
	strToExecute += ";";

	if(prs.Open(strToExecute.c_str()))
	{
		memset(szBaseHome, '\0', MAX_COL_SIZE);
		memset(szOwnHome, '\0', MAX_COL_SIZE);

		prs.GetFieldValue("BASEHOME", szBaseHome);
		prs.GetFieldValue("OWNHOME", szOwnHome);

		prs.Close();
	}

	strToExecute = "select spid from ";
	strToExecute.append((const char*)szBaseHome);
	strToExecute += " where pid like ";
	strToExecute.append((const char*)sz_Pid);
	strToExecute += ";";

	if(prs.Open(strToExecute.c_str()))
	{
		memset(szSpid, '\0', MAX_COL_SIZE);
		prs.GetFieldValue("SPID", szSpid);
		prs.Close();
		prs.Destroy();
	}

	StorageHomeBase_ptr p_sHomeBase = find_storage_home((const char*)szOwnHome);

	return (p_sHomeBase->find_by_short_pid(NULL));
}

////////////////////////////////////////////////////////////////////////////////
//The flush operation instructs the PSS implementation to write to disk any 
//cached modifications of storage object incarnations managed by this catalog.
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBaseImpl::flush()
{
	if(CanTransact()==TRUE && access_mode!=READ_ONLY)
		SQLEndTran(SQL_HANDLE_DBC, m_hDbc, SQL_COMMIT);
}

////////////////////////////////////////////////////////////////////////////////
//Calling refresh is unusual: most applications will never use this operation
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBaseImpl::refresh()
{
}

////////////////////////////////////////////////////////////////////////////////
//The operation free_all instructs the catalog implementation to set the 
//reference count of all its PSDL storage object instances to 0
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBaseImpl::free_all()
{

}

////////////////////////////////////////////////////////////////////////////////
//The operation close terminates the catalog. When closed, the catalog is also 
//flushed. If the catalog is associated with one or more transactions when close
//is called, these transactions are marked roll-back only.
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBaseImpl::close()
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

SessionPoolImpl::SessionPoolImpl(AccessMode eAM, TransactionPolicy tx_policy, const char* szConnString)
{
	CatalogBaseImpl::CatalogBaseImpl(eAM, szConnString);
	m_tx_policy = tx_policy;
}

SessionPoolImpl::~SessionPoolImpl()
{
}

bool 
SessionPoolImpl::Init()
{
	SQLRETURN ret;

	ret = SQLSetEnvAttr( SQL_NULL_HENV, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_DRIVER, 0 );

	if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		ret = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HENV, &m_hEnv );

		if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			ret = SQLSetEnvAttr( m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER );

			if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				ret = SQLAllocHandle ( SQL_HANDLE_DBC, m_hEnv, &m_hDbc );
				return ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO; 
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//with NON_TRANSACTIONAL, it makes durable all of the modifications to active
//incarnations whose PIDs are contained in the pids parameter, regardless of the
//transactional context of the calling thread
//
//with TRANSACTIONAL, it behaves as follows:
//$$ if the invoking thread is accociated with a transcation context, it makes
//   durable all state modifications made in the current transactional scope for
//   incarnations whose PIDs are contained in the pids parameter, flushing them
//   to the underying datastore.
//$$ if the invoking thread is not associated with a transactional context, the 
//   standard exception TRANSACTION_REQUIRED is raised.
//if the session pool implementation is unable to reconcile the changes and make
//them durable, then the PERSISTENT_STORE standard exception is raised 
////////////////////////////////////////////////////////////////////////////////
void 
SessionPoolImpl::flush_by_pids(const PidList& pids)
{

}

////////////////////////////////////////////////////////////////////////////////
//with NON_TRANSACTIONAL and the invoking thread is associated with a transcatinal
//context, it causes the following behavior:
//$$ All incarnations involved in the current transaction context, and associated 
//   with given pids, are refreshed.
//$$ If any of the given PIDs are associated with incarnations which are themselves
//   not associated with the current transaction, the INVALID_TRANSACTION standard
//   exception is raised
//
//with TRANSACTIONAL and the invoking thread is not associated with a transaction
//context, the standard exception TRANSACTION_REQUIRED is raised.
//if the session pool implementatin is unable to refresh the appropriate incarnations,
//the PERSIST_STORE standard exception is raised
////////////////////////////////////////////////////////////////////////////////
void 
SessionPoolImpl::refresh_by_pids(const PidList& pids)
{

}

TransactionPolicy 
SessionPoolImpl::transaction_policy()
{
	return m_tx_policy;
}

} // namespace Qedo
