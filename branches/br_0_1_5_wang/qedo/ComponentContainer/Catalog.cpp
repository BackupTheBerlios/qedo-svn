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

CatalogBaseImpl::CatalogBaseImpl(const AccessMode eAM, 
								 const char* szConnString, 
								 Connector_ptr connector) :
	eAM_(eAM),
	connector_(connector)
{
	QDDatabase::QDDatabase();
	strcpy(szConnString_, szConnString);
}

CatalogBaseImpl::~CatalogBaseImpl()
{
	if(!lStorageHomeBases_.empty())
	{
		list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	
		for (storageHomeBase_iter = lStorageHomeBases_.begin();
			 storageHomeBase_iter != lStorageHomeBases_.end();
			 storageHomeBase_iter++)
		{
			(*storageHomeBase_iter)->_remove_ref();
		}

		lStorageHomeBases_.clear();
	}

	_remove_ref();
}

bool 
CatalogBaseImpl::Init()
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

bool 
CatalogBaseImpl::DriverConnect(const char* szConnStr, char* szConnStrOut, HWND hWnd, const int nDrvConn)
{
	SQLRETURN ret;
	SQLSMALLINT pcbConnStrOut;

	if(nDrvConn == SQL_DRIVER_PROMPT && hWnd == NULL)
		return FALSE;

	SQLSetConnectAttr(hDbc_, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)lLoginTimeout_, 0);
	SQLSetConnectAttr(hDbc_, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)lQueryTimeout_, 0);
	
	if(eAM_==READ_ONLY)
		SQLSetConnectAttr(hDbc_, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)SQL_MODE_READ_ONLY, 0);
	else
		SQLSetConnectAttr(hDbc_, SQL_ATTR_ACCESS_MODE, (SQLPOINTER)SQL_MODE_READ_WRITE, 0);

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

////////////////////////////////////////////////////////////////////////////////
//returns the accsss mode of this catalog
////////////////////////////////////////////////////////////////////////////////
AccessMode 
CatalogBaseImpl::access_mode()
{
	/*
	if(!IsConnected())
		return 0;
	
	int nAccessMode;

	SQLGetConnectAttr(hDbc_, SQL_ATTR_ACCESS_MODE, &nAccessMode, SQL_IS_INTEGER, NULL);

	if(nAccessMode == SQL_MODE_READ_ONLY)
		return READ_ONLY;
	else
		return READ_WRITE;
	*/
	return eAM_;
}

////////////////////////////////////////////////////////////////////////////////
//to obtain a storage home instance, it raises NotFound if it cannot find a 
//storage home that matches the given storage_home_id
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
CatalogBaseImpl::find_storage_home(const char* storage_home_id)
{
	//find it in the list
	list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	
	for (storageHomeBase_iter = lStorageHomeBases_.begin();
		 storageHomeBase_iter != lStorageHomeBases_.end();
		 storageHomeBase_iter++)
	{
		const char* szName = (*storageHomeBase_iter)->getStorageHomeName();
		
		if(strcmp(szName, storage_home_id)==0)
			return *storageHomeBase_iter;
	}
	
	//check it whether in the database
	if( IsConnected()==FALSE || IsTableExist(storage_home_id)==FALSE )
		throw CosPersistentState::NotFound();

	//if not in the list, new one.
#ifdef ORBACUS_ORB
	StorageHomeFactory factory = new OBNative_CosPersistentState::StorageHomeFactory_pre();	
#endif

#ifdef MICO_ORB
	StorageHomeFactory factory = new CosPersistentState::StorageHomeFactory_pre();
#endif
	
	factory = connector_->register_storage_home_factory(storage_home_id, factory);
	StorageHomeBase_ptr pStorageHomeBase = factory->create();
    StorageHomeBaseImpl* pStorageHomeBaseImpl = dynamic_cast <StorageHomeBaseImpl*> (pStorageHomeBase);
	pStorageHomeBaseImpl->Init((dynamic_cast <CatalogBase_ptr> (this)), storage_home_id);

	lStorageHomeBases_.push_back(pStorageHomeBaseImpl);

	//return (CosPersistentState::StorageHomeBase::_narrow(pStorageHomeBase));
	return pStorageHomeBase;
}

////////////////////////////////////////////////////////////////////////////////
//to locate a storage object with the given PID in the storage homes provided by
//the target catalog. It raises NotFound if it cannot find a storage object with
//this pid; otherwise, it returns an incarnation of this storage object
////////////////////////////////////////////////////////////////////////////////
StorageObjectBase 
CatalogBaseImpl::find_by_pid(const Pid& the_pid)
{
	string strPid = PSSHelper::convertPidToString(the_pid);

	// fetch the table name where pid can be found
	string strToExecute;
	unsigned char szStorageHome[MAX_COL_SIZE];

	QDRecordset prs;
	prs.Init(&hDbc_);

	strToExecute = "SELECT ownhome FROM pid_content WHERE pid LIKE ";
	strToExecute += strPid;
	strToExecute += ";";

	if(prs.Open(strToExecute.c_str()))
	{
		memset(szStorageHome, '\0', MAX_COL_SIZE);
		prs.GetFieldValue("ownhome", szStorageHome);
		prs.Close();
		prs.Destroy();
	}

	StorageHomeBase_ptr p_sHomeBase = find_storage_home((const char*)szStorageHome);
	
	if(p_sHomeBase)
		return ( (dynamic_cast <StorageHomeBaseImpl*> (p_sHomeBase))->find_by_pid(strPid) );
	else 
		return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//write to disk any cached modifications of storage object incarnations managed 
//by this catalog.
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBaseImpl::flush()
{
	string strFlush = "";
	list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	
	for( storageHomeBase_iter = lStorageHomeBases_.begin();
		 storageHomeBase_iter != lStorageHomeBases_.end();
		 storageHomeBase_iter++ )
	{
		strFlush += (*storageHomeBase_iter)->getFlush();
	}

	if(CanTransact()==TRUE && access_mode!=READ_ONLY)
	{
		if(ExecuteSQL(strFlush.c_str()))
		{
			SQLRETURN ret;
			ret = SQLEndTran(SQL_HANDLE_DBC, hDbc_, SQL_COMMIT);
			if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				for( storageHomeBase_iter = lStorageHomeBases_.begin();
					 storageHomeBase_iter != lStorageHomeBases_.end();
					 storageHomeBase_iter++ )
				{
					// the flush is successfull, we set the modified-value of each
					// storage object back to FALSE
					(*storageHomeBase_iter)->setBatchUnModified();
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
//refresh any cached storage object incarnations accesed by this catalog
//Calling refresh is unusual: most applications will never use this operation
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBaseImpl::refresh()
{
	list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	
	for( storageHomeBase_iter = lStorageHomeBases_.begin();
		 storageHomeBase_iter != lStorageHomeBases_.end();
		 storageHomeBase_iter++ )
	{
		(*storageHomeBase_iter)->Refresh();
	}
}

////////////////////////////////////////////////////////////////////////////////
//The operation free_all instructs the catalog implementation to set the 
//reference count of all its PSDL storage object instances to 0
////////////////////////////////////////////////////////////////////////////////
void 
CatalogBaseImpl::free_all()
{
	list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	
	for( storageHomeBase_iter = lStorageHomeBases_.begin();
		 storageHomeBase_iter != lStorageHomeBases_.end();
		 storageHomeBase_iter++ )
	{
		(*storageHomeBase_iter)->FreeAllStorageObjects();
	}
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

		bIsConnected_ = FALSE;

		if(hDbc_ == NULL)
			return;

		SQLDisconnect(hDbc_);
	}
}

SessionPoolImpl::SessionPoolImpl(AccessMode eAM, 
								 TransactionPolicy tx_policy, 
								 const char* szConnString, 
								 Connector_ptr connector) :
	tx_policy_(tx_policy)
{
	CatalogBaseImpl::CatalogBaseImpl(eAM, szConnString, connector);
}

SessionPoolImpl::~SessionPoolImpl()
{
	_remove_ref();
}

bool 
SessionPoolImpl::Init()
{
	SQLRETURN ret;

	ret = SQLSetEnvAttr( SQL_NULL_HENV, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_DRIVER, 0 );

	if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		ret = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HENV, &hEnv_ );

		if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
		{
			ret = SQLSetEnvAttr( hEnv_, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER );

			if(ret==SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				ret = SQLAllocHandle ( SQL_HANDLE_DBC, hEnv_, &hDbc_ );
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
	string strFlush = "";
	std::vector <Pid> vPidList; 

	//there is no function for deleting Pid from PidList, so the PidList should 
	//be first converted in a list of Pid
	for(CORBA::ULong i=0; i<pids.length(); i++)
	{
		vPidList.push_back(pids[i]);
	}

	list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	for( storageHomeBase_iter = lStorageHomeBases_.begin();
		 storageHomeBase_iter != lStorageHomeBases_.end();
		 storageHomeBase_iter++ )
	{
		strFlush += (*storageHomeBase_iter)->getFlushByPid(vPidList);
	}

	if(CanTransact()==TRUE && access_mode!=READ_ONLY)
	{
		if(ExecuteSQL(strFlush.c_str()))
		{
			SQLRETURN ret;
			ret = SQLEndTran(SQL_HANDLE_DBC, hDbc_, SQL_COMMIT);
			if(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
			{
				for( storageHomeBase_iter = lStorageHomeBases_.begin();
					 storageHomeBase_iter != lStorageHomeBases_.end();
					 storageHomeBase_iter++ )
				{
					// the flush is successfull, we set the modified-value of each
					// storage object back to FALSE
					(*storageHomeBase_iter)->setBatchUnModified();
				}
			}
		}
	}
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
	std::vector <Pid> vPidList; 

	//there is no function for deleting Pid from PidList, so the PidList should 
	//be first converted in a list of Pid
	for(CORBA::ULong i=0; i<pids.length(); i++)
	{
		vPidList.push_back(pids[i]);
	}

	list <StorageHomeBaseImpl*> ::iterator storageHomeBase_iter;
	for( storageHomeBase_iter = lStorageHomeBases_.begin();
		 storageHomeBase_iter != lStorageHomeBases_.end();
		 storageHomeBase_iter++ )
	{
		(*storageHomeBase_iter)->RefreshByPid(vPidList);
	}
}

////////////////////////////////////////////////////////////////////////////////
//return the transaction policy
////////////////////////////////////////////////////////////////////////////////
TransactionPolicy 
SessionPoolImpl::transaction_policy()
{
	return tx_policy_;
}

} // namespace Qedo
