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

#include "ComponentServerImpl.h"
#include "Synchronisation.h"
#include "ORBInitializerImpl.h"
#include "Output.h"
#ifndef _QEDO_NO_STREAMS
#include "TCPTransportEndpointFactory.h"
#include "UDPTransportEndpointFactory.h"
#endif
#include "ConfigurationReader.h"

#include <cstring>
#include <string>

#include "version.h"

#ifndef _QEDO_NO_QOS
#include "ServerInterceptorDispatcher.h"
#include "ClientInterceptorDispatcher.h"
#include "ServantInterceptorDispatcher.h"
#include "StubInterceptorDispatcher.h"
#endif

static char rcsid[] UNUSED = "$Id: qcs.cpp,v 1.37 2004/09/27 12:48:26 tom Exp $";


/**
 * @addtogroup ComponentServer
 * @{
 */


void
usage (const char* prog_name)
{
	std::string usage_message;

	usage_message = "usage: ";
	usage_message += prog_name;
	usage_message += " [--debug] [--verbose] --csa_ref component_server_activator_object_reference";
	NORMAL_ERR (usage_message);
}


/**
 * starts the server for the object
 */
int
main (int argc, char** argv)
{
	NORMAL_OUT2 ("Qedo Component Server ", QEDO_VERSION);

	bool debug_mode = false;
	bool ref_supplied = false;
	bool qos_enabled = false;

	Qedo::debug_output = false;

	// Resolve config values from config file
	if ( Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/Debug/DebugMode") == "true")
	{
		debug_mode = true;
	}

	if (Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/VerboseOutput") == "true")
	{
		Qedo::debug_output = true;
	}

	if (Qedo::ConfigurationReader::instance()->lookup_config_value ("/QoS/EnableQoS") == "true")
	{
		qos_enabled = true;
	}

	CORBA::String_var csa_string_ref;

	for (int i = 1; i < argc; i++)
	{
		if (! strcmp (argv[i], "--debug"))
		{
			debug_mode = true;
		}

		if (! strcmp (argv[i], "--verbose"))
		{
			Qedo::debug_output = true;
		}

		if (! strcmp (argv[i], "--csa_ref"))
		{
			if (i+1 == argc)
			{
				NORMAL_ERR ("ComponentServer: --csa_ref switch misses argument");
				usage (argv[0]);
				exit (1);
			}

			csa_string_ref = CORBA::string_dup (argv[i+1]);
			ref_supplied = true;
		}

		if (! strcmp (argv[i], "--enable-qos"))
		{
			qos_enabled = true;
		}

	}

	if (! ref_supplied)
	{
		NORMAL_ERR ("ComponentServer: No object reference for Component Server Activator supplied");
		usage (argv[0]);
		exit (1);
	}

	if (debug_mode)
	{
		NORMAL_OUT ( "ComponentServer: Running in debug mode");
		NORMAL_OUT ( "ComponentServer: Please press a key when attached to process and breakpoints are set" );
		getchar();
	}

	if (qos_enabled)
	{
		DEBUG_OUT ("ComponentServer: Running in QoS mode");
	} else
	{
		DEBUG_OUT ("ComponentServer: Running in non-QoS mode");
	}

	//
	// initialize ORB
	//
	Qedo::ORBInitializerImpl initializer(qos_enabled);

#ifndef _QEDO_NO_QOS
	//
	// create dispatcher if QoS is enabled
	//

	//Portable Interceptors
	Qedo::ServerInterceptorDispatcher* server_dispatcher;
	Qedo::ClientInterceptorDispatcher* client_dispatcher;
	// Servant Dispatcher
	Qedo::ServantInterceptorDispatcher* servant_dispatcher;
	// Stub Dispatcher
	Qedo::StubInterceptorDispatcher* stub_dispatcher;

	if (qos_enabled)
	{
		// create dispatchers
		server_dispatcher = new Qedo::ServerInterceptorDispatcher();
		server_dispatcher -> _add_ref();
		client_dispatcher = new Qedo::ClientInterceptorDispatcher();
		client_dispatcher -> _add_ref();

		servant_dispatcher = new Qedo::ServantInterceptorDispatcher();
		servant_dispatcher -> _add_ref();
		stub_dispatcher = new Qedo::StubInterceptorDispatcher();
		stub_dispatcher -> _add_ref();

		// register interceptors before ORB_init
		initializer.set_server_dispatcher (
			PortableInterceptor::ServerRequestInterceptor::_narrow (server_dispatcher ) );
		initializer.set_client_dispatcher (
			PortableInterceptor::ClientRequestInterceptor::_narrow (client_dispatcher ) );

	} // if qos_enabled
#endif
	// create arguments for ORB_init
	char *orb_argv[27];
	int orb_argc=argc;
	int orb_n = 0;
	for (orb_n = 0; orb_n < argc; orb_n++)
	{
		orb_argv[orb_n] = strdup(argv[orb_n]);
		//hack for debug
		std::cout << argv[orb_n] << std::endl;
	};

	// check for Host Name Resolving
	std::string resolve = Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/ResolveHostName");
	if (!resolve.compare("false"))
	{

		orb_argv[orb_argc] = "-ORBNoResolve";
		orb_argc++;
	};

	CORBA::ORB_var orb = CORBA::ORB_init (orb_argc, orb_argv);

	Qedo::ComponentServerImpl* component_server = new Qedo::ComponentServerImpl (orb, csa_string_ref, initializer.slot_id());

#ifndef _QEDO_NO_QOS
	if (qos_enabled)
	{
		component_server -> set_server_dispatcher (
			Components::Extension::ServerInterceptorRegistration::_narrow(server_dispatcher));
		component_server -> set_client_dispatcher (
			Components::Extension::ClientInterceptorRegistration::_narrow(client_dispatcher));
		component_server -> set_servant_dispatcher (
			Components::Extension::ServantInterceptorRegistration::_narrow(servant_dispatcher));
		component_server -> set_stub_dispatcher (
			Components::Extension::StubInterceptorRegistration::_narrow(stub_dispatcher));

		server_dispatcher -> set_component_server ( component_server );
		client_dispatcher -> set_component_server ( component_server );

		servant_dispatcher -> set_component_server ( component_server );
		stub_dispatcher -> set_component_server ( component_server );

		// set cdr
		server_dispatcher -> init_cdr ();
		client_dispatcher -> init_cdr();
	}
#endif
	try
	{
		component_server->initialize();
	}
	catch (Qedo::ComponentServerImpl::CannotInitialize&)
	{
		NORMAL_ERR ("Cannot initialize Component Server... exiting.");
		orb->destroy();
		exit (1);
	}

#ifndef _QEDO_NO_STREAMS
        // Register the transport factories
		Qedo::UDPTransportEndpointFactory* udp_factory = new Qedo::UDPTransportEndpointFactory();
		udp_factory->_remove_ref();
        Qedo::TCPTransportEndpointFactory* tcp_factory = new Qedo::TCPTransportEndpointFactory();
        tcp_factory->_remove_ref();

#ifdef _WIN32
        // Initialize the Windows Socket Environment
        WSADATA winsock_data;
        if (WSAStartup( 0x0102 /*Version 1.2*/, &winsock_data) != 0)
        {
                NORMAL_ERR ("ComponentServer: Cannot initialize Windows Socket Environment");
                orb->destroy();
                exit (1);
        }
#endif
#endif

	orb->run();

#ifndef _QEDO_NO_STREAMS
        // Clear transport registry
        Qedo::TransportRegistry::clear_registry();
                                                                                                                          
#ifdef _WIN32
        // Clear Windows Socket Environment
        if (WSACleanup() != 0)
        {
                NORMAL_ERR ("ComponentServer: Cannot clean up Windows Socket Environment");
        }
#endif
#endif

	orb->destroy();

	component_server->_remove_ref();

	Qedo::GlobalObjectManagement::report();

	return 0;
}

/** @} */
