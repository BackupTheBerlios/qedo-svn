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


#include "SinkStreamPortServant.h"
#include "Output.h"


static char rcsid[] UNUSED = "$Id: SinkStreamPortServant.cpp,v 1.2 2003/10/17 09:11:40 stoinski Exp $";

namespace Qedo {
	

SinkStreamPortServant::SinkStreamPortServant (const char* port_name)
: port_name_ (port_name)
{
}


SinkStreamPortServant::~SinkStreamPortServant()
{
	DEBUG_OUT ("SinkStreamPortServant: Destructor called");
}


void 
SinkStreamPortServant::check_streamtype (const CORBA::RepositoryIdSeq& streamtypes)
throw(StreamComponents::UnsupportedStreamtype,
	  CORBA::SystemException)
{
	SinkPort& sink = stream_ccm_object_executor_->get_sink (port_name_.c_str());
	sink.check_streamtype (streamtypes);
}


void 
SinkStreamPortServant::consider_transport (StreamComponents::TransportSpec& the_transport)
throw(StreamComponents::AlreadyBound,
	  StreamComponents::TransportFailure,
	  CORBA::SystemException)
{
	SinkPort& sink = stream_ccm_object_executor_->get_sink (port_name_.c_str());
	sink.consider_transport (the_transport);
}


} // namespace Qedo


#endif

