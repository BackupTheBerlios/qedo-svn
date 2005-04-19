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

#ifndef __STREAM_CCM_OBJECT_EXECUTOR_H__
#define __STREAM_CCM_OBJECT_EXECUTOR_H__

#ifndef _QEDO_NO_STREAMS


#include <CORBA.h>
#include <Components_skel.h>

#include "RefCountBase.h"
#include "SourcePort.h"
#include "SinkPort.h"
#include "Util.h"


namespace Qedo {


class CONTAINERDLL_API StreamCCMObjectExecutor : public RefCountBase
{
private:
	SourceVector sources_;
	SinkVector sinks_;

public:
	StreamCCMObjectExecutor();
	~StreamCCMObjectExecutor();

	// Helper functions
	SourcePort& get_source (const char* name);
	SinkPort& get_sink (const char* name);

	//
	// Functions to build up the streaming part of the component instance structure
	//
	// Add a source
	void add_source (const char*, const char*, bool, const CORBA::RepositoryIdSeq&, bool);

	// Add a sink
	void add_sink (const char*, 
				   const char*, 
				   const CORBA::RepositoryIdSeq&, 
				   StreamComponents::SinkStreamPort_ptr,
				   Qedo::StreamDataDispatcher*);

	// Prepare remove (this function is needed to break cyclic reference counting dependencies when removing a component)
	void prepare_remove();

	// Begin a stream (caused by a call on the context)
	void begin_stream_source (const char*, const char*, const ::Components::ConfigValues&)
		throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream);

	// End a stream (caused by a call on the context)
	void end_stream_source (const char*)
		throw (StreamComponents::NoStream);

	// Begin a stream (caused by a call on the sink)
	void begin_stream_sink (const char*, const char*, const ::Components::ConfigValues&)
		throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream);

	// End a stream (caused by a call on the sink)
	void end_stream_sink (const char*)
		throw (StreamComponents::NoStream);

	// A stream transmission has failed before it has ended
	void failed_stream();

	// Send data for a stream
	void send_buffer (const char*, StreamComponents::StreamingBuffer_ptr)
		throw (StreamComponents::NoStream);

    //
    // IDL:omg.org/StreamComponents/Streams/provide_sink_stream_port:1.0
    //
    StreamComponents::SinkStreamPort_ptr provide_sink_stream_port(const char*)
        throw(Components::InvalidName,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/bind:1.0
    //
    Components::Cookie* bind(const char*, StreamComponents::SinkStreamPort_ptr, const char*)
        throw(Components::InvalidName,
              StreamComponents::AlreadyBound,
              StreamComponents::InvalidBinding,
              StreamComponents::ExceededBindingLimit,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/unbind:1.0
    //
    StreamComponents::SinkStreamPort_ptr unbind(const char*, Components::Cookie*)
        throw(Components::CookieRequired,
              StreamComponents::InvalidBinding,
              StreamComponents::NoBinding,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_bindings:1.0
    //
    StreamComponents::BindingDescriptions* get_bindings(const char*)
        throw(Components::InvalidName,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_named_sinks:1.0
    //
    StreamComponents::SinkDescriptions* get_named_sinks(const Components::NameList&)
        throw(Components::InvalidName,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_all_sinks:1.0
    //
    StreamComponents::SinkDescriptions* get_all_sinks()
        throw(CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_named_sources:1.0
    //
    StreamComponents::SourceDescriptions* get_named_sources(const Components::NameList&)
        throw(Components::InvalidName,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_all_sources:1.0
    //
    StreamComponents::SourceDescriptions* get_all_sources()
        throw(CORBA::SystemException);
};


} // namespace Qedo


#endif

#endif
