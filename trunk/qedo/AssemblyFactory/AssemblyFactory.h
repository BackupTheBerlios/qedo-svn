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

#ifndef __ASSEMBLY_FACTORY_H__
#define __ASSEMBLY_FACTORY_H__


#include <CORBA.h>
#include "QedoComponents_skel.h"
#include "Assembly.h"
#include "NameServiceBase.h"
#include "PlatformBase.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <list>

#ifdef _WIN32
#include <windows.h>
#endif


namespace Qedo {


/**
 * @addtogroup Assembly
 * @{
 */


/**
 * the implementation of the Components::Deployment::AssemblyFactory
 */
class AssemblyFactoryImpl : public virtual POA_Components::Deployment::AssemblyFactory,
                            public virtual NameServiceBase,
                            public virtual PlatformBase
{
private:
	/** the orb */
    CORBA::ORB_var					orb_;
	/** the root poa */
    PortableServer::POA_var			root_poa_;
	/** the root poa manager */
	PortableServer::POAManager_var	root_poa_manager_;

	/** the list of created assemblies */
	std::list < AssemblyImpl* >		assemblies_;
	/** the package directory */
	std::string						packageDirectory_;

	/**
	 * constructor
	 */
    AssemblyFactoryImpl();

public:
	/**
	 * constructor
	 * \param orb The orb.
	 */
	AssemblyFactoryImpl(CORBA::ORB_ptr orb);

	/**
	 * destructor
	 */
    virtual ~AssemblyFactoryImpl();

	/**
	 * initialize the server
	 */
	void initialize();

	/**
     * implements IDL:omg.org/Components/Deployment/AssemblyFactory/create:1.0
     */
    Components::Cookie* create(const char* assembly_loc)
		throw ( Components::Deployment::InvalidLocation, Components::CreateFailure );

    /**
     * implements IDL:omg.org/Components/Deployment/AssemblyFactory/lookup:1.0
     */
    Components::Deployment::Assembly_ptr lookup(::Components::Cookie* c)
		throw ( Components::Deployment::InvalidAssembly );

    /**
     * implements IDL:omg.org/Components/Deployment/AssemblyFactory/destroy:1.0
     */
    void destroy(::Components::Cookie* c)
		throw ( Components::Deployment::InvalidAssembly, Components::RemoveFailure );

	//
	// Exceptions
	//

	class CannotInitialize {};
};

/** @} */

}

#endif

