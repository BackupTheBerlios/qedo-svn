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
#include "winsock2.h"
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include "UDPSourceTransportEndpoint.h"
#include "Output.h"
#include "Valuetypes.h"

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>


static char rcsid[] UNUSED = "$Id: UDPSourceTransportEndpoint.cpp,v 1.3 2004/06/24 14:36:08 tom Exp $";

namespace Qedo {

	
UDPSourceTransportEndpoint::UDPSourceTransportEndpoint()
: established_ (false)
{
	current_stream_number_ = (this->rand_int()) & 0xFFFF;
}


UDPSourceTransportEndpoint::~UDPSourceTransportEndpoint()
{
	DEBUG_OUT ("UDPSourceTransportEndpoint: Destructor called");
}


bool 
UDPSourceTransportEndpoint::send_buffer (StreamComponents::StreamingBuffer_ptr buffer)
{
	DEBUG_OUT ("UDPSourceTransportEndpoint: send_buffer() called");

	// Test whether we must fragment, TODO

	// We do a copy here, there are solutions to avoid this copy and have zero-copy send semantics
	CORBA::ULong buf_size = buffer->get_used() + sizeof (StreamComponents::UDPProfileHeader);

	char* buf = (char*)malloc (buf_size);
	((StreamComponents::UDPProfileHeader*)buf)->stream_number = htons (current_stream_number_);
	((StreamComponents::UDPProfileHeader*)buf)->seq_length = htonl (buffer->get_used());
	((StreamComponents::UDPProfileHeader*)buf)->fragment_number = 0;
	((StreamComponents::UDPProfileHeader*)buf)->last_fragment_number = 0;
	memcpy (buf + sizeof (StreamComponents::UDPProfileHeader), buffer->get_buffer(), buffer->get_used());

#ifdef _WIN32
	if (sendto (socket_, buf, buf_size, 0, (const sockaddr*)&sink_sock_addr_, sizeof (sink_sock_addr_)) == SOCKET_ERROR)
#else
	if (sendto (socket_, buf, buf_size, 0, (const sockaddr*)&sink_sock_addr_, sizeof (sink_sock_addr_)) == -1)
#endif
	{
		DEBUG_OUT ("UDPSourceTransportEndpoint: send_buffer(): Could not send packet");
#ifdef _WIN32
		DEBUG_OUT2 ("UDPSourceTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("UDPSourceTransportEndpoint: error code was ", errno);
#endif
		this->close();
		return false;
	}

	return true;
}


void
UDPSourceTransportEndpoint::begin_stream()
{
}


void
UDPSourceTransportEndpoint::end_stream()
{
}


void
UDPSourceTransportEndpoint::close()
{
	DEBUG_OUT ("UDPSourceTransportEndpoint: close() called");

#ifdef _WIN32
		shutdown (socket_, SD_BOTH);
		closesocket (socket_);
	
		established_ = false;
#else
		shutdown (socket_, 2);
		::close (socket_);
		
		established_ = false;
#endif
}


void 
UDPSourceTransportEndpoint::setup_connection (StreamComponents::TransportSpec& transport_spec)
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
		DEBUG_OUT ("UDPSourceTransportEndpoint: setup_connection(): Insufficient transport parameters supplied by SinkTransportEndpoint");
		throw StreamComponents::TransportFailure();
	}

#ifdef _DEBUG
	std::string message;
	message = "UDPSourceTransportEndpoint: setup_connection(): Now trying to send to ";
	message += hostname;
	message += " on port number ";
	DEBUG_OUT2 (message.c_str(), ntohs (portnumber));
#endif

#ifdef _WIN32
	if ((socket_ = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
#else
	if ((socket_ = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
#endif
	{
		DEBUG_OUT ("UDPSourceTransportEndpoint: setup_connection(): socket() call failed");
#ifdef _WIN32
		DEBUG_OUT2 ("UDPSourceTransportEndpoint: error code was ", WSAGetLastError());
#else
		DEBUG_OUT2 ("UDPSourceTransportEndpoint: error code was ", errno);
#endif


		throw StreamComponents::TransportFailure();
	}

	sink_sock_addr_.sin_family = AF_INET;
	sink_sock_addr_.sin_port = portnumber;
	sink_sock_addr_.sin_addr.s_addr = inet_addr (hostname);

	established_ = true;
}


} // namespace Qedo

#endif

