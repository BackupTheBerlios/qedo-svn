/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002-2003 by the Qedo Team                                */
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

#ifndef __EXTENSION_CONTEXT_H__
#define __EXTENSION_CONTEXT_H__

#include <CORBA.h>
#include <Components.h>
#include "CCMContext.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */

#ifndef _QEDO_NO_QOS
/**
 * the extension context
 */
class CONTAINERDLL_API ExtensionContext : public virtual Components::ExtensionContext,
										public virtual CCMContext
{
private:
	Components::ContainerPortableInterceptor::ServerContainerInterceptorRegistration_var server_registration_;
	Components::ContainerPortableInterceptor::ClientContainerInterceptorRegistration_var client_registration_;
	Components::ContainerPortableInterceptor::ServantContainerInterceptorRegistration_var servant_registration_;
	Components::ContainerPortableInterceptor::StubContainerInterceptorRegistration_var stub_registration_;

	/*
	* list of config values to store contract inforamtion 
	*/
	Components::ConfigValues contracts_;

public:
	/**
	 * constructor
	 */
	ExtensionContext();

	/**
	 * destructor
	 */
	~ExtensionContext();

	/**
	 * set_server_intercpetor_registration
	 */
	 virtual void
	 set_server_interceptor_dispatcher_registration(Components::ContainerPortableInterceptor::ServerContainerInterceptorRegistration_ptr registration);

	/**
	 * set_client_intercpetor_registration
	 */
	 virtual void
	 set_client_interceptor_dispatcher_registration(Components::ContainerPortableInterceptor::ClientContainerInterceptorRegistration_ptr registration);

	/**
	 * set_servant_intercpetor_registration
	 */
	 virtual void
	 set_servant_interceptor_dispatcher_registration(Components::ContainerPortableInterceptor::ServantContainerInterceptorRegistration_ptr registration);

	/**
	 * set_servant_intercpetor_registration
	 */
	 virtual void
	 set_stub_interceptor_dispatcher_registration(Components::ContainerPortableInterceptor::StubContainerInterceptorRegistration_ptr registration);

	 /**
	 * get_server_intercpetor_registration
	 */
	 virtual Components::ContainerPortableInterceptor::ServerContainerInterceptorRegistration_ptr
	 get_server_interceptor_dispatcher_registration();


	/**
	 * get_client_intercpetor_registration
	 */
	 virtual Components::ContainerPortableInterceptor::ClientContainerInterceptorRegistration_ptr
	 get_client_interceptor_dispatcher_registration();

	 /**
	 * get_servant_intercpetor_registration
	 */
	 virtual Components::ContainerPortableInterceptor::ServantContainerInterceptorRegistration_ptr
	 get_servant_interceptor_dispatcher_registration();

	 /**
	 * get_servant_intercpetor_registration
	 */
	 virtual Components::ContainerPortableInterceptor::StubContainerInterceptorRegistration_ptr
	 get_stub_interceptor_dispatcher_registration();

	 virtual void
	 register_servant_locator_for_all(Components::ContainerPortableInterceptor::ServerContainerInterceptor_ptr server_interceptor);

	 virtual void
	 set_contract_data ( const Components::ConfigValues& contract_data);

	 virtual Components::ConfigValues*
	 get_contract_data();

	 virtual void
	 install_service_reference(const char* id, CORBA::Object_ptr obj);

    /**
	 * implements IDL:omg.org/Components/SessionContext/get_CCM_object:1.0
	 * provide the reference to the CCMObject of the component
	 * delegated to the object executor
	 * \return The object reference of the component.
	 */
    CORBA::Object_ptr get_CCM_object();

};

/** @} */
#endif
} // namespace Qedo

#endif


