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

StorageHomeBaseImpl::StorageHomeBaseImpl()
{
}

StorageHomeBaseImpl::~StorageHomeBaseImpl()
{
	if(!m_lStorageObjectes.empty())
	{
		list <StorageObjectImpl*> ::iterator storageObject_iter;
	
		for (storageObject_iter = m_lStorageObjectes.begin();
			storageObject_iter != m_lStorageObjectes.end();
			storageObject_iter++)
		{
			(dynamic_cast <StorageObject*> (*storageObject_iter))->_remove_ref();
		}

		m_lStorageObjectes.clear();
	}

	if(!m_lTempList.empty())
		m_lTempList.clear();

	delete m_szStorageHomeName;
	m_szStorageHomeName = NULL;
}

void StorageHomeBaseImpl::Init(CatalogBase_ptr pCatalogBase, const char* szStorageHomeName)
{
	m_szStorageHomeName = NULL;
	strcpy(m_szStorageHomeName, szStorageHomeName);
	m_pCatalogBase = pCatalogBase;
	
	QDRecordset::Init((dynamic_cast <CatalogBaseImpl*> (m_pCatalogBase))->getHDBC());
}

////////////////////////////////////////////////////////////////////////////////
//The find_by_short_pid operation looks for a storage object with the given 
//short pid in the target storage home. If such an object is not found, 
//find_by_short_pid, raises the CosPersistentState::NotFound exception.
////////////////////////////////////////////////////////////////////////////////
StorageObjectBase 
StorageHomeBaseImpl::find_by_short_pid(const ShortPid& short_pid)
{
	int i = 0;
	int iLength = short_pid.length();

	//find from list
	list <StorageObjectImpl*> ::iterator storageObject_iter;
	
	for (storageObject_iter = m_lStorageObjectes.begin();
		 storageObject_iter != m_lStorageObjectes.end();
		 storageObject_iter++)
	{
		ShortPid* sp = (*storageObject_iter)->get_short_pid();
		if(sp->length()==iLength)
		{
			for(i=0; i<iLength; i++)
			{
				if( (*sp)[i]!=short_pid[i] )
					break;
			}
			
			if(i+1==iLength)
				return (dynamic_cast <StorageObjectBase> (*storageObject_iter));
		}
	}

	//if not in the list
	unsigned char* sz_shortPid = new unsigned char[iLength];
	
	for(i=0; i<iLength; i++)
	{
		sz_shortPid[i] = short_pid[i];
	}

	string strToExecute;
	strToExecute = "select * from "; //??? Which columns should be seleted?
	strToExecute.append((const char*)m_szStorageHomeName);
	strToExecute += " where spid like ";
	strToExecute.append((const char*)sz_shortPid);
	strToExecute += ";";
	
	Open(strToExecute.c_str());

	//
	//ToDo: fetch the data into a storage object, for example through an operation setValue()
	//

	//m_lStorageObjectBases.push_back();
	
	throw CosPersistentState::NotFound();
	
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
StorageHomeBaseImpl::getStorageHomeName()
{
	return m_szStorageHomeName;
}

string 
StorageHomeBaseImpl::getFlush()
{
	if(!m_lTempList.empty())
		m_lTempList.clear();

	string strFlush = "";

	list <StorageObjectImpl*> ::iterator storageObject_iter;
	
	for (storageObject_iter = m_lStorageObjectes.begin();
		 storageObject_iter != m_lStorageObjectes.end();
		 storageObject_iter++)
	{
		if((*storageObject_iter)->isModified())
		{
			m_lTempList.push_back((*storageObject_iter));
			strFlush += (*storageObject_iter)->getUpdate();
		}
	}
	
	return strFlush;
}

string 
StorageHomeBaseImpl::getRefresh()
{
	string strRefresh = "";

	list <StorageObjectImpl*> ::iterator storageObject_iter;
	
	for (storageObject_iter = m_lStorageObjectes.begin();
		 storageObject_iter != m_lStorageObjectes.end();
		 storageObject_iter++)
	{
		strRefresh += (*storageObject_iter)->getSelect();
	}
	
	return strRefresh;
}

void
StorageHomeBaseImpl::setBatchUnModified()
{
	if(!m_lTempList.empty())
	{
		list <StorageObjectImpl*> ::iterator storageObject_iter;
		
		for (storageObject_iter = m_lTempList.begin();
			storageObject_iter != m_lTempList.end();
			storageObject_iter++)
		{
			(*storageObject_iter)->setModified(FALSE);
		}

		m_lTempList.clear();
	}
}

} // namespace Qedo
