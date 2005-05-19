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

#ifndef __CCD_READER_4_QXML_H__
#define __CCD_READER_4_QXML_H__


#ifdef _WIN32
#pragma warning (disable : 4290) // exception specification ignored
#endif

#include "Package.h"
#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "CCDStruc4qxml.h"


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
class QEDOUTIL_API CCDReader4qxml : public virtual PlatformBase
{

private:

	/** the component implementation data */
	CCDData*									data_;
    /** the parsed software package descriptor */
	DOMDocument*								ccd_document_;
	/** the Software Package */
	Package*									package_;
	/** the path to drop files from the package*/
	std::string									path_;
	/** ccd file */
	std::string									ccd_file_;
    
    
	void componentfeatures (DOMElement*)
		throw(CCDReadException);

	/**
	 * ports
	 */
	void ports (DOMElement*)
		throw(CCDReadException);
	
    
	/**
	 * softpkg
	 */
   void softpkg (DOMElement*)
        throw(CCDReadException);

   void consumes (DOMElement*)
	    throw(CCDReadException);

   void publishes (DOMElement*)
	    throw(CCDReadException);

   void uses (DOMElement*)
	    throw(CCDReadException);
   
   void provides (DOMElement*)
	    throw(CCDReadException);

   void emits (DOMElement*)
	    throw(CCDReadException);

   void sink (DOMElement*)
	    throw(CCDReadException);

   void source (DOMElement*)
	    throw(CCDReadException);

public:

	/**
	 * constructor
	 * constructs a new implementation
	 */
	CCDReader4qxml();

	/**
	 * constructor
	 * constructs a new implementation
	 */
	CCDReader4qxml(std::string package, std::string path);

	/**
	 * denstructor
	 */
	~CCDReader4qxml();

	/**
	 * read ports
	 */
	CCDData  getCCD()
		throw(CCDReadException);

	/**
	 * get ccd for the impl_id
	 */
	//std::string getCCD(std::string id)
	//	throw(CSDReadException);
};


/** @} */

}

#endif
