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


#ifdef _WIN32
#pragma warning (disable : 4290) // exception specification ignored
#endif


#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "Package.h"
#include "ComponentImplementationData.h"
#include <string>


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


extern std::string g_qedo_dir;


/**
 * exception
 */
class CCDReadException
{
};


/**
 * reader for component software description
 */
class QEDOUTIL_API CCDReader : public virtual PlatformBase
{

private:

	/** the composition data */
	CompositionData*						data_;
	
	/** the parsed CORBA component descriptor */
	DOMDocument*							ccd_document_;
	/** the package */
	Package*								package_;
	/** the descriptor file */
	std::string								descriptor_;
	/** the path to drop files */
	std::string								path_;


	/**
	 * componentfeature
	 */
	void componentfeatures (DOMElement*)
		throw(CCDReadException);
    
	/**
	 * componentkind
	 */
    void componentkind (DOMElement*)
        throw(CCDReadException);

	/**
	 * containerextension
	 */
    void containerextension (DOMElement*)
        throw(CCDReadException);

    /**
	 * corbacomponent
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
	 * entity
	 */
    void entity (DOMElement*)
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

	/**
	 * ports
	 */
	void ports (DOMElement*)
		throw(CCDReadException);

	/**
	 * process
	 */
    void process (DOMElement*)
        throw(CCDReadException);

	/**
	 * sink
	 */
	void sink(DOMElement*)
		throw(CCDReadException);

	/**
	 * service
	 */
    void service (DOMElement*)
        throw(CCDReadException);

	/**
	 * session
	 */
    void session (DOMElement*)
        throw(CCDReadException);

	/**
	 * source
	 */
	void source(DOMElement*)
		throw(CCDReadException);


	/**
	 * unclassified
	 */
    void unclassified (DOMElement*)
        throw(CCDReadException);

public:

	/**
	 * constructor
	 * constructs a new implementation
	 */
	CCDReader(std::string descriptor, std::string path);

	/**
	 * denstructor
	 */
	~CCDReader();

	/**
	 * read CORBA Component Descriptor
	 */
	void readCCD(CompositionData* data, Package* package)
		throw(CCDReadException);
};


/** @} */

}

#endif
