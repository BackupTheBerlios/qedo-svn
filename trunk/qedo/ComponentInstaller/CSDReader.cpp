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

#include "CSDReader.h"
#include "CCDReader.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


static char rcsid[] UNUSED = "$Id: CSDReader.cpp,v 1.1 2003/08/27 06:47:43 neubauer Exp $";


namespace Qedo {


CSDReader::CSDReader()
{
}


CSDReader::~CSDReader()
{
}


void
CSDReader::author (DOMElement* element)
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

	// company
	nodeList = element->getElementsByTagName(X("company"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        text.append(company((DOMElement*)(nodeList->item(i))));
		text.append(", ");
    }

	// webpage
	nodeList = element->getElementsByTagName(X("webpage"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        text.append(webpage((DOMElement*)(nodeList->item(i))));
    }

	std::cerr << "<author> " << text << std::endl;
}


void
CSDReader::code (DOMElement* element)
throw(CSDReadException)
{
	std::string type = XMLString::transcode(element->getAttribute(X("type")));
	std::string file_name;
	std::string element_name;
	std::string entry;
	std::string use;

	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// codebase
			//
			if (element_name == "codebase")
			{
				// TODO
			}

			//
			// fileinarchive
			//
			else if (element_name == "fileinarchive")
			{
				file_name = fileinarchive((DOMElement*)(child));
			}

			//
			// link
			//
			else if (element_name == "link")
			{
				file_name = link((DOMElement*)(child));
			}

			//
			// entrypoint
			//
			else if (element_name == "entrypoint")
			{
				entry = entrypoint((DOMElement*)(child));
			}

			//
			// usage
			//
			else if (element_name == "usage")
			{
				use = usage((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	//
	// dynamic library
	//
	if (type == "DLL")
	{
		if (use == "servant")
		{
			component_implementation_->servant_module_ = file_name;
			component_implementation_->servant_entry_point_ = entry;
		}
		else 
		{
			component_implementation_->executor_module_ = file_name;
			component_implementation_->executor_entry_point_ = entry;
		}
    }

	//
	// executable
	//
	else if (type == "Executable")
	{
		// todo
    }

	//
	// artifact
	//
	else if (type == "Artifact")
	{
		component_implementation_->artifacts_.push_back( file_name );
    }
}


std::string
CSDReader::name (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}
    return text;
}


std::string
CSDReader::company (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}
    return text;
}


std::string
CSDReader::entrypoint (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}
    return text;
}


void
CSDReader::dependency (DOMElement* element)
throw(CSDReadException)
{
    std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// softpkgref
			//
			if (element_name == "softpkgref")
			{
				// TODO
			}

			//
			// codebase
			//
			else if (element_name == "codebase")
			{
				// todo
			}

			//
			// fileinarchive
			//
			else if (element_name == "fileinarchive")
			{
				fileinarchive((DOMElement*)(child));
			}

			//
			// localfile
			//
			else if (element_name == "localfile")
			{
				// todo
			}

			//
			// name
			//
			else if (element_name == "name")
			{
				name((DOMElement*)child);
			}

			//
			// valuetypefactory
			//
			else if (element_name == "valuetypefactory")
			{
				valuetypefactory((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}
}


std::string
CSDReader::description (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}
	std::cerr << "<description> " << text << std::endl;
    return text;
}


std::string 
CSDReader::descriptor (DOMElement* element)
throw(CSDReadException)
{
	std::string element_name;
    std::string cfile;
    DOMNode* child = element->getFirstChild();
    while (child != 0)
    {
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// link
			//
			if (element_name == "link")
			{
				cfile = link((DOMElement*)(child));
			}

			//
			// fileinarchive
			//
			else if (element_name == "fileinarchive")
			{
				cfile = fileinarchive((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

    return cfile;
}


void
CSDReader::extension(DOMElement* element)
throw(CSDReadException)
{
	// TODO
}


std::string
CSDReader::fileinarchive(DOMElement* element)
throw(CSDReadException)
{
	std::string file_name = XMLString::transcode(element->getAttribute(X("name")));

	//
	// extract the file
	//
	if (component_implementation_->package_->extractFile(file_name, component_implementation_->build_path_ + file_name) != 0)
	{
		std::cerr << "Error during extracting file " << file_name << std::endl;
		throw CSDReadException();
	}

	return component_implementation_->build_path_ + file_name;
}


void
CSDReader::idl (DOMElement* element)
throw(CSDReadException)
{
	std::string element_name;
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// link
			//
			if (element_name == "link")
			{
				component_implementation_->idl_file_ = link((DOMElement*)(child));
			}

			//
			// fileinarchive
			//
			if (element_name == "fileinarchive")
			{
				component_implementation_->idl_file_ = fileinarchive((DOMElement*)(child));
				if(component_implementation_->idl_file_ == "")
				{
					std::cerr << "Missing idl file name for " << component_implementation_->uuid_ << std::endl;
					throw CSDReadException();
				}
			}

			//
			// repository
			//
			if (element_name == "repository")
			{
				// TODO
			}
		}

		// get next child
		child = child->getNextSibling();
    }
}


void
CSDReader::implementation (DOMElement* element)
throw(CSDReadException)
{
	DOMNodeList* nodeList;
	unsigned int len = 0;
	unsigned int i = 0;

	//
	// dependency
	//
	nodeList = element->getElementsByTagName(X("dependency"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        dependency((DOMElement*)(nodeList->item(i)));
    }

	//
	// descriptor
	//
	nodeList = element->getElementsByTagName(X("descriptor"));
	len = nodeList->getLength();
    if(len == 1)
    {
        ccd_file_ = descriptor((DOMElement*)(nodeList->item(0)));
    }
	else if(len > 1)
	{
		std::cerr << "..... multiple descriptors" << std::endl;
	}

	//
	// code
	//
	nodeList = element->getElementsByTagName(X("code"));
	len = nodeList->getLength();
	if(len == 0)
	{
		std::cerr << "Missing code for " << component_implementation_->uuid_ << std::endl;
		throw CSDReadException();
	}
    for (i = 0; i < len; ++i)
    {
        code((DOMElement*)(nodeList->item(i)));
    }

	//
	// os
	//
	nodeList = element->getElementsByTagName(X("os"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        os((DOMElement*)(nodeList->item(i)));
    }

	// more todo
}


std::string
CSDReader::license (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}

	if(text == "")
	{
		text = "for license see: ";
		text.append(XMLString::transcode(element->getAttribute(X("href"))));
	}

	std::cerr << "<license> " << text << std::endl;
	return text;
}


std::string
CSDReader::link (DOMElement* element)
throw(CSDReadException)
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
        throw CSDReadException();
    }
        
	std::ofstream aFile;
	aFile.open(fileName.c_str(), std::ios::binary|std::ios::app);
	if (!aFile)
	{
		std::cerr << "Cannot open file " << fileName << std::endl;
		throw CSDReadException();
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


std::string
CSDReader::os (DOMElement* element)
throw(CSDReadException)
{
	return XMLString::transcode(element->getAttribute(X("name")));
}


void
CSDReader::pkgtype (DOMElement* element)
throw(CSDReadException)
{
	// TODO
}


void
CSDReader::propertyfile (DOMElement* element)
throw(CSDReadException)
{
    DOMNodeList* nodeList;
	unsigned int len = 0;
	unsigned int i = 0;

	//
	// fileinarchive
	//
	nodeList = element->getElementsByTagName(X("fileinarchive"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        fileinarchive((DOMElement*)(nodeList->item(i)));
    }

	//
	// link
	//
	nodeList = element->getElementsByTagName(X("link"));
	len = nodeList->getLength();
    for (i = 0; i < len; ++i)
    {
        link((DOMElement*)(nodeList->item(i)));
    }
}


std::string
CSDReader::title (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}
	std::cerr << "<title> " << text << std::endl;
    return text;
}


void
CSDReader::softpkg (DOMElement* element)
throw(CSDReadException)
{
	std::string element_name;
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// title
			//
			if (element_name == "title")
			{
				title((DOMElement*)child);
			}

			//
			// pkgtype
			//
			else if (element_name == "pkgtype")
			{
				pkgtype((DOMElement*)child);
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
				author((DOMElement*)child);
			}

			//
			// description
			//
			else if (element_name == "description")
			{
				description((DOMElement*)child);
			}

			//
			// license
			//
			else if (element_name == "license")
			{
				license((DOMElement*)child);
			}

			//
			// idl
			//
			else if (element_name == "idl")
			{
				idl((DOMElement*)child);
			}

			//
			// propertyfile
			//
			else if (element_name == "propertyfile")
			{
				propertyfile((DOMElement*)child);
			}

			//
			// dependency
			//
			else if (element_name == "dependency")
			{
				dependency((DOMElement*)child);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	DOMNodeList* nodeList;
	DOMElement* elem;
	unsigned int len = 0;
	unsigned int i = 0;
	std::string uuid = component_implementation_->uuid_;

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
		std::cerr << "Implementation for " << uuid << " missing!" << std::endl;
		throw CSDReadException();
	}

    //
	// corba component descriptor
	//
    if (ccd_file_ == "")
    {
		nodeList = element->getElementsByTagName(X("descriptor"));
		len = nodeList->getLength();
		if(len == 1)
		{
			ccd_file_ = descriptor((DOMElement*)(nodeList->item(0)));
		}
		else if(len > 1)
		{
			std::cerr << "ComponentImplementation : multiple descriptor elements!" << std::endl;
		}

		if (ccd_file_ == "")
        {
			std::cerr << "ComponentImplementation : missing component descriptor for " << uuid << std::endl;
	        throw CSDReadException();
        }
    }
	//
	// parse the corba component descriptor file
    //
	CCDReader reader;
	reader.readCCD( ccd_file_, component_implementation_ );
}


std::string
CSDReader::usage (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}
    return text;
}


void
CSDReader::valuetypefactory (DOMElement* element)
throw(CSDReadException)
{
	std::string element_name;
	ValuetypeData data;
	data.repid = XMLString::transcode(element->getAttribute(X("repid")));
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// codebase
			//
			if (element_name == "codebase")
			{
				// todo
			}

			//
			// fileinarchive
			//
			if (element_name == "fileinarchive")
			{
				data.file_name = fileinarchive((DOMElement*)(child));
			}

			//
			// link
			//
			if (element_name == "link")
			{
				data.file_name = link((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	std::cerr << "<valuetypefactory> " << data.repid << std::endl;
	component_implementation_->valuetypes_.push_back(data);
}


std::string
CSDReader::webpage (DOMElement* element)
throw(CSDReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
	}
    return text;
}


void 
CSDReader::readCSD(std::string descriptor, ComponentImplementation* impl)
throw(CSDReadException)
{
	component_implementation_ = impl;

	//
	// parse the software package descriptor file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(descriptor.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw CSDReadException();
	}
	csd_document_ = parser.getDocument();

	// handle softpkg
	softpkg(csd_document_->getDocumentElement());
}


}

