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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _QEDO_NO_QOS


#include "ClientInterceptorDispatcher.h"
#include "Util.h"
#include <fstream>
#include "ContainerClientRequestInfo.h"

static char rcsid[] UNUSED = "$Id: ClientInterceptorDispatcher.cpp,v 1.13 2004/08/27 08:37:43 tom Exp $";

namespace Qedo {

ClientInterceptorDispatcher::ClientInterceptorDispatcher() {

}

ClientInterceptorDispatcher::~ClientInterceptorDispatcher() {

}

void
ClientInterceptorDispatcher::init_cdr ()
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
	Components::Extension::SlotInfo slot_info;
	slot >>= slot_info;
//	if (!slot_info.target_id)
//	{
//		id = "UNKNOWN_COMP_ID";
//	}

//	all_client_interceptors_mutex_.read_lock_object();
	Components::Extension::ContainerClientRequestInfo_var container_info = new Qedo::ContainerClientRequestInfo(info,slot_info.target_id,slot_info.target_id,slot_info.target_id);

	for (unsigned int i = 0; i < all_client_interceptors_.size(); i++)
	{
		try {
			all_client_interceptors_[i].interceptor->send_request( container_info.in() );
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
//	all_client_interceptors_mutex_.unlock_object();

	// set service context to transmit the caller identity to callee
		CORBA::Any context_any;
		context_any <<= slot_info.target_id;
		CORBA::OctetSeq_var data = m_cdrCodec -> encode_value(context_any);

		IOP::ServiceContext sc;

		sc.context_id = 100;

		sc.context_data.length(data->length());

		memcpy(sc.context_data.get_buffer(), data->get_buffer(), data->length());

		info -> add_request_service_context(sc, true);

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
	Components::Extension::SlotInfo slot_info;
	slot >>= slot_info;
//	if (!slot_info.target_id)
//	{
//		id = "UNKNOWN_COMP_ID";
//	}

//	all_client_interceptors_mutex_.read_lock_object();
	Components::Extension::ContainerClientRequestInfo_var container_info = new Qedo::ContainerClientRequestInfo(info,slot_info.target_id,slot_info.target_id,slot_info.target_id);

	for (unsigned int i = 0; i < all_client_interceptors_.size(); i++)
	{
		try {
			all_client_interceptors_[i].interceptor->receive_reply( container_info.in() );
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
	Components::Extension::SlotInfo slot_info;
	slot >>= slot_info;
//	if (!slot_info.target_id)
//	{
//		id = "UNKNOWN_COMP_ID";
//	}

//	all_client_interceptors_mutex_.read_lock_object();
	Components::Extension::ContainerClientRequestInfo_var container_info = new Qedo::ContainerClientRequestInfo(info,slot_info.target_id,slot_info.target_id,slot_info.target_id);

	for (unsigned int i = 0; i < all_client_interceptors_.size(); i++)
	{
		try {
			all_client_interceptors_[i].interceptor->receive_user_exception( container_info.in() );
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
ClientInterceptorDispatcher::unregister_interceptor_for_all(Components::Extension::ClientContainerInterceptor_ptr interceptor)
{
	DEBUG_OUT("ClientInterceptorDispatcher: Client COPI unregister_for_all called");

	std::vector <ClientInterceptorEntry>::iterator interceptor_iter;

	for (interceptor_iter = all_client_interceptors_.begin(); interceptor_iter != all_client_interceptors_.end(); interceptor_iter++)
	{

		if ((*interceptor_iter).interceptor == interceptor)
		{
			DEBUG_OUT ("ClientInterceptorDispatcher: unregister_interceptor_for_all(): interceptor found");
			all_client_interceptors_.erase (interceptor_iter);

			break;
		}
	}

	if (interceptor_iter == all_client_interceptors_.end())
	{
		DEBUG_OUT ("ClientInterceptorDispatcher: Unknown interceptor");
	}

}

void
ClientInterceptorDispatcher::set_component_server(Qedo::ComponentServerImpl* component_server)
{
	component_server_ = component_server;

}



}  //namespace Qedo

#endif
