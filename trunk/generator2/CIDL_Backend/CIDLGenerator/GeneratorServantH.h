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

#ifndef __GENERATOR_SERVANTH_H__
#define __GENERATOR_SERVANTH_H__

#include "CPPBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {


class GeneratorServantH : public CPPBase 
{

private:

	Printer						out;
	CIDL::CompositionDef_var	composition_;
	IR__::ComponentDef_var		component_;
	std::set<std::string>		m_recursion_set;

	void check_for_generation(IR__::Contained_ptr item);

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doComponent(IR__::ComponentDef_ptr component);
	void doComposition(CIDL::CompositionDef_ptr coposition);
	void doProvides(IR__::ProvidesDef_ptr provides, IR__::ComponentDef_ptr component);
	void doUses(IR__::UsesDef_ptr uses, IR__::ComponentDef_ptr component);
	void doSink(IR__::SinkDef_ptr sink, IR__::ComponentDef_ptr component);
	void doSource(IR__::SourceDef_ptr source, IR__::ComponentDef_ptr component);
	void doEmits(IR__::EmitsDef_ptr emits, IR__::ComponentDef_ptr component);
	void doPublishes(IR__::PublishesDef_ptr publishes, IR__::ComponentDef_ptr component);
	void doConsumes(IR__::ConsumesDef_ptr consumes, IR__::ComponentDef_ptr component);
	void doProvides(IR__::ProvidesDef_ptr provides);
	void doUses(IR__::UsesDef_ptr uses);
	void doSink(IR__::SinkDef_ptr sink);
	void doSource(IR__::SourceDef_ptr source);
	void doEmits(IR__::EmitsDef_ptr emits);
	void doPublishes(IR__::PublishesDef_ptr publishes);
	void doConsumes(IR__::ConsumesDef_ptr consumes);
	void doHome(IR__::HomeDef_ptr home);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);

	void genOperation(IR__::OperationDef_ptr operation, IR__::IDLType_ptr ret_type);
	void genFacetServants(IR__::ComponentDef_ptr component);
	void genSinkServants(IR__::ComponentDef_ptr component);
	void genConsumerServants(IR__::ComponentDef_ptr component);
	void genContextServant(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc);
	void genContextServantBody(IR__::ComponentDef_ptr component);
	void genComponentServant(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc);
	void genComponentServantBody(IR__::ComponentDef_ptr component, CIDL::LifecycleCategory lc);
	void genHomeServantBegin(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc);
	void genHomeServant(IR__::HomeDef_ptr home, CIDL::LifecycleCategory lc);

public:

	GeneratorServantH(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorServantH();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif

