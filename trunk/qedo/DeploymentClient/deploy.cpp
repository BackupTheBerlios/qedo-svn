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

static char rcsid[] = "$Id: deploy.cpp,v 1.3 2002/12/03 07:57:46 stoinski Exp $";


#include "DeploymentClient.h"


/**
 *
 */
int
main (int argc, char** argv)
{
	std::cout << "Qedo Test Client" << std::endl;

	std::string packageName;
    if (argc != 2)
    {
		std::cerr << "Usage : deploy <assembly_package>" << std::endl;
		std::cerr << "               <assembly_package> is a package in the local directory" << std::endl;
        return 1;
    }
    else
    {
        packageName = argv[1];
    }

	// init ORB
	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

	// Register valuetype factories
	CORBA::ValueFactoryBase_var factory;
	factory = new Qedo::CookieFactory_impl();
    orb -> register_value_factory ( "IDL:omg.org/Components/Cookie:1.0", factory );

	Qedo::DeploymentClient* client = new Qedo::DeploymentClient(orb);

	try
	{
		client->initialize();
		client->create(packageName);
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