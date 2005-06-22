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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifndef _QEDO_NO_DB

#include "StorageHomeBase.h"
#include "Catalog.h"


namespace Qedo
{

StorageHomeBaseImpl::StorageHomeBaseImpl() :
	//pCatalogBase_( CatalogBase::_nil() )
	pCatalogBase_( NULL )
{
}

StorageHomeBaseImpl::~StorageHomeBaseImpl()
{
	std::cout << "StorageHomeBaseImpl::~StorageHomeBaseImpl()\n";

	std::cout << lObjectes_.size() << " storage object(s) in the list\n";
	for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
	{
		std::cout << "storage object _remove_ref...\n";
		(*objIter_)->_remove_ref();
		std::cout << "erase storage object from list...\n";
		lObjectes_.erase(objIter_);
	}

	if( !lTempList_.empty() )
		lTempList_.clear();
}

void
StorageHomeBaseImpl::Init( CatalogBase_ptr pCatalogBase, const char* szHomeName )
{
	strHomeName_ = szHomeName;

	//pCatalogBase_ = CatalogBase::_duplicate(pCatalogBase);
	pCatalogBase_ = pCatalogBase;
	//CatalogBaseImpl* pCatalog = dynamic_cast <CatalogBaseImpl*> ( pCatalogBase_.in() );
	CatalogBaseImpl* pCatalog = dynamic_cast <CatalogBaseImpl*> ( pCatalogBase_ );

	QDRecordset::Init( pCatalog->getHDBC() );
}

void
StorageHomeBaseImpl::destroyObject( Pid* pPid ) 
	throw (CORBA::SystemException)
{
	DEBUG_OUT("StorageHomeBaseImpl::destroyObject() is called");

	std::string strPid = convertPidToString( pPid );

	std::string strSqlDel;
	strSqlDel = "DELETE FROM ";
	strSqlDel += strHomeName_;
	strSqlDel += " WHERE pid LIKE \'";
	strSqlDel += strPid;
	strSqlDel += "\';";
	strSqlDel += "DELETE FROM pid_content WHERE pid LIKE \'";
	strSqlDel += strPid;
	strSqlDel += "\';";

	//CatalogBaseImpl* pCatalogBaseImpl = dynamic_cast <CatalogBaseImpl*> (pCatalogBase_.in());
	CatalogBaseImpl* pCatalogBaseImpl = dynamic_cast <CatalogBaseImpl*> (pCatalogBase_);
	pCatalogBaseImpl->ExecuteSQL(strSqlDel.c_str());
}

CORBA::Boolean
StorageHomeBaseImpl::objectExists( Pid* pPid )
	throw (CORBA::SystemException)
{
	DEBUG_OUT("StorageHomeBaseImpl::objectExists() is called");

	std::string strPid = convertPidToString(pPid);

	std::string strSqlSel;
	strSqlSel = "SELECT COUNT(*) FROM ";
	strSqlSel += strHomeName_;
	strSqlSel += " WHERE pid LIKE \'";
	strSqlSel += strPid;
	strSqlSel += "\';";
    
	if(Open(strSqlSel.c_str()))
	{
		long nID = -1;
		GetFieldValue(0, &nID);
		return (nID==1);
	}
	else
		return FALSE;
}

void
StorageHomeBaseImpl::write_state(std::string strUpdate)
{
	//CatalogBaseImpl* pCatalogBaseImpl = dynamic_cast <CatalogBaseImpl*> (pCatalogBase_.in());
	CatalogBaseImpl* pCatalogBaseImpl = dynamic_cast <CatalogBaseImpl*> (pCatalogBase_);
	pCatalogBaseImpl->ExecuteSQL(strUpdate.c_str());
}

void
StorageHomeBaseImpl::read_state()
{

}

////////////////////////////////////////////////////////////////////////////////
//The find_by_short_pid operation looks for a storage object with the given 
//short pid in the target storage home. If such an object is not found, 
//find_by_short_pid raises the CosPersistentState::NotFound exception.
////////////////////////////////////////////////////////////////////////////////
StorageObjectBase 
StorageHomeBaseImpl::find_by_short_pid(const ShortPid& short_pid)
{
	DEBUG_OUT("StorageHomeBaseImpl::find_by_short_pid() is called");

	StorageObjectBase pObj = NULL;

	//find from list
	/*for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
	{
		ShortPid_var pSpid = (*objIter_)->get_short_pid();
		if(compareShortPid(pSpid.in(), short_pid))
		{
			pObj = dynamic_cast <StorageObjectBase> (*objIter_);
			return pObj;
		}
	}*/

	//if not in the list
	std::string strShortPid = convertSpidToString(short_pid);
	std::basic_string <char>::size_type idxBegin;
	static const std::basic_string <char>::size_type npos = -1;
	idxBegin = strShortPid.find("@");
	if( idxBegin==npos )
	{
		std::cout << "Invalid short pid!\n";
		throw CosPersistentState::NotFound();
	}

	std::string strType = strShortPid.substr(++idxBegin, strShortPid.length()-idxBegin);

	std::string strToExecute;
	strToExecute = "SELECT * FROM ";
	strToExecute += strHomeName_;
	strToExecute += " WHERE spid LIKE \'";
	strToExecute += strShortPid;
	strToExecute += "\';";

    if(Open(strToExecute.c_str()))
	{
		std::map<std::string, CORBA::Any> valueMap;
		ValuePaser(valueMap);
		Close();

		//use factory to create a storage object
		//CatalogBaseImpl* pCatalogBaseImpl = dynamic_cast <CatalogBaseImpl*> (pCatalogBase_.in());
		CatalogBaseImpl* pCatalogBaseImpl = dynamic_cast <CatalogBaseImpl*> (pCatalogBase_);

		StorageObjectFactory factory = NULL;
		factory = pCatalogBaseImpl->getConnector()->register_storage_object_factory(strType.c_str(), factory);
		if( factory==NULL )
			throw CosPersistentState::NotFound();
	
		StorageObjectImpl* pObjectImpl = factory->create();
		//factory->_remove_ref();
	
		pObjectImpl->setValue(valueMap);
		lObjectes_.push_back(pObjectImpl);
		pObj = dynamic_cast <StorageObjectBase> (pObjectImpl);
		return pObj;
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
//	return pCatalogBase_.in();
	return pCatalogBase_;
}

std::string
StorageHomeBaseImpl::getFlush()
{
	std::string strFlush = "";

	if(!lTempList_.empty())
		lTempList_.clear();

	for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
	{
		if((*objIter_)->isModified())
		{
			lTempList_.push_back((*objIter_));
			strFlush += (*objIter_)->getUpdate();
		}
	}
	
	return strFlush;
}

std::string
StorageHomeBaseImpl::getFlushByPid(std::vector<Pid> lPidList)
{
	std::string strFlush = "";
	std::vector<Pid>::iterator pidIter;
	
	if(!lTempList_.empty())
		lTempList_.clear();

	for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
	{
		pidIter = lPidList.begin();
		while(pidIter != lPidList.end())
		{
			if( comparePid((*pidIter), (*(*objIter_)->get_pid())) &&
				(*objIter_)->isModified() )
			{
				lTempList_.push_back((*objIter_));
				strFlush += (*objIter_)->getUpdate();
				lPidList.erase(pidIter);
			}
			else
				pidIter++;
		}
	}

	return strFlush;
}

void
StorageHomeBaseImpl::setBatchUnModified()
{
	if(!lTempList_.empty())
	{
		for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
			(*objIter_)->setModified(FALSE);

		lTempList_.clear();
	}
}

void 
StorageHomeBaseImpl::ValuePaser( std::map<std::string, CORBA::Any>& valueMap )
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
	//struct tm* strctData = new struct tm(); // SQL_TYPE_TIMESTAMP -> SQL_C_TYPE_TIMESTAMP(3.x); SQL_TIMESTAMP -> SQL_C_TIMESTAMP(2.x)
	
	for(int iCol=0; iCol<GetFieldCount(); iCol++)
	{
		std::string strColName;
		CORBA::Any anyData;

		memset(szColName, '\0', 256);
		GetFieldAttributes(iCol, szColName, nType, nLen);
		strColName = (char*)szColName;
		
		switch(nType)
		{
			case SQL_CHAR: // also for CORBA::Boolean
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
			//case SQL_TYPE_TIMESTAMP:
			//case SQL_TIMESTAMP:
			//	GetFieldValue(iCol, strctData);
			//	anyData <<= (CORBA::StructDef)strctData;
			//	break;
			//case SQL_NUMERIC:
			//case SQL_DECIMAL:
			//	GetFieldValue(iCol, fltIncome);
			//	break;
			default:
				assert("This data type is unknown!");
				break;
		}

		valueMap[strColName] = anyData;
	}
}

void 
StorageHomeBaseImpl::Refresh()
{
	std::string strRefresh;

	for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
	{
		strRefresh = (*objIter_)->getSelect();
	
		if(Open(strRefresh.c_str()))
		{
			std::map<std::string, CORBA::Any> valueMap;
			ValuePaser(valueMap);
			Close();
			//and then call ...
			(*objIter_)->setValue(valueMap);
		}
	}
}

void 
StorageHomeBaseImpl::RefreshByPid(std::vector<Pid> lPidList)
{
	std::string strRefresh;
	std::vector<Pid>::iterator pidIter;
	
	for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
	{
		for( pidIter=lPidList.begin(); pidIter!=lPidList.end(); pidIter++ )
		{
			if( comparePid((*pidIter), (*(*objIter_)->get_pid())) )
			{
				strRefresh = (*objIter_)->getSelect();
	
				if(Open(strRefresh.c_str()))
				{
					std::map<std::string, CORBA::Any> valueMap;
					ValuePaser(valueMap);
					Close();
					//and then call ...
					(*objIter_)->setValue(valueMap);
				}
			}
		}
	}
}

char*
StorageHomeBaseImpl::getStorageHomeName()
{
	return ( (char*)(strHomeName_.c_str()) );
}

void 
StorageHomeBaseImpl::FreeAllStorageObjects()
{
	for( objIter_=lObjectes_.begin(); objIter_!=lObjectes_.end(); objIter_++ )
	{
		(*objIter_)->_remove_ref();
		lObjectes_.erase(objIter_);
	}
}

} // namespace Qedo
#endif //_QEDO_NO_DB