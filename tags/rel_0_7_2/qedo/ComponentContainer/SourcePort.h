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

#ifndef __SOURCE_PORT_H__
#define __SOURCE_PORT_H__

#ifndef _QEDO_NO_STREAMS


#include <CORBA.h>
#include <Components.h>
#include "PortBase.h"
#include "Valuetypes.h"
#include "StreamingValuetypes.h"
#include "StreamingBuffer.h"
#include "TransportRegistry.h"
#include "Util.h"

#include <string>
#include <vector>
#include <queue>

namespace Qedo {


class SourceBinding
{
private:
	StreamComponents::SinkStreamPort_var the_sink_;
	Qedo::Cookie_impl* cookie_;
	bool connected_;
	bool tagged_for_remove_;
	SourceTransportEndpoint* tep_;

public:
	SourceBinding (StreamComponents::SinkStreamPort_ptr, Qedo::Cookie_impl*, SourceTransportEndpoint*);

	SourceBinding();

	SourceBinding (const SourceBinding& binding);

	SourceBinding& operator= (const SourceBinding&);

    ~SourceBinding();
    
	bool operator < (const SourceBinding&) const {return true;}
	bool operator == (const SourceBinding&) const {return true;}

	CORBA::Boolean tagged_for_remove() { return tagged_for_remove_; }
	void tag_for_remove() { tagged_for_remove_ = true; }

	bool begin_stream (const char*, const ::Components::ConfigValues&);

	bool end_stream();

	bool send_buffer (StreamComponents::StreamingBuffer_ptr);

	void close_transport();

    BindingDescription_impl* binding_description() const;

	const StreamComponents::SinkStreamPort_ptr sink_ref() const
	{
		return StreamComponents::SinkStreamPort::_duplicate (the_sink_.in());
	}

    Cookie_impl* cookie() const;

	CORBA::Boolean same_binding (Components::Cookie* cookie) const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<SourceBinding>;
typedef std::vector<SourceBinding> BindingVector;


// The base calss for all dispatcher list entries
class DispatcherEntry : public virtual RefCountBase
{
public:
	enum EntryType {NORMAL_BUFFER, BEGIN_OF_STREAM, END_OF_STREAM};
	
	EntryType entry_type_;
	
	DispatcherEntry (EntryType);
	DispatcherEntry (const DispatcherEntry&);
	DispatcherEntry& operator= (const DispatcherEntry&);
	virtual ~DispatcherEntry();
};


class NormalBufferEntry : public DispatcherEntry
{
private:
	NormalBufferEntry();

public:
	StreamComponents::StreamingBuffer_var buffer_;

	NormalBufferEntry (StreamComponents::StreamingBuffer_ptr);
	NormalBufferEntry (const NormalBufferEntry&);
	NormalBufferEntry& operator= (const NormalBufferEntry&);
	virtual ~NormalBufferEntry();
};


class BeginStreamEntry : public DispatcherEntry
{
private:
	BeginStreamEntry();

public:
	std::string repos_id_;
	::Components::ConfigValues_var meta_data_;

	BeginStreamEntry (const char*, const ::Components::ConfigValues&);
	BeginStreamEntry (const BeginStreamEntry&);
	BeginStreamEntry& operator= (const BeginStreamEntry&);
	~BeginStreamEntry();
};


class EndStreamEntry : public DispatcherEntry
{
public:
	EndStreamEntry();
	EndStreamEntry (const EndStreamEntry&);
	EndStreamEntry& operator= (const EndStreamEntry&);
	~EndStreamEntry();
};


class DispatcherEntry_smartptr
{
private:
	DispatcherEntry* dispatcher_entry_;

	DispatcherEntry_smartptr();
	
public:
	DispatcherEntry_smartptr (DispatcherEntry*);
	DispatcherEntry_smartptr (const DispatcherEntry_smartptr& dispatcher_entry_smartptr);
	DispatcherEntry_smartptr& operator= (const DispatcherEntry_smartptr& dispatcher_entry_smartptr);
	~DispatcherEntry_smartptr();

	DispatcherEntry* ptr() { return dispatcher_entry_; }
	DispatcherEntry* operator->() { return dispatcher_entry_; }
	const DispatcherEntry* operator->() const { return dispatcher_entry_; }
	DispatcherEntry& operator*() { return *dispatcher_entry_; }
};


CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<StreamComponents::StreamingBuffer_ptr>;
typedef std::vector<DispatcherEntry_smartptr> DispatcherVector;


class SourcePort : public virtual PortBase,
				   public virtual RefCountBase
{
private:
	bool is_multiplex_;
	bool active_stream_;
	CORBA::RepositoryIdSeq_var streamtypes_;
	bool configured_for_async_call_;
	bool dispatcher_thread_stopped_;

	BindingVector bindings_;
	QedoMutex bindings_mutex_;

	QedoMutex dispatch_mutex_;
	QedoCond dispatch_cond_;

	DispatcherVector dispatcher_entries_;
	QedoMutex dispatcher_entries_mutex_;
	
	void do_dispatch();
	static void* dispatcher_thread (void*);

	QedoThread* dispatcher_thread_;
	void dispatch_buffer (StreamComponents::StreamingBuffer_ptr);
	void dispatch_begin_of_stream (const char*, const ::Components::ConfigValues&);
	void dispatch_end_of_stream();

public:
	class ThreadExitHelper
	{
	public:
		SourcePort* thread_class_;
		ThreadExitHelper (SourcePort* thread_class) : thread_class_ (thread_class) 
			{ thread_class_->_add_ref(); }
		~ThreadExitHelper() 
			{ thread_class_->_remove_ref(); }
	};

	SourcePort (const char*, 
				const char*, 
				CORBA::Boolean, 
				const CORBA::RepositoryIdSeq&,
				bool);

	SourcePort();

	SourcePort (const SourcePort&);

	SourcePort& operator= (const SourcePort&);

    ~SourcePort();

	bool operator < (const SourcePort&) const {return true;}

	bool operator == (const SourcePort&) const {return true;}

	void remove_bogus_sinks();

    StreamComponents::BindingDescriptions* binding_descriptions() const;

    StreamComponents::SourceDescription* source_description() const;

	Cookie_impl* add_binding (StreamComponents::SinkStreamPort_ptr, const char*)
        throw (StreamComponents::InvalidBinding,
               StreamComponents::AlreadyBound,
               StreamComponents::ExceededBindingLimit);

	StreamComponents::SinkStreamPort_ptr remove_binding (Components::Cookie*)
        throw (StreamComponents::InvalidBinding,
	           Components::CookieRequired, 
		       StreamComponents::NoBinding);

	// Begin a stream
	void begin_stream (const char*, const ::Components::ConfigValues&)
		throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream);

	// End a stream
	void end_stream()
		throw (StreamComponents::NoStream);

	// Send data for a stream
	void send_buffer (StreamComponents::StreamingBuffer_ptr)
		throw (StreamComponents::NoStream);

	// Close all transports when removing the SourcePort during remove of the component
	void prepare_remove();
};


class SourcePort_smartptr
{
private:
	SourcePort* source_port_;
	
public:
	SourcePort_smartptr (SourcePort* source_port) : source_port_ (source_port) { source_port_->_add_ref(); }
	SourcePort_smartptr() {}
	SourcePort_smartptr (const SourcePort_smartptr& source_port_smartptr) 
		: source_port_ (source_port_smartptr.source_port_) { source_port_->_add_ref(); }
	SourcePort_smartptr& operator= (const SourcePort_smartptr& source_port_smartptr)
	{
		if (source_port_)
			source_port_->_remove_ref();

		source_port_ = source_port_smartptr.source_port_;
		source_port_->_add_ref();

		return *this;
	}
	~SourcePort_smartptr() { source_port_->_remove_ref(); }

	SourcePort* operator->() { return source_port_; }
	const SourcePort* operator->() const { return source_port_; }
	SourcePort& operator*() { return *source_port_; }

	bool operator < (const SourcePort_smartptr&) const {return true;}
	bool operator == (const SourcePort_smartptr&) const {return true;}
};


// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<SourcePort_smartptr>;
typedef std::vector<SourcePort_smartptr> SourceVector;


} // namespace Qedo

#endif

#endif

