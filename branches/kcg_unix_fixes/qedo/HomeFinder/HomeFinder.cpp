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

#include "HomeFinderImpl.h"
#include "ConfigurationReader.h"
#include "Output.h"
#include <cstring>
#include <string>
#include "version.h"
#include <signal.h>

#ifdef HAVE_LIBPTHREAD
#include "Synchronisation.h"
#endif

#ifdef USE_OPENPMF
#include <pmf_init.h>
#endif // USE_OPENPMF

static char rcsid[] UNUSED = "$Id: HomeFinder.cpp,v 1.12 2004/08/23 09:15:35 tom Exp $";


/**
 * @addtogroup HomeFinder
 * @{
 */

CORBA::ORB_var orb;

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
	// build name for name service
	//
    CORBA::Object_var obj;
	CosNaming::NamingContext_var nameService;
	CosNaming::Name name;
    name.length(2);
    name[0].id = CORBA::string_dup("Qedo");
    name[0].kind = CORBA::string_dup("");
	name[1].id = CORBA::string_dup("HomeFinder");
    name[1].kind = CORBA::string_dup("");
    
	//
	// unbind name in name service
	//
	try
	{
		//
		// try to get name service from config values
		//
		std::string ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );
		if( !ns.empty() )
		{
			try
			{
				obj = orb->string_to_object( ns.c_str() );
			}
			catch(...)
			{
				NORMAL_ERR2( "qassf: can't resolve NameService ", ns );
			}

			NORMAL_OUT2( "qassf: NameService is ", ns );
		}
		//
		// try to get naming service from orb
		//
		else
		{
			try
			{
				obj = orb->resolve_initial_references( "NameService" );
			}
			catch (const CORBA::ORB::InvalidName&)
			{
				NORMAL_ERR( "qassf: can't resolve NameService from ORB" );
			}

			if (CORBA::is_nil(obj.in()))
			{
				NORMAL_ERR( "qassf: NameService is a nil object reference" );
			}
		}

		try
		{
			nameService = CosNaming::NamingContext::_narrow( obj.in() );
		}
		catch (const CORBA::Exception&)
		{
			NORMAL_ERR( "qassf: NameService is not running" );
		}

		if( CORBA::is_nil(nameService.in()) )
		{
			NORMAL_ERR( "qassf: NameService is not a NamingContext object reference" );
		}

		if (!CORBA::is_nil(nameService.in()))
		{
 			nameService->unbind(name);
		}
	}
	catch (const CORBA::Exception&)
	{
		std::cerr << "..... could not unbind" << std::endl;
	}
	catch(...)
	{
		std::cerr << "..... error in signal handler" << std::endl;
	}

	orb->shutdown(false);
}

#ifdef HAVE_LIBPTHREAD

static bool signal_handler_thread_stop=false;

void*
signal_handler_thread(void *p)
{
	sigset_t sigs;
	sigemptyset (&sigs);
	sigaddset (&sigs, SIGINT);
	int sig;
	while ( !signal_handler_thread_stop)
	{
		sig = 0;
		sigwait(&sigs, &sig);
		switch(sig)
		{
			case SIGINT:
				handle_sigint(sig);
				signal_handler_thread_stop=true;
				break;
			default:
				std::cerr << "Got unexpected Signal (" << sig << ")" << std::endl;
		}
	}

	return 0;
}
#endif // HAVE_LIBPTHREAD

/**
 * the executable starts a HomeFinder
 */
int
main (int argc, char** argv)
{

	// create arguments for ORB_init
	char *orb_argv[27];
	int orb_argc=argc;
	int orb_n = 0;
	for (orb_n = 0; orb_n < argc; orb_n++)
	{
		orb_argv[orb_n] = strdup(argv[orb_n]);
	};

	// check for Host Name Resolving
	std::string resolve = Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/ResolveHostName");
	if (!resolve.compare("false"))
	{
		
		orb_argv[orb_argc] = "-ORBNoResolve";
		orb_argc++;
	};


	std::cout << "Qedo Home Finder " << QEDO_VERSION << " " << QEDO_REVISION << std::endl;

	orb = CORBA::ORB_init (orb_argc, orb_argv);
	Qedo::set_ORB(orb);

#ifdef HAVE_LIBPTHREAD
	// block SIGINT
	// Only the signal thread will handle this signal
	sigset_t sigs;
	sigset_t osigs;
	sigemptyset (&sigs);
	sigaddset (&sigs, SIGINT);
	assert(pthread_sigmask (SIG_BLOCK, &sigs, &osigs) == 0);

	// this thread will do the signal handling
	Qedo::QedoThread* signal_thread;

	signal_thread = Qedo::qedo_startDetachedThread(signal_handler_thread,0);

#else // HAVE_LIBPTHREAD
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
#else // HAVE_SIGACTION
	 signal ( SIGINT, handle_sigint );
#endif // HAVE_SIGACTION
#endif // HAVE_LIBPTHREAD


	//
	// register valuetype factories
	//
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::CookieFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/Cookie:1.0", factory);

	Qedo::HomeFinderImpl* home_finder = new Qedo::HomeFinderImpl(orb);

	try
	{
		home_finder->initialize();
	}
	catch (Qedo::HomeFinderImpl::CannotInitialize&)
	{
		std::cerr << "Cannot initialize Home Finder... exiting." << std::endl;
		orb->destroy();
		exit (1);
	}

	NORMAL_OUT ("Qedo Home Finder is up and running ...")
	orb->run();

#ifdef HAVE_LIBPTHREAD
	// It is not sure, that only SIGINT will break the orb/run
	// so we have to terminate the signal thread here also
	signal_handler_thread_stop = true;
	signal_thread->stop();
	signal_thread->join();
#endif // HAVE_LIBPTHREAD
        orb->destroy();
	return 0;
}

/** @} */
