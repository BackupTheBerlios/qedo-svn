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

static char rcsid[] UNUSED = "$Id: ServantInterceptorDispatcher.cpp,v 1.4 2004/08/16 10:13:52 tom Exp $";

namespace Qedo {

ServantInterceptorDispatcher::ServantInterceptorDispatcher()
{

}

ServantInterceptorDispatcher::~ServantInterceptorDispatcher()
{

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

CORBA::Boolean 
ServantInterceptorDispatcher::call( const char* oper ) 
{
	// call registered interceptors

	// return true if the execution shall continue
	// an out parameter of type any is needed to return a possible return type
	DEBUG_OUT("ServantInterceptorDispatcher: get call");
	return true;
}

Components::Cookie* 
ServantInterceptorDispatcher::connect( const char* comp_id, const char* name, CORBA::Object_ptr connection, CORBA::Boolean_out con )
{
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