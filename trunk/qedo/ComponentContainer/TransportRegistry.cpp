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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifndef _QEDO_NO_STREAMS


#include "TransportRegistry.h"

#include "Output.h"

static char rcsid[] UNUSED = "$Id: TransportRegistry.cpp,v 1.4 2004/06/24 14:36:08 tom Exp $";

namespace Qedo {


TransportEntry::TransportEntry (const char* transport_profile, TransportEndpointFactory* transport_factory)
: transport_profile_ (transport_profile),
  factory_ (transport_factory)
{
	factory_->_add_ref();
}

	
TransportEntry::TransportEntry()
{
	factory_ = 0;
}


TransportEntry::TransportEntry (const TransportEntry& entry)
: transport_profile_ (entry.transport_profile_),
  factory_ (entry.factory_)
{
	factory_->_add_ref();
}


TransportEntry&
TransportEntry::operator= (const TransportEntry& entry)
{
	transport_profile_ = entry.transport_profile_;

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
TransportRegistry::register_transport (const char* transport_profile, TransportEndpointFactory* transport_factory)
{
	DEBUG_OUT2 ("TransportRegistry: New transport registered for transport profile ", transport_profile);

	TransportEntry new_transport (transport_profile, transport_factory);

	transports_.push_back (new_transport);
}


void
TransportRegistry::clear_registry()
{
	transports_.erase (transports_.begin(), transports_.end());
}


} // namespace Qedo


#endif
