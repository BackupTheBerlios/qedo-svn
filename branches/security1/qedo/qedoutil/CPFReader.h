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

#ifndef __CPF_READER_H__
#define __CPF_READER_H__


#include <CORBA.h>
#include "Valuetypes.h"
#include "DOMXMLParser.h"


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


/**
 * exception
 */
class CPFReadException
{
};


/**
 * read component property file descriptor
 */
class QEDOUTIL_API CPFReader
{
private:

    /** the parsed software package descriptor */
	DOMDocument*							cpf_document_;

	/**
	 * handle choice
	 */
	std::string choice (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle choices
	 */
    void choices (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle defaultvalue
	 */
	std::string defaultvalue (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle description
	 */
	std::string description (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle properties
	 */
    Components::ConfigValues* properties (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle range
	 */
    void range (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle simple
	 */
    Components::ConfigValue* simple (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle sequence
	 */
    void sequence (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle struct
	 */
    void _struct (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle value
	 */
	std::string value (DOMElement*)
        throw(CPFReadException);

	/**
	 * handle valuetype
	 */
	void valuetype (DOMElement*)
        throw(CPFReadException);

public:
	/**
	 * constructor
	 */
	CPFReader();

	/**
	 * destructor
	 */
	virtual ~CPFReader();

	/**
	 * provides the list of config values
	 * \return The list of ConfigValue.
	 */
	Components::ConfigValues* readCPF(std::string descriptor)
		throw(CPFReadException);
};

/** @} */

}

#endif

