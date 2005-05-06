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
#ifndef __DTM_READER_H__
#define __DTM_READER_H__

#ifdef _WIN32
#pragma warning (disable : 4290) // exception specification ignored
#endif

#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include "CORBADepends_skel.h"
#include <string>
#include <vector>
#include <map>


namespace Qedo {

/**
 * exception
 */
class DTMReadException
{
};


/**
 * reader for datatype mapping
 */
class QEDOUTIL_API DTMReader : public virtual PlatformBase
{

private:

	/** the parsed datatype map */
	DOMDocument*							dtm_document_;
	/** the vector for corba type */
	std::vector<std::string>				vCorba_;
	/** the vector for cpp type */
	std::vector<std::string>				vCpp_;
	/** the vector for cpp native type */
	std::vector<std::string>				vCppNative_;
	/** the vector for sql type */
	std::vector<std::string>				vSql_;
	/** database connection information - name */
	std::vector<std::string>				vName_;
	/** database connection information - value */
	std::vector<std::string>				vValue_;
    /** the database connection string */
	std::string								strConn_;
	

    /**
	 * handle connection
	 */
    void connection (DOMElement*)
        throw(DTMReadException);

    /**
	 * handle type-mapping
	 */
	void type_mapping (DOMElement*)
        throw(DTMReadException);

    /**
	 * handle mapping
	 */
    void mapping (DOMElement*)
        throw(DTMReadException);

    /**
	 * handle each type
	 */
	std::string get_value (DOMElement*)
        throw(DTMReadException);

public:

	/**
	 * constructor
	 */
	DTMReader();

	/**
	 * denstructor
	 */
	~DTMReader();

	/**
	 * read database connection information
	 */
	std::string readConnection(std::string descriptor)
		throw(DTMReadException);

	void readConnection(std::string descriptor, CosPersistentState::ParameterList& params)
		throw(DTMReadException);

	/**
	 * read qedo datatype map
	 */
	void readDatatype(std::string descriptor)
		throw(DTMReadException);

	/**
	 * return appropriate map with given type names
	 */
	void getDatatypeMap(std::map<const char*, const char*> mType, std::string dt1, std::string dt2)
		throw(DTMReadException);
};

}

#endif
