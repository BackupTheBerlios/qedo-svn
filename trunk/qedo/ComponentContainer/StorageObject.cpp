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
	pPid_(new CosPersistentState::Pid),
	pShortPid_(new CosPersistentState::ShortPid),
	strUpdate_(""),
	strSelect_(""),
	//pHomeBase_(StorageHomeBase::_nil()),
	pHomeBase_(NULL),
	bModified_(FALSE)
{
}

StorageObjectImpl::~StorageObjectImpl()
{
	std::cout << "StorageObjectImpl::~StorageObjectImpl()\n";
}

std::string
StorageObjectImpl::getUpdate()
{ 
	return strUpdate_; 
}

std::string
StorageObjectImpl::getSelect()
{ 
	return strSelect_; 
}

bool
StorageObjectImpl::isModified()
{ 
	return bModified_; 
}

void
StorageObjectImpl::setModified(bool bModified)
{ 
	bModified_ = bModified;
}

void
StorageObjectImpl::set_pid(CosPersistentState::Pid* pPid)
{
	pPid_->length( pPid->length() );

	for( CORBA::ULong i=0; i<pPid->length(); i++ )
		(*pPid_)[i] = (*pPid)[i];
}

void
StorageObjectImpl::set_short_pid(CosPersistentState::ShortPid* pShortPid)
{
	pShortPid_->length( pShortPid->length() );

	for( CORBA::ULong i=0; i<pShortPid->length(); i++ )
		(*pShortPid_)[i] = (*pShortPid)[i];
}

void
StorageObjectImpl::set_pid(const char* szPid)
{
	int iLength = strlen(szPid);
	pPid_->length(iLength);
	
	for(int i=0; i<iLength; i++)
		(*pPid_)[i] = szPid[i];
}

void
StorageObjectImpl::set_short_pid(const char* szShortPid)
{
	int iLength = strlen(szShortPid);
	pShortPid_->length(iLength);
	
	for(int i=0; i<iLength; i++)
		(*pShortPid_)[i] = szShortPid[i];
}

void 
StorageObjectImpl::_add_ref()
{
	//std::cout << "StorageObjectImpl::_remove_ref()\n";
	RefCountLocalObject::_add_ref();
}
		
void
StorageObjectImpl::_remove_ref()
{
	std::cout << "StorageObjectImpl::_remove_ref()\n";
	RefCountLocalObject::_remove_ref();
	std::cout << "StorageObjectImpl::_remove_ref()22\n";
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
	DEBUG_OUT("StorageObjectImpl::destroy_object() is called");

	Pid_var pPid = get_pid();
	//StorageHomeBaseImpl* pHomeBaseImpl = dynamic_cast <StorageHomeBaseImpl*> (pHomeBase_.in());
	StorageHomeBaseImpl* pHomeBaseImpl = dynamic_cast <StorageHomeBaseImpl*> (pHomeBase_);
	pHomeBaseImpl->destroyObject(pPid);
}

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the object_exist operation returns TRUE if the 
//target incarnation represents an actual storage object, FALSE if it does not
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObjectImpl::object_exists() 
	throw (CORBA::SystemException)
{
	DEBUG_OUT("StorageObjectImpl::object_exists() is called");

	Pid_var pPid = get_pid();
	//StorageHomeBaseImpl* pHomeBaseImpl = dynamic_cast <StorageHomeBaseImpl*> (pHomeBase_.in());
	StorageHomeBaseImpl* pHomeBaseImpl = dynamic_cast <StorageHomeBaseImpl*> (pHomeBase_);
	return pHomeBaseImpl->objectExists(pPid);
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
	Pid_var pPid = new Pid;
	pPid->length( pPid_->length() );

	for( CORBA::ULong i=0; i<pPid_->length(); i++ )
		(*pPid)[i] = (*pPid_)[i];

	return pPid._retn();
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
	ShortPid_var pSpid = new ShortPid;
	pSpid->length( pShortPid_->length() );

	for( CORBA::ULong i=0; i<pShortPid_->length(); i++ )
		(*pSpid)[i] = (*pShortPid_)[i];

	return pSpid._retn();
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage home instance that manages the target storage object 
//instance
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectImpl::get_storage_home()
	throw (CORBA::SystemException)
{
	//return StorageHomeBase::_duplicate(pHomeBase_.in());
	return pHomeBase_;
}

StorageObject*
StorageObjectImpl::_duplicate(StorageObject* pStorageObject)
{
	if(pStorageObject)
		pStorageObject->_add_ref();
	return pStorageObject;
}

StorageObject*
StorageObjectImpl::_downcast(StorageObject* pStorageObject)
{
	return pStorageObject;
}

void
StorageObjectImpl::setStorageHome( StorageHomeBase_ptr pHomeBase )
{
	//pHomeBase_ = StorageHomeBase::_duplicate(pHomeBase);
	pHomeBase_ = pHomeBase;
}

}


namespace CosPersistentState
{
////////////////////////////////////////////////////////////////////////////////
//a public default constructor that creates a null reference
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::StorageObjectRef() :
	pObj_(NULL) 
{
}

////////////////////////////////////////////////////////////////////////////////
//a non-explicit constructor which takes an incarnation of the target storage
//type
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::StorageObjectRef(StorageObject* obj) :
	pObj_(NULL)
{
    if( obj!=NULL )
        pObj_ = obj;
}

////////////////////////////////////////////////////////////////////////////////
//a public copy constructor
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::StorageObjectRef(const StorageObjectRef& ref) :
	pObj_(NULL)
{
	pObj_ = ref.deref();
}

////////////////////////////////////////////////////////////////////////////////
//a public destructor
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef::~StorageObjectRef()
{
	if( pObj_!=NULL )
        pObj_->_remove_ref();
    pObj_ = NULL;
}


////////////////////////////////////////////////////////////////////////////////
//a public assignment operator
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef& 
StorageObjectRef::operator=(const StorageObjectRef& ref)
{
	if( pObj_!=ref.pObj_ )
    {
        if( pObj_!=NULL )
            pObj_->_remove_ref();

        pObj_ = ref.pObj_;

        if( pObj_!=NULL )
            pObj_->_add_ref();
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
	if( pObj_!=NULL )
        pObj_->_remove_ref();

    pObj_ = obj;

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
	return pObj_;
}

////////////////////////////////////////////////////////////////////////////////
//behaves like operator->()
////////////////////////////////////////////////////////////////////////////////
StorageObject* 
StorageObjectRef::deref() const
	throw(CORBA::SystemException)
{
	return pObj_;
}

////////////////////////////////////////////////////////////////////////////////
//releases this reference
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRef::release()
{
	if( pObj_!=NULL )
        pObj_->_remove_ref();
    pObj_ = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//destroys the target object
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRef::destroy_object() 
	throw(CORBA::SystemException)
{
	if( pObj_!=NULL )
        pObj_->destroy_object();
}

////////////////////////////////////////////////////////////////////////////////
//return the pid of the target object
////////////////////////////////////////////////////////////////////////////////
Pid* 
StorageObjectRef::get_pid() const 
	throw(CORBA::SystemException)
{
	Pid_var pPid = NULL;

    if( pObj_!=NULL )
        pPid = pObj_->get_pid();

    return pPid._retn();
}

////////////////////////////////////////////////////////////////////////////////
//return the short-pid of the target object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
StorageObjectRef::get_short_pid() const 
	throw(CORBA::SystemException)
{
	ShortPid_var pSpid = NULL;

    if( pObj_!=NULL )
        pSpid = pObj_->get_short_pid();

    return pSpid._retn();
}

////////////////////////////////////////////////////////////////////////////////
//return TRUE if and only if this reference is null
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObjectRef::is_null() const
{
	return ( pObj_==NULL );
}

////////////////////////////////////////////////////////////////////////////////
//return the storage home of the target object. This function increases the 
//reference count of the return storage home
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectRef::get_storage_home() const
	throw(CORBA::SystemException)
{
	StorageHomeBase_var pHomeBase = StorageHomeBase::_nil();

    if( pObj_!=NULL )
        pHomeBase = pObj_->get_storage_home();

    return pHomeBase._retn();
}

StorageObjectRef
StorageObjectRef::_duplicate( const StorageObjectRef ref )
{
    return StorageObjectRef( ref );
}

StorageObjectRef
StorageObjectRef::_downcast( const StorageObjectRef ref )
{
    return ref;
}

}
