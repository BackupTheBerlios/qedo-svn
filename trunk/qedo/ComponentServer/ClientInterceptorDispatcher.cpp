/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
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


#include "ClientInterceptorDispatcher.h"
#include "Util.h"
#include <fstream>
#include "ContainerClientRequestInfo.h"

static char rcsid[] UNUSED = "$Id: ClientInterceptorDispatcher.cpp,v 1.10 2004/02/16 14:26:54 tom Exp $";

namespace Qedo {

ClientInterceptorDispatcher::ClientInterceptorDispatcher() {

}

ClientInterceptorDispatcher::~ClientInterceptorDispatcher() {

}

char*
ClientInterceptorDispatcher::name ()
{
	return CORBA::string_dup("ClientIntereptorDispatcher");
}

void
ClientInterceptorDispatcher::destroy()
{
}

void
ClientInterceptorDispatcher::send_request( PortableInterceptor::ClientRequestInfo_ptr info )
{
	DEBUG_OUT ("ClientInterceptorDispatcher: send_request");

	CORBA::Any_var slot = info->get_slot(component_server_ -> slot_id_);
	const char* id = 0;
	slot >>= id;
	if (!id)
	{
		id = "UNKNOWN_COMP_ID";
	}

//	all_client_interceptors_mutex_.read_lock_object();
	Qedo::ContainerClientRequestInfo *container_info= new Qedo::ContainerClientRequestInfo(info,id,id,id);

	for (unsigned int i = 0; i < all_client_interceptors_.size(); i++)
	{
		try {
			all_client_interceptors_[i].interceptor->send_request( container_info );
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
//	all_client_interceptors_mutex_.unlock_object();

}

void
ClientInterceptorDispatcher::send_poll( PortableInterceptor::ClientRequestInfo_ptr info )
{

}

void
ClientInterceptorDispatcher::receive_reply( PortableInterceptor::ClientRequestInfo_ptr info )
{
	DEBUG_OUT ("ClientInterceptorDispatcher: send_request");

	CORBA::Any_var slot = info->get_slot(component_server_ -> slot_id_);
	const char* id = 0;
	slot >>= id;
	if (!id)
	{
		id = "UNKNOWN_COMP_ID";
	}

//	all_client_interceptors_mutex_.read_lock_object();
	Qedo::ContainerClientRequestInfo *container_info= new Qedo::ContainerClientRequestInfo(info,id,id,id);

	for (unsigned int i = 0; i < all_client_interceptors_.size(); i++)
	{
		try {
			all_client_interceptors_[i].interceptor->receive_reply( container_info );
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
//	all_client_interceptors_mutex_.unlock_object();

}

void
ClientInterceptorDispatcher::receive_exception( PortableInterceptor::ClientRequestInfo_ptr info )
{
	DEBUG_OUT ("ClientInterceptorDispatcher: receive_exception");

	CORBA::Any_var slot = info->get_slot(component_server_ -> slot_id_);
	const char* id = 0;
	slot >>= id;
	if (!id)
	{
		id = "UNKNOWN_COMP_ID";
	}

//	all_client_interceptors_mutex_.read_lock_object();
	Qedo::ContainerClientRequestInfo *container_info= new Qedo::ContainerClientRequestInfo(info,id,id,id);

	for (unsigned int i = 0; i < all_client_interceptors_.size(); i++)
	{
		try {
			all_client_interceptors_[i].interceptor->receive_user_exception( container_info );
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
//	all_client_interceptors_mutex_.unlock_object();

}

void
ClientInterceptorDispatcher::receive_other( PortableInterceptor::ClientRequestInfo_ptr info )
{

}

void
ClientInterceptorDispatcher::register_interceptor_for_all(Components::Extension::ClientContainerInterceptor_ptr interceptor)
{
	DEBUG_OUT("ClientInterceptorDispatcher: Client COPI registered for all components");

	ClientInterceptorEntry e;
	e.interceptor = Components::Extension::ClientContainerInterceptor::_duplicate( interceptor );

	interceptor->set_slot_id(component_server_->slot_id_);
	//Qedo::QedoLock l(all_client_interceptors_mutex_);
	//all_client_interceptors_mutex_.write_lock_object();
	all_client_interceptors_.push_back(e);
	//all_client_interceptors_mutex_.unlock_object();

}

void
ClientInterceptorDispatcher::set_component_server(Qedo::ComponentServerImpl* component_server)
{
	component_server_ = component_server;

}


}  //namespace Qedo

#endif
