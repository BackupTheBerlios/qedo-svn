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

StorageHomeBaseImpl::StorageHomeBaseImpl() :
	m_szStorageHomeName(NULL)
{
}

StorageHomeBaseImpl::~StorageHomeBaseImpl()
{
	if(!m_lStorageObjectes.empty())
	{
		list <StorageObjectImpl*> ::iterator storageObject_iter;
	
		for(storageObject_iter = m_lStorageObjectes.begin();
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
	m_pCatalogBase = pCatalogBase;
	strcpy(m_szStorageHomeName, szStorageHomeName);
	
	QDRecordset::Init((dynamic_cast <CatalogBaseImpl*> (m_pCatalogBase))->getHDBC());
}

StorageObjectBase 
StorageHomeBaseImpl::find_by_pid(string pid)
{
	string strToExecute;
	strToExecute = "select * from ";
	strToExecute.append((const char*)m_szStorageHomeName);
	strToExecute += " where PID like ";
	strToExecute += pid;
	strToExecute += ";";

	if(Open(strToExecute.c_str()))
	{
		map<string, CORBA::Any> valueMap;
		ValuePaser(valueMap);
		Close();

		//use factory to create a storage object
		StorageObjectFactory factory = new OBNative_CosPersistentState::StorageObjectFactory_pre();
		CatalogBaseImpl* tmp_catalog = dynamic_cast <CatalogBaseImpl*> (m_pCatalogBase);
		factory = tmp_catalog->getConnector()->register_storage_object_factory(NULL, factory);
		StorageObjectImpl* pStorageObjectImpl = factory->create();

		pStorageObjectImpl->setValue(valueMap);
		m_lStorageObjectes.push_back(pStorageObjectImpl);
		return (dynamic_cast <StorageObjectBase> (pStorageObjectImpl));
	}
	else
		throw CosPersistentState::NotFound();
}

////////////////////////////////////////////////////////////////////////////////
//The find_by_short_pid operation looks for a storage object with the given 
//short pid in the target storage home. If such an object is not found, 
//find_by_short_pid raises the CosPersistentState::NotFound exception.
////////////////////////////////////////////////////////////////////////////////
StorageObjectBase 
StorageHomeBaseImpl::find_by_short_pid(const ShortPid& short_pid)
{
	//find from list
	list <StorageObjectImpl*> ::iterator storageObject_iter;
	
	for (storageObject_iter = m_lStorageObjectes.begin();
		 storageObject_iter != m_lStorageObjectes.end();
		 storageObject_iter++)
	{
		ShortPid* cur_spid = (*storageObject_iter)->get_short_pid();
		if(PSSHelper::compareShortPid(*cur_spid, short_pid))
			return (dynamic_cast <StorageObjectBase> (*storageObject_iter));
	}

	//if not in the list
	string strShortPid = PSSHelper::convertSpidToString(short_pid);
	
	string strToExecute;
	strToExecute = "select * from ";
	strToExecute.append((const char*)m_szStorageHomeName);
	strToExecute += " where SPID like ";
	strToExecute += strShortPid;
	strToExecute += ";";

	if(Open(strToExecute.c_str()))
	{
		map<string, CORBA::Any> valueMap;
		ValuePaser(valueMap);
		Close();

		//use factory to create a storage object
		StorageObjectFactory factory = new OBNative_CosPersistentState::StorageObjectFactory_pre();
		CatalogBaseImpl* tmp_catalog = dynamic_cast <CatalogBaseImpl*> (m_pCatalogBase);
		factory = tmp_catalog->getConnector()->register_storage_object_factory(NULL, factory);
		StorageObjectImpl* pStorageObjectImpl = factory->create();

		pStorageObjectImpl->setValue(valueMap);
		m_lStorageObjectes.push_back(pStorageObjectImpl);
		return (dynamic_cast <StorageObjectBase> (pStorageObjectImpl));
	}
	else
		throw CosPersistentState::NotFound();
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

string 
StorageHomeBaseImpl::getFlush()
{
	string strFlush = "";

	if(!m_lTempList.empty())
		m_lTempList.clear();

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
StorageHomeBaseImpl::getFlushByPid(std::vector<Pid> lPidList)
{
	string strFlush = "";
	vector <Pid> ::iterator pid_iter;
	list <StorageObjectImpl*> ::iterator storageObject_iter;
	
	if(!m_lTempList.empty())
		m_lTempList.clear();

	for( storageObject_iter = m_lStorageObjectes.begin();
		 storageObject_iter != m_lStorageObjectes.end();
		 storageObject_iter++)
	{
		pid_iter = lPidList.begin();
		while(pid_iter != lPidList.end())
		{
			if( PSSHelper::comparePid((*pid_iter), (*(*storageObject_iter)->get_pid())) &&
				(*storageObject_iter)->isModified() )
			{
				m_lTempList.push_back((*storageObject_iter));
				strFlush += (*storageObject_iter)->getUpdate();
				lPidList.erase(pid_iter);
			}
			else
				pid_iter++;
		}
	}

	return strFlush;
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

void 
StorageHomeBaseImpl::ValuePaser( map<string, CORBA::Any>& valueMap )
{
	int nType, nLen;
	unsigned char szColName[256];

	unsigned char szData[1024]; // SQL_CHAR or SQL_VARCHAR -> SQL_C_CHAR; SQL_BINARY -> SQL_C_BINARY
	unsigned char ucData; // SQL_BIT -> SQL_C_BIT
	char cData; // SQL_TINYINT -> SQL_C_TINYINT				
	short siData; // SQL_SMALLINT -> SQL_C_SHORT				
	long lData; // SQL_INTEGER -> SQL_C_LONG				
	float fData; // SQL_REAL -> SQL_C_FLOAT
	double dData; // SQL_DOUBLE or SQL_FLOAT -> SQL_C_DOUBLE
	struct tm* strctData = new struct tm(); // SQL_TYPE_TIMESTAMP -> SQL_C_TYPE_TIMESTAMP(3.x); SQL_TIMESTAMP -> SQL_C_TIMESTAMP(2.x)
	
	for(int iCol=0; iCol<GetFieldCount(); iCol++)
	{
		string strColName;
		CORBA::Any anyData;
		typedef pair <string, CORBA::Any> Value_Pair;

		memset(szColName, '\0', 256);
		GetFieldAttributes(iCol, szColName, nType, nLen);
		strColName = (char*)szColName;
		
		switch(nType)
		{
			case SQL_CHAR:
			case SQL_VARCHAR:
				memset(szData, '\0', 1024);
				GetFieldValue(iCol, szData);
				anyData <<= (const char*)szData;
				break;
			case SQL_BIT:
				GetFieldValue(iCol, &ucData);
				anyData <<= CORBA::Any::from_octet(ucData);
				break;
			case SQL_TINYINT:
				GetFieldValue(iCol, cData);
				anyData <<= CORBA::Any::from_char(cData);
				break;
			case SQL_SMALLINT:
				GetFieldValue(iCol, &siData);
				anyData <<= (CORBA::Short)siData;
				break;
			case SQL_INTEGER:
				GetFieldValue(iCol, &lData);
				anyData <<= (CORBA::Long)lData;
				break;
			case SQL_REAL:
				GetFieldValue(iCol, &fData);
				anyData <<= (CORBA::Float)fData;
				break;
			case SQL_DOUBLE:
			case SQL_FLOAT:
				GetFieldValue(iCol, &dData);
				anyData <<= (CORBA::Double)dData;
				break;
			case SQL_TYPE_TIMESTAMP:
			case SQL_TIMESTAMP:
				GetFieldValue(iCol, strctData);
				//anyData <<= (void*)strctData;
				break;
			case SQL_NUMERIC:
			case SQL_DECIMAL:
			//	GetFieldValue(iCol, fltIncome);
				break;
			default:
				assert("This data type is unknown!");
				break;
		}

		valueMap.insert( Value_Pair(strColName, anyData) );
	}
}

void 
StorageHomeBaseImpl::Refresh()
{
	string strRefresh;
	list <StorageObjectImpl*> ::iterator storageObject_iter;

	for (storageObject_iter = m_lStorageObjectes.begin();
		 storageObject_iter != m_lStorageObjectes.end();
		 storageObject_iter++)
	{
		strRefresh = (*storageObject_iter)->getSelect();
	
		if(Open(strRefresh.c_str()))
		{
			map<string, CORBA::Any> valueMap;
			ValuePaser(valueMap);
			Close();
			//and then call ...
			(*storageObject_iter)->setValue(valueMap);
		}
	}
}

void 
StorageHomeBaseImpl::RefreshByPid(std::vector<Pid> lPidList)
{
	string strRefresh;
	vector <Pid> ::iterator pid_iter;
	list <StorageObjectImpl*> ::iterator storageObject_iter;
	
	for (storageObject_iter = m_lStorageObjectes.begin();
		 storageObject_iter != m_lStorageObjectes.end();
		 storageObject_iter++)
	{
		for( pid_iter = lPidList.begin();
			 pid_iter != lPidList.end();
			 pid_iter++ )
		{
			if( PSSHelper::comparePid((*pid_iter), (*(*storageObject_iter)->get_pid())) )
			{
				strRefresh = (*storageObject_iter)->getSelect();
	
				if(Open(strRefresh.c_str()))
				{
					map<string, CORBA::Any> valueMap;
					ValuePaser(valueMap);
					Close();
					//and then call ...
					(*storageObject_iter)->setValue(valueMap);
				}
			}
		}
	}
}

void 
StorageHomeBaseImpl::FreeAllStorageObjects()
{

}
} // namespace Qedo
