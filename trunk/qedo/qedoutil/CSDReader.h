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

#ifndef __CSD_READER_H__
#define __CSD_READER_H__


#include "Package.h"
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
class CSDReadException
{
};


/**
 * reader for component software description
 */
class CSDReader : public virtual PlatformBase
{

private:

	/** the component implementation */
	ComponentImplementation*				component_implementation_;
    /** the parsed software package descriptor */
	DOMDocument*							csd_document_;
	/** the CORBA component descriptor */
	std::string								ccd_file_;
    
    /**
	 * handle author
	 */
    void author (DOMElement*)
        throw(CSDReadException);

    /**
	 * handle code
	 */
    void code (DOMElement*)
        throw(CSDReadException);

	/**
	 * handle company
	 */
	std::string company (DOMElement*)
        throw(CSDReadException);

    /**
	 * handle dependency
	 */
    void dependency (DOMElement*)
        throw(CSDReadException);

    /**
	 * description
	 */
	std::string description (DOMElement*)
        throw(CSDReadException);

    /**
	 * descriptor
	 */
	std::string descriptor (DOMElement*)
        throw(CSDReadException);

	/**
	 * entrypoint
	 */
	std::string entrypoint (DOMElement*)
        throw(CSDReadException);

    /**
	 * extension
	 */
    void extension (DOMElement*)
        throw(CSDReadException);

    /**
	 * fileinarchive
	 */
	std::string fileinarchive (DOMElement*)
        throw(CSDReadException);

    /**
	 * idl
	 */
    void idl (DOMElement*)
        throw(CSDReadException);

    /**
	 * implementation
	 */
    void implementation (DOMElement*)
        throw(CSDReadException);

    /**
	 * license
	 */
    std::string license (DOMElement*)
        throw(CSDReadException);

    /**
	 * link
	 */
	std::string link (DOMElement*)
        throw(CSDReadException);

	/**
	 * name
	 */
	std::string name (DOMElement*)
        throw(CSDReadException);

    /**
	 * os
	 */
	std::string os (DOMElement*)
        throw(CSDReadException);

    /**
	 * package type
	 */
    void pkgtype (DOMElement*)
        throw(CSDReadException);

    /**
	 * propertyfile
	 */
    void propertyfile (DOMElement*)
        throw(CSDReadException);

	/**
	 * softpkg
	 */
    void softpkg (DOMElement*)
        throw(CSDReadException);

    /**
	 * title
	 */
	std::string title (DOMElement*)
        throw(CSDReadException);

	/**
	 * usage
	 */
	std::string usage (DOMElement*)
        throw(CSDReadException);

	/**
	 * valuetypefactory
	 */
	void valuetypefactory (DOMElement*)
        throw(CSDReadException);

	/**
	 * webpage
	 */
	std::string webpage (DOMElement*)
        throw(CSDReadException);

public:

	/**
	 * constructor
	 * constructs a new implementation
	 */
	CSDReader();

	/**
	 * denstructor
	 */
	~CSDReader();

	/**
	 * read Component Software Descriptor
	 */
	void readCSD(std::string descriptor, ComponentImplementation* impl)
		throw(CSDReadException);
};


/** @} */

}

#endif
