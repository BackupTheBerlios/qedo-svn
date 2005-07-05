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

#ifndef __GENERATOR_CSD_H__
#define __GENERATOR_CSD_H__


#include "CPPBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {


class GeneratorCSD : public CPPBase
{

private:

	std::set<std::string>	m_recursion_set;
	std::string				filename_;
	std::string				idlfilename_;
	Printer					out;

	/** for using the generator in the project generator */
	/** directory prefix is path to destination of output */
	std::string m_dir_prefix;

	void doComposition(CIDL::CompositionDef_ptr composition);

protected:

	void check_for_generation(IR__::Contained_ptr item);

public:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	/** points to the file which contains all relevant IDL and CIDL */
	/*  of this composition. This file should be the output of an  */
	/*  pretty printer */
	std::string source_file_name_;

	GeneratorCSD(CIDL::CIDLRepository_ptr repository);
	GeneratorCSD(CIDL::CIDLRepository_ptr repository, std::string dir_prefix);
	~GeneratorCSD();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif

