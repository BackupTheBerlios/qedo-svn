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


namespace Qedo {


CADReader::CADReader()
{
}


CADReader::~CADReader()
{
}


void
CADReader::componentassembly (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

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
	std::string file_name;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());
			
			//
			// fileinarchive
			//
			if (element_name == "fileinarchive")
			{
				file_name = fileinarchive((DOMElement*)child);
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
				file_name = link((DOMElement*)child);
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	std::string id = XMLString::transcode(element->getAttribute(X("id")));
	DEBUG_OUT2( "CADReader: <componentfile> ", file_name );
	data_->implementationMap_[id] = file_name;
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
			element_name = XMLString::transcode(child->getNodeName());

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
	return XMLString::transcode(element->getAttribute(X("idref")));
}


std::string
CADReader::componentimplref (DOMElement* element)
throw(CADReadException)
{
	return XMLString::transcode(element->getAttribute(X("idref")));
}


ComponentInstanceData
CADReader::componentinstantiation (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	ComponentInstanceData data;
    data.id = XMLString::transcode(element->getAttribute(X("id")));
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)(child));
			}

			//
			// componentproperties
			//
			else if (element_name == "componentproperties")
			{
				data.comp_prop = componentproperties((DOMElement*)(child));
			}

			//
			// registercomponent
			//
			else if (element_name == "registercomponent")
			{
				registercomponent((DOMElement*)(child));
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

	return data;
}


std::string
CADReader::componentinstantiationref (DOMElement* element)
throw(CADReadException)
{
	return XMLString::transcode(element->getAttribute(X("idref")));
}


std::string
CADReader::componentproperties (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	std::string file;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// fileinarchive
			//
			if (element_name == "fileinarchive")
			{
				file = fileinarchive((DOMElement*)(child));
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

	return file;
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
			element_name = XMLString::transcode(child->getNodeName());

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
			element_name = XMLString::transcode(child->getNodeName());

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
			element_name = XMLString::transcode(child->getNodeName());

			//
			// usesport
			//
			if (element_name == "usesport")
			{
				interface_connection.use = usesport((DOMElement*)(child));
			}

			//
			// providesport
			//
			else if (element_name == "providesport")
			{
				interface_connection.provide = providesport((DOMElement*)(child));
			}

			//
			// componentsupportedinterface
			//
			else if (element_name == "componentsupportedinterface")
			{
				interface_connection.provide.ref = componentsupportedinterface((DOMElement*)(child));
			}

			//
			// existinginterface
			//
			else if (element_name == "existinginterface")
			{
				interface_connection.provide.ref = existinginterface((DOMElement*)(child));
			}

			//
			// homeinterface
			//
			else if (element_name == "homeinterface")
			{
				interface_connection.provide.ref = homeinterface((DOMElement*)(child));
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
			element_name = XMLString::transcode(child->getNodeName());
		
			//
			// connectinterface
			//
			if (element_name == "connectinterface")
			{
				connectinterface((DOMElement*)(child));
			}

			//
			// connectevent
			//
			if (element_name == "connectevent")
			{
				connectevent((DOMElement*)(child));
			}

			//
			// connecthomes
			//
			if (element_name == "connecthomes")
			{
				connecthomes((DOMElement*)(child));
			}

			//
			// extension
			//
			if (element_name == "extension")
			{
				extension((DOMElement*)(child));
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
		text = XMLString::transcode(node->getNodeValue());
	}
    return text;
}


PortData
CADReader::consumesport (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	PortData data;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

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
		text = XMLString::transcode(node->getNodeValue());
	}
	
	DEBUG_OUT2( "CADReader: <description> ", text );
    return text;
}


std::string
CADReader::destination (DOMElement* element)
throw(CADReadException)
{
	std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
		return text;
	}

    // destination was empty
    char hostname[256];
	gethostname(hostname, 256);
    text = hostname;
    return text;
}


std::string
CADReader::emitsidentifier (DOMElement* element)
throw(CADReadException)
{
    std::string text = "";
	DOMNode* node = element->getFirstChild();
	if(node)
	{
		text = XMLString::transcode(node->getNodeValue());
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
			element_name = XMLString::transcode(child->getNodeName());

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
			element_name = XMLString::transcode(child->getNodeName());
		
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
	std::string class_attr = XMLString::transcode(element->getAttribute(X("class")));
	
    //
    // startorder
    //
    if( class_attr == "startorder" )
	{
		std::string id = XMLString::transcode(element->getFirstChild()->getNodeValue());
		data_->start_order_.push_back( id );
	}
}


std::string
CADReader::fileinarchive(DOMElement* element)
throw(CADReadException)
{
	std::string file_name = XMLString::transcode(element->getAttribute(X("name")));
	std::string file = path_ + getFileName( file_name );

	//
	// extract the file
	//
	if (package_->extractFile(file_name, file) != 0)
	{
		NORMAL_ERR2( "CADReader: error during extracting file ", file_name );
		throw CADReadException();
	}

	return file;
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
			element_name = XMLString::transcode(child->getNodeName());
		
			//
			// namingservice
			//
			if (element_name == "namingservice")
			{
				data.kind = NAMING;
				data.name = namingservice((DOMElement*)(child));
			}

			//
			// stringifiedobjectref
			//
			if (element_name == "stringifiedobjectref")
			{
				data.kind = OBJECTREF;
				data.name = stringifiedobjectref((DOMElement*)(child));
			}

			//
			// traderquery
			//
			if (element_name == "traderquery")
			{
				data.kind = TRADER;
				traderquery((DOMElement*)(child));
			}

			//
			// homefinder
			//
			if (element_name == "homefinder")
			{
				data.kind = FINDER;
				data.name = homefinder((DOMElement*)(child));
			}

			//
			// extension
			//
			if (element_name == "extension")
			{
				extension((DOMElement*)(child));
			}
		}

		// get next child
		child = child->getNextSibling();
    }

	return data;
}


std::string
CADReader::homefinder (DOMElement* element)
throw(CADReadException)
{
	return XMLString::transcode(element->getAttribute(X("name")));
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
			element_name = XMLString::transcode(child->getNodeName());

			//
			// homeplacementref
			//
			if (element_name == "homeplacementref")
			{
				data.kind = HOMEID;
				data.name = homeplacementref((DOMElement*)(child));
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


HomeInstanceData
CADReader::homeplacement (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	HomeInstanceData data;
	data.id = XMLString::transcode(element->getAttribute(X("id")));
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

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
				data.file = data_->implementationMap_[componentfileref((DOMElement*)child)];
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
		}

        // get next child
	    child = child->getNextSibling();
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


std::string
CADReader::homeplacementref (DOMElement* element)
throw(CADReadException)
{
	return XMLString::transcode(element->getAttribute(X("idref")));
}


std::string
CADReader::homeproperties (DOMElement* element)
throw(CADReadException)
{
	std::string element_name;
	std::string file;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// fileinarchive
			//
			if (element_name == "fileinarchive")
			{
				file = fileinarchive((DOMElement*)(child));
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

	return file;
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
			element_name = XMLString::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)(child));
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
				HomeInstanceData home_instance = homeplacement((DOMElement*)(child));
				ProcessData process;
				process.host = home_instance.dest;
				process.homes.push_back(home_instance);
				data.processes.push_back(process);
			}

			//
			// executableplacement
			//
			else if (element_name == "executableplacement")
			{
				executableplacement((DOMElement*)(child));
			}

			//
			// processcollocation
			//
			else if (element_name == "processcollocation")
			{
				ProcessData process = processcollocation((DOMElement*)(child));
				data.host = process.host;
				data.processes.push_back(process);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)(child));
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.host = destination((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return data;
}


std::string
CADReader::link (DOMElement* element)
throw(CADReadException)
{
    XMLURL uri(element->getAttribute(X("href")));
    std::string name = XMLString::transcode(uri.getPath());
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

    return name;
}


std::string
CADReader::namingservice (DOMElement* element)
throw(CADReadException)
{
	return XMLString::transcode(element->getAttribute(X("name")));
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
			element_name = XMLString::transcode(child->getNodeName());

			//
			// homeplacement
			//
			if (element_name == "homeplacement")
			{
				HomeInstanceData home = homeplacement((DOMElement*)child);
				if(home.file.empty())
				{
					// extension, use existing home
					data_->existing_homes_.push_back(home);
				}
				else
				{
					ProcessData process;
					process.host = home.dest;
					process.homes.push_back(home);
					HostData host;
					host.host = process.host;
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
				HostData host;
				host.host = process.host;
				host.processes.push_back(process);
				data_->hosts_.push_back(host);
			}

			//
			// hostcollocation
			//
			else if (element_name == "hostcollocation")
			{
				data_->hosts_.push_back(hostcollocation((DOMElement*)child));
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
			element_name = XMLString::transcode(child->getNodeName());

			//
			// usagename
			//
			if (element_name == "usagename")
			{
				data.usage_name = usagename((DOMElement*)(child));
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
				HomeInstanceData home_instance = homeplacement((DOMElement*)(child));
				data.host = home_instance.dest;
				data.homes.push_back(home_instance);
			}

			//
			// extension
			//
			else if (element_name == "extension")
			{
				extension((DOMElement*)(child));
			}

			//
			// destination
			//
			else if (element_name == "destination")
			{
				data.host = destination((DOMElement*)(child));
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
		text = XMLString::transcode(node->getNodeValue());
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
			element_name = XMLString::transcode(child->getNodeName());

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
		text = XMLString::transcode(node->getNodeValue());
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
			element_name = XMLString::transcode(child->getNodeName());

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


std::string
CADReader::registercomponent (DOMElement* element)
throw(CADReadException)
{
	// todo fix
	std::string element_name;
	std::string naming;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());

			//
			// emitsidentifier
			//
			if (element_name == "emitsidentifier")
			{
				emitsidentifier((DOMElement*)(child));
			}

			//
			// providesidentifier
			//
			else if (element_name == "providesidentifier")
			{
				providesidentifier((DOMElement*)(child));
			}

			//
			// publishesidentifier
			//
			else if (element_name == "publishesidentifier")
			{
				publishesidentifier((DOMElement*)(child));
			}

			//
			// registerwithnaming
			//
			else if (element_name == "registerwithnaming")
			{
				naming = registerwithnaming((DOMElement*)(child));
			}

			//
			// registerwithtrader
			//
			else if (element_name == "registerwithtrader")
			{
				registerwithtrader((DOMElement*)(child));
			}
		}

        // get next child
	    child = child->getNextSibling();
	}

	return naming;
}


std::string
CADReader::registerwithhomefinder (DOMElement* element)
throw(CADReadException)
{
	return XMLString::transcode(element->getAttribute(X("name")));
}


std::string
CADReader::registerwithnaming (DOMElement* element)
throw(CADReadException)
{
	return XMLString::transcode(element->getAttribute(X("name")));
}


std::string
CADReader::registerwithtrader (DOMElement* element)
throw(CADReadException)
{
	// todo more
	return XMLString::transcode(element->getAttribute(X("tradername")));
}


std::string 
CADReader::stringifiedobjectref (DOMElement* element)
throw(CADReadException)
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
		text = XMLString::transcode(node->getNodeValue());
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
		text = XMLString::transcode(node->getNodeValue());
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
			element_name = XMLString::transcode(child->getNodeName());

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
	char* xmlfile = strdup(cadfile.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		NORMAL_ERR2( "CADReader: error during parsing ", cadfile );
        throw CADReadException();
	}
	cad_document_ = parser.getDocument();

	// handle componentassembly
	componentassembly(cad_document_->getDocumentElement());

	// remove assembly descriptor and package
    removeFileOrDirectory(cadfile);
	delete package_;
}


}

