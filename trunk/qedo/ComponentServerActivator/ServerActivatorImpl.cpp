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

#include <iostream>
#include "fstream"
#include "ServerActivatorImpl.h"
#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif

static char rcsid[] UNUSED = "$Id: ServerActivatorImpl.cpp,v 1.21 2003/09/29 14:21:30 stoinski Exp $";

#ifdef _WIN32
//#include <strstream>
#include <process.h>
#else
#include <unistd.h>
#include <sstream>
#endif


namespace Qedo {

	
ServerActivatorImpl::ServerActivatorImpl (CORBA::ORB_ptr orb, bool debug_mode, bool qos_mode)
: orb_ (CORBA::ORB::_duplicate (orb)),
  debug_mode_ (debug_mode),
  enable_qos_ (qos_mode),
  component_server_activation_ ("QEDO_ACTIVATOR_SIGNAL")
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
		std::cerr << "ServerActivatorImpl: Fatal error - no root POA available." << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ServerActivatorImpl: Fatal error - cannot narrow root POA." << std::endl;
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
		std::cerr << "ServerActivatorImpl: Name Service not found" << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ServerActivatorImpl: Cannot narrow object reference of Name Service" << std::endl;
		throw CannotInitialize();
	}

	if (CORBA::is_nil (ns))
	{
		std::cerr << "ServerActivatorImpl: Name Service is nil" << std::endl;
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
		std::cerr << "ServerActivatorImpl: CORBA system exception during binding context 'Qedo'" << std::endl;
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
		std::cerr << "ServerActivatorImpl: CORBA system exception during binding context 'Activators'" << std::endl;
		throw CannotInitialize();
	}

	// Now bind this Component Server Activator with the Name Service, use the name Qedo/Activators/<hostname>
	char hostname[256];
	if (gethostname (hostname, 256))
	{
		std::cerr << "ServerActivatorImpl: Cannot determine my hostname" << std::endl;
		throw CannotInitialize();
	}

	std::cout << "ServerActivatorImpl: Binding Component Server Activator under Qedo/Activators/" << hostname << std::endl;

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
			std::cerr << "ServerActivatorImpl: Name Service complains about an invalid name" << std::endl;
			throw CannotInitialize();
		}
		catch (CORBA::SystemException&)
		{
			std::cerr << "ServerActivatorImpl: CORBA system exception in rebind()" << std::endl;
			throw CannotInitialize();
		}
	}
	catch (CosNaming::NamingContext::InvalidName&)
	{
		std::cerr << "ServerActivatorImpl: Name Service complains about an invalid name" << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ServerActivatorImpl: CORBA system exception during bind()" << std::endl;
		throw CannotInitialize();
	}



}


Components::Deployment::ComponentServer_ptr 
ServerActivatorImpl::create_component_server (const ::Components::ConfigValues& config)
throw (Components::CreateFailure, Components::Deployment::InvalidConfiguration, CORBA::SystemException)
{
	QedoLock lock (component_server_mutex_);
	std::cout << "ServerActivatorImpl: create_component_server() called" << std::endl;

	CORBA::String_var my_string_ref;


	try
	{
		my_string_ref = orb_->object_to_string (this->_this());
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "ServerActivatorImpl: Cannot stringify my object reference" << std::endl;
		throw Components::CreateFailure();
	}

#ifdef _WIN32
	int component_server_pid;

	if (debug_mode_)
	{
		if (enable_qos_) {
			component_server_pid = _spawnl(_P_NOWAIT, "qcs.exe", "qcs.exe", "--debug", 
				"--enable-qos", "--csa_ref", my_string_ref.in(), NULL);

		} else {
			component_server_pid = _spawnl(_P_NOWAIT, "qcs.exe", "qcs.exe", "--debug", 
				"--csa_ref", my_string_ref.in(), NULL);
		}
	}
	else
	{
		if (enable_qos_) {
			component_server_pid = _spawnl(_P_NOWAIT, "qcs.exe", "qcs.exe", 
				"--enable-qos", "--csa_ref", my_string_ref.in(), NULL);
		} else {
			component_server_pid = _spawnl(_P_NOWAIT, "qcs.exe", "qcs.exe", 
				"--csa_ref", my_string_ref.in(), NULL);
		}
	}

	if (component_server_pid < 0)
	{
		std::cerr << "ServerActivatorImpl: Cannot spawn Component Server process" << std::endl;
		std::cerr << "ServerActivatorImpl: " << strerror(errno) << std::endl;
		throw Components::CreateFailure();
	}

#else

	switch (fork())
	{
		case 0 : /* child process */
			if (debug_mode_)
			{
				long err = execlp ("qcs", "qcs", "--csa_ref", my_string_ref.in(), "--debug", 0);
			    if (err == -1) 
				{
					std::cerr << "ServerActivatorImpl: execlp() for component server failed" << std::endl;
					std::cerr << "ServerActivatorImpl: Error  was: " << strerror (errno) << std::endl;
					throw Components::CreateFailure();
				}
			}
			else
			{
				long err = execlp ("qcs", "qcs", "--csa_ref", my_string_ref.in(), 0);
			    if (err == -1) 
				{
					std::cerr << "ServerActivatorImpl: execlp() for component server failed" << std::endl;
					std::cerr << "ServerActivatorImpl: Error  was: " << strerror (errno) << std::endl;
					throw Components::CreateFailure();
				}
			}
			break;
		default : /* parent process */
			break;
		case -1 : /* error in fork */
			{
				std::cerr << "ServerActivatorImpl: Cannot spawn Component Server process" << std::endl;
				std::cerr << "ServerActivatorImpl: " << strerror(errno) << std::endl;
				throw Components::CreateFailure();
			}
			break;
	}

#endif

	component_server_activation_.wait (component_server_mutex_);

//#endif

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
	std::cout << "ServerActivatorImpl: remove_component_server() called" << std::endl;

	// Test whether this component server is known to us
	ComponentServerVector::iterator cs_iter;

	for (cs_iter = component_servers_.begin(); cs_iter != component_servers_.end(); cs_iter++)
	{
		if ((*cs_iter)->_is_equivalent (server))
			break;
	}

	if (cs_iter == component_servers_.end())
	{
		std::cerr << "ServerActivatorImpl: remove_component_server(): Unknown component server supplied" << std::endl;
		throw Components::RemoveFailure();
	}

	(*cs_iter)->remove();
}


Components::Deployment::ComponentServers* 
ServerActivatorImpl::get_component_servers()
throw (CORBA::SystemException)
{
	Components::Deployment::ComponentServers_var servers = new Components::Deployment::ComponentServers();
	servers->length (component_servers_.size());

	for (unsigned int i = 0; i < component_servers_.size(); i++)
	{
        servers.inout()[i] = component_servers_[i];
	}

	return servers._retn();
}


void 
ServerActivatorImpl::notify_component_server_create (Qedo_Components::Deployment::ComponentServer_ptr server)
throw (CORBA::SystemException)
{
	std::cout << "ServerActivatorImpl: notify_component_server() called" << std::endl;

	last_created_component_server_ = Components::Deployment::ComponentServer::_duplicate(server);

	// Signal that the callback function has been called by the Component Server,
	// so we can return the IOR to the client
	QedoLock lock (component_server_mutex_);
	component_server_activation_.signal();
}


void 
ServerActivatorImpl::notify_component_server_remove (Qedo_Components::Deployment::ComponentServer_ptr server)
throw(CORBA::SystemException)
{
	// Test whether this component server is known to us
	ComponentServerVector::iterator cs_iter;

	for (cs_iter = component_servers_.begin(); cs_iter != component_servers_.end(); cs_iter++)
	{
		if ((*cs_iter)->_is_equivalent (server))
			break;
	}

	if (cs_iter == component_servers_.end())
	{
		std::cerr << "ServerActivatorImpl: Unknown component server notified for removal" << std::endl;
		return;
	}

	component_servers_.erase (cs_iter);
}


} // namespace Qedo
