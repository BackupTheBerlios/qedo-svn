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

#ifndef __PRIMARY_STREAMS_SERVANT_H__
#define __PRIMARY_STREAMS_SERVANT_H__

#ifndef _QEDO_NO_STREAMS


#include <CORBA.h>
#include <StreamComponents_skel.h>

#include "ServantBase.h"
#include "Util.h"


namespace Qedo {

class CONTAINERDLL_API PrimaryStreamServant : public virtual POA_StreamComponents::StreamCCMObject,
											  public virtual Qedo::PrimaryServant
{
public:
	PrimaryStreamServant();
	~PrimaryStreamServant();

    //
    // IDL:omg.org/StreamComponents/Streams/provide_sink_stream_port:1.0
    //
    StreamComponents::SinkStreamPort_ptr provide_sink_stream_port(const char* name)
        throw(Components::InvalidName,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/bind:1.0
    //
    Components::Cookie* bind(const char* name,
                             StreamComponents::SinkStreamPort_ptr the_sink,
							 const char* transport_profile)
        throw(Components::InvalidName,
              StreamComponents::AlreadyBound,
              StreamComponents::InvalidBinding,
              StreamComponents::ExceededBindingLimit,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/unbind:1.0
    //
    StreamComponents::SinkStreamPort_ptr unbind(const char* name,
                                                        Components::Cookie* ck)
        throw(Components::CookieRequired,
              StreamComponents::InvalidBinding,
              StreamComponents::NoBinding,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_bindings:1.0
    //
    StreamComponents::BindingDescriptions* get_bindings(const char* name)
        throw(Components::InvalidName,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_named_sinks:1.0
    //
    StreamComponents::SinkDescriptions* get_named_sinks(const Components::NameList& names)
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
    StreamComponents::SourceDescriptions* get_named_sources(const Components::NameList& names)
        throw(Components::InvalidName,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/Streams/get_all_sources:1.0
    //
    StreamComponents::SourceDescriptions* get_all_sources()
        throw(CORBA::SystemException);

#ifndef _QEDO_NO_QOS
	char *
	get_component_id();

#endif
};

} // namespace Qedo

#endif

#endif

