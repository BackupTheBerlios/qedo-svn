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
#include "Output.h"
#include <cstring>
#include <string>
#include "version.h"
#include <signal.h>

#ifdef HAVE_LIBPTHREAD
#include "Synchronisation.h"
#endif

static char rcsid[] UNUSED = "$Id: HomeFinder.cpp,v 1.8 2003/11/12 14:49:35 boehme Exp $";


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

	std::cout << "Qedo Home Finder " << QEDO_VERSION << std::endl;

	orb = CORBA::ORB_init (argc, argv);

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

	return 0;
}

/** @} */
