/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002-2003 by the Qedo Team                                */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _QEDO_NO_QOS

#include "ServerInterceptorDispatcher.h"
#include "Util.h"
#include "Output.h"
#include <fstream>
#include "ComponentServerImpl.h"
#include "GlobalHelpers.h"
#include "ContainerServerRequestInfo.h"

static char rcsid[] UNUSED = "$Id: ServerInterceptorDispatcher.cpp,v 1.19 2004/08/27 08:37:43 tom Exp $";

namespace Qedo {

ServerInterceptorDispatcher::ServerInterceptorDispatcher()
{

}

ServerInterceptorDispatcher::~ServerInterceptorDispatcher()
{

}

void
ServerInterceptorDispatcher::init_cdr ()
{
	CORBA::Object_var obj = component_server_ -> orb_ ->resolve_initial_references ("CodecFactory");

	IOP::CodecFactory_var factory = IOP::CodecFactory::_narrow(obj);

    if ( CORBA::is_nil(factory) )
	{
		std::cout << "no CDR" << std::endl;
    	return;
	}

    /* 
	 * Create codec
	 */

    IOP::Encoding how;

    how.major_version = 1;
    how.minor_version = 0;
    how.format		  =	IOP::ENCODING_CDR_ENCAPS;

    try
    {
		m_cdrCodec = factory->create_codec(how);
    }
    catch(const IOP::CodecFactory::UnknownEncoding& _ex)
    {
		std::cout << "no CDR" << std::endl;
    }

}

char*
ServerInterceptorDispatcher::name ()
{
	return CORBA::string_dup("ServerIntereptorDispatcher");

}

void
ServerInterceptorDispatcher::destroy()
{

}

void
ServerInterceptorDispatcher::receive_request_service_contexts(PortableInterceptor::ServerRequestInfo_ptr)
throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{

}

void
ServerInterceptorDispatcher::receive_request(PortableInterceptor::ServerRequestInfo_ptr info)
throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{

	DEBUG_OUT ("ServerInterceptorDispatcher: receive_request");

	// call for regsitered COPI
		Components::ConfigValues* temp_config=0;

	//call for all interceptors

	// determine the id
	// all containers
	Qedo::ContainerList* temp_container_list = component_server_ -> get_all_containers();
	std::list <ContainerInterfaceImpl*>::iterator container_iter;

	//identify the component id
	const char* id = 0;
	// identify th component_UUID
	const char* uuid = 0;
	// identify port_id
	const char* port_id = 0;

	for (container_iter = temp_container_list->begin(); container_iter != temp_container_list->end(); container_iter++)
	{
		for (unsigned int i = 0; i < (*container_iter) -> installed_homes_.size(); i++)
		{
			for (unsigned int j = 0; j < (((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_.size()); j++)
			{

				// search for the oid
				if (Qedo::compare_OctetSeqs((*info->object_id()),((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_[j].object_id_))
				{
					port_id = "component";
					temp_config = ((*container_iter)->installed_homes_)[i].home_servant_->component_instances_[j].config_;

					if (temp_config != 0)
					{
//						std::cout << temp_config->length() << std::endl;

						Components::ConfigValue* value;
						for (CORBA::ULong k = 0; k < temp_config->length(); k++)
						{
							value = (*temp_config)[k];

							if (! strcmp ((*temp_config)[k]->name(), "id"))
							{
								(*temp_config)[k]->value() >>= id;
								break;
							}
						}
					}

				}
				// current call could be the call on a facet
				// search for facets
				for (unsigned int k = 0; k < ((*container_iter)->installed_homes_)[i].home_servant_->component_instances_[j].ccm_object_executor_->facets_.size(); k++)
				{
					if (Qedo::compare_OctetSeqs((*info->object_id()),*((*container_iter) -> installed_homes_)[i].home_servant_->reference_to_oid(((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_[j].ccm_object_executor_->facets_[k].facet_ref())))
					{
						port_id = strdup(((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_[j].ccm_object_executor_->facets_[k].port_name().c_str());

						temp_config = ((*container_iter)->installed_homes_)[i].home_servant_->component_instances_[j].config_;

						if (temp_config != 0)
						{
//							std::cout << temp_config->length() << std::endl;

							Components::ConfigValue* value;
							for (CORBA::ULong k = 0; k < temp_config->length(); k++)
							{
								value = (*temp_config)[k];

								if (! strcmp ((*temp_config)[k]->name(), "id"))
								{
									(*temp_config)[k]->value() >>= id;
									break;
								}
							}
						}

					}

				}
				// current call could be the call on a consumer
				// search for consumer
				for (unsigned int k = 0; k < ((*container_iter)->installed_homes_)[i].home_servant_->component_instances_[j].ccm_object_executor_->consumers_.size(); k++)
				{
					if (Qedo::compare_OctetSeqs((*info->object_id()),*((*container_iter) -> installed_homes_)[i].home_servant_->reference_to_oid(((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_[j].ccm_object_executor_->consumers_[k].consumer())))
					{
						port_id = strdup(((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_[j].ccm_object_executor_->consumers_[k].port_name().c_str());

						temp_config = ((*container_iter)->installed_homes_)[i].home_servant_->component_instances_[j].config_;

						if (temp_config != 0)
						{
//							std::cout << temp_config->length() << std::endl;

							Components::ConfigValue* value;
							for (CORBA::ULong k = 0; k < temp_config->length(); k++)
							{
								value = (*temp_config)[k];

								if (! strcmp ((*temp_config)[k]->name(), "id"))
								{
									(*temp_config)[k]->value() >>= id;
									break;
								}
							}
						}

					}

				}
			}
		}
	}


	// call the COPIs
	if (!id)
	{
		id="__QEDO__NOT_COMPONENT_ID__!!";
	}
	if (!port_id)
	{
		port_id="QEOD_UNKNOWN_PORT_ID";
	}

	// extract origin_id from service context
	IOP::ServiceContext_var sc = 0;
	CORBA::Any_var context_any = new CORBA::Any();
	CORBA::Any slot ;
	Components::Extension::SlotInfo slot_info;
	try {
		sc = info -> get_request_service_context(100);	
		
		CORBA::OctetSeq data;

		data.length(sc->context_data.length());
		memcpy(data.get_buffer(), sc->context_data.get_buffer(), sc->context_data.length());
		context_any = m_cdrCodec -> decode_value(data, CORBA::_tc_string);

		const char* temp_id;
		context_any >>= temp_id;
		slot_info.origin_id = CORBA::string_dup(temp_id);
		
	} catch (CORBA::BAD_PARAM&)
	{
		//no service context for tracing
		slot_info.origin_id = CORBA::string_dup("NO_ORIGIN");
	} catch (...)
	{
		//return;
	}
	// set identity in the slot

	CORBA::Object_var obj = component_server_ -> orb_ -> resolve_initial_references ("PICurrent");

	if ( CORBA::is_nil (obj) )
		return;

	PortableInterceptor::Current_var piCurrent = PortableInterceptor::Current::_narrow (obj);

	slot_info.target_id = CORBA::string_dup(id);
	slot <<= slot_info;
	piCurrent -> set_slot(component_server_ -> slot_id_, slot);

	Qedo::QedoLock l_all(all_server_interceptors_mutex_);

	Components::Extension::ContainerServerRequestInfo_var container_info = new Qedo::ContainerServerRequestInfo(info,slot_info.target_id,slot_info.target_id,port_id);
	for (unsigned int i = 0; i < all_server_interceptors_.size(); i++)
	{
		try {

			all_server_interceptors_[i].interceptor->receive_request( container_info.in() );
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}

	// call COPIS registered for id

	Qedo::QedoLock l_component(for_component_id_server_interceptors_mutex_);

	for (unsigned int m = 0; m < for_component_id_server_interceptors_.size(); m++)
	{
		if (!strcmp(id, for_component_id_server_interceptors_[m].id.c_str()))
		{
			try{
				for_component_id_server_interceptors_[m].interceptor->receive_request( container_info.in() );
			} catch (CORBA::SystemException e)
			{
				throw e;
			} catch ( ... )
				//catch of user exceptions is probably missing
			{

			}
		}
	}


}


void
ServerInterceptorDispatcher::send_reply(PortableInterceptor::ServerRequestInfo_ptr info)
throw(CORBA::SystemException)
{
	DEBUG_OUT ("ServerInterceptorDispatcher: send_reply");
	int dummy = 0;
	CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);

	CORBA::Object_var obj = orb->resolve_initial_references ("PICurrent");

	if ( CORBA::is_nil (obj) )
		return;

	PortableInterceptor::Current_var piCurrent = PortableInterceptor::Current::_narrow (obj);

	CORBA::Any_var slot = piCurrent->get_slot (component_server_ -> slot_id_);
	Components::Extension::SlotInfo slot_info;
	slot >>= slot_info;
//	if (!slot_info.target_id)
//	{
//		id = "UNKNOWN_COMP_ID";
//	}

	Qedo::QedoLock l(all_server_interceptors_mutex_);
	Components::Extension::ContainerServerRequestInfo_var container_info = new Qedo::ContainerServerRequestInfo(info,slot_info.target_id,slot_info.target_id,slot_info.target_id);

	for (unsigned int i = 0; i < all_server_interceptors_.size(); i++)
	{
		try{
            all_server_interceptors_[i].interceptor->send_reply( container_info.in() );
		} catch ( ... )
			// catch of user exceptions is probably missing
		{

		}
	}


}

void
ServerInterceptorDispatcher::send_exception(PortableInterceptor::ServerRequestInfo_ptr info)
throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{
	DEBUG_OUT ("ServerInterceptorDispatcher: send_exception");

	CORBA::Object_var obj = component_server_ -> orb_ -> resolve_initial_references ("PICurrent");

	if ( CORBA::is_nil (obj) )
		return;

	PortableInterceptor::Current_var piCurrent = PortableInterceptor::Current::_narrow (obj);

	CORBA::Any_var slot = piCurrent->get_slot (component_server_ -> slot_id_);
	Components::Extension::SlotInfo slot_info;
	slot >>= slot_info;
//	if (!slot_info.target_id)
//	{
//		id = "UNKNOWN_COMP_ID";
//	}

	Qedo::QedoLock l(all_server_interceptors_mutex_);
	Components::Extension::ContainerServerRequestInfo_var container_info = new Qedo::ContainerServerRequestInfo(info,slot_info.target_id,slot_info.target_id,slot_info.target_id);

	for (unsigned int i = 0; i < all_server_interceptors_.size(); i++)
	{
		try{
            all_server_interceptors_[i].interceptor->send_user_exception( container_info.in() );
		} catch ( ... )
			// catch of user exceptions is probably missing
		{

		}
	}


}

void
ServerInterceptorDispatcher::send_other(PortableInterceptor::ServerRequestInfo_ptr)
throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{

}

void
ServerInterceptorDispatcher::register_interceptor_for_all(Components::Extension::ServerContainerInterceptor_ptr interceptor)
{
	DEBUG_OUT("ServerInterceptorDispatcher: Server COPI registered for all components");

	ServerInterceptorEntry e;
	e.interceptor = Components::Extension::ServerContainerInterceptor::_duplicate( interceptor );

	Qedo::QedoLock l(all_server_interceptors_mutex_);

	all_server_interceptors_.push_back(e);

}

void
ServerInterceptorDispatcher::register_interceptor_for_component(Components::Extension::ServerContainerInterceptor_ptr interceptor, const char* id)
{
	DEBUG_OUT("ServerInterceptorDispatcher: Server COPI registered for component ");

	ServerInterceptorEntry e;
	e.interceptor = Components::Extension::ServerContainerInterceptor::_duplicate( interceptor );
	e.id = id;

	Qedo::QedoLock l(for_component_id_server_interceptors_mutex_);

	for_component_id_server_interceptors_.push_back(e);

}

void
ServerInterceptorDispatcher::unregister_interceptor_for_all(Components::Extension::ServerContainerInterceptor_ptr interceptor)
{
	DEBUG_OUT("ServerInterceptorDispatcher: Server COPI unregister_for_all called");

	std::vector <ServerInterceptorEntry>::iterator interceptor_iter;

	for (interceptor_iter = all_server_interceptors_.begin(); interceptor_iter != all_server_interceptors_.end(); interceptor_iter++)
	{

		if ((*interceptor_iter).interceptor == interceptor)
		{
			DEBUG_OUT ("ServerInterceptorDispatcher: unregister_interceptor_for_all(): interceptor found");
			all_server_interceptors_.erase (interceptor_iter);

			break;
		}
	}

	if (interceptor_iter == all_server_interceptors_.end())
	{
		DEBUG_OUT ("ServerinterceptorDispatcher: Unknown interceptor");
	}

}

void
ServerInterceptorDispatcher::unregister_interceptor_for_component(Components::Extension::ServerContainerInterceptor_ptr interceptor, const char* id)
{
	DEBUG_OUT("ServerInterceptorDispatcher: Server COPI unregister_for_component called");

	std::vector <ServerInterceptorEntry>::iterator interceptor_iter;

	for (interceptor_iter = all_server_interceptors_.begin(); interceptor_iter != all_server_interceptors_.end(); interceptor_iter++)
	{

		if (!strcmp((*interceptor_iter).id.c_str() ,id))
		{
			DEBUG_OUT ("ServerInterceptorDispatcher: unregister_interceptor_for_all(): interceptor found");
			all_server_interceptors_.erase (interceptor_iter);

			break;
		}
	}

	if (interceptor_iter == all_server_interceptors_.end())
	{
		DEBUG_OUT ("ServerinterceptorDispatcher: Unknown interceptor");
	}

}

void
ServerInterceptorDispatcher::set_component_server(Qedo::ComponentServerImpl* component_server)
{
	component_server_ = component_server;
};


}  //namespace Qedo

#endif
