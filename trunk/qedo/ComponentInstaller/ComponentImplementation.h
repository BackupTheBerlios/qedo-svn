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

#ifndef __COMPONENT_IMPLEMENTATION_H__
#define __COMPONENT_IMPLEMENTATION_H__


#include <CORBA.h>
#include "QedoComponents.h"
#include "NameServiceBase.h"
#include "PlatformBase.h"
#include "ComponentImplementationData.h"

#ifdef _WIN32
#include <windows.h>
#define DLL_EXT "dll"
#else
#include <unistd.h>
#include <sys/wait.h>
#define DLL_EXT "so"
#endif

#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#if !defined(UNUSED) 
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif


#define COMPONENT_INSTALLATION_CONTEXT "Qedo/ComponentInstallation/"


namespace Qedo {


/**
 * @addtogroup Deployment Component Deployment Support
 * @{
 */


/**
 * @defgroup ComponentInstaller Component Installer
 * bla.
 * @{
 */


extern std::string g_qedo_dir;


/**
 * represents a component implementation
 */
class ComponentImplementation : public virtual PlatformBase
							  , public virtual NameServiceBase	
{
	/** makes use of this */
	friend class ComponentInstallationImpl;

private:
    
	/** the data */
	ComponentImplementationData			data_;

	/** build dir of the component implementation */
	std::string							build_dir_;
    /** build path of the component implementation */
	std::string							build_path_;
	/** dir of the component implementation */
	std::string							installation_dir_;
    /** path of the component implementation */
	std::string							installation_path_;
    /** the path of the makefile */
	std::string							makefile_;
    
    /** the package */
	std::string							package_;
	/** the installation counter */
    int									installation_count_;
	
    /** the package */
	std::string							deployment_dir_;

	/**
	 * install all subcomponents in case of assembly
	 */
	void installAssembly()
		throw(Components::CreateFailure);

    /**
	 * install code (for servants, executor, artifacts)
	 */
    void installCode()
        throw(Components::CreateFailure);

	/**
	 * build servant code
	 */
	void buildServants()
		throw(Components::CreateFailure);

public:

	/**
	 * constructor
	 * constructs a new implementation
	 * \param data The data of the implementation.
	 * \param package The package of the component implementation.
	 */
	ComponentImplementation(ComponentImplementationData data,
							std::string package,
							CosNaming::NamingContext_ptr nameContext);

	/**
	 * destructor
	 */
	~ComponentImplementation();

	/**
	 * comparison
	 */
    bool operator == ( ComponentImplementation );

	/**
	 * install a component implementation
	 */
	void install()
		throw( Components::CreateFailure );

	/**
	 * uninstall a component implementation
	 */
    void uninstall()
		throw( Components::RemoveFailure );

	/**
	 * get the data of the implementation
	 */
    ComponentImplementationData getData();
};

/** @} */

/** @} */

}

#endif
