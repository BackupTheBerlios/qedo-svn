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

#include "CCDReader.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


static char rcsid[] UNUSED = "$Id: CCDReader.cpp,v 1.1 2003/08/27 06:47:43 neubauer Exp $";


namespace Qedo {


CCDReader::CCDReader()
{
}


CCDReader::~CCDReader()
{
}


void
CCDReader::corbacomponent (DOMElement* element)
throw(CCDReadException)
{
    std::string repid_of_home;
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			//
			// homerepid
			//
			if (!XMLString::compareString(child->getNodeName(), X("homerepid")))
			{
				component_implementation_->home_repid_ = homerepid((DOMElement*)child);
			}

			//
			// homefeatures
			//
			else if (!XMLString::compareString(child->getNodeName(), X("homefeatures")))
			{
				
			}
		}

        // get next child
		child = child->getNextSibling();
    }
}


std::string
CCDReader::description (DOMElement* element)
throw(CCDReadException)
{
	return XMLString::transcode(element->getFirstChild()->getNodeValue());
}


std::string 
CCDReader::descriptor (DOMElement* element)
throw(CCDReadException)
{
    std::string cfile;
    DOMNode* child = element->getFirstChild();
    while (child != 0)
    {
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			//
			// link
			//
			if (!XMLString::compareString(child->getNodeName(), X("link")))
			{
				cfile = link((DOMElement*)(child));
			}

			//
			// fileinarchive
			//
			else if (!XMLString::compareString(child->getNodeName(), X("fileinarchive")))
			{
				cfile = fileinarchive((DOMElement*)(child));
					
				//
				// extract the file
				//
				if (component_implementation_->package_->extractFile(cfile, component_implementation_->build_path_ + cfile) != 0)
				{
					std::cerr << "Error during extracting file " << cfile << std::endl;
					throw CCDReadException();
				}
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

    return cfile;
}


void
CCDReader::extension(DOMElement* element)
throw(CCDReadException)
{
	// TODO
}


std::string
CCDReader::fileinarchive(DOMElement* element)
throw(CCDReadException)
{
	return XMLString::transcode(element->getAttribute(X("name")));
}


void 
CCDReader::homefeatures (DOMElement* element)
throw(CCDReadException)
{
	if (component_implementation_->home_repid_ == XMLString::transcode(element->getAttribute(X("repid"))))
	{
		component_implementation_->home_name_ = XMLString::transcode(element->getAttribute(X("name")));
	}
}


std::string 
CCDReader::homerepid (DOMElement* element)
throw(CCDReadException)
{
	return XMLString::transcode(element->getAttribute(X("repid")));
}


std::string
CCDReader::link (DOMElement* element)
throw(CCDReadException)
{
    XMLURL uri(element->getAttribute(X("href")));
    std::string name = XMLString::transcode(uri.getPath());
    std::string::size_type pos = name.find_last_of("/");
    if (pos != std::string::npos)
    {
        name.erase(0, pos + 1);
    }
    
    std::string fileName = component_implementation_->build_path_ + name;
    URLInputSource inputSource(uri);
    BinInputStream* inputStream = inputSource.makeStream();
    if (!inputStream)
    {
        throw CCDReadException();
    }
        
	std::ofstream aFile;
	aFile.open(fileName.c_str(), std::ios::binary|std::ios::app);
	if (!aFile)
	{
		std::cerr << "Cannot open file " << fileName << std::endl;
		throw CCDReadException();
	}
    unsigned char* buf = (unsigned char*)malloc(4096);
    unsigned int len = inputStream->readBytes(buf, 4096);
    while (len)
    {
        aFile.write((const char*)buf, len);
        len = inputStream->readBytes(buf, 4096);
    }
    free(buf);
	aFile.close();

    return name;
}


void 
CCDReader::readCCD(std::string descriptor, ComponentImplementation* impl)
throw(CCDReadException)
{
	component_implementation_ = impl;

	//
	// parse the corba component descriptor file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(descriptor.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw CCDReadException();
	}
	ccd_document_ = parser.getDocument();

	// handle corbacomponent
	corbacomponent(ccd_document_->getDocumentElement());
}


}

