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
#ifndef __GENERATOR_PERSISTENCEH_H__
#define __GENERATOR_PERSISTENCEH_H__

#include "CPPBase.h"
#include "Printer.h"
#include "Debug.h"
#include <sstream>
#include <map>


namespace QEDO_CIDL_Generator {


class GeneratorPersistenceH : public virtual CPPBase
{

private:

	Printer out;
	bool bAbstract_;
	bool bTempGenerated_;
	bool bASHKey_; // key is from abstract storage home
	std::string strFilename_;
	std::string strActBasename_;
	std::set<std::string> sRecursion_;
	CIDL::CompositionDef_var composition_;

	void check_for_generation(IR__::Contained_ptr item);

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doKey(IR__::KeyDef_ptr key, IR__::InterfaceDef_ptr inf_def);
	void doFactory(IR__::FactoryDef_ptr factory, IR__::InterfaceDef_ptr inf_def);
	void doAbstractStorageType(IR__::AbstractStorageTypeDef_ptr abs_storagetype);
	void doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome);
	void doStorageType(IR__::StorageTypeDef_ptr storagetype);
	void doStorageHome(IR__::StorageHomeDef_ptr storagehome);
	void doComposition(CIDL::CompositionDef_ptr coposition);

	void genMemberVariable(IR__::StorageTypeDef_ptr storagetype);
	void genMemberVariable(IR__::ComponentDef_ptr component);
	void genDuplAndDown(std::string strClassName);
	void genAttributeWithNomalType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	//void genAttributeWithAbsStorageType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	//void genAttributeWithAbsStorageTypeRef(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genAttributeWithOtherType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type);
	void genPersistentOperation(IR__::OperationDef_ptr operation, IR__::ComponentDef_ptr component, bool isFinder);
	void genFactory(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type);
	void genKey(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type, bool bRef);
	void genBaseRefBody(std::string strTypeName);
	void genAbstractRefBody(IR__::AbstractStorageTypeDef_ptr abs_storagetype);
	void genRefBody(IR__::StorageTypeDef_ptr storagetype);
	void genAbstractStorageTypeBody(IR__::AbstractStorageTypeDef_ptr abs_storagetype/*, bool bRef*/);
	void genStorageTypeBody(IR__::StorageTypeDef_ptr storagetype/*, bool bRef*/);
	void genAbstractObjsForConcreteType(IR__::AbstractStorageTypeDef_ptr abs_storagetype);
	void genAbstractObjsForConcreteHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome);
	void genCreateOperation(IR__::StorageHomeDef_ptr storagehome, bool bRef);
	void genFactoryTemplate(bool isHome);
	void genComponentPersistence(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc);
	void genHomePersistence(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc);
	
	
public:

	GeneratorPersistenceH(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorPersistenceH();

	void generate(std::string target, std::string fileprefix);

};


} // namespace
#endif
