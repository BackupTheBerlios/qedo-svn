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
#include "ServerInterceptorDispatcher.h"

static char rcsid[] UNUSED = "$Id: ORBInitializerImpl.cpp,v 1.5.6.2 2003/09/10 06:13:33 tom Exp $";


namespace Qedo {


ORBInitializerImpl::ORBInitializerImpl()
{
	server_dispatcher_=PortableInterceptor::ServerRequestInterceptor::_nil();
	client_dispatcher_=PortableInterceptor::ClientRequestInterceptor::_nil();

    //
	// Register our ORB initializer
	//
    PortableInterceptor::register_orb_initializer (this);
}

ORBInitializerImpl::ORBInitializerImpl(bool enable_qos)
{
	server_dispatcher_=PortableInterceptor::ServerRequestInterceptor::_nil();
	client_dispatcher_=PortableInterceptor::ClientRequestInterceptor::_nil();

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
#ifndef MICO_ORB
	try
    {
        obj = info->resolve_initial_references("NameService");
    }
    catch (const CORBA::ORB::InvalidName&)
    {
		std::cerr << "ORBInitializerImpl: Can't resolve NameService" << std::endl;
		return;
    }

    if (CORBA::is_nil(obj.in()))
    {
		std::cerr << "ORBInitializerImpl: NameService is a nil object reference" << std::endl;
		return;
    }

	try
	{
		nameService_ = CosNaming::NamingContext::_narrow(obj.in());
	}
	catch (const CORBA::Exception&)
	{
		std::cerr << "ORBInitializerImpl: NameService is not running" << std::endl;
		return;
	}

    if (CORBA::is_nil(nameService_.in()))
    {
		std::cerr << "ORBInitializerImpl: NameService is not a NamingContext object reference" << std::endl;
		return;
    }

    //
	// Resolve the HomeFinder
	//
	Qedo_Components::HomeFinder_var home_finder;
	obj = resolveName("Qedo/HomeFinder");

	if (CORBA::is_nil(obj.in()))
    {
		std::cerr << "ORBInitializerImpl: HomeFinder not found" << std::endl;
		return;
    }

    try
    {
        home_finder = Qedo_Components::HomeFinder::_narrow(obj);
    }
    catch (CORBA::SystemException&)
    {
        std::cerr << "ORBInitializerImpl: HomeFinder is not running" << std::endl;
		return;
    }

	if (CORBA::is_nil(home_finder.in()))
    {
		std::cerr << "ORBInitializerImpl: HomeFinder is not running" << std::endl;
		return;
    }

	//
	// register HomeFinder
	//
	info->register_initial_reference ("ComponentHomeFinder", home_finder);
#endif
	//
	// Allocate a slot id to communicate data towards our components
	//
	slot_id_ = info->allocate_slot_id();


	if (m_enable_qos) {
		DEBUG_OUT("ComponentServer: ORBInitializer is registering interceptor dispatcher");
		//
		// Install ServerInterceptorDispatcher
		//
		info->add_server_request_interceptor(server_dispatcher_.in());

		//
		// Install ClientInterceptorDispatcher
		//
		info->add_client_request_interceptor(client_dispatcher_.in());

	}
}


PortableInterceptor::SlotId
ORBInitializerImpl::slot_id()
{
	return slot_id_;
}

void 
ORBInitializerImpl::set_server_dispatcher (PortableInterceptor::ServerRequestInterceptor_ptr server_dispatcher)
{
	server_dispatcher_ = server_dispatcher;

}

void 
ORBInitializerImpl::set_client_dispatcher (PortableInterceptor::ClientRequestInterceptor_ptr client_dispatcher)
{
	client_dispatcher_ = client_dispatcher;
}

} // namespace Qedo
