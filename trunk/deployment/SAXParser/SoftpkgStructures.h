/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

#ifndef SOFTPKG_DESCRIPTOR_STRUCTURES_HH
#define SOFTPKG_DESCRIPTOR_STRUCTURES_HH

#include <iostream>
#include <string>
#include <list>

class Implementation // the definition of a Implementation element from the softpkg descriptors;
{
private:

	std::string _uuid;
	std::string _code_type;
	std::string _file_name;
	std::string _entry_point;

public:
	Implementation(std::string, std::string, std::string, std::string);
	virtual ~Implementation();
	void get_uuid(std::string&);
	void get_code_type(std::string&);
	void get_file_name(std::string&);
	void get_entry_point(std::string&);

};


typedef std::list <Implementation*> CodeList;

#endif 