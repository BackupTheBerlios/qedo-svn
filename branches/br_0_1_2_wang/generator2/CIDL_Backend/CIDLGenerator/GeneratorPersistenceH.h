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
#include <iostream>


namespace QEDO_CIDL_Generator {


class GeneratorPersistenceH : public virtual CPPBase
{

private:

	std::string filename_;
	Printer out;
	std::string target_;
	//bool need_push_;
	//CIDL::CompositionDef_var composition_;

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storage_home);
	void doAbstractStorageType(IR__::AbstractStorageTypeDef_ptr abs_storage_type);
	void doStorageHome(IR__::StorageHomeDef_ptr storage_home);
	void doStorageType(IR__::StorageTypeDef_ptr storage_type);
	void doPSSKey(IR__::PSSKeyDef_ptr psskey);
	void doFactory(IR__::FactoryDef_ptr factory);
	
public:

	GeneratorPersistenceH(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorPersistenceH();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
