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
#ifndef __GENERATOR_PSD__
#define __GENERATOR_PSD__

#include "CPPBase.h"
#include "Printer.h"
#include "Debug.h"
#include <sstream>


namespace QEDO_CIDL_Generator {


class GeneratorPSD : public virtual CPPBase
{

private:

	Printer out;
	std::string strFilename_;
	std::set<std::string> sRecursion_;
	std::list<IR__::ValueDef_ptr> lValueTypes_;

	void check_for_generation(IR__::Contained_ptr item);

	void doAbstractStorageHome(IR__::AbstractStorageHomeDef_ptr abs_storagehome);
	void doStorageHome(IR__::StorageHomeDef_ptr storagehome);

	IR__::AttributeDefSeq collectStateMembers(IR__::InterfaceDef_ptr inf_def, CORBA__::CollectStyle style);
	
	
public:

	GeneratorPSD(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorPSD();

	void generate(std::string target, std::string fileprefix);

};


} // namespace
#endif
