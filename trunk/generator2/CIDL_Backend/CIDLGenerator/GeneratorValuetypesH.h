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

#ifndef __GENERATOR_VALUETYPESH_H__
#define __GENERATOR_VALUETYPESH_H__

#include "CPPBase.h"
#include "Printer.h"
#include <iostream>


namespace QEDO_CIDL_Generator {


class GeneratorValuetypesH : public virtual CPPBase
{

private:

	Printer out;
	std::set<std::string>		m_recursion_set;
	std::set < std::string > handled_interfaces_;

	void check_for_generation(IR__::Contained_ptr item);

	void doValue(IR__::ValueDef_ptr value);
	void doEvent(IR__::EventDef_ptr event);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doInterface(IR__::InterfaceDef_ptr intface);

public:

	GeneratorValuetypesH(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorValuetypesH();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
