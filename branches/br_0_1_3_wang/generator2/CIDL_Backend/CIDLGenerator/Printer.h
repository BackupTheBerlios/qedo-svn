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

#ifndef __PRINTER_H__
#define __PRINTER_H__

#ifdef _MSC_VER
#pragma warning ( disable:4786 )
#endif

#include <fstream>
#include <string>
#include <map>


namespace QEDO_CIDL_Generator {


//
//
//
class Printer
{

	long indent_;
	std::ofstream stream_;
	bool new_line_;
	std::map < std::string, std::string > user_sections_;

public:

	Printer() : indent_(0), new_line_(true) {}
	~Printer() {}

	Printer& operator<<(int text);
	Printer& operator<<(std::string text);
	Printer& operator<<(std::ifstream& text);

	void open(const char* name);
	void close();

	void indent();
	void unindent();

	void initUserSections(const char* name);
	void insertUserSection(std::string name, int blank_lines = 1);
};

} // namespace QEDO_CIDL_Generator

#endif
