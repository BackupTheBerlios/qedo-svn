
static char rcsid[] = "$Id: main.cpp,v 1.1 2003/08/29 10:55:30 tom Exp $";

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
#include "Chat_EQUIVALENT.h"
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
    getcwd(path,1023));
#endif
	std::string writer_servant = path;
	std::string writer_exec = path;
	std::string channel_servant = path;
	std::string channel_exec = path;
	std::string reader_servant = path;
	std::string reader_exec = path;

#ifdef _WIN32
#ifdef ORBACUS_ORB
	writer_servant.append("/../../Chat_Writer_Compo_SERVANT/Debug_orbacus/Chat_Writer_Compo_SERVANT.dll");
	writer_exec.append("/../../Chat_Writer_Compo/Debug_orbacus/Chat_Writer_Compo.dll");
	channel_servant.append("/../../Chat_Channel_Compo_SERVANT/Debug_orbacus/Chat_Channel_Compo_SERVANT.dll");
	channel_exec.append("/../../Chat_Channel_Compo/Debug_orbacus/Chat_Channel_Compo.dll");
	reader_servant.append("/../../Chat_Reader_Compo_SERVANT/Debug_orbacus/Chat_Reader_Compo_SERVANT.dll");
	reader_exec.append("/../../Chat_Reader_Compo/Debug_orbacus/Chat_Reader_Compo.dll");
#endif
#ifdef MICO_ORB
	callee_servant.append("/HelloWorld_CalleeImpl_SERVANT.dll");
	callee_exec.append("/HelloWorld_CalleeImpl.dll");
	caller_servant.append("/HelloWorld_CallerImpl_SERVANT.dll");
	caller_exec.append("/HelloWorld_CallerImpl.dll");
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

	std::string writer_loc = writer_servant + ";create_ChatWriterHomeS;" + writer_exec + ";create_ChatWriterHomeE";
	std::string channel_loc = channel_servant + ";create_ChatChannelHomeS;" + channel_exec + ";create_ChatChannelHomeE";
	std::string reader_loc = reader_servant + ";create_ChatReaderHomeS;" + reader_exec + ";create_ChatReaderHomeE";

	try
	{
		component_installer->install ("WRITER/1.0", writer_loc.c_str());
		component_installer->install ("CHANNEL/1.0", channel_loc.c_str());
		component_installer->install ("READER/1.0", reader_loc.c_str());

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

	std::cout << "register name service in the container" << std::endl;
	container->install_service_reference("NameService", ns);

	Components::CCMHome_var home;

	std::cout << "install home for writer" << std::endl;
	config.length(0);
	home = container->install_home ("WRITER/1.0", "", config);
	Chat::ChatWriterHome_var writer_home = Chat::ChatWriterHome::_narrow (home);

	std::cout << "install home for channel" << std::endl;
	config.length(0);
	home = container->install_home ("CHANNEL/1.0", "", config);
	Chat::ChatChannelHome_var channel_home = Chat::ChatChannelHome::_narrow (home);

	std::cout << "install home for reader" << std::endl;
	config.length(0);
	home = container->install_home ("READER/1.0", "", config);
	Chat::ChatReaderHome_var reader_home = Chat::ChatReaderHome::_narrow (home);

	Chat::ChatWriter_var writer;
	Chat::ChatChannel_var channel;
	Chat::ChatReader_var reader;

	try 
	{
		std::cout << "press button to create instances ..." << std::endl;
		getchar();

		std::cout << "create writer" << std::endl;
		writer = writer_home->create();

		std::cout << "create channel" << std::endl;
		channel= channel_home->create();

		std::cout << "create reader" << std::endl;
		reader= reader_home->create();

	}
	catch (Components::CreateFailure&)
	{
		std::cerr << "Create Failure exception" << std::endl;
	}

	try
	{
		std::cout << "connect writer, channel, and reader" << std::endl;
		Chat::ChatMessageConsumer_var a_message_consumer;
	
		a_message_consumer = channel->get_consumer_from_writer();
		writer->connect_to_channel(a_message_consumer.in());

		a_message_consumer = reader->get_consumer_from_channel();
		channel->subscribe_to_reader(a_message_consumer.in());

		// configuration complete
		std::cout << "configure complete reader" << std::endl;
		reader->configuration_complete();
		
		std::cout << "configure complete channel" << std::endl;
		channel->configuration_complete();

		std::cout << "configure complete writer" << std::endl;
		writer->configuration_complete();

	} catch (Components::InvalidConfiguration&)
	{
		std::cout << "failure with the configuration" << std::endl;
	};

	std::cout << "press button to start the writer ..." << std::endl;
	getchar();
	Chat::ClientControl_var control = writer->provide_control();
	control->request_and_push_message();

	try {
		std::cout << "press button to remove components ..." << std::endl;
		getchar();

		writer->remove();
		channel->remove();
		reader->remove();
	} catch (Components::RemoveFailure&)
	{
		std::cerr << "Remove Failure during remove_component()" << std::endl;
	}

	try
	{
		std::cout << "press button to remove container and component server ..." << std::endl;
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
