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
	Components::Extension::ServerInterceptorRegistration_var server_registration_;
	Components::Extension::ClientInterceptorRegistration_var client_registration_;

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
	 set_server_interceptor_dispatcher_registration(Components::Extension::ServerInterceptorRegistration_ptr registration);

	/**
	 * set_client_intercpetor_registration
	 */
	 virtual void
	 set_client_interceptor_dispatcher_registration(Components::Extension::ClientInterceptorRegistration_ptr registration);

	/**
	 * get_server_intercpetor_registration
	 */
	 virtual Components::Extension::ServerInterceptorRegistration_ptr
	 get_server_interceptor_dispatcher_registration();


	/**
	 * get_client_intercpetor_registration
	 */
	 virtual Components::Extension::ClientInterceptorRegistration_ptr
	 get_client_interceptor_dispatcher_registration();

	 virtual void
	 register_servant_locator_for_all(Components::Extension::ServerContainerInterceptor_ptr server_interceptor);

	 virtual void
	 set_contract_data ( const Components::ConfigValues& contract_data);

	 virtual Components::ConfigValues*
	 get_contract_data();

};

/** @} */
#endif
} // namespace Qedo

#endif


