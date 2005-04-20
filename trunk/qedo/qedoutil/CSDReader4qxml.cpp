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

#include "CSDReader4qxml.h"
#include "CCDReader.h"
#include "Output.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


static char rcsid[] UNUSED = "$Id: CSDReader4qxml.cpp,v 1.17 2005/04/13 09:30:19 heini Exp $";


namespace Qedo {


CSDReader4qxml::CSDReader4qxml()
:  csd_document_(0), package_(0)
{
	data_ =new CSDData();
}


CSDReader4qxml::CSDReader4qxml( std::string package, std::string path )
:  csd_document_(0)
{
	package_ = new Package(package);
	path_ = path;
	data_=new CSDData();
}


CSDReader4qxml::~CSDReader4qxml()
{
	delete package_;
}


std::string
CSDReader4qxml::author (DOMElement* element)
throw(CSDReadException)
{
    DOMNodeList* nodeList;
	unsigned int len = 0;
	unsigned int i = 0;
	std::string text = "";

	// name
	nodeList = element->getElementsByTagName(X("name"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        text.append(name((DOMElement*)(nodeList->item(i))));
		text.append(", ");
    }

	
	DEBUG_OUT2( "CSDReader4qxml: <author> ", text );
	return text;
}





std::string
CSDReader4qxml::name (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}













Descriptor
CSDReader4qxml::descriptor (DOMElement* element)
throw(CSDReadException)
{
	Descriptor descr;
	descr.type = Qedo::transcode(element->getAttribute(X("type")));
	std::string element_name;
    DOMNode* child = element->getFirstChild();
    while (child != 0)
    {
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// link
			//
			if (element_name == "link")
			{
//				return link((DOMElement*)child).file;
			}

			//
			// fileinarchive
			//
			else if (element_name == "fileinarchive")
			{
				descr.filearchive=fileinarchive((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return descr;
	//throw CSDReadException();
}


std::string
CSDReader4qxml::fileinarchive (DOMElement* element)
throw(CSDReadException)
{
	return Qedo::transcode(element->getAttribute(X("name")));
}



Implementation
CSDReader4qxml::implementation (DOMElement* element)
throw(CSDReadException)
{
	Implementation impl;
	impl.id = Qedo::transcode(element->getAttribute(X("id")));

	std::string element_name;
    DOMNode* child = element->getFirstChild();
    while (child != 0)
    {
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// os
			//
			if (element_name == "os")
			{
				impl.os_name=os((DOMElement*)child);
			}

			//
			// fileinarchive
			//
			else if (element_name == "descriptor")
			{
				impl.descriptor=descriptor((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	//throw CSDReadException();
	return impl;
}



std::string
CSDReader4qxml::os (DOMElement* element)
throw(CSDReadException)
{
	return Qedo::transcode(element->getAttribute(X("name")));
}


std::string
CSDReader4qxml::pkgtype (DOMElement* element)
throw(CSDReadException)
{
	// TODO
	std::string text;
	text="TODO";
	return text;
}





std::string
CSDReader4qxml::title (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
	//DEBUG_OUT2( "CSDReader: <title> ", text );
    return text;
}


void
CSDReader4qxml::softpkg (DOMElement* element)
throw(CSDReadException)
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
			// title
			//
			if (element_name == "title")
			{
				data_->title=title((DOMElement*)child);
			}

			//
			// pkgtype
			//
			else if (element_name == "pkgtype")
			{
//				data_->pkgtype=pkgtype((DOMElement*)child);
			}

			//
			// repository
			//
			else if (element_name == "repository")
			{
				// TODO
			}

			//
			// author
			//
			else if (element_name == "author")
			{
				data_->author=author((DOMElement*)child);
			}

			//
			// description
			//
			else if (element_name == "description")
			{
//				description((DOMElement*)child);
			}

			else if (element_name == "implementation")
			{
				data_->implementations.push_back(implementation((DOMElement*)child));
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	//DOMNodeList* nodeList;
	//DOMElement* elem;
	//unsigned int len = 0;
	//unsigned int i = 0;
/*	std::string uuid = data_->id;

    //
	// implementation
	//
	nodeList = element->getElementsByTagName(X("implementation"));
	len = nodeList->getLength();
	bool impl_found = false;
    for (i = 0; i < len; ++i)
    {
		elem = (DOMElement*)(nodeList->item(i));
		if (!XMLString::compareString(elem->getAttribute(X("id")), X(uuid.c_str())))
		{
			impl_found = true;
			break;
		}
    }
	if(impl_found)
	{
		implementation(elem);
	}
	else
	{
		NORMAL_ERR3( "CSDReader: implementation for ", uuid, " missing!" );
		throw CSDReadException();
	}

    //
	// corba component descriptor
	//
    if (ccd_file_.empty())
    {
		nodeList = element->getElementsByTagName(X("descriptor"));
		len = nodeList->getLength();
		if(len == 1)
		{
			ccd_file_ = descriptor((DOMElement*)(nodeList->item(0)));
		}
		else if(len > 1)
		{
			NORMAL_ERR( "CSDReader: multiple descriptor elements!" );
		}

		if (ccd_file_.empty())
        {
			NORMAL_ERR2( "CSDReader: missing component descriptor for ", uuid );
	        throw CSDReadException();
        }
    }
	//
	// parse the corba component descriptor file
    //
	CCDReader reader( path_ + ccd_file_, path_ );
//	reader.readCCD( &(data_->component), package_ );
*/
	
}


void
CSDReader4qxml::softpkgref (DOMElement* element)
throw(CSDReadException)
{
	std::string element_name;
	std::string idref;
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// fileinarchive
			//
			if (element_name == "fileinarchive")
			{
				// todo
//				fileinarchive( (DOMElement*)child );
			}

			
			//
			// implref
			//
			else if (element_name == "implref")
			{
//				idref = implref( (DOMElement*)child );
			}
		}

		// get next child
		child = child->getNextSibling();
    }

//	data_->softpkg_dependencies.push_back( idref );
}


std::string
CSDReader4qxml::usage (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}








CSDData 
CSDReader4qxml::getCSD()
throw(CSDReadException)
{
	//
	// find and extract the software package descriptor
	//
    std::string csdfile_name = package_->getFileNameWithSuffix( ".csd" );
	std::string csdfile = path_ + getFileName( csdfile_name );
    if ( csdfile_name == std::string( "" ) )
	{
		NORMAL_ERR( "CSDReader4qxml: missing a csd file!" );
        throw CSDReadException();
	}
    if (package_->extractFile(csdfile_name, csdfile) != 0)
	{
		NORMAL_ERR2( "CSDReader4qxml: error during extracting the descriptor file", csdfile_name );
		throw CSDReadException();
	}

	//
	// parse the software package descriptor file
    //
	DOMXMLParser parser;
    if ( parser.parse( const_cast<char*>(csdfile.c_str()) ) != 0 ) 
	{
		NORMAL_ERR2( "CSDReader: error during parsing ", csdfile );
        throw CSDReadException();
	}
	csd_document_ = parser.getDocument();

	// handle softpkg
	softpkg(csd_document_->getDocumentElement());
	return *data_;

}

/*
std::string 
CSDReader4qxml::getCCD(std::string id)
throw(CSDReadException)
{
	if (!package_) abort();
	//
	// find and extract the software package descriptor
	//
    std::string csdfile_name = package_->getFileNameWithSuffix( ".csd" );
	std::string csdfile = path_ + getFileName( csdfile_name );
    if ( csdfile_name == std::string( "" ) )
	{
		NORMAL_ERR( "CSDReader: missing a csd file!" );
        throw CSDReadException();
	}
    if (package_->extractFile(csdfile_name, csdfile) != 0)
	{
		NORMAL_ERR2( "CSDReader: error during extracting the descriptor file", csdfile_name );
		throw CSDReadException();
	}

	//
	// parse the software package descriptor file
    //
	DOMXMLParser parser;
    if ( parser.parse( const_cast<char*>(csdfile.c_str()) ) != 0 )
	{
		NORMAL_ERR2( "CSDReader: error during parsing ", csdfile );
        throw CSDReadException();
	}

	csd_document_ = parser.getDocument();
	DOMElement* element = csd_document_->getDocumentElement();
	DOMNodeList* nodeList;
	DOMNodeList* nodeList2;
	DOMElement* elem;
	unsigned int len = 0;
	unsigned int len2 = 0;
	unsigned int i = 0;

    //
	// implementation
	//
	nodeList = element->getElementsByTagName(X("implementation"));
	len = nodeList->getLength();
	bool impl_found = false;
    for( i = 0; i < len; ++i )
    {
		elem = (DOMElement*)(nodeList->item(i));
		if (!XMLString::compareString(elem->getAttribute(X("id")), X(id.c_str())))
		{
			impl_found = true;

			//
			// search for descriptor
			//
			nodeList2 = elem->getElementsByTagName(X("descriptor"));
			len2 = nodeList2->getLength();
			if(len2 == 1)
			{
				ccd_file_ = descriptor((DOMElement*)(nodeList2->item(0)));
			}
			else if(len > 1)
			{
				ccd_file_ = descriptor((DOMElement*)(nodeList2->item(0)));
				NORMAL_ERR( "CSDReader: multiple descriptors" );
			}

			break;
		}
    }
	if( !impl_found )
	{
		NORMAL_ERR3( "CSDReader: implementation for ", id, " missing!" );
		throw CSDReadException();
	}

    //
	// corba component descriptor
	//
    if( ccd_file_.empty() )
    {
		nodeList = element->getElementsByTagName(X("descriptor"));
		len = nodeList->getLength();
		if(len == 1)
		{
			ccd_file_ = descriptor((DOMElement*)(nodeList->item(0)));
		}
		else if(len > 1)
		{
			NORMAL_ERR( "CSDReader: multiple descriptor elements!" );
		}

		if (ccd_file_.empty())
        {
			NORMAL_ERR2( "CSDReader: missing component descriptor for ", id );
	        throw CSDReadException();
        }
    }

	return path_ + ccd_file_;
}
*/
}