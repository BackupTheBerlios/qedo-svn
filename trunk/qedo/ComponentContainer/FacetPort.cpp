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

static char rcsid[] = "$Id: FacetPort.cpp,v 1.4 2003/04/01 07:50:10 neubauer Exp $";

#include "FacetPort.h"


namespace Qedo {


FacetPort::FacetPort (const char* name, 
                      const char* type_id, 
                      const CORBA::Object_ptr ref)
: PortBase (name, type_id), 
  facet_ref_ (CORBA::Object::_duplicate (ref))
{
}


FacetPort::FacetPort()
{
}


FacetPort::FacetPort (const FacetPort& facet_port)
: PortBase (facet_port),
  facet_ref_ (CORBA::Object::_duplicate (facet_port.facet_ref_))
{
}


FacetPort::~FacetPort()
{
}


Components::FacetDescription*
FacetPort::facet_description() const
{
	Components::FacetDescription_var facet_desc = new FacetDescription_impl (port_name_.c_str(), type_id_.c_str(), facet_ref_);

    return facet_desc._retn();
}


const CORBA::Object_ptr
FacetPort::facet_ref() const
{
    return CORBA::Object::_duplicate (facet_ref_);
}

} // namespace Qedo
