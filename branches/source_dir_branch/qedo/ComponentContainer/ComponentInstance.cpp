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

#include "HomeServantBase.h"
#include "ComponentInstance.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: ComponentInstance.cpp,v 1.10 2003/07/24 13:14:54 boehme Exp $";


namespace Qedo {


ComponentInstance::ComponentInstance (const PortableServer::ObjectId& object_id,
									  CORBA::Object_ptr component_ref,
									  Components::ExecutorLocator_ptr executor_locator,
									  ExecutorContext* executor_context,
									  HomeServantBase* home_servant)
: object_id_ (new PortableServer::ObjectId (object_id)),
  component_ref_ (CORBA::Object::_duplicate (component_ref)),
  executor_locator_ (Components::ExecutorLocator::_duplicate (executor_locator)),
  ccm_object_executor_ (new CCMObjectExecutor (object_id, component_ref, home_servant))
{
	// Finally tell the context about the ccm object executor
	// The context always calls the generic functions of the ccm object executor to
	// provide the functionality of the type-specific generated context operations
	executor_context->ccm_object_executor (ccm_object_executor_);
}


ComponentInstance::ComponentInstance()
{
	ccm_object_executor_ = 0;
}


ComponentInstance::ComponentInstance (const ComponentInstance& component_entry)
: object_id_ (new PortableServer::ObjectId (component_entry.object_id_)),
  component_ref_ (CORBA::Object::_duplicate (component_entry.component_ref_.in())),
  executor_locator_ (Components::ExecutorLocator::_duplicate (component_entry.executor_locator_.in())),
  ccm_object_executor_ (component_entry.ccm_object_executor_)
{
	ccm_object_executor_->_add_ref();
}


ComponentInstance& 
ComponentInstance::operator= (const ComponentInstance& component_instance)
{
	object_id_ = new PortableServer::ObjectId (component_instance.object_id_);
	component_ref_ = CORBA::Object::_duplicate (component_instance.component_ref_.in());
	executor_locator_ = Components::ExecutorLocator::_duplicate (component_instance.executor_locator_.in());

	if (ccm_object_executor_)
		ccm_object_executor_->_remove_ref();

	ccm_object_executor_ = component_instance.ccm_object_executor_;
	ccm_object_executor_->_add_ref();

	return *this;
}


ComponentInstance::~ComponentInstance()
{
	DEBUG_OUT2("ComponentInstance: Destructor called for ", this);

	ccm_object_executor_->_remove_ref();
}


CORBA::Object_ptr
ComponentInstance::component_ref()
{
	return CORBA::Object::_duplicate (component_ref_);
}

} // namespace Qedo

