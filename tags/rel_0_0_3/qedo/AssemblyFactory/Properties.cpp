/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
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

#include "Properties.h"


namespace Qedo {


/**
 *
 */
Properties::Properties(std::string descriptor)
{
    descriptor_ = descriptor;
	parser_ = new DOMXMLParser();
}


/**
 *
 */
Properties::~Properties()
{
}


/**
 *
 */
Components::ConfigValues*
Properties::getConfigValues()
{
	char* fileName = strdup( descriptor_.c_str() );
	parser_->parse( fileName );
	document_ = parser_->getDocument();
	DOM_Element property = document_.getDocumentElement();
	
	Components::ConfigValues* config = new Components::ConfigValues();
	int len = 0;
	DOM_Node child = property.getFirstChild();
    while( child != 0)
    {
		// simple
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "simple" ) ) )
		{
			DOM_NodeList nodeList;
			DOM_Element simple = ( DOM_Element& )child;
			std::string type = simple.getAttribute( "type" ).transcode();
			std::string name = simple.getAttribute( "name" ).transcode();

			nodeList = simple.getElementsByTagName( "value" );
			DOM_Element value = ( const DOM_Element& )nodeList.item( 0 );

			CORBA::Any any;
			std::string val = value.getFirstChild().getNodeValue().transcode();
			
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
				CORBA::UShort v = atol( val.c_str() );
				any <<= v;
			}

			// new config entry
			config->length( ++len );
			( *config )[len - 1] = new ConfigValue_impl( CORBA::string_dup( name.c_str() ), any );
		}

		// sequence
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "sequence" ) ) )
		{
		}

		// struct
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "struct" ) ) )
		{
		}

		// value
		if( ( child.getNodeType() == DOM_Node::ELEMENT_NODE ) &&
			( child.getNodeName().equals( "valuetype" ) ) )
		{
		}

		// next element
		child = child.getNextSibling();
	}

	return config;
}


}