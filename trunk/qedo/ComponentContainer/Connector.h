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

#ifndef _QEDO_NO_DB

#include <map>
#include <string>
#include "Util.h"
#include "Output.h"
#include "CORBADepends.h"
#include "RefCountBase.h"
#include "Catalog.h"
#include "PSSStorageObject.h"

using namespace CosPersistentState;

#define DEFAULT_PROCESSOR_ACCOUNT 1;


namespace Qedo
{

class CONTAINERDLL_API ConnectorImpl : public virtual CosPersistentState::Connector,
									   public virtual RefCountLocalObject
{
	public:

		ConnectorImpl();

		ConnectorImpl(char* szImplID);
		
		virtual ~ConnectorImpl();

		bool checkMaxConnections();

		//
		// IDL:omg.org/CosPersistentState/Connector/implementation_id:1.0
		//
		char* implementation_id();

		//
		// IDL:omg.org/CosPersistentState/Connector/get_pid:1.0
		//
		Pid* get_pid(StorageObjectBase obj);

		//
		// IDL:omg.org/CosPersistentState/Connector/get_short_pid:1.0
		//
		ShortPid* get_short_pid(StorageObjectBase obj);

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
		StorageObjectFactory register_storage_object_factory(const char* storage_type_name,
															 StorageObjectFactory factory);

		//
		// IDL:omg.org/CosPersistentState/Connector/register_storage_home_factory:1.0
		//
		StorageHomeFactory register_storage_home_factory(const char* storage_home_type_name,
														 StorageHomeFactory factory);

		//
		// IDL:omg.org/CosPersistentState/Connector/register_session_factory:1.0
		//
		SessionFactory register_session_factory(const char* catalog_type_name,
												SessionFactory factory);

		//
		// IDL:omg.org/CosPersistentState/Connector/register_session_pool_factory:1.0
		//
		SessionPoolFactory register_session_pool_factory(const char* catalog_type_name,
														 SessionPoolFactory factory);

	private:
		
		static const int MAX_CAPACITY = 100;
		int iMaxConnections;
		std::string strImplID_;

		std::list<SessionImpl*> lSessions_;
		std::list<SessionImpl*>::iterator sessionIter_;
		std::list<SessionPoolImpl*> lSessionPools_;
		std::list<SessionPoolImpl*>::iterator sessionPoolIter_;
		
		std::map<std::string, StorageObjectFactory> objFactoryMap_;
		std::map<std::string, StorageObjectFactory>::iterator objFactoryIter_;
		std::map<std::string, StorageHomeFactory> homeFactoryMap_;
		std::map<std::string, StorageHomeFactory>::iterator homeFactoryIter_;
};

}; // namespace Qedo

#endif // _QEDO_NO_DB

#endif
