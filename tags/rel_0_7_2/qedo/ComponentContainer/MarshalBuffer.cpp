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


#include "MarshalBuffer.h"
#include "Output.h"


static char rcsid[] UNUSED = "$Id: MarshalBuffer.cpp,v 1.3 2004/06/24 14:36:07 tom Exp $";


namespace Qedo {


MarshalBuffer::MarshalBuffer (CORBA::ULong buf_size)
: StreamingBuffer (buf_size)
{
	marshal_ptr_ = 0;
}


MarshalBuffer::~MarshalBuffer()
{
}


void
MarshalBuffer::do_align (CORBA::ULong align_val)
{
	CORBA::ULong data_start = reinterpret_cast <CORBA::ULong> (buffer_);

	CORBA::ULong modulo = (data_start + marshal_ptr_) % align_val;

	if (modulo)
	{
		CORBA::ULong adjust_val = align_val - modulo;

		while (size_ - marshal_ptr_ < adjust_val)
		{
			// Grow buffer
			void *new_buffer = realloc (buffer_, size_ * 2);

			if (!new_buffer)
			{
				NORMAL_ERR ("MarshalBufferBase: Cannot grow buffer, out of memory...");
				assert (new_buffer);
			}

			buffer_ = new_buffer;
			size_ = size_ * 2;
		}

		marshal_ptr_ += adjust_val;
	}

	bytes_used_ = marshal_ptr_;
}


void 
MarshalBuffer::marshal_data (const char* data, CORBA::ULong data_size)
{
	while (size_ - marshal_ptr_ < data_size)
	{
		// Grow buffer
		void *new_buffer = realloc (buffer_, size_ * 2);

		if (!new_buffer)
		{
			NORMAL_ERR ("MarshalBuffer: Cannot grow marshal buffer, out of memory...");
			assert (new_buffer);
		}

		buffer_ = new_buffer;
		size_ = size_ * 2;
	}

	memcpy ((char*)buffer_ + marshal_ptr_, data, data_size);

	marshal_ptr_ += data_size;

	bytes_used_ = marshal_ptr_;
}


UnmarshalBuffer::UnmarshalBuffer (CORBA::ULong buf_size)
: StreamingBuffer (buf_size)
{
	unmarshal_ptr_ = 0;
}


UnmarshalBuffer::~UnmarshalBuffer()
{
}


void
UnmarshalBuffer::do_align (CORBA::ULong align_val)
{
	CORBA::ULong data_start = reinterpret_cast <CORBA::ULong> (buffer_);

	CORBA::ULong modulo = (data_start + unmarshal_ptr_) % align_val;

	if (modulo)
	{
		CORBA::ULong adjust_val = align_val - modulo;

		if (bytes_used_ - unmarshal_ptr_ < adjust_val)
		{
			NORMAL_ERR ("UnmarshalBuffer: Buffer does not hold enough data...");
			assert (bytes_used_ - unmarshal_ptr_ >= adjust_val);
		}

		unmarshal_ptr_ += adjust_val;
	}
}


void 
UnmarshalBuffer::unmarshal_data (char* dest, CORBA::ULong dest_size)
{
	if (bytes_used_ - unmarshal_ptr_ < dest_size)
	{
		NORMAL_ERR ("UnmarshalBuffer: Buffer does not hold enough data...");
		assert (bytes_used_ - unmarshal_ptr_ >= dest_size);
	}

	memcpy (dest, (char*)buffer_ + unmarshal_ptr_, dest_size);

	unmarshal_ptr_ += dest_size;
}


} // namespace Qedo

#endif
