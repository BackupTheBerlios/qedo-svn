#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "PSSUtil.h"
#include "RefCountBase.h"
#include "PSSNativeClasses.h"


using namespace CosPersistentState;

namespace Qedo
{

class StorageObjectImpl : public virtual CosPersistentState::StorageObject,
						  public virtual RefCountLocalObject
{
	public:
		
		// normal mapping of PSDL operations
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
		
		~StorageObjectImpl() {}

	private:

		StorageHomeBase* m_storageHomeBase;
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
