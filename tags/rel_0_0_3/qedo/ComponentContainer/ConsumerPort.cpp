/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

static char rcsid[] = "$Id: ConsumerPort.cpp,v 1.1 2002/10/07 07:17:02 tom Exp $";

#include "ConsumerPort.h"


namespace Qedo {

ConsumerPort::ConsumerPort (const char* name,
                            const char* type_id,
                            Components::EventConsumerBase_ptr consumer)
: PortBase (name, type_id),
  consumer_ (Components::EventConsumerBase::_duplicate (consumer))
{
}


ConsumerPort::ConsumerPort()
{
}


ConsumerPort::ConsumerPort (const ConsumerPort& cons_port)
: PortBase (cons_port),
  consumer_ (Components::EventConsumerBase::_duplicate (cons_port.consumer_))
{
}


ConsumerPort::~ConsumerPort()
{
}


Components::ConsumerDescription*
ConsumerPort::consumer_description() const
{
	Components::ConsumerDescription_var con_desc = new ConsumerDescription_impl (port_name_.c_str(), type_id_.c_str(), consumer_);

    return con_desc._retn();
}


const Components::EventConsumerBase_ptr 
ConsumerPort::consumer() const
{
    return Components::EventConsumerBase::_duplicate (consumer_);
}

} // namespace Qedo

