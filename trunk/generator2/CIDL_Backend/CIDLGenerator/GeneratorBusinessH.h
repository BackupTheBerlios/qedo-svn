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

#ifndef __GENERATOR_BUSINESSH_H__
#define __GENERATOR_BUSINESSH_H__

#include "CPPBase.h"
#include "Printer.h"
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {


class GeneratorBusinessH : public virtual CPPBase
{

private:

	std::string filename_;
	Printer out;
	std::string target_;
	bool need_push_;
	CIDL::CompositionDef_var composition_;
	std::set < std::string > handled_interfaces_;

	void doModule(IR__::ModuleDef_ptr module);
	void doException(IR__::ExceptionDef_ptr except);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doComponent(IR__::ComponentDef_ptr component);
	void doConsumes(IR__::ConsumesDef_ptr consumes, IR__::ComponentDef_ptr component);
	void doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component);
	void doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component);
	void doHome(IR__::HomeDef_ptr home);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);
	void doComposition(CIDL::CompositionDef_ptr composition);

public:

	GeneratorBusinessH(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorBusinessH();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
