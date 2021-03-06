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
#include <cstring>
#include <string>
#include "version.h"

static char rcsid[] UNUSED = "$Id: cs.cpp,v 1.16 2003/08/06 14:32:14 stoinski Exp $";


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
	usage_message += " [--debug] --csa_ref component_server_activator_object_reference";
	NORMAL_ERR (usage_message);
}


/**
 * starts the server for the object
 */
int
main (int argc, char** argv)
{
	NORMAL_OUT2 ("Qedo Component Server ", QEDO_VERSION);

	// Check for --debug switch and check and read object reference of Component Server Activator
	bool debug_mode = false;
	bool ref_supplied = false;
	bool qos_enabled = false;

	CORBA::String_var csa_string_ref;

	for (int i = 1; i < argc; i++)
	{
		if (! strcmp (argv[i], "--debug"))
		{
			debug_mode = true;
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
		DEBUG_OUT ( "ComponentServer: Running in debug mode");
		DEBUG_OUT ( "ComponentServer: Please press a key when attached to process and breakpoints are set" );
		getchar();
	}

	//
	// initialize ORB
	//
	Qedo::ORBInitializerImpl initializer(qos_enabled);
	CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

	Qedo::ComponentServerImpl* component_server = new Qedo::ComponentServerImpl (orb, csa_string_ref, initializer.slot_id());

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

	orb->run();

	orb->destroy();

	component_server->_remove_ref();

	DEBUG_OUT  ("#######################################################");

	if (Qedo::GlobalObjectManagement::native_object_count_
		|| Qedo::GlobalObjectManagement::CORBA_object_count_
		|| Qedo::GlobalObjectManagement::CORBA_local_object_count_)
	{
		DEBUG_OUT  ("# MEMORY LEAKS DETECTED!!!");
		if (Qedo::GlobalObjectManagement::native_object_count_)
		{
			DEBUG_OUT2 ("# Number of still running native objects      : ", Qedo::GlobalObjectManagement::native_object_count_);
		}
		if (Qedo::GlobalObjectManagement::CORBA_object_count_)
		{
			DEBUG_OUT2 ("# Number of still running CORBA objects        : ", Qedo::GlobalObjectManagement::CORBA_object_count_);
		}
		if (Qedo::GlobalObjectManagement::CORBA_local_object_count_)
		{
			DEBUG_OUT2 ("# Number of still running CORBA local objects : ", Qedo::GlobalObjectManagement::CORBA_local_object_count_);
		}
	}
	else
	{
		DEBUG_OUT  ("# All objects destroyed");
	}
	DEBUG_OUT2 ("# Number of constructed native objects        : ", Qedo::GlobalObjectManagement::native_object_instantiation_count_ );
	DEBUG_OUT2 ("# Number of constructed CORBA objects         : ", Qedo::GlobalObjectManagement::CORBA_object_instantiation_count_ );
	DEBUG_OUT2 ("# Number of constructed CORBA local objects   : ", Qedo::GlobalObjectManagement::CORBA_local_object_instantiation_count_ );
	DEBUG_OUT  ("#######################################################");

	return 0;
}

/** @} */
