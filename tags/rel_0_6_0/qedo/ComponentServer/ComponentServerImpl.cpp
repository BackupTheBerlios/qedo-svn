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
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/

#include "ComponentServerImpl.h"
#include "Output.h"
#include "Valuetypes.h"
#include "qedoutil.h"
#include "ConfigurationReader.h"

static char rcsid[] UNUSED = "$Id: ComponentServerImpl.cpp,v 1.28 2004/02/16 07:42:13 tom Exp $";

#ifdef TAO_ORB
//#include "corbafwd.h"
#endif


namespace Qedo {



ContainerEntry::ContainerEntry (ContainerInterfaceImpl* container)
: container_ (container)
{
	container_->_add_ref();
}


ContainerEntry::ContainerEntry()
{
}


ContainerEntry::ContainerEntry (const ContainerEntry& container_entry)
: container_ (container_entry.container_)
{
	container_->_add_ref();
}


ContainerEntry&
ContainerEntry::operator= (const ContainerEntry& container_entry)
{
	if (container_)
		container_->_remove_ref();

	container_ = container_entry.container_;
	container_->_add_ref();

	return *this;
}


ContainerEntry::~ContainerEntry()
{
	DEBUG_OUT ("ContainerEntry: Destructor called");

	container_->_remove_ref();
}


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
	DEBUG_OUT ("ComponentServerImpl: Destructor called");
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

	try
	{
		//
		// try to get naming service from config values
		//
		CORBA::Object_var obj;
		std::string ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );
		if( !ns.empty() )
		{
			obj = orb_->string_to_object( ns.c_str() );
			DEBUG_OUT2( "ComponentServerImpl:: NameService is ", ns );
		}
		//
		// try to get naming service from orb
		//
		else
		{
			obj = orb_->resolve_initial_references( "NameService" );
		}
		nameService_ = CosNaming::NamingContext::_narrow( obj.in() );

		if( CORBA::is_nil(nameService_.in()) )
		{
        		NORMAL_ERR( "NameService is not a NamingContext object reference" );
		}
	}
	catch (CORBA::ORB::InvalidName&)
	{
		NORMAL_ERR ("ComponentServerImpl: Name Service not found");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot narrow object reference of Name Service");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	if (CORBA::is_nil (nameService_))
	{
		NORMAL_ERR ("ComponentServerImpl: Name Service is nil");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	// Determine the hostname of the host on which I run
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot determine my hostname");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
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
		component_installer_obj = nameService_->resolve (installer_name);
	}
	catch (CosNaming::NamingContext::NotFound&)
	{
		NORMAL_ERR ("ComponentServerImpl: Component Installer not found in Name Service");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: CORBA system exception during resolve()");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	try
	{
		component_installer_ = Components::Deployment::ComponentInstallation::_narrow (component_installer_obj);
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR ("ComponentServerImpl: Cannot narrow Component Installer");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	if (CORBA::is_nil (component_installer_))
	{
		NORMAL_ERR ("ComponentServerImpl: Component Installer is nil");
		csa_ref_->notify_component_server_create (Qedo_Components::Deployment::ComponentServer::_nil());
		throw CannotInitialize();
	}

	// Register valuetype factories
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::ConfigValueFactory_impl();
	orb_->register_value_factory ("IDL:omg.org/Components/ConfigValue:1.0", factory);
	factory = new Qedo::CookieFactory_impl();
	orb_->register_value_factory ("IDL:omg.org/Components/Cookie:1.0", factory);

	Qedo_Components::Deployment::ComponentServer_var component_server = this->_this();
	csa_ref_->notify_component_server_create (component_server.in());

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
		DEBUG_OUT2 ("ComponentServerImpl: Got ConfigValue: ", config[i]->name());
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
	else if (! strcmp (container_type_string, "EXTENSION"))
	{
		container_type = CT_EXTENSION;
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
											   this,
											   component_installer_);

	ContainerEntry new_container (container_if);

	QedoLock lock (container_mutex_);

	containers_.push_back (new_container);

	container_if->_remove_ref();

	/*
	 * install service references 
	 * these service references are unique reference in the container
	 * can be used to register CORBA services
	 */
	/* Name service */
	container_if -> install_service_reference ("NameService", nameService_.in());

	return container_if->_this();
}
 
 
void 
ComponentServerImpl::remove_container(::Components::Deployment::Container_ptr cref)
throw (Components::RemoveFailure, CORBA::SystemException)
{
	QedoLock lock (container_mutex_);

	// Find the container in our list of created containers
	std::vector <ContainerEntry>::iterator container_iter;

	for (container_iter = containers_.begin(); container_iter != containers_.end(); container_iter++)
	{
		Components::Deployment::Container_var container_ref = (*container_iter).container_->_this();

		if (container_ref->_is_equivalent (cref))
		{
			DEBUG_OUT ("ComponentServerImpl: remove_container(): Container servant found");
			break;
		}
	}

	if (container_iter == containers_.end())
	{
		DEBUG_OUT ("ComponentServerImpl: remove_container(): Unknown container");
		throw Components::RemoveFailure();
	}

	Qedo::ContainerInterfaceImpl* container = (*container_iter).container_;
	container->prepare_remove();

	PortableServer::ObjectId_var oid = root_poa_->servant_to_id (container);
	root_poa_->deactivate_object (oid.in());

	containers_.erase (container_iter);
}


::Components::Deployment::Containers* 
ComponentServerImpl::get_containers()
throw (CORBA::SystemException)
{
	QedoLock lock (container_mutex_);

	Components::Deployment::Containers_var containers = new Components::Deployment::Containers();
	containers->length (containers_.size());

	for (unsigned int i = 0; i < containers_.size(); i++)
	{
		Components::Deployment::Container_var container = containers_[i].container_->_this();
        	containers.inout()[i] = container.in();
	}

	return containers._retn();
}


void 
ComponentServerImpl::remove()
throw (Components::RemoveFailure, CORBA::SystemException)
{
	DEBUG_OUT ("ComponentServerImpl: remove() called");

	//
	// remove containers
	//
	container_mutex_.lock_object();

	if (containers_.size() > 0)
	{
		DEBUG_OUT ("ComponentServerImpl: Warning: There are still container instances around, going to remove them...");

		// We cannot use an iterator to iterate through the list, since this list will be
		// manipulated by remove_container()
		while (containers_.size())
		{
			Components::Deployment::Container_var container = containers_[0].container_->_this();
			container_mutex_.unlock_object();
			this->remove_container (container.in());
			container_mutex_.lock_object();
		}
	}

	container_mutex_.unlock_object();

	//
	// remove valuetype impls
	//
	// get mutex
	QedoLock lock (value_mutex_);

	std::vector < ValuetypeEntry > ::iterator iter;
	for(iter = valuetypes_.begin();
		iter != valuetypes_.end();
		iter++)
	{
		Qedo::unload_shared_library ((*iter).dll);
	}

	valuetypes_.clear();

	root_poa_manager_->deactivate (false /*no etherealize objects*/, false /*no wait for completion*/);

	PortableServer::ObjectId_var oid = root_poa_->servant_to_id (this);
	root_poa_->deactivate_object (oid.in());

	orb_->shutdown (false /*wait for completion*/);

	Qedo_Components::Deployment::ComponentServer_var component_server = this->_this();
	csa_ref_->notify_component_server_remove (component_server.in());
}


void
ComponentServerImpl::loadValuetypeFactory(const char* repid, const char* loc)
throw (CORBA::SystemException)
{
	// get mutex
	QedoLock lock (value_mutex_);

	//
	// search list of installed impls
	//
	std::vector < ValuetypeEntry > ::iterator iter;
	for(iter = valuetypes_.begin();
		iter != valuetypes_.end();
		iter++)
	{
		if((*iter).repid == repid)
		{
			break;
		}
	}

	//
	// already installed
	//
	if(iter != valuetypes_.end())
	{
		DEBUG_OUT3("ComponentServerImpl: Value factory for ", repid, " already registered");
		// check whether factory is already registered
		if (orb_->lookup_value_factory( repid ) == 0 )
		{
			DEBUG_OUT("ComponentServerImpl: No.");
			// unload and erase
			Qedo::unload_shared_library ((*iter).dll);
			valuetypes_.erase(iter);
		}

		(*iter).count++;
	}
	//
	// to be installed
	//
	else
	{
		DEBUG_OUT2( "ComponentServerImpl: Loading value factory code for ", repid );
#ifdef _WIN32
		HINSTANCE handle_value_lib;
#else
		void* handle_value_lib;
#endif

		handle_value_lib = Qedo::load_shared_library (loc,0);

		if (! handle_value_lib)
		{
			NORMAL_ERR2 ("ComponentServerImpl: Failed to load valuetype module ", loc);
			throw Components::CCMException();
		}

		ValuetypeEntry data;
		data.repid = repid;
		data.code = loc;
		data.count = 1;
		data.dll = handle_value_lib;
		valuetypes_.push_back(data);
	}
}

#ifndef _QEDO_NO_QOS
PortableInterceptor::SlotId
ComponentServerImpl::slot_id()
{
	return slot_id_;
}


void
ComponentServerImpl::set_server_dispatcher ( Components::Extension::ServerInterceptorRegistration_ptr server_dispatcher)
{
	server_dispatcher_ = server_dispatcher;
}

void
ComponentServerImpl::set_client_dispatcher ( Components::Extension::ClientInterceptorRegistration_ptr client_dispatcher)
{
	client_dispatcher_ = client_dispatcher;
}

Components::Extension::ServerInterceptorRegistration_ptr
ComponentServerImpl::get_server_dispatcher (  )
{
	return Components::Extension::ServerInterceptorRegistration::_duplicate (server_dispatcher_);
}

Components::Extension::ClientInterceptorRegistration_ptr
ComponentServerImpl::get_client_dispatcher (  )
{
	return Components::Extension::ClientInterceptorRegistration::_duplicate (client_dispatcher_);
}

Qedo::ContainerList*
ComponentServerImpl::get_all_containers()
{
	ContainerList* list = new ContainerList();

	for (unsigned int i = 0; i < containers_.size(); i++)
	{
		list->push_back( containers_[i].container_ );
	}

	return list;
}


#endif


} // namespace Qedo
