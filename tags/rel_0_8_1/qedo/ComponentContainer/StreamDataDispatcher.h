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

#ifndef __STREAM_DATA_DISPATCHER_H__
#define __STREAM_DATA_DISPATCHER_H__

#ifndef _QEDO_NO_STREAMS


#include <CORBA.h>
#include <Components.h>

#include "RefCountBase.h"
#include "MarshalBuffer.h"
#include "Output.h"
#include "Util.h"


namespace Qedo {


class CONTAINERDLL_API StreamDataDispatcher : public virtual Qedo::RefCountBase
{
public:
	StreamDataDispatcher();
	virtual ~StreamDataDispatcher();

	// Hooks for the type-specific implementations
	virtual void begin_stream (const char*, const Components::ConfigValues&) = 0;
	virtual void end_stream() = 0;
	virtual void failed_stream() = 0;
	virtual void receive_stream (UnmarshalBuffer*) = 0;
};


} // namespace Qedo

#endif

#endif

