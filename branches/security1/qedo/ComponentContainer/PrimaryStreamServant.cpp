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


#include "PrimaryStreamServant.h"
#include "Output.h"

#pragma warning (disable : 4715) // not all control paths return a value

static char rcsid[] UNUSED = "$Id: PrimaryStreamServant.cpp,v 1.2 2003/10/17 09:11:40 stoinski Exp $";


namespace Qedo {


PrimaryStreamServant::PrimaryStreamServant()
{
}


PrimaryStreamServant::~PrimaryStreamServant()
{
	DEBUG_OUT ("PrimaryStreamServant: Destructor called");
}


StreamComponents::SinkStreamPort_ptr 
PrimaryStreamServant::provide_sink_stream_port(const char* name)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	return stream_ccm_object_executor_->provide_sink_stream_port (name);
}


Components::Cookie* 
PrimaryStreamServant::bind(const char* name,
                           StreamComponents::SinkStreamPort_ptr the_sink)
throw(Components::InvalidName,
      StreamComponents::AlreadyBound,
      StreamComponents::InvalidBinding,
      StreamComponents::ExceededBindingLimit,
      CORBA::SystemException)
{
	return stream_ccm_object_executor_->bind (name, the_sink);
}


StreamComponents::SinkStreamPort_ptr 
PrimaryStreamServant::unbind(const char* name,
                             Components::Cookie* ck)
throw(Components::CookieRequired,
      StreamComponents::InvalidBinding,
      StreamComponents::NoBinding,
      CORBA::SystemException)
{
	return stream_ccm_object_executor_->unbind (name, ck);
}


StreamComponents::BindingDescriptions* 
PrimaryStreamServant::get_bindings(const char* name)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	return stream_ccm_object_executor_->get_bindings (name);
}


StreamComponents::SinkDescriptions* 
PrimaryStreamServant::get_named_sinks(const Components::NameList& names)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	return stream_ccm_object_executor_->get_named_sinks (names);
}


StreamComponents::SinkDescriptions* 
PrimaryStreamServant::get_all_sinks()
throw(CORBA::SystemException)
{
	return stream_ccm_object_executor_->get_all_sinks();
}


StreamComponents::SourceDescriptions* 
PrimaryStreamServant::get_named_sources(const Components::NameList& names)
throw(Components::InvalidName,
      CORBA::SystemException)
{
	return stream_ccm_object_executor_->get_named_sources (names);
}


StreamComponents::SourceDescriptions* 
PrimaryStreamServant::get_all_sources()
throw(CORBA::SystemException)
{
	return stream_ccm_object_executor_->get_all_sources();
}


} // namespace Qedo


#endif

