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

#include "ServerActivatorImpl.h"
#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif
#include <iostream>
#include <cstring>
#include "version.h"

#ifdef HAVE_SIGACTION
#include <sys/types.h>  /* include this before any other sys headers */
#include <sys/wait.h>   /* header for waitpid() and various macros */
#endif

#ifndef _WIN32
#include <unistd.h>
#endif

#include <signal.h>

#include "Output.h"

static char rcsid[] UNUSED = "$Id: qcsa.cpp,v 1.16 2003/10/17 13:22:52 stoinski Exp $";

/**
 * addtogroup ServerActivator
 * @{
 */

CORBA::ORB_var orb;
Qedo::ServerActivatorImpl* server_activator;

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
	std::cout << "ServerActivatorImpl: got Crtl-C" << std::endl;
	std::cerr << "ServerActivatorImpl: unbinding from NameService" << std::endl;

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
	name[1].id = CORBA::string_dup("Activators");
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
		std::cerr << "ServerActivatorImpl: could not unbind" << std::endl;
	}
	catch(...)
	{
		std::cerr << "ServerActivatorImpl: error in signal handler" << std::endl;
	}
	
	exit(1);
}

#ifdef HAVE_SIGACTION
void
handle_sigchld
( int sig )
{
	std::cout << "\nGot SIGCHLD" << std::endl;
	int status, child_val;
	pid_t pid;

   pid = waitpid(-1, &status, WNOHANG); 
    /* Wait for any child without blocking */
    if ( pid == -1) 
    {
        /*
         * calling standard I/O functions like fprintf() in a 
         * signal handler is not recommended, but probably OK 
         * in toy programs like this one.
         */
		 std::cerr << "waitpid failed" << std::endl;
        return;
    }

    /*
     * We now have the info in 'status' and can manipulate it using
     * the macros in wait.h.
     */
    if (WIFEXITED(status))                /* did child exit normally? */
    {
        child_val = WEXITSTATUS(status); /* get child's exit status */
		  std::cout << "child's exited normally with status " << child_val << std::endl;
    }

	 std::cout << "Got signal child from " << pid << std::endl;

	 assert(server_activator);

	 server_activator->remove_by_pid(pid);
}
#endif

/**
 * starts the server for the server activator object
 */
int
main (int argc, char** argv)
{
	std::cout << "Qedo Component Server Activator " << QEDO_VERSION << std::endl;

	// Check for debug mode and enable-qos mode
	bool debug_mode = false;
	bool qos_enabled = false;
	bool terminal_enabled = false;

	for (int i = 1; i < argc; i++)
	{
		if (! strcmp(argv[i], "--debug"))
		{
			debug_mode = true;
		}
		if (! strcmp(argv[i], "--verbose"))
		{
			Qedo::debug_output = true;
		}
		if (! strcmp(argv[i], "--enable-qos"))
		{
			qos_enabled = true;
		}
		if (! strcmp(argv[i], "--terminal"))
		{
			terminal_enabled = true;
		}
	}

	orb = CORBA::ORB_init (argc, argv);

	server_activator = new Qedo::ServerActivatorImpl (orb, debug_mode, qos_enabled, terminal_enabled);

	try
	{
		server_activator->initialize();
	}
	catch (Qedo::ServerActivatorImpl::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Component Server Activator... exiting." << std::endl;
		orb->destroy();
		exit (1);
	}

#ifdef HAVE_SIGACTION
	 struct sigaction act;

    /* Assign handle_sigint as our SIGINT handler */
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

    /* Assign handle_sigchld as our SIGCHLD handler */
    act.sa_handler = handle_sigchld;

    /* We don't want to block any other signals in this example */
    sigemptyset(&act.sa_mask);

	 /*
     * We're only interested in children that have terminated, not ones
     * which have been stopped (eg user pressing control-Z at terminal)
     */
    act.sa_flags = SA_NOCLDSTOP;
	 act.sa_flags |= SA_RESTART;

    /*
     * Make these values effective. If we were writing a real 
     * application, we would probably save the old value instead of 
     * passing NULL.
     */
    if (sigaction(SIGCHLD, &act, NULL) < 0) 
    {
		 std::cerr << "sigaction failed" << std::endl;
        return 1;
    }
#else
	 signal ( SIGINT, handle_sigint );
#endif


	std::cout << "Qedo Component Server Activator is up and running ...\n";
	orb->run();

	return 0;
}

/** @} */
