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

#ifndef __INSTALLATION_READER_H__
#define __INSTALLATION_READER_H__


#ifdef _WIN32
#pragma warning (disable : 4290) // exception specification ignored
#endif

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
class InstallationReadException
{
};


/**
 * reader for persistent installation info
 */
class QEDOUTIL_API InstallationReader : public virtual PlatformBase
{
private:

	/** the component installation */
	ComponentImplementationDataVector*			data_;
	/** the parser */
	DOMXMLParser								parser_;
    /** the parsed document */
	DOMDocument*								document_;
    
	/**
	 * deployed
	 */
	void deployed (DOMElement*)
        throw(InstallationReadException);

    /**
	 * implementation
	 */
    void implementation (DOMElement*)
        throw(InstallationReadException);

public:

	/**
	 * constructor
	 * constructs a new implementation
	 */
	InstallationReader();

	/**
	 * destructor
	 */
	~InstallationReader();

	/**
	 * read installation file
	 */
	void read(std::string file, ComponentImplementationDataVector* data)
		throw(InstallationReadException);

	/**
	 * add a new installed implementation
	 */
	void add( std::string file, ComponentImplementationData* data )
		throw(InstallationReadException);

	/**
	 * remove an implementation
	 */
	void remove( std::string file, const char* uuid )
		throw(InstallationReadException);
};


/** @} */

}

#endif
