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

#ifndef __PSD_READER_H__
#define __PSD_READER_H__


#ifdef _WIN32
#pragma warning (disable : 4290) // exception specification ignored
#endif


#include "DOMXMLParser.h"
#include "PlatformBase.h"
#include <string>
#include <list>


namespace Qedo {


/**
 * exception
 */
class PSDReadException
{
};


/**
 * reader for component persistence description
 */
class QEDOUTIL_API PSDReader : public virtual PlatformBase
{

private:

	/** the parsed CORBA persistence descriptor */
    DOMDocument*							psd_document_;
	/** the path to drop files */
	std::string								path_;
	/** the database connection string */
	std::string								strConn_;
	/** the list holding the create table string */
	std::list <std::string>					lTableList_;
	/** the map for datatypes */
	std::map <const char*, const char*>		mType_;
    
    /**
	 * handle corbapersistence
	 */
    void corbapersistence (DOMElement*)
        throw(PSDReadException);

	/**
	 * handle database-info
	 */
	//void database_info (DOMElement*)
    //    throw(PSDReadException);

	/**
	 * handle connection
	 */
	//void connection (DOMElement*)
    //    throw(PSDReadException);

	/**
	 * handle param
	 */
	//std::string param (DOMElement*)
    //    throw(PSDReadException);

	/**
	 * handle each type
	 */
	std::string get_value (DOMElement*)
        throw(PSDReadException);

    /**
	 * handle storagehome
	 */
	void storagehome (DOMElement*)
        throw(PSDReadException);

    /**
	 * handle field
	 */
	std::string field (DOMElement*)
        throw(PSDReadException);

    /**
	 * handle primarykey
	 */
    std::string primarykey (DOMElement*)
        throw(PSDReadException);

    /**
	 * handle key
	 */
	std::string key (DOMElement*)
        throw(PSDReadException);

	/**
	 * handle independency
	 */
	std::string independency (DOMElement*)
		throw(PSDReadException);

	/**
	 * handle ancestor
	 */
	std::string ancestor (DOMElement*)
		throw(PSDReadException);

	/**
	 * parse table name from the form "PSDL:xxx:1.0"
	 */
	std::string get_table_name (std::string)
		throw(PSDReadException);

public:

	/**
	 * constructor
	 */
	PSDReader();

	/**
	 * denstructor
	 */
	~PSDReader();

	/**
	 * read CORBA Persistence Descriptor
	 */
	std::list<std::string> readPSD(std::string descriptor, std::string path)
		throw(PSDReadException);

	/**
	 * return database connection string
	 */
	std::string getDBConn();

};


}

#endif
