//
// TETRA
// Stream Container Implementation
// (C)2000-2002 Humboldt University Berlin, Department of Computer Science
//
// $Id: main.cpp,v 1.7 2002/11/08 10:04:16 neubauer Exp $
//

static char rcsid[] = "$Id: main.cpp,v 1.7 2002/11/08 10:04:16 neubauer Exp $";

#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include "Components.h"

#include "ClientValuetypes.h"

#include "DiningPhilosophers_EQUIVALENT.h"

#include <iostream>


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

	try
	{
		component_installer->install ("PHILOSOPHER_OMG/1.0", "philosopher_omgS.dll:create_PhilosopherHomeS:philosopher_omgE.dll:create_PhilosopherHomeE");
		component_installer->install ("FORK_OMG/1.0", "philosopher_omgS.dll:create_ForkHomeS:philosopher_omgE.dll:create_ForkHomeE");
		component_installer->install ("OBSERVER_OMG/1.0", "philosopher_omgS.dll:create_ObserverHomeS:philosopher_omgE.dll:create_ObserverHomeE");
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

	home = container->install_home ("PHILOSOPHER_OMG/1.0", "", config);
	DiningPhilosophers::PhilosopherHome_var p_home = DiningPhilosophers::PhilosopherHome::_narrow (home);

	home = container->install_home ("FORK_OMG/1.0", "", config);
	DiningPhilosophers::ForkHome_var c_home = DiningPhilosophers::ForkHome::_narrow (home);

	home = container->install_home ("OBSERVER_OMG/1.0", "", config);
	DiningPhilosophers::ObserverHome_var o_home = DiningPhilosophers::ObserverHome::_narrow (home);

	DiningPhilosophers::Philosopher_var phil1;
	DiningPhilosophers::Philosopher_var phil2;
	DiningPhilosophers::Philosopher_var phil3;
	DiningPhilosophers::Philosopher_var phil4;
	DiningPhilosophers::ForkManager_var cut1;
	DiningPhilosophers::ForkManager_var cut2;
	DiningPhilosophers::ForkManager_var cut3;
	DiningPhilosophers::ForkManager_var cut4;
	DiningPhilosophers::Observer_var obs;

	try 
	{
		phil1 = p_home->create();
		phil2 = p_home->create();
		phil3 = p_home->create();
		phil4 = p_home->create();
		cut1 = c_home->create();
		cut2 = c_home->create();
		cut3 = c_home->create();
		cut4 = c_home->create();
		obs = o_home->create();
	}
	catch (Components::CreateFailure&)
	{
		std::cerr << "Create Failure exception" << std::endl;
	}
	catch (CORBA::SystemException& ex)
	{
		std::cerr << ex << std::endl;
	}

	try
	{
		phil1->name ("Frank"); 
		phil2->name ("Bert"); 
		phil3->name ("Harry");
		phil4->name ("Tom");
		DiningPhilosophers::Fork_var a_fork;
		a_fork = cut1->provide_the_fork();
		phil1->connect_left (a_fork);
		phil2->connect_right (a_fork);
		a_fork = cut2->provide_the_fork();
		phil2->connect_left (a_fork);
		phil3->connect_right (a_fork);
		a_fork = cut3->provide_the_fork();
		phil3->connect_left (a_fork);
		phil4->connect_right (a_fork);
		a_fork = cut4->provide_the_fork();
		phil4->connect_left (a_fork);
		phil1->connect_right (a_fork);

		DiningPhilosophers::StatusInfoConsumer_var consumer = obs->get_consumer_info();
		phil1->subscribe_info (consumer);
		phil2->subscribe_info (consumer);
		phil3->subscribe_info (consumer);
		phil4->subscribe_info (consumer);
		phil1->configuration_complete(); 
		phil2->configuration_complete(); 
		phil3->configuration_complete();
		phil4->configuration_complete();
		cut1->configuration_complete();
		cut2->configuration_complete();
		cut3->configuration_complete();
		cut4->configuration_complete();

		obs->configuration_complete();
	}
	catch (CORBA::SystemException& ex)
	{
		std::cerr << ex << std::endl;
	}

	Sleep (10000);
	std::cout << "Press 's' and RETURN to stop ... " << std::endl;
	std::string in_string;
	std::cin >> in_string;
	try
	{
		phil1->remove();
		phil2->remove();
		phil3->remove();
		phil4->remove();
	}
	catch (Components::RemoveFailure&)
	{
		std::cerr << "Remove Failure during remove_component()" << std::endl;
	}
	catch (CORBA::SystemException& ex)
	{
		std::cerr << ex << std::endl;
	}

	try
	{
		container->remove();
	}
	catch (Components::RemoveFailure&)
	{
		std::cerr << "Remove Failure during removing home" << std::endl;
	}
	catch (CORBA::SystemException& ex)
	{
		std::cerr << ex << std::endl;
	}

	return 0;
}