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

#ifndef __CONTAINER_INTERFACE_IMPL_H__
#define __CONTAINER_INTERFACE_IMPL_H__

#include <CORBA.h>
#ifdef MICO_ORB
#include <mico/CosNaming.h>
#else
#include <CosNaming.h>
#endif
#include <QedoComponents_skel.h>

#include "HomeServantBase.h"
#include "Util.h"

#include <vector>

namespace Qedo {

class HomeEntry
{
public:

	/** the servant of the home */
	Qedo::HomeServantBase* home_servant_;

	/** id for registration in home finder */
	Components::Cookie* home_cookie_;

	HomeEntry (Qedo::HomeServantBase*, Components::Cookie* c);
	HomeEntry();
	HomeEntry (const HomeEntry&);
	HomeEntry& operator= (const HomeEntry&);
	~HomeEntry();
};


enum ContainerType {CT_EMPTY, CT_SERVICE, CT_SESSION, CT_PROCESS, CT_ENTITY};


//
// Implementation of the interface Components::Deployment::Container
//
class CONTAINERDLL_API ContainerInterfaceImpl : public virtual POA_Components::Deployment::Container,
												public virtual PortableServer::RefCountServantBase
{
private:
	CORBA::ORB_var											orb_;
	PortableServer::POA_var									root_poa_;
	ContainerType											container_type_;
	Components::Deployment::ComponentInstallation_var		component_installer_;
	Qedo_Components::HomeFinder_var							home_finder_;

	std::vector <HomeEntry>									installed_homes_;

#ifdef _WIN32
	HINSTANCE load_shared_library (const char* name);
#else
	void* load_shared_library (const char* name);
#endif

public:
	ContainerInterfaceImpl (CORBA::ORB_ptr, 
							PortableServer::POA_ptr, 
							ContainerType,
							Components::Deployment::ComponentInstallation_ptr);
	~ContainerInterfaceImpl();

	//
    // IDL:omg.org/Components/Deployment/Container/configuration:1.0
    //
    virtual Components::ConfigValues* configuration()
        throw (CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/Container/get_component_server:1.0
    //
    virtual Components::Deployment::ComponentServer_ptr get_component_server()
        throw (CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/Container/install_home:1.0
    //
    virtual Components::CCMHome_ptr install_home(const char* id,
												 const char* entrypt,
												 const Components::ConfigValues& config)
        throw (Components::Deployment::UnknownImplId,
               Components::Deployment::ImplEntryPointNotFound,
               Components::Deployment::InstallationFailure,
               Components::Deployment::InvalidConfiguration,
               CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/Container/remove_home:1.0
    //
    virtual void remove_home(Components::CCMHome_ptr href)
        throw (Components::RemoveFailure, CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/Container/get_homes:1.0
    //
    virtual Components::CCMHomes* get_homes()
        throw (CORBA::SystemException);

    //
    // IDL:omg.org/Components/Deployment/Container/remove:1.0
    //
    virtual void remove()
        throw (Components::RemoveFailure, CORBA::SystemException);
};

} // namespace Qedo

#endif

