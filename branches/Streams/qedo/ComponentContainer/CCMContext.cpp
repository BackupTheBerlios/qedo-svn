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
#ifndef _QEDO_NO_STREAMS
#include "StreamingBuffer.h"
#endif

static char rcsid[] UNUSED = "$Id: CCMContext.cpp,v 1.12.2.1 2003/09/26 14:26:02 stoinski Exp $";


namespace Qedo {


CCMContext::CCMContext()
{
}


CCMContext::~CCMContext()
{
	DEBUG_OUT ( "CCMContext: Destructor called" );

	ccm_object_executor_->_remove_ref();

#ifndef _QEDO_NO_STREAMS
	stream_ccm_object_executor_->_remove_ref();
#endif
}


void
CCMContext::ccm_object_executor (CCMObjectExecutor* ccm_object_exec)
{
	ccm_object_executor_ = ccm_object_exec;
	ccm_object_executor_->_add_ref();
}


#ifndef _QEDO_NO_STREAMS
void
CCMContext::stream_ccm_object_executor (StreamCCMObjectExecutor* stream_ccm_object_exec)
{
	stream_ccm_object_executor_ = stream_ccm_object_exec;
	stream_ccm_object_executor_->_add_ref();
}
#endif


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
CCMContext::queue_event(SubscribedConsumerVector& consumers, Components::EventBase* ev, CORBA::Long module_id)
{
	container_->queue_event(consumers, ev, module_id);
}


#ifndef _QEDO_NO_STREAMS
void 
CCMContext::begin_stream (const char* port_name, const char* repos_id, const ::Components::ConfigValues& meta_data)
throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream)
{
#ifdef _DEBUG
	std::string message = "CCMContext: begin_stream() called on source port ";
	message += port_name;
	message += " for streamtype ";
	message += repos_id;
	DEBUG_OUT (message.c_str());
#endif

	stream_ccm_object_executor_->begin_stream_source (port_name, repos_id, meta_data);
}


void 
CCMContext::end_stream (const char* port_name)
throw (StreamComponents::NoStream)
{
	DEBUG_OUT2 ("CCMContext: end_stream() called on source port ", port_name);

	stream_ccm_object_executor_->end_stream_source (port_name);
}


void 
CCMContext::send_buffer (const char* port_name, StreamComponents::StreamingBuffer_ptr buffer)
throw (StreamComponents::NoStream)
{
	DEBUG_OUT2 ("CCMContext: send_buffer() called on source port ", port_name);

	stream_ccm_object_executor_->send_buffer (port_name, buffer);
}


StreamComponents::StreamingBuffer_ptr 
CCMContext::get_streaming_buffer (CORBA::ULong min_size)
throw (StreamComponents::StreamingBuffer::IllegalSize,
	   StreamComponents::StreamingBuffer::OutOfMemory)
{
	if (!min_size)
		throw StreamComponents::StreamingBuffer::IllegalSize();

	StreamingBuffer *new_buffer = new StreamingBuffer (min_size);
	if (!new_buffer)
	{
		DEBUG_OUT ("CCMContext: Out of memory during creation of new streaming buffer");
		throw StreamComponents::StreamingBuffer::OutOfMemory();
	}

	return new_buffer;
}

#endif



HomeExecutorContext::HomeExecutorContext (Components::CCMHome_ptr my_home_ref)
: my_home_ref_ (Components::CCMHome::_duplicate (my_home_ref))
{
}


HomeExecutorContext::~HomeExecutorContext()
{
	DEBUG_OUT ( "HomeExecutorContext: Destructor called" );
}


Components::CCMHome_ptr 
HomeExecutorContext::get_CCM_home()
{
	return Components::CCMHome::_duplicate (my_home_ref_);
}


} // namespace Qedo

