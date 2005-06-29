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

#include "SoftpkgStructures.h"

Implementation::Implementation(std::string uuid, std::string code_type, std::string file_name, std::string entry_point)
{
	_uuid = uuid;
	_code_type = code_type;
	_file_name = file_name;
	_entry_point = entry_point;

};

Implementation::~Implementation()
{};

void Implementation::get_uuid(std::string& uuid)
{
	uuid = _uuid;
};
void Implementation::get_code_type(std::string& code_type)
{
	code_type = _code_type;
};
void Implementation::get_file_name(std::string& file_name)
{
	file_name = _file_name;
};
void Implementation::get_entry_point(std::string& entry_point)
{
	entry_point = _entry_point;
};
