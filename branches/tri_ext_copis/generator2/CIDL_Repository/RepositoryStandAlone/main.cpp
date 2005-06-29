#include "version.h"
#include "CIDLRepository_impl.h"
#include <fstream>

int
main
( int argc, char **argv )
{
	std::cout << "CIDL Repository Version " << GENERATOR_VERSION << std::endl;
	std::cout << "Qedo Team" << std::endl;


	//
	// get ORB
	//
	CORBA::ORB_var orb;
	try
	{
		orb = CORBA::ORB_init ( argc, argv );
	}
	catch ( ... )
	{
		std::cerr << "Error during ORB_init()" << std::endl;
		exit ( 1 );
	}


	//
	// get POA
	//
	PortableServer::POA_var root_poa;
	try
	{
		CORBA::Object_var root_poa_obj = orb->resolve_initial_references ( "RootPOA" );
		root_poa = PortableServer::POA::_narrow ( root_poa_obj );
	}
	catch ( ... )
	{
		std::cerr << "Error during getting root POA" << std::endl;
		orb -> destroy();
		exit ( 1 );
	}


	//
	// get POA manager and activate it
	//
	PortableServer::POAManager_var root_poa_manager;
	try
	{
		root_poa_manager = root_poa -> the_POAManager();
	}
	catch ( ... )
	{
		std::cerr << "Error getting root POA manager" << std::endl;
		orb->destroy();
		exit ( 1 );
	}
	root_poa_manager -> activate();

	QEDO_ComponentRepository::CIDLRepository_impl* repository = new QEDO_ComponentRepository::CIDLRepository_impl ( orb, root_poa );

	CORBA::Object_var anObject = root_poa->servant_to_reference(repository);

	CIDL::CIDLRepository_var rep_ref = CIDL::CIDLRepository::_narrow(anObject);

	std::string rep_ior;
	rep_ior = orb->object_to_string(rep_ref);

	std::ofstream ior_file;
	ior_file.open("rep.ior");

	ior_file << rep_ior.c_str();

	ior_file.close();

	orb->run();

	return 0;

};
