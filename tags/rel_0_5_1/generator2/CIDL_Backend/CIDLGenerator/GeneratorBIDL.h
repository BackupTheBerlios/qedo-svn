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

#ifndef __GENERATOR_BIDL_H__
#define __GENERATOR_BIDL_H__

#include "IDLBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {

typedef map < string, bool > t_string_map;
//
//
//
class GeneratorBIDL : public virtual IDLBase
{

private:

	std::set<std::string> m_recursion_set;
	std::string filename_;
	
	void doComposition(CIDL::CompositionDef_ptr composition);

	void
	gen_facet(IR__::ComponentDef_ptr component, t_string_map implemented_facets, t_string_map facet_types);

protected:

	void check_for_generation(IR__::Contained_ptr item);

public:

	GeneratorBIDL(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorBIDL();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif

