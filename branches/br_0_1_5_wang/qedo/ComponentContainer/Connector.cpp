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
#include "Connector.h"


namespace Qedo
{

ConnectorImpl::ConnectorImpl() :
	pSessionPool_(NULL)
{
}

ConnectorImpl::ConnectorImpl(char* szImplID) :
	pSessionPool_(NULL)
{
	strcpy(szImplID_, szImplID);
}

ConnectorImpl::~ConnectorImpl()
{	
	// delete all sessions and session pool(s)!
	if(!lSessions_.empty())
	{
		std::list<SessionImpl*>::iterator sessionIter;

		for( sessionIter=lSessions_.begin(); sessionIter!=lSessions_.end(); sessionIter++ )
			(*sessionIter)->close();

		lSessions_.clear();
	}

	pSessionPool_->close();
	delete pSessionPool_;
	pSessionPool_ = NULL;

	_remove_ref();
}

////////////////////////////////////////////////////////////////////////////////
//return the ID of this implementation
////////////////////////////////////////////////////////////////////////////////
char* 
ConnectorImpl::implementation_id()
{
	char* szImplID = NULL;
	strcpy(szImplID, szImplID_);

	return szImplID;
}

////////////////////////////////////////////////////////////////////////////////
//return the pid of the given storage object
////////////////////////////////////////////////////////////////////////////////
Pid* 
ConnectorImpl::get_pid(StorageObjectBase obj)
{
	Pid* pPid = NULL;
	StorageObject* pObj = dynamic_cast <StorageObject*> (obj);

	if( pObj==NULL )
		throw CORBA::PERSIST_STORE();
	
    pPid = pObj->get_pid();

    return pPid;
}

////////////////////////////////////////////////////////////////////////////////
//return the short pid of the given storage object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
ConnectorImpl::get_short_pid(StorageObjectBase obj)
{
	ShortPid* pSpid = NULL;
	StorageObject* pObj = dynamic_cast <StorageObject*> (obj);

	if( pObj==NULL )
		throw CORBA::PERSIST_STORE();
	
    pSpid = pObj->get_short_pid();

    return pSpid;
}

////////////////////////////////////////////////////////////////////////////////
//creates a basic, non-transactional session. Typically the additional parameters
//will contain information such as file name, database name, or authentication
//information. If the implementation cannot provide a session with the desired
//access mode (or higher) it raises the standard exception PERSIST_STORE
////////////////////////////////////////////////////////////////////////////////
Sessio_ptr 
ConnectorImpl::create_basic_session(AccessMode access_mode,
									const char* catalog_type_name,
									const ParameterList& additional_parameters)
{
	DEBUG_OUT("ConnectorImpl::create_basic_session() is called");

	if(additional_parameters.length()==0)
		return NULL;

	std::string strConn = "";
	const char* szVal;
	
	//DSN=myodbc3-test;SERVER=haw;UID=root;PWD=;DATABASE=test;
	for(CORBA::ULong i=0; i<additional_parameters.length(); i++)
	{
		strConn += additional_parameters[i].name;
		strConn += "=";
		additional_parameters[i].val >>= szVal;
		strConn += szVal;
		strConn += ";";
	}
	
	SessionImpl* pSession = new SessionImpl(access_mode, strConn.c_str(), this);

	if( pSession->Init()==FALSE || pSession->DriverConnect(strConn.c_str())==FALSE )
		throw CORBA::PERSIST_STORE();

	lSessions_.push_back(pSession);

	return pSession;
}

////////////////////////////////////////////////////////////////////////////////
//creates a new session pool
////////////////////////////////////////////////////////////////////////////////
SessionPool_ptr 
ConnectorImpl::create_session_pool(AccessMode access_mode,
									TransactionPolicy tx_policy,
									const char* catalog_type_name,
									const ParameterList& additional_parameters)
{
	DEBUG_OUT("ConnectorImpl::create_session_pool() is called");

	if(additional_parameters.length()==0)
		return NULL;

	std::string strConn = "";
	const char* szVal;

	//DSN=myodbc3-test;SERVER=haw;UID=root;PWD=;DATABASE=test;
	for(CORBA::ULong i=0; i<additional_parameters.length(); i++)
	{
		strConn += additional_parameters[i].name;
		strConn += "=";
		additional_parameters[i].val >>= szVal;
		strConn += szVal;
		strConn += ";";
	}
	
	if(pSessionPool_==NULL)
	{
		pSessionPool_ = new SessionPoolImpl( access_mode, tx_policy, strConn.c_str(), this );

		if( pSessionPool_->Init()==FALSE ||
			pSessionPool_->DriverConnect(strConn.c_str())==FALSE )
			throw CORBA::PERSIST_STORE();
	}
	else
	{
		if(!pSessionPool_->DriverConnect(strConn.c_str()))
			throw CORBA::PERSIST_STORE();
	}
	
	return pSessionPool_;
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage object factory previously registered with the given name
//; return NULL when there is no previously registered factory
//To invoke this method, a new instance of StorageObjectFactory and its 
//storage_type_name are necessary. When the factory is not found, we register 
//it in the map and return NULL; Otherwise the registert factory will be returned. 
//That means, to retrive a factory this method can be perhaps twice invoked.
////////////////////////////////////////////////////////////////////////////////
StorageObjectFactory
ConnectorImpl::register_storage_object_factory(const char* storage_type_name,
											   StorageObjectFactory factory)
{
	DEBUG_OUT("ConnectorImpl::register_storage_object_factory() is called");

	std::map<const char*, StorageObjectFactory>::iterator objFactoryIter;
	objFactoryIter = objFactoryMap_.find(storage_type_name);

	if( objFactoryIter!=objFactoryMap_.end() )
	{
		return objFactoryMap_[storage_type_name];
	}
	else
	{
		objFactoryMap_[storage_type_name] = factory;
		return NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage home factory previously registered with the given name
//; return NULL when there is no previously registered factory
//To invoke this method, a new instance of StorageHomeFactory and its 
//storage_home_type_name are necessary. When the factory is not found, we 
//register it in the map and return NULL; Otherwise the registert factory will 
//be returned. That means, to retrive a factory this method can be perhaps 
//twice invoked.
////////////////////////////////////////////////////////////////////////////////
StorageHomeFactory
ConnectorImpl::register_storage_home_factory(const char* storage_home_type_name,
											 StorageHomeFactory factory)
{
	DEBUG_OUT("ConnectorImpl::register_storage_home_factory() is called");

	std::map<const char*, StorageHomeFactory>::iterator homeFactoryIter;
	homeFactoryIter = homeFactoryMap_.find(storage_home_type_name);

	if( homeFactoryIter!=homeFactoryMap_.end() )
	{
		return homeFactoryMap_[storage_home_type_name];
	}
	else
	{
		homeFactoryMap_[storage_home_type_name] = factory;
		return NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//returns the session factory previously registered with the given name
//; return NULL when there is no previously registered factory
////////////////////////////////////////////////////////////////////////////////
SessionFactory
ConnectorImpl::register_session_factory(const char* catalog_type_name,
										SessionFactory factory)
{
	//unnecessary to implement
	throw CORBA::NO_IMPLEMENT();
}

////////////////////////////////////////////////////////////////////////////////
//returns the session pool factory previously registered with the given name
//; return NULL when there is no previously registered factory
////////////////////////////////////////////////////////////////////////////////
SessionPoolFactory
ConnectorImpl::register_session_pool_factory(const char* catalog_type_name,
											 SessionPoolFactory factory)
{
	//unnecessary to implement
	throw CORBA::NO_IMPLEMENT();
}

} // namespace Qedo
