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

#ifndef __CPPBASE_H__
#define __CPPBASE_H__

#include "GeneratorBase.h"
#include "Printer.h"
#include "CIDLRepository_impl.h"


namespace QEDO_CIDL_Generator {




//
//
//
class CPPBase : public GeneratorBase
{

protected:

	bool open_module(Printer& out, IR__::Contained* cur_cont, std::string prefix = "");
	void close_module(Printer& out, IR__::Contained* cur_cont);

	//
	// Helper functions for C++ mapping
	//
	std::string mapName(std::string name);
	std::string mapName(IR__::Contained_ptr obj);
	std::string mapFullName(IR__::Contained_ptr obj);
	std::string mapFullNameWithPrefix(IR__::Contained_ptr obj, std::string prefix);
	std::string mapFullNameLocal(IR__::Contained_ptr obj);
	std::string mapFullNameServant(IR__::Contained_ptr obj);
	std::string mapFullNamePOA(IR__::Contained_ptr obj);

	char* getAbsoluteName (IR__::Contained_ptr contained, std::string delim = "::")
		throw ( CannotMapAbsoluteName );

	char* getLocalName (IR__::Contained_ptr contained)
		throw ( CannotMapAbsoluteName );

	std::string mapScopeName(IR__::Contained_ptr type)
		throw(CannotMapAbsoluteName);

	char* map_return_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_value_return_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_attribute_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* assign_attribute ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_idl_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_in_parameter_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_inout_parameter_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_out_parameter_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

public:

	CPPBase(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	virtual ~CPPBase();
};


} // namespace

#endif

