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

#ifdef MICO_ORB
class StorageObject : public virtual CosPersistentState::StorageObjectBase_pre
#endif

#ifdef ORBACUS_ORB
class StorageObject : public virtual OBNative_CosPersistentState::StorageObjectBase_pre
#endif

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
/*
class StorageObjectRef
{
	public:

		typedef StorageObject _target_type;

		//StorageObjectRef(StorageObject* obj=0)
		//	throw() = 0;
		
		//StorageObjectRef(const StorageObjectRef& ref) // copy constructure
		//	throw() = 0;
	
		virtual StorageObjectRef& operator=(const StorageObjectRef& ref) 
			throw() = 0;

		virtual StorageObjectRef& operator=(StorageObject* obj) 
			throw() = 0;

		virtual void release() 
			throw() = 0;

		virtual StorageObject* deref() 
			throw(CORBA::SystemException) = 0;

		virtual StorageObject* operator->() 
			throw(CORBA::SystemException) = 0; // not const!

		virtual void destroy_object() 
			throw(CORBA::SystemException) = 0;

		virtual Pid* get_pid() const 
			throw(CORBA::SystemException) = 0;

		virtual ShortPid* get_short_pid() const 
			throw(CORBA::SystemException) = 0;

		virtual CORBA::Boolean is_null() const 
			throw() = 0;

		virtual StorageHomeBase_ptr get_storage_home() const
			throw(CORBA::SystemException) = 0;

		static StorageObjectRef _duplicate(StorageObjectRef ref);

		static StorageObjectRef _downcast(StorageObjectRef ref);

	protected:

		virtual ~StorageObjectRef() {};
};
*/

class StorageObjectRef
{
	public:

		typedef StorageObject _target_type;

		StorageObjectRef(StorageObject* obj=0)
			throw() {};
		
		StorageObjectRef(const StorageObjectRef& ref) // copy constructure
			throw() {};
	
		~StorageObjectRef() {};

		StorageObjectRef& operator=(const StorageObjectRef& ref) 
			throw() { throw CORBA::NO_IMPLEMENT(); };

		StorageObjectRef& operator=(StorageObject* obj) 
			throw() { throw CORBA::NO_IMPLEMENT(); };

		void release() 
			throw() { throw CORBA::NO_IMPLEMENT(); };

		StorageObject* deref() 
			throw(CORBA::SystemException) { throw CORBA::NO_IMPLEMENT(); };

		StorageObject* operator->() 
			throw(CORBA::SystemException) { throw CORBA::NO_IMPLEMENT(); }; // not const!

		void destroy_object() 
			throw(CORBA::SystemException) { throw CORBA::NO_IMPLEMENT(); };

		Pid* get_pid() const 
			throw(CORBA::SystemException) { throw CORBA::NO_IMPLEMENT(); };

		ShortPid* get_short_pid() const 
			throw(CORBA::SystemException) { throw CORBA::NO_IMPLEMENT(); };

		CORBA::Boolean is_null() const 
			throw() { throw CORBA::NO_IMPLEMENT(); };

		StorageHomeBase_ptr get_storage_home() const
			throw(CORBA::SystemException) { throw CORBA::NO_IMPLEMENT(); };

		static StorageObjectRef _duplicate(StorageObjectRef ref) { throw CORBA::NO_IMPLEMENT(); };

		static StorageObjectRef _downcast(StorageObjectRef ref) { throw CORBA::NO_IMPLEMENT(); };
};


};

#endif
