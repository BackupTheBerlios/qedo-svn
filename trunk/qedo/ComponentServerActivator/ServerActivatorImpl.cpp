/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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

static char rcsid[] = "$Id: ServerActivatorImpl.cpp,v 1.3 2002/12/03 07:48:58 stoinski Exp $";

#include "ServerActivatorImpl.h"
#include <CosNaming.h>

#include <iostream>
#ifdef _WIN32
#include <strstream>
#include <process.h>
#else
#include <unistd.h>
#include <sstream>
#endif

using namespace std;

namespace Qedo {

ServerActivatorImpl::ServerActivatorImpl (CORBA::ORB_ptr orb, bool debug_mode)
: orb_ (CORBA::ORB::_duplicate (orb)),
  debug_mode_ (debug_mode)
{
}


ServerActivatorImpl::~ServerActivatorImpl()
{
}


void
ServerActivatorImpl::initialize()
{
	try
	{
		CORBA::Object_var root_poa_obj = orb_->resolve_initial_references ("RootPOA");
		root_poa_ = PortableServer::POA::_narrow (root_poa_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		cerr << "ServerActivatorImpl: Fatal error - no root POA available." << endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		cerr << "ServerActivatorImpl: Fatal error - cannot narrow root POA." << endl;
		throw CannotInitialize();
	}

	root_poa_manager_ = root_poa_->the_POAManager();

	root_poa_manager_->activate();

	CosNaming::NamingContext_var ns;

	// Now try to bind with the Name Service
	try
	{
		CORBA::Object_var ns_obj = orb_->resolve_initial_references ("NameService");
		ns = CosNaming::NamingContext::_narrow (ns_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		cerr << "ServerActivatorImpl: Name Service not found" << endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		cerr << "ServerActivatorImpl: Cannot narrow object reference of Name Service" << endl;
		throw CannotInitialize();
	}

	if (CORBA::is_nil (ns))
	{
		cerr << "ServerActivatorImpl: Name Service is nil" << endl;
		throw CannotInitialize();
	}

	// Create the Qedo and Activators naming context
	CosNaming::Name current_name;
	current_name.length (1);
	current_name[0].id = CORBA::string_dup ("Qedo");
	current_name[0].kind = CORBA::string_dup ("");
	try
	{
		ns->bind_new_context (current_name);
	}
	catch (CosNaming::NamingContext::AlreadyBound&)
	{
		// Ignore this exception
	}
	catch (CORBA::SystemException&)
	{
		cerr << "ServerActivatorImpl: CORBA system exception during binding context 'Qedo'" << endl;
		throw CannotInitialize();
	}

	current_name.length(2);
	current_name[1].id = CORBA::string_dup ("Activators");
	current_name[1].kind = CORBA::string_dup ("");

	try
	{
		ns->bind_new_context (current_name);
	}
	catch (CosNaming::NamingContext::AlreadyBound&)
	{
		// Ignore this exception
	}
	catch (CORBA::SystemException&)
	{
		cerr << "ServerActivatorImpl: CORBA system exception during binding context 'Activators'" << endl;
		throw CannotInitialize();
	}

	// Now bind this Component Server Activator with the Name Service, use the name Qedo/Activators/<hostname>
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		cerr << "ServerActivatorImpl: Cannot determine my hostname" << endl;
		throw CannotInitialize();
	}

	cout << "ServerActivatorImpl: Binding Component Server Activator under Qedo/Activators/" << hostname << endl;

	current_name.length (3);
	current_name[2].id = CORBA::string_dup (hostname);
	current_name[2].kind = CORBA::string_dup ("");

	CORBA::Object_var my_ref = this->_this();

	try
	{
		ns->bind (current_name, my_ref);
	}
	catch (CosNaming::NamingContext::AlreadyBound&)
	{
		try
		{
			ns->rebind (current_name, my_ref);
		}
		catch (CosNaming::NamingContext::InvalidName&)
		{
			cerr << "ServerActivatorImpl: Name Service complains about an invalid name" << endl;
			throw CannotInitialize();
		}
		catch (CORBA::SystemException&)
		{
			cerr << "ServerActivatorImpl: CORBA system exception in rebind()" << endl;
			throw CannotInitialize();
		}
	}
	catch (CosNaming::NamingContext::InvalidName&)
	{
		cerr << "ServerActivatorImpl: Name Service complains about an invalid name" << endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		cerr << "ServerActivatorImpl: CORBA system exception during bind()" << endl;
		throw CannotInitialize();
	}

#ifdef HAVE_JTC
#else
#if _WIN32
	// Create an event handle to be used for the notification from the created component server
	event_handle_ = CreateEvent (NULL, TRUE /*auto-reset*/, FALSE /*initial: non-signaled*/, "QEDO_NOTIFY_EVENT");
	    
	if (event_handle_ == NULL)
	{
		cerr << "ServerActivatorImpl: ServerActivatorImpl: Cannot create event object for notify_component_server() operation"<< endl;
		throw CannotInitialize();
	}
#endif
#endif
}


Components::Deployment::ComponentServer_ptr 
ServerActivatorImpl::create_component_server (const ::Components::ConfigValues& config)
throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException)
{
	cout << "ServerActivatorImpl: create_component_server() called" << endl;

#ifdef HAVE_JTC
	JTCSynchronized sync(monitor);
#endif
	CORBA::String_var my_string_ref;


	try
	{
		my_string_ref = orb_->object_to_string (this->_this());
	}
	catch (CORBA::SystemException&)
	{
		cerr << "ServerActivatorImpl: Cannot stringify my object reference" << endl;
		throw Components::CreateFailure();
	}

#ifdef _WIN32
	int component_server_pid;

	if (debug_mode_)
	{
		component_server_pid = _spawnl(_P_NOWAIT, "cs.exe", "cs.exe", "--debug", 
			"--csa_ref", my_string_ref, NULL);
	}
	else
	{
		component_server_pid = _spawnl(_P_NOWAIT, "cs.exe", "cs.exe", 
			"--csa_ref", my_string_ref, NULL);
	}

	if (component_server_pid < 0)
	{
		cerr << "ServerActivatorImpl: Cannot spawn Component Server process" << endl;
		cerr << "ServerActivatorImpl: " << strerror(errno) << endl;
		throw Components::CreateFailure();
	}

#else

	switch (fork())
	{
		case 0 : /* child process */
			if (debug_mode_)
			{
				execlp("cs", "cs", "--csa_ref", static_cast<const char*>(my_string_ref), "--debug", 0);
			}
			else
			{
				execlp("cs", "cs", "--csa_ref", static_cast<const char*>(my_string_ref), 0);
			}
			break;
		default : /* parent process */
			break;
		case -1 : /* error in fork */
			{
				cerr << "ServerActivatorImpl: Cannot spawn Component Server process" << endl;
				cerr << "ServerActivatorImpl: " << strerror(errno) << endl;
				throw Components::CreateFailure();
			}
			break;
	}

#endif

#if HAVE_JTC
	monitor.wait();
#else
#ifdef _WIN32
	// Now wait for the component server to call notify_component_server() on me
	WaitForMultipleObjects(1, &event_handle_, TRUE, INFINITE /*wait for ever*/);
#endif
#endif

	if (CORBA::is_nil (last_created_component_server_))
	{
		// cerr << "ServerActivatorImpl: Component Server has not been created" << endl;
		throw Components::CreateFailure();
	}

	component_servers_.push_back(Components::Deployment::ComponentServer::_duplicate(last_created_component_server_));

	return Components::Deployment::ComponentServer::_duplicate(last_created_component_server_);
}

  
void 
ServerActivatorImpl::remove_component_server (::Components::Deployment::ComponentServer_ptr server)
throw (Components::RemoveFailure, CORBA::SystemException)
{
	// TODO
}


Components::Deployment::ComponentServers* 
ServerActivatorImpl::get_component_servers()
throw (CORBA::SystemException)
{
	Components::Deployment::ComponentServers_var servers = new Components::Deployment::ComponentServers();
	servers->length (component_servers_.size());

	for (unsigned int i = 0; i < component_servers_.size(); i++)
	{
        servers[i] = component_servers_[i];
	}

	return servers._retn();
}


void 
ServerActivatorImpl::notify_component_server (Components::Deployment::ComponentServer_ptr server)
throw (CORBA::SystemException)
{
	cout << "ServerActivatorImpl: notify_component_server() called" << endl;

#ifdef HAVE_JTC
	JTCSynchronized sync(monitor);
#endif

	last_created_component_server_ = Components::Deployment::ComponentServer::_duplicate(server);

	// Signal that the callback function has been called by the Component Server,
	// so we can return the IOR to the client
#ifdef HAVE_JTC
	monitor.notify();
#else
#ifdef _WIN32
	SetEvent(event_handle_);
#endif
#endif
}

} // namespace Qedo
