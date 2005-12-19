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

#ifndef __CSDSTRUC4QXML_H__
#define __CSDSTRUC4QXML_H__


#include <string>
#include <vector>



namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


/**
* implementation descriptor 
*/

struct Descriptor
{
	/** Descriptor type */
	std::string									type;
	/** Filearchive */
	std::string									filearchive;
};

/**
* the implementations
*/
struct Implementation
{
	/** implementation id*/
	std::string									id;
	/** the name of the OS */
	std::string									os_name;
	/** the descriptor */
	Qedo::Descriptor							descriptor;
};

/**
* the Component Software Descriptor data
*/
struct CSDData
{	
	/** Package Type */
	std::string									pkgtype;
	/** Title */
	std::string									title;
	/** Name of author */
	std::string									author;
	/** the implementations */
	std::vector < Qedo::Implementation >		implementations;
};







/** @} */

}

#endif
