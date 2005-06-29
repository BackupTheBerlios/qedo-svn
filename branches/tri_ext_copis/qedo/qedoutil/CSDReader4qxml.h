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

#ifndef __CSD_READER_4_QXML_H__
#define __CSD_READER_4_QXML_H__


#ifdef _WIN32
#pragma warning (disable : 4290) // exception specification ignored
#endif

#include "Package.h"
#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "CSDStruc4qxml.h"


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
class QEDOUTIL_API CSDReader4qxml : public virtual PlatformBase
{

private:

	/** the component implementation data */
	CSDData*									data_;
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
	std::string author (DOMElement*)
        throw(CSDReadException);

   
    /**
	 * descriptor
	 */
	Descriptor descriptor (DOMElement*)
        throw(CSDReadException);

	    
    /**
	 * fileinarchive
	 */
	//LocationData fileinarchive (DOMElement*)
      //  throw(CSDReadException);
	std::string
	CSDReader4qxml::fileinarchive (DOMElement*)
		throw(CSDReadException);

    /**
	 * Implementation
	 */    
    Implementation implementation (DOMElement*)
        throw(CSDReadException);

	
    /**
	 * link
	 */
	//LocationData link (DOMElement*)
      //  throw(CSDReadException);

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
	std::string pkgtype (DOMElement*)
        throw(CSDReadException);

    
	/**
	 * softpkg
	 */
   void softpkg (DOMElement*)
        throw(CSDReadException);

	/**
	 * softpkgref
	 */
    void softpkgref (DOMElement*)
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

	

public:

	/**
	 * constructor
	 * constructs a new implementation
	 */
	CSDReader4qxml();

	/**
	 * constructor
	 * constructs a new implementation
	 */
	CSDReader4qxml(std::string package, std::string path);

	/**
	 * denstructor
	 */
	~CSDReader4qxml();

	/**
	 * read Component Software Descriptor
	 */
	CSDData getCSD()
		throw(CSDReadException);

	/**
	 * get ccd for the impl_id
	 */
	//std::string getCCD(std::string id)
	//	throw(CSDReadException);
};


/** @} */

}

#endif
