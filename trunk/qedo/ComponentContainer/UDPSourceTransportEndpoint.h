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

#ifndef __UDP_SOURCE_TRANSPORT_ENDPOINT_H__
#define __UDP_SOURCE_TRANSPORT_ENDPOINT_H__

#ifndef _QEDO_NO_STREAMS


#include "TransportEndpoint.h"


namespace Qedo {


class UDPSourceTransportEndpoint : public virtual SourceTransportEndpoint
{
private:
	bool established_;
	struct sockaddr_in sink_sock_addr_;
	CORBA::UShort current_stream_number_;

#ifdef _WIN32
	SOCKET socket_;
#else
	int socket_;
#endif

public:
	UDPSourceTransportEndpoint();
	virtual ~UDPSourceTransportEndpoint();

	bool send_buffer (StreamComponents::StreamingBuffer_ptr);

	void begin_stream();

	void end_stream();

	void close();

	void setup_connection (StreamComponents::TransportSpec&)
		throw (StreamComponents::TransportFailure);
};


}


#endif

#endif

