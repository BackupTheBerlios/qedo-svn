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

#ifndef __TRANSPORT_ENDPOINT_H__
#define __TRANSPORT_ENDPOINT_H__

#ifndef _QEDO_NO_STREAMS


#include "CORBA.h"
#include "StreamComponents.h"

#include "RefCountBase.h"
#include "StreamDataDispatcher.h"


namespace Qedo {

class SinkPort;

class TransportEndpoint : public virtual RefCountBase
{
protected:
	int rand_int();

public:
	TransportEndpoint();
	virtual ~TransportEndpoint();

	virtual void begin_stream() = 0;
	virtual void end_stream() = 0;

	virtual void close() = 0;
};


class SourceTransportEndpoint : public virtual TransportEndpoint
{
public:
	SourceTransportEndpoint();
	virtual ~SourceTransportEndpoint();

	virtual void setup_for_connect (StreamComponents::TransportSpec&)
		throw (StreamComponents::TransportFailure) = 0;

	virtual bool send_buffer (StreamComponents::StreamingBuffer_ptr) = 0;
};

	
class SinkTransportEndpoint : public virtual TransportEndpoint
{
protected:
	SinkPort* my_sink_;

public:
	SinkTransportEndpoint (SinkPort*);
	virtual ~SinkTransportEndpoint();

	virtual void setup_for_accept (StreamComponents::TransportSpec&)
		throw (StreamComponents::TransportFailure) = 0;
};


class TransportEndpointFactory : public virtual RefCountBase
{
public:
	TransportEndpointFactory();
	virtual ~TransportEndpointFactory();

	virtual SourceTransportEndpoint* create_source_tep() = 0;
	virtual SinkTransportEndpoint* create_sink_tep (SinkPort*, StreamDataDispatcher*) = 0;
};


} // namespace Qedo

#endif

#endif

