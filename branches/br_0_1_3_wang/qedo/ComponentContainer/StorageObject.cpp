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
#include "StorageHomeBase.h"
#include "Catalog.h"

namespace Qedo
{

StorageObjectImpl::StorageObjectImpl() :
	m_pid(NULL),
	m_shortPid(NULL),
	m_bModified(FALSE),
	m_strUpdate(""),
	m_strSelect(""),
	m_storageHomeBase(NULL)
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
	StorageHomeBaseImpl* homeimpl = dynamic_cast <StorageHomeBaseImpl*> (m_storageHomeBase);
	char* homename = homeimpl->getStorageHomeName();
	string my_pid = PSSHelper::convertPidToString(m_pid);

	string strSqlDel;
	strSqlDel = "DELETE FROM ";
	strSqlDel.append((const char*)homename);
	strSqlDel += " WHERE pid LIKE ";
	strSqlDel += my_pid;
	strSqlDel += ";";
	strSqlDel += "DELETE FROM pid_content WHERE pid LIKE ";
	strSqlDel += my_pid;
	strSqlDel += ";";

	CatalogBaseImpl* cbImpl = dynamic_cast <CatalogBaseImpl*> (homeimpl->get_catalog());
	cbImpl->ExecuteSQL(strSqlDel.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//When called on an incarnation, the object_exist operation returns TRUE if the 
//target incarnation represents an actual storage object, FALSE if it does not
////////////////////////////////////////////////////////////////////////////////
CORBA::Boolean 
StorageObjectImpl::object_exists() 
	throw (CORBA::SystemException)
{
	StorageHomeBaseImpl* homeimpl = dynamic_cast <StorageHomeBaseImpl*> (m_storageHomeBase);
	char* homename = homeimpl->getStorageHomeName();
	string my_pid = PSSHelper::convertPidToString(m_pid);

	string strSqlSel;
	strSqlSel = "SELECT COUNT(*) FROM ";
	strSqlSel.append((const char*)homename);
	strSqlSel += " WHERE pid LIKE ";
	strSqlSel += my_pid;
	strSqlSel += ";";
    
	if(homeimpl->Open(strSqlSel.c_str()))
	{
		long nID = -1;
		homeimpl->GetFieldValue(0, &nID);
		if(nID==1)
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;
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
	return m_pid;
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
	return m_shortPid;
}

////////////////////////////////////////////////////////////////////////////////
//returns the storage home instance that manages the target storage object 
//instance
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectImpl::get_storage_home()
	throw (CORBA::SystemException)
{
	return m_storageHomeBase;
}

////////////////////////////////////////////////////////////////////////////////
//##############################################################################
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//a public default constructor that creates a null reference
////////////////////////////////////////////////////////////////////////////////
/*
StorageObjectRefImpl::StorageObjectRefImpl() 
	throw()
{
}
*/

////////////////////////////////////////////////////////////////////////////////
//a non-explicit constructor which takes an incarnation of the target storage
//type
////////////////////////////////////////////////////////////////////////////////
StorageObjectRefImpl::StorageObjectRefImpl(StorageObject* obj)  :
	m_pid(NULL),
	m_shortPid(NULL),
	m_bModified(FALSE),
	m_strUpdate(""),
	m_strSelect(""),
	m_storageHomeBase(NULL)
{
}
////////////////////////////////////////////////////////////////////////////////
//a public copy constructor
////////////////////////////////////////////////////////////////////////////////
StorageObjectRefImpl::StorageObjectRefImpl(const StorageObjectRef& ref) :
	m_pid(NULL),
	m_shortPid(NULL),
	m_bModified(FALSE),
	m_strUpdate(""),
	m_strSelect(""),
	m_storageHomeBase(NULL)
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
{/*
	m_pid = new CosPersistentState::Pid(*(ref.get_pid()));
	m_shortPid = new CosPersistentState::ShortPid(*(ref.get_short_pid()));
	m_storageHomeBase = CosPersistentState::StorageHomeBase::_duplicate(ref.get_storage_home());
	//m_strUpdate = ref.m_strUpdate;
	//m_strSelect = ref.m_strSelect;
	//m_bModified = ref.m_bModified;
*/	
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//a public assignment operator which takes an incarnation of the target
//abstract storage type
////////////////////////////////////////////////////////////////////////////////
StorageObjectRef& 
StorageObjectRefImpl::operator=(StorageObject* obj) 
	throw()
{/*
	m_pid = new CosPersistentState::Pid(*(obj->get_pid()));
	m_shortPid = new CosPersistentState::ShortPid(*(obj->get_short_pid()));
	m_storageHomeBase = CosPersistentState::StorageHomeBase::_duplicate(obj->get_storage_home());
	//m_strUpdate = ref.m_strUpdate;
	//m_strSelect = ref.m_strSelect;
	//m_bModified = ref.m_bModified;
*/
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//releases this reference
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRefImpl::release() 
	throw()
{
	//for(CORBA::ULong i=0; i<_get_refcount(); i++)
    _remove_ref();
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
//behaves like operator->()
////////////////////////////////////////////////////////////////////////////////
StorageObject* 
StorageObjectRefImpl::deref() 
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
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//destroys the target object
////////////////////////////////////////////////////////////////////////////////
void 
StorageObjectRefImpl::destroy_object() 
	throw(CORBA::SystemException)
{
	StorageHomeBaseImpl* homeimpl = dynamic_cast <StorageHomeBaseImpl*> (m_storageHomeBase);
	char* homename = homeimpl->getStorageHomeName();
	string my_pid = PSSHelper::convertPidToString(m_pid);

	string strSqlDel;
	strSqlDel = "DELETE FROM ";
	strSqlDel.append((const char*)homename);
	strSqlDel += " WHERE pid LIKE ";
	strSqlDel += my_pid;
	strSqlDel += ";";
	strSqlDel += "DELETE FROM pid_content WHERE pid LIKE ";
	strSqlDel += my_pid;
	strSqlDel += ";";

	CatalogBaseImpl* cbImpl = dynamic_cast <CatalogBaseImpl*> (homeimpl->get_catalog());
	cbImpl->ExecuteSQL(strSqlDel.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//return the pid of the target object
////////////////////////////////////////////////////////////////////////////////
Pid* 
StorageObjectRefImpl::get_pid() const 
	throw(CORBA::SystemException)
{
	return m_pid;
}

////////////////////////////////////////////////////////////////////////////////
//return the short-pid of the target object
////////////////////////////////////////////////////////////////////////////////
ShortPid* 
StorageObjectRefImpl::get_short_pid() const 
	throw(CORBA::SystemException)
{
	return m_shortPid;
}

////////////////////////////////////////////////////////////////////////////////
//return the storage home of the target object. This function increases the 
//reference count of the return storage home
////////////////////////////////////////////////////////////////////////////////
StorageHomeBase_ptr 
StorageObjectRefImpl::get_storage_home() const
	throw(CORBA::SystemException)
{
	return m_storageHomeBase;
}

}
