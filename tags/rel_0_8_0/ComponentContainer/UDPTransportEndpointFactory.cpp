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


#include "UDPTransportEndpointFactory.h"
#include "TransportRegistry.h"
#include "Output.h"
#include "Valuetypes.h"

#include <cstdlib>
#include <cstring>

static char rcsid[] UNUSED = "$Id: UDPTransportEndpointFactory.cpp,v 1.2 2004/06/24 14:36:08 tom Exp $";

namespace Qedo {


UDPTransportEndpointFactory::UDPTransportEndpointFactory()
{
	TransportRegistry::register_transport ("CCM_UDP", this);
}


UDPTransportEndpointFactory::~UDPTransportEndpointFactory()
{
	DEBUG_OUT ("UDPTransportEndpointFactory: Destructor called");
}


SourceTransportEndpoint* 
UDPTransportEndpointFactory::create_source_tep()
{
	DEBUG_OUT ("UDPTransportEndpointFactory: create_source_tep() called");

	return new UDPSourceTransportEndpoint();
}


SinkTransportEndpoint*
UDPTransportEndpointFactory::create_sink_tep (SinkPort* sink_port, StreamDataDispatcher* dispatcher)
{
	DEBUG_OUT ("UDPTransportEndpointFactory: create_sink_tep() called");

	return new UDPSinkTransportEndpoint (sink_port, dispatcher);
}


} // namespace Qedo

#endif

