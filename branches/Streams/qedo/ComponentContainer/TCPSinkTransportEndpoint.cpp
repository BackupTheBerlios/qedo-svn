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

static char rcsid[] = "$Id: TCPSinkTransportEndpoint.cpp,v 1.1.2.1 2003/09/26 14:26:02 stoinski Exp $";

#ifndef _QEDO_NO_STREAMS

#include "Winsock2.h"

#include "TCPSinkTransportEndpoint.h"
#include "SinkPort.h"
#include "Output.h"
#include "StreamingBuffer.h"
#include "Valuetypes.h"

#include <cstdlib>
#include <cstring>

namespace Qedo {


TCPSinkTransportEndpoint::TCPSinkTransportEndpoint (SinkPort* my_sink, StreamDataDispatcher* dispatcher)
: SinkTransportEndpoint (my_sink),
  dispatcher_ (dispatcher),
  connected_ (false),
  listening_ (false),
  pause_stream_cond_ ("TCP_SINK_TEP_PAUSE"),
  end_stream_cond_ ("TCP_SINK_TEP_END"),
  acceptor_thread_stopped_ (false),
  end_stream_tag_ (false),
  pause_stream_tag_ (false),
  current_stream_number_ (0)
{
	dispatcher_->_add_ref();
}


TCPSinkTransportEndpoint::~TCPSinkTransportEndpoint()
{
	DEBUG_OUT ("TCPSinkTransportEndpoint: Destructor called");

	dispatcher_->_remove_ref();
}


void 
TCPSinkTransportEndpoint::check_wait_or_signal_end_stream()
{
	QedoLock lock (end_stream_mutex_);
	if (! end_stream_tag_)
	{
		// I'm the first
		end_stream_tag_ = true;
		end_stream_cond_.wait (end_stream_mutex_);
	}
	else
	{
		// I'm the second
		end_stream_tag_ = false;
		end_stream_cond_.signal();
	}
}


void 
TCPSinkTransportEndpoint::check_wait_or_signal_pause_stream()
{
	QedoLock lock (pause_stream_mutex_);
	if (! pause_stream_tag_)
	{
		// I'm the first
		pause_stream_tag_ = true;
		pause_stream_cond_.wait (pause_stream_mutex_);
	}
	else
	{
		// I'm the second
		pause_stream_tag_ = false;
		pause_stream_cond_.signal();
	}
}


bool
TCPSinkTransportEndpoint::recv_complete (
#ifdef _WIN32
	SOCKET sock,
#else
#endif
	char* buf,
	int len)
{
	int bytes_received = 0;
	int bytes_left = len;

	while (bytes_left)
	{
		if ((bytes_received = recv (sock, buf + len - bytes_left, bytes_left, 0)) == SOCKET_ERROR)
		{
			DEBUG_OUT ("TCPSinkTransportEndpoint: recv_complete(): recv() call failed");
			DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
			return false;
		}
		bytes_left -= bytes_received;
	}

	return true;
}


void*
TCPSinkTransportEndpoint::acceptor_thread (void* data)
{
	TCPSinkTransportEndpoint* this_ptr = (TCPSinkTransportEndpoint*)data;

	DEBUG_OUT ("TCPSinkTransportEndpoint: Acceptor main thread routine started");

	this_ptr->do_accept();

	DEBUG_OUT ("TCPSinkTransportEndpoint: Acceptor main thread routine finished");

	// We must return something, why not the data value ;-)
	return data;
}


void
TCPSinkTransportEndpoint::do_read()
{
	stream_demarcation_detected_ = false;

#ifdef _WIN32
	// Now read from accept socket and dispatch data
	StreamComponents::TCPProfileHeader header;

	while (! acceptor_thread_stopped_)
	{
		if (! recv_complete (accept_socket_, (char*)&header, sizeof (header)))
		{
			DEBUG_OUT ("TCPSinkTransportEndpoint: do_accept(): Cannot read header");
			dispatcher_->failed_stream();
			return;		// End thread
		}

		CORBA::UShort stream_number = header.stream_number;
		CORBA::ULong seq_length = ntohl (header.seq_length);

		// Check for the final TCP packet (sequence length of 0)
		if (! seq_length)
		{
			DEBUG_OUT ("TCPSinkTransportEndpoint: Final packet detected, stream ends");

			this->check_wait_or_signal_end_stream();

			// We are going to be removed
			if (acceptor_thread_stopped_ )
				return;

			// Now pause reading until the next begin_stream_operation()
			this->check_wait_or_signal_pause_stream();

			continue;	// Now we are in the context of the next stream, go ahead and read stream data
		}

		// TODO @@@: This is wrong code, current_stream_number gets never set (low priority to fix)
		if (current_stream_number_ && stream_number != current_stream_number_)
		{
			// Stream demarcation detected without being called end_stream()
			DEBUG_OUT ("TCPSinkTransportEndpoint: Illegal change of current stream number");
			dispatcher_->failed_stream();
			return;		// End thread
		}

		DEBUG_OUT2 ("TCPSinkTransportEndpoint: Received a packet with stream number: ", (int)stream_number);

		// Read and dispatch data
		StreamComponents::StreamingBuffer_var buffer;
		buffer = new StreamingBuffer (seq_length);

		if (! recv_complete (accept_socket_, (char*)buffer->get_buffer(), seq_length))
		{
			DEBUG_OUT ("TCPSinkTransportEndpoint: do_accept(): Cannot read payload");
			dispatcher_->failed_stream();
			return;		// End thread
		}

		dispatcher_->receive_stream_data (buffer);
	}
#else
#endif
}


void
TCPSinkTransportEndpoint::do_accept()
{
#ifdef _WIN32
	struct fd_set my_fd_set;

	FD_ZERO (&my_fd_set);
	FD_SET (listen_socket_, &my_fd_set);
	
	DEBUG_OUT ("TCPSinkTransportEndpoint: Going to select");
	if (select (0 /*this parameter is ignored under Windows*/, 
			&my_fd_set /*for read*/, 
			NULL /*for write*/, 
			NULL /*for errors*/, 
			NULL /*no timeout*/) == SOCKET_ERROR)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: do_accept(): select() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
		dispatcher_->failed_stream();
		return;		// End thread
	}

	struct sockaddr_in foreign_sock_addr;
	int sock_addr_len = sizeof (foreign_sock_addr);

	if ((accept_socket_ = 
		accept (listen_socket_, (struct sockaddr*)&foreign_sock_addr, &sock_addr_len)) == INVALID_SOCKET)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: do_accept(): accept() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
		dispatcher_->failed_stream();
		return;		// End thread
	}

	connected_ = true;

	my_sink_->transport_established();

#ifdef _DEBUG
	std::string message;
	message = "TCPSinkTransportEndpoint: Accepted a connection from address ";
	message += inet_ntoa (foreign_sock_addr.sin_addr);
	message += " on port ";
	DEBUG_OUT2 (message.c_str(), ntohs (foreign_sock_addr.sin_port));
#endif
#else
#endif

	// Wait for the begin_stream() operation
	this->check_wait_or_signal_pause_stream();

	this->do_read();

	// Okay, when we are here, the transport endpoint was closed
	// This could be because of a failure of the network subsystem or because of
	// a close() call on the Sink
	// We only tell the sink about the closure when we are not in the scope of a close() operation on the Sink
	
	// Keep a reference to this until the thread has finished
	ThreadExitHelper thread_exit_helper (this);

	// We only tell the sink about the closure when we are not in the scope of a close() operation on the Sink
	{
		QedoLock lock (acceptor_thread_stop_mutex_);
		if (! acceptor_thread_stopped_)
		{
			this->close_transport();
			my_sink_->transport_closed();
		}
	}
}


void
TCPSinkTransportEndpoint::close_transport()
{
	QedoLock lock (transport_closure_mutex_);
	
	if (listening_)
	{
#ifdef _WIN32
		shutdown (listen_socket_, SD_BOTH);
		closesocket (listen_socket_);
		if (connected_)
		{
			shutdown (accept_socket_, SD_BOTH);
			closesocket (accept_socket_);

			connected_ = false;
		}
#else
#endif

		listening_ = false;
	}
}


void
TCPSinkTransportEndpoint::close()
{
	DEBUG_OUT ("TCPSinkTransportEndpoint: close() called");

	{
		QedoLock a_lock (acceptor_thread_stop_mutex_);

		acceptor_thread_stopped_ = true;

		this->close_transport();

		// The acceptor is possibly waiting for the end_stream_mutex_ or pause_stream_mutex_ variable
		// Try to wake it up
		{
			QedoLock lock (end_stream_mutex_);
			if (end_stream_tag_)
			{
				end_stream_cond_.signal();
			}
		}
		{
			QedoLock lock (pause_stream_mutex_);
			if (pause_stream_tag_)
			{
				pause_stream_cond_.signal();
			}
		}
	}

	// When we are closed, we join the acceptor thread
	// Note: we do not joint the acceptor thread when it terminates without the impact of the close_transport()
	// call in this close() call (e.g. because of the source components destruction)
	acceptor_thread_handle_->join();
}


void 
TCPSinkTransportEndpoint::setup_for_accept (StreamComponents::TransportSpec& transport_spec)
throw (StreamComponents::TransportFailure)
{
	// Open a TCP stream socket and store the transport parameters in the transport_spec variable
	DEBUG_OUT ("TCPSinkTransportEndpoint: setup_for_accept() called");

#ifdef _WIN32
	if ((listen_socket_ = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: setup_for_accept(): socket() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());

		throw StreamComponents::TransportFailure();
	}

	// We need to get our network address, so first figure out our name
	char hostname[100];
	if (gethostname (hostname, 100) == SOCKET_ERROR)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: setup_for_accept(): gethostname() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
		closesocket (listen_socket_);
		throw StreamComponents::TransportFailure();
	}

	// Now resolve our network address
	struct hostent* my_host;

	if ((my_host = gethostbyname (hostname)) == NULL)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: setup_for_accept(): gethostbyname() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
		closesocket (listen_socket_);
		throw StreamComponents::TransportFailure();
	}

	// Take the first network address (do we also have to consider h_addrtype???)
	struct sockaddr_in my_sock_addr;
	std::memcpy (&my_sock_addr.sin_addr.s_addr, (my_host->h_addr_list)[0], sizeof (my_sock_addr.sin_addr.s_addr));

	my_sock_addr.sin_family = AF_INET;
	my_sock_addr.sin_port = 0;		// Let the system decide which port to assign
	
	// Bind the socket
	if (bind (listen_socket_, (const sockaddr*)&my_sock_addr, sizeof (my_sock_addr)) == SOCKET_ERROR)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: setup_for_accept(): bind() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
		closesocket (listen_socket_);
		throw StreamComponents::TransportFailure();
	}

	// Get the assigned port number
	int sock_addr_len = sizeof (my_sock_addr);

	if (getsockname (listen_socket_, (struct sockaddr*)&my_sock_addr, &sock_addr_len) == SOCKET_ERROR)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: setup_for_accept(): getsockname() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
		closesocket (listen_socket_);
		throw StreamComponents::TransportFailure();
	}

	// Store the transport parameters in our transport spec
	if (transport_spec.transport_parameters.length())
	{
		NORMAL_OUT ("TCPSinkTransportEndpoint: setup_for_accept(): Warning: transport_parameters sequence already holds items");
		transport_spec.transport_parameters.length (0);
	}

	// Build up ConfigValues sequence with the transport parameters
	CORBA::Any any;
	transport_spec.transport_parameters.length (2);
	transport_spec.transport_parameters[0] = new ConfigValue_impl();
	transport_spec.transport_parameters[0]->name (CORBA::string_dup ("HOSTNAME"));
	any <<= inet_ntoa (my_sock_addr.sin_addr);
	transport_spec.transport_parameters[0]->value (any);
	transport_spec.transport_parameters[1] = new ConfigValue_impl();
	transport_spec.transport_parameters[1]->name (CORBA::string_dup ("PORTNUMBER"));

	any <<= my_sock_addr.sin_port;		// Port number was assigned by the system and is in network byte order already
	transport_spec.transport_parameters[1]->value (any);

#ifdef _DEBUG
	std::string message;
	message = "TCPSinkTransportEndpoint: Bound to address ";
	message += inet_ntoa (my_sock_addr.sin_addr);
	message += " on port ";
	DEBUG_OUT2 (message.c_str(), ntohs (my_sock_addr.sin_port));
#endif

	if (listen (listen_socket_, 1) == SOCKET_ERROR)
	{
		DEBUG_OUT ("TCPSinkTransportEndpoint: setup_for_accept(): listen() call failed");
		DEBUG_OUT2 ("TCPSinkTransportEndpoint: error code was ", WSAGetLastError());
		closesocket (listen_socket_);
		throw StreamComponents::TransportFailure();
	}

	listening_ = true;

	// Now accept a connection (this must be handled by a thread)
	acceptor_thread_handle_ = qedo_startDetachedThread (this->acceptor_thread, this);
#else
#endif
}


void
TCPSinkTransportEndpoint::begin_stream()
{
	// Signal my reader thread that it can go ahead
	this->check_wait_or_signal_pause_stream();
}


void
TCPSinkTransportEndpoint::end_stream()
{
	this->check_wait_or_signal_end_stream();
}


} // namespace Qedo

#endif