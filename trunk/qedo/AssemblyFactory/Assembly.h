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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#include <CORBA.h>
#include "QedoComponents_skel.h"
#include "Valuetypes.h"
#include "StandardConfigurator.h"
#include "NameServiceBase.h"
#include "PlatformBase.h"
#include "AssemblyData.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>
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
	                 public virtual PortableServer::RefCountServantBase,
                     public virtual NameServiceBase,
                     public virtual PlatformBase
{
private:

	/** the data */
	AssemblyData										data_;
    /** path name of the assembly package */
	std::string											pathname_;
    /** the assembly package */
    std::string											package_;
    /** the state of the assembly */
	Components::Deployment::AssemblyState				state_;
    /** the cookie of the assembly, to be used by the AssemblyFactory */
	Cookie_impl*										cookie_;
    /** the mapping of component instance ids to objects */
	std::map < std::string, Components::CCMObject_var > instanceMap_;
    /** the mapping of home instance ids to objects */
	std::map < std::string, Components::CCMHome_var >	homeMap_;

	/** the mutex that prohibits multiple threads from calling assembly CORBA operatione */
	QedoMutex											assembly_mutex_;

    /**
	 * create new component server
	 */
    Components::Deployment::ComponentServer_ptr createComponentServer (DestinationData)
        throw(Components::CreateFailure);

    /**
	 * create new container
	 */
    Components::Deployment::Container_ptr createContainer
		(Components::Deployment::ComponentServer_ptr, const ::Components::ConfigValues&)
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
	Components::Deployment::ExtComponentInstallation_ptr getComponentInstallation(DestinationData host)
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
	 * uninstall all component implementations referred to in the assembly descriptor
	 */
	void uninstall()
		throw(Components::RemoveFailure);

	/**
	 * install all component implementations referred to in the assembly descriptor
	 */
	void install()
		throw(Components::CreateFailure);

	/**
	 * install a component implementation
	 */
	void
	installComponent (Components::Deployment::ExtComponentInstallation_ptr, HomeInstanceData)
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

#ifndef _QEDO_NO_STREAMS
	/**
	 * make stream connections
	 */
	void connectstream()
		throw(Components::CreateFailure);
#endif

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

	/**
	 * provide the cookie value
	 */
    std::string get_cookie() const;

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

