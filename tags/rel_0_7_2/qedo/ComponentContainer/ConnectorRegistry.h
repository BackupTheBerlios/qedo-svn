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
#ifndef __CONNECTOR_REGISTRY_H__
#define __CONNECTOR_REGISTRY_H__

#include <map>
#include <string>
#include "Util.h"
#include "Output.h"
#include "CORBADepends.h"
#include "RefCountBase.h"
#include "Connector.h"

using namespace CosPersistentState;


namespace Qedo
{

class CONTAINERDLL_API ConnectorRegistryImpl : public virtual CosPersistentState::ConnectorRegistry,
											   public virtual RefCountLocalObject
{
	public:

		ConnectorRegistryImpl();

		virtual ~ConnectorRegistryImpl();

		//
		// IDL:omg.org/CosPersistentState/ConnectorRegistry/find_connector:1.0
		//
		Connector_ptr find_connector( const char* implementation_id )
			throw(CosPersistentState::NotFound, CORBA::SystemException);
		
		//
		// IDL:omg.org/CosPersistentState/ConnectorRegistry/register_connector:1.0
		//
		void register_connector( Connector_ptr conn, const char* implementation_id )
			throw(CORBA::SystemException);

		//
		// IDL:omg.org/CosPersistentState/ConnectorRegistry/unregister_connector:1.0
		//
		void unregister_connector( const char* implementation_id )
			throw(CosPersistentState::NotFound, CORBA::SystemException);

	private:
		
		std::map<std::string, Connector_ptr> connectors_;
		std::map<std::string, Connector_ptr>::iterator connIter_;
};

}; // namespace Qedo

#endif
