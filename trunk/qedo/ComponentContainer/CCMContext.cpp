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

#include "CCMContext.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: CCMContext.cpp,v 1.13 2003/08/26 11:33:53 boehme Exp $";


namespace Qedo {


CCMContext::CCMContext()
{
}


CCMContext::~CCMContext()
{
	DEBUG_OUT ( "CCMContext: Destructor called" );
}


void 
CCMContext::container(ContainerInterfaceImpl* container)
{
	container_ = container;
}


Components::Principal 
CCMContext::get_caller_principal()
{
	return 0;
}


Components::CCMHome_ptr 
CCMContext::get_CCM_home()
{
	return ccm_object_executor_->get_home();
}


CORBA::Boolean 
CCMContext::get_rollback_only()
throw (Components::IllegalState)
{
	throw Components::IllegalState();
}


Components::Transaction::UserTransaction_ptr 
CCMContext::get_user_transaction()
throw (Components::IllegalState)
{
	throw Components::IllegalState();
}


CORBA::Boolean 
CCMContext::is_caller_in_role (const char* role)
{
	return false;
}


void 
CCMContext::set_rollback_only()
throw (Components::IllegalState)
{
}


CORBA::Object_ptr 
CCMContext::resolve_service_reference(const char* service_id)
throw (Components::CCMException)
{
	return container_->resolve_service_reference(service_id);
}


void 
CCMContext::queue_event(Components::EventConsumerBase_ptr consumer, Components::EventBase* ev, CORBA::Long module_id)
{
	container_->queue_event(consumer, ev, module_id);
}


void 
CCMContext::queue_event(const SubscribedConsumerVector& consumers, Components::EventBase* ev, CORBA::Long module_id)
{
	container_->queue_event(consumers, ev, module_id);
}


ExecutorContext::ExecutorContext()
{
}


ExecutorContext::~ExecutorContext()
{
	DEBUG_OUT ("ExecutorContext: Destructor called");

	ccm_object_executor_->_remove_ref();
}


void
ExecutorContext::ccm_object_executor (CCMObjectExecutor* ccm_object_exec)
{
	ccm_object_executor_ = ccm_object_exec;
	ccm_object_executor_->_add_ref();
}


HomeExecutorContext::HomeExecutorContext (Components::CCMHome_ptr my_home_ref)
: my_home_ref_ (Components::CCMHome::_duplicate (my_home_ref))
{
}


HomeExecutorContext::~HomeExecutorContext()
{
	DEBUG_OUT ( "HomeExecutorContext: Destructor called" );
}


Components::Principal 
HomeExecutorContext::get_caller_principal()
{
	throw CORBA::NO_IMPLEMENT();
}


Components::CCMHome_ptr 
HomeExecutorContext::get_CCM_home()
{
	return Components::CCMHome::_duplicate (my_home_ref_);
}


CORBA::Boolean 
HomeExecutorContext::get_rollback_only()
throw (Components::IllegalState)
{
	throw CORBA::NO_IMPLEMENT();
}


Components::Transaction::UserTransaction_ptr 
HomeExecutorContext::get_user_transaction()
throw (Components::IllegalState)
{
	throw CORBA::NO_IMPLEMENT();
}


CORBA::Boolean 
HomeExecutorContext::is_caller_in_role (const char* role)
{
	throw CORBA::NO_IMPLEMENT();
}


void 
HomeExecutorContext::set_rollback_only()
throw (Components::IllegalState)
{
	throw CORBA::NO_IMPLEMENT();
}


CORBA::Object_ptr 
HomeExecutorContext::resolve_service_reference(const char* service_id)
throw (Components::CCMException)
{
	throw CORBA::NO_IMPLEMENT();
}


} // namespace Qedo

