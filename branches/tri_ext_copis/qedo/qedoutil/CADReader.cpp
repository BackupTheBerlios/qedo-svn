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

#include "CADReader.h"
#include "CSDReader.h"
#include "CCDReader.h"
#include "Output.h"
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <fstream>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#undef WIN32_LEAN_AND_MEAN
#endif

namespace Qedo {


CADReader::CADReader()
{
}


CADReader::~CADReader()
{
}


ScriptData 
CADReader::action (DOMElement* element)
throw(CADReadException)
{
	ScriptData data;
	data.language = Qedo::transcode(element->getAttribute(X("language")));

	std::string element_name;
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
				FileData file_data = fileinarchive( (DOMElement*)child );
				std::ifstream file;
				file.open( file_data.name.c_str() );
				if (!file)
				{
					NORMAL_ERR2( "CADReader: cannot open file ", file_data.name );
					throw CADReadException();
				}
				file >> data.code;
				file.close();
				// todo what to do with the extracted file?
			}

			//
			// scriptcode
			//
			else if (element_name == "scriptcode")
			{
				data.code = scriptcode( (DOMElement*)child );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


ReferenceData
CADReader::activation (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// findby
			//
			if (element_name == "findby")
			{
				return findby( (DOMElement*)child );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	NORMAL_ERR( "CADReader: no activation ref" );
	throw CADReadException();
}

void CADReader::binding (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	StreamConnectionData stream_connection_data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// sourceport
			//
			if (element_name == "sourceport")
			{
				stream_connection_data.kind=SOURCE;
				stream_connection_data.source=sourceport((DOMElement*)child);
			}

			//
			// sinkport
			//
			else if (element_name == "sinkport")
			{
				stream_connection_data.kind=SINK;
				stream_connection_data.sink=sinkport((DOMElement*)child);
			}

			
		}

        // get next child
		//data_->stream_connections_.push_back(stream_connection_data);
	    child = child->getNextSibling();
	}

	data_->stream_connections_.push_back(stream_connection_data);


}

void
CADReader::componentassembly (DOMElement* element)
throw(CADReadException)
{
	//
	// get assembly id
	//
	data_->uuid_ = Qedo::transcode(element->getAttribute(X("id")));
	
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// description
			//
			if (element_name == "description")
			{
				description((DOMElement*)(child));
			}

			//
			// componentfiles
			//
			else if (element_name == "componentfiles")
			{
				componentfiles((DOMElement*)(child));
			}

			//
			// partitioning
			//
			else if (element_name == "partitioning")
			{
				partitioning((DOMElement*)(child));
			}

			//
			// connections
			//
			else if (element_name == "connections")
			{
				connections((DOMElement*)(child));
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}
}


void
CADReader::componentfile (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	FileData file;
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
				file = fileinarchive((DOMElement*)child);
			}

			//
			// codebase
			//
			else if (element_name == "codebase")
			{
				// TODO
			}

			//
			// link
			//
			else if (element_name == "link")
			{
				file.name = link((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	std::string id = Qedo::transcode(element->getAttribute(X("id")));
	DEBUG_OUT( "CADReader: <componentfile>" );
	data_->implementationMap_[id] = file;
}


void
CADReader::componentfiles (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// componentfile
			//
			if (element_name == "componentfile")
			{
				componentfile((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}
}


std::string
CADReader::componentfileref (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("idref")));
}


std::string
CADReader::componentimplref (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("idref")));
}


ComponentInstanceData
CADReader::componentinstantiation (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ComponentInstanceData data;
    data.id = Qedo::transcode(element->getAttribute(X("id")));
	DOMNode* child = element->getFirstChild();
	DOMElement* elem;
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
			elem = (DOMElement*)child;

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename(elem);
			}

			//
			// componentproperties
			//
			else if (element_name == "componentproperties")
			{
				data.comp_prop = componentproperties(elem);
			}

			//
			// registercomponent
			//
			else if (element_name == "registercomponent")
			{
				registercomponent(elem, data);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension(elem);
			}

			//
			// rule
			//
			else if (element_name == "rule")
			{
				data.rules.push_back( rule(elem) );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}

ComponentInstanceData
CADReader::componentinstantiation_two (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ComponentInstanceData data;
    data.id = Qedo::transcode(element->getAttribute(X("id")));
	DOMNode* child = element->getFirstChild();
	DOMElement* elem;
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
			elem = (DOMElement*)child;

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename(elem);
			}

			//
			// componentproperties
			//
			else if (element_name == "componentproperties")
			{
				data.comp_prop = componentproperties_two(elem);
			}

			//
			// registercomponent
			//
			else if (element_name == "registercomponent")
			{
				registercomponent(elem, data);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension(elem);
			}

			//
			// rule
			//
			else if (element_name == "rule")
			{
				data.rules.push_back( rule(elem) );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}

std::string
CADReader::componentinstantiationref (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("idref")));
}


std::string
CADReader::componentproperties (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	FileData file;
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
				file = fileinarchive((DOMElement*)child);
			}

			//
			// codebase
			//
			else if (element_name == "codebase")
			{
				// todo
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	
	return file.name;
}

std::string
CADReader::componentproperties_two (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	FileData file;
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
				file = fileinarchive_two((DOMElement*)child);
			}

			//
			// codebase
			//
			else if (element_name == "codebase")
			{
				// todo
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	
	return file.name;
}


ReferenceData
CADReader::componentsupportedinterface (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ReferenceData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// componentinstantiationref
			//
			if (element_name == "componentinstantiationref")
			{
				data.kind = COMPONENTID;
				data.name = componentinstantiationref((DOMElement*)(child));
			}

			//
			// findby
			//
			else if (element_name == "findby")
			{
				data = findby((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


ScriptData 
CADReader::condition (DOMElement* element)
throw(CADReadException)
{
	ScriptData data;
	data.language = Qedo::transcode(element->getAttribute(X("language")));

	std::string element_name;
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
				FileData file_data = fileinarchive( (DOMElement*)child );
				std::ifstream file;
				file.open( file_data.name.c_str() );
				if (!file)
				{
					NORMAL_ERR2( "CADReader: cannot open file ", file_data.name );
					throw CADReadException();
				}
				file >> data.code;
				file.close();
				// todo what to do with the extracted file?
			}

			//
			// scriptcode
			//
			else if (element_name == "scriptcode")
			{
				data.code = scriptcode( (DOMElement*)child );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


void
CADReader::connectevent (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	EventConnectionData event_connection;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// consumesport
			//
			if (element_name == "consumesport")
			{
				event_connection.consumer = consumesport((DOMElement*)(child));
			}

			//
			// emitsport
			//
			else if (element_name == "emitsport")
			{
				event_connection.kind = EMITTER;
				event_connection.emitter = emitsport((DOMElement*)(child));
			}

			//
			// publishesport
			//
			else if (element_name == "publishesport")
			{
				event_connection.kind = PUBLISHER;
				event_connection.emitter = publishesport((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	// add new event_connection
	data_->event_connections_.push_back(event_connection);
}


void
CADReader::connecthomes (DOMElement* element)
throw(CADReadException)
{
	// todo
}


void
CADReader::connectinterface (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	InterfaceConnectionData interface_connection;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// usesport
			//
			if (element_name == "usesport")
			{
				interface_connection.use = usesport((DOMElement*)child);
			}

			//
			// providesport
			//
			else if (element_name == "providesport")
			{
				interface_connection.provide = providesport((DOMElement*)child);
			}

			//
			// componentsupportedinterface
			//
			else if (element_name == "componentsupportedinterface")
			{
				interface_connection.provide.ref = componentsupportedinterface((DOMElement*)child);
			}

			//
			// existinginterface
			//
			else if (element_name == "existinginterface")
			{
				interface_connection.provide.ref = existinginterface((DOMElement*)child);
			}

			//
			// homeinterface
			//
			else if (element_name == "homeinterface")
			{
				interface_connection.provide.ref = homeinterface((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	// add new interface_connection
	data_->interface_connections_.push_back(interface_connection);
}


void
CADReader::connections (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
		
			//
			// connectinterface
			//
			if (element_name == "connectinterface")
			{
				connectinterface((DOMElement*)child);
			}

			//
			// connectevent
			//
			if (element_name == "connectevent")
			{
				connectevent((DOMElement*)child);
			}

			//
			// connecthomes
			//
			if (element_name == "connecthomes")
			{
				connecthomes((DOMElement*)child);
			}

			//
			// extension
			//
			if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}

			// extension by Heini
			// binding
			//
			if (element_name == "binding")
			{
				binding((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }
}


std::string
CADReader::consumesidentifier (DOMElement* element)
throw(CADReadException)
{
    std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}


PortData
CADReader::consumesport (DOMElement* element)
throw(CADReadException)
{
	PortData data;

	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// consumesidentifier
			//
			if (element_name == "consumesidentifier")
			{
				data.name = consumesidentifier((DOMElement*)(child));
			}

			//
			// componentinstantiationref
			//
			else if (element_name == "componentinstantiationref")
			{
				data.ref.kind = COMPONENTID;
				data.ref.name = componentinstantiationref((DOMElement*)(child));
			}

			//
			// findby
			//
			else if (element_name == "findby")
			{
				data.ref = findby((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


std::string 
CADReader::description (DOMElement* element)
throw(CADReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
	
	DEBUG_OUT2( "CADReader: <description> ", text );
    return text;
}


DestinationData
CADReader::destination (DOMElement* element)
throw(CADReadException)
{
	DestinationData data;

	std::string element_name;
	DOMNode* child = element->getFirstChild();
	DOMElement* elem;
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
			elem = (DOMElement*)child;

			//
			// node
			//
			if (element_name == "node")
			{
				data.node = node( elem );
				
				
				// if empty take local host
				if( data.node.empty() )
				{
					char hostname[256];
					gethostname(hostname, 256);
					data.node = hostname;
					DEBUG_OUT2( "CADReader: unspecified node, take ", hostname );
				}
			}

			//
			// installation
			//
			else if (element_name == "installation")
			{
				// get type of installation
				data.installation_type = Qedo::transcode( elem->getAttribute(X("type")) );
				data.installation_ref = installation( elem );
			}

			//
			// activation
			//
			else if (element_name == "activation")
			{
				// get type of activation
				data.activation_type = Qedo::transcode( elem->getAttribute(X("type")) );
				data.activation_ref = activation( elem );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	data.specified = true;
	return data;
}

DestinationData
CADReader::destination_two (DOMElement* element)
throw(CADReadException)
{
	DestinationData data;

	std::string element_name;
	DOMNode* child = element->getFirstChild();
	DOMElement* elem;
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
			elem = (DOMElement*)child;

			//
			// node
			//
			if (element_name == "node")
			{
				data.node = node( elem );
				
				/*
				// if empty take local host
				if( data.node.empty() )
				{
					char hostname[256];
					gethostname(hostname, 256);
					data.node = hostname;
					DEBUG_OUT2( "CADReader: unspecified node, take ", hostname );
				}
				*/
			}

			//
			// installation
			//
			else if (element_name == "installation")
			{
				// get type of installation
				data.installation_type = Qedo::transcode( elem->getAttribute(X("type")) );
				data.installation_ref = installation( elem );
			}

			//
			// activation
			//
			else if (element_name == "activation")
			{
				// get type of activation
				data.activation_type = Qedo::transcode( elem->getAttribute(X("type")) );
				data.activation_ref = activation( elem );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	data.specified = true;
	return data;
}

std::string
CADReader::emitsidentifier (DOMElement* element)
throw(CADReadException)
{
    std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}


PortData
CADReader::emitsport (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	PortData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// emitsidentifier
			//
			if (element_name == "emitsidentifier")
			{
				data.name = emitsidentifier((DOMElement*)(child));
				
			}  

			//
			// componentinstantiationref
			//
			else if (element_name == "componentinstantiationref")
			{
				data.ref.kind = COMPONENTID;
				data.ref.name = componentinstantiationref((DOMElement*)(child));
			}

			//
			// findby
			//
			else if (element_name == "findby")
			{
				data.ref = findby((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


void
CADReader::executableplacement (DOMElement* element)
throw(CADReadException)
{
	// todo
}


ReferenceData
CADReader::existinginterface (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ReferenceData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
		
			//
			// findby
			//
			if (element_name == "findby")
			{
				data = findby((DOMElement*)(child));
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	return data;
}


void
CADReader::extension (DOMElement* element)
throw(CADReadException)
{
	std::string class_attr = Qedo::transcode(element->getAttribute(X("class")));
	
    //
    // startorder
    //
    if( class_attr == "startorder" )
	{
		std::string id = Qedo::transcode(element->getFirstChild()->getNodeValue());
		data_->start_order_.push_back( id );
	}
}

Extension 
CADReader::extension_two(DOMElement* element)
throw(CADReadException)
{
	Extension extension;
	std::string class_attr = Qedo::transcode(element->getAttribute(X("class")));
	
    //
    // startorder
    //
    if( class_attr == "startorder" )
	{
		std::string id = Qedo::transcode(element->getFirstChild()->getNodeValue());
		//extension.start_order_=id;
		//data_->start_order_.push_back( id );
	}

	return extension;
}


FileData
CADReader::fileinarchive(DOMElement* element)
throw(CADReadException)
{
	std::string file = Qedo::transcode(element->getAttribute(X("name")));

	FileData file_data;
	file_data.name = path_ + getFileName( file );

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
				file_data.archiv = link((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	//
	// extract the file
	//
	if( file_data.archiv.empty() )
	{
		//
		// same archiv
		//
		if (package_->extractFile(file, file_data.name) != 0)
		{
			NORMAL_ERR2( "CADReader: error during extracting file ", file );
			throw CADReadException();
		}
	}
	else
	{
		//
		// other archiv
		//		
		Package new_package( file_data.archiv );
		if (new_package.extractFile(file, file_data.name) != 0)
		{
			NORMAL_ERR2( "CADReader: error during extracting file ", file );
			NORMAL_ERR2( "CADReader: package is ", file_data.archiv );
			throw CADReadException();
		}
	}

	return file_data;
}

FileData
CADReader::fileinarchive_two(DOMElement* element)
throw(CADReadException)
{
	std::string file = Qedo::transcode(element->getAttribute(X("name")));

	FileData file_data;
	file_data.name = file; //path_ + getFileName( file );

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
				file_data.archiv = link((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	
	return file_data;
}


ReferenceData
CADReader::findby (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ReferenceData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
		
			//
			// namingservice
			//
			if (element_name == "namingservice")
			{
				data.kind = NAMING;
				data.name = namingservice((DOMElement*)child);
			}

			//
			// stringifiedobjectref
			//
			if (element_name == "stringifiedobjectref")
			{
				data.kind = OBJECTREF;
				data.name = stringifiedobjectref((DOMElement*)child);
			}

			//
			// traderquery
			//
			if (element_name == "traderquery")
			{
				data.kind = TRADER;
				traderquery((DOMElement*)child);
			}

			//
			// homefinder
			//
			if (element_name == "homefinder")
			{
				data.kind = FINDER;
				data.name = homefinder((DOMElement*)child);
			}

			//
			// extension
			//
			if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	return data;
}

std::vector <HomeInstanceData>
CADReader::findHomeInstanceData(DOMElement* element)
throw(CADReadException)
{
	//
	// need for qedo controller, find the homeplacements
	//
	
	std::string element_name;
	std::vector <HomeInstanceData> homeplacements;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

				
			//
			// partitioning
			//
			if (element_name == "partitioning")
			{
                homeplacements=partitioning_homeplacement((DOMElement*)child);

			}

			
			
		}

        // get next child
	    child = child->getNextSibling();
	}
	return homeplacements;
}

std::vector <HostData> 
CADReader::findHostData (DOMElement* element)
throw(CADReadException)
{ 
//
	// need for qedo controller, find the processcollocation
	//
	
	std::string element_name;
	std::vector <HostData> host_datas;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

				
			//
			// partitioning
			//
			if (element_name == "partitioning")
			{
                host_datas=partitioning_hostdata((DOMElement*)child);

			}

			
			
		}

        // get next child
	    child = child->getNextSibling();
	}
	return host_datas;

}

Partitioning CADReader::findPartitioningData(DOMElement* element)
throw(CADReadException)
{	
	//
	// need for qedo controller, find the processcollocation
	//
	
	std::string element_name;
	Partitioning parti;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

				
			//
			// partitioning
			//
			if (element_name == "partitioning")
			{
                //parti=partitioning_data((DOMElement*)child);

			}

			
			
		}

        // get next child
	    child = child->getNextSibling();
	}
	return parti;
}



std::vector <ProcessData> 
CADReader::findProcessData(DOMElement* element)
throw(CADReadException)
{
	//
	// need for qedo controller, find the processcollocation
	//
	
	std::string element_name;
	std::vector <ProcessData> Process_datas;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

				
			//
			// partitioning
			//
			if (element_name == "partitioning")
			{
                Process_datas=partitioning_processdata((DOMElement*)child);

			}

			
			
		}

        // get next child
	    child = child->getNextSibling();
	}
	return Process_datas;

}

std::string
CADReader::homefinder (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("name")));
}


ReferenceData
CADReader::homeinterface (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ReferenceData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// homeplacementref
			//
			if (element_name == "homeplacementref")
			{
				data.kind = HOMEID;
				data.name = homeplacementref((DOMElement*)child);
			}

			//
			// findby
			//
			else if (element_name == "findby")
			{
				data = findby((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


HomeInstanceData
CADReader::homeplacement (DOMElement* element)
throw(CADReadException)
{
	HomeInstanceData data;

	//
	// attribute id
	//
	data.id = Qedo::transcode(element->getAttribute(X("id")));

	//
	// attribute cardinality
	//
	std::string cardinality = Qedo::transcode(element->getAttribute(X("cardinality")));
	if( !cardinality.empty() )
	{
		data.cardinality = atoi( cardinality.c_str() );
	}
	else
	{
		data.cardinality = 1;
	}

	//
	// content
	//
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)child);
			}

			//
			// componentfileref
			//
			else if (element_name == "componentfileref")
			{
				data.file = data_->implementationMap_[componentfileref((DOMElement*)child)].archiv;
			}

			//
			// componentimplref
			//
			else if (element_name == "componentimplref")
			{
				data.impl_id = componentimplref((DOMElement*)child);
			}

			//
			// homeproperties
			//
			else if (element_name == "homeproperties")
			{
				data.home_prop = homeproperties((DOMElement*)child);
			}

			//
			// componentproperties
			//
			else if (element_name == "componentproperties")
			{
				data.comp_prop = componentproperties((DOMElement*)child);
			}

			//
			// registerwithhomefinder
			//
			else if (element_name == "registerwithhomefinder")
			{
				data.finder = registerwithhomefinder((DOMElement*)child);
			}

			//
			// registerwithnaming
			//
			else if (element_name == "registerwithnaming")
			{
				data.naming = registerwithnaming((DOMElement*)child);
			}

			//
			// registerwithtrader
			//
			else if (element_name == "registerwithtrader")
			{
				data.trader = registerwithtrader((DOMElement*)child);
			}

			//
			// componentinstantiation
			//
			else if (element_name == "componentinstantiation")
			{
				data.instances.push_back(componentinstantiation((DOMElement*)child));
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.dest = destination((DOMElement*)child);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}

			//
			// rule
			//
			else if (element_name == "rule")
			{
				data.rules.push_back( rule((DOMElement*)child) );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	//
	// extension: existing home
	//
	if( data.file.empty() )
	{
		return data;
	}

	//
	// read ccd for the requested component
	//
	Package archive = Package( data.file );
    std::string csdfile = archive.getFileNameWithSuffix( ".cad" );
	std::string ccdfile;
    if( 0 ) //!csdfile.empty() )
	{
		// todo extension
	}
	else
	{
		csdfile = archive.getFileNameWithSuffix( ".csd" );

		//
		// get ccd from the software package
		//
		CSDReader csd_reader( data.file, path_ );
		try 
		{
			ccdfile = csd_reader.getCCD( data.impl_id );
		}
		catch( CSDReadException ) 
		{
			NORMAL_ERR2( "CADReader: error during reading .csd file ", data.file );
			throw Components::CreateFailure();
		}

		//
		// read ccd
		//
		if( ccdfile.empty() )
		{
			NORMAL_ERR2( "CADReader: no .ccd file for ", data.impl_id );
			throw Components::CreateFailure();
		}
		CCDReader ccd_reader( ccdfile, path_ );
		try 
		{
			ccd_reader.readCCD( &data.component, &archive );
		}
		catch( CSDReadException ) 
		{
			NORMAL_ERR2( "CADReader: error during reading .ccd file ", ccdfile );
			throw Components::CreateFailure();
		}
	}

	return data;
}

HomeInstanceData
CADReader::homeplacement_two (DOMElement* element)
throw(CADReadException)
{
	HomeInstanceData data;

	//
	// attribute id
	//
	data.id = Qedo::transcode(element->getAttribute(X("id")));

	//
	// attribute cardinality
	//
	std::string cardinality = Qedo::transcode(element->getAttribute(X("cardinality")));
	if( !cardinality.empty() )
	{
		data.cardinality = atoi( cardinality.c_str() );
	}
	else
	{
		data.cardinality = -1;
	}

	//
	// content
	//
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)child);
			}

			//
			// componentfileref
			//
			else if (element_name == "componentfileref")
			{
				data.file = componentfileref((DOMElement*)child);
				
			}

			//
			// componentimplref
			//
			else if (element_name == "componentimplref")
			{
				data.impl_id = componentimplref((DOMElement*)child);
			}

			//
			// homeproperties
			//
			else if (element_name == "homeproperties")
			{
				data.home_prop = homeproperties((DOMElement*)child);
			}

			//
			// componentproperties
			//
			else if (element_name == "componentproperties")
			{
				data.comp_prop = componentproperties_two((DOMElement*)child);
			}

			//
			// registerwithhomefinder
			//
			else if (element_name == "registerwithhomefinder")
			{
				data.finder = registerwithhomefinder((DOMElement*)child);
			}

			//
			// registerwithnaming
			//
			else if (element_name == "registerwithnaming")
			{
				data.naming = registerwithnaming((DOMElement*)child);
			}

			//
			// registerwithtrader
			//
			else if (element_name == "registerwithtrader")
			{
				data.trader = registerwithtrader((DOMElement*)child);
			}

			//
			// componentinstantiation
			//
			else if (element_name == "componentinstantiation")
			{
				data.instances.push_back(componentinstantiation_two((DOMElement*)child));
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.dest = destination_two((DOMElement*)child);
				
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}

			//
			// rule
			//
			else if (element_name == "rule")
			{
				data.rules.push_back( rule((DOMElement*)child) );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}
	
	

	
	return data;
}


std::string
CADReader::homeplacementref (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("idref")));
}


std::string
CADReader::homeproperties (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	FileData file;
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
				file = fileinarchive((DOMElement*)child);
			}

			//
			// codebase
			//
			else if (element_name == "codebase")
			{
				// todo
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	// if changing  -> changing homeplacement_two(qedo controller...)
	return file.name;
}


HostData
CADReader::hostcollocation (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	HostData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)child);
			}

			//
			// impltype
			//
			else if (element_name == "impltype")
			{
				// todo
			}

			//
			// homeplacement
			//
			else if (element_name == "homeplacement")
			{
				HomeInstanceData home_instance = homeplacement((DOMElement*)child);
				ProcessData process;
				process.dest = home_instance.dest;
				process.homes.push_back(home_instance);
				data.processes.push_back(process);
			}

			//
			// executableplacement
			//
			else if (element_name == "executableplacement")
			{
				executableplacement((DOMElement*)child);
			}

			//
			// processcollocation
			//
			else if (element_name == "processcollocation")
			{
				ProcessData process = processcollocation((DOMElement*)child);
				data.dest = process.dest;
				data.processes.push_back(process);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.dest = destination((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}

HostData
CADReader::hostcollocation_two (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	HostData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)child);
			}

			//
			// impltype
			//
			else if (element_name == "impltype")
			{
				// todo
			}

			//
			// homeplacement
			//
			else if (element_name == "homeplacement")
			{
				HomeInstanceData home_instance = homeplacement_two((DOMElement*)child);
				ProcessData process;
				process.dest = home_instance.dest;
				process.homes.push_back(home_instance);
				data.processes.push_back(process);
			}

			//
			// executableplacement
			//
			else if (element_name == "executableplacement")
			{
				executableplacement((DOMElement*)child);
			}

			//
			// processcollocation
			//
			else if (element_name == "processcollocation")
			{
				ProcessData process = processcollocation_two((DOMElement*)child);
				data.dest = process.dest;
				data.processes.push_back(process);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.dest = destination_two((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


ReferenceData
CADReader::installation (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// findby
			//
			if (element_name == "findby")
			{
				return findby( (DOMElement*)child );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	NORMAL_ERR( "CADReader: no installation ref" );
	throw CADReadException();
}


std::string
CADReader::link (DOMElement* element)
throw(CADReadException)
{
    XMLURL uri(element->getAttribute(X("href")));
    std::string name = Qedo::transcode(uri.getPath());
    std::string::size_type pos = name.find_last_of("/");
	std::string fileName;

    if (pos != std::string::npos)
    {
        name.erase(0, pos + 1);
		fileName = path_ + name;
    }
	else
	{
		fileName = path_ + name;
    
		//
		// local uri (!!! without "/" !!!) is interpreted as link in archiv
		//
		if (package_->extractFile(name, fileName) != 0)
		{
			NORMAL_ERR2( "CADReader: error during extracting from archiv ", name );
			throw CADReadException();
		}

		return fileName;
	}

	//
	// get file from uri
	//
    URLInputSource inputSource(uri);
    BinInputStream* inputStream = inputSource.makeStream();
    if (!inputStream)
    {
        throw CADReadException();
    }
        
	std::ofstream aFile;
	aFile.open(fileName.c_str(), std::ios::binary|std::ios::app);
	if (!aFile)
	{
		NORMAL_ERR2( "CADReader: cannot open file ", fileName );
		throw CADReadException();
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

    return fileName;
}


std::string
CADReader::namingservice (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("name")));
}


std::string
CADReader::node (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("name")));
}


void
CADReader::partitioning (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// homeplacement
			//
			if (element_name == "homeplacement")
			{
				HomeInstanceData home = homeplacement((DOMElement*)child);
				if(home.file.empty())
				{
					//
					// extension, use existing home
					//
					data_->existing_homes_.push_back(home);
				}
				else
				{
					//
					// if destination is not specified take local host
					//
					if( !home.dest.specified )
					{
						char hostname[256];
						gethostname(hostname, 256);
						home.dest.node = hostname;
						DEBUG_OUT2( "CADReader: unspecified destination for home, take ", hostname );
					}

					ProcessData process;
					process.dest = home.dest;
					process.homes.push_back(home);
					HostData host;
					host.dest = process.dest;
					host.processes.push_back(process);
					data_->hosts_.push_back(host);
				}
			}

			//
			// executableplacement
			//
			else if (element_name == "executableplacement")
			{
				executableplacement((DOMElement*)child);
			}

			//
			// processcollocation
			//
			else if (element_name == "processcollocation")
			{
				ProcessData process = processcollocation((DOMElement*)child);

				//
				// if destination is not specified take local host
				//
				if( !process.dest.specified )
				{
					char hostname[256];
					gethostname(hostname, 256);
					process.dest.node = hostname;
					DEBUG_OUT2( "CADReader: unspecified destination for processcollocation, take ", hostname );
				}

				HostData host;
				host.dest = process.dest;
				host.processes.push_back(process);
				data_->hosts_.push_back(host);
			}

			//
			// hostcollocation
			//
			else if (element_name == "hostcollocation")
			{
				HostData host = hostcollocation( (DOMElement*)child );

				//
				// if destination is not specified take local host
				//
				if( !host.dest.specified )
				{
					char hostname[256];
					gethostname(hostname, 256);
					host.dest.node = hostname;
					DEBUG_OUT2( "CADReader: unspecified destination for hostcollocation, take ", hostname );
				}

				data_->hosts_.push_back( host );
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}
}

/*
Partitioning
partitioning_data(DOMElement* element)
throw(CADReadException)
{
	
	std::string element_name;
	Qedo::Partitioning parti;
	/*
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			/* ??????????

			//
			// executableplacement
			//
			if (element_name == "executableplacement")
			{
				parti executableplacement((DOMElement*)child);
			}

			????????????????
			
					
			//
			// extension
			//
			if (element_name == "extension")
			{
				Qedo::Extension extension;
				std::string class_attr = Qedo::transcode(element->getAttribute(X("class")));
	
				//
				// startorder
			    //
			   if( class_attr == "startorder" )
			   {
						std::string id = Qedo::transcode(element->getFirstChild()->getNodeValue());
						extension.start_order_.push_back(id);
		
				}

				parti.extensions.push_back(extension);
			}
			
		}

        // get next child
	    child = child->getNextSibling();
		
	}
	
	return parti;
}
*/
std::vector <HomeInstanceData>
CADReader::partitioning_homeplacement (DOMElement* element)
throw(CADReadException)
{ 
	std::string element_name;
	std::vector <HomeInstanceData> homeplacements;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{

			element_name = Qedo::transcode(child->getNodeName());

			//
			// homeplacement
			//
			if (element_name == "homeplacement")
			{
				HomeInstanceData home = homeplacement_two((DOMElement*)child);
				
				homeplacements.push_back(home);
			}

		}

        // get next child
	    child = child->getNextSibling();
	}

	return homeplacements;
}

std::vector <HostData> 
CADReader::partitioning_hostdata(DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	std::vector <HostData> host_datas;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{

			element_name = Qedo::transcode(child->getNodeName());

			if (element_name == "hostcollocation")
			{
				HostData host = 
					hostcollocation_two((DOMElement*)child);
				
				host_datas.push_back(host);
			}

		}

        // get next child
	    child = child->getNextSibling();
	}

	return host_datas;
}

std::vector <ProcessData> 
CADReader::partitioning_processdata(DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	std::vector <ProcessData> Process_datas;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{

			element_name = Qedo::transcode(child->getNodeName());

			if (element_name == "processcollocation")
			{
				ProcessData process = 
					processcollocation_two((DOMElement*)child);
				
				Process_datas.push_back(process);
			}

		}

        // get next child
	    child = child->getNextSibling();
	}

	return Process_datas;

}


ProcessData
CADReader::processcollocation (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ProcessData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)child);
			}

			//
			// impltype
			//
			else if (element_name == "impltype")
			{
				// todo
			}

			//
			// homeplacement
			//
			else if (element_name == "homeplacement")
			{
				HomeInstanceData home_instance = homeplacement((DOMElement*)child);
				data.dest = home_instance.dest;
				data.homes.push_back(home_instance);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)child);
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.dest = destination((DOMElement*)child);
				
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	

	return data;
}

ProcessData
CADReader::processcollocation_two (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ProcessData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
			
			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)child);
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.dest = destination_two((DOMElement*)child);
				
			}
			
			//
			// impltype
			//
			else if (element_name == "impltype")
			{
				// todo
			}

			//
			// homeplacement
			//
			else if (element_name == "homeplacement")
			{
				HomeInstanceData home_instance = homeplacement_two((DOMElement*)child);
				//data.dest = home_instance.dest;
				
				data.homes.push_back(home_instance);
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

	
	
	return data;
}


std::string
CADReader::providesidentifier (DOMElement* element)
throw(CADReadException)
{
    std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}


PortData
CADReader::providesport (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	PortData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// providesidentifier
			//
			if (element_name == "providesidentifier")
			{
				data.name = providesidentifier((DOMElement*)(child));
			}

			//
			// componentinstantiationref
			//
			else if (element_name == "componentinstantiationref")
			{
				data.ref.kind = COMPONENTID;
				data.ref.name = componentinstantiationref((DOMElement*)(child));
			}

			//
			// findby
			//
			else if (element_name == "findby")
			{
				data.ref = findby((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


std::string
CADReader::publishesidentifier (DOMElement* element)
throw(CADReadException)
{
    std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}


PortData
CADReader::publishesport (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	PortData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// publishesidentifier
			//
			if (element_name == "publishesidentifier")
			{
				data.name = publishesidentifier((DOMElement*)(child));
			}

			//
			// componentinstantiationref
			//
			else if (element_name == "componentinstantiationref")
			{
				data.ref.kind = COMPONENTID;
				data.ref.name = componentinstantiationref((DOMElement*)(child));
			}

			//
			// findby
			//
			else if (element_name == "findby")
			{
				data.ref = findby((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


void
CADReader::registercomponent (DOMElement* element, ComponentInstanceData& data)
throw(CADReadException)
{
	PortKind port_kind = COMPONENT_PORT;
	std::string port;

	std::string element_name;
	DOMNode* child = element->getFirstChild();
	DOMElement* elem;
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
			elem = (DOMElement*)child;

			//
			// emitsidentifier
			//
			if (element_name == "emitsidentifier")
			{
				port_kind = EMITTER_PORT;
				port = emitsidentifier(elem);
			}

			//
			// providesidentifier
			//
			else if (element_name == "providesidentifier")
			{
				port_kind = FACET_PORT;
				port = providesidentifier(elem);
			}

			//
			// publishesidentifier
			//
			else if (element_name == "publishesidentifier")
			{
				port_kind = PUBLISHER_PORT;
				port = publishesidentifier(elem);
			}

			//
			// registerwithnaming
			//
			else if (element_name == "registerwithnaming")
			{
				NamingRegistrationData reg;
				reg.port_kind = port_kind;
				reg.port = port;
				reg.name = registerwithnaming(elem);

				data.naming_registrations.push_back( reg );

				port_kind = COMPONENT_PORT;
				port = "";
			}

			//
			// registerwithtrader
			//
			else if (element_name == "registerwithtrader")
			{
				// todo
				registerwithtrader(elem);

				port_kind = COMPONENT_PORT;
				port = "";
			}
		}

        // get next child
	    child = child->getNextSibling();
	}
}


std::string
CADReader::registerwithhomefinder (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("name")));
}


std::string
CADReader::registerwithnaming (DOMElement* element)
throw(CADReadException)
{
	return Qedo::transcode(element->getAttribute(X("name")));
}


std::string
CADReader::registerwithtrader (DOMElement* element)
throw(CADReadException)
{
	// todo more
	return Qedo::transcode(element->getAttribute(X("tradername")));
}


RuleData 
CADReader::rule (DOMElement* element)
throw(CADReadException)
{
	RuleData data;
	data.name = Qedo::transcode(element->getAttribute(X("name")));
	data.interval = atol(Qedo::transcode(element->getAttribute(X("interval"))).c_str());

	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// condition
			//
			if (element_name == "condition")
			{
				data.condition = condition( (DOMElement*)child );
			}

			//
			// action
			//
			else if (element_name == "action")
			{
				data.action = action( (DOMElement*)child );
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}



std::string 
CADReader::scriptcode (DOMElement* element)
throw(CADReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}

PortData CADReader::sinkport (DOMElement* element)
throw(CADReadException)
{
	PortData data;

	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// sinkportname
			//
			if (element_name == "sinkportname")
			{
				data.name = consumesidentifier((DOMElement*)(child));
			}

			//
			// componentinstantiationref
			//
			else if (element_name == "componentinstantiationref")
			{
				data.ref.kind = COMPONENTID;
				data.ref.name = componentinstantiationref((DOMElement*)(child));
			}

		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}

PortData CADReader::sourceport (DOMElement* element)
throw(CADReadException)
{
	PortData data;

	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// sourceportname
			//
			if (element_name == "sourceportname")
			{
				data.name = consumesidentifier((DOMElement*)(child));
			}

			//
			// componentinstantiationref
			//
			else if (element_name == "componentinstantiationref")
			{
				data.ref.kind = COMPONENTID;
				data.ref.name = componentinstantiationref((DOMElement*)(child));
			}

		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}

std::string 
CADReader::stringifiedobjectref (DOMElement* element)
throw(CADReadException)
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
CADReader::traderquery (DOMElement* element)
throw(CADReadException)
{
	// todo
}


std::string 
CADReader::usagename (DOMElement* element)
throw(CADReadException)
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
CADReader::usesidentifier (DOMElement* element)
throw(CADReadException)
{
    std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = Qedo::transcode(node->getNodeValue());
	}
    return text;
}


PortData
CADReader::usesport (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	PortData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// usesidentifier
			//
			if (element_name == "usesidentifier")
			{
				data.name = usesidentifier((DOMElement*)(child));
			}

			//
			// componentinstantiationref
			//
			else if (element_name == "componentinstantiationref")
			{
				data.ref.kind = COMPONENTID;
				data.ref.name = componentinstantiationref((DOMElement*)(child));
			}

			//
			// findby
			//
			else if (element_name == "findby")
			{
				data.ref = findby((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


void
CADReader::readCAD(std::string package, AssemblyData* data, std::string path)
throw(CADReadException)
{
	data_ = data;
	path_ = path;
	package_ = new Package(package);

	//
	// find and extract the assembly descriptor
    //
	std::string cadfile_name = package_->getFileNameWithSuffix( ".cad" );
	std::string cadfile = path_ + getFileName( cadfile_name );
    if ( cadfile_name == std::string( "" ) )
	{
		NORMAL_ERR( "CADReader: the format of the package file is not correct" );
        throw CADReadException();
	}
    if ( package_->extractFile( cadfile_name, cadfile) != 0 )
	{
		NORMAL_ERR2( "CADReader: error during extracting descriptor file ", cadfile_name );
        throw CADReadException();
	}

	//
	// parse the component assembly descriptor
    //
	DOMXMLParser parser;
    if ( parser.parse( const_cast<char*>(cadfile.c_str()) ) != 0 ) 
	{
		NORMAL_ERR2( "CADReader: error during parsing ", cadfile );
        throw CADReadException();
	}
	cad_document_ = parser.getDocument();

	// handle componentassembly
	componentassembly(cad_document_->getDocumentElement());

	// remove assembly descriptor and package
    removeFile( cadfile );
	delete package_;
}


std::vector <HomeInstanceData> CADReader::getHomeplacements(std::string cadfile)
throw(CADReadException)
{ 
	std::vector <HomeInstanceData> Homeplacements;
	//
	// parse the component assembly descriptor
    //
	DOMXMLParser parser;
	DOMDocument* cad_document_;
	if ( parser.parse( const_cast<char*>(cadfile.c_str()) ) != 0 ) 
	{
		NORMAL_ERR2( "CADReader: error during parsing ", cadfile );
        throw CADReadException();
	}

	cad_document_ = parser.getDocument();
	
	// handle componentassembly
	Homeplacements=findHomeInstanceData(cad_document_->getDocumentElement());

	return Homeplacements;

}

std::vector <HostData> CADReader::getHostcollocations(std::string cadfile)
throw(CADReadException)
{
	std::vector <HostData> hostdatas;
	
	//
	// parse the component assembly descriptor
    //
	DOMXMLParser parser;
	DOMDocument* cad_document_;
	if ( parser.parse( const_cast<char*>(cadfile.c_str()) ) != 0 ) 
	{
		NORMAL_ERR2( "CADReader: error during parsing ", cadfile );
        throw CADReadException();
	}

	cad_document_ = parser.getDocument();
	
	// handle componentassembly
	hostdatas = findHostData (cad_document_->getDocumentElement());
	
	return hostdatas;
}

std::vector <ProcessData> CADReader::getProcesscollocations(std::string cadfile)
throw(CADReadException)
{
	std::vector <ProcessData> Process_datas;
	//
	// parse the component assembly descriptor
    //
	DOMXMLParser parser;
	DOMDocument* cad_document_;
	if ( parser.parse( const_cast<char*>(cadfile.c_str()) ) != 0 ) 
	{
		NORMAL_ERR2( "CADReader: error during parsing ", cadfile );
        throw CADReadException();
	}

	cad_document_ = parser.getDocument();
	
	// handle componentassembly
	Process_datas=findProcessData(cad_document_->getDocumentElement());

	return Process_datas;

}


// is need for qedo controller to edit destination
Qedo::Partitioning CADReader::getPartitioning(std::string cadfile)
throw(CADReadException)
{
	Partitioning parti;
	//
	// parse the component assembly descriptor
    //
	DOMXMLParser parser;
	DOMDocument* cad_document_;
	if ( parser.parse( const_cast<char*>(cadfile.c_str()) ) != 0 ) 
	{
		NORMAL_ERR2( "CADReader: error during parsing ", cadfile );
        throw CADReadException();
	}

	cad_document_ = parser.getDocument();
	
	// handle componentassembly
	parti=findPartitioningData(cad_document_->getDocumentElement());

	return parti;

}

}
