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

#include "Assembly.h"
#include "CADReader.h"
#include "CPFReader.h"
#include "Components.h"


namespace Qedo {


AssemblyImpl::AssemblyImpl (std::string package, Cookie_impl* cookie, CosNaming::NamingContext_ptr nameContext)
: package_(package)
{
	//
	// get the path where the package is installed
	//
	pathname_ = package;
#ifdef _WIN32
	std::string::size_type i = pathname_.find_last_of("/\\");
#else
	std::string::size_type i = pathname_.find_last_of("/");
#endif
	if ( ( i >= 0 ) && ( i < pathname_.size() ) )
	{
		pathname_.replace( i + 1, pathname_.size() - i - 1, std::string( "" ) );
	}

	state_ = Components::Deployment::INACTIVE;
	cookie_ = cookie;
	cookie_->_add_ref();
    nameService_ = CosNaming::NamingContext::_duplicate(nameContext);
}


AssemblyImpl::~AssemblyImpl ()
{
	cookie_->_remove_ref();
}


std::string 
AssemblyImpl::get_uuid () const
{
	return data_.uuid_;
}


std::string 
AssemblyImpl::get_cookie () const
{
	const char* s = cookie_->to_string();
	std::string x = s;
	CORBA::string_free(const_cast<char*>(s));
	return x;
}


bool 
AssemblyImpl::operator == (Components::Cookie* cook)
{
	return cookie_->equal(cook);
}


Components::Deployment::ComponentServer_ptr
AssemblyImpl::createComponentServer (DestinationData dest)
throw( Components::CreateFailure )
{
	DEBUG_OUT( "..... create new component server" );
	Components::Deployment::ServerActivator_var serverActivator;
	Components::Deployment::ComponentServer_var component_server;
	CORBA::Object_var obj;

    //
	// destination is given as node
	//
	if(!dest.node.empty())
	{
		//
		// get server activator for destination node
		//
		obj = resolveName( SERVER_ACTIVATOR_CONTEXT + dest.node );
		if ( CORBA::is_nil(obj))
		{
			DEBUG_OUT2(".......... no ServerActivator found for ", dest.node );
			throw Components::CreateFailure();
		}

		serverActivator = Components::Deployment::ServerActivator::_narrow(obj.in());
		if ( CORBA::is_nil(serverActivator.in()))
		{
			DEBUG_OUT(".......... ServerActivator is NIL ");
			throw Components::CreateFailure();
		}

		//
		// create new Component Server
		//
		try
		{
			Components::ConfigValues_var config = new Components::ConfigValues();
			component_server = serverActivator->create_component_server(config);
		}
		catch ( CORBA::SystemException& )
		{
			std::cerr << ".......... CORBA system exception during create_component_server()" << std::endl;
			std::cerr << ".......... is ServerActivator running?" << std::endl;
			throw Components::CreateFailure();
		}
		if (CORBA::is_nil(component_server))
		{
			std::cerr << ".......... Component Server is NIL" << std::endl;
			throw Components::CreateFailure();
		}
	}
	//
	// destination is given as activation
	//
	else
	{
		obj = getRef( dest.activation_ref );

		//
		// serveractivator is given
		//
		if(dest.activation_type.compare( "serveractivator" ))
		{
			serverActivator = Components::Deployment::ServerActivator::_narrow(obj.in());
			if ( CORBA::is_nil(serverActivator.in()))
			{
				NORMAL_ERR( "AssemblyImpl: ServerActivator is NIL " );
				throw Components::CreateFailure();
			}

			//
			// create new Component Server
			//
			try
			{
				Components::ConfigValues_var config = new Components::ConfigValues();
				component_server = serverActivator->create_component_server(config);
			}
			catch ( CORBA::SystemException& )
			{
				NORMAL_ERR( "AssemblyImpl: CORBA system exception during create_component_server()" );
				throw Components::CreateFailure();
			}
			if (CORBA::is_nil(component_server))
			{
				NORMAL_ERR( "AssemblyImpl: Component Server is NIL" );
				throw Components::CreateFailure();
			}
		}
		//
		// componentserver is given
		//
		else if(dest.activation_type.compare( "componentserver" ))
		{
			component_server = Components::Deployment::ComponentServer::_narrow(obj.in());
			if ( CORBA::is_nil(component_server.in()))
			{
				NORMAL_ERR( "AssemblyImpl: ComponentServer is NIL " );
				throw Components::CreateFailure();
			}
		}
		//
		// unknown activation type
		//
		else
		{
			NORMAL_ERR2( "unknown activation type", dest.activation_type );
			throw Components::CreateFailure();
		}
	}

    return component_server._retn();
}


Components::Deployment::Container_ptr
AssemblyImpl::createContainer
(Components::Deployment::ComponentServer_ptr component_server, const ::Components::ConfigValues& config)
throw( Components::CreateFailure )
{
	DEBUG_OUT( "AssemblyImpl: create new container" );

    //
	// create new Container
	//
    Components::Deployment::Container_var container;
	try
	{
        container =	component_server->create_container( config );
	}
	catch (Components::CreateFailure&)
	{
		NORMAL_ERR( "AssemblyImpl: This Component Server cannot create a container of the requested type" );
		throw Components::CreateFailure();
	}
	catch (CORBA::SystemException& ex)
	{
		NORMAL_ERR2( "AssemblyImpl: CORBA::SystemException during create_container() : ", ex );
		throw Components::CreateFailure();
	}

    return container._retn();
}


Components::Deployment::ExtComponentInstallation_ptr
AssemblyImpl::getComponentInstallation(DestinationData dest)
throw( Components::CreateFailure )
{
	Components::Deployment::ExtComponentInstallation_var componentInstallation;
	CORBA::Object_var obj;

	//
	// get ComponentInstallation for destination node
	//
	if(!dest.node.empty())
	{
		obj = resolveName(COMPONENT_INSTALLATION_CONTEXT + dest.node);
		if ( CORBA::is_nil(obj))
		{
			NORMAL_ERR2( "AssemblyImpl: no Object for ", dest.node );
			throw Components::CreateFailure();
		}
    
		try
		{
			componentInstallation = Components::Deployment::ExtComponentInstallation::_narrow(obj.in());
		}
		catch( CORBA::SystemException& ex )
		{
			NORMAL_ERR2( "AssemblyImpl: problem with ComponentInstallation for ", dest.node );
			NORMAL_ERR2( "AssemblyImpl: ", ex );

			Components::CreateFailure my_ex;
			my_ex.reason = 11;
			throw my_ex;
		}

		if ( CORBA::is_nil(componentInstallation.in()))
		{
			NORMAL_ERR2( "AssemblyImpl: no ComponentInstallation for ", dest.node );
			throw Components::CreateFailure();
		}
	}
	//
	// get ComponentInstallation according to installation ref
	//
	else
	{
		obj = getRef( dest.installation_ref );

		// todo check type of installation
		componentInstallation = Components::Deployment::ExtComponentInstallation::_narrow(obj.in());
		if ( CORBA::is_nil(componentInstallation.in()))
		{
			NORMAL_ERR( "AssemblyImpl: no ComponentInstallation" );
			throw Components::CreateFailure();
		}
	}

	return componentInstallation._retn();
}


Components::CCMObject_ptr
AssemblyImpl::getInstance (std::string name)
throw( Components::CreateFailure )
{
    Components::CCMObject_var obj;
	std::map < std::string, Components::CCMObject_var > ::iterator it;
    it = instanceMap_.find(name);
    if (it != instanceMap_.end())
    {
        obj = (*it).second;
        return obj._retn();
    }

    DEBUG_OUT2(".......... no component reference for ", name);
    throw Components::CreateFailure();
}


Components::CCMHome_ptr
AssemblyImpl::getHomeInstance (std::string name)
throw( Components::CreateFailure )
{
    Components::CCMHome_var obj;
	std::map < std::string, Components::CCMHome_var > ::iterator iter;
    iter = homeMap_.find(name);
    if (iter != homeMap_.end())
    {
        obj = (*iter).second;
        return obj._retn();
    }

    DEBUG_OUT2(".......... no home reference for ", name);
    throw Components::CreateFailure();
}


CORBA::Object_ptr
AssemblyImpl::getRef (ReferenceData data)
throw(Components::CreateFailure)
{
    CORBA::Object_var obj;

	switch( data.kind )
	{
	case COMPONENTID:
		obj = getInstance( data.name );
		break;
	case HOMEID:
		obj = getHomeInstance( data.name );
		break;
	case NAMING:
		obj = resolveName( data.name );
        if( CORBA::is_nil(obj) )
        {
			NORMAL_ERR2( "AssemblyImpl: invalid name binding ", data.name );
			throw Components::CreateFailure();
        }
		break;
	case OBJECTREF:
		// todo
		break;
	case TRADER:
		// todo
		break;
	case FINDER:
		// todo
		break;
	default:
		break;
	}

	return obj._retn();
}


void
AssemblyImpl::uninstall ()
throw( Components::RemoveFailure )
{
	Components::Deployment::ExtComponentInstallation_var componentInstallation;

	//
	// for each hostcollocation
	//
	std::vector < HostData > ::const_iterator host_iter;
	for(host_iter = data_.hosts_.begin(); 
		host_iter != data_.hosts_.end(); 
		host_iter++)
	{
		try
		{
			componentInstallation = getComponentInstallation((*host_iter).dest);
		}
		catch( Components::CreateFailure& ex )
		{
			Components::RemoveFailure my_ex;
			my_ex.reason = ex.reason;
			throw my_ex;
		}

		//
		// for each processcollocation
		//
		std::vector < ProcessData > ::const_iterator process_iter;
		for(process_iter = (*host_iter).processes.begin(); 
			process_iter != (*host_iter).processes.end();
			process_iter++)
		{
			//
			// for each homeplacement
			//
			std::vector < HomeInstanceData > ::const_iterator iter;
			for(iter = (*process_iter).homes.begin();
				iter != (*process_iter).homes.end(); 
				iter++)
			{
				//
				// remove component
				//
				try
				{
					DEBUG_OUT2( "AssemblyImpl: uninstall component ", (*iter).impl_id );
					componentInstallation->remove( (*iter).impl_id.c_str() );
				}
				catch(Components::Deployment::UnknownImplId&)
				{
					NORMAL_ERR3( "AssemblyImpl: component ", (*iter).impl_id, " not installed" );
					throw Components::RemoveFailure();
				}
				catch(Components::RemoveFailure&)
				{
					NORMAL_ERR3( "AssemblyImpl: component ", (*iter).impl_id, " not removed" );
					throw Components::RemoveFailure();
				}
				catch ( CORBA::SystemException& )
				{
					NORMAL_ERR( "AssemblyImpl: CORBA system exception during uninstall()" );
					throw Components::RemoveFailure();
				}
			}
		}
	}
}


void
AssemblyImpl::install ()
throw( Components::CreateFailure )
{
	Components::Deployment::ExtComponentInstallation_var componentInstallation;
	DestinationData destination;

	//
	// for each hostcollocation
	//
	std::vector < HostData > ::iterator host_iter;
	for(host_iter = data_.hosts_.begin();
		host_iter != data_.hosts_.end(); 
		host_iter++)
	{
		destination = (*host_iter).dest;
		componentInstallation = getComponentInstallation( destination );

		//
		// for each processcollocation
		//
		std::vector < ProcessData > ::iterator process_iter;
		for(process_iter = (*host_iter).processes.begin(); 
			process_iter != (*host_iter).processes.end();
			process_iter++)
		{
			(*process_iter).dest = destination;

			//
			// for each homeplacement
			//
			std::vector < HomeInstanceData > ::iterator iter;
			for(iter = (*process_iter).homes.begin();
				iter != (*process_iter).homes.end(); 
				iter++)
			{
				(*iter).dest = destination;
				installComponent( componentInstallation, (*iter) );
			}
		}
	}

    /*
	//
    // remove extracted packages
    //
	std::map < std::string, FileData > ::iterator iter2;
	for(iter2 = data_.implementationMap_.begin();
		iter2 != data_.implementationMap_.end();
		iter2++)
	{
        removeFileOrDirectory((*iter2).second.archiv);
    }
	*/
}


void
AssemblyImpl::installComponent 
(Components::Deployment::ExtComponentInstallation_ptr componentInstallation, HomeInstanceData data)
throw( Components::CreateFailure )
{
	std::string package_file = data.file;
	std::string impl_id = data.impl_id;
	std::string location = std::string("PACKAGE=") + getFileName(package_file);

	//
	// install
	//
	try
	{
		DEBUG_OUT("..... install implementation ");
		//DEBUG_OUT2(".......... destination is ", data.dest);
		DEBUG_OUT2(".......... implementation id is ", impl_id);
		DEBUG_OUT2(".......... package is ", package_file);
		componentInstallation->install(impl_id.c_str(), location.c_str());
	}
	catch(Components::Deployment::InvalidLocation&)
	{
		DEBUG_OUT( ".......... upload required " );
		CORBA::OctetSeq_var octSeq = new CORBA::OctetSeq();
		struct stat statbuff;
		int rt = stat(package_file.c_str(), &statbuff);
		long size = statbuff.st_size;
		octSeq->length(size);
       
		std::ifstream package_stream(package_file.c_str(), std::ios::binary|std::ios::in);
		package_stream.read((char*)octSeq->get_buffer(), size);
		package_stream.close();
        
		//
		// upload first and install afterwards
		//
		try
		{
			location = componentInstallation->upload(impl_id.c_str(), octSeq);
			DEBUG_OUT( ".......... upload done, install now " );
			componentInstallation->install(impl_id.c_str(), location.c_str());
		}
		catch(Components::Deployment::InstallationFailure&)
		{
			throw Components::CreateFailure();
		}
	}
	catch(Components::Deployment::InstallationFailure&)
	{
		NORMAL_ERR( "AssemblyImpl: InstallationFailure during install()" );
		throw Components::CreateFailure();
	}
	catch ( CORBA::SystemException& )
	{
		NORMAL_ERR( "AssemblyImpl: CORBA system exception during install()" );
		NORMAL_ERR( "..... is ComponentInstallation running?" );
		throw Components::CreateFailure();
	}
}


void
AssemblyImpl::instantiate ()
throw(Components::CreateFailure)
{
	Components::CCMHome_var home;
	Components::Deployment::Container_var container;
	Components::Deployment::ComponentServer_var component_server;
	std::vector < HomeInstanceData > ::iterator iter;
	
	//
	// for each hostcollocation
	//
	std::vector < HostData > ::iterator host_iter;
	for(host_iter = data_.hosts_.begin(); 
		host_iter != data_.hosts_.end(); 
		host_iter++)
	{
		//
		// for each processcollocation
		//
		std::vector < ProcessData > ::iterator process_iter;
		for(process_iter = (*host_iter).processes.begin(); 
			process_iter != (*host_iter).processes.end();
			process_iter++)
		{
			//
			// componentserver is needed if at least one home has to be instantiated
			//
			(*process_iter).server = Components::Deployment::ComponentServer::_nil();
			for(iter = (*process_iter).homes.begin(); 
				iter != (*process_iter).homes.end(); 
				iter++)
			{
				if( (*iter).cardinality > 0 )
				{
					component_server = createComponentServer((*host_iter).dest);
					(*process_iter).server = Components::Deployment::ComponentServer::_duplicate(component_server);
					break;
				}
			}

			//
			// for each homeplacement
			//
			for(iter = (*process_iter).homes.begin(); 
				iter != (*process_iter).homes.end(); 
				iter++)
			{
				if( (*iter).cardinality > 0 )
				{
					//
					// get config values (e.g. container kind)
					//
					Components::ConfigValues_var config = new Components::ConfigValues();
					config->length(1);
					CORBA::Any any;
					any <<= ((*iter).component.kind.c_str());
					config.inout()[0] = new ConfigValue_impl("CONTAINER_TYPE", any);

					container = createContainer( component_server, config );
					(*iter).container = Components::Deployment::Container::_duplicate(container);

					home = instantiateHome( container, (*iter) );
					instantiateComponents( home, (*iter) );
				}
			}
		}
	}

	//
	// for each existing home
	//
	for(iter = data_.existing_homes_.begin();
		iter != data_.existing_homes_.end();
		iter++)
	{
		home = instantiateHome( container, (*iter) );
		instantiateComponents( home, (*iter) );
	}
}


void
AssemblyImpl::instantiateComponents( Components::CCMHome_ptr home, HomeInstanceData data )
throw(Components::CreateFailure)
{
	//
	// instanciate components
	//
	std::vector < ComponentInstanceData > ::const_iterator iter;
	for(iter = data.instances.begin(); iter != data.instances.end(); iter++)
	{
		DEBUG_OUT2( "AssemblyImpl: create new component ", (*iter).id );
		Components::ConfigValues_var config = new Components::ConfigValues();
		Components::CCMObject_var comp;
		
		//
		// get initial configuration (COACH extension)
		//
		if( (*iter).comp_prop.length())
		{
			CPFReader reader;
			config = reader.readConf( (*iter).comp_prop );
		}

		//
		// create with config (COACH extension)
		//
		if( config->length() )
		{
			try
			{
				comp = Components::KeylessCCMHome::_narrow(home)->create_component_with_config(config);
			}
			catch( ... )
			{
				NORMAL_ERR3( "AssemblyImpl: cannot create component ", (*iter).id, " with config" );
				
				try
				{
					comp = Components::KeylessCCMHome::_narrow(home)->create_component();
				}
				catch( ... )
				{
					NORMAL_ERR2( "AssemblyImpl: cannot create component ", (*iter).id );
					throw Components::CreateFailure();
				}
			}
		}
		//
		// normal create
		//
		else
		{
			try
			{
				Components::KeylessCCMHome_var khome;
				khome = Components::KeylessCCMHome::_narrow(home);
				comp = khome->create_component();
			}
			catch( ... )
			{
				NORMAL_ERR2( "AssemblyImpl: cannot create component ", (*iter).id );
				throw Components::CreateFailure();
			}
		}

		instanceMap_[(*iter).id] = Components::CCMObject::_duplicate(comp);

		//
		// property configuration
		//
		if( (*iter).comp_prop.length())
		{
			DEBUG_OUT2( "AssemblyImpl: configure component ", (*iter).id );

			CPFReader reader;
			config = reader.readCPF( (*iter).comp_prop );

			// remove property descriptor file
			removeFileOrDirectory((*iter).comp_prop);

			//
			// configure with standard configurator
			//
			StandardConfiguratorImpl* configurator = new StandardConfiguratorImpl();
			try
			{
				configurator->_this()->set_configuration(config);
				configurator->_this()->configure(comp);
			}
			catch( ... )
			{
				NORMAL_ERR2( "AssemblyImpl: cannot configure Component", (*iter).id );
				throw Components::CreateFailure();
			}
		}

		//
		// register in nameservice
		//
		std::vector < NamingRegistrationData > ::const_iterator naming_iter;
		for(naming_iter = (*iter).naming_registrations.begin();
			naming_iter != (*iter).naming_registrations.end();
			naming_iter++)
		{
			//
			// register facet
			//
			if( (*naming_iter).port_kind == FACET_PORT )
			{
				CORBA::Object_var facet;

				try
				{
					facet = comp->provide_facet( (*naming_iter).port.c_str() );
				}
				catch( Components::InvalidName& )
				{
					NORMAL_ERR2( "AssemblyImpl: no facet ", (*naming_iter).port );
					NORMAL_ERR2( "AssemblyImpl: cannot register facet for component", (*iter).id );
					break;
				}

				if( !registerName( (*naming_iter).name, facet, true ) )
				{
					NORMAL_ERR2( "AssemblyImpl: cannot register facet for component", (*iter).id );
				}

				continue;
			}

			//
			// register event
			//
			// todo
			
			//
			// register component
			//
			if( (*naming_iter).port_kind == COMPONENT_PORT )
			{
				if( !registerName( (*naming_iter).name, comp, true ) )
				{
					NORMAL_ERR2( "AssemblyImpl: cannot register component", (*iter).id );
				}
			}
		}
    }
}


Components::CCMHome_ptr
AssemblyImpl::instantiateHome 
(Components::Deployment::Container_ptr container, HomeInstanceData data)
throw(Components::CreateFailure)
{
    Components::CCMHome_var home;

	// extension, existing home can be referenced
	if(data.file.length())
	{
		//
		// create home
		//
		DEBUG_OUT2( "AssemblyImpl: create new home ", data.id );
		Components::ConfigValues_var config = new Components::ConfigValues();

		//
		// registerwithhomefinder
		//
		if( !data.finder.empty() )
		{
			config->length(1);
			CORBA::Any any;
			any <<= data.finder.c_str();
			config.inout()[0] = new ConfigValue_impl( "HOMEFINDERNAME", any );
		}

		try
		{
			home = container->install_home(data.impl_id.c_str(), "", config);
		}
		catch (Components::Deployment::UnknownImplId&)
		{
			NORMAL_ERR2( "AssemblyImpl: unknown impl id during install_home() for ", data.id );
			throw Components::CreateFailure();
		}
		catch (Components::Deployment::ImplEntryPointNotFound&)
		{
			NORMAL_ERR2( "AssemblyImpl: entry point not found during install_home() for ", data.id );
			throw Components::CreateFailure();
		}
		catch (Components::Deployment::InstallationFailure&)
		{
			NORMAL_ERR2( "AssemblyImpl: installation failure during install_home() for ", data.id );
			throw Components::CreateFailure();
		}
		catch (Components::Deployment::InvalidConfiguration&)
		{
			NORMAL_ERR2( "AssemblyImpl: invalid configuration during install_home() for ", data.id );
			throw Components::CreateFailure();
		}
		catch (CORBA::SystemException&)
		{
			NORMAL_ERR2( "AssemblyImpl: CORBA system exception during install_home() for ", data.id );
			throw Components::CreateFailure();
		}

		if (CORBA::is_nil(home))
		{
			NORMAL_ERR2( "AssemblyImpl: Component Home is NIL for ", data.id );
			throw Components::CreateFailure();
		}

		//
		// register created home
		//
		homeMap_[data.id] = Components::CCMHome::_duplicate(home);
	}
	else
    {
		//
		// extension, use referenced home
		//
		DEBUG_OUT2( "AssemblyImpl: resolve home ", data.impl_id );
        home = Components::CCMHome::_narrow( resolveName(data.impl_id) );
	}

	//
	// registerwithnaming
	//
	if (data.naming.length())
    {
		DEBUG_OUT2( "AssemblyImpl: register home with naming ", data.naming );
        registerName( data.naming, home, true );
    }

	//
	// registerwithtrader
	//
	// todo

    return home._retn();
}


void
AssemblyImpl::connectinterface ()
throw(Components::CreateFailure)
{
	std::string receptacle;
	std::string facet;
	Components::CCMObject_var user;
	CORBA::Object_var provider;
	std::vector < InterfaceConnectionData > ::const_iterator iter;
	for(iter = data_.interface_connections_.begin();
		iter != data_.interface_connections_.end();
		iter++)
	{
		DEBUG_OUT( "AssemblyImpl: make interface connection" );

		//
		// the receptacle port
		//
		receptacle = (*iter).use.name;
		DEBUG_OUT2( "..... user is ", (*iter).use.ref.name );
		DEBUG_OUT2( "..... receptacle is ", receptacle );
		user = Components::CCMObject::_narrow( getRef((*iter).use.ref) );
		
		//
		// the interface to be connected
		//
		DEBUG_OUT2( "..... provider is ", (*iter).provide.ref.name );
		provider = getRef( (*iter).provide.ref );

		//
		// in case of facet get the facet ref
		//
		facet = (*iter).provide.name;
		if( !facet.empty() )
		{
			DEBUG_OUT2( "..... facet is ", facet );
			try
			{
				provider = Components::CCMObject::_narrow(provider)->provide_facet(facet.c_str());
			}
			catch( Components::InvalidName& )
			{
				NORMAL_ERR2( "AssemblyImpl: invalid facet name ", facet );
				throw Components::CreateFailure();
			}
		}

		//
		// make the connection
		//
		Components::Cookie_var cookie;
		try
		{
			cookie = user->connect(receptacle.c_str(), provider);
		}
		catch(Components::InvalidName&)
		{
			NORMAL_ERR2( "AssemblyImpl: invalid receptacle name ", receptacle );
			throw Components::CreateFailure();
		}
		catch( Components::InvalidConnection& )
		{
			NORMAL_ERR2( "AssemblyImpl: invalid connection for ", receptacle );
			throw Components::CreateFailure();
		}
		catch( Components::AlreadyConnected& )
		{
			NORMAL_ERR2( "AssemblyImpl: already connected for ", receptacle );
			throw Components::CreateFailure();
		}
		catch( Components::ExceededConnectionLimit& )
		{
			NORMAL_ERR2( "AssemblyImpl: exceeded connection limit for ", receptacle );
			throw Components::CreateFailure();
		}
	}
}


void
AssemblyImpl::connectevent()
throw(Components::CreateFailure)
{
	std::string consume;
	std::string emit;
	Components::CCMObject_var consumer;
	Components::EventConsumerBase_var consumer_port;
	Components::CCMObject_var source;
	std::vector < EventConnectionData > ::const_iterator iter;
	for(iter = data_.event_connections_.begin();
		iter != data_.event_connections_.end();
		iter++)
	{
		DEBUG_OUT( "AssemblyImpl: make event connection" );
		
		//
		// consumer
		//
		consume = (*iter).consumer.name;
		DEBUG_OUT2( "..... consumer is ", (*iter).consumer.ref.name );
		DEBUG_OUT2( "..... port is ", consume );
		consumer = Components::CCMObject::_narrow(getRef((*iter).consumer.ref));
		try
	    {
		    consumer_port = consumer->get_consumer(consume.c_str());
	    }
		catch(Components::InvalidName&)
	    {
			NORMAL_ERR2( "AssemblyImpl: invalid sink name ", consume );
		    throw Components::CreateFailure();
		}

		if((*iter).kind == EMITTER)
		{
			//
			// emitter
			//
            source = Components::CCMObject::_narrow( getRef((*iter).emitter.ref) );
            emit = (*iter).emitter.name;
            DEBUG_OUT2( "..... emitter is ", (*iter).emitter.ref.name );
			DEBUG_OUT2( "..... port is ", emit );
                    
            //
            // connect
            //
      		try
      		{
       			source->connect_consumer( emit.c_str(), consumer_port );
       		}
       		catch(Components::InvalidName&)
       		{
				NORMAL_ERR2( "AssemblyImpl: invalid emits name ", emit );
       			throw Components::CreateFailure();
       		}
       		catch(Components::AlreadyConnected&)
            {
				NORMAL_ERR2( "AssemblyImpl: already connected with ", emit );
       			throw Components::CreateFailure();
       		}
        }
		else
		{
			//
			// publishesport
			//
			source = Components::CCMObject::_narrow( getRef((*iter).emitter.ref) );
            emit = (*iter).emitter.name;
            DEBUG_OUT2( "..... publisher is ", (*iter).emitter.ref.name );
			DEBUG_OUT2( "..... port is ", emit );

            //
            // connect
            //
            try
       		{
                // returns Cookie TODO
	   			source->subscribe( emit.c_str(), consumer_port );
	   		}
	   		catch( Components::InvalidName& )
	   		{
				NORMAL_ERR2( "AssemblyImpl: invalid publishes name ", emit );
	   			throw Components::CreateFailure();
	   		}
        }
    }
}


void
AssemblyImpl::connect()
throw(Components::CreateFailure)
{
	connectinterface();
	connectevent();
#ifndef _QEDO_NO_STREAMS
	connectstream();
#endif

}

#ifndef _QEDO_NO_STREAMS
void
AssemblyImpl::connectstream()
throw(Components::CreateFailure)
{
	std::string consume;

	std::string emit;
	//Components::CCMObject_var consumer;
	StreamComponents::SinkStreamPort_var consumer_port;
	//Components::CCMObject_var source;
	StreamComponents::StreamCCMObject_var consumer;
	StreamComponents::StreamCCMObject_var source;
	std::vector < StreamConnectionData > ::const_iterator iter;
	for(iter = data_.stream_connections_.begin();
		iter != data_.stream_connections_.end();
		iter++)
	{
		DEBUG_OUT( "AssemblyImpl: make stream connection" );

		//
		// consumer
		//
		consume =  (*iter).sink.name ;
		DEBUG_OUT2( "..... sink is ", (*iter).sink.ref.name );
		DEBUG_OUT2( "..... port is ", consume );


		consumer = StreamComponents::StreamCCMObject::_narrow(getRef((*iter).sink.ref));


		try
	    {

			consumer_port = consumer->provide_sink_stream_port(consume.c_str());

	    }
		catch(Components::InvalidName&)
	    {
			NORMAL_ERR2( "AssemblyImpl: invalid sink name ", consume );
		    throw Components::CreateFailure();
		}

		if((*iter).kind == SOURCE)
		{
			//
			// source
			//
            source = StreamComponents::StreamCCMObject::_narrow( getRef((*iter).source.ref) );
            emit = (*iter).source.name;
            DEBUG_OUT2( "..... source is ", (*iter).source.ref.name );
			DEBUG_OUT2( "..... port is ", emit );

            //
            // connect
            //
      		try
      		{

       			source->bind(emit.c_str(), consumer_port.in(), "CCM_TCP");

       		}
       		catch(Components::InvalidName&)
       		{
				NORMAL_ERR2( "AssemblyImpl: invalid emits name ", emit );
       			throw Components::CreateFailure();
       		}
       		catch(Components::AlreadyConnected&)
            {
				NORMAL_ERR2( "AssemblyImpl: already connected with ", emit );
       			throw Components::CreateFailure();
       		}
        }
		else
		{
			//
			// sourceport
			//
			source = StreamComponents::StreamCCMObject::_narrow( getRef((*iter).source.ref) );
            emit = (*iter).source.name;
            DEBUG_OUT2( "..... source is ", (*iter).source.ref.name );
			DEBUG_OUT2( "..... port is ", emit );

            //
            // connect
            //

		    try
       		{

        		source->bind(emit.c_str(), consumer_port.in(), "CCM_TCP");

	   		}
	   		catch( Components::InvalidName& )
	   		{
				NORMAL_ERR2( "AssemblyImpl: invalid source name ", emit );
	   			throw Components::CreateFailure();
	   		}

        }
    }
}
#endif


void
AssemblyImpl::configurationComplete()
throw(Components::CreateFailure)
{
	DEBUG_OUT2( "AssemblyImpl: start the application for ", package_ );

	//
    // call configuration complete according to startorder
    //
	std::vector < std::string > ::iterator iter;
	for(iter = data_.start_order_.begin();
		iter != data_.start_order_.end();
		iter++)
	{
		std::string id = (*iter);
		Components::CCMObject_var comp = instanceMap_[id];
		if( comp )
		{
			try
			{
				DEBUG_OUT2( "..... configuration_complete for ", id );
				comp->configuration_complete();
			}
			catch (CORBA::Exception& ex)
			{
				NORMAL_ERR2( "AssemblyImpl: EXCEPTION during configuration_complete: ", ex );
                throw Components::CreateFailure();
			}
			catch ( ... )
			{
				NORMAL_ERR( "AssemblyImpl: UNKNOWN EXCEPTION during configuration_complete" );
                throw Components::CreateFailure();
			}
		}
	}

	//
	// call configuration complete for all remaining components
	//
   	Components::CCMObject_var comp;
	std::map < std::string, Components::CCMObject_var > ::iterator instanceIter;
	bool found = false;
	for(instanceIter = instanceMap_.begin();
		instanceIter != instanceMap_.end();
		instanceIter++ )
	{
		//
		// if not yet started, start it
		//
		for(iter = data_.start_order_.begin();
			iter != data_.start_order_.end();
			iter++ )
		{
			if( instanceIter->first == *iter )
			{
				found = true;
				break;
			}
		}

		if( !found )
		{
			try
			{
				DEBUG_OUT2( "..... configuration_complete for ", instanceIter->first );
				instanceIter->second->configuration_complete();
			}
			catch ( CORBA::Exception& ex )
			{
				NORMAL_ERR2( "AssemblyImpl EXCEPTION during configuration_complete : ", ex );
                throw Components::CreateFailure();
			}
			catch ( ... )
			{
				NORMAL_ERR( "AssemblyImpl: UNKNOWN EXCEPTION during configuration_complete" );
                throw Components::CreateFailure();
			}
		}
	}

	// set assembly state to active
	state_ = Components::Deployment::INSERVICE;
}


void
AssemblyImpl::build
()
throw( Components::CreateFailure )
{
	DEBUG_OUT2( "AssemblyImpl: build assembly for ", package_ );

	QedoLock lock (assembly_mutex_);

	//
	// get data from descriptor file
    //
	CADReader reader;
	try 
	{
		reader.readCAD( package_, &data_, pathname_ );
	}
	catch( CADReadException ) 
	{
        throw Components::CreateFailure();
	}

	//
	// install implementations
	//
	install();

	//
	// instantiate components
	//
	instantiate();

	//
	// make connections
	//
	connect();

	//
	// start components
	//
	configurationComplete();
    
	DEBUG_OUT3( "AssemblyImpl: assembly for ", package_, " is running" );
}


void 
AssemblyImpl::tear_down ()
throw( Components::RemoveFailure )
{
	DEBUG_OUT2( "AssemblyImpl: tear down the application for ", package_ );

	QedoLock lock (assembly_mutex_);

	//
	// use reverse start order to remove components
	//
	std::vector < std::string > ::reverse_iterator iter;
	std::map < std::string, Components::CCMObject_var > ::iterator instanceIter;
	Components::CCMObject_var comp;
	for(iter = data_.start_order_.rbegin();
		iter != data_.start_order_.rend();
		iter++ )
	{
		instanceIter = instanceMap_.find( *iter );
		if( instanceIter != instanceMap_.end() )
		{
			try
			{
				DEBUG_OUT2("..... remove ", instanceIter->first );
				comp = Components::CCMObject::_duplicate( instanceIter->second );
				comp->remove();
			}
			catch (CORBA::Exception&)
			{
				NORMAL_ERR2( "AssemblyImpl: EXCEPTION during removal of ", instanceIter->first );
			}

			instanceMap_.erase( instanceIter );
		}
	}

	//
	// call remove for all remaining components
	//
	for( instanceIter = instanceMap_.begin();
		 instanceIter != instanceMap_.end();
		 instanceIter++ )
	{
		try
		{
			DEBUG_OUT2( "..... remove ", instanceIter->first );
			instanceIter->second->remove();
		}
		catch (CORBA::Exception&)
		{
			NORMAL_ERR2( "AssemblyImpl: EXCEPTION during removal of ", instanceIter->first );
		}
	}

	instanceMap_.clear();

	//
	// remove homes/containers/servers
	//
	std::vector < HostData > ::iterator host_iter;
	std::vector < ProcessData > ::iterator process_iter;
	std::vector < HomeInstanceData > ::iterator home_iter;

	// for each host
	for(host_iter = data_.hosts_.begin();
		host_iter != data_.hosts_.end();
		host_iter++)
	{
		// for each processcollocation
		for(process_iter = (*host_iter).processes.begin(); 
			process_iter != (*host_iter).processes.end();
			process_iter++)
		{
			//
			// for each homeplacement
			//
			for(home_iter = (*process_iter).homes.begin();
				home_iter != (*process_iter).homes.end();
				home_iter++)
			{
				if( (*home_iter).cardinality > 0 )
				{
					//
					// remove home
					//
					try
					{
						DEBUG_OUT2( "..... remove home ", (*home_iter).id );
						(*home_iter).container->remove_home(getHomeInstance((*home_iter).id));
					}
					catch (Components::RemoveFailure)
					{
						NORMAL_ERR2( "AssemblyImpl: remove home failure for ", (*home_iter).id );
					}
					catch (CORBA::Exception& e)
					{
						NORMAL_ERR2( "AssemblyImpl: EXCEPTION during removal of home ", (*home_iter).id );
#ifdef MICO_ORB
						e._print (std::cerr);
						std::cerr << std::endl;
#endif
					}

					//
					// remove container
					//
					try
					{
						DEBUG_OUT( "..... remove container" );
						(*home_iter).container->remove();
					}
					catch (Components::RemoveFailure)
					{
						NORMAL_ERR( "AssemblyImpl: remove container failure" );
					}
					catch (CORBA::Exception& e)
					{
						NORMAL_ERR( "AssemblyImpl: EXCEPTION during removal of container" );
#ifdef MICO_ORB
						e._print (std::cerr);
						std::cerr << std::endl;
#endif
					}
				}
			}

			if( !CORBA::is_nil( (*process_iter).server ) )
			{
				//
				// remove component server
				//
				try
				{
					DEBUG_OUT( "..... remove component server" );
					(*process_iter).server->remove();
				}
				catch (Components::RemoveFailure)
				{
					NORMAL_ERR( "AssemblyImpl: remove component server failure");
				}
				catch (CORBA::Exception& e)
				{
					NORMAL_ERR( "AssemblyImpl: EXCEPTION during removal of container" );
#ifdef MICO_ORB
					e._print (std::cerr);
					std::cerr << std::endl;
#endif
				}
			}
		}
	}

	homeMap_.clear();

	//
	// uninstall
	//
	uninstall();

	DEBUG_OUT3( "application for ", package_, " is teared down and uninstalled" );
}


Components::Deployment::AssemblyState 
AssemblyImpl::get_state ()
throw(CORBA::SystemException)
{
	return state_;
}


} // namespace
