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

#include "ContainerInterfaceImpl.h"
#include "ComponentServerImpl.h"
#include "ConfigurationReader.h"

#ifndef _QEDO_NO_DB
#include "DTMReader.h"
#include "EntityHomeServant.h"
#endif

#include "SessionHomeServant.h"
#ifndef _QEDO_NO_QOS
#include "ExtensionHomeServant.h"
#endif
#include "Output.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <dlfcn.h>
#endif

static char rcsid [] UNUSED = "$Id: ContainerInterfaceImpl.cpp,v 1.60 2004/07/16 11:21:23 tom Exp $";


namespace Qedo {


HomeEntry::HomeEntry (Qedo::HomeServantBase* home_servant, 
					  Components::Cookie* c, 
#ifdef _WIN32
					  HINSTANCE servant_module,
					  HINSTANCE executor_module
#else
					  void* servant_module,
					  void* executor_module
#endif
					  )
: home_servant_ (home_servant)
, home_cookie_(c)
, servant_module_ (servant_module)
, executor_module_ (executor_module)
{
	home_servant_->_add_ref();
	if (home_cookie_) { home_cookie_->_add_ref(); }
}


HomeEntry::HomeEntry()
{
}


HomeEntry::HomeEntry (const HomeEntry& home_entry)
: home_servant_ (home_entry.home_servant_)
, home_cookie_(home_entry.home_cookie_)
, servant_module_ (home_entry.servant_module_)
, executor_module_ (home_entry.executor_module_)
{
	home_servant_->_add_ref();
	if (home_cookie_) { home_cookie_->_add_ref(); }
}


HomeEntry& 
HomeEntry::operator= (const HomeEntry& home_entry)
{
	if ( & home_entry != this ) {

		if (home_servant_)
			home_servant_->_remove_ref();

		home_servant_ = home_entry.home_servant_;
		home_servant_->_add_ref();

		if (home_cookie_) { home_cookie_->_remove_ref(); }
		home_cookie_ = home_entry.home_cookie_;
		if (home_cookie_) { home_cookie_->_add_ref(); }

		servant_module_ = home_entry.servant_module_;
		executor_module_ = home_entry.executor_module_;

	}

	return *this;
}


HomeEntry::~HomeEntry()
{
	home_servant_->_remove_ref();
	if (home_cookie_) { home_cookie_->_remove_ref(); }
}


ServiceReferenceEntry::ServiceReferenceEntry (const char* service_id, CORBA::Object_ptr service_ref)
: _service_id(service_id)
, _service_ref(CORBA::Object::_duplicate(service_ref))
{
	DEBUG_OUT2("ServiceReferenceEntry: new entry for ", service_id);
}


ServiceReferenceEntry::ServiceReferenceEntry (const ServiceReferenceEntry& service_entry)
: _service_id(service_entry._service_id)
, _service_ref(CORBA::Object::_duplicate(service_entry._service_ref.in()))
{
}


ServiceReferenceEntry::~ServiceReferenceEntry()
{
	//CORBA::release( _service_ref ); !!! _var
}


ContainerInterfaceImpl::EventEntry::EventEntry (Components::EventConsumerBase_ptr c, Components::EventBase* e)
: consumer_ (Components::EventConsumerBase::_duplicate(c))
, event_ (e)
{
	CORBA::add_ref (e);
}

ContainerInterfaceImpl::EventEntry::EventEntry (const EventEntry& e)
{
	const Components::EventConsumerBase_ptr a = e.consumer_.in();
	Components::EventConsumerBase_ptr c = const_cast<Components::EventConsumerBase_ptr>(a);
	consumer_ = Components::EventConsumerBase::_duplicate(c);
	event_ = e.event_;
	CORBA::add_ref(event_);
}

ContainerInterfaceImpl::EventEntry::~EventEntry()
{
	CORBA::remove_ref (event_);
}

ContainerInterfaceImpl::EventEntry&
ContainerInterfaceImpl::EventEntry::operator= (const ContainerInterfaceImpl::EventEntry& e)
{
	if( &e != this) {
		CORBA::remove_ref (event_);
		consumer_ = Components::EventConsumerBase::_duplicate(e.consumer_.in());
		event_ = e.event_;
		CORBA::add_ref(event_);
	}
	return *this;
}

void*
ContainerInterfaceImpl::event_dispatcher_thread (void* data)
{
	DEBUG_OUT ("ContainerInterfaceImpl: Event dispatcher Thread started");

	ContainerInterfaceImpl* this_ptr = (ContainerInterfaceImpl*)data;

	this_ptr->event_queue_mutex_.lock_object();

	do
	{
		while (! this_ptr->event_list.empty()) 
		{
			EventEntry e = this_ptr->event_list.front();
			this_ptr->event_list.erase (this_ptr->event_list.begin());
			this_ptr->event_queue_mutex_.unlock_object();

			try 
			{
				e.consumer_->push_event (e.event_);
			}
			catch (const CORBA::SystemException& e)
			{
				DEBUG_OUT ("ContainerInterfaceImpl: Event dispatcher thread: Got CORBA system exception during delivery");
#ifdef MICO_ORB
			//	e._print (std::cerr);
#endif
			}
			catch (...)
			{
				DEBUG_OUT("ContainerInterfaceImpl: Event dispatcher thread: Got non-CORBA exception during delivery");
			}

			this_ptr->event_queue_mutex_.lock_object();
		}

		this_ptr->event_queue_cond_.wait (this_ptr->event_queue_mutex_);

	} while( ! this_ptr->event_queue_stopping_);

	// here has to be checked for finalize of the thread

	this_ptr->event_queue_mutex_.unlock_object();

	return 0;
}


ContainerInterfaceImpl::ContainerInterfaceImpl (CORBA::ORB_ptr orb, 
												PortableServer::POA_ptr root_poa, 
												ContainerType container_type,
												ComponentServerImpl* component_server,
												Components::Deployment::ComponentInstallation_ptr component_installer)
: orb_ (CORBA::ORB::_duplicate (orb)),
  root_poa_ (PortableServer::POA::_duplicate (root_poa)),
  container_type_ (container_type),
  component_server_ (component_server),
  component_installer_ (Components::Deployment::ComponentInstallation::_duplicate (component_installer))
{
	event_queue_thread_ = 0;
	event_queue_stopping_ = false ;

	component_server_->_add_ref();

	// Retrieve config values
	if (Qedo::ConfigurationReader::instance()->lookup_config_value ("/Events/EventDispatchingStrategy") == "asynchronous")
	{
		event_communication_mode_ = EVENT_COMMUNICATION_ASYNCHRONOUS;
	}
	else
	{
		event_communication_mode_ = EVENT_COMMUNICATION_SYNCHRONOUS;
	}

	//
	// get home finder
	//
	home_finder_ = Qedo_Components::HomeFinder::_nil();
	CORBA::Object_var obj;

    try
    {
        obj = orb->resolve_initial_references("ComponentHomeFinder");
    }
    catch (const CORBA::ORB::InvalidName&)
    {

        DEBUG_OUT("ContainerInterfaceImpl: No HomeFinder");
		// Since problem with MICO Initializer a new try directly over the name service
		//return;

		CosNaming::NamingContext_var nameService;

		try
		{
			std::string ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );

			if( !ns.empty() )
			{
				obj = orb_->string_to_object( ns.c_str() );
				DEBUG_OUT2( "ContainerInterfaceImpl:: NameService is ", ns );
			}
			//
			// try to get naming service from orb
			//
			else
			{
				obj = orb_->resolve_initial_references( "NameService" );
			}
		}
		catch (const CORBA::ORB::InvalidName&)
		{
			std::cerr << "ContainerInterfaceImpl: Can't resolve NameService" << std::endl;
		}

		if (CORBA::is_nil(obj.in()))
		{
			std::cerr << "ContainerInterfaceImpl: NameService is a nil object reference" << std::endl;
		}

		try
		{
			nameService = CosNaming::NamingContext::_narrow(obj.in());
		}
		catch (CORBA::SystemException&)
		{
			std::cerr << "ContainerInterfaceImpl: ORB knows NameService, but I cannot contact it" << std::endl;
		}

		//
		// Resolve the HomeFinder
		//
		CosNaming::Name aName;
	    aName.length(2);
		aName[0].id = CORBA::string_dup("Qedo");
		aName[0].kind = CORBA::string_dup("");
		aName[1].id = CORBA::string_dup("HomeFinder");
		aName[1].kind = CORBA::string_dup("");

		try
		{
			obj = nameService->resolve(aName);
		}
		catch (CosNaming::NamingContext::InvalidName&)
		{
			obj = CORBA::Object::_nil();
		}
		catch (CosNaming::NamingContext::NotFound&)
		{
			obj = CORBA::Object::_nil();
		}
		catch (CORBA::SystemException&)
		{
			obj = CORBA::Object::_nil();
		}

    }
    if (CORBA::is_nil(obj.in())) {
        DEBUG_OUT("ContainerInterfaceImpl: No HomeFinder");
    }

	try
	{
		home_finder_ = Qedo_Components::HomeFinder::_narrow(obj.in());
	}
	catch (const CORBA::SystemException&)
	{
		DEBUG_OUT("ContainerInterfaceImpl: No HomeFinder");
	}
    if (CORBA::is_nil(home_finder_.in())) {
        DEBUG_OUT("ContainerInterfaceImpl: No HomeFinder");
    }

	// Start global event dispatcher thread
	if (event_communication_mode_ == EVENT_COMMUNICATION_ASYNCHRONOUS)
		event_queue_thread_ = qedo_startDetachedThread (event_dispatcher_thread, this);
}


ContainerInterfaceImpl::~ContainerInterfaceImpl()
{
	DEBUG_OUT ("ContainerInterfaceImpl: Destructor called");

	QedoLock lock (service_references_mutex_);

	service_references_.clear();
	
	component_server_->_remove_ref();

	/* stop the event thread */
	if ( event_queue_thread_ )
	{
		event_queue_mutex_.lock_object();
		event_queue_stopping_ = true;
		event_queue_cond_.signal();
		event_queue_mutex_.unlock_object();
		event_queue_thread_->join();
		delete event_queue_thread_;
	}
}


void
ContainerInterfaceImpl::prepare_remove()
{
	DEBUG_OUT ("ContainerInterfaceImpl: prepare_remove() called");

	// Here we must remove all home instances that are still running
	if (installed_homes_.size() > 0)
	{
		DEBUG_OUT ("ContainerInterfaceImpl: Warning: There are still home instances around");

		// We cannot use an iterator to iterate through the list, since this list will be
		// manipulated by the remove actions
		while (installed_homes_.size())
		{
			this->remove_home (installed_homes_[0].home_servant_->ref());
		}
	}
}


void 
ContainerInterfaceImpl::queue_event
(Components::EventConsumerBase_ptr consumer, Components::EventBase* ev, CORBA::Long module_id)
{
	if (event_communication_mode_ == EVENT_COMMUNICATION_ASYNCHRONOUS)
	{
		QedoLock lock (event_queue_mutex_);
		Components::EventBase* e = Components::EventBase::_downcast(ev->_copy_value());
		EventEntry entry(consumer,e);
		event_list.push_back(entry);

		CORBA::remove_ref (e);

		event_queue_cond_.signal();
	}
	else
	{
		consumer->push_event (ev);
	}
}

void 
ContainerInterfaceImpl::queue_event
(const SubscribedConsumerVector& consumers, Components::EventBase* ev, CORBA::Long module_id)
{
	SubscribedConsumerVector::const_iterator iter;

	if (event_communication_mode_ == EVENT_COMMUNICATION_ASYNCHRONOUS)
	{
		QedoLock lock (event_queue_mutex_);

		Components::EventBase* e = Components::EventBase::_downcast(ev->_copy_value());

		for(iter = consumers.begin();iter != consumers.end();iter++) {
			EventEntry entry(iter->consumer(),e);
			event_list.push_back(entry);
		}

		CORBA::remove_ref (e);

		event_queue_cond_.signal();
	}
	else
	{
		for(iter = consumers.begin();iter != consumers.end();iter++) {
			iter->consumer()->push_event (ev);
		}
	}
}


Components::ConfigValues*
ContainerInterfaceImpl::configuration()
throw (CORBA::SystemException)
{
	return 0;
}


Components::Deployment::ComponentServer_ptr 
ContainerInterfaceImpl::get_component_server()
throw (CORBA::SystemException)
{
	return 0;
}


Components::CCMHome_ptr
ContainerInterfaceImpl::install_home (const char* id,
									  const char* entrypt,
									  const Components::ConfigValues& config)
throw (Components::Deployment::UnknownImplId,
       Components::Deployment::ImplEntryPointNotFound,
       Components::Deployment::InstallationFailure,
       Components::Deployment::InvalidConfiguration,
       CORBA::SystemException)
{
	DEBUG_OUT2("ContainerInterfaceImpl: install_home() called for ", id);

	//
	// analyse the configuration values
	//
	Components::ConfigValue* value;
	const char* homefinder_name = "";
	const char* service_name = 0;

	for (CORBA::ULong i = 0; i < config.length(); i++)
	{
		DEBUG_OUT2("ContainerInterfaceImpl: config value : ", config[i]->name());

		value = config[i].in();

		if (! strcmp (config[i]->name(), "HOMEFINDERNAME"))
		{
			config[i]->value() >>= homefinder_name;
			break;
		}

		if (! strcmp (config[i]->name(), "CCMSERVICE"))
		{
			config[i]->value() >>= service_name;
			break;
		}

		DEBUG_OUT2("ContainerInterfaceImpl: Unknown config value : ", config[i]->name());
	}

	//
	// Retrieve implementation description from the Component Installer
	//
	CORBA::String_var description;

	try
	{
		description = component_installer_->get_implementation (id);
	}
	catch (Components::Deployment::UnknownImplId&)
	{
		NORMAL_ERR2 ( "ContainerInterfaceImpl: Unknown Implementation Id ", id );
		throw;
	}

	//
	// Now extract relevant information out of the description
	//
	std::string::size_type pos;
	std::string desc = (const char*)description;

	// installation dir
	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract installation dir" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string install_dir = desc.substr (0, pos);
	std::string path = install_dir;
	if(install_dir != "")
	{
		path.append("/");
	}
	desc = desc.substr (pos + 1);

	// servant module
	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract servant module name" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string servant_module = path + desc.substr (0, pos);
	desc = desc.substr (pos + 1);

	// servant entry point
	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract servant entry point" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string servant_entry_point = desc.substr (0, pos);
	desc = desc.substr (pos + 1);

	// executor module
	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract executor module name" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string executor_module = path + desc.substr (0, pos);
	desc = desc.substr (pos + 1);

	// executor entry point
	pos = desc.find (";");
	if (pos == std::string::npos)
	{
		std::cerr << "ContainerInterfaceImpl: Cannot extract executor entry point name" << std::endl;
		throw Components::Deployment::InstallationFailure();
	}
	std::string executor_entry_point = desc.substr (0, pos);
	desc = desc.substr (pos + 1);

	//
	// handle valuetypes
	//
	loadValuetypeFactories( desc, install_dir );

	//
	// Now we have all relevant information and can go to load the dynamic code modules
	//
#ifdef _WIN32
	HINSTANCE handle_servant_lib;
	HINSTANCE handle_executor_lib;
#else
	void* handle_servant_lib;
	void* handle_executor_lib;
#endif

	//
	// load servant module
	//
	handle_servant_lib = Qedo::load_shared_library (servant_module.c_str(),install_dir.c_str());
	if (! handle_servant_lib)
	{
		NORMAL_ERR2 ("ContainerInterfaceImpl: Failed to load servant module ", servant_module);
		throw Components::Deployment::InstallationFailure();
	}

	//
	// find the entry point function
	//
	Qedo::HomeServantBase* (*servant_entry_proc)();

#ifdef _WIN32
	(FARPROC&)servant_entry_proc = GetProcAddress (handle_servant_lib, servant_entry_point.c_str());
#else
	servant_entry_proc = (Qedo::HomeServantBase* (*)()) 
				dlsym (handle_servant_lib, servant_entry_point.c_str());
#endif

	if (servant_entry_proc == NULL)
	{
		// Unable to locate entry point
		NORMAL_ERR2 ("ContainerInterfaceImpl: Cannot find entry point function for servant module: ",
			servant_entry_point.c_str());
		throw Components::Deployment::ImplEntryPointNotFound();
	}
	
	Qedo::HomeServantBase* qedo_home_servant;
	qedo_home_servant = (*servant_entry_proc)();

	if (! qedo_home_servant)
	{
		NORMAL_ERR ("ContainerInterfaceImpl: Entry point function returned a nil home servant");
		throw Components::Deployment::InstallationFailure();
	}

	// Validate the created home servant
	// Service or session container only accept Qedo::SessionHomeServants and process and entity containers
	// only accept Qedo::EntityHomeServants
#ifndef _QEDO_NO_QOS
	Components::Extension::ServerInterceptorRegistration_var server_reg;
	Components::Extension::ClientInterceptorRegistration_var client_reg;
#endif
	switch (container_type_)
	{
	case CT_SERVICE:
	case CT_SESSION:
		Qedo::SessionHomeServant* session_home;

		session_home = dynamic_cast <Qedo::SessionHomeServant*> (qedo_home_servant);

#ifndef _QEDO_NO_QOS
		servant_reg = component_server_ -> get_servant_dispatcher ();
		session_home -> set_servant_interceptor_dispatcher (servant_reg);
		DEBUG_OUT("ContainerInterfaceImpl: servant dispatcher set at home");
#endif

		if (! session_home)
		{
			NORMAL_ERR ("ContainerInterfaceImpl: Container type is incompatible. Loaded home servant is not a Qedo::SessionHomeServant");
			throw Components::Deployment::InstallationFailure();
		}
		break;
	case CT_PROCESS:
	case CT_ENTITY:
	{
#ifndef _QEDO_NO_DB
		Qedo::EntityHomeServant* entity_home;

		entity_home = dynamic_cast <Qedo::EntityHomeServant*> (qedo_home_servant);

		if (! entity_home)
		{
			NORMAL_ERR ("ContainerInterfaceImpl: Container type is incompatible. Loaded home servant is not a Qedo::EntityHomeServant");
			throw Components::Deployment::InstallationFailure();
		}

		//get etc path
		std::string etc_path = Qedo::getEnvironment ("QEDO");

		if (etc_path == "")
		{
			NORMAL_OUT ("ConfigurationReader: Warning: QEDO environment varibale not set or empty");
	#ifdef _WIN32
			etc_path = "C:\\etc\\";
	#else
			etc_path = "/etc/";
	#endif
			NORMAL_OUT2 ("ConfigurationReader: Using default path ", etc_path.c_str());
		}
		else
		{
	#ifdef _WIN32
			etc_path += "\\etc\\";
	#else
			etc_path += "/etc/";
	#endif
		}
		//get connector
		Connector_var pConn = Connector::_duplicate(component_server_->getConnector());

		if( ! pConn )
		{
			std::cout << "pConn is NULL" << std::endl;
			throw Components::Deployment::InstallationFailure();
		}

		//create a session ...
		DTMReader reader;
		CosPersistentState::ParameterList params;

		try
		{
			reader.readConnection( etc_path+"database.xml", params );
		}
		catch( DTMReadException )
		{
			std::cerr << "!!!!! Error during reading database.xml" << std::endl;
			throw Components::Deployment::InstallationFailure();
		}

		std::cout << "creating session ...\n";
		CosPersistentState::Sessio_var pSession = pConn->create_basic_session(CosPersistentState::READ_WRITE, "", params);
		SessionImpl* pSessionImpl = dynamic_cast <SessionImpl*> (pSession.in());

		std::map<std::string, std::string> mTables;
		std::map<std::string, std::string>::iterator iter;
		entity_home->get_table_info(mTables);

		std::string strTable = "PID_CONTENT";
		strTable = convert2Lowercase(strTable);
		if( ! pSessionImpl->IsTableExist(strTable.c_str()) )
		{
			std::stringstream strContent;
			strContent << "create table PID_CONTENT ( PID VARCHAR(254) not null, ";
			strContent << "HOME VARCHAR(254) not null, ";
			strContent << "TYPE VARCHAR(254) not null, ";
			strContent << "constraint PK_PIDCONTENT primary key (PID));";

			pSessionImpl->ExecuteSQL(strContent.str().c_str());
		}

		//create table in the database
		for(iter=mTables.begin(); iter!=mTables.end(); iter++)
		{
			std::string strName = iter->first;
			std::string strInfo = iter->second;
			strName = convert2Lowercase(strName);

			if( ! pSessionImpl->IsTableExist(strName.c_str()) )
			{
				std::cout << "creating table " << strName << " ...\n";
				pSessionImpl->ExecuteSQL(strInfo.c_str());
			}
			else
				std::cout << "table " << strName << " exists!\n";
		}

		//register storage object/home factory
		entity_home->init_datastore( pConn.in(), pSession.in() );
		break;
#endif // _QEDO_NO_DB
	}
	case CT_EXTENSION:
#ifndef _QEDO_NO_QOS
		Qedo::ExtensionHomeServant* extension_home;

		extension_home = dynamic_cast <Qedo::ExtensionHomeServant*> (qedo_home_servant);
		if (! extension_home)
		{
			NORMAL_ERR ("ContainerInterfaceImpl: Container type is incompatible. Loaded home servant is not a Qedo::ExtensionHomeServant");
			throw Components::Deployment::InstallationFailure();
		}

		//
		// set interceptor_dispatchers
		//

		server_reg = component_server_ -> get_server_dispatcher ();
		extension_home -> set_server_interceptor_dispatcher (server_reg);
		DEBUG_OUT("ContainerInterfaceImpl: server dispatcher set at home");

		client_reg = component_server_ -> get_client_dispatcher ();
		extension_home -> set_client_interceptor_dispatcher (client_reg);
		DEBUG_OUT("ContainerInterfaceImpl: client dispatcher set at home");

		servant_reg = component_server_ -> get_servant_dispatcher ();
		extension_home -> set_servant_interceptor_dispatcher (servant_reg);
		DEBUG_OUT("ContainerInterfaceImpl: servant dispatcher set at home");
#endif
		break;

	default:
		NORMAL_ERR ("ContainerInterfaceImpl: Container type is unknown");
		throw Components::Deployment::InstallationFailure();
	}

	//
	// Load the executor module
	//
	handle_executor_lib = Qedo::load_shared_library (executor_module.c_str(),install_dir.c_str());

	if (! handle_executor_lib)
	{
		NORMAL_ERR2 ("ContainerInterfaceImpl: Failed to load executor module ", executor_module);
		throw Components::Deployment::InstallationFailure();
	}

	//
	// Find the entry point function for the executor module
	//
	Components::HomeExecutorBase_ptr (*executor_entry_proc)();

#ifdef _WIN32
	(FARPROC&)executor_entry_proc = GetProcAddress (handle_executor_lib, executor_entry_point.c_str());
#else
	executor_entry_proc = (::Components::HomeExecutorBase_ptr (*)())
				dlsym ( handle_executor_lib, executor_entry_point.c_str() );
#endif

	if (executor_entry_proc == NULL)
	{
		// Unable to locate entry point
		NORMAL_ERR2 ("ContainerInterfaceImpl: Cannot find entry point function for executor module: ",
			executor_entry_point.c_str());
		throw Components::Deployment::ImplEntryPointNotFound();
	}
	
	Components::HomeExecutorBase_ptr home_executor;
	home_executor = (*executor_entry_proc)();

	if (! home_executor)
	{
		NORMAL_ERR ("ContainerInterfaceImpl: Entry point function returned a nil home executor");
		throw Components::Deployment::InstallationFailure();
	}

	//
	// Initialize home servant
	//
	qedo_home_servant->initialize( root_poa_, home_executor, this, install_dir );
	Components::CCMHome_var home_ref = qedo_home_servant->ref();

	HomeExecutorContext *home_ctx = new HomeExecutorContext (home_ref);
	home_executor->set_context (home_ctx);	// Qedo extension (hack): Standard home executor has no context!
	home_ctx->_remove_ref();

	if(service_name)
	{
		DEBUG_OUT2("..... home for CCMService installed: ", service_name);
		qedo_home_servant->service (service_name);
	}

	//
	// register home in HomeFinder
	//
	Components::Cookie_var cookie;
	if (!CORBA::is_nil(home_finder_.in()))
	{
        try
		{
			cookie = home_finder_->register_home(home_ref, qedo_home_servant->get_component_repid(), 
												 qedo_home_servant->get_home_repid(), homefinder_name);
		}
		catch(...)
		{
		}
    }

	//
	// register home in container
	//
	HomeEntry new_entry(qedo_home_servant, cookie, handle_servant_lib, handle_executor_lib);
	installed_homes_.push_back (new_entry);
	// Okay, our home servant is stored in the home entry and the executor is stored in the
	// home servant, so we do not need any additional reference here
	qedo_home_servant->_remove_ref();

	CORBA::release (home_executor);

	return home_ref._retn();
}


void 
ContainerInterfaceImpl::remove_home (Components::CCMHome_ptr href)
throw (Components::RemoveFailure, CORBA::SystemException)
{
	//
	// Find the home in our list of installed homes
	//
	std::vector <HomeEntry>::iterator homes_iter;

	for (homes_iter = installed_homes_.begin(); homes_iter != installed_homes_.end(); homes_iter++)
	{
		Components::CCMHome_var home_ref = (*homes_iter).home_servant_->ref();

		if (home_ref->_is_equivalent (href))
		{
			DEBUG_OUT ("ContainerInterfaceImpl: remove_home(): Home servant found");
			break;
		}
	}

	if (homes_iter == installed_homes_.end())
	{
		DEBUG_OUT ("ContainerInterfaceImpl: Unknown home");
		throw Components::RemoveFailure();
	}

	//
	// unregister home in HomeFinder
	//
	Components::Cookie* cookie = (*homes_iter).home_cookie_;
	if (!CORBA::is_nil(home_finder_.in()) && cookie)
	{
        DEBUG_OUT ("ContainerInterfaceImpl: unregister home");

		try
		{
			home_finder_->unregister_home( cookie );
		}
		catch (CORBA::SystemException& ex)
		{
			DEBUG_OUT2 ("ContainerInterfaceImpl: CORBA system exception during unregister_home() ", ex);
		}
    }

	Qedo::HomeServantBase* home_servant = (*homes_iter).home_servant_;
	home_servant->prepare_remove();

#ifdef _WIN32
	HINSTANCE servant_module;
	HINSTANCE executor_module;
#else
	void* servant_module;
	void* executor_module;
#endif

	servant_module = (*homes_iter).servant_module_;
	executor_module = (*homes_iter).executor_module_;

	installed_homes_.erase (homes_iter);


	DEBUG_OUT ("ContainerInterfaceImpl: unload home servant code");
	Qedo::unload_shared_library (servant_module);

	DEBUG_OUT ("ContainerInterfaceImpl: unload home executor code");
	Qedo::unload_shared_library (executor_module);
}


Components::CCMHomes* 
ContainerInterfaceImpl::get_homes()
throw (CORBA::SystemException)
{
	Components::CCMHomes_var homes = new Components::CCMHomes();
	homes->length (installed_homes_.size());

	for (unsigned int i = 0; i < installed_homes_.size(); i++)
	{
        homes.inout()[i] = installed_homes_[i].home_servant_->ref();
	}

	return homes._retn();
}


void 
ContainerInterfaceImpl::remove()
throw (Components::RemoveFailure, CORBA::SystemException)
{
	Components::Deployment::Container_var container = this->_this();
	component_server_->remove_container (container.in());
}


void 
ContainerInterfaceImpl::install_service_reference(const char* id, CORBA::Object_ptr ref)
throw (Components::CCMException, CORBA::SystemException)
{
	//
	// check whether a service for this id is already in our list of services
	//
	std::vector <ServiceReferenceEntry>::iterator iter;

	QedoLock lock (service_references_mutex_);

	for (iter = service_references_.begin(); iter != service_references_.end(); iter++)
	{
		if(!iter->_service_id.compare(id)) {
			// throw an exception
			// this policy could be configured by ConfigValue (e.g. replace the old service by the new one)
			throw Components::CCMException();
		}
	}

	//
	// register service
	//
	ServiceReferenceEntry new_entry(id, ref);
	service_references_.push_back (new_entry);

	DEBUG_OUT2("ContainerInterfaceImpl: service registered for ", id);
}


CORBA::Object_ptr 
ContainerInterfaceImpl::resolve_service_reference(const char* service_id)
throw (Components::CCMException)
{
	//
	// find the service in our list of services
	//
	std::vector <ServiceReferenceEntry>::iterator iter;

	QedoLock lock (service_references_mutex_);

	for (iter = service_references_.begin(); iter != service_references_.end(); iter++)
	{
		if(!iter->_service_id.compare(service_id)) {
			return iter->_service_ref;
		}
	}
	return component_server_ -> resolve_service_reference(service_id);
//	throw Components::CCMException();
}


void
ContainerInterfaceImpl::loadValuetypeFactories(std::string desc, std::string install_dir)
throw (Components::CCMException)
{
	std::string::size_type pos = desc.find (";");
	while (pos != std::string::npos)
	{
		std::string value_repid = desc.substr (0, pos);
		desc = desc.substr (pos + 1);
		pos = desc.find (";");
		std::string value_code = install_dir + "/" + desc.substr (0, pos);
		desc = desc.substr (pos + 1);
		pos = desc.find (";");

		component_server_->loadValuetypeFactory(value_repid.c_str(), value_code.c_str());
	}
}


} // namespace Qedo

