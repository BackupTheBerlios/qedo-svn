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

#include "PSSNativeClasses_impl.h"

namespace Qedo
{

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the destroy_object operation destroys the 
//associated storage object (but does not destroy any of its incarnation)
//The standard exception PERSISTENT_STORE is raised when this operation is called
//on the instance of an embedded storage object
////////////////////////////////////////////////////////////////////////////////
void 
StorageObject::destroy_object() 
	throw (CORBA::SystemException)
{

}

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the object_exist operation returns TRUE if the 
//target incarnation represents an actual storage object, FLASE if it does not
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObject::object_exists() 
	throw (CORBA::SystemException)
{
	return TRUE;
}
		
////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the get_pid operation returns pid of the 
//associated storage object
//The standard exception PERSISTENT_STORE is raised when this operation is called
//on the instance of an embedded storage object
////////////////////////////////////////////////////////////////////////////////
Pid* 
StorageObject::get_pid()
	throw (CORBA::SystemException)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the get_short_pid operation returns short pid 
//of the associated storage object
//The standard exception PERSISTENT_STORE is raised when this operation is called
//on the instance of an embedded storage object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
StorageObject::get_short_pid()
	throw (CORBA::SystemException)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage home instance that manages the target storage object 
//instance
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObject::get_storage_home()
	throw (CORBA::SystemException)
{
	if(m_storageHomeBase)
		return (dynamic_cast <StorageHomeBase_ptr> (m_storageHomeBase));
	return
		NULL;
}

}
