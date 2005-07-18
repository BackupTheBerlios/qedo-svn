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

#include "PSDReader.h"
#include "DTMReader.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/framework/URLInputSource.hpp>


static char rcsid[] UNUSED = "$Id: PSDReader.cpp,v 1.2 2004/05/13 13:01:57 hao Exp $";


namespace Qedo {


PSDReader::PSDReader()
{
}

PSDReader::~PSDReader()
{
	if(!lTableList_.empty())
		lTableList_.clear();
}

std::string
PSDReader::get_table_name (std::string name)
throw(PSDReadException)
{
	std::basic_string <char>::size_type idxBegin, idxEnd;
	static const std::basic_string <char>::size_type npos = -1;

	idxBegin = name.find(":");
	idxEnd = name.rfind(":");
	if (idxBegin != npos || idxEnd != npos)
		throw PSDReadException();

	return name.substr(++idxBegin, idxEnd-idxBegin);
}

void
PSDReader::corbapersistence (DOMElement* element)
throw(PSDReadException)
{
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			// handle storagehome
			if ( !XMLString::compareString(child->getNodeName(), X("storagehome")) )
				storagehome((DOMElement*)child);
			// get qedo datatype map
			//else if ( !XMLString::compareString(child->getNodeName(), X("database-info")) )
			//	database_info((DOMElement*)child);
		}

        // get next child
		child = child->getNextSibling();
    }
}
/*
void
PSDReader::database_info (DOMElement* element)
throw(PSDReadException)
{
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			// handle dbname
			if ( !XMLString::compareString(child->getNodeName(), X("dbname")) )
			{
				DTMReader dtm_reader;
				dtm_reader.readDTM( path_ + "qedo-datatype-map.xml", path_, get_value((DOMElement*)child) );
				dtm_reader.getDatatypeMap(mType_, "corba-type", "sql-type");
				return;
			}
			// handle connection
			else if ( !XMLString::compareString(child->getNodeName(), X("connection")) )
				connection((DOMElement*)child);
		}

        // get next child
		child = child->getNextSibling();
    }
}

void
PSDReader::connection (DOMElement* element)
throw(PSDReadException)
{
	unsigned int i = 0;
	unsigned int len = 0;
	DOMNodeList* nodeList;

	strConn_ = "";
	nodeList = element->getElementsByTagName(X("param"));
	for (i = 0; i < len; ++i)
	{
		strConn_ += param((DOMElement*)(nodeList->item(i)));
	}
}

std::string
PSDReader::param (DOMElement* element)
throw(PSDReadException)
{
	std::string text = "";
	
	text += XMLString::transcode(element->getAttribute(X("name")));
	text += "=";
	text = XMLString::transcode(element->getAttribute(X("value")));
	text += ";";
	
	return text;
}
*/
std::string
PSDReader::get_value(DOMElement* element)
throw(PSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
		text = XMLString::transcode(node->getNodeValue());

	return text;
}

void
PSDReader::storagehome (DOMElement* element)
throw(PSDReadException)
{
	unsigned int i = 0;
	unsigned int len = 0;
	DOMNodeList* nodeList;

	// parse table name
	std::string table = XMLString::transcode(element->getAttribute(X("id")));
	std::string text = "CREATE TABLE " + get_table_name(table) + "( ";
	
	// check whether storagehome is derived from others
	std::string inh = "";
	nodeList = element->getElementsByTagName(X("independency"));
	len = nodeList->getLength();
	if( len>0 )
	{
		inh = " INHERITS( ";
		for (i = 0; i < len; ++i)
			inh += independency((DOMElement*)(nodeList->item(i)));
		inh += " )";
	}
	else
	{
		text += "pid  VARCHAR(254)  NOT NULL  REFERENCES PID_CONTENT, ";
		text += "spid  VARCHAR(254), ";
	}

	//
	// field
	//
	std::string col = "";
	nodeList = element->getElementsByTagName(X("field"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        col += field((DOMElement*)(nodeList->item(i)));
		if((i+1)!=len) col += ", ";
    }

	//
	// primarykey
	//
	std::string pk = "";
	nodeList = element->getElementsByTagName(X("primary-key"));
	len = nodeList->getLength();
	if ( len>0 )
	{ 
		pk = ", PRIMARY KEY( ";
		for (i = 0; i < len; ++i)
		{
			pk += primarykey((DOMElement*)(nodeList->item(i)));
		}
		pk += " )";
	}
	col += pk;
	col += " )";

	text += get_table_name(table) + "$$" + col + inh + ";";
	lTableList_.push_back(text);
}

std::string
PSDReader::field (DOMElement* element)
throw(PSDReadException)
{
	std::string text = "";
	std::string tmp = "";
	std::map<const char*, const char*> ::iterator iter;

	text += XMLString::transcode(element->getAttribute(X("name")));
	text += " ";

	tmp = XMLString::transcode(element->getAttribute(X("type")));
	iter = mType_.find( tmp.c_str() );
	text += iter->second;
	text += " ";
	
	tmp = XMLString::transcode(element->getAttribute(X("isnull")));
	if(tmp.compare("no")==0)
		text += "NOT NULL";
	
	return text;
}

std::string
PSDReader::primarykey (DOMElement* element)
throw(PSDReadException)
{
	unsigned int i = 0;
	unsigned int len = 0;
	std::string text = "";
	DOMNodeList* nodeList;

	nodeList = element->getElementsByTagName(X("key"));
	for (i = 0; i < len; ++i)
	{
		text += key((DOMElement*)(nodeList->item(i)));
		if((i+1)!=len) text += ", ";
	}

	return text;
}

std::string
PSDReader::key (DOMElement* element)
throw(PSDReadException)
{
	std::string text;
	text = XMLString::transcode(element->getAttribute(X("name")));

	return text;
}

std::string
PSDReader::independency (DOMElement* element)
throw(PSDReadException)
{
	unsigned int i = 0;
	unsigned int len = 0;
	std::string text = "";
	DOMNodeList* nodeList;

	nodeList = element->getElementsByTagName(X("ancestor"));
	for (i = 0; i < len; ++i)
	{
		text += ancestor((DOMElement*)(nodeList->item(i)));
		if((i+1)!=len) text += ", ";
	}

	return text;
}

std::string
PSDReader::ancestor (DOMElement* element)
throw(PSDReadException)
{
	std::string text;
	text = XMLString::transcode(element->getAttribute(X("id")));

	return get_table_name(text);
}

std::list<std::string>
PSDReader::readPSD(std::string descriptor, std::string path)
throw(PSDReadException)
{
	path_ = path;

	//
	// parse the corba persistence descriptor file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(descriptor.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw PSDReadException();
	}
	psd_document_ = parser.getDocument();

	// handle corbapersistence
	corbapersistence(psd_document_->getDocumentElement());

	return lTableList_;
}

std::string
PSDReader::getDBConn()
{
	return strConn_;
}

/*
bool 
TableBuilder::build( std::string descriptor, std::string path )
{
	QDDatabase pdb;
	PSDReader psd_reader;
	std::string strAll, strName, strSql, strConn;
	std::basic_string <char>::size_type idxBegin;

	// get the sql sentences to create tables
	std::list<std::string> lTable(psd_reader.readPSD( path+descriptor, path ));
	std::list<std::string>::iterator iter;
	
	// get database connection string
	strConn = psd_reader.getDBConn();
	
	// connect to database
	pdb.Init();
	if(!pdb.DriverConnect(strConn.c_str()))
	{
		std::cout << "Failed to connect to database!" << std::endl;
		return false;
	}

	for(iter=lTable.begin(); iter!=lTable.end(); iter++)
	{
		strAll = *iter;
		idxBegin = strAll.find("$$");
		
		strName.substr(0, idxBegin);
		strSql.substr(idxBegin+2, strAll.length()-idxBegin-1);
		
		// check whether table has been already created
		if(!pdb.IsTableExist(strName.c_str()))
			// if not, create it!
			if(!pdb.ExecuteSQL(strSql.c_str()))
			{
				std::cout << "Failed to build table in database!" << std::endl;
				return false;
			}
	}
	
	//close database
	pdb.close();

	return true;
}
*/

}
