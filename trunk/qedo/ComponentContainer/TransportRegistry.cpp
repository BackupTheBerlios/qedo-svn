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


#ifndef _QEDO_NO_STREAMS


#include "TransportRegistry.h"

#include "Output.h"

static char rcsid[] UNUSED = "$Id: TransportRegistry.cpp,v 1.2 2003/10/17 09:11:41 stoinski Exp $";

namespace Qedo {


TransportEntry::TransportEntry (const char* transport_protocol, TransportEndpointFactory* transport_factory)
: transport_protocol_ (transport_protocol),
  factory_ (transport_factory)
{
	factory_->_add_ref();
}

	
TransportEntry::TransportEntry()
{
	factory_ = 0;
}


TransportEntry::TransportEntry (const TransportEntry& entry)
: transport_protocol_ (entry.transport_protocol_),
  factory_ (entry.factory_)
{
	factory_->_add_ref();
}


TransportEntry&
TransportEntry::operator= (const TransportEntry& entry)
{
	transport_protocol_ = entry.transport_protocol_;

	if (factory_)
		factory_->_remove_ref();

	factory_ = entry.factory_;
	factory_->_add_ref();

	return *this;
}


TransportEntry::~TransportEntry()
{
	if (factory_)
		factory_->_remove_ref();
}


TransportVector TransportRegistry::transports_;


void
TransportRegistry::register_transport (const char* transport_protocol, TransportEndpointFactory* transport_factory)
{
	DEBUG_OUT2 ("TransportRegistry: New transport registered for transport protocol ", transport_protocol);

	TransportEntry new_transport (transport_protocol, transport_factory);

	transports_.push_back (new_transport);
}


void
TransportRegistry::clear_registry()
{
	transports_.erase (transports_.begin(), transports_.end());
}


} // namespace Qedo


#endif
