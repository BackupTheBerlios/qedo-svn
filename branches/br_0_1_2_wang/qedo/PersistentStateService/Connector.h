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
#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include <CORBA.h>
#include <string>
#include "Util.h"
#include "RefCountBase.h"
#include "CORBADepends.h"
#include "Catalog.h"


#define DEFAULT_PROCESSOR_ACCOUNT 0;

using namespace CosPersistentState;
using namespace std;

namespace Qedo
{

class  Connector : public virtual CosPersistentState::Connector,
					public virtual Qedo::RefCountLocalObject
{
	public:

		Connector();
		~Connector();

		//
		// IDL:omg.org/CosPersistentState/Connector/implementation_id:1.0
		//
		char* implementation_id();

		//
		// IDL:omg.org/CosPersistentState/Connector/get_pid:1.0
		//
		Pid* get_pid(StorageObjectBase_ptr obj);

		//
		// IDL:omg.org/CosPersistentState/Connector/get_short_pid:1.0
		//
		ShortPid* get_short_pid(StorageObjectBase_ptr obj);

		//
		// IDL:omg.org/CosPersistentState/Connector/create_basic_session:1.0
		//
		Sessio_ptr create_basic_session(AccessMode access_mode,
										const char* catalog_type_name,
										const ParameterList& additional_parameters);

		//
		// IDL:omg.org/CosPersistentState/Connector/create_session_pool:1.0
		//
		SessionPool_ptr create_session_pool(AccessMode access_mode,
											TransactionPolicy tx_policy,
											const char* catalog_type_name,
											const ParameterList& additional_parameters);

		//
		// IDL:omg.org/CosPersistentState/Connector/register_storage_object_factory:1.0
		//
		StorageObjectFactory_ptr register_storage_object_factory(const char* storage_type_name,
																 StorageObjectFactory_ptr factory);

		//
		// IDL:omg.org/CosPersistentState/Connector/register_storage_home_factory:1.0
		//
		StorageHomeFactory_ptr register_storage_home_factory(const char* storage_home_type_name,
															 StorageHomeFactory_ptr factory);

		//
		// IDL:omg.org/CosPersistentState/Connector/register_session_factory:1.0
		//
		SessionFactory_ptr register_session_factory(const char* catalog_type_name,
													SessionFactory_ptr factory);

		//
		// IDL:omg.org/CosPersistentState/Connector/register_session_pool_factory:1.0
		//
		SessionPoolFactory_ptr register_session_pool_factory(const char* catalog_type_name,
															 SessionPoolFactory_ptr factory);
};

}; // namespace Qedo

#endif
