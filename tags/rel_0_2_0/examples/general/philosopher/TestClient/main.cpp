//
// TETRA
// Stream Container Implementation
// (C)2000-2002 Humboldt University Berlin, Department of Computer Science
//
// $Id: main.cpp,v 1.5 2003/05/12 13:10:34 neubauer Exp $
//

static char rcsid[] = "$Id: main.cpp,v 1.5 2003/05/12 13:10:34 neubauer Exp $";

#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include "Components.h"

#include "ClientValuetypes.h"

#include "dinner_EQUIVALENT.h"

#include <iostream>

using namespace std;

Components::Deployment::ServerActivator_ptr
get_server_activator (CORBA::ORB_ptr orb, CosNaming::NamingContext_ptr ns, const char* hostname)
{
	cout << "Getting Component Server Activator from Qedo/Activators/" << hostname << endl;

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
		cerr << "Component Server Activator not found in Name Service" << endl;
		orb->destroy();
		exit (1);
	}
	catch (CORBA::SystemException&)
	{
		cerr << "CORBA system exception during resolve()" << endl;
		orb->destroy();
		exit (1);
	}
		
	try
	{
		server_activator = Components::Deployment::ServerActivator::_narrow (server_activator_obj);
	}
	catch (CORBA::SystemException&)
	{
		cerr << "Cannot narrow Component Server Activator" << endl;
		orb->destroy();
		exit (1);
	}

	return server_activator._retn();
}


void
deploy_test_components (CORBA::ORB_ptr orb, CosNaming::NamingContext_ptr ns, const char* hostname)
{
	cout << "Getting Component Installation from Qedo/ComponentInstallation/" << hostname << endl;

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
		cerr << "Component Installer not found in Name Service" << endl;
		orb->destroy();
		exit (1);
	}
	catch (CORBA::SystemException&)
	{
		cerr << "CORBA system exception during resolve()" << endl;
		orb->destroy();
		exit (1);
	}
		
	try
	{
		component_installer = Components::Deployment::ComponentInstallation::_narrow (component_installer_obj);
	}
	catch (CORBA::SystemException&)
	{
		cerr << "Cannot narrow Component Installer" << endl;
		orb->destroy();
		exit (1);
	}

	try
	{
		component_installer->install ("PHILOSOPHER/1.0", "philosopherS.dll;create_PhilosopherHomeS;philosopherE.dll;create_PhilosopherHomeE");
		component_installer->install ("CUTLERY/1.0", "philosopherS.dll;create_CutleryHomeS;philosopherE.dll;create_CutleryHomeE");
		component_installer->install ("OBSERVER/1.0", "philosopherS.dll;create_ObserverHomeS;philosopherE.dll;create_ObserverHomeE");
	}
	catch (Components::Deployment::InvalidLocation&)
	{
		cerr << "Component Installer raised Components::Deployment::InvalidLocation" << endl;
	}
	catch (Components::Deployment::InstallationFailure&)
	{
		cerr << "Component Installer raised Components::Deployment::InstallationFailure" << endl;
	}
}


int
main (int argc, char** argv)
{
	cout << "Test Client for Stream Container" << endl;

	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

    orb->register_value_factory ("IDL:omg.org/Components/FacetDescription:1.0", new FacetDescriptionFactory_impl());
	orb->register_value_factory ("IDL:omg.org/Components/ReceptacleDescription:1.0", new ReceptacleDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/SubscriberDescription:1.0", new SubscriberDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/EmitterDescription:1.0", new EmitterDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/ConsumerDescription:1.0", new ConsumerDescriptionFactory_impl());
    orb->register_value_factory ("IDL:omg.org/Components/ComponentPortDescription:1.0", new ComponentPortDescriptionFactory_impl());

	CosNaming::NamingContext_var ns;

	try
	{
		CORBA::Object_var ns_obj = orb->resolve_initial_references ("NameService");
		ns = CosNaming::NamingContext::_narrow (ns_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		cerr << "Name Service not found" << endl;
		orb->destroy();
		exit (1);
	}
	catch (CORBA::SystemException&)
	{
		cerr << "Cannot narrow object reference of Name Service" << endl;
		orb->destroy();
		exit (1);
	}

	if (CORBA::is_nil (ns))
	{
		cerr << "Name Service is nil" << endl;
		orb->destroy();
		exit (1);
	}

	// Now get the Component Server Activator from the Name Service, use the name TETRA/Activators/<hostname>
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		cerr << "Cannot determine my hostname" << endl;
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
		cerr << "Exception during test run" << endl;
		orb->destroy();
		exit (1);
	}

	if (CORBA::is_nil (component_server))
	{
		cerr << "I got a nil reference for the created Component Server" << endl;
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
	catch (CORBA::SystemException& ex)
	{
		cerr << "CORBA system exception during creating container : " << ex << endl;
		orb->destroy();
		exit (1);
	}

	config.length(0);

	Components::CCMHome_var home;

	home = container->install_home ("PHILOSOPHER/1.0", "", config);
	dinner::PhilosopherHome_var p_home = dinner::PhilosopherHome::_narrow (home);

	home = container->install_home ("CUTLERY/1.0", "", config);
	dinner::CutleryHome_var c_home = dinner::CutleryHome::_narrow (home);

	home = container->install_home ("OBSERVER/1.0", "", config);
	dinner::ObserverHome_var o_home = dinner::ObserverHome::_narrow (home);

	dinner::Philosopher_var phil1;
	dinner::Philosopher_var phil2;
	dinner::Philosopher_var phil3;
	dinner::Cutlery_var cut1;
	dinner::Cutlery_var cut2;
	dinner::Observer_var obs;

	try 
	{
		phil1 = p_home->create();
		phil2 = p_home->create();
		phil3 = p_home->create();
		cut1 = c_home->create();
		cut2 = c_home->create();
		obs = o_home->create();
	}
	catch (Components::CreateFailure&)
	{
		cerr << "Create Failure exception" << endl;
	}
	catch (CORBA::SystemException& ex)
	{
		cerr << ex << endl;
	}

	try
	{
		phil1->name ("Frank"); 
		phil2->name ("Bert"); 
		phil3->name ("Harry");
		phil1->thinking_seconds (5); 
		phil2->thinking_seconds (3); 
		phil3->thinking_seconds (6);
		phil1->eating_seconds (4); 
		phil2->eating_seconds (6); 
		phil3->eating_seconds (3);
		phil1->sleeping_seconds (6); 
		phil2->sleeping_seconds (7); 
		phil3->sleeping_seconds (5);
		dinner::Fork_var a_fork;
		a_fork = cut1->provide_the_fork();
		phil1->connect_left_hand (a_fork);
		phil2->connect_left_hand (a_fork);
		phil3->connect_left_hand (a_fork);
		a_fork = cut2->provide_the_fork();
		phil1->connect_right_hand (a_fork);
		phil2->connect_right_hand (a_fork);
		phil3->connect_right_hand (a_fork);
		dinner::PhilosopherStateConsumer_var consumer = obs->get_consumer_philosopher_state();
		phil1->connect_philosopher_state (consumer);
		phil2->connect_philosopher_state (consumer);
		phil3->connect_philosopher_state (consumer);
		phil1->configuration_complete(); 
		phil2->configuration_complete(); 
		phil3->configuration_complete();
		cut1->configuration_complete();
		cut2->configuration_complete();
		obs->configuration_complete();
	}
	catch (CORBA::SystemException& ex)
	{
		cerr << ex << endl;
	}

	Sleep (10000);

	try
	{
		phil1->remove();
		phil2->remove();
		phil3->remove();
		c_home->remove_component (cut1);
		c_home->remove_component (cut2);
	}
	catch (Components::RemoveFailure&)
	{
		cerr << "Remove Failure during remove_component()" << endl;
	}
	catch (CORBA::SystemException& ex)
	{
		cerr << ex << endl;
	}


	try
	{
		container->remove_home (c_home);
		container->remove_home (p_home);
	}
	catch (Components::RemoveFailure&)
	{
		cerr << "Remove Failure during removing home" << endl;
	}
	catch (CORBA::SystemException& ex)
	{
		cerr << ex << endl;
	}

	return 0;
}