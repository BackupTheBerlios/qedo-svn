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
#include "Output.h"


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
		text = Qedo::transcode(node->getNodeValue());
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


Components::ConfigValue* 
CPFReader::configuration (DOMElement* element)
throw(CPFReadException)
{
	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// simple
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("simple")) ) )
		{
			return simple((DOMElement*)child);
		}

		// next element
		child = child->getNextSibling();
	}

	return 0;
}


std::string 
CPFReader::defaultvalue (DOMElement* element)
throw(CPFReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
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
		text = Qedo::transcode(node->getNodeValue());
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
	std::string type = Qedo::transcode(element->getAttribute(X("type")));
	std::string name = Qedo::transcode(element->getAttribute(X("name")));

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
		text = Qedo::transcode(node->getNodeValue());
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
		NORMAL_ERR2( "CPFReader: error during XML parsing of ", descriptor );
        throw CPFReadException();
	}
	cpf_document_ = parser.getDocument();

	// handle properties
	return properties(cpf_document_->getDocumentElement());
}


Components::ConfigValues*
CPFReader::readConf(std::string descriptor)
throw(CPFReadException)
{
	//
	// parse the component property file descriptor file
    //
	DOMXMLParser parser;
	char* xmlfile = strdup(descriptor.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		NORMAL_ERR2( "CPFReader: error during XML parsing of ", descriptor );
        throw CPFReadException();
	}
	cpf_document_ = parser.getDocument();

	Components::ConfigValues* config = new Components::ConfigValues();
	int len = 0;
	DOMNode* child = cpf_document_->getDocumentElement()->getFirstChild();
    while( child != 0)
    {
		//
		// configuration
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("configuration")) ) )
		{
			// new config entry
			Components::ConfigValue* cf = configuration((DOMElement*)(child));
			if(cf)
			{
				config->length( ++len );
				( *config )[len - 1] = cf;
			}
		}

		//
		// extensionspecification
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("extensionspecification")) ) )
		{
			// new config entry
			Components::ConfigValue* cf = extensionspecification((DOMElement*)(child));
			if(cf)
			{
				config->length( ++len );
				( *config )[len - 1] = cf;
			}
		}

		// next element
		child = child->getNextSibling();
	}

	return config;
}

Components::ConfigValue* 
CPFReader::extensionspecification (DOMElement* element)
throw(CPFReadException)
{
	CORBA::ULong len = 0;
	Components::ConfigValues *content = new Components::ConfigValues();
	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// binding
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("binding")) ) )
		{
			// new config entry
			Components::ConfigValue* cf = binding((DOMElement*)(child));
			if(cf)
			{
				content->length( ++len );
				( *content )[len - 1] = cf;
			}

		}

		//
		// constraint
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("constraint")) ) )
		{
			// new config entry
			Components::ConfigValue* cf = constraint((DOMElement*)(child));
			if(cf)
			{
				content->length( ++len );
				( *content )[len - 1] = cf;
			}
		}
		// next element
		child = child->getNextSibling();
	}

	CORBA::Any content_any;
	content_any <<= content;
	return new ConfigValue_impl( CORBA::string_dup( "extensionspecification" ), content_any );

}

Components::ConfigValue* 
CPFReader::binding (DOMElement* element)
throw(CPFReadException)
{
	CORBA::ULong len = 0;
	CORBA::Any any;
	std::string val;
	Components::ConfigValues *content = new Components::ConfigValues();
	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// componentid
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("componentid")) ) )
		{
			val = value((DOMElement*)(child));
			any <<= val.c_str();
			Components::ConfigValue* cf = new ConfigValue_impl( CORBA::string_dup( "componentid"), any );
			content->length( ++len );
			( *content )[len - 1] = cf;

		}

		//
		// restriction
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("restriction")) ) )
		{
			val = value((DOMElement*)(child));
			any <<= val.c_str();
			Components::ConfigValue* cf = new ConfigValue_impl( CORBA::string_dup( "restriction" ), any );
			content->length( ++len );
			( *content )[len - 1] = cf;

		}
		
		// next element
		child = child->getNextSibling();
	}

	CORBA::Any content_any;
	content_any <<= content;
	return new ConfigValue_impl( CORBA::string_dup( "binding" ), content_any );

}

Components::ConfigValue* 
CPFReader::constraint(DOMElement* element)
throw(CPFReadException)
{
	CORBA::ULong len = 0;
	Components::ConfigValues *content = new Components::ConfigValues();
	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// characteristic
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("characteristic")) ) )
		{
			// new config entry
			Components::ConfigValue* cf = characteristic ((DOMElement*)(child));
			if(cf)
			{
				content->length( ++len );
				( *content )[len - 1] = cf;
			}
		}
		// next element
		child = child->getNextSibling();
	}

	CORBA::Any content_any;
	content_any <<= content;
	return new ConfigValue_impl( CORBA::string_dup( "constraint" ), content_any );

}

Components::ConfigValue* 
CPFReader::characteristic (DOMElement* element)
throw(CPFReadException)
{
	CORBA::ULong len = 0;
	Components::ConfigValues *content = new Components::ConfigValues();

	//
	// name
	//
	std::string name = Qedo::transcode(element->getAttribute(X("name")));
	CORBA::Any name_any;
	name_any <<= name.c_str();
	Components::ConfigValue* name_config = new ConfigValue_impl(CORBA::string_dup("name"), name_any);
	content->length( ++len );
	( *content )[len - 1] = name_config;

	DOMNode* child = element->getFirstChild();
    while( child != 0)
    {
		//
		// characteristic
		//
		if( ( child->getNodeType() == DOMNode::ELEMENT_NODE ) &&
			( !XMLString::compareString(child->getNodeName(), X("dimension")) ) )
		{
			// new config entry
			Components::ConfigValue* cf = dimension ((DOMElement*)(child));
			if(cf)
			{
				content->length( ++len );
				( *content )[len - 1] = cf;
			} 
		}
		// next element
		child = child->getNextSibling();
	}

	CORBA::Any content_any;
	content_any <<= content;
	return new ConfigValue_impl( CORBA::string_dup( "characteristic" ), content_any );

}

Components::ConfigValue* 
CPFReader::dimension (DOMElement* element)
throw(CPFReadException)
{
	CORBA::ULong len = 0;
	Components::ConfigValues *content = new Components::ConfigValues();

	//
	// name
	//
	std::string name = Qedo::transcode(element->getAttribute(X("name")));
	CORBA::Any name_any;
	name_any <<= name.c_str();
	Components::ConfigValue* name_config = new ConfigValue_impl(CORBA::string_dup("name"), name_any);
	content->length( ++len );
	( *content )[len - 1] = name_config;

	//
	// statistical
	//
	std::string statistical = Qedo::transcode(element->getAttribute(X("statistical")));
	CORBA::Any statistical_any;
	statistical_any <<= statistical.c_str();
	Components::ConfigValue* statistical_config = new ConfigValue_impl(CORBA::string_dup("statistical"), statistical_any);
	content->length( ++len );
	( *content )[len - 1] = statistical_config;
	
	//
	// direction
	//
	std::string direction = Qedo::transcode(element->getAttribute(X("direction")));
	CORBA::Any direction_any;
	direction_any <<= direction.c_str();
	Components::ConfigValue* direction_config = new ConfigValue_impl(CORBA::string_dup("direction"), direction_any);
	content->length( ++len );
	( *content )[len - 1] = direction_config;

	//
	// unit
	//
	std::string unit = Qedo::transcode(element->getAttribute(X("unit")));
	CORBA::Any unit_any;
	unit_any <<= unit.c_str();
	Components::ConfigValue* unit_config = new ConfigValue_impl(CORBA::string_dup("unit"), unit_any);
	content->length( ++len );
	( *content )[len - 1] = unit_config;


	//
	// value
	//
	std::string val = value(element);
	CORBA::Any val_any;
	val_any <<= val.c_str();
	Components::ConfigValue* val_config = new ConfigValue_impl( CORBA::string_dup( "value"), val_any );
	content->length( ++len );
	( *content )[len - 1] = val_config;

	CORBA::Any content_any;
	content_any <<= content;
	return new ConfigValue_impl( CORBA::string_dup( "dimension" ), content_any );

}

}

