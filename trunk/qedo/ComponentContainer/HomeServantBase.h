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

#ifndef __HOME_SERVANT_BASE_H__
#define __HOME_SERVANT_BASE_H__

#include <OB/CORBA.h>
#include "Components.h"

#include "CCMContext.h"
#include "ComponentInstance.h"
#include "ServantBase.h"
#include "ServantLocator.h"
#include "ServantRegistry.h"
#include "Util.h"

#include <vector>

namespace Qedo {

class ComponentInstance;
class ContainerInterfaceImpl;

class CONTAINERDLL_API HomeServantBase : public PortableServer::RefCountServantBase
{
	friend class ContainerInterfaceImpl;

private:
	PortableServer::POAManager_var	home_poa_manager_;
	PortableServer::Servant			my_home_servant_;
	PortableServer::ObjectId_var	my_object_id_;
	
	Components::CCMHome_var			my_home_ref_;
	CORBA::String_var				repository_id_;
	CORBA::String_var				comp_repository_id_;

	ServantLocator*					servant_locator_;
	
	CORBA::ULong instance_counter_;		// This counter will be part of any object reference created by this home

	// This function is used to create an object reference for the primary interface
	// and for home interfaces
	// Facets and event consumers must use create_object_reference()
	CORBA::Object_ptr create_primary_object_reference (const char* rep_id);

	//
	// These are the virtual functions that should be implemented by each container type
	//
	// This function is called shortly before the component instance is removed from a home
	// because of CCMHome::remove_component or the destruction of the home
	virtual void before_remove_component (Components::ExecutorLocator_ptr) = 0;

	// This function is called in the final stage of finalize_component_incarnation 
	virtual void do_finalize_component_incarnation (Components::ExecutorLocator_ptr) = 0;

protected:
	PortableServer::POA_var					home_poa_;
	Components::HomeExecutorBase_var		home_executor_;
	ServantRegistry*						servant_registry_;

	std::vector <ComponentInstance>				component_instances_;

	// This function creates an object reference and is used by create_primary_object_reference()
	CORBA::Object_ptr HomeServantBase::create_object_reference (const CORBA::OctetSeq*, const char*);

	ComponentInstance& incarnate_component (const char*, Components::ExecutorLocator_ptr, ExecutorContext*);
	
	void finalize_component_incarnation (const PortableServer::ObjectId&);

public:
	HomeServantBase (const char*, const char*);
	HomeServantBase();
	HomeServantBase (const HomeServantBase&);
	HomeServantBase& operator= (const HomeServantBase&);
	~HomeServantBase();

	void initialize (PortableServer::POA_ptr, Components::HomeExecutorBase_ptr)
		throw (Components::Deployment::InstallationFailure);

	Components::CCMHome_ptr ref();

	PortableServer::ObjectId* reference_to_oid (const CORBA::Object_ptr);
	void remove_component_with_oid (const PortableServer::ObjectId&);

	PortableServer::Servant lookup_servant (const PortableServer::ObjectId&);
	void prepare_remove();

	// in order to get information about repository ids
	const char* get_home_repid();
	const char* get_component_repid();
};

} // namespace Qedo

#endif

