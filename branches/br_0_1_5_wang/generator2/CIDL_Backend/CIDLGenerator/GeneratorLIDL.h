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

#ifndef __GENERATOR_LIDL_H__
#define __GENERATOR_LIDL_H__

#include "IDLBase.h"
#include "Printer.h"

#include <fstream>
#include <iostream>

#include <set>
using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorLIDL : public virtual IDLBase
{
	std::set<std::string> m_recursion_set;
	void check_for_generation(IR__::Contained_ptr item);

	string filename_;
	std::string managed_component_;
	IR__::ComponentDef_var component_;

	void doModule(IR__::ModuleDef_ptr module);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doValue(IR__::ValueDef_ptr value);
	void doEvent(IR__::EventDef_ptr event);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);
	void doHome(IR__::HomeDef_ptr home);
	// do component needs to be replaced by do composition
	void doComponent(IR__::ComponentDef_ptr component);
	void doComposition(CIDL::CompositionDef_ptr coposition);
	void doUses(IR__::UsesDef_ptr uses, IR__::ComponentDef_ptr component);
	void doEmits(IR__::EmitsDef_ptr emits, IR__::ComponentDef_ptr component);
	void doPublishes(IR__::PublishesDef_ptr publishes, IR__::ComponentDef_ptr component);
	void doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component);
	void doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component);

public:

	GeneratorLIDL(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorLIDL();

	void generate(std::string target, std::string fileprefix);

};

} // namespace QEDO_CIDL_Generator

#endif
