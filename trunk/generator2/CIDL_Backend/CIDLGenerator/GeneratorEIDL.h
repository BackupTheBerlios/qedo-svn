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

#ifndef __GENERATOR_EIDL_H__
#define __GENERATOR_EIDL_H__

#include "IDLBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <set>


namespace QEDO_CIDL_Generator {


class GeneratorEIDL : public virtual IDLBase
{

	CORBA::ORB_var _orb;
	std::set<std::string> m_recursion_set;
	void check_for_generation(IR__::Contained_ptr item);

	std::string filename_;
	std::string managed_component_;
	std::map < std::string, bool > includes_;
	std::map < std::string, IR__::ContainedSeq_var > interface_def_map_;

	void planInterfaceContent(IR__::Contained_ptr item);
	void doInterfaceContent(IR__::InterfaceDef_ptr item);

	void doModule(IR__::ModuleDef_ptr module);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doException(IR__::ExceptionDef_ptr except);
	void doEnum(IR__::EnumDef_ptr enumeration);
	void doValue(IR__::ValueDef_ptr value);
	void doEvent(IR__::EventDef_ptr event);
	void doValueMember(IR__::ValueMemberDef_ptr member);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);
	void doHome(IR__::HomeDef_ptr home);
	void doComponent(IR__::ComponentDef_ptr component);
	void doProvides(IR__::ProvidesDef_ptr provides);
	void doUses(IR__::UsesDef_ptr uses);
	void doEmits(IR__::EmitsDef_ptr emits);
	void doPublishes(IR__::PublishesDef_ptr publishes);
	void doConsumes(IR__::ConsumesDef_ptr consumes);
	void doSink(IR__::SinkDef_ptr sink);
	void doSource(IR__::SourceDef_ptr source);
	void doSiSo(IR__::SiSoDef_ptr siso);
	void doAlias(IR__::AliasDef_ptr adef);
	void doStruct(IR__::StructDef_ptr sdef);
	void doUnion(IR__::UnionDef_ptr udef);


public:

	GeneratorEIDL(QEDO_ComponentRepository::CIDLRepository_impl *repository, CORBA::ORB_ptr orb);
	~GeneratorEIDL();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
