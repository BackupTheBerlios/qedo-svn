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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ComponentInstallationImpl.h"
#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif
#include <iostream>
#include "version.h"
#include <signal.h>
#include "Output.h"
#include "ConfigurationReader.h"


static char rcsid[] UNUSED = "$Id: qci.cpp,v 1.24 2003/10/27 10:14:29 boehme Exp $";


/**
 * @addtogroup ComponentInstaller
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
#ifdef HAVE_SIGACTION
	 struct sigaction act;

    /* Assign sig_chld as our SIGINT handler */
    act.sa_handler = SIG_IGN;

    /* We don't want to block any other signals in this example */
    sigemptyset(&act.sa_mask);

	 sigaction(SIGINT,&act,0);
#else
	signal(sig, SIG_IGN);
#endif
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
	name[1].id = CORBA::string_dup("ComponentInstallation");
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
	catch(...)
	{
		std::cerr << "..... error in signal handler" << std::endl;
	}
	
	exit(1);
}


/**
 * starts the server for the component installer object
 */
int
main (int argc, char** argv)
{
	std::cout << "Qedo Component Installer " << QEDO_VERSION << std::endl;

	//
	// Resolve config values from config file
	//
	if (! strcmp (Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/VerboseOutput"), "true"))
	{
		Qedo::debug_output = true;
	}

	for (int i = 1; i < argc; i++)
	{
		if (! strcmp (argv[i], "--verbose"))
		{
			Qedo::debug_output = true;
		}
	}

	//
	// get the qedo dir
	//
	Qedo::g_qedo_dir = Qedo::getEnvironment( "QEDO" );
	if(Qedo::g_qedo_dir.empty())
	{
	    std::cout << "Missing Environment Variable QEDO" << std::endl;
	    std::cout << "Assuming current dir as local deployment dir" << std::endl; 
	    Qedo::g_qedo_dir = Qedo::getCurrentDirectory();
	}
	std::cout << "..... Qedo directory is " << Qedo::g_qedo_dir << std::endl;

	//
	// init ORB
	//
	orb = CORBA::ORB_init (argc, argv);

	Qedo::ComponentInstallationImpl* component_installation = new Qedo::ComponentInstallationImpl (orb);

	try
	{
		component_installation->initialize();
	}
	catch (Qedo::ComponentInstallationImpl::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Component Installer... exiting." << std::endl;
		orb->destroy();
		exit (1);
	}

#ifdef HAVE_SIGACTION
	 struct sigaction act;

    /* Assign sig_chld as our SIGINT handler */
    act.sa_handler = handle_sigint;

    /* We don't want to block any other signals in this example */
    sigemptyset(&act.sa_mask);

    /*
     * Make these values effective. If we were writing a real 
     * application, we would probably save the old value instead of 
     * passing NULL.
     */
    if (sigaction(SIGINT, &act, NULL) < 0) 
    {
		 std::cerr << "sigaction failed" << std::endl;
        return 1;
    }
#else
	 signal ( SIGINT, handle_sigint );
#endif

	std::cout << "Qedo Component Installer is up and running ...\n";
	orb->run();
	return 0;
}

/** @} */
