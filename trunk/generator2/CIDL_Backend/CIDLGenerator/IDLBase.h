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

#ifndef __IDLBASE_H__
#define __IDLBASE_H__

#include "GeneratorBase.h"
#include "Printer.h"


namespace QEDO_CIDL_Generator {


//
//
//
class IDLBase : public GeneratorBase
{

protected:

	Printer out;

	void generate_the_item(IR__::Contained_ptr item);
	
	// check whether the contained is defined in an interface
	bool definedInInterface(IR__::Contained_ptr contained);

	// module
	void open_module(IR__::Contained_ptr cont);
	void close_module(IR__::Contained_ptr cont);

	// TypeCode to name
	std::string tcToName(CORBA::TypeCode_ptr type);

	char* map_absolute_name ( CORBA__::IRObject_ptr contained );
	char* map_idl_type ( IR__::IDLType_ptr type );
	char* getLocalName ( CORBA__::IRObject_ptr contained );

public:

	IDLBase(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	virtual ~IDLBase();
};


} // namespace

#endif

