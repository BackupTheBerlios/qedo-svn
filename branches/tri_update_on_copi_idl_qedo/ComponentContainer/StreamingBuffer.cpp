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


#include "StreamingBuffer.h"
#include "Output.h"


static char rcsid[] UNUSED = "$Id: StreamingBuffer.cpp,v 1.4 2004/06/24 14:36:08 tom Exp $";


namespace Qedo {
	
	
StreamingBuffer::StreamingBuffer (CORBA::ULong min_size)
: size_ (min_size),
  bytes_used_ (min_size),
  release_ (true)
{
	buffer_ = malloc (min_size);

	if (! buffer_)
	{
		NORMAL_ERR ("StreamingBuffer: Could not allocate memory");
		size_ = 0;
		assert (0);
	}
}


StreamingBuffer::StreamingBuffer (void *data, CORBA::ULong data_size, bool release)
: buffer_ (data),
  size_ (data_size),
  bytes_used_ (data_size),
  release_ (release)
{
}


StreamingBuffer::~StreamingBuffer()
{
	DEBUG_OUT ("StreamingBuffer: Destructor called");

	if (buffer_)
		free (buffer_);
}


StreamComponents::BufferPtr 
StreamingBuffer::get_buffer()
{
	return buffer_;
}


CORBA::ULong 
StreamingBuffer::get_size()
{
	return size_;
}


void 
StreamingBuffer::set_used (CORBA::ULong bytes_used)
throw (StreamComponents::StreamingBuffer::OutOfRange)
{
	if (bytes_used > size_)
	{
		DEBUG_OUT ("StreamingBuffer: set_used(): Warning: Supplied value greater than current size");
		throw StreamComponents::StreamingBuffer::OutOfRange();
	}

	if (! bytes_used)
	{
		DEBUG_OUT ("StreamingBuffer: set_used(): Warning: Size of null not allowed");
		throw StreamComponents::StreamingBuffer::OutOfRange();
	}

	bytes_used_ = bytes_used > size_ ? size_ : bytes_used;
}


CORBA::ULong 
StreamingBuffer::get_used()
{
	return bytes_used_;
}


} // namespace Qedo

#endif

