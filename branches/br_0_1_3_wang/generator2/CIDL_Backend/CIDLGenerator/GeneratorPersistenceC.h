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
#include "Debug.h"
#include <sstream>
#include <iostream>
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorPersistenceC : public virtual CPPBase
{

private:

	typedef pair <string, string>	Sth_Pair;

	Printer							out;
	bool							m_isAbstract;
	bool							m_isRef;
	std::string						m_filename;
	std::string						m_class_name;
	std::string						m_strName;
	std::string						m_strContent;
	std::set <std::string>			m_recursion_set;
	std::map <string, string>		m_SthMap;
	std::map <string, string> :: const_iterator m_SthIter;
	std::list <IR__::ValueDef_ptr>	m_lValueTypes;

	void check_for_generation(IR__::Contained_ptr item);

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doFactory(IR__::FactoryDef_ptr factory, IR__::InterfaceDef_ptr inf_def);
	void doKey(IR__::KeyDef_ptr key, IR__::InterfaceDef_ptr inf_def);
	void doStorageType(IR__::StorageTypeDef_ptr storagetype);
	void doStorageHome(IR__::StorageHomeDef_ptr storagehome);

	void genAttributeWithNomalType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	//void genAttributeWithAbsStorageType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	//void genAttributeWithAbsStorageTypeRef(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genAttributeWithOtherType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type);
	void genFactory(IR__::OperationDef_ptr operation, IR__::InterfaceDef_ptr inf_type, IR__::InterfaceDef_ptr inf_home );
	void genKey(IR__::OperationDef_ptr operation, IR__::InterfaceDef_ptr inf_type, IR__::InterfaceDef_ptr inf_home, bool isRef);
	void genStorageTypeBody(IR__::StorageTypeDef_ptr storagetype, bool isRef);
	void genCreateOperation(IR__::StorageHomeDef_ptr storagehome, bool isRef);
	void genAbstractObjsForConcreteType(IR__::AbstractStorageTypeDef_ptr abs_storagetype);
	void genAbstractObjsForConcreteHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome);
	string genSQLLine(string strName, string strContent, bool start, bool comma, bool space, bool func=false);
	IR__::AttributeDefSeq collectStateMembers(IR__::InterfaceDef_ptr inf_def, CORBA__::CollectStyle style);


public:

	GeneratorPersistenceC(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorPersistenceC();

	void generate(std::string target, std::string fileprefix);

};


} // namespace
#endif
