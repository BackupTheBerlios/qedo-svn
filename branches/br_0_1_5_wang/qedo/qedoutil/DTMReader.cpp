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


static char rcsid[] UNUSED = "$Id: DTMReader.cpp,v 1.1.4.1 2003/12/19 16:23:18 hao Exp $";


namespace Qedo {


DTMReader::DTMReader()
{
}

DTMReader::~DTMReader()
{
	if(!m_vCorba.empty())
		m_vCorba.clear();
	if(!m_vCpp.empty())
		m_vCpp.clear();
	if(!m_vCppNative.empty())
		m_vCppNative.clear();
	if(!m_vSql.empty())
		m_vSql.clear();
}

void
DTMReader::qedo_datatype_map(DOMElement* element, std::string dbname)
throw(DTMReadException)
{
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
			// handle type_mapping
			if ( XMLString::compareString(child->getNodeName(), X("type-mapping")) )
				// find appropriate database
				if(pre_type_mapping((DOMElement*)child, dbname))
				{
					type_mapping((DOMElement*)child);
					break;
				}

        // get next child
		child = child->getNextSibling();
    }
}

bool
DTMReader::pre_type_mapping(DOMElement* element, std::string dbname)
throw(DTMReadException)
{
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			// find appropriate database name
			if ( XMLString::compareString(child->getNodeName(), X("name")) )
			{
				if(dbname.compare(get_value((DOMElement*)child))==0)
					return true;
			}
		}

        // get next child
		child = child->getNextSibling();
    }

	return false;
}

void
DTMReader::type_mapping(DOMElement* element)
throw(DTMReadException)
{
	unsigned int i = 0;
	unsigned int len = 0;
	std::string text = "";
	DOMNodeList* nodeList;

	nodeList = element->getElementsByTagName(X("mapping"));
	for (i = 0; i < len; ++i)
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
			if ( XMLString::compareString(child->getNodeName(), X("corba-type")) )
				m_vCorba.push_back(get_value((DOMElement*)child));

			// handle cpp-type
			else if ( XMLString::compareString(child->getNodeName(), X("cpp-type")) )
				m_vCpp.push_back(get_value((DOMElement*)child));

			// handle cpp-native-type
			else if ( XMLString::compareString(child->getNodeName(), X("cpp-native-type")) )
				m_vCppNative.push_back(get_value((DOMElement*)child));

			// handle sql-type
			else if ( XMLString::compareString(child->getNodeName(), X("sql-type")) )
				m_vSql.push_back(get_value((DOMElement*)child));
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

void
DTMReader::readDTM(std::string descriptor, std::string path, std::string dbname)
throw(DTMReadException)
{
	path_ = path;

	//
	// parse the qedo datatype map file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(descriptor.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw DTMReadException();
	}
	dtm_document_ = parser.getDocument();

	// handle qedo-datatype-map
	qedo_datatype_map(dtm_document_->getDocumentElement(), dbname);
}

void
DTMReader::getDatatypeMap(std::map<const char*, const char*> mType, std::string dt1, std::string dt2)
throw(DTMReadException)
{
	if(dt1.compare("corba-type")==0 && dt2.compare("sql-type")==0)
	{
		for(unsigned int i=0; i<m_vCorba.size(); i++)
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
