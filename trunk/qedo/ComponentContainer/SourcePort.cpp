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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef _QEDO_NO_STREAMS

#include "SourcePort.h"
#include "Output.h"
#include "TransportRegistry.h"

#include <string>
#include <cstring>


static char rcsid[] UNUSED = "$Id: SourcePort.cpp,v 1.5 2004/06/24 14:36:08 tom Exp $";


namespace Qedo {


//
// SourceBinding
//
SourceBinding::SourceBinding (StreamComponents::SinkStreamPort_ptr the_sink,
							  Cookie_impl* cookie,
							  SourceTransportEndpoint* tep)
: the_sink_ (StreamComponents::SinkStreamPort::_duplicate (the_sink)),
  cookie_ (cookie),
  connected_ (false),
  tagged_for_remove_ (false),
  tep_ (tep)
{
    cookie_->_add_ref();
	tep_->_add_ref();
}


SourceBinding::SourceBinding()
{
}


SourceBinding::SourceBinding (const SourceBinding& src_binding)
: the_sink_ (StreamComponents::SinkStreamPort::_duplicate (src_binding.the_sink_.in())),
  cookie_ (src_binding.cookie_),
  connected_ (src_binding.connected_),
  tagged_for_remove_ (src_binding.tagged_for_remove_),
  tep_ (src_binding.tep_)
{
	cookie_->_add_ref();
	tep_->_add_ref();
}


SourceBinding& 
SourceBinding::operator= (const SourceBinding& src_binding)
{
	the_sink_ = StreamComponents::SinkStreamPort::_duplicate (src_binding.the_sink_.in());

	if (cookie_)
		cookie_->_remove_ref();

	cookie_ = src_binding.cookie_;
	cookie_->_add_ref();

	if (tep_)
		tep_->_remove_ref();

	tep_ = src_binding.tep_;
	tep_->_add_ref();

	connected_ = src_binding.connected_;
	tagged_for_remove_ = src_binding.tagged_for_remove_;

	return *this;
}


SourceBinding::~SourceBinding()
{
    cookie_->_remove_ref();

	if (tep_)
		tep_->_remove_ref();
}


bool
SourceBinding::begin_stream (const char* repos_id, const ::Components::ConfigValues& meta_data)
{
	// Propagate towards transport endpoint
	tep_->begin_stream();

	// Propagate towards the SinkStreamPort object
	try
	{
		the_sink_->begin_stream (repos_id, meta_data);
	}
	catch (StreamComponents::UnsupportedStreamtype& ex)
	{
		DEBUG_OUT ("SourcePort: Fatal error: Compatible sink complains about already negotiated streamtype");
		if (ex.unsupported_streamtypes.length())
			DEBUG_OUT2 ("SourcePort: First incompatible streamtype (as told by the sink) was: ",
				ex.unsupported_streamtypes[0]);
		DEBUG_OUT ("SourcePort: Going to remove this sink from my binding list");
		this->tag_for_remove();
		return false;
	}
	catch (StreamComponents::DuplicateStream&)
	{
		DEBUG_OUT ("SourcePort: Fatal error: Unbound sink complains about being already bound");
		DEBUG_OUT ("SourcePort: Going to remove this sink from my binding list");
		this->tag_for_remove();
		return false;
	}
	catch (CORBA::SystemException&)
	{
		DEBUG_OUT ("SourcePort: CORBA system exception during calling begin_stream(): Sink is maybe gone");
		DEBUG_OUT ("SourcePort: Going to remove this sink from my binding list");
		this->tag_for_remove();
		return false;
	}

	return true;
}


bool
SourceBinding::end_stream()
{
	// Propagate towards transport endpoint
	tep_->end_stream();

	// Propagate towards the SinkStreamPort object
	try
	{
		the_sink_->end_stream();
	}
	catch (StreamComponents::NoStream&)
	{
		NORMAL_ERR ("SourcePort: Fatal error: Bound sink complains about being not bound");
		NORMAL_ERR ("SourcePort: Going to remove this sink from my binding list");
		this->tag_for_remove();
		return false;
	}
	catch (CORBA::SystemException&)
	{
		DEBUG_OUT ("SourceBinding: CORBA system exception during calling end_stream(): Sink is maybe gone");
		DEBUG_OUT ("SourcePort: Going to remove this sink from my binding list");
		this->tag_for_remove();
		return false;
	}

	return true;
}


void
SourceBinding::close_transport()
{
	if (tep_)
	{
		tep_->close();
		tep_->_remove_ref();
		tep_ = 0;
		connected_ = false;
	}
}


bool 
SourceBinding::send_buffer (StreamComponents::StreamingBuffer_ptr buffer) 
{
	if (! tep_->send_buffer (buffer))
	{
		DEBUG_OUT ("SourceBinding: send_buffer() failed");

		this->tag_for_remove();
		return false;
	}

	return true;
}


BindingDescription_impl* 
SourceBinding::binding_description() const
{
	BindingDescription_impl* binding_desc = new BindingDescription_impl (cookie_, the_sink_.in()); 

    return binding_desc;
}


Cookie_impl*
SourceBinding::cookie() const
{
	cookie_->_add_ref();
    return cookie_;
}


CORBA::Boolean 
SourceBinding::same_binding (Components::Cookie* cookie) const
{
    return cookie_->equal (cookie);
}


//
// DispatcherEntry
//
DispatcherEntry::DispatcherEntry (EntryType entry_type)
: entry_type_ (entry_type)
{
}


DispatcherEntry::DispatcherEntry (const DispatcherEntry& entry)
: entry_type_ (entry.entry_type_)
{
}


DispatcherEntry&
DispatcherEntry::operator= (const DispatcherEntry& entry)
{
	entry_type_ = entry.entry_type_;

	return *this;
}


DispatcherEntry::~DispatcherEntry()
{
}


NormalBufferEntry::NormalBufferEntry (StreamComponents::StreamingBuffer_ptr buffer)
: DispatcherEntry (NORMAL_BUFFER),
  buffer_ (StreamComponents::StreamingBuffer::_duplicate (buffer))
{
}


NormalBufferEntry::NormalBufferEntry (const NormalBufferEntry& entry)
: DispatcherEntry (entry),
  buffer_ (StreamComponents::StreamingBuffer::_duplicate (entry.buffer_.in()))
{
}


NormalBufferEntry&
NormalBufferEntry::operator= (const NormalBufferEntry& entry)
{
	DispatcherEntry::operator= (entry);

	buffer_ = StreamComponents::StreamingBuffer::_duplicate (entry.buffer_.in());

	return *this;
}


NormalBufferEntry::~NormalBufferEntry()
{
}


BeginStreamEntry::BeginStreamEntry (const char* repos_id, const ::Components::ConfigValues& meta_data)
: DispatcherEntry (BEGIN_OF_STREAM),
  repos_id_ (repos_id),
  meta_data_ (new ::Components::ConfigValues (meta_data))
{
}


BeginStreamEntry::BeginStreamEntry (const BeginStreamEntry& entry)
: DispatcherEntry (entry),
  repos_id_ (entry.repos_id_),
  meta_data_ (new ::Components::ConfigValues (entry.meta_data_))
{
}


BeginStreamEntry& 
BeginStreamEntry::operator= (const BeginStreamEntry& entry)
{
	DispatcherEntry::operator= (entry);

	repos_id_ = entry.repos_id_;
	meta_data_ = new ::Components::ConfigValues (entry.meta_data_);

	return *this;
}


BeginStreamEntry::~BeginStreamEntry()
{
}


EndStreamEntry::EndStreamEntry()
: DispatcherEntry (END_OF_STREAM)
{
}


EndStreamEntry::EndStreamEntry (const EndStreamEntry& entry)
: DispatcherEntry (entry)
{
}


EndStreamEntry& 
EndStreamEntry::operator= (const EndStreamEntry& entry)
{
	DispatcherEntry::operator= (entry);

	return *this;
}


EndStreamEntry::~EndStreamEntry()
{
}


DispatcherEntry_smartptr::DispatcherEntry_smartptr (DispatcherEntry* dispatcher_entry) 
: dispatcher_entry_ (dispatcher_entry) 
{ 
	dispatcher_entry_->_add_ref();
}


DispatcherEntry_smartptr::DispatcherEntry_smartptr (const DispatcherEntry_smartptr& dispatcher_entry_smartptr) 
: dispatcher_entry_ (dispatcher_entry_smartptr.dispatcher_entry_) 
{ 
	dispatcher_entry_->_add_ref(); 
}


DispatcherEntry_smartptr& 
DispatcherEntry_smartptr::operator= (const DispatcherEntry_smartptr& dispatcher_entry_smartptr)
{
	if (dispatcher_entry_)
		dispatcher_entry_->_remove_ref();

	dispatcher_entry_ = dispatcher_entry_smartptr.dispatcher_entry_;
	dispatcher_entry_->_add_ref();
	
	return *this;
}

DispatcherEntry_smartptr::~DispatcherEntry_smartptr() 
{ 
	dispatcher_entry_->_remove_ref(); 
}


//
// SourcePort
//
SourcePort::SourcePort (const char* name,
						const char* type_id, 
						CORBA::Boolean is_multiplex,
						const CORBA::RepositoryIdSeq& streamtypes,
						bool configured_for_async_call)
: PortBase (name, type_id),
  is_multiplex_ (is_multiplex),
  active_stream_ (false),
  streamtypes_ (new CORBA::RepositoryIdSeq (streamtypes)),
  configured_for_async_call_ (configured_for_async_call),
  dispatcher_thread_stopped_ (false)
{
	if (configured_for_async_call_)
	{
		dispatcher_thread_ = qedo_startDetachedThread (this->dispatcher_thread, this);
	}
}


SourcePort::SourcePort()
{
}


SourcePort::SourcePort (const SourcePort& src_port)
: PortBase (src_port),
  is_multiplex_ (src_port.is_multiplex_),
  active_stream_ (src_port.active_stream_),
  streamtypes_ (new CORBA::RepositoryIdSeq (src_port.streamtypes_)),
  configured_for_async_call_ (src_port.configured_for_async_call_),
  dispatcher_thread_stopped_ (src_port.dispatcher_thread_stopped_),
  bindings_ (src_port.bindings_),
  dispatcher_entries_ (src_port.dispatcher_entries_)
{
}


SourcePort& 
SourcePort::operator= (const SourcePort& src_port)
{
  is_multiplex_ = src_port.is_multiplex_;
  active_stream_ = src_port.active_stream_;
  streamtypes_ = new CORBA::RepositoryIdSeq (src_port.streamtypes_);
  configured_for_async_call_ = src_port.configured_for_async_call_;
  dispatcher_thread_stopped_ = src_port.dispatcher_thread_stopped_;
  bindings_ = src_port.bindings_;
  dispatcher_entries_ = src_port.dispatcher_entries_;

  return *this;
}


SourcePort::~SourcePort()
{
}


void
SourcePort::do_dispatch()
{
	ThreadExitHelper thread_exit_helper (this);

	while (! dispatcher_thread_stopped_)
	{
		while (! dispatcher_entries_.empty())
		{
			DispatcherEntry_smartptr& entry = dispatcher_entries_.front();

			switch (entry->entry_type_)
			{
			case DispatcherEntry::NORMAL_BUFFER:
				NormalBufferEntry* normal_entry;
				normal_entry = static_cast<NormalBufferEntry*> (entry.ptr());
				this->dispatch_buffer (normal_entry->buffer_);
				break;
			case DispatcherEntry::BEGIN_OF_STREAM:
				BeginStreamEntry* begin_entry;
				begin_entry = static_cast<BeginStreamEntry*> (entry.ptr());
				this->dispatch_begin_of_stream (begin_entry->repos_id_.c_str(), begin_entry->meta_data_.in());
				break;
			case DispatcherEntry::END_OF_STREAM:
				// No need to cast to EndStreamEntry
				this->dispatch_end_of_stream();
				break;
			}
			{
				QedoLock lock (dispatcher_entries_mutex_);
				dispatcher_entries_.erase(dispatcher_entries_.begin());
			}

			if (dispatcher_thread_stopped_)
			{
				break;
			}
		}

		if (dispatcher_thread_stopped_)
		{
			break;
		}

		QedoLock lock (dispatch_mutex_);
		dispatch_cond_.wait (dispatch_mutex_);
	}
}


void* 
SourcePort::dispatcher_thread (void* data)
{
	DEBUG_OUT ("SourcePort: Asynchronous dispatcher thread started");

	SourcePort* this_ptr = (SourcePort*)data;

	this_ptr->do_dispatch();

	// Okay, when e are here, the dispatcher thread has stopped
	DEBUG_OUT ("SourcePort: Asynchronous dispatcher thread finished");

	// We must return something, why not the data value ;-)
	return data;
}


void
SourcePort::dispatch_buffer (StreamComponents::StreamingBuffer_ptr buffer)
{
	BindingVector::iterator binding_iter;
	bool bogus_sink_detected = false;

	QedoLock lock (bindings_mutex_);

	for (binding_iter = bindings_.begin(); binding_iter != bindings_.end(); binding_iter++)
	{
		if (! (*binding_iter).send_buffer (buffer))
		{
			bogus_sink_detected = true;
		}
	}

	if (bogus_sink_detected)
		this->remove_bogus_sinks();
}


void
SourcePort::dispatch_begin_of_stream (const char* repos_id, const ::Components::ConfigValues& meta_data)
{
	BindingVector::iterator binding_iter;
	bool bogus_sink_detected = false;

	QedoLock lock (bindings_mutex_);

	for (binding_iter = bindings_.begin(); binding_iter != bindings_.end(); binding_iter++)
	{
		if (! (*binding_iter).begin_stream (repos_id, meta_data))
			bogus_sink_detected = true;
	}

	if (bogus_sink_detected)
		this->remove_bogus_sinks();
}


void
SourcePort::dispatch_end_of_stream()
{
	BindingVector::iterator binding_iter;
	bool bogus_sink_detected = false;

	QedoLock lock (bindings_mutex_);

	for (binding_iter = bindings_.begin(); binding_iter != bindings_.end(); binding_iter++)
	{
		if (! (*binding_iter).end_stream())
			bogus_sink_detected = true;
	}

	if (bogus_sink_detected)
		this->remove_bogus_sinks();
}


StreamComponents::BindingDescriptions* 
SourcePort::binding_descriptions() const
{
	StreamComponents::BindingDescriptions_var binding_descs =
        new StreamComponents::BindingDescriptions();

	QedoLock lock (bindings_mutex_);

	binding_descs->length (bindings_.size());

	for (unsigned int i = 0; i < binding_descs->length(); i++)
	{
		(*binding_descs)[i] = bindings_[i].binding_description(); 
	}

    return binding_descs._retn();
}


StreamComponents::SourceDescription* 
SourcePort::source_description() const
{
	StreamComponents::BindingDescriptions_var binding_descs = binding_descriptions();

	StreamComponents::SourceDescription_var src_desc = new SourceDescription_impl (port_name_.c_str(), 
																				   type_id_.c_str(), 
																				   is_multiplex_,
																				   streamtypes_,
																				   binding_descs);

    return src_desc._retn();
}


Cookie_impl*
SourcePort::add_binding (StreamComponents::SinkStreamPort_ptr the_sink,
						 const char* transport_profile)
throw (StreamComponents::InvalidBinding,
       StreamComponents::AlreadyBound,
       StreamComponents::ExceededBindingLimit)
{
	QedoLock lock (bindings_mutex_);

	// Test whether already bound
	if ( !is_multiplex_ && bindings_.size() > 0 )
	{
		DEBUG_OUT2 ("SourcePort: Multiple bindings not allowed for source ", port_name_);
		throw StreamComponents::AlreadyBound();
	}

	// Test for type of binding
	try
	{
		the_sink->check_streamtype (streamtypes_.in());
	}
	catch (StreamComponents::UnsupportedStreamtype& ex)
	{
		std::string message = "SourcePort: UnsupportedStreamtype exception during check_streamtype(): ";
		for ( unsigned int i = 0; i < ex.unsupported_streamtypes.length(); i++)
		{
			if (i)
			{
				message = message + ", ";
			}

			message = message + ex.unsupported_streamtypes[i].in();
		}

		DEBUG_OUT (message.c_str());

		throw StreamComponents::InvalidBinding();
	}
	catch (CORBA::SystemException&)
	{
		DEBUG_OUT ("SourcePort: CORBA system exception during check_streamtype()");
		throw StreamComponents::InvalidBinding();
	}

	// Setup transport
	// If we get a transport_profile parameter different from "", we try to establish
	// a connection using this transport profile and throw an exception on failure
	SourceTransportEndpoint *tep;
	StreamComponents::TransportSpec transport_spec;
	TransportVector::const_iterator transport_iter;

	if (strcmp (transport_profile, ""))
	{
		// Find transport factory
		for (transport_iter = TransportRegistry::transports_.begin();
			 transport_iter != TransportRegistry::transports_.end();
			 transport_iter++)
		{
			if (!strcmp ((*transport_iter).transport_profile_.c_str(), transport_profile))
			{
				// Transport found
				break;
			}
		}
		
		if (transport_iter == TransportRegistry::transports_.end())
		{
			// Not found
			throw StreamComponents::InvalidBinding();
		}

		transport_spec.transport_profile = (*transport_iter).transport_profile_.c_str();
		transport_spec.transport_parameters.length (0);

		try
		{
			the_sink->consider_transport (transport_spec);
		}
		catch (StreamComponents::TransportFailure&)
		{
			DEBUG_OUT2 ("SourcePort: Transport could not be set up for source ", port_name_);
			throw StreamComponents::InvalidBinding();
		}
		catch (CORBA::SystemException&)
		{
			DEBUG_OUT ("SourcePort: CORBA system exception during consider_transport()");
			throw StreamComponents::InvalidBinding();
		}

		// Now create a corresponding transport endpoint that connects to the one denoted in transport_spec.transport_parameters
		tep = (*transport_iter).factory_->create_source_tep();
		tep->setup_connection (transport_spec);

		// Create cookie
		Cookie_impl* new_cookie = new Cookie_impl();

		// Create binding entry
		SourceBinding new_entry (the_sink, new_cookie, tep);

		bindings_.push_back (new_entry);

		tep->_remove_ref();

		return new_cookie;
	}
	else
	{
		for (transport_iter = TransportRegistry::transports_.begin();
			 transport_iter != TransportRegistry::transports_.end();
			transport_iter++)
		{
			DEBUG_OUT2 ("SourcePort: Considering transport: ", (*transport_iter).transport_profile_);

			transport_spec.transport_profile = (*transport_iter).transport_profile_.c_str();
			transport_spec.transport_parameters.length (0);

			try
			{
				the_sink->consider_transport (transport_spec);
			}
			catch (StreamComponents::TransportFailure&)
			{
				DEBUG_OUT2 ("SourcePort: Transport could not be set up for source ", port_name_);
				continue;
			}
			catch (CORBA::SystemException&)
			{
				DEBUG_OUT ("SourcePort: CORBA system exception during consider_transport()");
				continue;
			}

			// Now create a corresponding transport endpoint that connects to the one denoted in transport_spec.transport_parameters
			tep = (*transport_iter).factory_->create_source_tep();
			tep->setup_connection (transport_spec);

			// Create cookie
			Cookie_impl* new_cookie = new Cookie_impl();

			// Create binding entry
			SourceBinding new_entry (the_sink, new_cookie, tep);

			bindings_.push_back (new_entry);

			tep->_remove_ref();

			return new_cookie;
		}
	}

	DEBUG_OUT ("SourcePort: No transport found or no transport found that was able to connect with the SinkPort");

	throw StreamComponents::InvalidBinding();
}


StreamComponents::SinkStreamPort_ptr 
SourcePort::remove_binding (Components::Cookie* cookie)
throw (StreamComponents::InvalidBinding,
       Components::CookieRequired, 
       StreamComponents::NoBinding)
{
	if (is_multiplex_ && ! cookie)	// Multiple source needs cookie
	{
		throw Components::CookieRequired();
	}

	QedoLock lock (bindings_mutex_);
	
	BindingVector::iterator binding_iter;

	// Search binding
    for (binding_iter = bindings_.begin();
         binding_iter != bindings_.end();
         binding_iter++)
    {
		if ((! is_multiplex_ ) ||	// Simple sources always have at most 1 binding
			(*binding_iter).same_binding (cookie)) // Multiple sources need matching cookie
		{
			StreamComponents::SinkStreamPort_var the_sink = (*binding_iter).sink_ref();

			bindings_.erase (binding_iter);

			DEBUG_OUT2 ( "SourcePort: Unbinding from source ", port_name_ );

			return the_sink._retn();
		}
	}

	// Not found
	if (is_multiplex_)
	{
		throw StreamComponents::InvalidBinding();
	}
	else
	{
		throw StreamComponents::NoBinding();
	}
}


void
SourcePort::remove_bogus_sinks()
{
	CORBA::Boolean item_removed;

	do
	{
		BindingVector::iterator binding_iter;
		item_removed = false;

		for (binding_iter = bindings_.begin(); binding_iter != bindings_.end(); binding_iter++)
		{
			item_removed = false;

			if ((*binding_iter).tagged_for_remove())
			{
				bindings_.erase (binding_iter);
				item_removed = true;
				break;
			}
		}
	} while (item_removed);
}


void 
SourcePort::begin_stream (const char* repos_id, const ::Components::ConfigValues& meta_data)
throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream)
{
	// First test whether we are already in a current stream context
	if (active_stream_)
		throw StreamComponents::DuplicateStream();

	// Now test for the compatibility of the streamtype
	unsigned int i;

	for (i = 0; i < streamtypes_->length(); i++)
	{
#ifdef MICO_ORB
		if (! std::strcmp (streamtypes_.in()[i], repos_id))
#else
		if (! std::strcmp (streamtypes_[i], repos_id))
#endif
			break;
	}

	if (i == streamtypes_->length())
	{
		CORBA::RepositoryIdSeq unsupported_streamtype;
		unsupported_streamtype.length (1);
		unsupported_streamtype[0] = CORBA::string_dup (repos_id);
		throw StreamComponents::UnsupportedStreamtype (unsupported_streamtype);
	}

	active_stream_ = true;

	if (configured_for_async_call_)
	{
		// Insert this buffer into our list of buffers to be dispatched
		BeginStreamEntry *new_entry = 
			new BeginStreamEntry (repos_id, meta_data);
		DispatcherEntry_smartptr entry_smartptr (new_entry);
		new_entry->_remove_ref();

		QedoLock lock (dispatcher_entries_mutex_);
		dispatcher_entries_.push_back (entry_smartptr);

		QedoLock lock2 (dispatch_mutex_);
		dispatch_cond_.signal();
	}
	else
	{
		this->dispatch_begin_of_stream (repos_id, meta_data);
	}
}


void 
SourcePort::end_stream()
throw (StreamComponents::NoStream)
{
	// First test whether we are in a current stream context
	if (! active_stream_)
		throw StreamComponents::NoStream();

	active_stream_ = false;

	if (configured_for_async_call_)
	{
		// Insert this buffer into our list of buffers to be dispatched
		EndStreamEntry *new_entry = 
			new EndStreamEntry();
		DispatcherEntry_smartptr entry_smartptr (new_entry);
		new_entry->_remove_ref();

		QedoLock lock (dispatcher_entries_mutex_);
		dispatcher_entries_.push_back (entry_smartptr);

		QedoLock lock2 (dispatch_mutex_);
		dispatch_cond_.signal();
	}
	else
	{
		this->dispatch_end_of_stream();
	}
}


void 
SourcePort::send_buffer (StreamComponents::StreamingBuffer_ptr buffer)
throw (StreamComponents::NoStream)
{
	if (! active_stream_)
		throw StreamComponents::NoStream();

	// If we are not bound, we can simply return
	if (bindings_.size() == 0)
		return;

	if (configured_for_async_call_)
	{
		// Insert this buffer into our list of buffers to be dispatched
		NormalBufferEntry *new_entry = 
			new NormalBufferEntry (buffer);
		DispatcherEntry_smartptr entry_smartptr (new_entry);
		new_entry->_remove_ref();

		QedoLock lock (dispatcher_entries_mutex_);
		dispatcher_entries_.push_back (entry_smartptr);

		QedoLock lock2 (dispatch_mutex_);
		dispatch_cond_.signal();
	}
	else
	{
		// Simply dispatch the buffer
		this->dispatch_buffer (buffer);
	}
}


void
SourcePort::prepare_remove()
{
	if (configured_for_async_call_)
	{
		dispatcher_thread_stopped_ = true;

		// Signal the dispatcher thread
		{
			QedoLock lock (dispatch_mutex_);
			dispatch_cond_.signal();
		}

		dispatcher_thread_->join();
	}

	QedoLock lock (dispatcher_entries_mutex_);
	dispatcher_entries_.clear();

	// Close all transports
	QedoLock lock2 (bindings_mutex_);

	BindingVector::iterator binding_iter;

	for (binding_iter = bindings_.begin(); binding_iter != bindings_.end(); binding_iter++)
	{
		(*binding_iter).close_transport();
	}
}


} // namepace Qedo

#endif
