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


#include "SinkPort.h"
#include "StreamingValuetypes.h"
#include "Output.h"

#include <cstring>


static char rcsid[] UNUSED = "$Id: SinkPort.cpp,v 1.5 2004/01/20 12:55:45 stoinski Exp $";

namespace Qedo {


SinkPort::SinkPort (const char* name,
					const char* type_id,
					const CORBA::RepositoryIdSeq& streamtypes,
					StreamComponents::SinkStreamPort_ptr the_sink,
					Qedo::StreamDataDispatcher* dispatcher)
: PortBase (name, type_id),
  streamtypes_ (new CORBA::RepositoryIdSeq (streamtypes)),
  the_sink_ (StreamComponents::SinkStreamPort::_duplicate (the_sink)),
  dispatcher_ (dispatcher),
  bound_ (false),
  active_stream_ (false),
  tep_ (0)
{
	dispatcher_->_add_ref();
}


SinkPort::SinkPort()
{
}


SinkPort::SinkPort (const SinkPort& sink_port)
: PortBase (sink_port),
  streamtypes_ (new CORBA::RepositoryIdSeq (sink_port.streamtypes_.in())),
  the_sink_ (StreamComponents::SinkStreamPort::_duplicate (sink_port.the_sink_.in())),
  dispatcher_ (sink_port.dispatcher_),
  active_stream_ (sink_port.active_stream_),
  tep_ (sink_port.tep_)
{
	dispatcher_->_add_ref();

	if (tep_)
		tep_->_add_ref();
}


SinkPort::~SinkPort()
{
	dispatcher_->_remove_ref();

	// TEP remove is done in prepare_remove()
}


StreamComponents::SinkDescription*
SinkPort::sink_description() const
{
	StreamComponents::SinkDescription_var sink_desc = new SinkDescription_impl (port_name_.c_str(), 
																				type_id_.c_str(), 
																				streamtypes_,
																				the_sink_.in());

    return sink_desc._retn();
}


const StreamComponents::SinkStreamPort_ptr 
SinkPort::sink_ref() const
{
    return StreamComponents::SinkStreamPort::_duplicate (the_sink_.in());
}


void 
SinkPort::begin_stream (const char* repos_id, const Components::ConfigValues& meta_data)
throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream)
{
	// First test whether we are already in a current stream context
	if (active_stream_)
		throw StreamComponents::DuplicateStream();

	CORBA::RepositoryIdSeq streamtype;
	streamtype.length (1);
	streamtype[0] = CORBA::string_dup (repos_id);

	this->check_streamtype (streamtype);

	active_stream_ = true;

	// Before calling the executor, propagate the begin_stream() operation to the transport endpoint
	tep_->begin_stream();

	// Now let let the dispatcher call the type-specific operations
	dispatcher_->begin_stream (repos_id, meta_data);
}


void 
SinkPort::end_stream()
throw (StreamComponents::NoStream)
{
	// First test whether we are in a current stream context
	if (! active_stream_)
		throw StreamComponents::NoStream();

	active_stream_ = false;

	// Before calling the executor, propagate the end_stream() operation to the transport endpoint
	tep_->end_stream();

	// Now let let the dispatcher call the type-specific operations
	dispatcher_->end_stream();
}


void
SinkPort::prepare_remove()
{
	QedoLock lock (transport_closure_mutex_);

	if (tep_)
	{
		tep_->close();
		tep_->_remove_ref();
		tep_ = 0;
		bound_ = false;
		active_stream_ = false;
	}
}


void
SinkPort::transport_established()
{
	DEBUG_OUT ("SinkPort: Transport established- now I'm bound");

	bound_ = true;
}


void
SinkPort::transport_closed()
{
	DEBUG_OUT ("SinkPort: Unexpected closure of transport");

	QedoLock lock (transport_closure_mutex_);

	if (tep_)
	{
		tep_->_remove_ref();
		tep_ = 0;
		bound_ = false;
		active_stream_ = false;
	}
}


void 
SinkPort::check_streamtype (const CORBA::RepositoryIdSeq& streamtypes)
throw(StreamComponents::UnsupportedStreamtype,
	  CORBA::SystemException)
{
	// First check for distinguished stream type 'Raw'
#ifdef MICO_ORB
	if (streamtypes_->length() == 1 && ! strcmp (streamtypes_.in()[0], "IDL:StreamComponents/Streamtypes/Raw:1.0"))
#else
	if (streamtypes_->length() == 1 && ! strcmp (streamtypes_[0], "IDL:StreamComponents/Streamtypes/Raw:1.0"))
#endif
	{
		DEBUG_OUT ("SinkPort: check_streamtype(): I'm of Streamtype 'Raw' - everything supported");
		return;
	}

	CORBA::RepositoryIdSeq unknown_streamtypes;

	for (unsigned int i = 0; i < streamtypes.length(); i++)
	{
		bool streamtype_found = false;

		for (unsigned int j = 0; j < streamtypes_->length(); j++)
		{
#ifdef MICO_ORB
			if (! std::strcmp (streamtypes[i], streamtypes_.in()[j]))
#else
			if (! std::strcmp (streamtypes[i], streamtypes_[j]))
#endif
			{
				streamtype_found = true;
				break;
			}
		}

		if (! streamtype_found)
		{
			unknown_streamtypes.length (unknown_streamtypes.length() + 1);
#ifndef MICO_ORB
			unknown_streamtypes[unknown_streamtypes.length() - 1] = CORBA::string_dup (streamtypes[i]);
#else
			unknown_streamtypes[unknown_streamtypes.length() - 1] = CORBA::string_dup (streamtypes[i].in());
#endif
		}

		// Test whether some stream type were not found
		if (unknown_streamtypes.length())
		{
			throw StreamComponents::UnsupportedStreamtype (unknown_streamtypes);
		}
	}
}


void 
SinkPort::consider_transport(StreamComponents::TransportSpec& the_transport)
throw(StreamComponents::AlreadyBound,
	  StreamComponents::TransportFailure,
	  CORBA::SystemException)
{
	DEBUG_OUT ("SinkPort: consider_transport() called");

	if (tep_)
		throw StreamComponents::AlreadyBound();

	// Iterate through our registered transport factories to find an appropriate one
	TransportVector::const_iterator transport_iter;

	for (transport_iter = TransportRegistry::transports_.begin();
		 transport_iter != TransportRegistry::transports_.end();
		 transport_iter++)
	{
		if (! strcmp (the_transport.transport_profile.in(), (*transport_iter).transport_profile_.c_str()))
		{
			break;
		}
	}

	if (transport_iter == TransportRegistry::transports_.end())
	{
		DEBUG_OUT2 ("SinkPort: Transport not supported: ", the_transport.transport_profile);

		throw StreamComponents::TransportFailure();
	}

	// Setup transport endpoint
	tep_ = (*transport_iter).factory_->create_sink_tep (this, dispatcher_);

	try
	{
		tep_->setup_connection (the_transport);
	}
	catch (StreamComponents::TransportFailure&)
	{
		DEBUG_OUT ("SinkPort: consider_transport(): setup_connection() on TransportEndpoint failed");

		tep_->close();
		tep_->_remove_ref();
		tep_ = 0;
	}
}


void 
SinkPort::release_transport()
throw(CORBA::SystemException)
{
	DEBUG_OUT ("SinkPort: release_transport() called");

	tep_->close();
	tep_->_remove_ref();
	tep_ = 0;
}


} // namespace Qedo


#endif

