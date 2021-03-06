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
#ifndef __STORAGEHOMEBASE_H__
#define __STORAGEHOMEBASE_H__

#include <list>
#include <string>
#include <vector>
#include "Util.h"
#include "CORBADepends.h"
#include "RefCountBase.h"
#include "PSSStorageObject.h"
#include "QDRecordset.h"
#include "StorageObject.h"
#include "PSSHelper.h"

using namespace std;
using namespace CosPersistentState;

namespace Qedo
{

class CONTAINERDLL_API StorageHomeBaseImpl : public virtual CosPersistentState::StorageHomeBase,
											public virtual RefCountLocalObject,
											public virtual QDRecordset
{
	public:

		StorageHomeBaseImpl();

		~StorageHomeBaseImpl();

		void Init(CatalogBase_ptr pCatalogBase, const char* szStorageHomeName);

		string getFlush();

		string getFlushByPid(std::vector<Pid> lPidList);

		void setBatchUnModified();

		void Refresh();

		void RefreshByPid(std::vector<Pid> lPidList);

		void FreeAllStorageObjects();

		char* getStorageHomeName() { return m_szStorageHomeName; };

		StorageObjectBase find_by_pid(string pid);

		//
		// IDL:omg.org/CosPersistentState/StorageHomeBase/find_by_short_pid:1.0
		//
		StorageObjectBase find_by_short_pid(const ShortPid& short_pid);

		//
		// IDL:omg.org/CosPersistentState/StorageHomeBase/get_catalog:1.0
		//
		CatalogBase_ptr get_catalog();

	private:

		void ValuePaser( map<string, CORBA::Any>& value_map );

	protected:

		char* m_szStorageHomeName; // its own table or view name!
		CatalogBase_ptr m_pCatalogBase;
		std::list <StorageObjectImpl*> m_lStorageObjectes;

	private:

		std::list <StorageObjectImpl*> m_lTempList;
};

}; // namespace Qedo

#endif
