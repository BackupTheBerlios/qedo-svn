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


#include "TransportEndpoint.h"
#include "SinkPort.h"			// SinkPort.cpp and TransportEndpoint.cpp depend on each other, that's why the include is found here and not in the header
#include "Output.h"

#include <cstdlib>
#include <ctime>

static char rcsid[] UNUSED = "$Id: TransportEndpoint.cpp,v 1.3 2003/12/16 13:37:32 stoinski Exp $";

namespace Qedo {


TransportEndpoint::TransportEndpoint()
{
	// Initialize random numbers generator
	std::srand ((unsigned)std::time (NULL));
	rand();
}


TransportEndpoint::~TransportEndpoint()
{
	DEBUG_OUT ("TransportEndpoint: Destructor called");
}


int
TransportEndpoint::rand_int()
{
	return std::rand();
}


SourceTransportEndpoint::SourceTransportEndpoint()
{
}


SourceTransportEndpoint::~SourceTransportEndpoint()
{
	DEBUG_OUT ("SourceTransportEndpoint: Destructor called");
}


SinkTransportEndpoint::SinkTransportEndpoint (SinkPort* my_sink, StreamDataDispatcher* dispatcher)
: my_sink_ (my_sink),
  dispatcher_ (dispatcher)
{
	my_sink_->_add_ref();
	dispatcher_->_add_ref();
}


SinkTransportEndpoint::~SinkTransportEndpoint()
{
	DEBUG_OUT ("SinkTransportEndpoint: Destructor called");

	my_sink_->_remove_ref();
	dispatcher_->_remove_ref();
}


TransportEndpointFactory::TransportEndpointFactory()
{
}


TransportEndpointFactory::~TransportEndpointFactory()
{
	DEBUG_OUT ("TransportEndpointFactory: Destructor called");
}


} // namespace Qedo

#endif
