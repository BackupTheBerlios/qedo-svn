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
#include "StubInterceptorDispatcher.h"
#include "Util.h"
#include "Output.h"
#include <fstream>

static char rcsid[] UNUSED = "$Id: StubInterceptorDispatcher.cpp,v 1.2 2004/08/27 08:37:43 tom Exp $";

namespace Qedo {

StubInterceptorDispatcher::StubInterceptorDispatcher()
{

}

StubInterceptorDispatcher::~StubInterceptorDispatcher()
{

}

void
StubInterceptorDispatcher::set_component_server(Qedo::ComponentServerImpl* component_server)
{
	component_server_ = component_server;

}

void
StubInterceptorDispatcher::register_interceptor_for_all(Components::Extension::ClientContainerInterceptor_ptr interceptor)
{
	DEBUG_OUT("StubInterceptorDispatcher: Client COPI registered for all components");

	StubInterceptorEntry e;
	e.interceptor = Components::Extension::ClientContainerInterceptor::_duplicate( interceptor );

	Qedo::QedoLock l(all_stub_interceptors_mutex_);

	all_stub_interceptors_.push_back(e);

}

void
StubInterceptorDispatcher::unregister_interceptor_for_all(Components::Extension::ClientContainerInterceptor_ptr interceptor)
{
DEBUG_OUT("ServerInterceptorDispatcher: Stub interceptor Dispatcher unregister_for_all called");

	std::vector <StubInterceptorEntry>::iterator interceptor_iter;

	for (interceptor_iter = all_stub_interceptors_.begin(); interceptor_iter != all_stub_interceptors_.end(); interceptor_iter++)
	{

		if ((*interceptor_iter).interceptor == interceptor)
		{
			DEBUG_OUT ("StubInterceptorDispatcher: unregister_interceptor_for_all(): interceptor found");
			all_stub_interceptors_.erase (interceptor_iter);

			break;
		}
	}

	if (interceptor_iter == all_stub_interceptors_.end())
	{
		DEBUG_OUT ("ServerinterceptorDispatcher: Unknown interceptor");
	}

}

CORBA::Boolean 
StubInterceptorDispatcher::call( const char* oper ) 
{
	// call registered interceptors

	// return true if the execution shall continue
	// an out parameter of type any is needed to return a possible return type
	DEBUG_OUT("ServantInterceptorDispatcher: get call");
	return true;
}

Components::Cookie* 
StubInterceptorDispatcher::connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con )
{
	Components::Cookie* temp_ck;
	for (unsigned int i = 0; i < all_stub_interceptors_.size(); i++)
	{
		try {

			temp_ck = all_stub_interceptors_[i].interceptor->connect( comp_id, name, connection, con);

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
StubInterceptorDispatcher::provide_facet( const char* comp_id, const char* name, CORBA::Boolean_out con ) 
{
	CORBA::Object_var anObject;
	for (unsigned int i = 0; i < all_stub_interceptors_.size(); i++)
	{
		try {

			anObject = all_stub_interceptors_[i].interceptor->provide_facet( comp_id, name, con);

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
StubInterceptorDispatcher::bind(const char* comp_id, char*&  name,
                           StreamComponents::SinkStreamPort_ptr& the_sink,
						   char*& transport_profile,
						   CORBA::Boolean_out con)
{

	Components::Cookie* temp_ck;
	for (unsigned int i = 0; i < all_stub_interceptors_.size(); i++)
	{
		try {

			temp_ck = all_stub_interceptors_[i].interceptor->bind( comp_id, name, the_sink, transport_profile, con);

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
StubInterceptorDispatcher::unbind(const char* comp_id, char*&  name,
									 Components::Cookie*& ck,
									CORBA::Boolean_out con)
{

	StreamComponents::SinkStreamPort_ptr temp_port;
	for (unsigned int i = 0; i < all_stub_interceptors_.size(); i++)
	{
		try {

			temp_port = all_stub_interceptors_[i].interceptor->unbind( comp_id, name, ck, con);

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
StubInterceptorDispatcher::provide_sink_stream_port( const char* comp_id, char*& name, CORBA::Boolean_out con ) 
{
	CORBA::Object_var anObject;
	for (unsigned int i = 0; i < all_stub_interceptors_.size(); i++)
	{
		try {

			anObject = all_stub_interceptors_[i].interceptor->provide_sink_stream_port( comp_id, name, con);

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