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


#ifdef _WIN32
#pragma warning (disable : 4290) // exception specification ignored
#endif

#include "Package.h"
#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "ComponentImplementationData.h"


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


extern std::string g_qedo_dir;


/**
 * exception
 */
class CSDReadException
{
};


/**
 * reader for component software description
 */
class QEDOUTIL_API CSDReader : public virtual PlatformBase
{

private:

	/** the component implementation data */
	ComponentImplementationData*				data_;
    /** the parsed software package descriptor */
	DOMDocument*								csd_document_;
	/** the Software Package */
	Package*									package_;
	/** the path to drop files from the package*/
	std::string									path_;
	/** ccd file */
	std::string									ccd_file_;
    
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
	LocationData fileinarchive (DOMElement*)
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
	LocationData link (DOMElement*)
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
	void readCSD(std::string package, ComponentImplementationData* data, std::string path)
		throw(CSDReadException);
};


/** @} */

}

#endif
