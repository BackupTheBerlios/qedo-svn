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

#ifndef __SINK_PORT_H__
#define __SINK_PORT_H__

#ifndef _QEDO_NO_STREAMS


#include <CORBA.h>
#include <StreamComponents_skel.h>

#include "PortBase.h"
#include "RefCountBase.h"
#include "StreamDataDispatcher.h"
#include "Util.h"
#include "TransportRegistry.h"

#include <string>
#include <vector>


namespace Qedo {


class SinkPort : public virtual PortBase,
				 public virtual RefCountBase
{
private:
	CORBA::RepositoryIdSeq_var streamtypes_;
    StreamComponents::SinkStreamPort_var the_sink_;
	Qedo::StreamDataDispatcher* dispatcher_;
	CORBA::Boolean bound_;
	CORBA::Boolean active_stream_;
	SinkTransportEndpoint* tep_;

	QedoMutex transport_closure_mutex_;

public:
	SinkPort (const char*, 
			  const char*, 
			  const CORBA::RepositoryIdSeq&, 
			  StreamComponents::SinkStreamPort_ptr,
			  Qedo::StreamDataDispatcher*);

	SinkPort();

	SinkPort (const SinkPort&);

    ~SinkPort();

	bool operator < (const SinkPort&) const {return true;}

	bool operator == (const SinkPort&) const {return true;}

    StreamComponents::SinkDescription* sink_description() const;

    const StreamComponents::SinkStreamPort_ptr sink_ref() const;

	// Begin a stream
	void begin_stream (const char*, const Components::ConfigValues&)
		throw (StreamComponents::UnsupportedStreamtype, StreamComponents::DuplicateStream);

	// End a stream
	void end_stream()
		throw (StreamComponents::NoStream);

	// Inform about successfull establishment of the transport (callback from TEP)
	void transport_established();

	// Inform about unexpected closure of the TEP (callback from TEP)
	void transport_closed();

	// Close the transport when removing the SinkPort during remove of the component
	void prepare_remove();

	void check_streamtype(const CORBA::RepositoryIdSeq&)
        throw(StreamComponents::UnsupportedStreamtype,
              CORBA::SystemException);

    void consider_transport(StreamComponents::TransportSpec&)
        throw(StreamComponents::AlreadyBound,
			  StreamComponents::TransportFailure,
              CORBA::SystemException);
};


class SinkPort_smartptr
{
private:
	SinkPort* sink_port_;
	
public:
	SinkPort_smartptr (SinkPort* sink_port) : sink_port_ (sink_port) { sink_port_->_add_ref(); }
	SinkPort_smartptr() {}
	SinkPort_smartptr (const SinkPort_smartptr& sink_port_smartptr) 
		: sink_port_ (sink_port_smartptr.sink_port_) { sink_port_->_add_ref(); }
	SinkPort_smartptr& operator= (const SinkPort_smartptr& sink_port_smartptr)
	{
		if (sink_port_)
			sink_port_->_remove_ref();

		sink_port_ = sink_port_smartptr.sink_port_;
		sink_port_->_add_ref();

		return *this;
	}
	~SinkPort_smartptr() { sink_port_->_remove_ref(); }

	SinkPort* operator->() { return sink_port_; }
	const SinkPort* operator->() const { return sink_port_; }
	SinkPort& operator*() { return *sink_port_; }

	bool operator < (const SinkPort_smartptr&) const {return true;}
	bool operator == (const SinkPort_smartptr&) const {return true;}
};


// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<SinkPort_smartptr>;
typedef std::vector<SinkPort_smartptr> SinkVector;


} // namespace Qedo

#endif

#endif

