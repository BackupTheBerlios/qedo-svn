#ifndef __PSSNATIVECLASSES_H__
#define __PSSNATIVECLASSES_H__

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
