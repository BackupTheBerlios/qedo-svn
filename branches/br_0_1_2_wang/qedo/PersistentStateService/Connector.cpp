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
ConnectorImpl::get_pid(StorageObjectBase_ptr obj)
{
	if(obj==NULL)
		return NULL;

	return ((dynamic_cast <StorageObject*> (obj))->get_pid());
}

////////////////////////////////////////////////////////////////////////////////
//return the short pid of the given storage object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
ConnectorImpl::get_short_pid(StorageObjectBase_ptr obj)
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
	
	SessioImpl* pSession = new SessioImpl(access_mode, strConn.c_str());

	if(!pSession->Init())
		throw CORBA::PERSIST_STORE();

	if(!pSession->DriverConnect(strConn.c_str()))
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
		SessionPoolImpl* pSessionPool = new SessionPoolImpl(access_mode, tx_policy, strConn.c_str());

		if(!pSessionPool->Init())
			throw CORBA::PERSIST_STORE();

		if(!pSessionPool->DriverConnect(strConn.c_str()))
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
////////////////////////////////////////////////////////////////////////////////
StorageObjectFactory_ptr 
ConnectorImpl::register_storage_object_factory(const char* storage_type_name,
                                           StorageObjectFactory_ptr factory)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage home factory previously registered with the given name
//; return NULL when there is no previously registered factory
////////////////////////////////////////////////////////////////////////////////
StorageHomeFactory_ptr 
ConnectorImpl::register_storage_home_factory(const char* storage_home_type_name,
                                         StorageHomeFactory_ptr factory)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//returns the session factory previously registered with the given name
//; return NULL when there is no previously registered factory
////////////////////////////////////////////////////////////////////////////////
SessionFactory_ptr 
ConnectorImpl::register_session_factory(const char* catalog_type_name,
                                    SessionFactory_ptr factory)
{
	//unnessicary
	throw CORBA::NO_IMPLEMENT();
}

////////////////////////////////////////////////////////////////////////////////
//returns the session pool factory previously registered with the given name
//; return NULL when there is no previously registered factory
////////////////////////////////////////////////////////////////////////////////
SessionPoolFactory_ptr 
ConnectorImpl::register_session_pool_factory(const char* catalog_type_name,
                                         SessionPoolFactory_ptr factory)
{
	throw CORBA::NO_IMPLEMENT();
}

} // namespace Qedo
