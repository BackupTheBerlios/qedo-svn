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

Connector::Connector()
{

}

Connector::~Connector()
{

}

char* 
Connector::implementation_id()
{
	return NULL;
}

Pid* 
Connector::get_pid(StorageObjectBase_ptr obj)
{
	return NULL;
}

ShortPid* 
Connector::get_short_pid(StorageObjectBase_ptr obj)
{
	return NULL;
}

Sessio_ptr 
Connector::create_basic_session(AccessMode access_mode,
                                const char* catalog_type_name,
                                const ParameterList& additional_parameters)
{
	if(additional_parameters.length()==0)
		return NULL;

	string strConn = "";
	const char* szVal;

	//DSN=myodbc3-test;SERVER=haw;UID=root;PWD=;DATABASE=test;
	for(int i=0; i<additional_parameters.length(); i++)
	{
		strConn += additional_parameters[i].name;
		strConn += "=";
		additional_parameters[i].val >>= szVal;
		strConn += szVal;
		strConn += ";";
	}
	
	
	//Sessio pSession;
	//Qedo::CatalogBase pSession = new Qedo::CatalogBase(access_mode, strConn.c_str());
	//pSession->Init();
	//return pSession;

	return NULL;
}

SessionPool_ptr 
Connector::create_session_pool(AccessMode access_mode,
                               TransactionPolicy tx_policy,
                               const char* catalog_type_name,
                               const ParameterList& additional_parameters)
{
	return NULL;
}

StorageObjectFactory_ptr 
Connector::register_storage_object_factory(const char* storage_type_name,
                                           StorageObjectFactory_ptr factory)
{
	return NULL;
}

StorageHomeFactory_ptr 
Connector::register_storage_home_factory(const char* storage_home_type_name,
                                         StorageHomeFactory_ptr factory)
{
	return NULL;
}

SessionFactory_ptr 
Connector::register_session_factory(const char* catalog_type_name,
                                    SessionFactory_ptr factory)
{
	return NULL;
}

SessionPoolFactory_ptr 
Connector::register_session_pool_factory(const char* catalog_type_name,
                                         SessionPoolFactory_ptr factory)
{
	return NULL;
}

} // namespace Qedo
