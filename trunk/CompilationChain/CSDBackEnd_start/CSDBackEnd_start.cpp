
static char rcsid[] = "$Id: CSDBackEnd_start.cpp,v 1.2 2004/06/15 12:12:10 jre Exp $";

//#include <CORBA.h>

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
#include "CCMGenerator_EQUIVALENT.h"
#include "HelpFunctions.h"
#include <iostream>
using namespace std;

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
	catch (CosNaming::NamingContext::NotFound&)
	{
		std::cerr << "Component Server Activator not found in Name Service" << std::endl;
		orb->destroy();
		exit (-1);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "CORBA system exception during resolve()" << std::endl;
		orb->destroy();
		exit (-1);
	}
		
	try
	{
		server_activator = Components::Deployment::ServerActivator::_narrow (server_activator_obj);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "Cannot narrow Component Server Activator" << std::endl;
		orb->destroy();
		exit (-1);
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
		exit (-1);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "CORBA system exception during resolve()" << std::endl;
		orb->destroy();
		exit (-1);
	}
		
	try
	{
		component_installer = Components::Deployment::ComponentInstallation::_narrow (component_installer_obj);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "Cannot narrow Component Installer" << std::endl;
		orb->destroy();
		exit (-1);
	}
	if(CORBA::is_nil(component_installer))
	{
		std::cerr << "Cannot narrow Component Installer" << std::endl;
		orb->destroy();
		exit (-1);
	}

	//
	// install components
	//
	const char* path;
	path = getenv ( "qedo_backends" );
	std::string csd_servant = path ;
	std::string csd_exec = path;

#ifdef _WIN32
#ifdef ORBACUS_ORB
	csd_servant.append("\\orbacus\CCMGenerator_CSDBackEnd_compo_SERVANT.dll");
	csd_exec.append("\\orbacus\CCMGenerator_CSDBackEnd_compo.dll");
#endif//ORBACUS_ORB
#ifdef MICO_ORB
	csd_servant.append("\\CCMGenerator_CSDBackEnd_compo_SERVANT.dll");
	csd_exec.append("\\CCMGenerator_CSDBackEnd_compo.dll");
#endif//MICO_ORB
#else//!_WIN32
#ifdef ORBACUS_ORB
	csd_servant.append("/Debug_orbacus/libHelloWorld_CalleeImpl_SERVANT.so");
	csd_exec.append("/Debug_orbacus/libHelloWorld_CalleeImpl.so");
#endif//ORBACUS_ORB
#ifdef MICO_ORB
	csd_servant.append("/Debug_mico/libHelloWorld_CalleeImpl_SERVANT.so");
	csd_exec.append("/Debug_mico/libHelloWorld_CalleeImpl.so");
#endif//ORBACUS_ORB
#endif//_WIN32*/
	
	std::string CSDBackEnd_loc = csd_servant + ";create_CSDBackendHomeS;" + csd_exec + ";create_CSDBackendHomeE";
	//std::string MiddleEnd_loc = rep_servant + ";create_MOFRepositoryHomeS;" + rep_exec + ";create_MOFRepositoryHomeE";
	
	try
	{
		component_installer->install ("CSDBACKEND", CSDBackEnd_loc.c_str());
		//component_installer->install ("MIDDLEBACKEND", MiddleEnd_loc.c_str());
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
	/*std::string input;
	for (int loop = 0;loop<argc;loop++)
        std::cout << argv[loop] << std::endl;

	std::cout << "Test Client for CSDBACKEND Container" << std::endl;	
	cout << "Enter \n";
	cin >> input;*/

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
		exit (-1);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "Cannot narrow object reference of Name Service" << std::endl;
		orb->destroy();
		exit (-1);
	}

	if (CORBA::is_nil (ns))
	{
		std::cerr << "Name Service is nil" << std::endl;
		orb->destroy();
		exit (-1);
	}

	// Now get the Component Server Activator from the Name Service, use the name TETRA/Activators/<hostname>
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		std::cerr << "Cannot determine my hostname" << std::endl;
		orb->destroy();
		exit (-1);
	}

	// Get the Server Activator
	Components::Deployment::ServerActivator_var server_activator = get_server_activator (orb, ns, hostname);

	// Feed our test deployment into the Component Installer
	deploy_test_components (orb, ns, hostname);

	//
	// Begin test
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
		exit (-1);
	}

	if (CORBA::is_nil (component_server))
	{
		std::cerr << "I got a nil reference for the created Component Server" << std::endl;
		orb->destroy();
		exit (-1);
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
		exit (-1);
	}

	try
	{ 
		std::cout << "register name service in the container" << std::endl;
		container->install_service_reference("NameService", ns);
	}
	catch (Components::CCMException&)
	{
		std::cerr << "Components::CCMException by install service reference" << std::endl;
	}

	Components::CCMHome_var home;

	std::cout << "install home for caller" << std::endl;
	config.length(0);

	home = container->install_home ("CSDBACKEND", "", config);
	CCMGenerator::CSDBackendHome_var csd_home = CCMGenerator::CSDBackendHome::_narrow (home);
	if (CORBA::is_nil (csd_home))
	{
		std::cerr << "I got a nil reference for the install CSDBACKEND home" << std::endl;
		orb->destroy();
		exit (-1);
	}

	CCMGenerator::CSDBackend_var csd_backend;

	try 
	{
		/*std::cout << "press button to continue ..." << std::endl;
		getchar();*/

		std::cout << "create caller" << std::endl;
		csd_backend = csd_home->create();
	}
	catch (Components::CreateFailure&)
	{
		std::cerr << "Create Failure exception" << std::endl;
	}
	if (CORBA::is_nil (csd_home))
	{
		std::cerr << "I got a nil reference for the CSD BackEnd by create" << std::endl;
		orb->destroy();
		exit (-1);
	}
	// attribute setzen
	CORBA::Object_var obj_;
	obj_ = CCMGenerator::HelpFunctions::get_repository_ref ( orb );

	if ( CORBA::is_nil (obj_) )
	{
		std::cerr << "The repository reference ist null!!!" << std::endl;
		orb->destroy();
		exit (-1);
	}
	csd_backend->rep_ref (obj_);

	char *name, *vers, *a_name, *a_comp, *a_web, *title, *description, *lisence, *idl_id, *idl_file, *output;

	CCMGenerator::DeploymentUnitIDList_var units = new CCMGenerator::DeploymentUnitIDList;
	units->length(0);
	for (int i = 12; i < argc; i++)
	{
		char * unit_id_ = argv[i];
		units->length ( units->length () + 1);
		units[ units->length () - 1 ] = CORBA::string_dup(unit_id_);
	}
	
	name = argv[1];
	vers = argv[2];
	a_name = argv[3];
	a_comp = argv[4];
	a_web = argv[5];
	title = argv[6];
	description = argv[7];
	lisence = argv[8];
	idl_id = argv[9];
	idl_file = argv[10];
	output = argv[11];

	try
	{
		obj_ = csd_backend->provide_control();
		CCMGenerator::CSDBackEndControl_var control = 
			CCMGenerator::CSDBackEndControl::_narrow(obj_);
		if( CORBA::is_nil ( control ) )
		{
			std::cerr << "I got a nil reference for the CSDBackEndControl interface" << std::endl;
			orb->destroy();
			exit (-1);
		}

		std::cout << "configure CSD Backend" << std::endl;
		csd_backend->configuration_complete();

		control->generate( name, vers, a_name, a_comp, a_web, title, description, lisence, idl_id, idl_file, output, units );   
		
    
		/*std::cout << "press button to continue ..." << std::endl;
		getchar();*/

		csd_backend->remove();
	}
	catch (Components::RemoveFailure&)
	{
		std::cerr << "Remove Failure during remove_component()" << std::endl;
		orb->destroy();
		exit (-1);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "Hat nicht geklappt: CORBA::SystemException" << std::endl;
		orb->destroy();
		exit (-1);
	}
	catch (...)
	{
		std::cerr << "Hat nicht geklappt!!!" << std::endl;
		orb->destroy();
		exit (-1);
	}


	try
	{
		/*std::cout << "press button to continue ..." << std::endl;
		getchar();*/

		container->remove();
		component_server->remove();
		return 0;
	}
	catch (Components::RemoveFailure&)
	{
		std::cerr << "Remove Failure during removing home" << std::endl;
		orb->destroy();
		exit (-1);
	}
}
