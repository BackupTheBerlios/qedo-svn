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
//MEMO: incarnation is a member variable m_xx, storage object is xx;
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectImpl::destroy_object() 
	throw (CORBA::SystemException)
{
	
}

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the object_exist operation returns TRUE if the 
//target incarnation represents an actual storage object, FALSE if it does not
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObjectImpl::object_exists() 
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
StorageObjectImpl::get_pid()
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
StorageObjectImpl::get_short_pid()
	throw (CORBA::SystemException)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage home instance that manages the target storage object 
//instance
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectImpl::get_storage_home()
	throw (CORBA::SystemException)
{
	if(m_storageHomeBase)
		return (dynamic_cast <StorageHomeBase_ptr> (m_storageHomeBase));
	return
		NULL;
}


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//a public default constructor that creates a null reference
////////////////////////////////////////////////////////////////////////////////
StorageObjectRefImpl::StorageObjectRefImpl(StorageObject* obj) 
	throw()
{

}

////////////////////////////////////////////////////////////////////////////////
//a public copy constructor
////////////////////////////////////////////////////////////////////////////////
StorageObjectRefImpl::StorageObjectRefImpl(const StorageObjectRef& ref)
	throw()
{

}

////////////////////////////////////////////////////////////////////////////////
//a public destructor
////////////////////////////////////////////////////////////////////////////////
StorageObjectRefImpl::~StorageObjectRefImpl()
{

}

////////////////////////////////////////////////////////////////////////////////
//a public assignment operator
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef& 
StorageObjectRefImpl::operator=(const StorageObjectRef& ref) 
	throw()
{
	CosPersistentState::StorageObjectRef aaa;
	return aaa;
}

////////////////////////////////////////////////////////////////////////////////
//a public assignment operator which takes an incarnation of the target
//abstract storage type
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef& 
StorageObjectRefImpl::operator=(StorageObject* obj) 
	throw()
{
	CosPersistentState::StorageObjectRef aaa;
	return aaa;
}

////////////////////////////////////////////////////////////////////////////////
//releases this reference
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRefImpl::release() 
	throw()
{

}

////////////////////////////////////////////////////////////////////////////////
//behaves like operator->()
////////////////////////////////////////////////////////////////////////////////
StorageObject* 
StorageObjectRefImpl::deref() 
	throw(CORBA::SystemException)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//dereferences this reference and returns the target object. 
//The caller is not supposed to release this incarnation
////////////////////////////////////////////////////////////////////////////////
StorageObject* 
StorageObjectRefImpl::operator->() 
	throw(CORBA::SystemException)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//destroys the target object
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRefImpl::destroy_object() 
	throw(CORBA::SystemException)
{

}

////////////////////////////////////////////////////////////////////////////////
//return the pid of the target object
////////////////////////////////////////////////////////////////////////////////
Pid* 
StorageObjectRefImpl::get_pid() const 
	throw(CORBA::SystemException)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//return the short-pid of the target object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
StorageObjectRefImpl::get_short_pid() const 
	throw(CORBA::SystemException)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//return TRUE if and only if this reference is null
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObjectRefImpl::is_null() const 
	throw()
{
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//return the storage home of the target object. This function increases the 
//reference count of the return storage home
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectRefImpl::get_storage_home() const
	throw(CORBA::SystemException)
{
	return NULL;
}


////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
//a public default constructor that creates a null reference
////////////////////////////////////////////////////////////////////////////////
/*template <class T>
T* 
FactoryImpl<T>::create()
{
	return (new Qedo::T());
}
*/
}
