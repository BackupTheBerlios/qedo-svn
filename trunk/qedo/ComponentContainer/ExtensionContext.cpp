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

#include "ExtensionContext.h"
#include "Output.h"
#ifndef _QEDO_NO_QOS
#include "ComponentServerImpl.h"
#endif

static char rcsid[] UNUSED = "$Id: ExtensionContext.cpp,v 1.11 2004/08/20 10:52:37 tom Exp $";


namespace Qedo {
#ifndef _QEDO_NO_QOS

ExtensionContext::ExtensionContext()
{
}


ExtensionContext::~ExtensionContext()
{
	DEBUG_OUT ( "ExtensionContext: Destructor called" );
}

void
ExtensionContext::set_server_interceptor_dispatcher_registration(Components::Extension::ServerInterceptorRegistration_ptr registration)
{
	DEBUG_OUT ( "ExtensionContext: set_server_interceptor_dispatcher_registration called");
	server_registration_ = registration;
};


void
ExtensionContext::set_client_interceptor_dispatcher_registration(Components::Extension::ClientInterceptorRegistration_ptr registration)
{
	DEBUG_OUT ( "ExtensionContext: set_client_interceptor_dispatcher_registration called");
	client_registration_ = registration;
}

void
ExtensionContext::set_servant_interceptor_dispatcher_registration(Components::Extension::ServantInterceptorRegistration_ptr registration)
{
	DEBUG_OUT ( "ExtensionContext: set_servant_interceptor_dispatcher_registration called");
	servant_registration_ = registration;
};

void
ExtensionContext::set_stub_interceptor_dispatcher_registration(Components::Extension::StubInterceptorRegistration_ptr registration)
{
	DEBUG_OUT ( "ExtensionContext: set_stub_interceptor_dispatcher_registration called");
	stub_registration_ = registration;
};

Components::Extension::ServerInterceptorRegistration_ptr
ExtensionContext::get_server_interceptor_dispatcher_registration()
{
	DEBUG_OUT ( "ExtensionContext: get_server_interceptor_dispatcher_registration called");
	return Components::Extension::ServerInterceptorRegistration::_duplicate(server_registration_);

}

Components::Extension::ClientInterceptorRegistration_ptr
ExtensionContext::get_client_interceptor_dispatcher_registration()
{
	DEBUG_OUT ( "ExtensionContext: get_client_interceptor_dispatcher_registration called");
	return Components::Extension::ClientInterceptorRegistration::_duplicate(client_registration_);

}

Components::Extension::ServantInterceptorRegistration_ptr
ExtensionContext::get_servant_interceptor_dispatcher_registration()
{
	DEBUG_OUT ( "ExtensionContext: get_servant_interceptor_dispatcher_registration called");
	return Components::Extension::ServantInterceptorRegistration::_duplicate(servant_registration_);

}

Components::Extension::StubInterceptorRegistration_ptr
ExtensionContext::get_stub_interceptor_dispatcher_registration()
{
	DEBUG_OUT ( "ExtensionContext: get_stub_interceptor_dispatcher_registration called");
	return Components::Extension::StubInterceptorRegistration::_duplicate(stub_registration_);

}

void
ExtensionContext::register_servant_locator_for_all(Components::Extension::ServerContainerInterceptor_ptr server_interceptor)
{

// identify all servant locators
	Qedo::ContainerList* temp_container_list = container_->component_server_->get_all_containers();

	std::list <ContainerInterfaceImpl*>::iterator container_iter;

	for (container_iter = temp_container_list->begin(); container_iter != temp_container_list->end(); container_iter++)
	{
		for (unsigned int i = 0; i < (*container_iter) -> installed_homes_.size(); i++)
		{
			((*container_iter) -> installed_homes_)[i].home_servant_->servant_locator_ -> register_interceptor(server_interceptor);
		}
	}
}


void
ExtensionContext::set_contract_data ( const Components::ConfigValues& contract_data) {

	// test wehter the config data is a contract data

	// append data to the current list of contract data
//	contracts_ = new Components::ConfigValues();
	contracts_ = Components::ConfigValues(contract_data);
}

Components::ConfigValues*
ExtensionContext::get_contract_data ( ) {

	Components::ConfigValues* ret_contract = new Components::ConfigValues(contracts_);
//	ret_contract = contracts_;
	return ret_contract;
}

void
ExtensionContext::install_service_reference(const char* id, CORBA::Object_ptr obj)
{
	container_ -> component_server_ -> install_service_reference(id, obj);

}

CORBA::Object_ptr
ExtensionContext::get_CCM_object()
{
	return ccm_object_executor_->get_component();
}

#endif
} // namepscae Qedo

