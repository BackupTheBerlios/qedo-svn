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


#ifndef _QEDO_NO_STREAMS

#ifdef _WIN32
#include "winsock2.h"
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "TCPSourceTransportEndpoint.h"
#include "Output.h"
#include "Valuetypes.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>


static char rcsid[] UNUSED = "$Id: TCPSourceTransportEndpoint.cpp,v 1.2 2003/10/17 09:11:41 stoinski Exp $";

namespace Qedo {

	
TCPSourceTransportEndpoint::TCPSourceTransportEndpoint()
: connected_ (false)
{
	current_stream_number_ = (this->rand_int()) & 0xFFFF;
}


TCPSourceTransportEndpoint::~TCPSourceTransportEndpoint()
{
	DEBUG_OUT ("TCPSourceTransportEndpoint: Destructor called");
}


bool
TCPSourceTransportEndpoint::send_complete (
#ifdef _WIN32
	SOCKET sock,
#else
	int sock,
#endif
	const char* data,
	int len)
{
	int bytes_sent = 0;
	int bytes_left = len;

	while (bytes_left)
	{
#ifdef _WIN32
		if ((bytes_sent = send (sock, data + len - bytes_left, bytes_left, 0)) == SOCKET_ERROR)
#else
		if ((bytes_sent = send (sock, data + len - bytes_left, bytes_left, 0)) == -1)
#endif
		{
			DEBUG_OUT ("TCPSourceTransportEndpoint: send_complete(): send() call failed");
#ifdef _WIN32
			DEBUG_OUT2 ("TCPSourceTransportEndpoint: error code was ", WSAGetLastError());
#else
			DEBUG_OUT2 ("TCPSourceTransportEndpoint: error code was ", errno);
#endif
			return false;
		}
		bytes_left -= bytes_sent;
	}

	return true;
}


bool 
TCPSourceTransportEndpoint::send_buffer (StreamComponents::StreamingBuffer_ptr buffer)
{
	DEBUG_OUT ("TCPSourceTransportEndpoint: send_buffer() called");

	StreamComponents::TCPProfileHeader header;
	header.stream_number = htons (current_stream_number_);
	header.seq_length = htonl (buffer->get_used());

	if (! send_complete (connect_socket_, (const char*)&header, sizeof (header)))
	{
		DEBUG_OUT ("TCPSourceTransportEndpoint: send_buffer(): Could not send transport header");
		this->close();
		return false;
	}

	if (! send_complete (connect_socket_, (const char*)buffer->get_buffer(), buffer->get_used()))
	{
		DEBUG_OUT ("TCPSourceTransportEndpoint: send_buffer(): Could not send data");
		this->close();
		return false;
	}

	return true;
}


void
TCPSourceTransportEndpoint::begin_stream()
{
	++current_stream_number_;
}


void
TCPSourceTransportEndpoint::end_stream()
{
	StreamComponents::TCPProfileHeader header;
	header.stream_number = current_stream_number_;
	header.seq_length = htons (0);

	if (! send_complete (connect_socket_, (const char*)&header, sizeof (header)))
	{
		DEBUG_OUT ("TCPSourceTransportEndpoint: send_buffer(): Could not send ending transport header");
	}
}


void
TCPSourceTransportEndpoint::close()
{
	DEBUG_OUT ("TCPSourceTransportEndpoint: close() called");

	if (connected_)
	{
#ifdef _WIN32
		shutdown (connect_socket_, SD_BOTH);
		closesocket (connect_socket_);
#else
		shutdown (connect_socket_, 2);
		::close (connect_socket_);
#endif
	
		connected_ = false;
	}
}


void 
TCPSourceTransportEndpoint::setup_for_connect (StreamComponents::TransportSpec& transport_spec)
throw (StreamComponents::TransportFailure)
{
	const char* hostname;
	CORBA::Boolean hostname_found = false;
	CORBA::UShort portnumber;
	CORBA::Boolean portnumber_found = false;

	for (unsigned int i = 0; i < transport_spec.transport_parameters.length(); i++)
	{
		if (! std::strcmp (transport_spec.transport_parameters[i]->name(), "HOSTNAME"))
		{
			transport_spec.transport_parameters[i]->value() >>= hostname;
			hostname_found = true;
		}
		if (! std::strcmp (transport_spec.transport_parameters[i]->name(), "PORTNUMBER"))
		{
			transport_spec.transport_parameters[i]->value() >>= portnumber;
			portnumber_found = true;
		}
	}

	if (! hostname_found || ! portnumber_found)
	{
		DEBUG_OUT ("TCPSourceTransportEndpoint: setup_for_connect(): Insufficient transport parameters supplied by SinkTransportEndpoint");
		throw StreamComponents::TransportFailure();
	}

#ifdef _DEBUG
	std::string message;
	message = "TCPSourceTransportEndpoint: setup_for_connect(): Now trying to connect to ";
	message += hostname;
	message += " on port number ";
	DEBUG_OUT2 (message.c_str(), ntohs (portnumber));
#endif

#ifdef _WIN32
	if ((connect_socket_ = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
#else
	if ((connect_socket_ = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
#endif
	{
		DEBUG_OUT ("TCPSourceTransportEndpoint: setup_for_connect(): socket() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("TCPSourceTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("TCPSourceTransportEndpoint: error code was ", errno);
#endif


		throw StreamComponents::TransportFailure();
	}

	struct sockaddr_in my_sock_addr;
	my_sock_addr.sin_family = AF_INET;
	my_sock_addr.sin_port = portnumber;
	my_sock_addr.sin_addr.s_addr = inet_addr (hostname);

#ifdef _WIN32
	if (connect (connect_socket_, (const struct sockaddr*)&my_sock_addr, sizeof (my_sock_addr)) == SOCKET_ERROR)
#else
	if (connect (connect_socket_, (const struct sockaddr*)&my_sock_addr, sizeof (my_sock_addr)) == -1)
#endif
	{
		DEBUG_OUT ("TCPSourceTransportEndpoint: setup_for_connect(): connect() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("TCPSourceTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("TCPSourceTransportEndpoint: error code was ", errno);
#endif

#ifdef _WIN32
		closesocket (connect_socket_);
#else
		::close (connect_socket_);
#endif

		throw StreamComponents::TransportFailure();
	}

	connected_ = true;

}


} // namespace Qedo

#endif

