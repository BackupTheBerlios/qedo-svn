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
#include "Util.h"
#include "RefCountBase.h"
#include "PSSStorageObject.h"
#include "PSSHelper.h"
#include "StorageHomeBase.h"

using namespace std;
using namespace CosPersistentState;

namespace Qedo
{

class CONTAINERDLL_API StorageObjectImpl : public virtual CosPersistentState::StorageObject,
											public virtual RefCountLocalObject
{
	public:
		
		StorageObjectImpl();

		string getUpdate() { return strUpdate_; };

		string getSelect() { return strSelect_; };

		bool isModified() { return bModified_; };

		void setModified(bool bModified) { bModified_ = bModified; };

		void setStorageHome( StorageHomeBaseImpl* pHomeBaseImpl );

		virtual void setValue(map<string, CORBA::Any> valueMap) { throw CORBA::NO_IMPLEMENT(); };

		//
		// normal mapping of PSDL operations
		//
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

		static StorageObject* _duplicate(StorageObject* pStorageObject)
		{
			if(pStorageObject)
				pStorageObject->_add_ref();
			return pStorageObject;
		};

		static StorageObject* _downcast(StorageObject* pStorageObject)
		{
			//if(pStorageObject)
			//	return dynamic_cast <StorageObjectImpl*> (pStorageObject);
			//else
			//	return NULL;

			return pStorageObject;
		};

	protected:
		
		~StorageObjectImpl() {};

	protected:

		Pid* pid_;
		ShortPid* shortPid_;
		string strUpdate_;
		string strSelect_;

	private:

		StorageHomeBaseImpl* pHomeBaseImpl_;
		bool bModified_;
};


}; // namespace Qedo

#endif
