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
#include "Output.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


static char rcsid[] UNUSED = "$Id: CCDReader.cpp,v 1.7 2003/11/14 16:48:16 boehme Exp $";


namespace Qedo {


CCDReader::CCDReader(std::string descriptor, std::string path)
{
	descriptor_ = descriptor;
	path_ = path;
}


CCDReader::~CCDReader()
{
}


void
CCDReader::componentkind (DOMElement* element)
throw(CCDReadException)
{
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			//
			// service
			//
			if (!XMLString::compareString(child->getNodeName(), X("service")))
			{
				service((DOMElement*)child);
			}

			//
			// session
			//
			else if (!XMLString::compareString(child->getNodeName(), X("session")))
			{
				session((DOMElement*)child);
			}

			//
			// process
			//
			else if (!XMLString::compareString(child->getNodeName(), X("process")))
			{
				process( (DOMElement*)child );
			}

			//
			// entity
			//
			else if (!XMLString::compareString(child->getNodeName(), X("entity")))
			{
				entity( (DOMElement*)child );
			}

			//
			// unclassified
			//
			else if (!XMLString::compareString(child->getNodeName(), X("unclassified")))
			{
				unclassified( (DOMElement*)child );
			}

			//
			// containerextension
			//
			else if (!XMLString::compareString(child->getNodeName(), X("containerextension")))
			{
				containerextension( (DOMElement*)child );
			}
		}

        // get next child
		child = child->getNextSibling();
    }
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
				data_->home_repid = homerepid((DOMElement*)child);
			}

			//
			// homefeatures
			//
			else if (!XMLString::compareString(child->getNodeName(), X("homefeatures")))
			{
				
			}

			//
			// componentkind
			//
			else if (!XMLString::compareString(child->getNodeName(), X("componentkind")))
			{
				componentkind( (DOMElement*)child );
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
	return Qedo::transcode(element->getFirstChild()->getNodeValue());
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
				std::string cfile_name = fileinarchive((DOMElement*)(child));
				cfile = path_ + getFileName( cfile );
					
				//
				// extract the file
				//
				if (package_->extractFile(cfile_name, cfile) != 0)
				{
					std::cerr << "Error during extracting file " << cfile_name << std::endl;
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
	return Qedo::transcode(element->getAttribute(X("name")));
}


void 
CCDReader::homefeatures (DOMElement* element)
throw(CCDReadException)
{
	if (data_->home_repid == Qedo::transcode(element->getAttribute(X("repid"))))
	{
		data_->home_name = Qedo::transcode(element->getAttribute(X("name")));
	}
}


std::string 
CCDReader::homerepid (DOMElement* element)
throw(CCDReadException)
{
	return Qedo::transcode(element->getAttribute(X("repid")));
}


std::string
CCDReader::link (DOMElement* element)
throw(CCDReadException)
{
    XMLURL uri(element->getAttribute(X("href")));
    std::string name = Qedo::transcode(uri.getPath());
    std::string::size_type pos = name.find_last_of("/");
    if (pos != std::string::npos)
    {
        name.erase(0, pos + 1);
    }
    
    std::string fileName = path_ + name;
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
CCDReader::service (DOMElement* element)
throw(CCDReadException)
{
	data_->kind = "SERVICE";
}


void 
CCDReader::session (DOMElement* element)
throw(CCDReadException)
{
	data_->kind = "SESSION";
}


void 
CCDReader::process (DOMElement* element)
throw(CCDReadException)
{
	data_->kind = "PROCESS";
}


void 
CCDReader::entity (DOMElement* element)
throw(CCDReadException)
{
	data_->kind = "ENTITY";
}


void 
CCDReader::unclassified (DOMElement* element)
throw(CCDReadException)
{
	data_->kind = "UNCLASSIFIED";
}


void 
CCDReader::containerextension (DOMElement* element)
throw(CCDReadException)
{
	data_->kind = "EXTENSION";
}


void 
CCDReader::readCCD(CompositionData* data, Package* package)
throw(CCDReadException)
{
	data_ = data;
	package_ = package;

	//
	// parse the corba component descriptor file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(descriptor_.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		NORMAL_ERR( "CCDReader: error during XML parsing" );
        throw CCDReadException();
	}
	ccd_document_ = parser.getDocument();

	// handle corbacomponent
	corbacomponent(ccd_document_->getDocumentElement());
}


}

