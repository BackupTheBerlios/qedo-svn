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
#include "InternalConfiguration.h"
#ifndef _QEDO_NO_QOS
#include "ComponentServerImpl.h"
#endif

static char rcsid[] UNUSED = "$Id: CCMContext.cpp,v 1.24 2004/02/25 10:39:14 neubauer Exp $";


namespace Qedo {


CCMContext::CCMContext()
: ccm_object_executor_ (0)
#ifndef _QEDO_NO_STREAMS
, stream_ccm_object_executor_ (0)
#endif
{
}


CCMContext::~CCMContext()
{
	DEBUG_OUT ( "CCMContext: Destructor called" );

	if (ccm_object_executor_)
		ccm_object_executor_->_remove_ref();

#ifndef _QEDO_NO_STREAMS
        if (stream_ccm_object_executor_)
		stream_ccm_object_executor_->_remove_ref();
#endif

	QedoLock lock (service_references_mutex_);
	service_references_.clear();
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
	//
	// component specific service
	//
	if(!strcmp( service_id, "ConfigurationService" ))
	{
		//
		// find the service instance in our list
		//
		std::vector < ServiceReferenceEntry >::iterator iter;

		QedoLock lock (service_references_mutex_);

		for(iter = service_references_.begin();
			iter != service_references_.end();
			iter++)
		{
			if(!iter->_service_id.compare(service_id))
			{
				return iter->_service_ref.out();
			}
		}

		//
		// create and register service instance
		//
		InternalConfiguration* ref = new InternalConfiguration( this );
		ServiceReferenceEntry new_entry( service_id, ref );
		service_references_.push_back (new_entry);
		ref->_remove_ref();
		
		return ref;
	}

	//
	// non component specific service
	//
	return container_->resolve_service_reference( service_id );
}


class Thread_impl : public virtual Components::Thread,
					public virtual RefCountLocalObject
{
	QedoThread* thread;
	Thread_impl();
public:
	Thread_impl(QedoThread* t);
	void stop();
	void join();
};


Components::Thread_ptr 
ThreadSupport::start_thread( Components::Function func, Components::FunctionData data )
{
	Thread_impl* thread = new Thread_impl(qedo_startDetachedThread(func, data));
	return thread;
}

class Mutex_impl : public virtual Components::Mutex,
                   public virtual QedoMutex,
				   public virtual RefCountLocalObject
{
	public:
	void lock() {this->lock_object();}
	void unlock() {this->unlock_object();}
	void destroy() { delete this; }
};

Components::Mutex_ptr 
ThreadSupport::create_mutex()
{
	Mutex_impl* mutex = new Mutex_impl();
	return mutex;
}

class Cond_impl : public virtual Components::Cond,
                  public virtual QedoCond,
				  public virtual RefCountLocalObject
{
	public:
	void wait(Components::Mutex_ptr);
	CORBA::Boolean wait_timed(Components::Mutex_ptr, CORBA::ULong);
	void signal() { QedoCond::signal(); }
	void destroy() { delete this; }
};

void
Cond_impl::wait(Components::Mutex_ptr x)
{
	Qedo::QedoMutex* m = dynamic_cast<QedoMutex*>(x);

	if(!m) abort();

	QedoCond::wait(m);
}

CORBA::Boolean
Cond_impl::wait_timed(Components::Mutex_ptr x, CORBA::ULong time)
{
	Qedo::QedoMutex* m = dynamic_cast<QedoMutex*>(x);

	if(!m) abort();

	return QedoCond::wait_timed(m,time);
}

Components::Cond_ptr 
ThreadSupport::create_cond()
{
	Cond_impl* cond = new Cond_impl();
	return cond;
}

Components::Thread_ptr 
CCMContext::start_thread( Components::Function func, Components::FunctionData data )
{
	Thread_impl* thread ;
#ifndef _QEDO_NO_QOS
	int dummy = 0;
    CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);
	CORBA::Object_var obj = orb->resolve_initial_references ("PICurrent");
	PortableInterceptor::Current_var piCurrent = PortableInterceptor::Current::_narrow (obj);
	CORBA::Any* slot_content = 0;
	slot_content = piCurrent->get_slot(this->ccm_object_executor_->home_servant_->container_->component_server_->slot_id());
	if (slot_content)
	{
		thread = new Thread_impl(qedo_startDetachedThread(func, data, ccm_object_executor_->home_servant_->container_->component_server_->slot_id(), slot_content));
	} else
	{
		thread = new Thread_impl(qedo_startDetachedThread(func, data));
	}
#else
	thread = new Thread_impl(qedo_startDetachedThread(func, data));
#endif
	return thread;

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


Thread_impl::Thread_impl() {};

Thread_impl::Thread_impl(QedoThread* t)
: thread(t)
{
};

void
Thread_impl::stop()
{
	thread->stop();
};

void
Thread_impl::join()
{
	thread->join();
};


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

