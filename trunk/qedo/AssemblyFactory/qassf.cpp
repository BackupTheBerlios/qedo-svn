/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#include "AssemblyFactory.h"
#include "Output.h"
#include "version.h"
#include <signal.h>


static char rcsid[] UNUSED = "$Id: qassf.cpp,v 1.14 2003/09/29 14:42:25 boehme Exp $";

/**
 * @addtogroup Assembly
 * @{
 */


CORBA::ORB_var orb;


/**
 * qedo namespace
 */
namespace Qedo {

	/** the Qedo directory */
	std::string g_qedo_dir;
};


void
handle_sigint
( int sig )
{
	signal(sig, SIG_IGN);
	std::cout << "\nGot Crtl-C" << std::endl;
	std::cerr << "..... unbind in NameService" << std::endl;

	//
	// unbind in naming service
	//
    CORBA::Object_var obj;
	CosNaming::NamingContext_var nameService;
	char hostname[256];
	gethostname(hostname, 256);
	CosNaming::Name name;
    name.length(3);
    name[0].id = CORBA::string_dup("Qedo");
    name[0].kind = CORBA::string_dup("");
	name[1].id = CORBA::string_dup("AssemblyFactory");
    name[1].kind = CORBA::string_dup("");
	name[2].id = CORBA::string_dup(hostname);
    name[2].kind = CORBA::string_dup("");
    try
    {
        obj = orb->resolve_initial_references("NameService");
		nameService = CosNaming::NamingContext::_narrow(obj.in());
		nameService->unbind(name);
    }
	catch (const CORBA::Exception&)
	{
		std::cerr << "..... could not unbind" << std::endl;
	}
	
	exit(1);
}


/**
 * start the server for the assembly factory object
 */
int
main (int argc, char** argv)
{
	std::cout << "Qedo Assembly Factory " << QEDO_VERSION << std::endl;

	//
	// get the qedo dir
	//
	Qedo::g_qedo_dir = Qedo::getEnvironment( "QEDO" );
	if(Qedo::g_qedo_dir == "")
	{
	    std::cout << "Missing Environment Variable QEDO" << std::endl;
	    Qedo::g_qedo_dir.append("./");
	}
	std::cout << "..... Qedo directory is " << Qedo::g_qedo_dir << std::endl;

	//
	// init ORB
	//
	orb = CORBA::ORB_init (argc, argv);

	//
	// register valuetype factories
	//
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::CookieFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/Cookie:1.0", factory);
	factory = new Qedo::ConfigValueFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/ConfigValue:1.0", factory);

	Qedo::AssemblyFactoryImpl* assembly_factory = new Qedo::AssemblyFactoryImpl(orb);

	try
	{
		assembly_factory->initialize();
	}
	catch (Qedo::AssemblyFactoryImpl::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Assembly Factory... exiting." << std::endl;
		orb->destroy();
		exit (1);
	}
	std::cout << "Qedo Assembly Factory Server is up and running ...\n";
	signal ( SIGINT, handle_sigint );
	orb->run();
	return 0;
}

/** @} */
