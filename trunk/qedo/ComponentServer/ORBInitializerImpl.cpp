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

#include "ORBInitializerImpl.h"
#include "Output.h"
#include "ConfigurationReader.h"

#ifndef _QEDO_NO_QOS
#include "ServerInterceptorDispatcher.h"
#include "ClientInterceptorDispatcher.h"
#endif

static char rcsid[] UNUSED = "$Id: ORBInitializerImpl.cpp,v 1.11 2004/01/23 13:18:30 neubauer Exp $";


namespace Qedo {


ORBInitializerImpl::ORBInitializerImpl()
{
	//
	// Register our ORB initializer
	//
	PortableInterceptor::register_orb_initializer (this);
}

ORBInitializerImpl::ORBInitializerImpl(bool enable_qos)
{
    //
	// Register our ORB initializer
	//
    PortableInterceptor::register_orb_initializer (this);

	m_enable_qos = enable_qos;
}


ORBInitializerImpl::~ORBInitializerImpl()
{
}


void
ORBInitializerImpl::pre_init (PortableInterceptor::ORBInitInfo_ptr info)
{
}


void
ORBInitializerImpl::post_init (PortableInterceptor::ORBInitInfo_ptr info)
{
	//
	// First resolve the Name Service
	//
	CORBA::Object_var obj;

	try
	{
		obj = info->resolve_initial_references( "NameService" );
		if (CORBA::is_nil(obj.in()))
		{
			DEBUG_OUT( "ORBInitializerImpl: NameService is a nil object reference" );
		}
		nameService_ = CosNaming::NamingContext::_narrow(obj.in());

	}
	catch (const CORBA::ORB::InvalidName&)
	{
		DEBUG_OUT( "ORBInitializerImpl: Can't resolve NameService");
	}
	catch (const CORBA::Exception&)
	{
		DEBUG_OUT( "ORBInitializerImpl: NameService is not running") ;
		return;
	}

	if (!CORBA::is_nil(nameService_.in()))
	{
		//
		// Resolve the HomeFinder
		//
		Qedo_Components::HomeFinder_var home_finder;
		obj = resolveName("Qedo/HomeFinder");

		if (CORBA::is_nil(obj.in()))
		{
			DEBUG_OUT( "ORBInitializerImpl: HomeFinder not found");
			return;
		}

		try
		{
			home_finder = Qedo_Components::HomeFinder::_narrow(obj);
		}
		catch (CORBA::SystemException&)
		{
			DEBUG_OUT( "ORBInitializerImpl: HomeFinder is not running");
		}

		if (CORBA::is_nil(home_finder.in()))
		{
			DEBUG_OUT ("ORBInitializerImpl: HomeFinder is not running" );
		}

		//
		// register HomeFinder
		//
		info->register_initial_reference ("ComponentHomeFinder", home_finder);


	}
	else
	{
		DEBUG_OUT ("ORBInitializerImpl: NameService is not a NamingContext object reference");
	}
	//
	// Allocate a slot id to communicate data towards our components
	//
	slot_id_ = info->allocate_slot_id();


#ifndef _QEDO_NO_QOS
	//
	// Install ServerInterceptorDispatcher
	//
	if (m_enable_qos) {

		info->add_server_request_interceptor(server_dispatcher_.in());

		//info->add_client_request_interceptor(client_dispatcher_.in());

		DEBUG_OUT("ORBInitializerImpl:post_init: interceptors dispatchers registered at ORB");

	}

#endif
}


PortableInterceptor::SlotId
ORBInitializerImpl::slot_id()
{
	return slot_id_;
}

#ifndef _QEDO_NO_QOS
void
ORBInitializerImpl::set_server_dispatcher (PortableInterceptor::ServerRequestInterceptor_ptr server_dispatcher)
{
	server_dispatcher_ = server_dispatcher;
	DEBUG_OUT("ORBInitializerImpl: server_dispatcher set");
}


void
ORBInitializerImpl::set_client_dispatcher (PortableInterceptor::ClientRequestInterceptor_ptr client_dispatcher)
{
	client_dispatcher = client_dispatcher;
	DEBUG_OUT("ORBInitializerImpl: client dispatcher set");
}
#endif
} // namespace Qedo
