#include "Debug.h"
#include "GeneratorEIDL.h"
#include "GeneratorLIDL.h"
#include "GeneratorBIDL.h"
#include "GeneratorCCD.h"
#include "GeneratorCSD.h"
#include "GeneratorBusinessH.h"
#include "GeneratorBusinessC.h"
#include "GeneratorServantH.h"
#include "GeneratorServantC.h"
#include "GeneratorVC7.h"
#include "GeneratorValuetypesH.h"
#include "GeneratorValuetypesC.h"
#include "TestMode.h"
#include "version.h"
#include "frontend.h"

#include <signal.h>
#include <iostream>
#ifdef TAO_ORB
#include "tao/TypeCodeFactory/TypeCodeFactory_Adapter_impl.h"
#endif
using namespace std;


QEDO_ComponentRepository::CIDLRepository_impl *repository;


void
handle_sigint
( int signal )
{
	std::cout << "Got Crtl-C" << std::endl;
	std::cout << "Waiting for completion..." << std::endl;
}


void
printUsage()
{
	std::cerr << "usage : gen_cidl [options] --target <compositionname> filename" << std::endl;
	std::cerr << "        [--target|-t] <compositionname> : the element to generate code for" << std::endl;
	std::cerr << "        [--business|-b] : generate business code skeletons" << std::endl;
	std::cerr << "        [--servant|-s] : generate servant code" << std::endl;
	std::cerr << "        --out <fileprefix> : idl files will be prefixed with fileprefix" << std::endl;
	std::cerr << "        --vc7 : generate VC7 projects" << std::endl;
	std::cerr << "        -d : generate XML Descriptor skeletons" << std::endl;
	std::cerr << "		  [--help|-h] : print this" << std::endl;
}


int
main
( int argc, char **argv )
{
	std::cout << "CIDL Generator Version " << GENERATOR_VERSION << std::endl;
	std::cout << "Qedo Team" << std::endl;

	/*
	// disable heap checks in debug mode to fasten up the idl compilations
	*/
#ifdef _WIN32
#ifdef _DEBUG
	// Get current flag
	int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );

	tmpFlag &= ~_CRTDBG_ALLOC_MEM_DF;

	// Set flag to the new value
	_CrtSetDbgFlag( tmpFlag );
#endif
#endif

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

	repository = new QEDO_ComponentRepository::CIDLRepository_impl ( orb, root_poa );
	bool generateEIDL = true;
	bool generateLIDL = true;
	bool generateBusiness = false;
	bool generateServant = false;
	bool generatevc7 = false;
	bool generateDescriptors = false;
	std::string target;
	std::string fileprefix = "";
	std::string target_file_name = argv[argc - 1];

	//
	// process arguments
	//
	if(argc < 2)
	{
		printUsage();
		orb->destroy();
		exit ( 1 );
	}
    for(int i = 1; i < argc;)
    {
        const char* option = argv[i];
		if((strcmp(option, "--help") == 0) || (strcmp(option, "-h") == 0))
		{
			printUsage();
			orb->destroy();
			exit ( 1 );
		}
		else if(strcmp(option, "--testmode") == 0)
		{
			frontend_replacement_feed ( repository );
            
            for(int j = i ; j + 1 < argc ; j++)
                argv[j] = argv[j + 1];
            
            argc--;
		}
		else if((strcmp(option, "--business") == 0) || (strcmp(option, "-b") == 0))
		{
			generateBusiness = true;
            
            for(int j = i ; j + 1 < argc ; j++)
                argv[j] = argv[j + 1];
            
            argc--;
		}
		else if((strcmp(option, "--servant") == 0) || (strcmp(option, "-s") == 0))
		{
			generateServant = true;
            
            for(int j = i ; j + 1 < argc ; j++)
                argv[j] = argv[j + 1];
            
            argc--;
		}
		else if(strcmp(option, "--vc7") == 0)
		{
			generatevc7 = true;
            
            for(int j = i ; j + 1 < argc ; j++)
                argv[j] = argv[j + 1];
            
            argc--;
		}
		else if(strcmp(option, "-d") == 0)
		{
			generateDescriptors = true;
            
            for(int j = i ; j + 1 < argc ; j++)
                argv[j] = argv[j + 1];
            
            argc--;
		}
		else if((strcmp(option, "--target") == 0) || (strcmp(option, "-t") == 0))
		{
			if(i + 1 >= argc)
			{
				std::cerr << "argument expected for --target" << std::endl;
				orb -> destroy();
				exit ( 1 );
			}

            target = argv[i + 1];
            
            for(int j = i ; j + 2 < argc ; j++)
                argv[j] = argv[j + 2];
            
            argc -= 2;
		}
		else if(strcmp(option, "--out") == 0)
		{
			if(i + 1 >= argc)
			{
				std::cerr << "argument expected for --out" << std::endl;
				orb -> destroy();
				exit ( 1 );
			}

            fileprefix = argv[i + 1];
            
            for(int j = i ; j + 2 < argc ; j++)
                argv[j] = argv[j + 2];
            
            argc -= 2;
		}
		else
		{
			i++;
		}
	}

	if(target == "")
	{
		printUsage();
		orb->destroy();
		exit ( 1 );
	}

	// feed repository
	frontend_feed ( argc, argv, repository -> _this() );

	if(generateEIDL)
	{
		// generate equivalent IDL
		std::cout << "Generating equivalent IDL for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorEIDL *eidl_generator =
			new QEDO_CIDL_Generator::GeneratorEIDL(repository, orb.in());
		eidl_generator->generate(target, fileprefix);
		eidl_generator->destroy();
	}

	if(generateLIDL)
	{
		// generate local IDL
		std::cout << "Generating local IDL for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorLIDL *lidl_generator =
			new QEDO_CIDL_Generator::GeneratorLIDL(repository);
		lidl_generator->generate(target, fileprefix);
		lidl_generator->destroy();
	}

	if(generateBusiness)
	{
		// generate local business IDL
		std::cout << "Generating local business IDL for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorBIDL *bidl_generator =
			new QEDO_CIDL_Generator::GeneratorBIDL(repository);
		bidl_generator->generate(target, fileprefix);
		bidl_generator->destroy();

		// generate business header
		std::cout << "Generating business code header for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorBusinessH *bh_generator =
			new QEDO_CIDL_Generator::GeneratorBusinessH(repository);
		bh_generator->generate(target, fileprefix);
		bh_generator->destroy();
	
		// generate business code
		std::cout << "Generating business code for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorBusinessC *bc_generator =
			new QEDO_CIDL_Generator::GeneratorBusinessC(repository);
		bc_generator->generate(target, fileprefix);
		bc_generator->destroy();

		// generate valuetype header
		std::cout << "Generating valuetype header" << std::endl;
		QEDO_CIDL_Generator::GeneratorValuetypesH *vth_generator =
			new QEDO_CIDL_Generator::GeneratorValuetypesH(repository);
		vth_generator->generate(target, fileprefix);
		vth_generator->destroy();

		// generate valuetype code
		std::cout << "Generating valuetype code" << std::endl;
		QEDO_CIDL_Generator::GeneratorValuetypesC *vtc_generator =
			new QEDO_CIDL_Generator::GeneratorValuetypesC(repository);
		vtc_generator->generate(target, fileprefix);
		vtc_generator->destroy();
	}

	if(generateDescriptors)
	{
		// generate CORBA Component Descriptor
		std::cout << "Generating CORBA Component Descriptor for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorCCD *ccd_generator =
			new QEDO_CIDL_Generator::GeneratorCCD(repository);
		ccd_generator->generate(target, fileprefix);
		ccd_generator->destroy();

		// generate Software Package Descriptor
		std::cout << "Generating Software Package Descriptor for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorCSD *csd_generator =
			new QEDO_CIDL_Generator::GeneratorCSD(repository);
		csd_generator->generate(target, fileprefix);
		csd_generator->destroy();
	}

	if(generateServant)
	{
		// generate servant header
		std::cout << "Generating servant code header for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorServantH *sh_generator =
			new QEDO_CIDL_Generator::GeneratorServantH(repository);
		sh_generator->generate(target, fileprefix);
		sh_generator->destroy();

		// generate servant code
		std::cout << "Generating servant code for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorServantC *sc_generator =
			new QEDO_CIDL_Generator::GeneratorServantC(repository);
		sc_generator->generate(target, fileprefix);
		sc_generator->destroy();
	}

	if(generatevc7)
	{
		// generate VC7 projects
		std::cout << "Generating VC7 projetcs for " << target << std::endl;
		QEDO_CIDL_Generator::GeneratorVC7 *vc7_generator =
			new QEDO_CIDL_Generator::GeneratorVC7(repository);
		vc7_generator->target_file_name_ = target_file_name;
		vc7_generator->generate(target, fileprefix);
		vc7_generator->destroy();
	}

	signal ( SIGINT, SIG_DFL );

	repository -> destroy_repository();

	orb -> shutdown ( false );


	return 0;
}
