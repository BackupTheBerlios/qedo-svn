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

#ifndef _QEDO_NO_QOS

#include "ServerInterceptorDispatcher.h"
#include "Util.h"
#include "Output.h"
#include <fstream>
#include "ComponentServerImpl.h"
#include "GlobalHelpers.h"

static char rcsid[] UNUSED = "$Id: ServerInterceptorDispatcher.cpp,v 1.13 2004/01/19 07:34:01 tom Exp $";

namespace Qedo {

ServerInterceptorDispatcher::ServerInterceptorDispatcher()
{

}

ServerInterceptorDispatcher::~ServerInterceptorDispatcher()
{

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
		const Components::ConfigValues* temp_config=0;

	//call for all interceptors

	// determine the id
	// all containers
	Qedo::ContainerList* temp_container_list = component_server_ -> get_all_containers();
	std::list <ContainerInterfaceImpl*>::iterator container_iter;

	//identify the id
	const char* id = 0;

	for (container_iter = temp_container_list->begin(); container_iter != temp_container_list->end(); container_iter++)
	{
		for (unsigned int i = 0; i < (*container_iter) -> installed_homes_.size(); i++)
		{
			for (unsigned int j = 0; j < (((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_.size()); j++)
			{

				// search for the oid
				if (Qedo::compare_OctetSeqs((*info->object_id()),((*container_iter) -> installed_homes_)[i].home_servant_->component_instances_[j].object_id_))
				{
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
		id="__QEDO__NOT_COMPONENT_ID__";
	}
	Qedo::QedoLock l_all(all_server_interceptors_mutex_);

	for (unsigned int i = 0; i < all_server_interceptors_.size(); i++)
	{
		try {
			all_server_interceptors_[i].interceptor->receive_request( info, id );
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
				for_component_id_server_interceptors_[m].interceptor->receive_request( info, id );
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

	Qedo::QedoLock l(all_server_interceptors_mutex_);

	for (unsigned int i = 0; i < all_server_interceptors_.size(); i++)
	{
		try{
            all_server_interceptors_[i].interceptor->send_reply( info ,"NOT_IMPLEMENTED_YET");
		} catch ( ... )
			// catch of user exceptions is probably missing
		{

		}
	}


}

void
ServerInterceptorDispatcher::send_exception(PortableInterceptor::ServerRequestInfo_ptr)
throw(PortableInterceptor::ForwardRequest, CORBA::SystemException)
{

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
ServerInterceptorDispatcher::set_component_server(Qedo::ComponentServerImpl* component_server)
{
	component_server_ = component_server;
};


}  //namespace Qedo

#endif
