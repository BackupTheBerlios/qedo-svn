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


#include "DeploymentClient.h"
#include "Util.h"
#include "version.h"
#ifdef _WIN32
#else
#include <unistd.h>
#endif


static char rcsid[] UNUSED = "$Id: qdeploy.cpp,v 1.10 2003/09/01 10:47:48 neubauer Exp $";


/**
 * @addtogroup DeploymentClient
 * @{
 */


void
printUsage()
{
	std::cerr << "usage : deploy [options] <package>" << std::endl;
	std::cerr << "		  [--help|-h] : print this" << std::endl;
	std::cerr << "        -f : <package> is a local file" << std::endl;
	std::cerr << "        <package> is the URL of an assembly package" << std::endl;
}


/**
 * starts the client
 */
int
main (int argc, char** argv)
{
	std::cout << "Qedo Deployment Client " << QEDO_VERSION << std::endl;

	//
	// process arguments
	//
	if(argc < 2)
	{
		printUsage();
		exit ( 1 );
	}

	std::string package = argv[argc - 1];

    for(int i = 1; i < argc;)
    {
        const char* option = argv[i];
		if((strcmp(option, "--help") == 0) || (strcmp(option, "-h") == 0))
		{
			printUsage();
			exit ( 1 );
		}
		else if(strcmp(option, "-f") == 0)
		{
			package = "file:///";
			char path[1024];
#ifdef _WIN32
			GetCurrentDirectory(1024, path);
			package.append(path);
			std::string::size_type pos = package.find_first_of("\\");
			while ((pos >= 0) && (pos < package.size()))
			{
				package.replace(pos, 1, "/");
				pos = package.find_first_of("\\");
			}
#else
			getcwd(path,1023);
			package.append(path);
#endif
			package.append("/");
			package.append(argv[argc - 1]);
            
            for(int j = i ; j + 1 < argc ; j++)
                argv[j] = argv[j + 1];
            
            argc--;
		}
		else
		{
			i++;
		}
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

	Qedo::DeploymentClient* client = new Qedo::DeploymentClient(orb);

	try
	{
		client->initialize();
		client->create(package);
	}
	catch(Qedo::DeploymentClient::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Test Client ... exiting." << std::endl;
		orb->destroy();
		exit(1);
	}
	catch(CORBA::SystemException&)
	{
		std::cerr << "CORBA system exception ... exiting." << std::endl;
		orb->destroy();
		exit(1);
	}
}

/** @} */
