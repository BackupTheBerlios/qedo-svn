/*****************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                     */
/*                                                                           */
/* Copyright (c) 2002/2003 by the Qedo Team                                  */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/

#ifndef __GENERATOR_PERSISTENCEH_C__
#define __GENERATOR_PERSISTENCEH_C__

#include "CPPBase.h"
#include "Printer.h"
#include <iostream>
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorPersistenceC : public virtual CPPBase
{

private:

	enum SQLFunc{ sql_CREATE, sql_INSERT, sql_DELETE, sql_SELECT, sql_UPDATE };
	std::string						filename_;
	std::string						class_name_;
	Printer							out;
	bool							isAbstract;
	std::string						m_strContent;
	std::string						m_strName;
	std::set<std::string>			m_recursion_set;

	IR__::AbstractStorageTypeDef_var	m_abs_storagetype;
	IR__::AbstractStorageHomeDef_var	m_abs_storagehome;
	IR__::StorageTypeDef_var			m_storagetype;
	IR__::StorageHomeDef_var			m_storagehome;

	map<string, string>				m_SthMap;
	typedef pair <string, string>	Sth_Pair;
	map <string, string> :: const_iterator m_SthIter;


	void check_for_generation(IR__::Contained_ptr item);

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doKey(IR__::KeyDef_ptr key, IR__::InterfaceDef_ptr inf_def);
	void doFactory(IR__::FactoryDef_ptr factory, IR__::InterfaceDef_ptr inf_def);
	void doStorageType(IR__::StorageTypeDef_ptr storage_type);
	void doStorageHome(IR__::StorageHomeDef_ptr storage_home);

	void genAttributeWithNomalType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	//void genAttributeWithAbsStorageType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	//void genAttributeWithAbsStorageTypeRef(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genAttributeWithOtherType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type);
	void genKey(IR__::OperationDef_ptr operation, IR__::InterfaceDef_ptr inf_type, IR__::InterfaceDef_ptr inf_home, bool isRef);
	void genFactory(IR__::OperationDef_ptr operation, IR__::InterfaceDef_ptr inf_type, IR__::InterfaceDef_ptr inf_home );
	void genCreateOperation(IR__::StorageHomeDef_ptr storage_home, bool isRef);
	void genAbstractObjsForConcreteType(IR__::AbstractStorageTypeDef_ptr abs_storage_type);
	void genAbstractObjsForConcreteHome(IR__::AbstractStorageHomeDef_ptr abs_storage_home);
	void genSQLSentences(IR__::AbstractStorageHomeDef_ptr abs_storage_home, SQLFunc sf);
	void genSQLSentences(IR__::AbstractStorageTypeDef_ptr abs_storage_type, SQLFunc sf);
	string genSQLLine(string strName, string strContent, bool start, bool comma, bool space, bool func=false);
	IR__::AttributeDefSeq collectStateMembers(IR__::InterfaceDef_ptr inf_def, CORBA__::CollectStyle style);

public:

	GeneratorPersistenceC(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorPersistenceC();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
