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

#ifndef __TCP_SINK_TRANSPORT_ENDPOINT_H__
#define __TCP_SINK_TRANSPORT_ENDPOINT_H__

#ifndef _QEDO_NO_STREAMS


#include "Synchronisation.h"
#include "TransportEndpoint.h"

#ifndef _WIN32
#include <netinet/in.h>
#endif


namespace Qedo {


class TCPSinkTransportEndpoint : public virtual SinkTransportEndpoint
{
private:
	StreamDataDispatcher* dispatcher_;
	bool listening_;
	bool connected_;
	bool stream_demarcation_detected_;
	CORBA::UShort current_stream_number_;

	QedoMutex transport_closure_mutex_;
	QedoMutex acceptor_thread_stop_mutex_;

	QedoCond end_stream_cond_;
	QedoMutex end_stream_mutex_;
	bool end_stream_tag_;

	QedoCond pause_stream_cond_;
	QedoMutex pause_stream_mutex_;
	bool pause_stream_tag_;

#ifdef _WIN32
	SOCKET listen_socket_;
	SOCKET accept_socket_;
#else
	int listen_socket_;
	int accept_socket_;
#endif

#ifdef _WIN32
	bool recv_complete (SOCKET sock, char* buf, int len);
#else
	bool recv_complete (int sock, char* buf, int len);
#endif

	void check_wait_or_signal_end_stream();
	void check_wait_or_signal_pause_stream();

	QedoThread* acceptor_thread_handle_;

	bool acceptor_thread_stopped_;

	static void* acceptor_thread (void*);
	void do_read();
	void do_accept();

	void close_transport();

public:
	class ThreadExitHelper
	{
	public:
		TCPSinkTransportEndpoint* thread_class_;
		ThreadExitHelper (TCPSinkTransportEndpoint* thread_class) : thread_class_ (thread_class) 
			{ thread_class_->_add_ref(); }
		~ThreadExitHelper() 
			{ thread_class_->_remove_ref(); }
	};

	TCPSinkTransportEndpoint (SinkPort*, StreamDataDispatcher*);
	virtual ~TCPSinkTransportEndpoint();

	void close();

	void begin_stream();
	
	void end_stream();
	
	void setup_for_accept (StreamComponents::TransportSpec&)
		throw (StreamComponents::TransportFailure);
};


}


#endif

#endif

