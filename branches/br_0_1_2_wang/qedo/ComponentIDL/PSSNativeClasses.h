#ifndef __PSSNATIVECLASSES_H__
#define __PSSNATIVECLASSES_H__

#include <CORBA.h>

namespace CosPersistentState
{

class StorageObjectBase
{
	protected:
	
		virtual ~StorageObjectBase () {}
};

class StorageObject : public virtual StorageObjectBase
{
	public:
		
		virtual void _add_ref () = 0;
		
		virtual void _remove_ref () = 0;
		
		// normal mapping of PSDL operations
		virtual void destroy_object () 
			throw (CORBA::SystemException) = 0;
		
		virtual CORBA::Boolean object_exists () 
			throw (CORBA::SystemException) = 0;
		
		virtual CosPersistentState::Pid* get_pid ()
			throw (CORBA::SystemException) = 0;
		
		virtual CosPersistentState::ShortPid* get_short_pid ()
			throw (CORBA::SystemException) = 0;
		
		virtual CosPersistentState::StorageHomeBase_ptr get_storage_home ()
			throw (CORBA::SystemException) = 0;

		static StorageObject* _duplicate(StorageObject*);

		static StorageObject* _downcast(StorageObject*);
		
	
	protected:
		
		virtual ~StorageObject () {}
};

class StorageObjectRef
{
	public:
		
		StorageObjectRef(StorageObject* obj=0) 
			throw();
		
		StorageObjectRef(const StorageObjectRef& ref) // copy constructure
			throw();

		StorageObjectRef(StorageObject* obj) 
			throw();

		~StorageObjectRef ();

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

template class<T>
class Factory
{
	public:

		virtual T* create() throw (SystemException) = 0;
		virtual void _add_ref() {};
		virtual void _remove_ref() {};
		virtual ~Factory() {};
};

typedef Factory<StorageObject> StorageObjectFactory;
typedef Factory<StorageHomeBase> StorageHomeFactory;
typedef Factory<Sessio> SessionFactory;
typedef Factory<SessionPool> SessionPoolFactory;

};

#endif
