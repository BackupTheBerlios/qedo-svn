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
	std::cout << "destruct ConnectorRegistryImpl\n";
}

Connector_ptr
ConnectorRegistryImpl::find_connector(const char* implementation_id)
    throw(CosPersistentState::NotFound, CORBA::SystemException)
{
	std::string strID = implementation_id;

	connIter_ = connectors_.find(strID);

	if( connIter_==connectors_.end() )
		throw CosPersistentState::NotFound();
	
	Connector_var pConnector = connectors_[strID];

    return pConnector._retn();
}

void
ConnectorRegistryImpl::register_connector(Connector_ptr conn, const char* implementation_id)
    throw(CORBA::SystemException)
{
	std::string strID = implementation_id;
	connectors_[strID] = Connector::_duplicate(conn);
}

void
ConnectorRegistryImpl::unregister_connector(const char* implementation_id)
    throw(CosPersistentState::NotFound,CORBA::SystemException)
{
	std::string strID = implementation_id;

	connIter_ = connectors_.find(strID);

	if( connIter_ == connectors_.end())
		throw CosPersistentState::NotFound();
	
	ConnectorImpl* pConn = dynamic_cast <ConnectorImpl*> (connectors_[strID]);
	pConn->_remove_ref();
	connectors_.erase(strID);
}

} // namespace Qedo

