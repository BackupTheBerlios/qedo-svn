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

#include "CORBA.h"
#include "CosNaming.h"
#include "DCI_Basics_NodeManagerImpl_EQUIVALENT.h"
#include "ClientValuetypes.h"


Components::Deployment::ServerActivator_ptr
get_server_activator (CORBA::ORB_ptr orb, CosNaming::NamingContext_ptr ns, const char* hostname)
{
	std::cout << "Getting Component Server Activator from Qedo/Activators/" << hostname << std::endl;

	CosNaming::Name server_activator_name;
	server_activator_name.length (3);
	server_activator_name[0].id = CORBA::string_dup ("Qedo");
	server_activator_name[0].kind = CORBA::string_dup ("");
	server_activator_name[1].id = CORBA::string_dup ("Activators");
	server_activator_name[1].kind = CORBA::string_dup ("");
	server_activator_name[2].id = CORBA::string_dup (hostname);
	server_activator_name[2].kind = CORBA::string_dup ("");

	Components::Deployment::ServerActivator_var server_activator;
	CORBA::Object_var server_activator_obj;

	try
	{
		server_activator_obj = ns->resolve (server_activator_name);
	}
	catch (CosNaming::NamingContext::NotFound&)
	{
		std::cerr << "Component Server Activator not found in Name Service" << std::endl;
		orb->destroy();
		exit (1);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "CORBA system exception during resolve()" << std::endl;
		orb->destroy();
		exit (1);
	}
		
	try
	{
		server_activator = Components::Deployment::ServerActivator::_narrow (server_activator_obj);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "Cannot narrow Component Server Activator" << std::endl;
		orb->destroy();
		exit (1);
	}

	return server_activator._retn();
}

Components::Deployment::ComponentInstallation*
get_component_installation(CORBA::ORB_ptr orb, CosNaming::NamingContext_ptr ns, const char* hostname)
{
	std::cout << "Getting Component Installation from Qedo/ComponentInstallation/" << hostname << std::endl;

	CosNaming::Name installer_name;
	installer_name.length (3);
	installer_name[0].id = CORBA::string_dup ("Qedo");
	installer_name[0].kind = CORBA::string_dup ("");
	installer_name[1].id = CORBA::string_dup ("ComponentInstallation");
	installer_name[1].kind = CORBA::string_dup ("");
	installer_name[2].id = CORBA::string_dup (hostname);
	installer_name[2].kind = CORBA::string_dup ("");

	Components::Deployment::ComponentInstallation_var component_installer;
	CORBA::Object_var component_installer_obj;

	try
	{
		component_installer_obj = ns->resolve (installer_name);
	}
	catch (CosNaming::NamingContext::NotFound&)
	{
		std::cerr << "Component Installer not found in Name Service" << std::endl;
		orb->destroy();
		exit (1);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "CORBA system exception during resolve()" << std::endl;
		orb->destroy();
		exit (1);
	}
		
	try
	{
		component_installer = Components::Deployment::ComponentInstallation::_narrow (component_installer_obj);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "Cannot narrow Component Installer" << std::endl;
		orb->destroy();
		exit (1);
	}

return component_installer._retn();
}


int
main (int argc, char** argv)
{
	std::cout << "Test Client for Stream Container" << std::endl;

	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

    orb->register_value_factory ("IDL:omg.org/Components/FacetDescription:1.0", new FacetDescriptionFactory_impl());
	orb->register_value_factory ("IDL:omg.org/Components/ReceptacleDescription:1.0", new ReceptacleDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/SubscriberDescription:1.0", new SubscriberDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/EmitterDescription:1.0", new EmitterDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/ConsumerDescription:1.0", new ConsumerDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/Cookie:1.0", new CookieFactory_impl());

	CosNaming::NamingContext_var ns;

	try
	{
		CORBA::Object_var ns_obj = orb->resolve_initial_references ("NameService");
		ns = CosNaming::NamingContext::_narrow (ns_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		std::cerr << "Name Service not found" << std::endl;
		orb->destroy();
		exit (1);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "Cannot narrow object reference of Name Service" << std::endl;
		orb->destroy();
		exit (1);
	}

	if (CORBA::is_nil (ns))
	{
		std::cerr << "Name Service is nil" << std::endl;
		orb->destroy();
		exit (1);
	}

	// Now get the Component Server Activator from the Name Service, use the name TETRA/Activators/<hostname>
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		std::cerr << "Cannot determine my hostname" << std::endl;
		orb->destroy();
		exit (1);
	}
	// Get the Server Activator
	Components::Deployment::ServerActivator_var server_activator = get_server_activator (orb, ns, hostname);

	Components::Deployment::ComponentInstallation_var component_installer = get_component_installation (orb, ns, hostname);

	try {
#if _WIN32
		component_installer->install ("NodeManagerImpl/1.0", "DCI_Basics_NodeManagerImpl_SERVANT.dll:create_NodeManagerHomeS:DCI_Basics_NodeManagerImpl_EXECUTOR.dll:create_NodeManagerHomeE");
#else
//		component_installer->install ("NodeManagerImpl/1.0", "libCallerS.so:create_CallerHomeS:libCallerE.so:create_CallerHomeE");
#endif
	}
	catch (Components::Deployment::InvalidLocation&)
	{
		std::cerr << "Component Installer raised Components::Deployment::InvalidLocation" << std::endl;
	}
	catch (Components::Deployment::InstallationFailure&)
	{
		std::cerr << "Component Installer raised Components::Deployment::InstallationFailure" << std::endl;
	}

	// Create Component Server
	std::cout << "create component server" << std::endl;
	Components::ConfigValues config;
	Components::Deployment::ComponentServer_var component_server;

	try
	{
		component_server = 	server_activator->create_component_server (config);
	}
	catch (CORBA::Exception&)
	{
		std::cerr << "Exception during test run" << std::endl;
		orb->destroy();
		exit (1);
	}

	if (CORBA::is_nil (component_server))
	{
		std::cerr << "I got a nil reference for the created Component Server" << std::endl;
		orb->destroy();
		exit (1);
	}

	// Create Container
	std::cout << "create container" << std::endl;
	Components::Deployment::Container_var container;
	config.length (1);
	CORBA::Any any;
	any <<= "SESSION";
	config[0] = new ConfigValue_impl ("CONTAINER_TYPE", any);

	try
	{
		container = component_server->create_container (config);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "CORBA system exception during creating container" << std::endl;
		orb->destroy();
		exit (1);
	}

	config.length(0);

	Components::CCMHome_var home;

	std::cout << "install home for NodeManager" << std::endl;
	home = container->install_home ("NodeManagerImpl/1.0", "", config);
	DCI_Basics::NodeManagerHome_var node_manager_home = DCI_Basics::NodeManagerHome::_narrow (home);

	DCI_Basics::NodeManager_var node_manager;
	try {
	node_manager = node_manager_home->create();

	}
	catch (Components::CreateFailure&)
	{
		std::cerr << "Create Failure exception" << std::endl;
	}
	catch (CORBA::SystemException& ex)
	{
		std::cerr << /*ex <<*/ std::endl;
	}

	try	{
		std::cout << "connect NodeManager with ci and csa" << std::endl;
		// needs to be adapted if other CCM implementations are used.
		node_manager->connect_orig_component_installation(Components::Deployment::ComponentInstallation::_duplicate(component_installer.in()));
		node_manager->connect_orig_server_activator(server_activator);

		std::cout << "start NodeManager" << std::endl;
		node_manager->configuration_complete();
	}
	catch (CORBA::SystemException& ex)
	{
		std::cerr << /*ex <<*/ std::endl;
	}

	return 0;
};