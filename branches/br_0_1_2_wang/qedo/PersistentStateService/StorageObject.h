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
#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include <map>
#include <string>
#include "PSSUtil.h"
#include "RefCountBase.h"
#include "PSSHelper.h"
#include "PSSStorageObject.h"

using namespace std;
using namespace CosPersistentState;

namespace Qedo
{

class StorageObjectImpl : public virtual CosPersistentState::StorageObject,
						  public virtual RefCountLocalObject
{
	public:
		
		StorageObjectImpl();

		string getUpdate();

		string getSelect();

		bool isModified();

		void setModified(bool bModified);

		virtual void setValue(map<string, CORBA::Any> valueMap) {};

		// normal mapping of PSDL operations
		void _add_ref() {RefCountLocalObject::_add_ref();};
		
		void _remove_ref() {RefCountLocalObject::_remove_ref();};

		void destroy_object() 
			throw (CORBA::SystemException);
		
		CORBA::Boolean object_exists() 
			throw (CORBA::SystemException);
		
		CosPersistentState::Pid* get_pid()
			throw (CORBA::SystemException);
		
		CosPersistentState::ShortPid* get_short_pid()
			throw (CORBA::SystemException);
		
		CosPersistentState::StorageHomeBase_ptr get_storage_home()
			throw (CORBA::SystemException);		

	protected:
		
		~StorageObjectImpl() {};

	private:
		Pid* m_pid;
		ShortPid* m_shortPid;
		StorageHomeBase* m_storageHomeBase;
		bool m_bModified;
		string m_strUpdate;
		string m_strSelect;
};

class StorageObjectRefImpl : public virtual CosPersistentState::StorageObjectRef,
						     public virtual RefCountLocalObject
{
	StorageObjectRefImpl(StorageObject* obj=0) 
		throw();

	StorageObjectRefImpl(const StorageObjectRef& ref) // copy constructure
		throw();

	~StorageObjectRefImpl();

	StorageObjectRef& operator=(const StorageObjectRef& ref) 
			throw();

	StorageObjectRef& operator=(StorageObject* obj) 
		throw();

	void release() 
		throw();

	StorageObject* deref() 
		throw(CORBA::SystemException);

	StorageObject* operator->() 
		throw(CORBA::SystemException); // not const!

	void destroy_object() 
		throw(CORBA::SystemException);

	Pid* get_pid() const 
		throw(CORBA::SystemException);

	ShortPid* get_short_pid() const 
		throw(CORBA::SystemException);

	CORBA::Boolean is_null() const 
		throw();

	StorageHomeBase_ptr get_storage_home() const
		throw(CORBA::SystemException);
};

}; // namespace Qedo

#endif
