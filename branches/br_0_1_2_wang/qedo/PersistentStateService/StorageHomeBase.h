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

#include "PSSUtil.h"
#include "CORBADepends.h"
#include "RefCountBase.h"
#include "QDRecordset.h"


using namespace CosPersistentState;


namespace Qedo
{

class  StorageHomeBaseImpl : public virtual CosPersistentState::StorageHomeBase,
							 public virtual RefCountLocalObject,
							 public virtual QDRecordset
{
	public:

		StorageHomeBaseImpl() {};

		StorageHomeBaseImpl(Sessio_ptr pSession, const char* szOwnStorageHomeName);

		~StorageHomeBaseImpl();
		
		//
		// IDL:omg.org/CosPersistentState/StorageHomeBase/find_by_short_pid:1.0
		//
		StorageObjectBase_ptr find_by_short_pid(const ShortPid& short_pid);

		//
		// IDL:omg.org/CosPersistentState/StorageHomeBase/get_catalog:1.0
		//
		CatalogBase_ptr get_catalog();

		char* getOwnStorageHomeName();

	protected:
		
		char* m_szOwnStorageHomeName;

	private:
		
		CatalogBase_ptr m_pCatalogBase;
		char* m_szBaseStorageHomeName;
};

}; // namespace Qedo

#endif
