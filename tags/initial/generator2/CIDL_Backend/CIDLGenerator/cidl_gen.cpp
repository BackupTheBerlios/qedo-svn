#include "Debug.h"
#include "GeneratorEIDL.h"
#include "GeneratorLIDL.h"
#include "GeneratorBIDL.h"
#include "GeneratorCCD.h"
#include "GeneratorBusinessH.h"
#include "GeneratorBusinessC.h"
#include "GeneratorServantH.h"
#include "GeneratorServantC.h"
#include "TestMode.h"
#include <frontend.h>

#include <signal.h>
#include <iostream>


using namespace std;


QEDO_ComponentRepository::CIDLRepository_impl *repository;


void
handle_sigint
( int signal )
{
	std::cout << "Got Crtl-C" << std::endl;
	std::cout << "Waiting for completion..." << std::endl;
}


int
main
( int argc, char **argv )
{
	std::cout << "CIDL Generator Version 0.x" << std::endl;
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

	signal ( SIGINT, handle_sigint );


	//
	// feed the repository (Test whether we have to use test mode)
	//
	string target;
	repository = new QEDO_ComponentRepository::CIDLRepository_impl ( orb, root_poa );
	if ( !strcmp ( argv[1], "--testmode" ) ) {
		frontend_replacement_feed ( repository );
	}
	else {
		if(argc < 3) {
			std::cerr << std::endl;
			std::cerr << "usage : gen_cidl [options] filename target_module" << std::endl;
			orb->destroy();
			exit ( 1 );
		}
		target = argv[--argc];
		frontend_feed ( argc, argv, repository -> _this() );
	}


	// generate equivalent IDL
	std::cout << "Generating equivalent IDL for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorEIDL *eidl_generator =
		new QEDO_CIDL_Generator::GeneratorEIDL(repository);
	eidl_generator->generate(target);

	// generate local IDL
	std::cout << "Generating local IDL for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorLIDL *lidl_generator =
		new QEDO_CIDL_Generator::GeneratorLIDL(repository);
	lidl_generator->generate(target);

	// generate local business IDL
	std::cout << "Generating local business IDL for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorBIDL *bidl_generator =
		new QEDO_CIDL_Generator::GeneratorBIDL(repository);
	bidl_generator->generate(target);

	// generate CORBA Component Descriptor
	std::cout << "Generating CORBA Component Descriptor for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorCCD *ccd_generator =
		new QEDO_CIDL_Generator::GeneratorCCD(repository);
	ccd_generator->generate(target);

	// generate business header
	std::cout << "Generating business code header for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorBusinessH *bh_generator =
		new QEDO_CIDL_Generator::GeneratorBusinessH(repository);
	bh_generator->generate(target);
	
	// generate business code
	std::cout << "Generating business code for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorBusinessC *bc_generator =
		new QEDO_CIDL_Generator::GeneratorBusinessC(repository);
	bc_generator->generate(target);

	// generate servant header
	std::cout << "Generating servant code header for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorServantH *sh_generator =
		new QEDO_CIDL_Generator::GeneratorServantH(repository);
	sh_generator->generate(target);

	// generate servant code
	std::cout << "Generating servant code for " << target << std::endl;
	QEDO_CIDL_Generator::GeneratorServantC *sc_generator =
		new QEDO_CIDL_Generator::GeneratorServantC(repository);
	sc_generator->generate(target);


	//
	// destroy all
	//
	eidl_generator->destroy();
	lidl_generator->destroy();
	bidl_generator->destroy();
	ccd_generator->destroy();
	bh_generator->destroy();
	bc_generator->destroy();
	sh_generator->destroy();
	sc_generator->destroy();

	signal ( SIGINT, SIG_DFL );

	repository -> destroy_repository();

	orb -> shutdown ( false );


	return 0;
}
