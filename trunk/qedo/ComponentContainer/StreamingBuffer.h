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

#ifndef __STREAMING_BUFFER_H__
#define __STREAMING_BUFFER_H__

#ifndef _QEDO_NO_STREAMS

#include <CORBA.h>
#include <StreamComponents_skel.h>

#include "RefCountBase.h"
#include "Util.h"


namespace Qedo {


class CONTAINERDLL_API StreamingBuffer : public virtual StreamComponents::StreamingBuffer,
										 public virtual RefCountLocalObject
{
protected:
	void* buffer_;
	CORBA::ULong size_;
	CORBA::ULong bytes_used_;
	bool release_;

public:
	StreamingBuffer (CORBA::ULong);
	StreamingBuffer (void*, CORBA::ULong, bool);
	virtual ~StreamingBuffer();

	//
    // IDL:omg.org/StreamComponents/StreamingBuffer/get_buffer:1.0
    //
	StreamComponents::BufferPtr get_buffer();

    //
    // IDL:omg.org/StreamComponents/StreamingBuffer/get_size:1.0
    //
    CORBA::ULong get_size();

    //
    // IDL:omg.org/StreamComponents/StreamingBuffer/set_used:1.0
    //
    void set_used(CORBA::ULong)
		throw (StreamComponents::StreamingBuffer::OutOfRange);

    //
    // IDL:omg.org/StreamComponents/StreamingBuffer/get_used:1.0
    //
    CORBA::ULong get_used();
};


} // namespace Qedo


#endif

#endif

