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


namespace Qedo {


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


AssemblyImpl::~AssemblyImpl ()
{
}


std::string 
AssemblyImpl::get_uuid () const
{
    return uuid_;
}


bool 
AssemblyImpl::operator == (Components::Cookie* cook)
{
	return cookie_->equal(cook);
}


void
AssemblyImpl::registerWithNaming (DOMElement* element, CORBA::Object_ptr obj)
{
	std::string binding = XMLString::transcode(element->getAttribute(X("name")));
    registerName(binding, obj, true);
}


void
AssemblyImpl::registerComponent (DOMElement* element, CORBA::Object_ptr obj)
{
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			//
			// emitsidentifier
			//
			if(!XMLString::compareString(child->getNodeName(), X("emitsidentifier")))
			{
				// TODO
			}

			//
			// providesidetifier
			//
			if(!XMLString::compareString(child->getNodeName(), X("providesidetifier")))
			{
				// TODO
			}

			//
			// publishesidentifier
			//
			if(!XMLString::compareString(child->getNodeName(), X("publishesidentifier")))
			{
				// TODO
			}

			//
			// registerwithnaming
			//
			if(!XMLString::compareString(child->getNodeName(), X("registerwithnaming")))
			{
				registerWithNaming((DOMElement*)child, obj);
			}

			//
			// registerwithtrader
			//
			if(!XMLString::compareString(child->getNodeName(), X("registerwithtrader")))
			{
				// TODO
			}
		}

        // get next child element
		child = child->getNextSibling();
    }
}


void
AssemblyImpl::extension (DOMElement* ext)
throw( Components::CreateFailure )
{
	std::string class_attr = XMLString::transcode(ext->getAttribute(X("class")));
	
    //
    // startorder
    //
    if( class_attr == "startorder" )
	{
		std::string comp_id = XMLString::transcode(ext->getFirstChild()->getNodeValue());
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


std::string
AssemblyImpl::destination (DOMElement* homeplacement)
throw(Components::CreateFailure)
{
	DOMNodeList* nodeList = homeplacement->getElementsByTagName(X("destination"));
	if (nodeList->getLength() != 1)
	{
		DEBUG_OUT2("\nAssembly: not exactly one destination element for ", XMLString::transcode(homeplacement->getAttribute(X("id"))));
		throw Components::CreateFailure();
	}

	std::string name;
    DOMNode* dest = ((DOMElement*)nodeList->item(0))->getFirstChild();
    if (dest != 0)
    {
        name = XMLString::transcode(dest->getNodeValue());
        return name;
    }

    // destination was empty
    char hostname[256];
	gethostname(hostname, 256);
    name = hostname;
    return name;
}


std::string
AssemblyImpl::componentfileref (DOMElement* homeplacement)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = homeplacement->getElementsByTagName(X("componentfileref"));
    if (nodeList->getLength() != 1)
	{
		DEBUG_OUT2("\nAssembly: not exactly one componentfileref element for ", homeplacement->getAttribute(X("id")));
		throw Components::CreateFailure();
	}
	DOMElement* fileElement = (DOMElement*)nodeList->item(0);
	std::string id = XMLString::transcode(fileElement->getAttribute(X("idref")));
    return id;
}


std::string
AssemblyImpl::componentimplref (DOMElement* homeplacement)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = homeplacement->getElementsByTagName(X("componentimplref"));
    if (nodeList->getLength() != 1)
	{
		DEBUG_OUT2("\nAssembly : missing componentimplref element for ", homeplacement->getAttribute(X("id")));
		throw Components::CreateFailure();
	}
	DOMElement* fileElement = (DOMElement*)nodeList->item(0);
	std::string id = XMLString::transcode(fileElement->getAttribute(X("idref")));
    return id;
}


std::string
AssemblyImpl::usesidentifier (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("usesidentifier"));
    if (nodeList->getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing usesidentifier element");
		throw Components::CreateFailure();
	}
	DOMElement* elem = (DOMElement*)nodeList->item(0);
	std::string receptacle = XMLString::transcode(elem->getFirstChild()->getNodeValue());

    return receptacle;
}


std::string
AssemblyImpl::providesidentifier (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("providesidentifier"));
    if (nodeList->getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing providesidentifier element");
		throw Components::CreateFailure();
	}
	DOMElement* elem = (DOMElement*)nodeList->item(0);
	std::string facet = XMLString::transcode(elem->getFirstChild()->getNodeValue());

    return facet;
}


std::string
AssemblyImpl::consumesidentifier (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("consumesidentifier"));
    if (nodeList->getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing consumesidentifier element");
		throw Components::CreateFailure();
	}
	DOMElement* elem = (DOMElement*)nodeList->item(0);
	std::string name = XMLString::transcode(elem->getFirstChild()->getNodeValue());

    return name;
}


std::string
AssemblyImpl::emitsidentifier (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("emitsidentifier"));
    if (nodeList->getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing emitsidentifier element");
		throw Components::CreateFailure();
	}
	DOMElement* elem = (DOMElement*)nodeList->item(0);
	std::string name = XMLString::transcode(elem->getFirstChild()->getNodeValue());

    return name;
}


std::string
AssemblyImpl::publishesidentifier (DOMElement* element)
throw(Components::CreateFailure)
{
    DOMNodeList* nodeList = element->getElementsByTagName(X("publishesidentifier"));
    if (nodeList->getLength() != 1)
	{
		DEBUG_OUT("\nAssembly : missing publishesidentifier element");
		throw Components::CreateFailure();
	}
	DOMElement* elem = (DOMElement*)nodeList->item(0);
	std::string name = XMLString::transcode(elem->getFirstChild()->getNodeValue());

    return name;
}


CORBA::Object_ptr
AssemblyImpl::getPort (DOMElement* port)
throw(Components::CreateFailure)
{
    CORBA::Object_var obj;
    std::string name;
    DOMNode* child = port->getFirstChild();
	while (child != 0)
	{
		//
		// componentinstantiationref
		//
		if((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		   (!XMLString::compareString(child->getNodeName(), X("componentinstantiationref"))))
		{
			DOMElement* componentinstantiationref = (DOMElement*)child;
			name = XMLString::transcode(componentinstantiationref->getAttribute(X("idref")));
            obj = getInstance(name);
            break;
		}
	
		//
		// findby
		//
		if((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		   (!XMLString::compareString(child->getNodeName(), X("findby"))))
		{
            DOMNode* find_child = ((DOMElement*)child)->getFirstChild();
	        while (find_child != 0)
	        {
                //
		        // namingservice
		        //
		        if((find_child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		           (!XMLString::compareString(find_child->getNodeName(), X("namingservice"))))
		        {
                    name = XMLString::transcode(((DOMElement*)find_child)->getAttribute(X("name")));
                    obj = resolveName(name);
                    if ( CORBA::is_nil(obj))
                    {
                        throw Components::CreateFailure();
                    }
                    break;
                }

                //
		        // stringifiedobjectref
		        //
		        if((find_child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		           (!XMLString::compareString(find_child->getNodeName(), X("stringifiedobjectref"))))
		        {
                    // TODO
                }

                //
		        // traderquery
		        //
		        if((find_child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		           (!XMLString::compareString(find_child->getNodeName(), X("traderquery"))))
		        {
                    // TODO
                }

                //
		        // homefinder
		        //
		        if((find_child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		           (!XMLString::compareString(find_child->getNodeName(), X("homefinder"))))
		        {
                    // TODO
                }

                //
		        // extension
		        //
		        if((find_child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		           (!XMLString::compareString(find_child->getNodeName(), X("extension"))))
		        {
                    // TODO
                }

                // get next child
		        find_child = find_child->getNextSibling();
            }
		}

		// get next child
		child = child->getNextSibling();
	}

    //
    // usesport
    //
    if (!XMLString::compareString(port->getNodeName(), X("usesport")))
	{
        DEBUG_OUT2("\tuser is ", name);
        return obj._retn();
    }

    //
    // providesport
    //
    if (!XMLString::compareString(port->getNodeName(), X("providesport")))
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
    if (!XMLString::compareString(port->getNodeName(), X("consumesport")))
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
    if (!XMLString::compareString(port->getNodeName(), X("emitsport")))
	{
        DEBUG_OUT2("\temitter is ", name);
        return obj._retn();
    }

    //
    // publishesport
    //
    if (!XMLString::compareString(port->getNodeName(), X("publishesport")))
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
    if ( CORBA::is_nil(obj))
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
	config.inout()[0] = new ConfigValue_impl("CONTAINER_TYPE", any);

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


void
AssemblyImpl::installImplementation (DOMElement* homeplacement)
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
    if ( CORBA::is_nil(obj))
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


void
AssemblyImpl::install ()
throw( Components::CreateFailure )
{
	//
	// map uuid to package and extract all packages
	//
	DOMElement* document = document_->getDocumentElement();
	DOMNodeList* aNodeList;
	aNodeList = document->getElementsByTagName(X("componentfiles"));
	if ( aNodeList->getLength() != 1 )
	{
		DEBUG_OUT2("\nAssembly: there must be one componentfiles element in ", package_->getName());
		throw Components::CreateFailure();
	}

	DOMElement* anElement;
	anElement = (DOMElement*)aNodeList->item( 0 );
	aNodeList = anElement->getElementsByTagName(X("componentfile"));
	for(CORBA::ULong i = 0; i < aNodeList->getLength(); i++ )
	{
		anElement = (DOMElement*)aNodeList->item( i );
		std::string id = XMLString::transcode(anElement->getAttribute(X("id")));
		DOMNodeList* fileNodeList = anElement->getElementsByTagName(X("fileinarchive"));
		anElement = (DOMElement*)fileNodeList->item( 0 );
		std::string package = XMLString::transcode(anElement->getAttribute(X("name")));
		
		
		// extract package
		package_->extractFile( package, pathname_ + package );
		
		
		// map uuid to package
		implementationMap_[id] = package;
	}

	//
	// install component implementations for all homeplacements
	//
	aNodeList = document->getElementsByTagName(X("partitioning"));
	anElement = (DOMElement*)aNodeList->item( 0 );
	DOMNode* partition_child = anElement->getFirstChild();
	while (partition_child != 0)
	{
		//
		// processcollocation
		//
		if( ( partition_child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(partition_child->getNodeName(), X("processcollocation"))))
		{
			aNodeList = ((DOMElement*)partition_child)->getElementsByTagName(X("homeplacement"));
			for(CORBA::ULong i = 0; i < aNodeList->getLength(); i++ )
			{
				installImplementation((DOMElement*)aNodeList->item(i));
			}
		}
	
		//
		// homeplacement
		//
		if( ( partition_child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(partition_child->getNodeName(), X("homeplacement"))))
		{
            installImplementation((DOMElement*)partition_child);
		}

		// get next partition element
		partition_child = partition_child->getNextSibling();
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


void
AssemblyImpl::instantiateComponent (DOMElement* instance, Components::CCMHome_ptr home)
throw(Components::CreateFailure)
{
	DEBUG_OUT2 ("\nAssembly: create new Component : ", XMLString::transcode(instance->getAttribute(X("id"))));

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
	instanceMap_[XMLString::transcode(instance->getAttribute(X("id")))] = Components::CCMObject::_duplicate(comp);

    DOMNode* child = instance->getFirstChild();
	std::string property_descriptor = "";
	while( child != 0 )
	{
		//
		// property configuration
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("componentproperties"))))
		{
			DOMNode* location = child->getFirstChild();
			while( location != 0 )
			{
				if( ( location->getNodeType() == DOMNode::ELEMENT_NODE ) &&
					( !XMLString::compareString(location->getNodeName(), X("fileinarchive"))))
				{
					property_descriptor = XMLString::transcode(((DOMElement*)location )->getAttribute(X("name")));
				}

				
				if( ( location->getNodeType() == DOMNode::ELEMENT_NODE ) &&
					( !XMLString::compareString(location->getNodeName(), X("codebase"))) )
				{
					// TODO
				}

				// next element in componentproperties
				location = location->getNextSibling();
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
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
			(!XMLString::compareString(child->getNodeName(), X("registercomponent"))))
		{
            registerComponent((DOMElement*)child, comp);
        }

		// next element in componentinstantiation
		child = child->getNextSibling();
	}
}


void
AssemblyImpl::processcollocation (DOMElement* element)
throw(Components::CreateFailure)
{
    Components::Deployment::ComponentServer_var component_server;
	Components::Deployment::Container_var container;

    //
	// get a homeplacement to determine destination
	//
	DOMNodeList* nodeList = element->getElementsByTagName(X("homeplacement"));
	if (nodeList->getLength() == 0)
	{
		DEBUG_OUT2("\nAssembly: no homeplacements in processcollocation in ", package_->getName());
		return;
	}

	// create new Component Server
    component_server = createComponentServer(destination((DOMElement*)nodeList->item(0)));

	// create new Container
    container = createContainer(component_server);

	//
    // create new homes and instances
	//
	for (CORBA::ULong i = 0; i < nodeList->getLength(); i++)
	{
		homeplacement((DOMElement*)nodeList->item(i), container); // !!!!!!!! var type
	}
}


void
AssemblyImpl::homeplacement (DOMElement* element, Components::Deployment::Container_ptr contain)
throw(Components::CreateFailure)
{
    Components::Deployment::Container_var container = Components::Deployment::Container::_duplicate(contain);
	Components::CCMHome_var home;

	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		//
		// componentfileref
		//
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
			(!XMLString::compareString(child->getNodeName(), X("componentfileref"))))
        {
            std::string idref = XMLString::transcode(((DOMElement*)child)->getAttribute(X("idref")));
            if (idref != "")
            {
                if ( CORBA::is_nil( container))
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
                homeMap_[XMLString::transcode(((DOMElement*)element)->getAttribute(X("id")))] = 
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
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
			(!XMLString::compareString(child->getNodeName(), X("registerwithnaming"))))
        {
            registerWithNaming((DOMElement*)child, home);
        }

        //
		// componentinstantiation
		//
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
			(!XMLString::compareString(child->getNodeName(), X("componentinstantiation"))))
        {
		    instantiateComponent((DOMElement*)child, home);
        }

        // get next child
		child = child->getNextSibling();
	}
}


void
AssemblyImpl::instantiate ()
throw(Components::CreateFailure)
{
	DOMNodeList* aNodeList = document_->getDocumentElement()->getElementsByTagName(X("partitioning"));
	if (aNodeList->getLength() != 1)
	{
		DEBUG_OUT2("XMLParser : missing partitioning element in ", package_->getName());
		throw Components::CreateFailure();
	}

	DOMNode* child = ((DOMElement*)aNodeList->item(0))->getFirstChild();
	while (child != 0)
	{
		//
		// processcollocation
		//
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
			(!XMLString::compareString(child->getNodeName(), X("processcollocation"))))
		{
			processcollocation((DOMElement*)child);
		}

		//
		// homeplacement
		//
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
			(!XMLString::compareString(child->getNodeName(), X("homeplacement"))))
		{
			homeplacement((DOMElement*)child, 0);
		}

        //
		// extension
		//
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
			(!XMLString::compareString(child->getNodeName(), X("extension"))))
		{
            extension((DOMElement*)child);
        }

		// get next child
		child = child->getNextSibling();
	}
}


void
AssemblyImpl::connectinterface (DOMElement* element)
throw(Components::CreateFailure)
{
	DEBUG_OUT("\nAssembly: make connection");

    Components::CCMObject_var user;
    std::string receptacle;
    CORBA::Object_var used;
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
        //
	    // usesport
		//
		if((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		   (!XMLString::compareString(child->getNodeName(), X("usesport"))))
		{
		    DOMElement* port = (DOMElement*)child;
            CORBA::Object_var dummy = getPort(port);
            user = Components::CCMObject::_narrow(dummy);
            receptacle = usesidentifier(port);
            DEBUG_OUT2( "\treceptacle is ", receptacle );
        }

        //
        // providesport etc
        //
		if((child->getNodeType() == DOMNode::ELEMENT_NODE) &&
		   (!XMLString::compareString(child->getNodeName(), X("providesport")) ||
            !XMLString::compareString(child->getNodeName(), X("componentsupportedinterface")) ||
            !XMLString::compareString(child->getNodeName(), X("existinginterface")) ||
            !XMLString::compareString(child->getNodeName(), X("homeinterface"))))
		{
            used = getPort((DOMElement*)child);
        }

        // next child
        child = child->getNextSibling();
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


void
AssemblyImpl::connectevent (DOMElement* element)
throw(Components::CreateFailure)
{
    DEBUG_OUT( "\nAssembly: make event connection" );
			
    Components::EventConsumerBase_var consumer;
    Components::CCMObject_var source;
    DOMNode* child = element->getFirstChild();
    while (child != 0)
    {
	    //
		// consumesport
		//
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
		    (!XMLString::compareString(child->getNodeName(), X("consumesport" ))))
		{
            CORBA::Object_var dummy = getPort((DOMElement*)child);
            consumer = Components::EventConsumerBase::_narrow(dummy);
        }

        //
        // emitsport
        //
        if ((child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			(!XMLString::compareString(child->getNodeName(), X("emitsport" ))))
		{
        	DOMElement* port = (DOMElement*)child;
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
		if ((child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			(!XMLString::compareString(child->getNodeName(), X("publishesport" ))))
		{
            DOMElement* port = (DOMElement*)child;
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
        child = child->getNextSibling();
    }
}


void
AssemblyImpl::connections ()
throw(Components::CreateFailure)
{
	DOMNodeList* aNodeList = document_->getDocumentElement()->getElementsByTagName(X("connections"));
	if (aNodeList->getLength() == 0)
	{
		return;
	}

	DOMNode* child = ((DOMElement*)aNodeList->item(0))->getFirstChild();
    while (child != 0)
    {
		//
		// connectinterface
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("connectinterface" ))))
		{
			connectinterface((DOMElement*)child);
		}

		//
		// connectevent
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("connectevent" ))))
		{
            connectevent((DOMElement*)child);
        }

        //
		// connecthomes
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("connecthomes" ))))
		{
			// TODO
		}

        //
		// extension
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("extension" ))))
		{
			// TODO
		}

		// get next connection element
		child = child->getNextSibling();
    }
}


void
AssemblyImpl::configuration_complete ()
throw(Components::CreateFailure)
{
	//
	// use the startorder extension
	//
	DOMElement* anElement = document_->getDocumentElement();
	DOMNodeList* aNodeList = anElement->getElementsByTagName(X("extension"));
	for (CORBA::ULong i = 0; i < aNodeList->getLength(); i++)
	{
		extension((DOMElement*)aNodeList->item(i));
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


Components::Deployment::AssemblyState 
AssemblyImpl::get_state ()
throw(CORBA::SystemException)
{
	return state_;
}


} // namespace
