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

#include "CPFReader.h"


namespace Qedo {


CPFReader::CPFReader()
{
}


CPFReader::~CPFReader()
{
}


std::string 
CPFReader::choice (DOMElement* element)
throw(CPFReadException)
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
CPFReader::choices (DOMElement* element)
throw(CPFReadException)
{
	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// choice
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("choice")) ) )
		{
			choice((DOMElement*)(child));
		}

		//
		// range
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("range")) ) )
		{
			range((DOMElement*)(child));
		}

		// next element
		child = child->getNextSibling();
	}
}


std::string 
CPFReader::defaultvalue (DOMElement* element)
throw(CPFReadException)
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
CPFReader::description (DOMElement* element)
throw(CPFReadException)
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


Components::ConfigValues* 
CPFReader::properties (DOMElement* element)
throw(CPFReadException)
{
	Components::ConfigValues* config = new Components::ConfigValues();
	int len = 0;
	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// description
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("description")) ) )
		{
			description((DOMElement*)(child));
		}

		//
		// simple
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("simple")) ) )
		{
			// new config entry
			config->length( ++len );
			( *config )[len - 1] = simple((DOMElement*)(child));
		}

		//
		// sequence
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("sequence")) ) )
		{
			sequence((DOMElement*)(child));
		}

		//
		// struct
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("struct")) ) )
		{
			_struct((DOMElement*)(child));
		}

		//
		// valuetype
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("valuetype")) ) )
		{
			valuetype((DOMElement*)(child));
		}

		// next element
		child = child->getNextSibling();
	}

	return config;
}


void 
CPFReader::range (DOMElement* element)
throw(CPFReadException)
{
	//
	// value
	//
	DOMNodeList* nodeList;
	nodeList = element->getElementsByTagName(X("value"));
	std::string min = value((DOMElement*)(nodeList->item(0)));
	std::string max = value((DOMElement*)(nodeList->item(1)));
}


Components::ConfigValue* 
CPFReader::simple (DOMElement* element)
throw(CPFReadException)
{
	CORBA::Any any;
	std::string val;
	std::string type = XMLString::transcode(element->getAttribute(X("type")));
	std::string name = XMLString::transcode(element->getAttribute(X("name")));

	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// description
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("description")) ) )
		{
			description((DOMElement*)(child));
		}

		//
		// value
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("value")) ) )
		{
			val = value((DOMElement*)(child));
		}

		//
		// choices
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("choices")) ) )
		{
			//val = choices((DOMElement*)(child));
			// what is the meaning???
			throw CPFReadException();
		}

		//
		// defaultvalue
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("defaultvalue")) ) )
		{
			if(val.empty())
			{
				val = defaultvalue((DOMElement*)(child));
			}
		}

		// next element
		child = child->getNextSibling();
	}
			
	if( type == "boolean" )
	{
		CORBA::Boolean v;
		if( val == "true" )
		{
			v = true;
		}
		else
		{
			v = false;
		}
		any <<= CORBA::Any::from_boolean( v );
	}

	if( type == "char" )
	{
		CORBA::Char v = val[0];
		any <<= CORBA::Any::from_char( v );
	}

	if( type == "double" )
	{
		CORBA::Double v = atof( val.c_str() );
		any <<= v;
	}

	if( type == "float" )
	{
		CORBA::Float v = atof( val.c_str() );
		any <<= v;
	}

	if( type == "short" )
	{
		CORBA::Short v = atoi( val.c_str() );
		any <<= v;
	}

	if( type == "long" )
	{
		CORBA::Long v = atol( val.c_str() );
		any <<= v;
	}

	if( type == "objref" )
	{
		// TODO
	}

	if( type == "octet" )
	{
		CORBA::Octet v = val[0];
		any <<= CORBA::Any::from_octet( v );
	}

	if( type == "string" )
	{
		any <<= val.c_str();
	}

	if( type == "ulong" )
	{
		CORBA::ULong v = atol( val.c_str() );
		any <<= v;
	}

	if( type == "ushort" )
	{
		CORBA::UShort v = atoi( val.c_str() );
		any <<= v;
	}

	return new ConfigValue_impl( CORBA::string_dup( name.c_str() ), any );
}


void 
CPFReader::sequence (DOMElement* element)
throw(CPFReadException)
{
	// todo
	std::cerr << "<sequence> not implemented" << std::endl;
}


void 
CPFReader::_struct (DOMElement* element)
throw(CPFReadException)
{
	// todo
	std::cerr << "<struct> not implemented" << std::endl;
}


std::string 
CPFReader::value (DOMElement* element)
throw(CPFReadException)
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
CPFReader::valuetype (DOMElement* element)
throw(CPFReadException)
{
	// todo
	std::cerr << "<valuetype> not implemented" << std::endl;
}


Components::ConfigValues*
CPFReader::readCPF(std::string descriptor)
throw(CPFReadException)
{
	//
	// parse the component property file descriptor file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(descriptor.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw CPFReadException();
	}
	cpf_document_ = parser.getDocument();

	// handle properties
	return properties(cpf_document_->getDocumentElement());
}


}

