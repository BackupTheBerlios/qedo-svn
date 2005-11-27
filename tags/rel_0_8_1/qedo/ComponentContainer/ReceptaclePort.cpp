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

#include "ReceptaclePort.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: ReceptaclePort.cpp,v 1.7 2003/10/30 17:24:14 stoinski Exp $";


namespace Qedo {


ReceptacleConnection::ReceptacleConnection (CORBA::Object_ptr connection,
											Cookie_impl* cookie)
: connection_ (CORBA::Object::_duplicate (connection)),
  cookie_ (cookie)
{
    cookie_->_add_ref();
}


ReceptacleConnection::ReceptacleConnection()
{
}


ReceptacleConnection::ReceptacleConnection (const ReceptacleConnection& rec_conn)
: connection_ (CORBA::Object::_duplicate (rec_conn.connection_.in())),
  cookie_ (rec_conn.cookie_)
{
	cookie_->_add_ref();
}


ReceptacleConnection& 
ReceptacleConnection::operator= (const ReceptacleConnection& rec_conn)
{
	connection_ = CORBA::Object::_duplicate (rec_conn.connection_.in());

	if (cookie_)
		cookie_->_remove_ref();

	cookie_ = rec_conn.cookie_;
	cookie_->_add_ref();

	return *this;
}


ReceptacleConnection::~ReceptacleConnection()
{
    cookie_->_remove_ref();
}


ConnectionDescription_impl* 
ReceptacleConnection::connection_description() const
{
	ConnectionDescription_impl* con_desc = new ConnectionDescription_impl (cookie_, connection_.in()); 

    return con_desc;
}


const CORBA::Object_ptr 
ReceptacleConnection::connection() const
{
    return CORBA::Object::_duplicate (connection_.in());
}


Cookie_impl*
ReceptacleConnection::cookie() const
{
	cookie_->_add_ref();
    return cookie_;
}


CORBA::Boolean 
ReceptacleConnection::same_connection (Components::Cookie* cookie) const
{
    return cookie_->equal (cookie);
}


ReceptaclePort::ReceptaclePort (const char* name, 
                                const char* type_id, 
								CORBA::Boolean is_multiplex)
: PortBase (name, type_id),
  is_multiplex_ (is_multiplex)
{
}


ReceptaclePort::ReceptaclePort()
{
}


ReceptaclePort::ReceptaclePort (const ReceptaclePort& rec_port)
: PortBase (rec_port),
  is_multiplex_ (rec_port.is_multiplex_),
  connections_ (rec_port.connections_)
{
}


ReceptaclePort::~ReceptaclePort()
{
}


Components::ConnectedDescriptions* 
ReceptaclePort::connected_descriptions() const
{
	Components::ConnectedDescriptions_var con_descs = 
        new Components::ConnectedDescriptions();

	QedoLock lock (connections_mutex_);

	con_descs->length (connections_.size());

	for (unsigned int i = 0; i < con_descs->length(); i++)
	{
		(*con_descs)[i] = connections_[i].connection_description(); 
	}

    return con_descs._retn();
}


Components::ReceptacleDescription* 
ReceptaclePort::receptacle_description() const
{
	Components::ConnectedDescriptions_var con_descs = connected_descriptions();

	Components::ReceptacleDescription_var rec_desc = new ReceptacleDescription_impl (port_name_.c_str(), 
																					 type_id_.c_str(), 
																					 is_multiplex_,
																					 con_descs);

    return rec_desc._retn();
}


Cookie_impl*
ReceptaclePort::add_connection (CORBA::Object_ptr connection)
throw (Components::InvalidConnection,
       Components::AlreadyConnected,
       Components::ExceededConnectionLimit)
{
	QedoLock lock (connections_mutex_);

	// Test whether already connected
	if ( !is_multiplex_ && connections_.size() > 0 )
	{
		DEBUG_OUT2 ("ReceptaclePort: Multiple connections not allowed for receptacle ", port_name_);
		throw Components::AlreadyConnected();
	}

	// Test for type of connection
	if (! connection->_is_a (type_id_.c_str()))
	{
		DEBUG_OUT2 ( "ReceptaclePort: Connection has wrong type for receptacle ", port_name_ );
        throw Components::InvalidConnection();
	}

    // Create cookie
	Cookie_impl* new_cookie = new Cookie_impl();

    // Create connection entry
    ReceptacleConnection new_entry (connection, new_cookie);

    connections_.push_back (new_entry);

    return new_cookie;
}


void 
ReceptaclePort::remove_connection (Components::Cookie* cookie)
throw (Components::InvalidConnection,
       Components::CookieRequired, 
       Components::NoConnection)
{
	if (is_multiplex_ && ! cookie)	// Multiple receptacle needs cookie
	{
		throw Components::CookieRequired();
	}

	ConnectionVector::iterator con_iter;

	QedoLock lock (connections_mutex_);

	// Search connection
    for (con_iter = connections_.begin();
         con_iter != connections_.end();
         con_iter++)
    {
		if ((! is_multiplex_ ) ||	// Simple receptacles always have at most 1 connection
			(*con_iter).same_connection (cookie)) // Multiple receptacles need matching cookie
		{
			connections_.erase (con_iter);

			DEBUG_OUT2 ( "ReceptaclePort: Disconnection from receptacle ", port_name_ );

			return;
		}
	}

	// Not found
	if (is_multiplex_)
	{
		throw Components::InvalidConnection();
	}
	else
	{
		throw Components::NoConnection();
	}
}

} // namespace Qedo
