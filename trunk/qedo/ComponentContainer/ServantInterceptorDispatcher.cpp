/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org/                                                    */
/*                                                                         */
/* Copyright (C) 2002-2004 by the Qedo Team                                */
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
#include "ServantInterceptorDispatcher.h"
#include "Util.h"
#include "Output.h"
#include <fstream>

static char rcsid[] UNUSED = "$Id: ServantInterceptorDispatcher.cpp,v 1.5 2004/08/27 08:37:43 tom Exp $";

namespace Qedo {

ServantInterceptorDispatcher::ServantInterceptorDispatcher()
{

}

ServantInterceptorDispatcher::~ServantInterceptorDispatcher()
{

}

void
ServantInterceptorDispatcher::set_component_server(Qedo::ComponentServerImpl* component_server)
{
	component_server_ = component_server;

}


char*
ServantInterceptorDispatcher::get_target_id()
{

	CORBA::Object_var obj = component_server_ -> orb_ -> resolve_initial_references ("PICurrent");

	if ( CORBA::is_nil (obj) )
		return "UNKNOWN_COMP_ID";

	PortableInterceptor::Current_var piCurrent = PortableInterceptor::Current::_narrow (obj);

	CORBA::Any_var slot = piCurrent->get_slot (component_server_ -> slot_id_);
	Components::Extension::SlotInfo slot_info;
	slot >>= slot_info;
	if (!slot_info.target_id)
	{
		return "UNKNOWN_COMP_ID";
	}
	return strdup(slot_info.target_id);

}

char*
ServantInterceptorDispatcher::get_origin_id()
{

	CORBA::Object_var obj = component_server_ -> orb_ -> resolve_initial_references ("PICurrent");

	if ( CORBA::is_nil (obj) )
		return "UNKNOWN_COMP_ID";

	PortableInterceptor::Current_var piCurrent = PortableInterceptor::Current::_narrow (obj);

	CORBA::Any_var slot = piCurrent->get_slot (component_server_ -> slot_id_);
	Components::Extension::SlotInfo slot_info;
	slot >>= slot_info;
	if (!slot_info.origin_id)
	{
		return "UNKNOWN_COMP_ID";
	}
	return strdup(slot_info.origin_id);

}

void
ServantInterceptorDispatcher::register_interceptor_for_all(Components::Extension::ServerContainerInterceptor_ptr interceptor)
{
	DEBUG_OUT("ServantInterceptorDispatcher: Server COPI registered for all components");

	ServantInterceptorEntry e;
	e.interceptor = Components::Extension::ServerContainerInterceptor::_duplicate( interceptor );

	Qedo::QedoLock l(all_servant_interceptors_mutex_);

	all_servant_interceptors_.push_back(e);

}

void
ServantInterceptorDispatcher::unregister_interceptor_for_all(Components::Extension::ServerContainerInterceptor_ptr interceptor)
{
	DEBUG_OUT("ServantInterceptorDispatcher: Server COPI unregister_for_all called");

	std::vector <ServantInterceptorEntry>::iterator interceptor_iter;

	for (interceptor_iter = all_servant_interceptors_.begin(); interceptor_iter != all_servant_interceptors_.end(); interceptor_iter++)
	{

		if ((*interceptor_iter).interceptor == interceptor)
		{
			DEBUG_OUT ("ServantInterceptorDispatcher: unregister_interceptor_for_all(): interceptor found");
			all_servant_interceptors_.erase (interceptor_iter);

			break;
		}
	}

	if (interceptor_iter == all_servant_interceptors_.end())
	{
		DEBUG_OUT ("ServantInterceptorDispatcher: Unknown interceptor");
	}
}	

CORBA::Boolean 
ServantInterceptorDispatcher::call( const char* oper ) 
{
	DEBUG_OUT("ServantInterceptorDispatcher: get call");

	// call registered interceptors
	CORBA::Boolean con = true;
	for (unsigned int i = 0; i < all_servant_interceptors_.size(); i++)
	{
		try {

			all_servant_interceptors_[i].interceptor->call( get_target_id(), get_origin_id(), oper, con);

			if (!con)
			{
				return false;
				break;
			};
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
	con = true;
	return true ;

	// return true if the execution shall continue
	// an out parameter of type any is needed to return a possible return type
}

Components::Cookie* 
ServantInterceptorDispatcher::connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con )
{
	std::cout << "ServantInterceptor: get connect()" << std::endl;
	Components::Cookie* temp_ck;
	for (unsigned int i = 0; i < all_servant_interceptors_.size(); i++)
	{
		try {

			temp_ck = all_servant_interceptors_[i].interceptor->connect( comp_id, name, connection, con);

			if (!con)
			{
				return temp_ck;
				break;
			};
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
	con = true;
	return 0;

}


CORBA::Object_ptr 
ServantInterceptorDispatcher::provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con ) 
{
	CORBA::Object_var anObject;
	for (unsigned int i = 0; i < all_servant_interceptors_.size(); i++)
	{
		try {

			anObject = all_servant_interceptors_[i].interceptor->provide_facet( comp_id, name, con);

			if (!con)
			{
				return anObject;
				break;
			};
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
	con = true;
	return CORBA::Object::_nil();


}

#ifndef _QEDO_NO_STREAMS

Components::Cookie* 
ServantInterceptorDispatcher::bind(const char* comp_id, char*&  name,
                           StreamComponents::SinkStreamPort_ptr& the_sink,
						   char*& transport_profile,
						   CORBA::Boolean_out con)
{

	Components::Cookie* temp_ck;
	for (unsigned int i = 0; i < all_servant_interceptors_.size(); i++)
	{
		try {

			temp_ck = all_servant_interceptors_[i].interceptor->bind( comp_id, name, the_sink, transport_profile, con);

			if (!con)
			{
				return temp_ck;
				break;
			};
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
	con = true;
	return 0;
}

StreamComponents::SinkStreamPort_ptr 
ServantInterceptorDispatcher::unbind(const char* comp_id, char*&  name,
									 Components::Cookie*& ck,
									CORBA::Boolean_out con)
{

	StreamComponents::SinkStreamPort_ptr temp_port;
	for (unsigned int i = 0; i < all_servant_interceptors_.size(); i++)
	{
		try {

			temp_port = all_servant_interceptors_[i].interceptor->unbind( comp_id, name, ck, con);

			if (!con)
			{
				return temp_port;
				break;
			};
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
	con = true;
	return StreamComponents::SinkStreamPort::_nil();


}

CORBA::Object_ptr 
ServantInterceptorDispatcher::provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) 
{
	CORBA::Object_var anObject;
	for (unsigned int i = 0; i < all_servant_interceptors_.size(); i++)
	{
		try {

			anObject = all_servant_interceptors_[i].interceptor->provide_sink_stream_port( comp_id, name, con);

			if (!con)
			{
				return anObject;
				break;
			};
		} catch (CORBA::SystemException e)
		{
			throw e;
		} catch ( ... )
			// catch of user exception is probably missing
		{
		}
	}
	con = true;
	return CORBA::Object::_nil();

}

#endif //_QEDO_NO_STREAMS



}; // namespace Qedo
#endif // _QEDO_NO_QOS