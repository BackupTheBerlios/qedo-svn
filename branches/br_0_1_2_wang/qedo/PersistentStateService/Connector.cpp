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

ConnectorImpl::ConnectorImpl()
{
}

ConnectorImpl::ConnectorImpl(char* szImplID) :
	m_pSessionPool(NULL)
{
	strcpy(m_szImplID, szImplID);
}

ConnectorImpl::~ConnectorImpl()
{	
	// delete all sessions and session pool(s)!
	list <SessioImpl*> ::iterator sessio_iter;
	
	for (sessio_iter = m_lSessions.begin();
		 sessio_iter != m_lSessions.end();
		 sessio_iter++)
	{
		(*sessio_iter)->close();
	}

	m_lSessions.clear();

	if(m_pSessionPool->IsConnected())
		m_pSessionPool->close();

	delete m_pSessionPool;
	m_pSessionPool = NULL;

	_remove_ref();
}

////////////////////////////////////////////////////////////////////////////////
//return the ID of this implementation
////////////////////////////////////////////////////////////////////////////////
char* 
ConnectorImpl::implementation_id()
{
	return m_szImplID;
}

////////////////////////////////////////////////////////////////////////////////
//return the pid of the given storage object
////////////////////////////////////////////////////////////////////////////////
Pid* 
ConnectorImpl::get_pid(StorageObjectBase obj)
{
	if(obj==NULL)
		return NULL;

	return ((dynamic_cast <StorageObject*> (obj))->get_pid());
}

////////////////////////////////////////////////////////////////////////////////
//return the short pid of the given storage object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
ConnectorImpl::get_short_pid(StorageObjectBase obj)
{
	if(obj==NULL)
		return NULL;

	return ((dynamic_cast <StorageObject*> (obj))->get_short_pid());
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
	if(additional_parameters.length()==0)
		return NULL;

	string strConn = "";
	const char* szVal;

	//DSN=myodbc3-test;SERVER=haw;UID=root;PWD=;DATABASE=test;
	for(unsigned int i=0; i<additional_parameters.length(); i++)
	{
		strConn += additional_parameters[i].name;
		strConn += "=";
		additional_parameters[i].val >>= szVal;
		strConn += szVal;
		strConn += ";";
	}
	
	SessioImpl* pSession = new SessioImpl(access_mode, 
										strConn.c_str(), 
										(dynamic_cast <Connector*> (this)));

	if( pSession->Init()==FALSE ||
		pSession->DriverConnect(strConn.c_str())==FALSE )
		throw CORBA::PERSIST_STORE();

	m_lSessions.push_back(pSession);

	return (dynamic_cast <Sessio_ptr> (pSession));
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
	if(additional_parameters.length()==0)
		return NULL;

	string strConn = "";
	const char* szVal;

	//DSN=myodbc3-test;SERVER=haw;UID=root;PWD=;DATABASE=test;
	for(unsigned int i=0; i<additional_parameters.length(); i++)
	{
		strConn += additional_parameters[i].name;
		strConn += "=";
		additional_parameters[i].val >>= szVal;
		strConn += szVal;
		strConn += ";";
	}
	
	if(m_pSessionPool==NULL)
	{
		SessionPoolImpl* pSessionPool = 
			new SessionPoolImpl(access_mode, 
								tx_policy, 
								strConn.c_str(), 
								(dynamic_cast <Connector*> (this)));

		if( pSessionPool->Init()==FALSE ||
			pSessionPool->DriverConnect(strConn.c_str())==FALSE )
			throw CORBA::PERSIST_STORE();

		m_pSessionPool = pSessionPool;
	}
	else
	{
		if(!m_pSessionPool->DriverConnect(strConn.c_str()))
			throw CORBA::PERSIST_STORE();
	}
	
	return (dynamic_cast <SessionPool_ptr> (m_pSessionPool));
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
	map<const char*, StorageObjectFactory>::iterator sof_iter;
	sof_iter = m_SOFMap.find(storage_type_name);

	if(sof_iter != m_SOFMap.end())
	{
		return sof_iter->second;
	}
	else
	{
		typedef pair <const char*, StorageObjectFactory> Factory_Pair;
		m_SOFMap.insert( Factory_Pair(storage_type_name, factory) );
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
	map<const char*, StorageHomeFactory>::iterator shf_iter;
	shf_iter = m_SHFMap.find(storage_home_type_name);

	if(shf_iter != m_SHFMap.end())
	{
		return shf_iter->second;
	}
	else
	{
		typedef pair <const char*, StorageHomeFactory> Factory_Pair;
		m_SHFMap.insert( Factory_Pair(storage_home_type_name, factory) );
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
