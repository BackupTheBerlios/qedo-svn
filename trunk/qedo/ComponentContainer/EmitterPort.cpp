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

static char rcsid[] = "$Id: EmitterPort.cpp,v 1.5 2003/04/14 09:17:49 tom Exp $";

#include "EmitterPort.h"
#include "Output.h"


namespace Qedo {


EmitterPort::EmitterPort (const char* name, const char* type_id)
: PortBase (name, type_id),
  consumer_ (Components::EventConsumerBase::_nil())
{
}


EmitterPort::EmitterPort()
{
}


EmitterPort::EmitterPort (const EmitterPort& emit_port)
: PortBase (emit_port),
  consumer_ (Components::EventConsumerBase::_duplicate (emit_port.consumer_.in()))
{
}


EmitterPort::~EmitterPort()
{
}


Components::EmitterDescription*
EmitterPort::emitter_description() const
{
	Components::EmitterDescription_var emi_desc = new EmitterDescription_impl (port_name_.c_str(), type_id_.c_str(), consumer_.in());

    return emi_desc._retn();
}


void
EmitterPort::set_consumer (Components::EventConsumerBase_ptr consumer)
throw (Components::AlreadyConnected)
{
    if (! CORBA::is_nil (consumer_))
	{
		throw Components::AlreadyConnected();
    }

    consumer_ = Components::EventConsumerBase::_duplicate (consumer);

	DEBUG_OUT2 ("EmitterPort: New emitter connected for port ", port_name_);
}


Components::EventConsumerBase_ptr 
EmitterPort::unset_consumer()
throw (Components::NoConnection)
{
    if (CORBA::is_nil (consumer_))
	{
		throw Components::NoConnection();
	}

	Components::EventConsumerBase_var connected_consumer =
		Components::EventConsumerBase::_duplicate (consumer_);

    consumer_ = Components::EventConsumerBase::_nil();

	return connected_consumer._retn();
}

} // namespace Qedo
