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

#include "StreamCCMObjectExecutor.h"
#include "Output.h"


static char rcsid[] UNUSED = "$Id: StreamCCMObjectExecutor.cpp,v 1.5 2004/06/24 14:36:08 tom Exp $";

namespace Qedo {


StreamCCMObjectExecutor::StreamCCMObjectExecutor()
{
}


StreamCCMObjectExecutor::~StreamCCMObjectExecutor()
{
	DEBUG_OUT ("StreamCCMObjectExecutor: Destructor called");
}


SourcePort& 
StreamCCMObjectExecutor::get_source (const char* name)
{
	for (unsigned int i = 0; i < sources_.size(); i++)
	{	
		if (sources_[i]->port_name() == name)
		{
			return *(sources_[i]);
		}
	}

	NORMAL_ERR2 ("StreamCCMObjectExecutor: Fatal internal error: SourcePort for get_source not found for name ", name);
	abort();
}


SinkPort& 
StreamCCMObjectExecutor::get_sink (const char* name)
{
	for (unsigned int i = 0; i < sinks_.size(); i++)
	{	
		if (sinks_[i]->port_name() == name)
		{
			return *(sinks_[i]);
		}
	}

	NORMAL_ERR2 ("StreamCCMObjectExecutor: Fatal internal error: SinkPort for get_sink not found for name ", name);
	abort();
}


void 
StreamCCMObjectExecutor::add_source (const char* name, 
									 const char* type_id, 
									 bool is_multiplex, 
									 const CORBA::RepositoryIdSeq& streamtypes,
									 bool configured_for_async_call)
{
	SourcePort* new_source_port = new SourcePort(name, type_id, is_multiplex, streamtypes, configured_for_async_call);
	SourcePort_smartptr source_smartptr (new_source_port);
	new_source_port->_remove_ref();

	sources_.push_back (source_smartptr);

	DEBUG_OUT2 ("StreamCCMObjectExecutor: New source registered: ", name);
}


void 
StreamCCMObjectExecutor::add_sink (const char* name, 
								   const char* type_id, 
								   const CORBA::RepositoryIdSeq& streamtypes, 
								   StreamComponents::SinkStreamPort_ptr the_sink,
								   Qedo::StreamDataDispatcher* dispatcher)
{
	SinkPort* new_sink_port = new SinkPort (name, type_id, streamtypes, the_sink, dispatcher);
	SinkPort_smartptr sink_smartptr (new_sink_port);
	new_sink_port->_remove_ref();

	sinks_.push_back (sink_smartptr);

	DEBUG_OUT2 ("StreamCCMObjectExecutor: New sink registered: ", name);
}


void
StreamCCMObjectExecutor::prepare_remove()
{
	// Since a SinkPort holds a reference to a TransportEndpoint and vice versa,
	// we have to split this circular dependency here explicitly
	SinkVector::iterator sink_iter;

	for (sink_iter = sinks_.begin(); sink_iter != sinks_.end(); sink_iter++)
	{
		(*sink_iter)->prepare_remove();
	}

	// Although there is no cyclic reference in the SourcePort structures, we
	// use the same mechanism here (easier to understand)
	SourceVector::iterator source_iter;

	for (source_iter = sources_.begin(); source_iter != sources_.end(); source_iter++)
	{
		(*source_iter)->prepare_remove();
	}

	sinks_.clear();
	sources_.clear();
}


void 
StreamCCMObjectExecutor::begin_stream_source (const char* port_name, const char* repos_id, const ::Components::ConfigValues& meta_data)
throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream)
{
	// First find the source port
	SourceVector::iterator src_iter;

	for (src_iter = sources_.begin(); src_iter != sources_.end(); src_iter++)
	{
		if ((*src_iter)->port_name() == port_name)
			break;
	}

	if (src_iter == sources_.end())
	{
		DEBUG_OUT2 ("StreamCCMObjectExecutor: begin_stream_source(): Fatal internal error: No source port registered with name ", port_name);
		assert (0);
	}

	(*src_iter)->begin_stream (repos_id, meta_data);
}


void 
StreamCCMObjectExecutor::end_stream_source (const char* port_name)
throw (StreamComponents::NoStream)
{
	// First find the source port
	SourceVector::iterator src_iter;

	for (src_iter = sources_.begin(); src_iter != sources_.end(); src_iter++)
	{
		if ((*src_iter)->port_name() == port_name)
			break;
	}

	if (src_iter == sources_.end())
	{
		DEBUG_OUT2 ("StreamCCMObjectExecutor: end_stream_source(): Fatal internal error: No source port registered with name ", port_name);
		assert (0);
	}

	(*src_iter)->end_stream();
}


void 
StreamCCMObjectExecutor::begin_stream_sink (const char* port_name, const char* repos_id, const ::Components::ConfigValues& meta_data)
throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream)
{
	// First find the sink port
	SinkVector::iterator snk_iter;

	for (snk_iter = sinks_.begin(); snk_iter != sinks_.end(); snk_iter++)
	{
		if ((*snk_iter)->port_name() == port_name)
			break;
	}

	if (snk_iter == sinks_.end())
	{
		DEBUG_OUT2 ("StreamCCMObjectExecutor: begin_stream_sink(): Fatal internal error: No sink port registered with name ", port_name);
		assert (0);
	}

	(*snk_iter)->begin_stream (repos_id, meta_data);
}


void 
StreamCCMObjectExecutor::end_stream_sink (const char* port_name)
throw (StreamComponents::NoStream)
{
	// First find the sink port
	SinkVector::iterator snk_iter;

	for (snk_iter = sinks_.begin(); snk_iter != sinks_.end(); snk_iter++)
	{
		if ((*snk_iter)->port_name() == port_name)
			break;
	}

	if (snk_iter == sinks_.end())
	{
		DEBUG_OUT2 ("StreamCCMObjectExecutor: end_stream_sink(): Fatal internal error: No sink port registered with name ", port_name);
		assert (0);
	}

	(*snk_iter)->end_stream();
}


void 
StreamCCMObjectExecutor::send_buffer (const char* port_name, StreamComponents::StreamingBuffer_ptr buffer)
throw (StreamComponents::NoStream)
{
	// First find the source port
	SourceVector::iterator src_iter;

	for (src_iter = sources_.begin(); src_iter != sources_.end(); src_iter++)
	{
		if ((*src_iter)->port_name() == port_name)
			break;
	}

	if (src_iter == sources_.end())
	{
		DEBUG_OUT2 ("StreamCCMObjectExecutor: send_buffer(): Fatal internal error: No source port registered with name ", port_name);
		assert (0);
	}

	(*src_iter)->send_buffer (buffer);
}


StreamComponents::SinkStreamPort_ptr 
StreamCCMObjectExecutor::provide_sink_stream_port (const char* name)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	DEBUG_OUT ("StreamCCMObjectExecutor: provide_sink_stream_port() called");

	SinkVector::const_iterator sink_iter;

	for (sink_iter = sinks_.begin(); sink_iter != sinks_.end(); sink_iter++)
	{
		if ((*sink_iter)->port_name() == name)
		{
			return (*sink_iter)->sink_ref();
		}
	}

	DEBUG_OUT2 ( "StreamCCMObjectExecutor: No sink registered with name ", name );

    throw Components::InvalidName();
}


Components::Cookie* 
StreamCCMObjectExecutor::bind(const char* name,
							  StreamComponents::SinkStreamPort_ptr the_sink,
							  const char* transport_profile)
throw(Components::InvalidName,
      StreamComponents::AlreadyBound,
      StreamComponents::InvalidBinding,
      StreamComponents::ExceededBindingLimit,
      CORBA::SystemException)
{
	DEBUG_OUT ("StreamCCMObjectExecutor: bind() called");

	SourceVector::iterator src_iter;

	for (src_iter = sources_.begin(); 
         src_iter != sources_.end(); 
         src_iter++)
	{
		if ((*src_iter)->port_name() == name)
		{
			return (*src_iter)->add_binding (the_sink, transport_profile);
		}
	}

	DEBUG_OUT2 ( "StreamCCMObjectExecutor: No source registered with name ", name );

	throw Components::InvalidName();
}


StreamComponents::SinkStreamPort_ptr 
StreamCCMObjectExecutor::unbind(const char* name,
                                Components::Cookie* ck)
throw(Components::CookieRequired,
      StreamComponents::InvalidBinding,
      StreamComponents::NoBinding,
      CORBA::SystemException)
{
	SourceVector::iterator src_iter;

	for (src_iter = sources_.begin(); 
         src_iter != sources_.end(); 
         src_iter++ )
	{
		if ((*src_iter)->port_name() == name)
		{
            return (*src_iter)->remove_binding (ck);
        }
	}

	throw Components::InvalidName();
}


StreamComponents::BindingDescriptions* 
StreamCCMObjectExecutor::get_bindings(const char* name)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	DEBUG_OUT2 ("StreamCCMObjectExecutor: get_bindings() called for ", name);

	SourceVector::const_iterator src_iter;
	
	for (src_iter = sources_.begin(); src_iter != sources_.end(); src_iter++)
	{
		if ((*src_iter)->port_name() == name)
			break;
	}

	if (src_iter == sources_.end())
	{
		throw Components::InvalidName();
	}

	StreamComponents::BindingDescriptions_var binding_descs = (*src_iter)->binding_descriptions();

	return binding_descs._retn();
}


StreamComponents::SinkDescriptions* 
StreamCCMObjectExecutor::get_named_sinks(const Components::NameList& names)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	DEBUG_OUT ("StreamCCMObjectExecutor: get_named_sinks() called");

	StreamComponents::SinkDescriptions_var sinks = 
        new StreamComponents::SinkDescriptions();

	for (unsigned int i = 0; i < names.length(); i++)
	{
		for (unsigned int j = 0; j < sinks_.size(); j++)
		{
#ifdef MICO_ORB
			if (sinks_[j]->port_name() == names[i].in())
#else
			if (sinks_[j]->port_name() == names[i])
#endif
			{
                sinks->length (sinks->length() + 1);

				sinks[sinks->length() - 1] = 
                    sinks_[j]->sink_description();

				break;
			}
		}

		if (sinks->length() == 0)
			throw Components::InvalidName();
	}

	return sinks._retn();
}


StreamComponents::SinkDescriptions* 
StreamCCMObjectExecutor::get_all_sinks()
throw(CORBA::SystemException)
{
	DEBUG_OUT ("StreamCCMObjectExecutor: get_all_sinks() called");

	StreamComponents::SinkDescriptions_var sinks = 
        new StreamComponents::SinkDescriptions();
	sinks->length (sinks_.size());

	StreamComponents::SinkDescriptions_var sink_descs;

	for (unsigned int i = 0; i < sinks_.size(); i++)
	{
#ifdef MICO_ORB
		sinks.inout()[i] = sinks_[i]->sink_description();
#else
		sinks[i] = sinks_[i]->sink_description();
#endif
	}

	return sinks._retn();
}


StreamComponents::SourceDescriptions* 
StreamCCMObjectExecutor::get_named_sources(const Components::NameList& names)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	DEBUG_OUT ("StreamCCMObjectExecutor: get_named_sources() called");

	StreamComponents::SourceDescriptions_var sources = 
        new StreamComponents::SourceDescriptions();

	for (unsigned int i = 0; i < names.length(); i++)
	{
		for (unsigned int j = 0; j < sources_.size(); j++)
		{
#ifdef MICO_ORB
			if (sources_[j]->port_name() == names[i].in())
#else
			if (sources_[j]->port_name() == names[i])
#endif
			{
                sources->length (sources->length() + 1);

				sources[sources->length() - 1] = 
                    sources_[j]->source_description();

				break;
			}
		}

		if (sources->length() == 0)
			throw Components::InvalidName();
	}

	return sources._retn();
}



StreamComponents::SourceDescriptions* 
StreamCCMObjectExecutor::get_all_sources()
throw(CORBA::SystemException)
{
	DEBUG_OUT ("StreamCCMObjectExecutor: get_all_sources() called");

	StreamComponents::SourceDescriptions_var sources = 
        new StreamComponents::SourceDescriptions();
	sources->length (sources_.size());

	for (unsigned int i = 0; i < sources_.size(); i++)
	{
#ifdef MICO_ORB
		sources.inout()[i] = sources_[i]->source_description();
#else
		sources[i] = sources_[i]->source_description();
#endif
	}

	return sources._retn();
}


} // namespace Qedo

#endif

