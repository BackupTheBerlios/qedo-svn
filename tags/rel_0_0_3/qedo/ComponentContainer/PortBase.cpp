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

static char rcsid[] = "$Id: PortBase.cpp,v 1.1 2002/10/07 07:17:02 tom Exp $";

#include "PortBase.h"


namespace Qedo {

PortBase::PortBase (const char* port_name, const char* type_id)
: port_name_ (port_name), type_id_ (type_id)
{
}


PortBase::PortBase()
{
}


PortBase::PortBase (const PortBase& port_base)
: port_name_ (port_base.port_name_),
  type_id_ (port_base.type_id_)
{
}


PortBase::~PortBase()
{
}


const std::string&
PortBase::port_name() const
{
    return port_name_;
}


} // namespace Qedo

