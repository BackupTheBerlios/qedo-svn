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

#include "CCDReader4qxml.h"
#include "CCDStruc4qxml.h"
//#include "CCDReader.h"
#include "Output.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


static char rcsid[] UNUSED = "$Id: CCDReader4qxml.cpp,v 1.17 2005/04/13 09:30:19 heini Exp $";


namespace Qedo {


CCDReader4qxml::CCDReader4qxml()
:  ccd_document_(0), package_(0)
{
	

}


CCDReader4qxml::CCDReader4qxml( std::string package, std::string path )
:  ccd_document_(0)
{
	package_ = new Package(package);
	path_ = path;
	data_ = new CCDData() ;
}


CCDReader4qxml::~CCDReader4qxml()
{
	delete package_;
}

void 
CCDReader4qxml::componentfeatures (DOMElement* element)
throw(CCDReadException)
{
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			//
			// ports
			//
			if (!XMLString::compareString(child->getNodeName(), X("ports")))
			{
				ports((DOMElement*)child);
			}

		}

        // get next child
		child = child->getNextSibling();
    }

}

void
CCDReader4qxml::ports (DOMElement* element)
throw(CCDReadException)
{
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			//
			// source
			//
			if (!XMLString::compareString(child->getNodeName(), X("source")))
			{
				 source((DOMElement*)child);
			}
			//
			// sink
			//
			else if (!XMLString::compareString(child->getNodeName(), X("sink")))
			{
				 sink( (DOMElement*) child);
			}

			//
			// uses
			//
			else if (!XMLString::compareString(child->getNodeName(), X("uses")))
			{
				 uses( (DOMElement*) child);
			}

			//
			// provides
			//
			else if (!XMLString::compareString(child->getNodeName(), X("provides")))
			{
				 provides( (DOMElement*) child);
			}
			
			//
			// emits
			//
			else if (!XMLString::compareString(child->getNodeName(), X("emits")))
			{
				 emits( (DOMElement*) child);
			}
			
			//
			// publishes
			//
			else if (!XMLString::compareString(child->getNodeName(), X("publishes")))
			{
				 publishes( (DOMElement*) child);
			}

			//
			// consumes
			//
			else if (!XMLString::compareString(child->getNodeName(), X("consumes")))
			{
				 consumes( (DOMElement*) child);
			}


		}

        // get next child
		child = child->getNextSibling();
    }

}

void CCDReader4qxml::source (DOMElement* element)
throw(CCDReadException)
{
	CCDPort port;
	port.type=sourceport;
	port.identifier= Qedo::transcode(element->getAttribute(X("source_name")));
	
	data_->ports.push_back(port);
	
}

void CCDReader4qxml::sink (DOMElement* element)
throw(CCDReadException)
{
	CCDPort port;
	port.type=sinkport;
	port.identifier= Qedo::transcode(element->getAttribute(X("sink_name")));
	
	data_->ports.push_back(port);
	
}

void CCDReader4qxml::uses (DOMElement* element)
throw(CCDReadException)
{
	CCDPort port;
	port.type=usesport;
	port.identifier= Qedo::transcode(element->getAttribute(X("usesname")));
	
	data_->ports.push_back(port);
	
}

void CCDReader4qxml::provides (DOMElement* element)
throw(CCDReadException)
{
	CCDPort port;
	port.type=providesport;
	port.identifier= Qedo::transcode(element->getAttribute(X("providesname")));
	
	data_->ports.push_back(port);
	
}

void CCDReader4qxml::consumes (DOMElement* element)
throw(CCDReadException)
{
	CCDPort port;
	port.type=consumesport;
	port.identifier= Qedo::transcode(element->getAttribute(X("consumesname")));
	
	data_->ports.push_back(port);
	
}

void CCDReader4qxml::publishes (DOMElement* element)
throw(CCDReadException)
{
	CCDPort port;
	port.type=publishesport;
	port.identifier= Qedo::transcode(element->getAttribute(X("publishesname")));
	
	data_->ports.push_back(port);
	
}

void CCDReader4qxml::emits (DOMElement* element)
throw(CCDReadException)
{
	CCDPort port;
	port.type=emitsport;
	port.identifier= Qedo::transcode(element->getAttribute(X("emitsname")));
	
	data_->ports.push_back(port);
	
}

void
CCDReader4qxml::softpkg (DOMElement* element)
throw(CCDReadException)
{
	if ( !package_ ) abort();
	std::string element_name;
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// componentfeatures
			//
			if (element_name == "componentfeatures")
			{
				componentfeatures((DOMElement*)child);
			}

			
		}

		// get next child
		child = child->getNextSibling();
    }

		
}

CCDData 
CCDReader4qxml::getCCD()
throw(CCDReadException)
{
	//
	// find and extract the software package descriptor
	//
    std::string ccdfile_name = package_->getFileNameWithSuffix( ".ccd" );
	std::string ccdfile = path_ + getFileName( ccdfile_name );
    if ( ccdfile_name == std::string( "" ) )
	{
		NORMAL_ERR( "CCDReader4qxml: missing a ccd file!" );
        throw CCDReadException();
	}
    if (package_->extractFile(ccdfile_name, ccdfile) != 0)
	{
		NORMAL_ERR2( "CCDReader4qxml: error during extracting the descriptor file", ccdfile_name );
		throw CCDReadException();
	}

	//
	// parse the software package descriptor file
    //
	DOMXMLParser parser;
    if ( parser.parse( const_cast<char*>(ccdfile.c_str()) ) != 0 ) 
	{
		NORMAL_ERR2( "CCDReader: error during parsing ", ccdfile );
        throw CCDReadException();
	}
	ccd_document_ = parser.getDocument();

	// handle softpkg
	softpkg(ccd_document_->getDocumentElement());
	return *data_;

}


}