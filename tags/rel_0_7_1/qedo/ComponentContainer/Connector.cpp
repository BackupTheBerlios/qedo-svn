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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifndef _QEDO_NO_DB

#include "Connector.h"

/*
* This connector can know how many sessions or session pools can be established
* in a given database. It can also control how many storagehome can share one 
* session or session pool dynamically and explicitly
* Supporting only one database is the limitation of this connector, but this
* can be improved in the future ;-)
*/

namespace Qedo
{

ConnectorImpl::ConnectorImpl() :
	iMaxConnections(-100)
{
}

ConnectorImpl::ConnectorImpl(char* szImplID) :
	iMaxConnections(-100), // -100 means this value is to be initiated
	strImplID_(szImplID)
{
}

ConnectorImpl::~ConnectorImpl()
{	
	std::cout << "ConnectorImpl::~ConnectorImpl()\n";

	// delete all sessions and session pool(s)!
	std::cout << lSessions_.size() << " session(s) in the list\n";
	int count = lSessions_.size();
	sessionIter_=lSessions_.begin();
	//for( sessionIter_=lSessions_.begin(); sessionIter_!=lSessions_.end(); sessionIter_++ )

	for(int i=0; i<count; i++)
	{
		std::cout << "close session...\n";
		(*sessionIter_)->close();
		std::cout << "session _remove_ref()...\n";
		(*sessionIter_)->_remove_ref();
		std::cout << "erase session from list...\n";
		if((*sessionIter_)!=NULL)
			std::cout << "session is not null!\n";
		lSessions_.erase(sessionIter_);
		std::cout << "end of erase session from list...\n";
	}

	std::cout << lSessionPools_.size() << " session pool(s) in the list\n";
	for( sessionPoolIter_=lSessionPools_.begin(); 
		 sessionPoolIter_!=lSessionPools_.end(); 
		 sessionPoolIter_++ )
	{
		std::cout << "close session pool...\n";
		(*sessionPoolIter_)->close();
		std::cout << "session pool _remove_ref...\n";
		(*sessionPoolIter_)->_remove_ref();
		std::cout << "erase session pool from list...\n";
		lSessionPools_.erase(sessionPoolIter_);
	}

	std::cout << homeFactoryMap_.size() << " home factory(ies) in the map\n";
	for( homeFactoryIter_=homeFactoryMap_.begin();
		 homeFactoryIter_!=homeFactoryMap_.end();
		 homeFactoryIter_++ )
	{
		std::cout << "release home factory...\n";
		//(homeFactoryIter_->second)->_remove_ref();
		StorageHomeFactory h_factory = homeFactoryIter_->second;
		if(h_factory)
		{
			std::cout << "h_factory is not null !\n";
			h_factory->_remove_ref();
			//delete h_factory;
		}
		else
			std::cout << "h_factory is null !\n";

		std::cout << "erase home factory from map...\n";
		homeFactoryMap_.erase(homeFactoryIter_);
	}

	// release factories
	std::cout << objFactoryMap_.size() << " object factory(ies) in the map\n";
	for( objFactoryIter_=objFactoryMap_.begin();
		 objFactoryIter_!=objFactoryMap_.end();
		 objFactoryIter_++ )
	{
		std::cout << "release object factory...\n";
		(objFactoryIter_->second)->_remove_ref();
		std::cout << "erase object factory from map...\n";
		objFactoryMap_.erase(objFactoryIter_);
	}

	std::cout << "end of destrctor of connector...\n";
}

bool
ConnectorImpl::checkMaxConnections()
{
	// '=0' means there is no specified limit or the limit is unknown
	// '>0' means that connector know how many sessions or session pools it can be create
	if( iMaxConnections > 0 )
		if( (lSessions_.size()+lSessionPools_.size()) >= iMaxConnections )
			return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//return the ID of this implementation
////////////////////////////////////////////////////////////////////////////////
char* 
ConnectorImpl::implementation_id()
{
	return (char*)(strImplID_.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//return the pid of the given storage object
////////////////////////////////////////////////////////////////////////////////
Pid* 
ConnectorImpl::get_pid(StorageObjectBase obj)
{
	StorageObject* pObj = dynamic_cast <StorageObject*> (obj);

	if( pObj==NULL )
		throw CORBA::PERSIST_STORE();
	
	Pid_var pPid = pObj->get_pid();

    return pPid._retn();
}

////////////////////////////////////////////////////////////////////////////////
//return the short pid of the given storage object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
ConnectorImpl::get_short_pid(StorageObjectBase obj)
{
	StorageObject* pObj = dynamic_cast <StorageObject*> (obj);

	if( pObj==NULL )
		throw CORBA::PERSIST_STORE();
	
    ShortPid_var pSpid = pObj->get_short_pid();

    return pSpid._retn();
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

	Sessio_var _session = Sessio::_nil();

	if( !lSessions_.empty() )
	{
		//get a session
		for( sessionIter_=lSessions_.begin(); sessionIter_!=lSessions_.end(); sessionIter_++ )
		{
			if( ((*sessionIter_)->getCapacity()) < MAX_CAPACITY )
			{
				_session = Sessio::_duplicate((*sessionIter_));
				return _session._retn();
			}
		}
	}
	
	if( !checkMaxConnections() )
	{
		NORMAL_ERR("The limitation of maximal connections is reached!");
		throw CORBA::PERSIST_STORE();
	}
	
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

	// this value will be initiated if session is created at first time
	if( iMaxConnections == -100 )
		iMaxConnections = pSession->GetMaxDriverConnections();

	lSessions_.push_back(pSession); //deep copy or!
	
	_session = Sessio::_duplicate(pSession);
	return _session._retn();
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

	SessionPool_var _sessionpool = SessionPool::_nil();

	if( !lSessionPools_.empty() )
	{
		//get a session pool
		for( sessionPoolIter_=lSessionPools_.begin();
			 sessionPoolIter_!=lSessionPools_.end(); 
			 sessionPoolIter_++ )
		{
			if( ((*sessionPoolIter_)->getCapacity()) < MAX_CAPACITY )
			{
				_sessionpool = SessionPool::_duplicate((*sessionPoolIter_));
				return _sessionpool._retn();
			}
		}
	}

	if( !checkMaxConnections() )
	{
		NORMAL_ERR("The limitation of maximal connections is reached!");
		throw CORBA::PERSIST_STORE();
	}

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
	
	SessionPoolImpl* pSessionPool = new SessionPoolImpl( access_mode, tx_policy, strConn.c_str(), this );

	if( pSessionPool->Init()==FALSE || pSessionPool->DriverConnect(strConn.c_str())==FALSE )
		throw CORBA::PERSIST_STORE();

	// this value will be initiated if session pool is created at first time
	if( iMaxConnections == -100 )
		iMaxConnections = pSessionPool->GetMaxDriverConnections();
	
	lSessionPools_.push_back(pSessionPool);

	_sessionpool = SessionPool::_duplicate(pSessionPool);
	return _sessionpool._retn();
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

	std::string strName = storage_type_name;
	objFactoryIter_ = objFactoryMap_.find(strName);

	if( objFactoryIter_!=objFactoryMap_.end() )
	{
		return objFactoryMap_[strName];
	}
	else
	{
		objFactoryMap_[strName] = factory;
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

	std::string strName = storage_home_type_name;
	homeFactoryIter_ = homeFactoryMap_.find(strName);
	
	if( homeFactoryIter_!=homeFactoryMap_.end() )
	{
		return homeFactoryMap_[strName];
	}
	else
	{
		homeFactoryMap_[strName] = factory;
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
#endif // _QEDO_NO_DB