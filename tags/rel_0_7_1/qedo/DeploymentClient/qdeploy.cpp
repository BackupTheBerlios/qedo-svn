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
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/


#include "ComponentDeployment.h"
#include "Util.h"
#include "version.h"
#ifdef _WIN32
#else
#include <unistd.h>
#endif


static char rcsid[] UNUSED = "$Id: qdeploy.cpp,v 1.16 2003/11/14 15:18:31 boehme Exp $";


/**
 * @addtogroup DeploymentClient
 * @{
 */


void
printUsage()
{
	std::cerr << "usage : qdeploy [options] <package>" << std::endl;
	std::cerr << "        [--help|-h] : print this" << std::endl;
	std::cerr << "        -s don't wait for a key press, sleep 1 sec" << std::endl;
	std::cerr << "        -f : <package> is a local file" << std::endl;
	std::cerr << "        <package> is the URL of an assembly package" << std::endl;
}


/**
 * starts the client
 */
int
main (int argc, char** argv)
{
	std::cout << "qdeploy " << QEDO_VERSION << std::endl;

	//
	// process arguments
	//
	if(argc < 2)
	{
		printUsage();
		exit ( 1 );
	}

	std::string package = argv[argc - 1];
	bool debug_mode = false;
	bool sleep_mode = false;

    for(int i = 1; i < argc;)
    {
        const char* option = argv[i];
		if((strcmp(option, "--help") == 0) || (strcmp(option, "-h") == 0))
		{
			printUsage();
			exit ( 1 );
		}
		else if(strcmp(option, "--debug") == 0)
		{
			debug_mode = true;
		}
		else if(strcmp(option, "-s") == 0)
		{
			sleep_mode = true;
		}
		else if(strcmp(option, "-f") == 0)
		{
			package = "file:///";
			package.append( Qedo::getCurrentDirectory() );
#ifdef _WIN32
			std::string::size_type pos = package.find_first_of("\\");
			while ((pos >= 0) && (pos < package.size()))
			{
				package.replace(pos, 1, "/");
				pos = package.find_first_of("\\");
			}
#endif
			package.append("/");
			package.append(argv[argc - 1]);
            
            for(int j = i ; j + 1 < argc ; j++)
                argv[j] = argv[j + 1];
            
            argc--;
		}

		i++;
	}

	if (debug_mode)
	{
		std::cerr << "..... Running in debug mode" << std::endl;
		std::cerr << "..... Please press a key when attached to process and breakpoints are set" << std::endl;
		getchar();
	}

	//
	// init ORB
	//
	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

	//
	// Register valuetype factories
	//
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::CookieFactory_impl();
    orb -> register_value_factory ( "IDL:omg.org/Components/Cookie:1.0", factory );

	//
	// deploy the assembly
	//
	Qedo::ComponentDeployment ass(package);
	try
	{
		std::cerr << "..... deploy " << package << std::endl;
		ass.deploy();
	}
	catch(Qedo::ComponentDeployment::DeploymentFailure&)
	{
		std::cerr << "Cannot deploy " << package << std::endl;
		orb->destroy();
		exit(1);
	}
	catch(CORBA::SystemException&)
	{
		std::cerr << "Cannot deploy " << package << std::endl;
		orb->destroy();
		exit(1);
	}

	//
	// wait
	//
	if ( sleep_mode )
	{
#ifdef _WIN32
		Sleep(1000);
#else
		sleep(1);
#endif
	}
	else
	{
    std::cout << "..... please press any key to destroy and undeploy the Assembly ..." << std::endl;
    getchar();
	}
	//
	// undeploy the assembly
	//
	try
	{
		ass.undeploy();
	}
	catch(Qedo::ComponentDeployment::DeploymentFailure&)
	{
		std::cerr << "Cannot undeploy " << package << std::endl;
		orb->destroy();
		exit(1);
	}
	catch(CORBA::SystemException&)
	{
		std::cerr << "Cannot undeploy " << package << std::endl;
		orb->destroy();
		exit(1);
	}
}

/** @} */
