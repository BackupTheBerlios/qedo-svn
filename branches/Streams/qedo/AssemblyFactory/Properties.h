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

#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__


#include <CORBA.h>
#include "Components_skel.h"
#include "Valuetypes.h"
#include "DOMXMLParser.h"


namespace Qedo {


/**
 * @addtogroup Assembly
 * @{
 */


/**
 * represents a property desription
 */
class Properties
{
private:
	/** the descriptor file */
	std::string descriptor_;
	/** the parser */
	DOMXMLParser* parser_;
	/** the parsed description */
	DOMDocument* document_;


public:
	/**
	 * constructor
	 * \param descriptor The descriptor file.
	 */
	Properties (std::string descriptor);

	/**
	 * destructor
	 */
	virtual ~Properties();

	/**
	 * provides the list of config values
	 * \return The list of ConfigValue.
	 */
	Components::ConfigValues* getConfigValues();
};

/** @} */

}

#endif

