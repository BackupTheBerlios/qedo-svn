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

#ifndef __CATALOG_H__
#define __CATALOG_H__

#include <list>
#include "PSSUtil.h"
#include "CORBADepends.h"
#include "RefCountBase.h"
#include "QDDatabase.h"
#include "StorageHomeBase.h"

using namespace std;
using namespace CosPersistentState;

namespace Qedo
{

class CatalogBaseImpl : public virtual CosPersistentState::CatalogBase,
                        public virtual RefCountLocalObject,
						public virtual QDDatabase
{
	public:

		CatalogBaseImpl() {};

		CatalogBaseImpl(const AccessMode eAM, const char* szConnString);

		~CatalogBaseImpl();

		virtual bool Init();

		bool DriverConnect(const char* szConnStr, char* szConnStrOut = NULL, HWND hWnd = NULL, const int nDrvConn = SQL_DRIVER_NOPROMPT);

		//
		// IDL:omg.org/CosPersistentState/CatalogBase/access_mode:1.0
		//
		AccessMode access_mode();

		//
		// IDL:omg.org/CosPersistentState/CatalogBase/find_storage_home:1.0
		//
		StorageHomeBase_ptr find_storage_home(const char* storage_home_id);

		//
		// IDL:omg.org/CosPersistentState/CatalogBase/find_by_pid:1.0
		//
		StorageObjectBase_ptr find_by_pid(const Pid& the_pid);

		//
		// IDL:omg.org/CosPersistentState/CatalogBase/flush:1.0
		//
		void flush();

		//
		// IDL:omg.org/CosPersistentState/CatalogBase/refresh:1.0
		//
		void refresh();

		//
		// IDL:omg.org/CosPersistentState/CatalogBase/free_all:1.0
		//
		void free_all();

		//
		// IDL:omg.org/CosPersistentState/CatalogBase/close:1.0
		//
		void close();

	private:

		AccessMode m_eAM;
		std::list <StorageHomeBaseImpl*> m_lStorageHomeBases;
};


class  SessioImpl : public virtual CosPersistentState::Sessio,
                    public CatalogBaseImpl
{
	public:

		SessioImpl() {};

		SessioImpl(AccessMode eAM, const char* szConnString) {};

		~SessioImpl() {};
};


class  SessionPoolImpl : public virtual CosPersistentState::SessionPool,
                         public CatalogBaseImpl
{
	public:

		SessionPoolImpl() {};

		SessionPoolImpl(AccessMode eAM, TransactionPolicy tx_policy, const char* szConnString);

		~SessionPoolImpl();

		bool Init();

		//
		// IDL:omg.org/CosPersistentState/SessionPool/flush_by_pids:1.0
		//
		void flush_by_pids(const PidList& pids);

		//
		// IDL:omg.org/CosPersistentState/SessionPool/refresh_by_pids:1.0
		//
		void refresh_by_pids(const PidList& pids);

		//
		// IDL:omg.org/CosPersistentState/SessionPool/transaction_policy:1.0
		//
		TransactionPolicy transaction_policy();

	private:

		TransactionPolicy m_tx_policy;
};

}; // namespace Qedo

#endif
