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
#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "Util.h"

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
{
	/** makes use of this */
	friend class ComponentInstallationImpl;

private:
	/** description */
	std::string description_;
	/** the uuid of the component implementation*/
	std::string uuid_;
	/** the servant module */
	std::string servant_module_;
	/** the entry point for the servant module */
	std::string servant_entry_point_;
	/** the executor module */
	std::string executor_module_;
	/** the entry point for the executor module */
	std::string executor_entry_point_;

    /** the path of the idl file */
	std::string mIdlFile;

	/** the RepId of the home */
	std::string mIdlTarget;
    
    /** path of component implementations */
	std::string mBuildPath;
    
    /** path of the components implementation */
	std::string mPath;
	
    /** the name of the components home */
	std::string mHomeName;
    
    /** the path of the make file */
	std::string mMakeFile;
    
    /** the parser */
	DOMXMLParser* mParser;
    
    /** the parsed software package descriptor */
	DOMDocument* mDocument;
	/** the parsed CORBA component descriptor */
    DOMDocument* mComponentDescriptor;
    
    /** the package */
	Package* mPackage;
	
    /** the installation counter */
    int mCounter;

    /**
	 * handle author
	 */
    void author (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle code
	 * handle code elements being children of the given element
	 */
    void code (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle corbacomponent
	 */
    void corbacomponent (DOMDocument*)
        throw(Components::CreateFailure);

    /**
	 * handle dependency
	 */
    void dependency (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle description
	 */
    void description (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle descriptor
	 */
    DOMDocument* descriptor (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle extension
	 */
    void extension (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle fileinarchive
	 */
	std::string fileinarchive (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle idl element
	 */
    void idl (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle implementation elements
	 */
    void implementation (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle license
	 */
    void license (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle link
	 */
	std::string link (DOMElement*)
        throw(Components::CreateFailure);

	/**
	 * handle usage element
	 */
	std::string usage (DOMElement*)
        throw(Components::CreateFailure);

	/**
	 * handle entrypoint element
	 */
	std::string entrypoint (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle os
	 */
    void os (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle package type
	 */
    void pkgtype (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle propertyfile
	 */
    void propertyfile (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * handle title
	 */
    void title (DOMElement*)
        throw(Components::CreateFailure);

    /**
	 * build the servant code for the component
	 */
    void installCode()
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
	 * destructor
	 */
	~ComponentImplementation();

	/**
	 * comparison
	 */
    bool operator == (ComponentImplementation);

	/**
	 * provide the installation counter
	 */
    int get_counter();

	/**
	 * install a component implementation
	 */
	bool install();

	/**
	 * uninstall a component implementation
	 */
    void uninstall();
};

/** @} */

/** @} */

}

#endif
