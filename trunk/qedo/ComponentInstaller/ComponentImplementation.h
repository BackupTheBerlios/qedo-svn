/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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


#include <OB/CORBA.h>
#include "Components.h"
#include "Package.h"
#include "DOMXMLParser.h"
#include "PlatformBase.h"

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
 * a component implementation
 */
class ComponentImplementation : public virtual PlatformBase
{
friend class ComponentInstallationImpl;

private:
	std::string description_;
	std::string uuid_;
	std::string servant_module_;
	std::string servant_entry_point_;
	std::string executor_module_;
	std::string executor_entry_point_;

    //the path of the idl file
	std::string mIdlFile;

	// the RepId of the home
	std::string mIdlTarget;
    
    // the CORBA component descriptor
    DOM_Document mComponentDescriptor;
    
    // path of component implementations
	std::string mBuildPath;
    
    // path of the components implementation
	std::string mPath;
	
    // the name of the components home
	std::string mHomeName;
    
    // the path of the make file
	std::string mMakeFile;
    
    // the parser
	DOMXMLParser* mParser;
    
    // the parsed document
	DOM_Document mDocument;
    
    // the package
	Package* mPackage;
	
    // the installation counter
    int mCounter;

    // handle author
    void author (DOM_Element)
        throw(Components::CreateFailure);

    // handle code
    void code (DOM_Element)
        throw(Components::CreateFailure);

    // handle corbacomponent
    void corbacomponent (DOM_Document)
        throw(Components::CreateFailure);

    // handle dependency
    void dependency (DOM_Element)
        throw(Components::CreateFailure);

    // handle description
    void description (DOM_Element)
        throw(Components::CreateFailure);

    // handle descriptor
    DOM_Document descriptor (DOM_Element)
        throw(Components::CreateFailure);

    // handle extension
    void extension (DOM_Element)
        throw(Components::CreateFailure);

    // handle fileinarchive
	std::string fileinarchive (DOM_Element, std::string)
        throw(Components::CreateFailure);

    // handle idl element
    void idl (DOM_Element)
        throw(Components::CreateFailure);

    // handle implementation elements
    void implementation (DOM_Element)
        throw(Components::CreateFailure);

    // handle license
    void license (DOM_Element)
        throw(Components::CreateFailure);

    // handle link
	std::string link (DOM_Element, std::string)
        throw(Components::CreateFailure);

    // handle os
    void os (DOM_Element)
        throw(Components::CreateFailure);

    // handle package type
    void pkgtype (DOM_Element)
        throw(Components::CreateFailure);

    // handle propertyfile
    void propertyfile (DOM_Element)
        throw(Components::CreateFailure);

    // handle title
    void title (DOM_Element)
        throw(Components::CreateFailure);

    // buildServantCode
    void buildServantCode()
        throw(Components::CreateFailure);

public:
	ComponentImplementation (const char*, std::string, std::string);
	ComponentImplementation (std::string, std::string, std::string, std::string, std::string);
	~ComponentImplementation();

    bool operator == (ComponentImplementation);

    int get_counter();

	// install a component implementation
	bool install ();

	// uninstall a component implementation
    void uninstall ();
};


}

#endif
