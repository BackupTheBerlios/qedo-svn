/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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


namespace Qedo {


/**
 *
 */
AssemblyImpl::AssemblyImpl (std::string package, Cookie_impl* cookie, CosNaming::NamingContext_ptr nameContext)
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

    uuid_ = "";
	package_ = new Package( package );
	state_ = Components::Deployment::INACTIVE;
	cookie_ = cookie;
    nameService_ = CosNaming::NamingContext::_duplicate(nameContext);
}


/**
 *
 */
AssemblyImpl::~AssemblyImpl ()
{
}


std::string 
AssemblyImpl::get_uuid () const
{
    return uuid_;
}


/**
 *
 */
bool 
AssemblyImpl::operator == (Components::Cookie* cook)
{
	return cookie_->equal(cook);
}


/**
 *
 */
void
AssemblyImpl::registerWithNaming (DOM_Element element, CORBA::Object_ptr obj)
{
	std::string binding = element.getAttribute("name").transcode();
    registerName(binding, obj, true);
}


/**
 *
 */
void
AssemblyImpl::registerComponent (DOM_Element element, CORBA::Object_ptr obj)
{
    DOM_Node child = element.getFirstChild();
	while (child != 0)
	{
		//
		// emitsidentifier
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("emitsidentifier")))
		{
            // TODO
        }

        //
		// providesidetifier
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("providesidetifier")))
		{
            // TODO
        }

        //
		// publishesidentifier
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("publishesidentifier")))
		{
            // TODO
        }

        //
		// registerwithnaming
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("registerwithnaming")))
		{
            registerWithNaming((DOM_Element&)child, obj);
        }

        //
		// registerwithtrader
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("registerwithtrader")))
		{
            // TODO
        }

        // get next child element
		child = child.getNextSibling();
    }
}


/**
 *
 */
void
AssemblyImpl::extension (DOM_Element ext)
throw( Components::CreateFailure )
{
	std::string class_attr = ext.getAttribute("class").transcode();
	
    //
    // startorder
    //
    if( class_attr == "startorder" )
	{
		std::string comp_id = ext.getFirstChild().getNodeValue().transcode();
		Components::CCMObject_var comp = instanceMap_[comp_id];
		if( comp )
		{
			DEBUG_OUT2("\nAssembly: call configuration_complete to : ", comp_id);

			try
			{
				comp->configuration_complete();
			}
			catch (CORBA::Exception& ex)
			{
				DEBUG_OUT2( "..... EXCEPTION DURING configuration_complete : ", ex );
                throw Components::CreateFailure();
			}
			catch ( ... )
			{
				DEBUG_OUT( "..... UNKNOWN EXCEPTION DURING configuration_complete" );
                throw Components::CreateFailure();
			}

            // keep start order
			startOrder_.push_back( comp_id );
		}
	}
}


/**
 * return the destination for placement,
 * if destination is empty, return the local hostname (for convenience)
 */
std::string
AssemblyImpl::destination (DOM_Element homeplacement)
throw(Components::CreateFailure)
{
	DOM_NodeList nodeList = homeplacement.getElementsByTagName("destination");
	if (nodeList.getLength() != 1)
	{
		DEBUG_OUT2("\nAssembly: not exactly one destination element for ", homeplacement.getAttribute("id").transcode());
		throw Components::CreateFailure();
	}

	std::string name;
    DOM_Node dest = ((const DOM_Element& )nodeList.item(0)).getFirstChild();
    if (dest != 0)
    {
        name = dest.getNodeValue().transcode();
        return name;
    }

    // destination was empty
    char hostname[256];
	gethostname(hostname, 256);
    name = hostname;
    return name;
}


/**
 *
 */
std::string
AssemblyImpl::componentfileref (DOM_Element homeplacement)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = homeplacement.getElementsByTagName("componentfileref");
    if (nodeList.getLength() != 1)
	{
		DEBUG_OUT2("\nAssembly: not exactly one componentfileref element for ", homeplacement.getAttribute("id").transcode());
		throw Components::CreateFailure();
	}
	DOM_Element fileElement = (const DOM_Element&)nodeList.item(0);
	std::string id = fileElement.getAttribute("idref").transcode();
    return id;
}


/**
 *
 */
std::string
AssemblyImpl::componentimplref (DOM_Element homeplacement)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = homeplacement.getElementsByTagName("componentimplref");
    if (nodeList.getLength() != 1)
	{
		DEBUG_OUT2("\nAssembly : missing componentimplref element for ", homeplacement.getAttribute("id").transcode());
		throw Components::CreateFailure();
	}
	DOM_Element fileElement = (const DOM_Element&)nodeList.item(0);
	std::string id = fileElement.getAttribute("idref").transcode();
    return id;
}


/**
 *
 */
std::string
AssemblyImpl::usesidentifier (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("usesidentifier");
    if (nodeList.getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing usesidentifier element");
		throw Components::CreateFailure();
	}
	DOM_Element elem = (const DOM_Element&)nodeList.item(0);
	std::string receptacle = elem.getFirstChild().getNodeValue().transcode();

    return receptacle;
}


/**
 *
 */
std::string
AssemblyImpl::providesidentifier (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("providesidentifier");
    if (nodeList.getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing providesidentifier element");
		throw Components::CreateFailure();
	}
	DOM_Element elem = (const DOM_Element&)nodeList.item(0);
	std::string facet = elem.getFirstChild().getNodeValue().transcode();

    return facet;
}


/**
 *
 */
std::string
AssemblyImpl::consumesidentifier (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("consumesidentifier");
    if (nodeList.getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing consumesidentifier element");
		throw Components::CreateFailure();
	}
	DOM_Element elem = (const DOM_Element&)nodeList.item(0);
	std::string name = elem.getFirstChild().getNodeValue().transcode();

    return name;
}


/**
 *
 */
std::string
AssemblyImpl::emitsidentifier (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("emitsidentifier");
    if (nodeList.getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing emitsidentifier element");
		throw Components::CreateFailure();
	}
	DOM_Element elem = (const DOM_Element&)nodeList.item(0);
	std::string name = elem.getFirstChild().getNodeValue().transcode();

    return name;
}


/**
 *
 */
std::string
AssemblyImpl::publishesidentifier (DOM_Element element)
throw(Components::CreateFailure)
{
    DOM_NodeList nodeList = element.getElementsByTagName("publishesidentifier");
    if (nodeList.getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing publishesidentifier element");
		throw Components::CreateFailure();
	}
	DOM_Element elem = (const DOM_Element&)nodeList.item(0);
	std::string name = elem.getFirstChild().getNodeValue().transcode();

    return name;
}


/**
 *
 */
CORBA::Object_ptr
AssemblyImpl::getPort (DOM_Element port)
throw(Components::CreateFailure)
{
    CORBA::Object_var obj;
    std::string name;
    DOM_Node child = port.getFirstChild();
	while (child != 0)
	{
		//
		// componentinstantiationref
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("componentinstantiationref")))
		{
			DOM_Element componentinstantiationref = (const DOM_Element&)child;
			name = componentinstantiationref.getAttribute("idref").transcode();
            obj = getInstance(name);
            break;
		}
	
		//
		// findby
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("findby")))
		{
            DOM_Node find_child = ((DOM_Element&)child).getFirstChild();
	        while (find_child != 0)
	        {
                //
		        // namingservice
		        //
		        if((find_child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		           (find_child.getNodeName().equals("namingservice")))
		        {
                    name = ((const DOM_Element&)find_child).getAttribute("name").transcode();
                    obj = resolveName(name);
                    if ( ! obj)
                    {
                        throw Components::CreateFailure();
                    }
                    break;
                }

                //
		        // stringifiedobjectref
		        //
		        if((find_child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		           (find_child.getNodeName().equals("stringifiedobjectref")))
		        {
                    // TODO
                }

                //
		        // traderquery
		        //
		        if((find_child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		           (find_child.getNodeName().equals("traderquery")))
		        {
                    // TODO
                }

                //
		        // homefinder
		        //
		        if((find_child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		           (find_child.getNodeName().equals("homefinder")))
		        {
                    // TODO
                }

                //
		        // extension
		        //
		        if((find_child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		           (find_child.getNodeName().equals("extension")))
		        {
                    // TODO
                }

                // get next child
		        find_child = find_child.getNextSibling();
            }
		}

		// get next child
		child = child.getNextSibling();
	}

    //
    // usesport
    //
    if (port.getNodeName().equals("usesport"))
	{
        DEBUG_OUT2("\tuser is ", name);
        return obj._retn();
    }

    //
    // providesport
    //
    if (port.getNodeName().equals("providesport"))
	{
        Components::CCMObject_var comp = Components::CCMObject::_narrow(obj);
		std::string facet = providesidentifier(port);
        try
		{
			obj = comp->provide_facet(facet.c_str());
		}
		catch( Components::InvalidName& )
		{
			DEBUG_OUT( "invalid facet name" );
			throw Components::CreateFailure();
		}
        DEBUG_OUT2("\tprovider is ", name);
		DEBUG_OUT2("\tfacet is ", facet);
        return obj._retn();
    }

    //
    // consumesport
    //
    if (port.getNodeName().equals("consumesport"))
	{
        Components::CCMObject_var comp;
        try
        {
            comp = Components::CCMObject::_narrow(obj);
        }
        catch (...)
        {
            DEBUG_OUT2("component is not reachable : ", name);
		    throw Components::CreateFailure();
        }

        std::string consume = consumesidentifier(port);
        try
	    {
		    obj = comp->get_consumer(consume.c_str());
	    }
		catch(Components::InvalidName&)
	    {
		    DEBUG_OUT( "invalid sink name" );
		    throw Components::CreateFailure();
		}
        DEBUG_OUT2( "\tconsumer is ", name );
		DEBUG_OUT2( "\tport is ", consume );
        return obj._retn();
    }

    //
    // emitsport
    //
    if (port.getNodeName().equals("emitsport"))
	{
        DEBUG_OUT2("\temitter is ", name);
        return obj._retn();
    }

    //
    // publishesport
    //
    if (port.getNodeName().equals("publishesport"))
	{
        DEBUG_OUT2("\tpublisher is ", name);
        return obj._retn();
    }

    //
    // other ports
    //
    DEBUG_OUT2("\tused interface is ", name);
    return obj._retn();
}


/**
 *
 */
Components::Deployment::ComponentServer_ptr
AssemblyImpl::createComponentServer (std::string dest)
throw( Components::CreateFailure )
{
    //
	// get ServerStarter for destination
	//
	Components::Deployment::ServerActivator_var serverActivator;
    Components::Deployment::ComponentServer_var component_server;

	CORBA::Object_var obj = resolveName(SERVER_ACTIVATOR_CONTEXT + dest);
    if ( ! obj)
    {
        DEBUG_OUT2("\nAssembly: no ServerActivator found for ", dest);
        throw Components::CreateFailure();
    }

    try
    {
	    serverActivator = Components::Deployment::ServerActivator::_narrow(obj.in());
    }
    catch (...)
    {
        DEBUG_OUT2("\nAssembly: ServerActivator not reachable for ", dest);
        throw Components::CreateFailure();
    }

    if ( CORBA::is_nil(serverActivator.in()))
    {
        DEBUG_OUT2("\nAssembly : ServerActivator with wrong interface for ", dest);
        throw Components::CreateFailure();
    }

	//
	// create new Component Server
	//
	DEBUG_OUT ( "\nAssembly: create new Component Server" );
	try
	{
		Components::ConfigValues_var config = new Components::ConfigValues();
        component_server = serverActivator->create_component_server(config);
	}
	catch ( CORBA::SystemException& )
	{
		std::cerr << "CORBA system exception during create_component_server()" << std::endl;
		throw Components::CreateFailure();
	}
	if (CORBA::is_nil(component_server))
	{
		std::cerr << "Cannot create Component Server" << std::endl;
		throw Components::CreateFailure();
	}

    return component_server._retn();
}


/**
 *
 */
Components::Deployment::Container_ptr
AssemblyImpl::createContainer (Components::Deployment::ComponentServer_ptr component_server)
throw( Components::CreateFailure )
{
    //
	// create new Container
	//
	DEBUG_OUT("\nAssembly: create new Container");
    Components::Deployment::Container_var container;
	Components::ConfigValues_var config = new Components::ConfigValues();
	config->length(1);
	CORBA::Any any;
	any <<= "SESSION";
	config[0] = new ConfigValue_impl("CONTAINER_TYPE", any);

	try
	{
        container =	component_server->create_container(config);
	}
	catch (Components::CreateFailure&)
	{
		std::cerr << "This Component Server cannot create a container of the requested type" << std::endl;
		throw Components::CreateFailure();
	}
	catch (CORBA::SystemException& ex)
	{
		std::cerr << "CORBA::SystemException during create_container() : " << ex << std::endl;
		throw Components::CreateFailure();
	}

    return container._retn();
}


/**
 *
 */
Components::CCMHome_ptr
AssemblyImpl::createHome (Components::Deployment::Container_ptr container, std::string id)
throw(Components::CreateFailure)
{
	//
    // create home
	//
	DEBUG_OUT2("\nAssembly: create new Component Home for ", id.c_str());
    Components::CCMHome_var home;
				
	try
	{
		Components::ConfigValues_var config = new Components::ConfigValues();
        home = container->install_home(id.c_str(), "", config);
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "CORBA system exception during install_home()" << std::endl;
		throw Components::CreateFailure();
	}

	if (CORBA::is_nil(home))
	{
		std::cerr << "Cannot create Component Home" << std::endl;
		throw Components::CreateFailure();
	}

    return home._retn();
}


/**
 *
 */
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


    DEBUG_OUT2("no component reference for : ", name);
    throw Components::CreateFailure();
}


/**
 * install a component implementation
 */
void
AssemblyImpl::installImplementation (DOM_Element homeplacement)
throw(Components::CreateFailure)
{
    std::string file = componentfileref(homeplacement);
    std::string id = componentimplref(homeplacement);
	std::string dest = destination(homeplacement);

    //
    // extension, skip if fileref is empty, id contains reference to NS
    //
    if (file == "")
    {
        return;
    }

	//
	// get ComponentInstallation for destination
	//
	Qedo_Components::Deployment::ComponentInstallation_var componentInstallation;

	CORBA::Object_var obj = resolveName(COMPONENT_INSTALLATION_CONTEXT + dest);
    if ( ! obj)
    {
        DEBUG_OUT2("no Object for ", dest);
        throw Components::CreateFailure();
    }
    
    componentInstallation = Qedo_Components::Deployment::ComponentInstallation::_narrow(obj.in());
    if ( CORBA::is_nil(componentInstallation.in()))
    {
        DEBUG_OUT2("no ComponentInstallation for ", dest);
        throw Components::CreateFailure();
    }

    //
    // install
	//
	std::string location = std::string("PACKAGE=") + implementationMap_[file];
    try
    {
		componentInstallation->install(id.c_str(), location.c_str());
    }
    catch(Components::Deployment::InvalidLocation&)
    {
        //
        // upload first
        //
        CORBA::OctetSeq_var octSeq = new CORBA::OctetSeq();
        struct stat statbuff;
        std::string packagePath = pathname_ + implementationMap_[file];
        int rt = stat(packagePath.c_str(), &statbuff);
        long size = statbuff.st_size;
        octSeq->length(size);
       
		std::ifstream packageFile(packagePath.c_str(), std::ios::binary|std::ios::in);
        packageFile.read((char*)octSeq->get_buffer(), size);
        packageFile.close();
        
        componentInstallation->upload(implementationMap_[file].c_str(), octSeq);

        //
		// install afterwards
		//
        componentInstallation->install(id.c_str(), location.c_str());
    }
}


/**
 * install all component implementations referred to in the assembly descriptor
 */
void
AssemblyImpl::install ()
throw( Components::CreateFailure )
{
	//
	// map uuid to package and extract all packages
	//
	DOM_Element document = document_.getDocumentElement();
	DOM_NodeList aNodeList;
	aNodeList = document.getElementsByTagName( "componentfiles" );
	if ( aNodeList.getLength() != 1 )
	{
		DEBUG_OUT2("\nAssembly: there must be one componentfiles element in ", package_->getName());
		throw Components::CreateFailure();
	}

	DOM_Element anElement;
	anElement = ( const DOM_Element& )aNodeList.item( 0 );
	aNodeList = anElement.getElementsByTagName( "componentfile" );
	for(CORBA::ULong i = 0; i < aNodeList.getLength(); i++ )
	{
		anElement = ( const DOM_Element& )aNodeList.item( i );
		std::string id = anElement.getAttribute( "id" ).transcode();
		DOM_NodeList fileNodeList = anElement.getElementsByTagName( "fileinarchive" );
		anElement = ( const DOM_Element& )fileNodeList.item( 0 );
		std::string package = anElement.getAttribute( "name" ).transcode();
		
		
		// extract package
		package_->extractFile( package, pathname_ + package );
		
		
		// map uuid to package
		implementationMap_[id] = package;
	}

	//
	// install component implementations for all homeplacements
	//
	aNodeList = document.getElementsByTagName("partitioning");
	anElement = (const DOM_Element&)aNodeList.item( 0 );
	DOM_Node partition_child = anElement.getFirstChild();
	while (partition_child != 0)
	{
		//
		// processcollocation
		//
		if( ( partition_child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( partition_child.getNodeName().equals( "processcollocation" ) ) )
		{
			aNodeList = ((DOM_Element&)partition_child).getElementsByTagName("homeplacement");
			for(CORBA::ULong i = 0; i < aNodeList.getLength(); i++ )
			{
				installImplementation((const DOM_Element&)aNodeList.item(i));
			}
		}
	
		//
		// homeplacement
		//
		if( ( partition_child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( partition_child.getNodeName().equals( "homeplacement" ) ) )
		{
            installImplementation((DOM_Element&)partition_child);
		}

		// get next partition element
		partition_child = partition_child.getNextSibling();
	}

    //
    // remove extracted packages
    //
	std::map < std::string, std::string > ::iterator iter;
	for (iter = implementationMap_.begin(); iter != implementationMap_.end(); iter++)
	{
        removeFileOrDirectory(pathname_ + (*iter).second);
    }
}


/**
 * instantiate a component according to the xml element in the assembly descriptor
 */
void
AssemblyImpl::instantiateComponent (DOM_Element instance, Components::CCMHome_ptr home)
throw(Components::CreateFailure)
{
	DEBUG_OUT2 ("\nAssembly: create new Component : ", instance.getAttribute( "id" ).transcode());

    //
    // instantiate component
    //
	Components::CCMObject_var comp;
	try
	{
		comp = Components::KeylessCCMHome::_narrow(home)->create_component();
	}
	catch( ... )
	{
		std::cerr << "Cannot create Component" << std::endl;
		throw Components::CreateFailure();
	}
	instanceMap_[instance.getAttribute( "id" ).transcode()] = Components::CCMObject::_duplicate(comp);

    DOM_Node child = instance.getFirstChild();
	std::string property_descriptor = "";
	while( child != 0 )
	{
		//
		// property configuration
		//
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "componentproperties" ) ) )
		{
			DOM_Node location = child.getFirstChild();
			while( location != 0 )
			{
				if( ( location.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
					( location.getNodeName().equals( "fileinarchive" ) ) )
				{
					property_descriptor = ( ( DOM_Element& )location ).getAttribute( "name" ).transcode();
				}

				
				if( ( location.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
					( location.getNodeName().equals( "codebase" ) ) )
				{
					// TODO
				}

				// next element in componentproperties
				location = location.getNextSibling();
			}

			//
			// configure
			//
			if (property_descriptor != "")
			{
				if (package_->extractFile(property_descriptor, pathname_ + property_descriptor) != 0)
				{
					std::cerr << "Error during extracting the descriptor file : " << property_descriptor << std::endl;
					throw Components::CreateFailure();
				}

				Properties* properties = new Properties(pathname_ + property_descriptor);
				Components::ConfigValues_var config = properties->getConfigValues();

                // remove property descriptor file
                removeFileOrDirectory(pathname_ + property_descriptor);

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
					std::cerr << "Cannot configure Component" << std::endl;
					throw Components::CreateFailure();
				}
			}
		}

        //
		// registercomponent
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("registercomponent")))
		{
            registerComponent((DOM_Element&)child, comp);
        }

		// next element in componentinstantiation
		child = child.getNextSibling();
	}
}


/**
 * processcollocation
 */
void
AssemblyImpl::processcollocation (DOM_Element element)
throw(Components::CreateFailure)
{
    Components::Deployment::ComponentServer_var component_server;
	Components::Deployment::Container_var container;

    //
	// get a homeplacement to determine destination
	//
	DOM_NodeList nodeList = element.getElementsByTagName("homeplacement");
	if (nodeList.getLength() == 0)
	{
		DEBUG_OUT2("\nAssembly: no homeplacements in processcollocation in ", package_->getName());
		return;
	}

	// create new Component Server
    component_server = createComponentServer(destination((const DOM_Element&)nodeList.item(0)));

	// create new Container
    container = createContainer(component_server);

	//
    // create new homes and instances
	//
	for (CORBA::ULong i = 0; i < nodeList.getLength(); i++)
	{
		homeplacement((const DOM_Element&)nodeList.item(i), container); // !!!!!!!! var type
	}
}


/**
 * home placement
 */
void
AssemblyImpl::homeplacement (DOM_Element element, Components::Deployment::Container_ptr contain)
throw(Components::CreateFailure)
{
    Components::Deployment::Container_var container = Components::Deployment::Container::_duplicate(contain);
	Components::CCMHome_var home;

	DOM_Node child = element.getFirstChild();
	while (child != 0)
	{
		//
		// componentfileref
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("componentfileref")))
        {
            std::string idref = ((const DOM_Element&)child).getAttribute("idref").transcode();
            if (idref != "")
            {
                if ( ! container)
                {
	                // create new Component Server
                    Components::Deployment::ComponentServer_var component_server;
                    component_server = createComponentServer(destination(element));

                    // create new Container
                    container = createContainer(component_server);
                }

                // instantiate home
                home = createHome(container, componentimplref(element));

                // register home reference
                homeMap_[((const DOM_Element&)element).getAttribute("id").transcode()] = 
                    Components::CCMHome::_duplicate(home);
            }
            else
            {
                // extension, use referenced home
                CORBA::Object_var dummy = resolveName(componentimplref(element));
                try
                {
                    home = Components::CCMHome::_narrow(dummy);
                }
                catch (...)
                {
                    DEBUG_OUT2("home is not reachable : ", componentimplref(element));
		            throw Components::CreateFailure();
                }
            }
        }

        //
		// registerwithnaming
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("registerwithnaming")))
        {
            registerWithNaming((const DOM_Element&)child, home);
        }

        //
		// componentinstantiation
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("componentinstantiation")))
        {
		    instantiateComponent((const DOM_Element&)child, home);
        }

        // get next child
		child = child.getNextSibling();
	}
}


/**
 * create all component instances defined in the assembly descriptor
 */
void
AssemblyImpl::instantiate ()
throw(Components::CreateFailure)
{
	DOM_NodeList aNodeList = document_.getDocumentElement().getElementsByTagName("partitioning");
	if (aNodeList.getLength() != 1)
	{
		DEBUG_OUT2("XMLParser : missing partitioning element in ", package_->getName());
		throw Components::CreateFailure();
	}

	DOM_Node child = ((const DOM_Element&)aNodeList.item(0)).getFirstChild();
	while (child != 0)
	{
		//
		// processcollocation
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("processcollocation")))
		{
			processcollocation((DOM_Element&)child);
		}

		//
		// homeplacement
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals("homeplacement")))
		{
			homeplacement((DOM_Element&)child, 0);
		}

        //
		// extension
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
			(child.getNodeName().equals( "extension")))
		{
            extension((DOM_Element&)child);
        }

		// get next child
		child = child.getNextSibling();
	}
}


/**
 * connect interface
 */
void
AssemblyImpl::connectinterface (DOM_Element element)
throw(Components::CreateFailure)
{
	DEBUG_OUT("\nAssembly: make connection");

    Components::CCMObject_var user;
    std::string receptacle;
    CORBA::Object_var used;
    DOM_Node child = element.getFirstChild();
	while (child != 0)
	{
        //
	    // usesport
		//
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("usesport")))
		{
		    DOM_Element port = (const DOM_Element&)child;
            CORBA::Object_var dummy = getPort(port);
            user = Components::CCMObject::_narrow(dummy);
            receptacle = usesidentifier(port);
            DEBUG_OUT2( "\treceptacle is ", receptacle );
        }

        //
        // providesport etc
        //
		if((child.getNodeType() == DOM_Node::ELEMENT_NODE) &&
		   (child.getNodeName().equals("providesport") ||
            child.getNodeName().equals("componentsupportedinterface") ||
            child.getNodeName().equals("existinginterface") ||
            child.getNodeName().equals("homeinterface")))
		{
            used = getPort((const DOM_Element&)child);
        }

        // next child
        child = child.getNextSibling();
    }

    //
    // connect
    //
    Components::Cookie_var cookie;
	try
	{
	    cookie = user->connect(receptacle.c_str(), used);
	}
	catch(Components::InvalidName&)
	{
	   	DEBUG_OUT( "invalid receptacle name" );
		throw Components::CreateFailure();
	}
	catch( Components::InvalidConnection& )
	{
		DEBUG_OUT( "invalid connection" );
		throw Components::CreateFailure();
	}
	catch( Components::AlreadyConnected& )
	{
		DEBUG_OUT( "already connected" );
		throw Components::CreateFailure();
	}
	catch( Components::ExceededConnectionLimit& )
	{
		DEBUG_OUT( "exceeded connection limit" );
		throw Components::CreateFailure();
	}
}


/**
 * connect events
 */
void
AssemblyImpl::connectevent (DOM_Element element)
throw(Components::CreateFailure)
{
    DEBUG_OUT( "\nAssembly: make event connection" );
			
    Components::EventConsumerBase_var consumer;
    Components::CCMObject_var source;
    DOM_Node child = element.getFirstChild();
    while (child != 0)
    {
	    //
		// consumesport
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
		    (child.getNodeName().equals( "consumesport" ) ) )
		{
            CORBA::Object_var dummy = getPort((const DOM_Element&)child);
            consumer = Components::EventConsumerBase::_narrow(dummy);
        }

        //
        // emitsport
        //
        if ((child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			(child.getNodeName().equals( "emitsport" ) ) )
		{
        	DOM_Element port = (const DOM_Element&)child;
            CORBA::Object_var dummy = getPort(port);
            source = Components::CCMObject::_narrow(dummy);
            std::string emit = emitsidentifier(port);
            DEBUG_OUT2( "\tport is ", emit );
                    
            //
            // connect
            //
      		try
      		{
       			source->connect_consumer(emit.c_str(), consumer);
       		}
       		catch(Components::InvalidName&)
       		{
       			DEBUG_OUT("invalid emits name");
       			throw Components::CreateFailure();
       		}
       		catch(Components::AlreadyConnected&)
            {
       			DEBUG_OUT("already connected");
       			throw Components::CreateFailure();
       		}
        }

        //
        // publishesport
		//
		if ((child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			(child.getNodeName().equals( "publishesport" ) ) )
		{
            DOM_Element port = (const DOM_Element&)child;
            CORBA::Object_var dummy = getPort(port);
            source = Components::CCMObject::_narrow(dummy);
            std::string publish = publishesidentifier(port);
            DEBUG_OUT2( "\tport is ", publish );

            //
            // connect
            //
            try
       		{
                // returns Cookie TODO
	   			source->subscribe(publish.c_str(), consumer);
	   		}
	   		catch( Components::InvalidName& )
	   		{
	   			DEBUG_OUT("invalid publish name");
	   			throw Components::CreateFailure();
	   		}
        }

        // get next child
        child = child.getNextSibling();
    }
}


/**
 * connect all component instances according to the assembly descriptor
 */
void
AssemblyImpl::connections ()
throw(Components::CreateFailure)
{
	DOM_NodeList aNodeList = document_.getDocumentElement().getElementsByTagName("connections");
	if (aNodeList.getLength() == 0)
	{
		return;
	}

	DOM_Node child = ((const DOM_Element&)aNodeList.item(0)).getFirstChild();
    while (child != 0)
    {
		//
		// connectinterface
		//
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "connectinterface" ) ) )
		{
			connectinterface((DOM_Element&)child);
		}

		//
		// connectevent
		//
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "connectevent" ) ) )
		{
            connectevent((DOM_Element&)child);
        }

        //
		// connecthomes
		//
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "connecthomes" ) ) )
		{
			// TODO
		}

        //
		// extension
		//
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "extension" ) ) )
		{
			// TODO
		}

		// get next connection element
		child = child.getNextSibling();
    }
}


/**
 * start all created component instances
 */
void
AssemblyImpl::configuration_complete ()
throw(Components::CreateFailure)
{
	//
	// use the startorder extension
	//
	DOM_Element anElement = document_.getDocumentElement();
	DOM_NodeList aNodeList = anElement.getElementsByTagName("extension");
	for (CORBA::ULong i = 0; i < aNodeList.getLength(); i++)
	{
		extension((const DOM_Element&)aNodeList.item(i));
	}

	//
	// call configuration complete for all remaining components
	//
   	Components::CCMObject_var comp;
	std::list < std::string > ::iterator iter;
	std::map < std::string, Components::CCMObject_var > ::iterator instanceIter;
	bool found = false;
	for( instanceIter = instanceMap_.begin(); instanceIter != instanceMap_.end(); instanceIter++ )
	{
		//
		// if not yet started, start it
		//
		for( iter = startOrder_.begin(); iter != startOrder_.end(); iter++ )
		{
			if( instanceIter->first == *iter )
			{
				found = true;
				break;
			}
		}

		if( !found )
		{
			DEBUG_OUT2( "\nAssembly: call configuration_complete to ", instanceIter->first );


			try
			{
				instanceIter->second->configuration_complete();
			}
			catch ( CORBA::Exception& ex )
			{
				DEBUG_OUT2("\nAssembly: EXCEPTION DURING configuration_complete : ", ex );
                throw Components::CreateFailure();
			}
			catch ( ... )
			{
				DEBUG_OUT("\nAssembly: UNKNOWN EXCEPTION DURING configuration_complete" );
                throw Components::CreateFailure();
			}
		}
	}

	// set assembly state to active
	state_ = Components::Deployment::INSERVICE;
}


/**
 * build the assembly
 */
void
AssemblyImpl::build
()
throw( Components::CreateFailure )
{
	DEBUG_OUT2("\nAssembly: starting assembly for ", package_->getName());

    //
	// find and extract the assembly descriptor
    //
	std::string cadfile = package_->getFileNameWithSuffix( ".cad" );
    if ( cadfile == std::string( "" ) )
	{
		std::cerr << "The format of the package file is not correct\n";
        throw Components::CreateFailure();
	}
    if ( package_->extractFile( cadfile, pathname_ + cadfile ) != 0 )
	{
		std::cerr << "Error during extracting the descriptor file\n";
        throw Components::CreateFailure();
	}

	//
	// parse the descriptor file
    //
	cadParser_ = new DOMXMLParser();
	char* xmlfile = strdup((pathname_ + cadfile).c_str());
    if (cadParser_->parse(xmlfile) != 0) 
	{
		std::cerr << "Error during XML parsing\n";
        delete(cadParser_);
        throw Components::CreateFailure();
	}
	document_ = cadParser_->getDocument();

	// install all necessary implementations
	install();

	// instantiate all components
	instantiate();

	// make connections
	connections();

	// start components
	configuration_complete();
    
	DEBUG_OUT3("\nAssembly: Assembly for ", package_->getName(), " is running !");

    // remove assembly descriptor
    removeFileOrDirectory(pathname_ + cadfile);
}


/**
 * tear down the assembly
 */
void 
AssemblyImpl::tear_down ()
throw( Components::RemoveFailure )
{
	//
	// use reverse start order to remove components
	//
	startOrder_.reverse();
	std::list < std::string > ::iterator iter;
	std::map < std::string, Components::CCMObject_var > ::iterator instanceIter;
	Components::CCMObject_var comp;
	for( iter = startOrder_.begin(); iter != startOrder_.end(); iter++ )
	{
		instanceIter = instanceMap_.find( *iter );
		if( instanceIter != instanceMap_.end() )
		{
			DEBUG_OUT2("\nAssembly: call remove to ", instanceIter->first );

			comp = Components::CCMObject::_duplicate( instanceIter->second );

			try
			{
				comp->remove();
			}
			catch (CORBA::Exception&)
			{
				DEBUG_OUT2("Assembly: EXCEPTION DURING removal of ", instanceIter->first);
				instanceMap_.erase( instanceIter );
                continue;
			}
			
			DEBUG_OUT3("Assembly: ", instanceIter->first, " removed!");

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
		DEBUG_OUT2("\nAssembly: call remove to ", instanceIter->first);

		try
		{
			instanceIter->second->remove();
		}
		catch (CORBA::Exception&)
		{
			DEBUG_OUT2("Assembly: EXCEPTION DURING removal of ", instanceIter->first);
			continue;
		}

		DEBUG_OUT3("Assembly: ", instanceIter->first, " removed!");
	}

	instanceMap_.clear();

	DEBUG_OUT("\nAssembly: Assembly is teared down!");
}


/**
 * return the state of the assembly
 */
Components::Deployment::AssemblyState 
AssemblyImpl::get_state ()
{
	return state_;
}


} // namespace
