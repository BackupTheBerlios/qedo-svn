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

#include "StorageHomeBase.h"
#include "Catalog.h"


namespace Qedo
{

StorageHomeBaseImpl::StorageHomeBaseImpl(Sessio_ptr pSession, const char* szOwnStorageHomeName) :
	m_szBaseStorageHomeName(NULL),
	m_szOwnStorageHomeName(NULL)
{
	strcpy(m_szOwnStorageHomeName, szOwnStorageHomeName);
	m_pCatalogBase = dynamic_cast <CatalogBase_ptr> (pSession);

	QDRecordset::QDRecordset((dynamic_cast <CatalogBaseImpl*> (pSession))->getHDBC());
}

StorageHomeBaseImpl::~StorageHomeBaseImpl()
{
	delete m_szBaseStorageHomeName;
	delete m_szOwnStorageHomeName;
	m_szBaseStorageHomeName = NULL;
	m_szOwnStorageHomeName = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//The find_by_short_pid operation looks for a storage object with the given 
//short pid in the target storage home. If such an object is not found, 
//find_by_short_pid, raises the CosPersistentState::NotFound exception.
////////////////////////////////////////////////////////////////////////////////
StorageObjectBase_ptr 
StorageHomeBaseImpl::find_by_short_pid(const ShortPid& short_pid)
{
	int iLength = short_pid.length();

	unsigned char* sz_shortPid = new unsigned char[iLength];
	
	for(int i=0; i<iLength; i++)
	{
		sz_shortPid[i] = short_pid[i];
	}

	//if(the short_pid in the list)
	//	then return
	//else

	string strToExecute;
	strToExecute = "select * from ";
	strToExecute.append((const char*)m_szBaseStorageHomeName);
	strToExecute += " where storagehome like ";
	strToExecute.append((const char*)m_szOwnStorageHomeName);
	strToExecute += " and spid= ";
	strToExecute.append((const char*)sz_shortPid);
	strToExecute += ";";
	
	Open(strToExecute.c_str());
	
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//The get_catalog operation returns the catalog that manages the target storage 
//home instance.
////////////////////////////////////////////////////////////////////////////////
CatalogBase_ptr 
StorageHomeBaseImpl::get_catalog()
{
	return m_pCatalogBase;
}

char*
StorageHomeBaseImpl::getOwnStorageHomeName()
{
	return m_szOwnStorageHomeName;
}

} // namespace Qedo
