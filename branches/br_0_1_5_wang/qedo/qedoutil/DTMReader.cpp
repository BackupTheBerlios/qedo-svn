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
#include "DTMReader.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/framework/URLInputSource.hpp>


static char rcsid[] UNUSED = "$Id: DTMReader.cpp,v 1.1.4.3 2004/01/28 16:59:11 hao Exp $";


namespace Qedo {


DTMReader::DTMReader()
{
}

DTMReader::~DTMReader()
{
	if(!vCorba_.empty())
		vCorba_.clear();
	if(!vCpp_.empty())
		vCpp_.clear();
	if(!vCppNative_.empty())
		vCppNative_.clear();
	if(!vSql_.empty())
		vSql_.clear();
}

void
DTMReader::connection (DOMElement* element)
	throw(DTMReadException)
{
	strConn_ = "";
	DOMElement* child_element;

	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			child_element = (DOMElement*)child;

			if ( !XMLString::compareString(child->getNodeName(), X("param")) )
			{
				strConn_ += XMLString::transcode(child_element->getAttribute(X("name")));
				strConn_ += "=";
				strConn_ += XMLString::transcode(child_element->getAttribute(X("value")));
				strConn_ += ";";
			}
		}
		// get next child
		child = child->getNextSibling();
    }
}

void
DTMReader::type_mapping(DOMElement* element)
	throw(DTMReadException)
{
	std::string text = "";
	DOMNodeList* nodeList;

	nodeList = element->getElementsByTagName(X("mapping"));
	for( unsigned int i = 0; i < nodeList->getLength(); i++ )
		mapping((DOMElement*)(nodeList->item(i)));
}

void
DTMReader::mapping(DOMElement* element)
	throw(DTMReadException)
{
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			// handle corba-type
			if ( !XMLString::compareString(child->getNodeName(), X("corba-type")) )
				vCorba_.push_back(get_value((DOMElement*)child));

			// handle cpp-type
			else if ( !XMLString::compareString(child->getNodeName(), X("cpp-type")) )
				vCpp_.push_back(get_value((DOMElement*)child));

			// handle cpp-native-type
			else if ( !XMLString::compareString(child->getNodeName(), X("cpp-native-type")) )
				vCppNative_.push_back(get_value((DOMElement*)child));

			// handle sql-type
			else if ( !XMLString::compareString(child->getNodeName(), X("sql-type")) )
				vSql_.push_back(get_value((DOMElement*)child));
		}

        // get next child
		child = child->getNextSibling();
    }
}

std::string
DTMReader::get_value(DOMElement* element)
	throw(DTMReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
		text = XMLString::transcode(node->getNodeValue());

	return text;
}

std::string
DTMReader::readConnection(std::string descriptor)
	throw(DTMReadException)
{
	DOMXMLParser parser;
	
    if ( parser.parse( ((char*)descriptor.c_str()) ) != 0 )
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw DTMReadException();
	}

	dtm_document_ = parser.getDocument();

	DOMNode* child = dtm_document_->getDocumentElement()->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
			// handle connection
			if ( !XMLString::compareString(child->getNodeName(), X("connection")) )
				connection((DOMElement*)child);
		
        // get next child
		child = child->getNextSibling();
    }

	return strConn_;
}

void
DTMReader::readDatatype(std::string descriptor)
	throw(DTMReadException)
{
	DOMXMLParser parser;
	
    if ( parser.parse( ((char*)descriptor.c_str()) ) != 0 )
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw DTMReadException();
	}

	dtm_document_ = parser.getDocument();

	DOMNode* child = dtm_document_->getDocumentElement()->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
			// handle type_mapping
			if ( !XMLString::compareString(child->getNodeName(), X("type-mapping")) )
				type_mapping((DOMElement*)child);

        // get next child
		child = child->getNextSibling();
    }
}

void
DTMReader::getDatatypeMap(std::map<const char*, const char*> mType, std::string dt1, std::string dt2)
	throw(DTMReadException)
{
	if(dt1.compare("corba-type")==0 && dt2.compare("sql-type")==0)
	{
		for(unsigned int i=0; i<vCorba_.size(); i++)
		{
			typedef std::pair <const char*, const char*> Type_Pair;
			std::string strA = "", strB="";
			strA += dt1.at(i);
			strB += dt2.at(i);
			mType.insert( Type_Pair(strA.c_str(), strB.c_str()) );
		}
	}
	else
		throw DTMReadException();
}

}
