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
#include <fstream>
#include "ServerActivatorImpl.h"
#include "ConfigurationReader.h"

#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif

static char rcsid[] UNUSED = "$Id: ServerActivatorImpl.cpp,v 1.39 2004/04/26 13:30:58 neubauer Exp $";

#ifdef _WIN32
//#include <strstream>
#include <process.h>
#else
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <signal.h>
#endif


namespace Qedo {


	ServerActivatorImpl::ServerActivatorImpl (CORBA::ORB_ptr orb, bool debug_mode, bool qos_mode, bool terminal_enabled, bool global_context_used, std::string global_context, bool verbose_mode )
: debug_mode_ (debug_mode),
  enable_qos_ (qos_mode),
  enable_terminal_ (terminal_enabled),
  verbose_mode_ (verbose_mode),
  global_context_used_ (global_context_used),
  global_context_ (global_context),
  cs_activation_cond_ ("QEDO_ACTIVATOR_SIGNAL"),
  orb_ (CORBA::ORB::_duplicate (orb))
{
	std::string delay (Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/ComponentServerKillDelay"));

	if (delay != "")
	{
		cs_kill_delay_  = atol (delay.c_str());
	}

	if (! cs_kill_delay_)
	{
		cs_kill_delay_ = 10000;
	}
}

unsigned long ServerActivatorImpl::cs_kill_delay_=0;

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

	//
	// register in name service
	//

	CosNaming::NamingContext_var nameService;

	//
	// try to get naming service from config values
	//
	CORBA::Object_var obj;
	std::string ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );
	if( !ns.empty() )
	{
		try
		{
			obj = orb_->string_to_object( ns.c_str() );
		}
		catch(...)
		{
			std::cerr << "ServerActivatorImpl: can't resolve NameService " << ns << std::endl;
			throw CannotInitialize();
		}

		std::cout <<  "ServerActivatorImpl: NameService is " <<  ns << std::endl;
	}
	//
	// try to get naming service from orb
	//
	else
	{
		try
		{
			obj = orb_->resolve_initial_references( "NameService" );
		}
		catch (const CORBA::ORB::InvalidName&)
		{
			std::cerr << "ServerActivatorImpl: can't resolve NameService" << std::endl;
			throw CannotInitialize();
		}

		if (CORBA::is_nil(obj.in()))
		{
			std::cerr << "ServerActivatorImpl: NameService is a nil object reference" << std::endl;
			throw CannotInitialize();
		}
	}

	try
	{
		nameService = CosNaming::NamingContext::_narrow( obj.in() );
	}
	catch (const CORBA::Exception&)
	{
		std::cerr << "ServerActivatorImpl: NameService is not running" << std::endl;
		throw CannotInitialize();
	}

	if( CORBA::is_nil(nameService.in()) )
	{
		std::cerr << "NameService is not a NamingContext object reference" << std::endl;
		throw CannotInitialize();
	}

	CORBA::ULong context_offset;
	if (global_context_used_)
	{
		context_offset = 1;
	} else 
	{
		context_offset= 0;
	};


	// Create the Qedo and Activators naming context
	CosNaming::Name current_name;

	current_name.length (1);
	if (global_context_used_)
	{
		current_name[0].id = CORBA::string_dup(global_context_.c_str());
		current_name[0].kind = CORBA::string_dup("");
		try 
		{
			nameService->bind_new_context (current_name);
		}
		catch (CosNaming::NamingContext::AlreadyBound&)
		{
			// ignore this exception
		}
		catch (CORBA::SystemException&)
		{
			std::cerr << "ServerActivatorImpl: CORBA system exception during binding context 'Qedo'" << std::endl;
			throw CannotInitialize();
		}

	} 
	current_name.length (1 + context_offset);
	current_name[0 + context_offset].id = CORBA::string_dup ("Qedo");
	current_name[0 + context_offset].kind = CORBA::string_dup ("");
	try
	{
		nameService->bind_new_context (current_name);
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

	current_name.length(2 + context_offset);
	current_name[1+context_offset].id = CORBA::string_dup ("Activators");
	current_name[1+context_offset].kind = CORBA::string_dup ("");

	try
	{
		nameService->bind_new_context (current_name);
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

	current_name.length (3 + context_offset);
	current_name[2+context_offset].id = CORBA::string_dup (hostname);
	current_name[2+context_offset].kind = CORBA::string_dup ("");

	CORBA::Object_var my_ref = this->_this();

	try
	{
		nameService->bind (current_name, my_ref);
	}
	catch (CosNaming::NamingContext::AlreadyBound&)
	{
		try
		{
			nameService->rebind (current_name, my_ref);
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
	QedoLock lock (cs_activation_mutex_);
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
	char *args[17];
	//const char* prog;
	std::string prog;
	int args_nr=0;

	if (enable_terminal_)
	{
		#define INFO_BUFFER_SIZE MAX_PATH+4
		TCHAR infoBuf[INFO_BUFFER_SIZE];
		DWORD bufCharCount = INFO_BUFFER_SIZE;
		GetWindowsDirectory( infoBuf, INFO_BUFFER_SIZE );
		prog = std::string( infoBuf ) + "/system32/cmd.exe";
		//prog = "c:/windows/system32/cmd.exe";
		args[args_nr++] = "cmd";
		args[args_nr++] = "/c";
		args[args_nr++] = "start";
		args[args_nr++] = "qcs.exe";
	}
	else
	{
		prog = "qcs.exe";
		args[args_nr++] = "qcs.exe";
	}

	if (debug_mode_)
	{
		args[args_nr++] = "--debug";
	}

	if (verbose_mode_)
	{
		args[args_nr++] = "--verbose";
	}

	args[args_nr++] = "--csa_ref";
	args[args_nr++] = my_string_ref.inout();

	args[args_nr] = 0;

	component_server_pid = _spawnv(_P_NOWAIT, prog.c_str(), args);

	if (component_server_pid < 0)
	{
		std::cerr << "ServerActivatorImpl: Cannot spawn Component Server process" << std::endl;
		std::cerr << "ServerActivatorImpl: " << strerror(errno) << std::endl;
		throw Components::CreateFailure();
	}

#else

	pid_t component_server_pid;

	switch (component_server_pid = fork())
	{
		case 0 : /* child process */
		{
			char *args[17];
			const char* prog;
			int args_nr=0;


			if (enable_terminal_)
			{
				args[args_nr++] = "xterm";
				args[args_nr++] = "-e";
				args[args_nr++] = "qcs.sh";
				prog = "xterm";
			}
			else
			{
				args[args_nr++] = "qcs";
				prog = "qcs";
			}

			if (debug_mode_)
			{
				args[args_nr++] = "--debug";
			}

			if (verbose_mode_)
			{
				args[args_nr++] = "--verbose";
			}

			args[args_nr++] = "--csa_ref";
			args[args_nr++] = my_string_ref.inout();

			args[args_nr] = 0;

			long err = execvp (prog,args);
			if (err == -1) 
			{
				std::cerr << "ServerActivatorImpl: execvp() for component server failed" << std::endl;
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

	cs_activation_cond_.wait (cs_activation_mutex_);

//#endif

	if (CORBA::is_nil (last_created_component_server_))
	{
		// cerr << "ServerActivatorImpl: Component Server has not been created" << endl;
		throw Components::CreateFailure();
	}

	ComponentServerEntry e;
	e.server = Components::Deployment::ComponentServer::_duplicate(last_created_component_server_);
	e.pid = component_server_pid;

	Qedo::QedoLock l(component_servers_mutex_);

	component_servers_.push_back(e);

	return Components::Deployment::ComponentServer::_duplicate(last_created_component_server_);
}

  
void 
ServerActivatorImpl::remove_component_server (::Components::Deployment::ComponentServer_ptr server)
throw (Components::RemoveFailure, CORBA::SystemException)
{
	// Test whether this component server is known to us
	ComponentServerVector::iterator cs_iter;

	component_servers_mutex_.lock_object();

	for (cs_iter = component_servers_.begin(); cs_iter != component_servers_.end(); cs_iter++)
	{
		if ((*cs_iter).server->_is_equivalent (server))
			break;
	}

	if (cs_iter == component_servers_.end())
	{
		std::cerr << "ServerActivatorImpl: remove_component_server(): Unknown component server supplied" << std::endl;
		component_servers_mutex_.unlock_object();
		throw Components::RemoveFailure();
	}

	// the struct will be freed in the thread
	
	RemoveStruct *r = new RemoveStruct((*cs_iter));

	component_servers_mutex_.unlock_object();

	Qedo::QedoThread* thread;

	thread = Qedo::qedo_startDetachedThread(timer_thread,r);

	try
	{
		(*cs_iter).server->remove();
	}
	catch (CORBA::SystemException&)
	{
	}

	r->mutex.lock_object();
	if (r->locked_by_other)
	{
		r->join_cond.signal();
	}
	else
	{
		r->locked_by_other = true;
		r->cond.signal();
		r->join_cond.wait(r->mutex);
	}

	r->mutex.unlock_object();

	thread->join();

	delete r;

	delete thread;
}


Components::Deployment::ComponentServers* 
ServerActivatorImpl::get_component_servers()
throw (CORBA::SystemException)
{
	Components::Deployment::ComponentServers_var servers = new Components::Deployment::ComponentServers();
	Qedo::QedoLock l(component_servers_mutex_);
	servers->length (component_servers_.size());

	for (unsigned int i = 0; i < component_servers_.size(); i++)
	{
        servers.inout()[i] = component_servers_[i].server;
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
	QedoLock lock (cs_activation_mutex_);
	cs_activation_cond_.signal();
}


void 
ServerActivatorImpl::notify_component_server_remove (Qedo_Components::Deployment::ComponentServer_ptr server)
throw(CORBA::SystemException)
{
	// Test whether this component server is known to us
	ComponentServerVector::iterator cs_iter;

	Qedo::QedoLock l(component_servers_mutex_);
	for (cs_iter = component_servers_.begin(); cs_iter != component_servers_.end(); cs_iter++)
	{
		if ((*cs_iter).server->_is_equivalent (server))
			break;
	}

	if (cs_iter == component_servers_.end())
	{
		std::cerr << "ServerActivatorImpl: Unknown component server notified for removal" << std::endl;
		return;
	}

}

#ifndef _WIN32
void 
ServerActivatorImpl::remove_by_pid (pid_t server)
{
	std::cout << "ServerActivatorImpl: remove_by_pid() called" << std::endl;

	// Test whether this component server is known to us
	ComponentServerVector::iterator cs_iter;

	Qedo::QedoLock l(component_servers_mutex_);

	for (cs_iter = component_servers_.begin(); cs_iter != component_servers_.end(); cs_iter++)
	{
		if ((*cs_iter).pid == server)
			break;
	}

	if (cs_iter == component_servers_.end())
	{
		std::cerr << "ServerActivatorImpl: remove_by_pid(): Unknown component server supplied" << std::endl;
	}
	else
	{
		component_servers_.erase (cs_iter);
	}
}
#endif

ServerActivatorImpl::RemoveStruct::RemoveStruct(const ComponentServerEntry& e)
	: entry(e)
{
	locked_by_other = false;
}

void *
ServerActivatorImpl::timer_thread(void *data)
{
	RemoveStruct* s = static_cast<RemoveStruct*>(data);

	s->mutex.lock_object();

	if( !s->cond.wait_timed(s->mutex,cs_kill_delay_) )
	{
		// got timeout
		std::cout << "ServerActivatorImpl: Component Server not responding, killing it..." << std::endl;

#ifdef _WIN32
		if (! TerminateProcess ((HANDLE)s->entry.pid, 0))
		{
			std::cerr << "ServerActivatorImpl: Cannot terminate Component Server process" << std::endl;
			std::cerr << "ServerActivatorImpl: Error was: " << GetLastError() << std::endl;
		}
#else
		if ( kill(s->entry.pid,SIGKILL) == -1 )
		{
			std::cerr << "ServerActivatorImpl: Cannot kill Component Server process" << std::endl;
			std::cerr << "ServerActivatorImpl: " << strerror(errno) << std::endl;
		}
#endif

	}

	if ( s->locked_by_other)
	{
		s->join_cond.signal();
	}
	else
	{
		s->locked_by_other = true;
		s->join_cond.wait (s->mutex);
	}

	s->mutex.unlock_object();

	return 0;
}
} // namespace Qedo
