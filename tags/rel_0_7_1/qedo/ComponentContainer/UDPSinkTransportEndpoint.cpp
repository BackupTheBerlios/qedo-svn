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

#ifdef _WIN32
#include "Winsock2.h"
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

#include "UDPSinkTransportEndpoint.h"
#include "SinkPort.h"
#include "Output.h"
#include "MarshalBuffer.h"
#include "Valuetypes.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>

#define MAX_DGRAM_SIZE 32768

static char rcsid[] UNUSED = "$Id: UDPSinkTransportEndpoint.cpp,v 1.5 2004/06/24 14:36:08 tom Exp $";


namespace Qedo {


UDPSinkTransportEndpoint::UDPSinkTransportEndpoint (SinkPort* my_sink, StreamDataDispatcher* dispatcher)
: SinkTransportEndpoint (my_sink, dispatcher),
  thread_stopped_ (false),
  active_stream_ (false),
  established_ (false)
{
}


UDPSinkTransportEndpoint::~UDPSinkTransportEndpoint()
{
	DEBUG_OUT ("UDPSinkTransportEndpoint: Destructor called");
}


void* 
UDPSinkTransportEndpoint::recv_thread (void* data)
{
	UDPSinkTransportEndpoint* this_ptr = (UDPSinkTransportEndpoint*)data;

	DEBUG_OUT ("UDPSinkTransportEndpoint: Main thread routine started");

	this_ptr->recv_thread_entry();

	DEBUG_OUT ("UDPSinkTransportEndpoint: Main thread routine finished");

	// We must return something, why not the data value ;-)
	return data;
}


void
UDPSinkTransportEndpoint::recv_thread_entry()
{
	// Keep a reference to this until the thread has finished
	ThreadExitHelper thread_exit_helper (this);

	this->do_recv();
}


void
UDPSinkTransportEndpoint::do_recv()
{
	// Mutex einbauen
	// Thread empfängt nur Pakete, wenn in einem aktiven Stream
	// Pakete mit Nummer ungleich meiner aktuellen werden verworfen

	struct sockaddr_in sender_address;

#ifdef _WIN32
	int sender_address_size;
#else
	socklen_t sender_address_size;
#endif

	sender_address_size = sizeof(sender_address);

	//StreamComponents::UDPProfileHeader header;
	char datagram[MAX_DGRAM_SIZE];

	while (! thread_stopped_)
	{
#ifdef _WIN32
		if (recvfrom (socket_, datagram, MAX_DGRAM_SIZE, 0, (struct sockaddr*)&sender_address, &sender_address_size) == SOCKET_ERROR)
#else
		if (recvfrom (socket_, datagram, MAX_DGRAM_SIZE, 0, (struct sockaddr*)&sender_address, &sender_address_size) == -1)
#endif
		{
			DEBUG_OUT ("UDPSinkTransportEndpoint: do_recv(): Cannot read datagram");
#ifdef _WIN32
			DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", WSAGetLastError());
#else
			DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", errno);
#endif

			if (active_stream_)
				dispatcher_->failed_stream();
			return;		// End thread
		}

#ifdef _DEBUG
		std::string message;
		message = "UDPSinkTransportEndpoint: Got a datagram from address ";
		message += inet_ntoa (sender_address.sin_addr);
		message += " on port ";
		DEBUG_OUT2 (message.c_str(), ntohs (sender_address.sin_port));
#endif

		StreamComponents::UDPProfileHeader* header = reinterpret_cast <StreamComponents::UDPProfileHeader*> (datagram);

		CORBA::UShort stream_number = ntohs (header->stream_number);
		CORBA::ULong seq_length = ntohl (header->seq_length);

		UnmarshalBuffer* buffer;
		buffer = new UnmarshalBuffer (seq_length);

		memcpy (buffer->get_buffer(), datagram + sizeof (StreamComponents::UDPProfileHeader), seq_length);

		QedoLock lock (stream_mutex_);

		if (active_stream_)
			dispatcher_->receive_stream (buffer);

		buffer->_remove_ref();
	}
}


void
UDPSinkTransportEndpoint::close()
{
	DEBUG_OUT ("UDPSinkTransportEndpoint: close() called");

	thread_stopped_ = true;

#ifdef _WIN32
	shutdown (socket_, SD_BOTH);
	closesocket (socket_);
	
	established_ = false;
#else
	shutdown (socket_, 2);
	::close (socket_);
		
	established_ = false;
#endif

	if (thread_handle_)
		thread_handle_->join();
}


void 
UDPSinkTransportEndpoint::setup_connection (StreamComponents::TransportSpec& transport_spec)
throw (StreamComponents::TransportFailure)
{
	// Open a UDP datagram socket and store the transport parameters in the transport_spec variable
	DEBUG_OUT ("UDPSinkTransportEndpoint: setup_connection() called");

#ifdef _WIN32
	if ((socket_ = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
#else
	if ((socket_ = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
#endif
	{
		DEBUG_OUT ("UDPSinkTransportEndpoint: setup_connection(): socket() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", errno);
#endif

		throw StreamComponents::TransportFailure();
	}

	// We need to get our network address, so first figure out our name
	char hostname[100];

#ifdef _WIN32
	if (gethostname (hostname, 100) == SOCKET_ERROR)
#else
	if (gethostname (hostname, 100) == -1)
#endif

	{
		DEBUG_OUT ("UDPSinkTransportEndpoint: setup_connection(): gethostname() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", errno);
#endif

#ifdef _WIN32
		closesocket (socket_);
#else
		::close (socket_);
#endif
		throw StreamComponents::TransportFailure();
	}

	// Now resolve our network address
	struct hostent* my_host;

	if ((my_host = gethostbyname (hostname)) == NULL)
	{
		DEBUG_OUT ("UDPSinkTransportEndpoint: setup_connection(): gethostbyname() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", errno);
#endif

#ifdef _WIN32
		closesocket (socket_);
#else
		::close (socket_);
#endif

		throw StreamComponents::TransportFailure();
	}

	// Take the first network address (do we also have to consider h_addrtype???)
	struct sockaddr_in my_sock_addr;
	std::memcpy (&my_sock_addr.sin_addr.s_addr, (my_host->h_addr_list)[0], sizeof (my_sock_addr.sin_addr.s_addr));

	my_sock_addr.sin_family = AF_INET;
	my_sock_addr.sin_port = 0;		// Let the system decide which port to assign
	
	// Bind the socket
#ifdef _WIN32
	if (bind (socket_, (const sockaddr*)&my_sock_addr, sizeof (my_sock_addr)) == SOCKET_ERROR)
#else
	if (bind (socket_, (const sockaddr*)&my_sock_addr, sizeof (my_sock_addr)) == -1)
#endif

	{
		DEBUG_OUT ("UDPSinkTransportEndpoint: setup_connection(): bind() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", errno);
#endif

#ifdef _WIN32
		closesocket (socket_);
#else
		::close (socket_);
#endif

		throw StreamComponents::TransportFailure();
	}

	// Get the assigned port number
#ifdef _WIN32
	int sock_addr_len;
#else
	socklen_t sock_addr_len;
#endif

	sock_addr_len = sizeof (my_sock_addr);

#ifdef _WIN32
	if (getsockname (socket_, (struct sockaddr*)&my_sock_addr, &sock_addr_len) == SOCKET_ERROR)
#else
	if (getsockname (socket_, (struct sockaddr*)&my_sock_addr, &sock_addr_len) == -1)
#endif
	{
		DEBUG_OUT ("UDPSinkTransportEndpoint: setup_connection(): getsockname() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("UDPSinkTransportEndpoint: error code was ", errno);
#endif

#ifdef _WIN32
		closesocket (socket_);
#else
		::close (socket_);
#endif

		throw StreamComponents::TransportFailure();
	}

	// Store the transport parameters in our transport spec
	if (transport_spec.transport_parameters.length())
	{
		NORMAL_OUT ("UDPSinkTransportEndpoint: setup_connection(): Warning: transport_parameters sequence already holds items");
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
	message = "UDPSinkTransportEndpoint: Bound to address ";
	message += inet_ntoa (my_sock_addr.sin_addr);
	message += " on port ";
	DEBUG_OUT2 (message.c_str(), ntohs (my_sock_addr.sin_port));
#endif

	// Start thread
	thread_handle_ = qedo_startDetachedThread (this->recv_thread, this);

	established_ = true;
}


void
UDPSinkTransportEndpoint::begin_stream()
{
	QedoLock lock (stream_mutex_);
	active_stream_ = true;
}


void
UDPSinkTransportEndpoint::end_stream()
{
	QedoLock lock (stream_mutex_);
	active_stream_ = false;
}


} // namespace Qedo

#endif

