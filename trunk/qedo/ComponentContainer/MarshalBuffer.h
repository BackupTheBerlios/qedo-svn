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

#ifndef __MARSHAL_BUFFER_H__
#define __MARSHAL_BUFFER_H__

#ifndef _QEDO_NO_STREAMS

#include <CORBA.h>
#include <Components_skel.h>

#include "StreamingBuffer.h"
#include "Util.h"


namespace Qedo {


class CONTAINERDLL_API MarshalBuffer : public StreamingBuffer
{
private:
	CORBA::ULong marshal_ptr_;

public:
	MarshalBuffer (CORBA::ULong);
	~MarshalBuffer();

	void do_align (CORBA::ULong);
	void marshal_data (const char*, CORBA::ULong);
};


class CONTAINERDLL_API UnmarshalBuffer : public StreamingBuffer
{
private:
	CORBA::ULong unmarshal_ptr_;

public:
	UnmarshalBuffer (CORBA::ULong);
	~UnmarshalBuffer();

	void do_align (CORBA::ULong);
	void unmarshal_data (char*, CORBA::ULong);
};

} // namespace Qedo

#endif

#endif

