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

#ifndef __NAME_SERVICE_BASE_H__
#define __NAME_SERVICE_BASE_H__


#include "qedoutil.h"
#include <CORBA.h>
#ifdef MICO_ORB
#include <coss/CosNaming.h>
#else
#include <CosNaming.h>
#endif
#include <stdio.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


/**
 * base class for easy name service usage
 */
class QEDOUTIL_API NameServiceBase
{
protected:
	/**
	 * constructor
	 */
	NameServiceBase();

	/** the name service reference */
	CosNaming::NamingContext_var nameService_;

public:
	/**
	 * desctructor
	 */
    virtual ~NameServiceBase();

    /**
	 * initialize NameService
	 */
    bool initNameService (CORBA::ORB_ptr);

    /**
	 * register a name in NameService
	 * \param name The name of the binding.
	 * \param obj The reference of the binding.
	 * \param rebind True if rebinding allowed.
	 */
	bool registerName (std::string name, CORBA::Object_ptr obj, bool rebind);

    /**
	 * resolve a name from NameService
	 * \param name The name of the binding.
	 */
	CORBA::Object_ptr resolveName (std::string name);
};

/** @} */

} // namespace

#endif

