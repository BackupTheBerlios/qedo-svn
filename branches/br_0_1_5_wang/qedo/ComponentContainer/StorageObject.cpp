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
#include "StorageObject.h"

namespace Qedo
{

StorageObjectImpl::StorageObjectImpl() :
	pid_(NULL),
	shortPid_(NULL),
	strUpdate_(""),
	strSelect_(""),
	pHomeBaseImpl_(NULL),
	bModified_(FALSE)
{
}

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the destroy_object operation destroys the 
//associated storage object (but does not destroy any of its incarnation)
//The standard exception PERSISTENT_STORE is raised when this operation is called
//on the instance of an embedded storage object
//MEMO: delete its record in database;
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectImpl::destroy_object()
	throw (CORBA::SystemException)
{
	Pid_var pPid = get_pid();
	pHomeBaseImpl_->destroyObject(pPid);
}

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the object_exist operation returns TRUE if the 
//target incarnation represents an actual storage object, FALSE if it does not
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObjectImpl::object_exists() 
	throw (CORBA::SystemException)
{
	Pid_var pPid = get_pid();
	return pHomeBaseImpl_->objectExists(pPid);
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
	Pid_var pid = new Pid;
	pid->length( pid_->length() );

	for( CORBA::ULong i=0; i<pid_->length(); i++ )
		(*pid)[i] = (*pid_)[i];

	return pid._retn();
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
	ShortPid_var spid = new ShortPid;
	spid->length( shortPid_->length() );

	for( CORBA::ULong i=0; i<shortPid_->length(); i++ )
		(*spid)[i] = (*shortPid_)[i];

	return spid._retn();
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage home instance that manages the target storage object 
//instance
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectImpl::get_storage_home()
	throw (CORBA::SystemException)
{
	StorageHomeBase_var pHomeBase = pHomeBaseImpl_;
	return pHomeBase._retn();
}

void
StorageObjectImpl::setStorageHome( StorageHomeBaseImpl* pHomeBaseImpl )
{
	pHomeBaseImpl_ = pHomeBaseImpl;
}

}


namespace CosPersistentState
{
////////////////////////////////////////////////////////////////////////////////
//a public default constructor that creates a null reference
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::StorageObjectRef()
{
	obj_ = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//a non-explicit constructor which takes an incarnation of the target storage
//type
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::StorageObjectRef(StorageObject* obj)
{
	obj_ = NULL;
    if( obj != NULL)
        obj_ = obj;
}

////////////////////////////////////////////////////////////////////////////////
//a public copy constructor
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::StorageObjectRef(const StorageObjectRef& ref)
{
	obj_ = ref.deref();
}

////////////////////////////////////////////////////////////////////////////////
//a public destructor
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::~StorageObjectRef()
{
	if( obj_ != NULL)
        obj_ -> _remove_ref();
    obj_ = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//a public assignment operator
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef& 
StorageObjectRef::operator=(const StorageObjectRef& ref)
{
	if( obj_ != ref.obj_ )
    {
        if( obj_ != NULL)
            obj_ -> _remove_ref();

        obj_ = ref.obj_;

        if( obj_ != NULL)
            obj_ -> _add_ref();
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
//a public assignment operator which takes an incarnation of the target
//abstract storage type
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef& 
StorageObjectRef::operator=(StorageObject* obj)
{
	if( obj_ != NULL)
        obj_ -> _remove_ref();

    obj_ = obj;

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
//dereferences this reference and returns the target object. 
//The caller is not supposed to release this incarnation
////////////////////////////////////////////////////////////////////////////////
StorageObject* 
StorageObjectRef::operator->() const
	throw(CORBA::SystemException)
{
	return obj_;
}

////////////////////////////////////////////////////////////////////////////////
//behaves like operator->()
////////////////////////////////////////////////////////////////////////////////
StorageObject* 
StorageObjectRef::deref() const
	throw(CORBA::SystemException)
{
	return obj_;
}

////////////////////////////////////////////////////////////////////////////////
//releases this reference
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRef::release()
{
	if( obj_ != NULL)
        obj_ -> _remove_ref();
    obj_ = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//destroys the target object
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRef::destroy_object() 
	throw(CORBA::SystemException)
{
	if( obj_ != NULL)
        obj_ -> destroy_object();
}

////////////////////////////////////////////////////////////////////////////////
//return the pid of the target object
////////////////////////////////////////////////////////////////////////////////
Pid* 
StorageObjectRef::get_pid() const 
	throw(CORBA::SystemException)
{
	CosPersistentState::Pid* ret = NULL;

    if( obj_ != NULL)
        ret  = obj_ -> get_pid();

    return ret;
}

////////////////////////////////////////////////////////////////////////////////
//return the short-pid of the target object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
StorageObjectRef::get_short_pid() const 
	throw(CORBA::SystemException)
{
	CosPersistentState::ShortPid* ret = NULL;

    if( obj_ != NULL)
        ret = obj_ -> get_short_pid();

    return ret;
}

////////////////////////////////////////////////////////////////////////////////
//return TRUE if and only if this reference is null
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObjectRef::is_null() const
{
	return (obj_ == NULL);
}

////////////////////////////////////////////////////////////////////////////////
//return the storage home of the target object. This function increases the 
//reference count of the return storage home
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectRef::get_storage_home() const
	throw(CORBA::SystemException)
{
	CosPersistentState::StorageHomeBase* ret = NULL ;

    if( obj_ != NULL)
        ret = obj_ -> get_storage_home();

    return ret;
}

StorageObjectRef
StorageObjectRef::_duplicate( const StorageObjectRef ref )
{
    return StorageObjectRef(ref);
}

}
