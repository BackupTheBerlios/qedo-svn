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

#include "HomeServantBase.h"
#include "ServantLocator.h"
#include "GetComponentHelperServant.h"
#include "Output.h"
#include "GlobalHelpers.h"


static char rcsid[] UNUSED = "$Id: ServantLocator.cpp,v 1.14 2004/03/08 11:10:50 boehme Exp $";

namespace Qedo {


ServantLocator::ServantLocator (HomeServantBase* home_servant)
: home_servant_ (home_servant)
{
}


ServantLocator::~ServantLocator()
{
	DEBUG_OUT ("ServantLocator: Destructor called");
}


PortableServer::Servant
ServantLocator::preinvoke (const PortableServer::ObjectId& oid,
						   PortableServer::POA_ptr adapter,
						   const char* operation,
						   PortableServer::ServantLocator::Cookie& the_cookie )
throw (PortableServer::ForwardRequest, CORBA::SystemException)
{
	// Our helper get_component operation will be handled by a special servant
	if (!strcmp (operation, "_component") || !strcmp (operation, "get_component"))
	{
		DEBUG_OUT ("ServantLocator: ######### GetComponentHelperServant: returning parametrized helper servant ########");

		Components::CCMObject_var ccm_object = home_servant_->lookup_component (oid);

		Qedo::GetComponentHelperServant* helper_servant = new Qedo::GetComponentHelperServant (ccm_object);

		return helper_servant;
	}

	/*
	//
	// call services registered for preinvoke, but exclude services itself
	//
	if(home_servant_->service_name_.empty())
	{
		std::vector <Qedo::ComponentInstance> ::iterator iter;

		Components::CCMService_ptr service;

		for (iter = home_servant_->container_->services_preinvoke_.begin();
			 iter != home_servant_->container_->services_preinvoke_.end(); iter++)
		{
 			service = dynamic_cast<Components::CCMService_ptr>((*iter).executor_locator_.in());
 			service->preinvoke((*iter).uuid_.c_str(), operation);

		}
	}*/

#ifndef _QEDO_NO_QOS
if(!CORBA::is_nil(server_interceptor_))
{
//	if (Qedo::compare_object_ids(oid_,oid))
		server_interceptor_->rec_request_from_servant_locator(operation);

}
#endif

	return home_servant_->lookup_servant (oid);
}


void
ServantLocator::postinvoke (const PortableServer::ObjectId& oid,
							PortableServer::POA_ptr adapter,
							const char* operation,
							PortableServer::ServantLocator::Cookie the_cookie,
							PortableServer::Servant the_servant )
throw (CORBA::SystemException)
{
	/*
	//
	// call services registered for postinvoke
	//
	if(home_servant_->service_name_.empty())
	{
		std::vector <Qedo::ComponentInstance> ::iterator iter;

		Components::CCMService_ptr service;

		for (iter = home_servant_->container_->services_postinvoke_.begin();
			 iter != home_servant_->container_->services_postinvoke_.end(); iter++)
		{
 			service = dynamic_cast<Components::CCMService_ptr>((*iter).executor_locator_.in());
 			service->postinvoke((*iter).uuid_.c_str(), operation);
		}
	}*/

	the_servant->_remove_ref();
}

#ifndef _QEDO_NO_QOS
void
ServantLocator::register_interceptor(Components::Extension::ServerContainerInterceptor_ptr interceptor)
{
server_interceptor_ = interceptor;

}


void
ServantLocator::register_interceptor_with_oid(Components::Extension::ServerContainerInterceptor_ptr interceptor, PortableServer::ObjectId* oid)
{
server_interceptor_ = interceptor;
oid_ = oid;
}


#endif
} // namespace Qedo
