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

#ifndef __CCD_READER_H__
#define __CCD_READER_H__


#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "ComponentImplementation.h"
#include <string>

#if !defined(UNUSED) && defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

namespace Qedo {


/**
 * @addtogroup ComponentInstaller
 * @{
 */


extern std::string g_qedo_dir;


// exception
class CCDReadException
{
};


/**
 * reader for component software description
 */
class CCDReader : public virtual PlatformBase
{

private:

	/** the component implementation */
	ComponentImplementation*				component_implementation_;
	/** the parsed CORBA component descriptor */
    DOMDocument*							ccd_document_;
    
    /**
	 * handle corbacomponent
	 */
    void corbacomponent (DOMElement*)
        throw(CCDReadException);

    /**
	 * handle description
	 */
	std::string description (DOMElement*)
        throw(CCDReadException);

    /**
	 * handle descriptor
	 */
	std::string descriptor (DOMElement*)
        throw(CCDReadException);

    /**
	 * handle extension
	 */
    void extension (DOMElement*)
        throw(CCDReadException);

    /**
	 * handle fileinarchive
	 */
	std::string fileinarchive (DOMElement*)
        throw(CCDReadException);

	/**
	 * handle homefeatures
	 */
	void homefeatures (DOMElement*)
		throw(CCDReadException);

	/**
	 * handle homerepid
	 */
	std::string homerepid (DOMElement*)
		throw(CCDReadException);

    /**
	 * handle link
	 */
	std::string link (DOMElement*)
        throw(CCDReadException);

public:

	/**
	 * constructor
	 * constructs a new implementation
	 */
	CCDReader();

	/**
	 * denstructor
	 */
	~CCDReader();

	/**
	 * read CORBA Component Descriptor
	 */
	void readCCD(std::string descriptor, ComponentImplementation* impl)
		throw(CCDReadException);
};


/** @} */

}

#endif
