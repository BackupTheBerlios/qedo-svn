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
#include "Components.h"
#include "Package.h"
#include "PlatformBase.h"
//#include "RefCountBase.h"

#ifdef _WIN32
#include <windows.h>
#define DLL_EXT "dll"
#else
#include <unistd.h>
#include <sys/wait.h>
#define DLL_EXT "so"
#endif

#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

#if !defined(UNUSED) && defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

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


struct ValuetypeData
{
	std::string								repid;
	std::string								file_name;
};


/**
 * represents a component implementation
 */
class ComponentImplementation : public virtual PlatformBase
//							  , public virtual RefCountBase	
{
	/** makes use of this */
	friend class ComponentInstallationImpl;
	friend class CSDReader;
	friend class CCDReader;

private:

	/** the uuid of the component implementation */
	std::string							uuid_;
	/** the servant module */
	std::string							servant_module_;
	/** the entry point for the servant module */
	std::string							servant_entry_point_;
	/** the executor module */
	std::string							executor_module_;
	/** the entry point for the executor module */
	std::string							executor_entry_point_;
    /** the path of the idl file */
	std::string							idl_file_;
	/** the RepId of the home */
	std::string							home_repid_;
	/** the name of the home */
	std::string							home_name_;
	/** list of installed artifacts */
	std::vector < std::string >			artifacts_;
	/** list of required valuetype factories */
	std::vector < ValuetypeData >		valuetypes_;
    
	/** build dir of the component implementation */
	std::string							build_dir_;
    /** build path of the component implementation */
	std::string							build_path_;
	/** dir of the component implementation */
	std::string							installation_dir_;
    /** path of the component implementation */
	std::string							installation_path_;
    /** the path of the make file */
	std::string							makefile_;
    
    /** the package */
	Package*							package_;
	/** the installation counter */
    int									installation_count_;
	
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
	 * \param uuid The uuid of the implementation.
	 * \param installationDirectory The directory for the installation.
	 * \param package The package of the component implementation.
	 */
	ComponentImplementation (const char* uuid, std::string installationDirectory, std::string package);

	/**
	 * constructor
	 * constructs an implementation read from DeployedComponents file
	 * \param uuid The uuid of the implementation.
	 * \param servant_module The servant module.
	 * \param servant_entry_point The entry point for the servant module.
	 * \param executor_module The executor module.
	 * \param executor_entry_point The entry point for the executor module.
	 */
	ComponentImplementation (std::string uuid, std::string servant_module, std::string servant_entry_point,
		                     std::string executor_module, std::string executor_entry_point);

	/**
	 * constructor
	 * constructs an implementation read from DeployedComponents file
	 * \param uuid The uuid of the implementation.
	 */
	ComponentImplementation (std::string uuid);

	/**
	 * destructor
	 */
	~ComponentImplementation();

	/**
	 * comparison
	 */
    bool operator == (ComponentImplementation);

	/**
	 * install a component implementation
	 */
	bool install();

	/**
	 * uninstall a component implementation
	 */
    bool uninstall();
};

/** @} */

/** @} */

}

#endif
