#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "Util.h"
#include "RefCountBase.h"
#include "PSSNativeClasses.h"


using namespace CosPersistentState;

namespace Qedo
{

class StorageObject : public virtual CosPersistentState::StorageObject,
						public virtual Qedo::RefCountLocalObject
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
		
		~StorageObject() {}

	private:

		StorageHomeBase* m_storageHomeBase;
};

}; // namespace Qedo

#endif
