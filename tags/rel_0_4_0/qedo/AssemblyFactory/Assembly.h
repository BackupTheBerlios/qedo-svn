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


struct ComponentInstanceData
{
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** component properties */
	std::string									comp_prop;
};


struct HomeInstanceData
{
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** implementation package */
	std::string									file;
	/** implementation id */
	std::string									impl_id;
	/** destination */
	std::string									dest;
	/** registration with homefinder */
	std::string									finder;
	/** registration with naming service */
	std::string									naming;
	/** registration with trading service */
	std::string									trader;
	/** home properties */
	std::string									home_prop;
	/** component properties */
	std::string									comp_prop;
	/** list of component instances */
	std::vector < ComponentInstanceData >		instances;
	/** container of the home */
	Components::Deployment::Container_var		container;
};


struct ProcessData
{
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** destination host */
	std::string									host;
	/** list of home instances */
	std::vector < HomeInstanceData >			homes;
	/** component server */
	Components::Deployment::ComponentServer_var	server;
};


struct HostData
{
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** destination host */
	std::string									host;
	/** list of processes */
	std::vector < ProcessData >					processes;
};


enum ReferenceKind { COMPONENTID, HOMEID, NAMING, OBJECTREF, TRADER, FINDER };
struct ReferenceData
{
	/** reference kind */
	ReferenceKind								kind;
	/** reference name */
	std::string									name;
};


struct PortData
{
	/** port name */
	std::string									name;
	/** port reference */
	ReferenceData								ref;
};


struct InterfaceConnectionData
{
	/** use port */
	PortData									use;
	/** provided interface */
	PortData									provide;
};


enum EventConnectionKind { EMITTER, PUBLISHER };
struct EventConnectionData
{
	/** consumer port */
	PortData									consumer;
	/** connection kind */
	EventConnectionKind							kind;
	/** emitter or publisher*/
	PortData									emitter;
};


/**
 * the implementation of the assembly interface
 */
class AssemblyImpl : public virtual POA_Components::Deployment::Assembly,
					 public virtual PortableServer::RefCountServantBase,
                     public virtual NameServiceBase,
                     public virtual PlatformBase
{

	friend class CADReader;

private:

	/** the uuid of the assembly */
	std::string									uuid_;
    /** path name of the assembly package */
	std::string									pathname_;
    /** the package object */
    Package*									package_;
    /** the state of the assembly */
	Components::Deployment::AssemblyState		state_;
    /** the cookie of the assembly, to be used by the AssemblyFactory */
	Cookie_impl*								cookie_;
	
    /** the dom document of the assembly description */
	DOMDocument* document_;
	
    /** the mapping of component implementation ids to softpackages */
	std::map < std::string, std::string >				implementationMap_;
    /** the mapping of component instance ids to objects */
	std::map < std::string, Components::CCMObject_var > instanceMap_;
    /** the mapping of home instance ids to objects */
	std::map < std::string, Components::CCMHome_var >	homeMap_;
    /** start order of the instances */
	std::list < std::string >							start_order_;
	/** list of existing homes */
	std::vector < HomeInstanceData >					existing_homes_;
	/** list of server/process/home instantiations */
	std::vector < HostData >							hosts_;
	/** list of interface connections */
	std::vector < InterfaceConnectionData >				interface_connections_;
	/** list of event connections */
	std::vector < EventConnectionData >					event_connections_;

private:

    // create new component server
    Components::Deployment::ComponentServer_ptr createComponentServer (std::string)
        throw(Components::CreateFailure);

    // create new container
    Components::Deployment::Container_ptr createContainer (Components::Deployment::ComponentServer_ptr)
        throw(Components::CreateFailure);

	/**
	 * instantiate components of a home
	 */
    void instantiateComponents (Components::CCMHome_ptr, HomeInstanceData)
        throw(Components::CreateFailure);

    /**
	 * instantiate home
	 */
    Components::CCMHome_ptr instantiateHome (Components::Deployment::Container_ptr, HomeInstanceData)
        throw(Components::CreateFailure);

	/**
	 * get component installation
	 */
	Qedo_Components::Deployment::ComponentInstallation_ptr getComponentInstallation(std::string host)
		throw(Components::CreateFailure);

	/**
	 * get the named component instance
	 */
    Components::CCMObject_ptr getInstance (std::string)
        throw(Components::CreateFailure);

	/**
	 * get the named home instance
	 */
	Components::CCMHome_ptr getHomeInstance (std::string name)
		throw(Components::CreateFailure);

    /**
	 * get reference
	 */
    CORBA::Object_ptr getRef (ReferenceData)
        throw(Components::CreateFailure);

	/**
	 * install all component implementations referred to in the assembly descriptor
	 */
	void install()
		throw(Components::CreateFailure);

	/**
	 * install a component implementation
	 */
	void
	installComponent (Qedo_Components::Deployment::ComponentInstallation_ptr, HomeInstanceData)
		throw(Components::CreateFailure);

	/**
	 * create all component instances defined in the assembly descriptor
	 */
	void instantiate()
		throw(Components::CreateFailure);

    /**
	 * make interface connections
	 */
    void connectinterface()
        throw(Components::CreateFailure);

    /**
	 * make event connections
	 */
    void connectevent()
        throw(Components::CreateFailure);

	/**
	 * make all connections according to the assembly descriptor
	 */
	void connect()
		throw(Components::CreateFailure);

	/**
	 * start all created component instances
	 */
	void configurationComplete()
        throw(Components::CreateFailure);


public:
	/**
	 * constructor
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

