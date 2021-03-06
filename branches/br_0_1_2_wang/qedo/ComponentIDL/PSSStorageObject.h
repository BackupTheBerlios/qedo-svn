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

#ifndef __STORAGEOBJECT_H__
#define __STORAGEOBJECT_H__

#include <CORBA.h>
#include "CORBADepends.h"

namespace CosPersistentState
{

class StorageObject : public virtual OBNative_CosPersistentState::StorageObjectBase_pre
{
	public:
		
		virtual void _add_ref() = 0;
		
		virtual void _remove_ref() = 0;
		
		// normal mapping of PSDL operations
		virtual void destroy_object() 
			throw (CORBA::SystemException) = 0;
		
		virtual CORBA::Boolean object_exists() 
			throw (CORBA::SystemException) = 0;
		
		virtual CosPersistentState::Pid* get_pid()
			throw (CORBA::SystemException) = 0;
		
		virtual CosPersistentState::ShortPid* get_short_pid()
			throw (CORBA::SystemException) = 0;
		
		virtual CosPersistentState::StorageHomeBase_ptr get_storage_home()
			throw (CORBA::SystemException) = 0;

		static StorageObject* _duplicate(StorageObject*);

		static StorageObject* _downcast(StorageObject*);
		
	
	protected:
		
		virtual ~StorageObject() {}
};

class StorageObjectRef
{
	public:
		
		StorageObjectRef(StorageObject* obj=0) 
			throw() {};
		
		StorageObjectRef(const StorageObjectRef& ref) // copy constructure
			throw() {};

		~StorageObjectRef() {};

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

		static StorageObjectRef _duplicate(StorageObjectRef ref);

		static StorageObjectRef _downcast(StorageObjectRef ref);


	public:
		
		typedef StorageObject _target_type;
};

};

#endif
