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
	/** the path to drop files */
	std::string								path_;
	/** the vector for corba type */
	std::vector <std::string>				m_vCorba;
	/** the vector for cpp type */
	std::vector <std::string>				m_vCpp;
	/** the vector for cpp native type */
	std::vector <std::string>				m_vCppNative;
	/** the vector for sql type */
	std::vector <std::string>				m_vSql;
    
    /**
	 * handle qedo-datatype-map
	 */
    void qedo_datatype_map (DOMElement*, std::string dbname)
        throw(DTMReadException);

	/**
	 * find database
	 */
	bool pre_type_mapping (DOMElement*, std::string)
        throw(DTMReadException);

    /**
	 * handle type-mapping
	 */
	void type_mapping (DOMElement*)
        throw(DTMReadException);

    /**
	 * handle name
	 */
	std::string name (DOMElement*)
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
	 * read qedo datatype map
	 */
	void readDTM(std::string descriptor, std::string path, std::string dbname)
		throw(DTMReadException);

	/**
	 * return appropriate map with given type names
	 */
	void getDatatypeMap(std::map<const char*, const char*> mType, std::string dt1, std::string dt2)
		throw(DTMReadException);

};


}

#endif
