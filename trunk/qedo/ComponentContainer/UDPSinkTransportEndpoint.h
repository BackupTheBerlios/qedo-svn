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

#ifndef __UDP_SINK_TRANSPORT_ENDPOINT_H__
#define __UDP_SINK_TRANSPORT_ENDPOINT_H__

#ifndef _QEDO_NO_STREAMS


#include "Synchronisation.h"
#include "TransportEndpoint.h"

#ifndef _WIN32
#include <netinet/in.h>
#endif


namespace Qedo {


class UDPSinkTransportEndpoint : public virtual SinkTransportEndpoint
{
private:
#ifdef _WIN32
	SOCKET socket_;
#else
	int socket_;
#endif

	QedoThread* thread_handle_;
	bool thread_stopped_;

	QedoMutex stream_mutex_;
	bool active_stream_;
	bool established_;

	static void* recv_thread (void*);
	void recv_thread_entry();
	void do_recv();

	class ThreadExitHelper
	{
	public:
		UDPSinkTransportEndpoint* thread_class_;
		ThreadExitHelper (UDPSinkTransportEndpoint* thread_class) : thread_class_ (thread_class) 
			{ thread_class_->_add_ref(); }
		~ThreadExitHelper() 
			{ thread_class_->_remove_ref(); }
	};

public:
	UDPSinkTransportEndpoint (SinkPort*, StreamDataDispatcher*);
	virtual ~UDPSinkTransportEndpoint();

	void close();

	void begin_stream();
	
	void end_stream();
	
	void setup_connection (StreamComponents::TransportSpec&)
		throw (StreamComponents::TransportFailure);
};


}


#endif

#endif

