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


namespace QEDO_CIDL_Generator {


class GeneratorPersistenceC : public virtual CPPBase
{

private:

	std::string filename_;
	std::string class_name_;
	Printer out;
	bool isAbstract;
	IR__::StorageHomeDef_var			storagehome_;
	IR__::StorageTypeDef_var			storagetype_;
	std::set<std::string>				m_recursion_set;

	void check_for_generation(IR__::Contained_ptr item);

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doStorageType(IR__::StorageTypeDef_ptr storage_type);
	void doStorageHome(IR__::StorageHomeDef_ptr storage_home);
	void doKey(IR__::KeyDef_ptr key, IR__::InterfaceDef_ptr inf_def);
	void doFactory(IR__::FactoryDef_ptr factory, IR__::InterfaceDef_ptr inf_def);

	void genAttributeWithNomalType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genAttributeWithOtherType(IR__::AttributeDef_ptr attribute, CORBA::TCKind att_type_kind);
	void genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type);
	void genKey(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type, bool isRef);
	void genCreateOperation(IR__::StorageHomeDef_ptr storage_home, bool isRef);
	
public:

	GeneratorPersistenceC(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorPersistenceC();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
