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

#ifndef __GENERATOR_MAKEFILE_H__
#define __GENERATOR_MAKEFILE_H__

#include "CPPBase.h"
#include "Printer.h"

#include <fstream>
#include <iostream>


namespace QEDO_CIDL_Generator {


class GeneratorMakefile : public CPPBase {

	std::string filename_;
	Printer out;
	int uid_;

	void doModule(IR__::ModuleDef_ptr module);
	void doComposition(CIDL::CompositionDef_ptr composition);
	void generateServant();


public:

	GeneratorMakefile(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorMakefile();

	void generate(std::string target, std::string fileprefix);

	std::string target_file_name_;

};


} // namespace


#endif

