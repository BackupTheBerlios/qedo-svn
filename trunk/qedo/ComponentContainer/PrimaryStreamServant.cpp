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


#include "PrimaryStreamServant.h"
#include "Output.h"

#ifndef _QEDO_NO_QOS
#include "GlobalHelpers.h"
#endif

#ifdef _WIN32
#pragma warning (disable : 4715) // not all control paths return a value
#endif

static char rcsid[] UNUSED = "$Id: PrimaryStreamServant.cpp,v 1.6 2004/07/16 11:21:23 tom Exp $";


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

#ifndef _QEDO_NO_QOS
	char * act_id = this-> get_component_id();
	CORBA::Boolean con;
	CORBA::Object_var anObject = servant_interceptor_registry_ -> provide_sink_stream_port (act_id, name, con);
	if (con) {
#endif

		return stream_ccm_object_executor_->provide_sink_stream_port (name);
#ifndef _QEDO_NO_QOS
	}
	return StreamComponents::SinkStreamPort::_narrow(anObject);
#endif
}


Components::Cookie* 
PrimaryStreamServant::bind(const char* name,
                           StreamComponents::SinkStreamPort_ptr the_sink,
						   const char* transport_profile)
throw(Components::InvalidName,
      StreamComponents::AlreadyBound,
      StreamComponents::InvalidBinding,
      StreamComponents::ExceededBindingLimit,
      CORBA::SystemException)
{
	// identify_component_id



#ifndef _QEDO_NO_QOS
	char * act_id = this-> get_component_id();
	CORBA::Boolean con;
	Components::Cookie* temp_ck = servant_interceptor_registry_ -> bind (act_id, name, the_sink, transport_profile, con);
	if (con)
	{
#endif

	return stream_ccm_object_executor_->bind (name, the_sink, transport_profile);
#ifndef _QEDO_NO_QOS
	}
	return temp_ck;
#endif 
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

#ifndef _QEDO_NO_QOS
char *
PrimaryStreamServant::get_component_id(){
	char* comp_id = 0;
	unsigned int i;
	for (i=0; i < ccm_object_executor_ -> home_servant_ -> component_instances_.size(); i++)
	{
		if (Qedo::compare_OctetSeqs(this -> ccm_object_executor_ -> component_object_id_,
			(this -> ccm_object_executor_ -> home_servant_ -> component_instances_[i].object_id_)))
		{
			Components::ConfigValues* temp_config=0;
			temp_config = this -> ccm_object_executor_ -> home_servant_ -> component_instances_[i].config_;

			if (temp_config != 0)
			{

				Components::ConfigValue* value;
				for (CORBA::ULong k = 0; k < temp_config->length(); k++)
				{
					value = (*temp_config)[k];

					if (! strcmp ((*temp_config)[k]->name(), "id"))
					{
						(*temp_config)[k]->value() >>= comp_id;
						break;
					}
				}
			}
		}
	}
	if (!comp_id)
	{
		comp_id="__QEDO__NOT_COMPONENT_ID__";
	}
	return comp_id;	
}

#endif

} // namespace Qedo


#endif

