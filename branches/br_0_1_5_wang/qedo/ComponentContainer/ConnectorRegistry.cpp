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
#include "ConnectorRegistry.h"


namespace Qedo
{

ConnectorRegistryImpl::ConnectorRegistryImpl()
{
}

ConnectorRegistryImpl::~ConnectorRegistryImpl()
{
}

Connector_ptr
ConnectorRegistryImpl::find_connector(const char* implementation_id)
    throw(CosPersistentState::NotFound, CORBA::SystemException)
{
	DEBUG_OUT("ConnectorRegistryImpl::find_connector() is called");

    Connector_var pConnector = Connector::_nil();

	connIter_ = connectors_.find(implementation_id);

	if( connIter_==connectors_.end() )
		throw CosPersistentState::NotFound();
	else
		pConnector = connectors_[implementation_id];

    return pConnector._retn();
}

void
ConnectorRegistryImpl::register_connector(Connector_ptr conn, const char* implementation_id)
    throw(CORBA::SystemException)
{
	DEBUG_OUT("ConnectorRegistryImpl::register_connector() is called");

    connectors_[implementation_id] = conn;
}

void
ConnectorRegistryImpl::unregister_connector(const char* implementation_id)
    throw(CosPersistentState::NotFound,CORBA::SystemException)
{
	DEBUG_OUT("ConnectorRegistryImpl::unregister_connector() is called");

	connIter_ = connectors_.find(implementation_id);

	if( connIter_ == connectors_.end())
		throw CosPersistentState::NotFound();
	else
		connectors_.erase(implementation_id);
}

} // namespace Qedo
