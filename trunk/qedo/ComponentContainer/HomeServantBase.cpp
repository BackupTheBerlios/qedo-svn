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

#include "GlobalHelpers.h"
#include "HomeServantBase.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: HomeServantBase.cpp,v 1.19 2003/08/01 14:57:25 stoinski Exp $";


namespace Qedo {


HomeServantBase::HomeServantBase (const char* repository_id, const char* comp_repid)
: my_home_ref_ (Components::CCMHome::_nil()),
  repository_id_ (CORBA::string_dup (repository_id)),
  comp_repository_id_(CORBA::string_dup (comp_repid)),
  container_ (0),
  instance_counter_ (0),
  servant_registry_ (new ServantRegistry())
{
	servant_locator_ = new ServantLocator(this);
}


HomeServantBase::HomeServantBase()
{
	// We only have this constructor to allow default constructors for derived classes
	// Any final class must call the normal constructor with parameters
	NORMAL_ERR ("HomeServantBase: Wrong constructor used: Home servants must never call the default constructor");
	assert (0);
}


HomeServantBase::HomeServantBase (const HomeServantBase& base)
{
	NORMAL_ERR ("HomeServantBase: Wrong constructor used");
	assert (0);
}


HomeServantBase&
HomeServantBase::operator= (const HomeServantBase&)
{
	return *this;
}


HomeServantBase::~HomeServantBase()
{
	DEBUG_OUT ("HomeServantBase: Destructor called");

	servant_locator_->_remove_ref();

	servant_registry_->_remove_ref();

	if (container_)
		container_->_remove_ref();
}


void 
HomeServantBase::container(ContainerInterfaceImpl* container)
{
	container_ = container;

	container_->_add_ref();
}


void 
HomeServantBase::service(const char* name)
{
	service_name_ = name;
}


CORBA::Object_ptr
HomeServantBase::create_object_reference (const CORBA::OctetSeq* qedo_key, const char* rep_id)
{
	CORBA::String_var instance_info = CORBA::string_alloc (20 + 1);
	sprintf (instance_info, "%d", ++instance_counter_);

	PortableServer::ObjectId_var object_id = Qedo::create_object_id (qedo_key, instance_info);

	return home_poa_->create_reference_with_id (object_id, rep_id);
}


CORBA::Object_ptr
HomeServantBase::create_primary_object_reference (const char* rep_id)
{
	Qedo::Key* key = new Qedo::Key();
	CORBA::OctetSeq_var key_seq = key->key_value();

	CORBA::Object_var obj = create_object_reference (&key_seq.in(), rep_id);

	key->_remove_ref();

	return obj._retn();
}


PortableServer::ObjectId* 
HomeServantBase::reference_to_oid (const CORBA::Object_ptr obj)
{
	PortableServer::ObjectId_var object_id = home_poa_->reference_to_id (obj);

	return object_id._retn();
}


ComponentInstance& 
HomeServantBase::incarnate_component (Components::ExecutorLocator_ptr executor_locator, ExecutorContext* ccm_context)
{
	ccm_context->container (this->container_);

	// create object reference
	CORBA::Object_var component_ref = this->create_primary_object_reference (this->comp_repository_id_);

	// create object id
	PortableServer::ObjectId_var object_id = this->reference_to_oid (component_ref);

	// create component instance and register it
	ComponentInstance new_component (object_id, component_ref, executor_locator, ccm_context, this);
	component_instances_.push_back (new_component);
	
	return component_instances_.back ();
}


void
HomeServantBase::finalize_component_incarnation (const PortableServer::ObjectId& object_id)
{
	// Check whether a static servant was registered for this object id and set
	// the executor context, executor locator and ccm object executor
	std::vector <ComponentInstance>::const_iterator components_iter;

	for (components_iter = component_instances_.begin(); 
		 components_iter != component_instances_.end(); 
		 components_iter++)
	{
		if (Qedo::compare_object_ids ((*components_iter).object_id_, object_id))
		{
			break;
		}
	}

	if (components_iter == component_instances_.end())
	{
		NORMAL_ERR ("HomeServantBase: Unknown object id requested in finalize_component_incarnation");
		return;
	}

	servant_registry_->set_variables_static_servant (*components_iter);

	this->do_finalize_component_incarnation ((*components_iter).executor_locator_.in());
}


void
HomeServantBase::remove_component_with_oid (const PortableServer::ObjectId& object_id)
{
	// Look, whether we know this component instance
	std::vector <ComponentInstance>::iterator components_iter;

	for (components_iter = component_instances_.begin(); 
		 components_iter != component_instances_.end(); 
		 components_iter++)
	{
		if (Qedo::compare_object_ids ((*components_iter).object_id_, object_id))
		{
			break;
		}
	}

	if (components_iter == component_instances_.end())
	{
		NORMAL_ERR ("HomeServantBase: Unknown component supplied to remove_component()");
		return;
	}

	DEBUG_OUT ("HomeServantBase: remove_component_with_oid(): Component instance found... removing.");

	// Before removing the component and associating servants, let the different homes
	// decide, what additional things to do
	this->before_remove_component ((*components_iter).executor_locator_);

	component_instances_.erase (components_iter);

	// Now look in the static servants list and in the servant factories list to remove
	// the entry that belongs to this object id
	servant_registry_->unregister_static_servant (object_id);

	servant_registry_->unregister_servant_factory (object_id);
}


void 
HomeServantBase::initialize (PortableServer::POA_ptr root_poa,
							 Components::HomeExecutorBase_ptr home_executor)
throw (Components::Deployment::InstallationFailure)
{
	home_executor_ = Components::HomeExecutorBase::_duplicate (home_executor);

	// Create a new POA for the components
	CORBA::PolicyList policies;
	policies.length (7);
	policies[0] = root_poa->create_thread_policy (PortableServer::ORB_CTRL_MODEL);
	policies[1] = root_poa->create_lifespan_policy (PortableServer::TRANSIENT);
	policies[2] = root_poa->create_id_uniqueness_policy (PortableServer::UNIQUE_ID);
	policies[3] = root_poa->create_id_assignment_policy (PortableServer::USER_ID);
	policies[4] = root_poa->create_implicit_activation_policy (PortableServer::NO_IMPLICIT_ACTIVATION);
	policies[5] = root_poa->create_servant_retention_policy (PortableServer::NON_RETAIN);
	policies[6] = root_poa->create_request_processing_policy (PortableServer::USE_SERVANT_MANAGER);

	static CORBA::ULong poa_name = 0;
	char buffer[17];

	sprintf (buffer, "Qedo_POA_%d", ++poa_name);
	
	try
	{
		home_poa_ = root_poa->create_POA (buffer, NULL, policies);
	}
	catch (PortableServer::POA::AdapterAlreadyExists&)
	{
		NORMAL_ERR ("HomeServantBase: Fatal internal error - POA already exists???");
		throw Components::Deployment::InstallationFailure();
	}
	catch (PortableServer::POA::InvalidPolicy&)
	{
		NORMAL_ERR ("HomeServantBase: Fatal internal error - Invalid policy during POA creation: ORB not CORBA 2.3 compliant???");
		throw Components::Deployment::InstallationFailure();
	}

	// Set servant locator
	try
	{
#ifdef MICO_ORB
//	    home_poa_->set_servant_manager (dynamic_cast<PortableServer::ServantManager*>(servant_locator_));
	    home_poa_->set_servant_manager (servant_locator_->_this());		// THIS IS WRONG - ServantLocator is no CORBA::Object!
#else
	    home_poa_->set_servant_manager (servant_locator_);
#endif
	}
	catch (PortableServer::POA::WrongPolicy&)
	{
		// Cannot be, since our POA has the right policies
		NORMAL_ERR ("HomeServantBase: Fatal internal error - Setting servant manager complains about a wrong policy???");
		throw Components::Deployment::InstallationFailure();
	}

	my_home_servant_ = dynamic_cast <PortableServer::Servant> (this);

	if (! my_home_servant_)
	{
		NORMAL_ERR ("HomeServantBase: initialize(): Cannot dynamic_cast this pointer to PortableServer::Servant");
		throw Components::Deployment::InstallationFailure();
	}

	// Activate the POA using the POA manager
	home_poa_manager_ = home_poa_->the_POAManager();

	home_poa_manager_->activate();

	// Create a first object reference, which belongs to this home
	CORBA::Object_var home_obj = this->create_primary_object_reference (repository_id_);
	my_object_id_ = this->reference_to_oid (home_obj);

	// Narrow the object reference for the home (this can involve remote _is_a() calls to the
	// servant, so it must be active at this time)
	my_home_ref_ = Components::CCMHome::_narrow (home_obj);
}


Components::CCMHome_ptr 
HomeServantBase::ref()
{
	return Components::CCMHome::_duplicate (my_home_ref_);
}


Components::CCMObject_ptr
HomeServantBase::lookup_component (const PortableServer::ObjectId& object_id)
{
	CORBA::OctetSeq_var foreign_key_seq = Key::key_value_from_object_id (object_id);
	CORBA::OctetSeq_var our_key_seq;

	std::vector <ComponentInstance>::const_iterator components_iter;

	for (components_iter = component_instances_.begin(); 
		 components_iter != component_instances_.end(); 
		 components_iter++)
	{
		our_key_seq = Key::key_value_from_object_id ((*components_iter).object_id_);

		if (Qedo::compare_OctetSeqs (foreign_key_seq, our_key_seq))
		{
			break;
		}
	}

	if (components_iter == component_instances_.end())
	{
		DEBUG_OUT ("HomeServantBase: Unknown object id requested in lookup_component");
		throw CORBA::OBJECT_NOT_EXIST();
	}

	return Components::CCMObject::_narrow ((*components_iter).component_ref_);
}


PortableServer::Servant
HomeServantBase::lookup_servant (const PortableServer::ObjectId& object_id)
{
	// First check, whether it is our own object id (we are the home)
	if (Qedo::compare_object_ids (object_id, my_object_id_))
	{
		my_home_servant_->_add_ref();
		return my_home_servant_;
	}

	// It is not the home, so look, whether we know this component instance
	CORBA::OctetSeq_var foreign_key_seq = Key::key_value_from_object_id (object_id);
	CORBA::OctetSeq_var our_key_seq;

	std::vector <Qedo::ComponentInstance>::const_iterator components_iter;

	for (components_iter = component_instances_.begin(); 
		 components_iter != component_instances_.end(); 
		 components_iter++)
	{
		our_key_seq = Key::key_value_from_object_id ((*components_iter).object_id_);

		if (Qedo::compare_OctetSeqs (foreign_key_seq, our_key_seq))
		{
			break;
		}
	}

	if (components_iter == component_instances_.end())
	{
		DEBUG_OUT ("HomeServantBase: Unknown object id requested in lookup_servant");
		throw CORBA::OBJECT_NOT_EXIST();
	}

	// Now look for a servant to handle this request
	// First try to get a static servant, static servants have their
	// executor context, executor locator and CCM object executor already set
	Qedo::ServantBase* servant;

	servant = servant_registry_->lookup_static_servant (object_id);

	if (servant)
	{
		return servant;
	}

	// No static servant, try to find a servant generated by a factory
	servant = servant_registry_->lookup_factory_created_servant (object_id);

	if (!servant)
	{
		NORMAL_ERR ("HomeServantBase: Fatal internal error: There is neither a static servant nor a servant factory registered");
		assert (0);
	}

	// set the instance
	servant->set_instance(*components_iter);
		
	return servant;
}


void
HomeServantBase::prepare_remove()
{
	DEBUG_OUT ("HomeServantBase: prepare_remove() called");

	// Here we must remove all component instances that are still running
	if (component_instances_.size() > 0)
	{
		DEBUG_OUT ("HomeServantBase: Warning: There are still component instances around");

		// We cannot use an iterator to iterate through the list, since this list will be
		// manipulated by remove_component_with_oid()
		while (component_instances_.size())
		{
			// We do need to construct a copy of the object key, since (*components_iter).object_id_ will
			// get destroyed in the first part of remove_component_with_oid(), but the object key is
			// afterwards needed in the function to remove static servants and servant factories
			PortableServer::ObjectId_var object_id = new PortableServer::ObjectId (component_instances_[0].object_id_);

			this->remove_component_with_oid (object_id);
		}
	}

	home_poa_manager_->deactivate (false /*no etherealize objects*/, false /*no wait for completion*/);

	home_poa_->destroy (false /*no etherealize objects*/, false /*no wait for completion*/);
}


const char* 
HomeServantBase::get_home_repid()
{
	return repository_id_;
}


const char* 
HomeServantBase::get_component_repid()
{
	return comp_repository_id_;
}


} // namespace Qedo

