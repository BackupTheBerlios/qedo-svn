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


static char rcsid[] UNUSED = "$Id: CSDReader.cpp,v 1.3 2003/09/05 12:55:18 neubauer Exp $";


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

	std::cerr << ".......... <author> " << text << std::endl;
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
				file_name = fileinarchive((DOMElement*)child).file;
			}

			//
			// link
			//
			else if (element_name == "link")
			{
				file_name = link((DOMElement*)child).file;
			}

			//
			// entrypoint
			//
			else if (element_name == "entrypoint")
			{
				entry = entrypoint((DOMElement*)child);
			}

			//
			// usage
			//
			else if (element_name == "usage")
			{
				use = usage((DOMElement*)child);
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
			data_->servant_module = file_name;
			data_->servant_entry_point = entry;
		}
		else 
		{
			data_->executor_module = file_name;
			data_->executor_entry_point = entry;
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
		data_->artifacts.push_back( file_name );
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
				fileinarchive((DOMElement*)child);
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
	std::cerr << ".......... <description> " << text << std::endl;
    return text;
}


std::string 
CSDReader::descriptor (DOMElement* element)
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
				return link((DOMElement*)child).file;
			}

			//
			// fileinarchive
			//
			else if (element_name == "fileinarchive")
			{
				return fileinarchive((DOMElement*)child).file;
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	throw CSDReadException();
}


void
CSDReader::extension(DOMElement* element)
throw(CSDReadException)
{
	// TODO
}


LocationData
CSDReader::fileinarchive(DOMElement* element)
throw(CSDReadException)
{
	LocationData data;
	data.uri = "file://";
	std::string file_name = XMLString::transcode(element->getAttribute(X("name")));
	data.uri.append(path_ + file_name);
	data.file = path_ + file_name;

	//
	// extract the file
	//
	if (package_->extractFile(file_name, path_ + file_name) != 0)
	{
		std::cerr << "Error during extracting file " << file_name << std::endl;
		throw CSDReadException();
	}

	return data;
}


void
CSDReader::idl (DOMElement* element)
throw(CSDReadException)
{
	std::string element_name;
	IDLData data;
	data_->repid = XMLString::transcode(element->getAttribute(X("id")));
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
				data.kind = LINK;
				data.location = link((DOMElement*)child);
				data_->idl = data;
			}

			//
			// fileinarchive
			//
			if (element_name == "fileinarchive")
			{
				data.kind = FILEINARCHIVE;
				data.location = fileinarchive((DOMElement*)child);
				data_->idl = data;
			}

			//
			// repository
			//
			if (element_name == "repository")
			{
				// todo
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
		std::cerr << ".......... multiple descriptors" << std::endl;
	}

	//
	// code
	//
	nodeList = element->getElementsByTagName(X("code"));
	len = nodeList->getLength();
	if(len == 0)
	{
		std::cerr << "missing code for " << data_->uuid << std::endl;
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

	std::string ref = XMLString::transcode(element->getAttribute(X("href")));
	if(ref != "")
	{
		if(text != "")
		{
			text.append("\n");
		}
		text.append("for license see : ");
		text.append(ref);
	}

	std::cerr << ".......... <license> " << text << std::endl;
	return text;
}


LocationData
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
    
	std::string fileName = path_ + name;
	LocationData data;
	data.uri = XMLString::transcode(element->getAttribute(X("href")));
	data.file = fileName;

	//
	// get file
	//
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

    return data;
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
	std::cerr << ".......... <title> " << text << std::endl;
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
	std::string uuid = data_->uuid;

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
	reader.readCCD( ccd_file_, data_, package_, path_ );
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
				data.location = fileinarchive((DOMElement*)child);
			}

			//
			// link
			//
			if (element_name == "link")
			{
				data.location = link((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	std::cerr << ".......... <valuetypefactory> " << data.repid << std::endl;
	data_->valuetypes.push_back(data);
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
CSDReader::readCSD(std::string package, ComponentImplementationData* data, std::string path)
throw(CSDReadException)
{
	data_ = data;
	path_ = path;
	package_ = new Package(package);

	//
	// find and extract the software package descriptor
	//
    std::string csdfile = package_->getFileNameWithSuffix( ".csd" );
    if ( csdfile == std::string( "" ) )
	{
		std::cerr << ".......... missing a csd file!" << std::endl;
        throw CSDReadException();
	}
    if (package_->extractFile(csdfile, path_ + csdfile) != 0)
	{
		std::cerr << ".......... error during extracting the descriptor file" << std::endl;
		throw CSDReadException();
	}
	csdfile = path_ + csdfile;

	//
	// parse the software package descriptor file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(csdfile.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw CSDReadException();
	}
	csd_document_ = parser.getDocument();

	// handle softpkg
	softpkg(csd_document_->getDocumentElement());

	// remove package
	delete package_;
}


}

