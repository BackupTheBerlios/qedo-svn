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

#include "ComponentServerImpl.h"
#include "ContainerInterfaceImpl.h"
#include "Output.h"
#include "Valuetypes.h"

static char rcsid[] UNUSED = "$Id: ComponentServerImpl.cpp,v 1.11 2003/08/01 12:25:30 boehme Exp $";

#ifdef TAO_ORB
//#include "corbafwd.h"
#endif

namespace Qedo {

ComponentServerImpl::ComponentServerImpl (CORBA::ORB_ptr orb, 
										  const char* csa_string_ref,
										  PortableInterceptor::SlotId slot_id)
: csa_string_ref_ (CORBA::string_dup (csa_string_ref)),
  orb_ (CORBA::ORB::_duplicate (orb)),
  slot_id_ (slot_id)
{
}


ComponentServerImpl::~ComponentServerImpl()
{
}


void
ComponentServerImpl::initialize()
{
	try
	{
		CORBA::Object_var root_poa_obj = orb_->resolve_initial_references ("RootPOA");
		root_poa_ = PortableServer::POA::_narrow (root_poa_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		NORMAL_ERR ("ComponentServerImpl: Fatal error - no root POA available.");
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: Fatal error - cannot narrow root POA.");
		throw CannotInitialize();
	}

	root_poa_manager_ = root_poa_->the_POAManager();

	root_poa_manager_->activate();

	// Convert the stringified object reference from the command line into a usable ComponentServerActivator reference
	CORBA::Object_var csa_obj;
	
	try
	{
		csa_obj = orb_->string_to_object (csa_string_ref_);
	}
	catch (CORBA::BAD_PARAM&)
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot get Component Server Activator object reference from string");
		throw CannotInitialize();
	}


	if (CORBA::is_nil (csa_obj))
	{
		NORMAL_ERR ("ComponentServerImpl: Component Server Activator object reference is nil");
		throw CannotInitialize();
	}

	try
	{
		csa_ref_ = Qedo_Components::Deployment::ServerActivator::_narrow (csa_obj);
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot narrow Component Server Activator object reference");
		throw CannotInitialize();
	}

	// Now retrieve the Component Installer to be used for containers created by this Component Server
	// From now, we also inform the Component Server Activator to return a nil reference in case of any failure
	// First get the Name Service
	CosNaming::NamingContext_var ns;

	try
	{
		CORBA::Object_var ns_obj = orb_->resolve_initial_references ("NameService");
		ns = CosNaming::NamingContext::_narrow (ns_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		NORMAL_ERR ("ComponentServerImpl: Name Service not found");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot narrow object reference of Name Service");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	if (CORBA::is_nil (ns))
	{
		NORMAL_ERR ("ComponentServerImpl: Name Service is nil");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	// Determine the hostname of the host on which I run
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot determine my hostname");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	// Finally resolve the Component Installer
	CosNaming::Name installer_name;
	installer_name.length (3);
	installer_name[0].id = CORBA::string_dup ("Qedo");
	installer_name[0].kind = CORBA::string_dup ("");
	installer_name[1].id = CORBA::string_dup ("ComponentInstallation");
	installer_name[1].kind = CORBA::string_dup ("");
	installer_name[2].id = CORBA::string_dup (hostname);
	installer_name[2].kind = CORBA::string_dup ("");

	CORBA::Object_var component_installer_obj;

	try
	{
		component_installer_obj = ns->resolve (installer_name);
	}
	catch (CosNaming::NamingContext::NotFound&)
	{
		NORMAL_ERR ("ComponentServerImpl: Component Installer not found in Name Service");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: CORBA system exception during resolve()");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}
		
	try
	{
		component_installer_ = Components::Deployment::ComponentInstallation::_narrow (component_installer_obj);
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot narrow Component Installer");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	if (CORBA::is_nil (component_installer_))
	{
		NORMAL_ERR ("ComponentServerImpl: Component Installer is nil");
		csa_ref_->notify_component_server (Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	// Register valuetype factories
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::ConfigValueFactory_impl();
    orb_->register_value_factory ("IDL:omg.org/Components/ConfigValue:1.0", factory);
	factory = new Qedo::CookieFactory_impl();
    orb_->register_value_factory ("IDL:omg.org/Components/Cookie:1.0", factory);

	csa_ref_->notify_component_server (this->_this());
}


::Components::ConfigValues* 
ComponentServerImpl::configuration()
throw (CORBA::SystemException)
{
	return 0;
}

 
::Components::Deployment::ServerActivator_ptr 
ComponentServerImpl::get_server_activator()
throw (CORBA::SystemException)
{
	return Qedo_Components::Deployment::ServerActivator::_duplicate(csa_ref_);
}


::Components::Deployment::Container_ptr 
ComponentServerImpl::create_container(const ::Components::ConfigValues& config)
throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException)
{
	Qedo::ContainerInterfaceImpl* container_if;

	// handle configuration
	const char* container_type_string = "";

	for (unsigned int i = 0; i < config.length(); i++)
	{
		std::cerr << "Got ConfigValue: \"" << config[i]->name() << "\"\n";
		if (! strcmp (config[i]->name(), "CONTAINER_TYPE"))
		{
			config[i]->value() >>= container_type_string;

			break;
		}
	}

	ContainerType container_type;
	std::string message;

	if (! container_type_string)
	{
		message = "..... no CONTAINER_TYPE specified";
		DEBUG_OUT (message);
		throw Components::InvalidConfiguration();
	}
	if (! strcmp (container_type_string, "Empty"))
	{
		container_type = CT_EMPTY;
	}
	else if (! strcmp (container_type_string, "SERVICE"))
	{
		container_type = CT_SERVICE;
	}
	else if (! strcmp (container_type_string, "SESSION"))
	{
		container_type = CT_SESSION;
	}
	else if (! strcmp (container_type_string, "PROCESS"))
	{
			container_type = CT_PROCESS;
	}
	else if (! strcmp (container_type_string, "ENTITY"))
	{
		container_type = CT_ENTITY;
	}
	else
	{
		message = "..... wrong CONTAINER_TYPE specified";
		DEBUG_OUT (message);
		throw Components::InvalidConfiguration();
	}

	message = "ComponentServerImpl: Create new ContainerInterfaceImpl with container type ";
	message.append(container_type_string);
	DEBUG_OUT (message);

	container_if = new ContainerInterfaceImpl (orb_, 
											   root_poa_, 
											   container_type, 
											   component_installer_);

	Components::Deployment::Container_var container = container_if->_this();
	containers_.push_back(Components::Deployment::Container::_duplicate(container));

	return container._retn();
}
 
 
void 
ComponentServerImpl::remove_container(::Components::Deployment::Container_ptr cref)
throw (Components::RemoveFailure, CORBA::SystemException)
{
	// TODO
}


::Components::Deployment::Containers* 
ComponentServerImpl::get_containers()
throw (CORBA::SystemException)
{
	Components::Deployment::Containers_var containers = new Components::Deployment::Containers();
	containers->length (containers_.size());

	for (unsigned int i = 0; i < containers_.size(); i++)
	{
        containers.inout()[i] = containers_[i];
	}

	return containers._retn();
}


void 
ComponentServerImpl::remove()
throw (Components::RemoveFailure, CORBA::SystemException)
{
	// TODO
}


} // namespace Qedo
