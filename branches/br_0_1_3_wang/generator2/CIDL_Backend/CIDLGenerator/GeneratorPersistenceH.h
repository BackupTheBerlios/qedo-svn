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
#include <map>

using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorPersistenceH : public virtual CPPBase
{

private:

	Printer out;
	bool m_isAbstract;
	bool m_isASHKey; // key is from abstract storage home
	std::string m_filename;
	std::set<std::string> m_recursion_set;

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

	void genAttribute(IR__::StorageTypeDef_ptr storagetype);
	void genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type);
	void genKey(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type, bool isRef);
	void genAbstractStorageTypeBody(IR__::AbstractStorageTypeDef_ptr abs_storagetype, bool isRef);
	void genStorageTypeBody(IR__::StorageTypeDef_ptr storagetype, bool isRef);
	void genAbstractObjsForConcreteType(IR__::AbstractStorageTypeDef_ptr abs_storagetype);
	void genAbstractObjsForConcreteHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome);
	void genCreateOperation(IR__::StorageHomeDef_ptr storagehome, bool isRef);
	
	
public:

	GeneratorPersistenceH(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorPersistenceH();

	void generate(std::string target, std::string fileprefix);

};


} // namespace
#endif
