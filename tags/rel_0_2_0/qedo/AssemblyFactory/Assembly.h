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

#ifndef __ASSEMBLY_H__
#define __ASSEMBLY_H__


#include <CORBA.h>
#include "QedoComponents_skel.h"
#include "Valuetypes.h"
#include "Package.h"
#include "Properties.h"
#include "StandardConfigurator.h"
#include "DOMXMLParser.h"
#include "NameServiceBase.h"
#include "PlatformBase.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <sys/types.h>
#include <sys/stat.h>


namespace Qedo {


/**
 * @addtogroup Deployment Component Deployment Support
 * @{
 */


/**
 * @defgroup Assembly Assembly and AssemblyFactory
 * bla
 * @{
 */


#define COMPONENT_INSTALLATION_CONTEXT "Qedo/ComponentInstallation/"
#define SERVER_ACTIVATOR_CONTEXT "Qedo/Activators/"


/**
 * the implementation of the assembly interface
 */
class AssemblyImpl : public virtual POA_Components::Deployment::Assembly,
                     public virtual NameServiceBase,
                     public virtual PlatformBase
{

private:
	/** the uuid of the assembly */
	std::string uuid_;
	
    /** path name of the assembly package */
	std::string pathname_;
    
    /** the package object */
    Package* package_;
	
    /** the state of the assembly */
	Components::Deployment::AssemblyState state_;
	
    /** the cookie of the assembly, to be used by the AssemblyFactory */
	Cookie_impl* cookie_;
	
    /** the xml parser */
	DOMXMLParser* cadParser_;
	
    /** the dom document of the assembly description */
	DOMDocument* document_;
	
    /** the mapping of component implementation ids to softpackages */
	std::map < std::string, std::string > implementationMap_;
	
    /** the mapping of component instance ids to objects */
	std::map < std::string, Components::CCMObject_var > instanceMap_;
    
    /** the mapping of home instance ids to objects */
	std::map < std::string, Components::CCMHome_var > homeMap_;
	
    /** start order of the instances */
	std::list < std::string > startOrder_;

private:
    /**
	 * handle extension elements
	 */
    void extension (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * get the named component instance
	 */
    Components::CCMObject_ptr getInstance (std::string)
        throw(Components::CreateFailure);

    // create new component server
    Components::Deployment::ComponentServer_ptr createComponentServer (std::string)
        throw(Components::CreateFailure);

    // create new container
    Components::Deployment::Container_ptr createContainer (Components::Deployment::ComponentServer_ptr)
        throw(Components::CreateFailure);

    /**
	 * create new home
	 */
    Components::CCMHome_ptr createHome (Components::Deployment::Container_ptr, std::string)
        throw(Components::CreateFailure);

    /**
	 * return the destination for placement,
	 * if destination is empty, return the local hostname (for convenience)
	 */
	std::string destination (DOMElement*)
        throw(Components::CreateFailure);

    // get reference for port
    CORBA::Object_ptr getPort (DOMElement*)
        throw(Components::CreateFailure);

    // get componentfileref for home
	std::string componentfileref (DOMElement*)
        throw(Components::CreateFailure);

    // get componentimplref for home
	std::string componentimplref (DOMElement*)
        throw(Components::CreateFailure);

    // get usesidentifier for port
	std::string usesidentifier (DOMElement*)
        throw(Components::CreateFailure);

    // get providesidentifier for port
	std::string providesidentifier (DOMElement*)
        throw(Components::CreateFailure);

    // get consumesidentifier for port
	std::string consumesidentifier (DOMElement*)
        throw(Components::CreateFailure);

    // get emitsidentifier for port
	std::string emitsidentifier (DOMElement*)
        throw(Components::CreateFailure);

    // get publishesidentifier for port
	std::string publishesidentifier (DOMElement*)
        throw(Components::CreateFailure);

    // register in NS
    void registerWithNaming (DOMElement*, CORBA::Object_ptr);

    // register component
    void registerComponent (DOMElement*, CORBA::Object_ptr);

    // install a component
    void installImplementation (DOMElement*)
        throw(Components::CreateFailure);

	/**
	 * install all component implementations referred to in the assembly descriptor
	 */
	void install()
		throw(Components::CreateFailure);

	/**
	 * instantiate a component according to the xml element in the assembly descriptor
	 */
	void instantiateComponent (DOMElement*, Components::CCMHome_ptr)
		throw(Components::CreateFailure);

    // processcollocation
    void processcollocation (DOMElement*)
        throw(Components::CreateFailure);

    // homeplacement
    void homeplacement (DOMElement*, Components::Deployment::Container_ptr)
        throw(Components::CreateFailure);

	/**
	 * create all component instances defined in the assembly descriptor
	 */
	void instantiate ()
		throw(Components::CreateFailure);

    /**
	 * connect interfaces
	 */
    void connectinterface (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * connect events
	 */
    void connectevent (DOMElement*)
        throw(Components::CreateFailure);

	/**
	 * connect all component instances according to the assembly descriptor
	 */
	void connections ()
		throw(Components::CreateFailure);

	/**
	 * start all created component instances
	 */
	void configuration_complete ()
        throw(Components::CreateFailure);


public:
	/**
	 * consructor
	 * \param package The package of the assembly.
	 * \param cookie The cookie of the assembly (from AssemblyFactory).
	 * \param nameContext The naming service.
	 */
    AssemblyImpl( std::string package, Cookie_impl* cookie, CosNaming::NamingContext_ptr nameContext);

	/**
	 * desctructor
	 */
	virtual ~AssemblyImpl();

	/**
	 * provide the uuid
	 */
    std::string get_uuid() const;

	bool operator == ( Components::Cookie* );

    /**
	 * implements IDL:omg.org/Components/Deployment/Assembly/build:1.0
	 * build the assembly
	 */
    void build()
		throw( Components::CreateFailure );

    /**
     * implements IDL:omg.org/Components/Deployment/Assembly/tear_down:1.0
	 * tear down the assembly
	 */
    void tear_down()
		throw( Components::RemoveFailure );

    /**
	 * implements IDL:omg.org/Components/Deployment/Assembly/get_state:1.0
	 * return the state of the assembly
	 */
    Components::Deployment::AssemblyState get_state()
		throw( CORBA::SystemException );
};

/** @} */

/** @} */

}

#endif

