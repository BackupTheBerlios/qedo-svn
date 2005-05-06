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


#include "GetComponentHelperServant.h"
#include "Output.h"

static char rcsid[] UNUSED = "$Id: GetComponentHelperServant.cpp,v 1.5 2004/03/08 11:14:03 boehme Exp $";


namespace Qedo {

GetComponentHelperServant::GetComponentHelperServant (Components::CCMObject_ptr ccm_object)
: ccm_object_ (Components::CCMObject::_duplicate (ccm_object))
{
}


GetComponentHelperServant::~GetComponentHelperServant()
{
	DEBUG_OUT ("GetComponentHelperServant: Destructor called");
}



Components::CCMObject_ptr 
GetComponentHelperServant::get_component()
throw(CORBA::SystemException)
{
	return Components::CCMObject::_duplicate (ccm_object_);
}


CORBA::Object_ptr 
GetComponentHelperServant::_get_component()
throw(CORBA::SystemException)
{
	return CORBA::Object::_duplicate (ccm_object_);
}

} // namespace Qedo
