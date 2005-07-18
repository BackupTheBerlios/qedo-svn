
static char rcsid[] = "$Id: main.cpp,v 1.4 2003/10/10 15:58:51 tom Exp $";

#include <CORBA.h>

#ifdef MICO_ORB
#ifdef WIN32
#include "Winsock2.h"
#endif
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif

#include "Components.h"
#include "ClientValuetypes.h"
#include "HelloWorld_EQUIVALENT.h"
#include <iostream>

#ifndef _WIN32
#include <unistd.h>
#endif


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
	catch (...)
	{
		std::cerr << "Can not resolve Component Server Activator" << std::endl;
		orb->destroy();
		exit (1);
	}

	server_activator = Components::Deployment::ServerActivator::_narrow (server_activator_obj);
	if(CORBA::is_nil(server_activator))
	{
		std::cerr << "Cannot narrow Component Server Activator" << std::endl;
		orb->destroy();
		exit (1);
	}

	return server_activator._retn();
}


void
deploy_test_components (CORBA::ORB_ptr orb, CosNaming::NamingContext_ptr ns, const char* hostname)
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
	catch (...)
	{
		std::cerr << "Can not resolve Component Installer" << std::endl;
		orb->destroy();
		exit (1);
	}
	
	component_installer = Components::Deployment::ComponentInstallation::_narrow (component_installer_obj);
	if(CORBA::is_nil(component_installer))
	{
		std::cerr << "Cannot narrow Component Installer" << std::endl;
		orb->destroy();
		exit (1);
	}

	//
	// install components
	//
	char path[1024];
#ifdef _WIN32
    ::GetCurrentDirectory(1024, path);
#else
    getcwd(path,1023);
#endif
	std::string callee_servant = path;
	std::string callee_exec = path;
	std::string caller_servant = path;
	std::string caller_exec = path;
#ifdef _WIN32
#ifdef ORBACUS_ORB
	callee_servant.append("/../../HelloWorld_CalleeImpl_SERVANT/Debug_orbacus/HelloWorld_CalleeImpl_SERVANT.dll");
	callee_exec.append("/../../HelloWorld_CalleeImpl/Debug_orbacus/HelloWorld_CalleeImpl.dll");
	caller_servant.append("/../../HelloWorld_CallerImpl_SERVANT/Debug_orbacus/HelloWorld_CallerImpl_SERVANT.dll");
	caller_exec.append("/../../HelloWorld_CallerImpl/Debug_orbacus/HelloWorld_CallerImpl.dll");
#endif
#ifdef MICO_ORB
	callee_servant.append("/../../HelloWorld_CalleeImpl_SERVANT/Debug_mico/HelloWorld_CalleeImpl_SERVANT.dll");
	callee_exec.append("/../../HelloWorld_CalleeImpl/Debug_mico/HelloWorld_CalleeImpl.dll");
	caller_servant.append("/../../HelloWorld_CallerImpl_SERVANT/Debug_mico/HelloWorld_CallerImpl_SERVANT.dll");
	caller_exec.append("/../../HelloWorld_CallerImpl/Debug_mico/HelloWorld_CallerImpl.dll");
#endif
#else
#ifdef ORBACUS_ORB
	callee_servant.append("/Debug_orbacus/libHelloWorld_CalleeImpl_SERVANT.so");
	callee_exec.append("/Debug_orbacus/libHelloWorld_CalleeImpl.so");
	caller_servant.append("/Debug_orbacus/libHelloWorld_CallerImpl_SERVANT.so");
	caller_exec.append("/Debug_orbacus/libHelloWorld_CallerImpl.so");
#endif
#ifdef MICO_ORB
	callee_servant.append("/Debug_mico/libHelloWorld_CalleeImpl_SERVANT.so");
	callee_exec.append("/Debug_mico/libHelloWorld_CalleeImpl.so");
	caller_servant.append("/Debug_mico/libHelloWorld_CallerImpl_SERVANT.so");
	caller_exec.append("/Debug_mico/libHelloWorld_CallerImpl.so");
#endif
#endif

	std::string callee_loc = callee_servant + ";create_CalleeHomeS;" + callee_exec + ";create_CalleeHomeE";
	std::string caller_loc = caller_servant + ";create_CallerHomeS;" + caller_exec + ";create_CallerHomeE";
	try
	{
		component_installer->install ("CALLER/1.0", caller_loc.c_str());
		component_installer->install ("CALLEE/1.0", callee_loc.c_str());
	}
	catch (Components::Deployment::InvalidLocation&)
	{
		std::cerr << "Component Installer raised Components::Deployment::InvalidLocation" << std::endl;
	}
	catch (Components::Deployment::InstallationFailure&)
	{
		std::cerr << "Component Installer raised Components::Deployment::InstallationFailure" << std::endl;
	}
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

	// Feed our test deployment into the Component Installer
	deploy_test_components (orb, ns, hostname);

	//
	// Begin tests
	//

	// Create Component Server
	std::cout << "create component server" << std::endl;
	Components::ConfigValues config;
	Components::ConfigValues home_config;
	Components::Deployment::ComponentServer_var component_server;

	//
	// first try to use an existing component server
	// create a new one otherwise
	//

	Components::Deployment::ComponentServers_var component_servers = server_activator->get_component_servers();
	if (component_servers->length() > 0)
	{
		component_server = component_servers.in()[0];
	} else
	{
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

	std::cout << "register name service in the container" << std::endl;
	container->install_service_reference("NameService", ns);

	Components::CCMHome_var home;

	std::cout << "install home for caller" << std::endl;
	config.length(0);
	home = container->install_home ("CALLER/1.0", "", config);
	HelloWorld::CallerHome_var caller_home = HelloWorld::CallerHome::_narrow (home);

	std::cout << "install home for callee" << std::endl;
	home = container->install_home ("CALLEE/1.0", "", config);
	HelloWorld::CalleeHome_var callee_home = HelloWorld::CalleeHome::_narrow (home);

	HelloWorld::Caller_var caller;
	HelloWorld::Callee_var callee;

	try 
	{
		std::cout << "press button to continue ..." << std::endl;
		getchar();

		std::cout << "create caller" << std::endl;
		caller = caller_home->create();

		std::cout << "create callee" << std::endl;
		callee = callee_home->create();
	}
	catch (Components::CreateFailure&)
	{
		std::cerr << "Create Failure exception" << std::endl;
	}

	try
	{
		std::cout << "connect caller and callee" << std::endl;
		HelloWorld::Hello_var a_hello;
		a_hello = callee->provide_the_hello();
		caller->connect_hi(a_hello.in());

		std::cout << "configure callee" << std::endl;
		callee->configuration_complete();
		std::cout << "configure caller and call" << std::endl;
		caller->configuration_complete();

		caller->remove();
		callee->remove();
	}
	catch (Components::RemoveFailure&)
	{
		std::cerr << "Remove Failure during remove_component()" << std::endl;
	}

	try
	{
		std::cout << "press button to continue ..." << std::endl;
		getchar();

		container->remove();

		component_server->remove();
	}
	catch (Components::RemoveFailure&)
	{
		std::cerr << "Remove Failure during removing home" << std::endl;
	}

	return 0;
}
