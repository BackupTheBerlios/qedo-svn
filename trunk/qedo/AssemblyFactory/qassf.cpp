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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "AssemblyFactory.h"
#include "Output.h"
#include "ConfigurationReader.h"
#include "version.h"
#include <signal.h>


#ifdef HAVE_LIBPTHREAD
#include "Synchronisation.h"
#endif


static char rcsid[] UNUSED = "$Id: qassf.cpp,v 1.24 2004/08/23 09:13:21 tom Exp $";


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
 * start the server for the assembly factory object
 */
int
main (int argc, char** argv)
{
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
#else
	signal ( SIGINT, handle_sigint );
#endif

#endif // HAVE_LIBPTHREAD
	std::cout << "Qedo Assembly Factory " << QEDO_VERSION << std::endl;

	Qedo::debug_output = false;
	//
	// Resolve config values from config file
	//
	if ( Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/VerboseOutput") == "true")
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

	//
	// get the qedo dir
	//
	Qedo::g_qedo_dir = Qedo::getEnvironment( "QEDO" );
	if(Qedo::g_qedo_dir == "")
	{
	    std::cout << "Missing Environment Variable QEDO" << std::endl;
	    Qedo::g_qedo_dir = Qedo::getCurrentDirectory();
	}
	std::cout << "..... Qedo directory is " << Qedo::g_qedo_dir << std::endl;

	//
	// init ORB
	//
	orb = CORBA::ORB_init (orb_argc, orb_argv);

	//
	// register valuetype factories
	//
	CORBA::ValueFactoryBase* factory;
	factory = new Qedo::CookieFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/Cookie:1.0", factory);
	CORBA::ValueFactoryBase* factory1;
	factory1 = new Qedo::ConfigValueFactory_impl();
    orb->register_value_factory("IDL:omg.org/Components/ConfigValue:1.0", factory1);

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
	orb->run();

#ifdef HAVE_LIBPTHREAD
	// It is not sure, that only SIGINT will break the orb/run
	// so we have to terminate the signal thread here also
	signal_handler_thread_stop = true;
	signal_thread->stop();
	signal_thread->join();
#endif // HAVE_LIBPTHREAD

    orb->unregister_value_factory("IDL:omg.org/Components/Cookie:1.0");
    orb->unregister_value_factory("IDL:omg.org/Components/ConfigValue:1.0");
	 delete assembly_factory;
	 delete factory1;
	 delete factory;
	return 0;
}

/** @} */
