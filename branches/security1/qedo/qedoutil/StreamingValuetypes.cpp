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


#include "StreamingValuetypes.h"


static char rcsid[] UNUSED = "$Id: StreamingValuetypes.cpp,v 1.2 2003/10/17 09:11:41 stoinski Exp $";


namespace Qedo {


BindingDescription_impl::BindingDescription_impl (Components::Cookie* ck, StreamComponents::SinkStreamPort_ptr the_sink)
#if _MSC_VER < 1300 
: BindingDescription()
#else
: BindingDescription (ck, the_sink)
#endif
{
#if _MSC_VER < 1300
	this -> ck (ck);
	this -> the_sink (the_sink);
#endif
}


BindingDescription_impl::BindingDescription_impl()
{
}


BindingDescription_impl::~BindingDescription_impl
()
{
}


CORBA::ValueBase* 
BindingDescriptionFactory_impl::create_for_unmarshal
()
{	
	return new BindingDescription_impl();
}


SourceDescription_impl::SourceDescription_impl (const char* name, 
												const char* type_id,
												CORBA::Boolean is_multiplex,
												const CORBA::RepositoryIdSeq& stream_types,
												const StreamComponents::BindingDescriptions& bindings)
#ifdef MICO_ORB
: SourceDescription()
#else
: SourceDescription (name, type_id, is_multiplex, stream_types, bindings)
#endif
{
#ifdef MICO_ORB
	this->name (name);
	this->type_id (type_id);
	this->is_multiplex (is_multiplex);
	this->stream_types (stream_types);
	this->bindings (bindings);
#endif
}


SourceDescription_impl::SourceDescription_impl()
{
}


SourceDescription_impl::~SourceDescription_impl()
{
}


CORBA::ValueBase* 
SourceDescriptionFactory_impl::create_for_unmarshal()
{	
	return new SourceDescription_impl();
}


SinkDescription_impl::SinkDescription_impl (const char* name, 
											const char* type_id,
											const CORBA::RepositoryIdSeq& stream_types,
											StreamComponents::SinkStreamPort_ptr the_sink)
#ifdef MICO_ORB
: SinkDescription()
#else
: SinkDescription (name, type_id, stream_types, the_sink)
#endif
{
#ifdef MICO_ORB
	this->name (name);
	this->type_id (type_id);
	this->stream_types (stream_types);
	this->the_sink (the_sink);
#endif
}


SinkDescription_impl::SinkDescription_impl()
{
}


SinkDescription_impl::~SinkDescription_impl()
{
}


CORBA::ValueBase* 
SinkDescriptionFactory_impl::create_for_unmarshal()
{	
	return new SinkDescription_impl();
}

} // namespace Qedo


#endif

