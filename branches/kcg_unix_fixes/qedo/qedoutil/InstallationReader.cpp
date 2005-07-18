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

#include "InstallationReader.h"
#include "Output.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


static char rcsid[] UNUSED = "$Id: InstallationReader.cpp,v 1.7 2003/11/28 13:08:27 boehme Exp $";


namespace Qedo {


InstallationReader::InstallationReader()
{
}


InstallationReader::~InstallationReader()
{
}


void
InstallationReader::implementation (DOMElement* element)
throw(InstallationReadException)
{
	std::string element_name;
	ComponentImplementationData data;
	data.uuid = Qedo::transcode(element->getAttribute(X("id")));
	data.installation_dir = Qedo::transcode(element->getAttribute(X("installation")));
	data.csd = Qedo::transcode(element->getAttribute(X("csd")));
	data.assembly.cad = Qedo::transcode(element->getAttribute(X("cad")));
	DOMElement* child_element;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());
			child_element = (DOMElement*)child;

			//
			// servants
			//
			if (element_name == "servants")
			{
				data.servant_module = Qedo::transcode(child_element->getAttribute(X("code")));
				data.servant_entry_point = Qedo::transcode(child_element->getAttribute(X("entry")));
			}

			//
			// business
			//
			else if (element_name == "business")
			{
				data.executor_module = Qedo::transcode(child_element->getAttribute(X("code")));
				data.executor_entry_point = Qedo::transcode(child_element->getAttribute(X("entry")));
			}

			//
			// valuetype
			//
			else if (element_name == "valuetype")
			{
				ValuetypeData vdata;
				vdata.repid = Qedo::transcode(child_element->getAttribute(X("repid")));
				vdata.location.file = Qedo::transcode(child_element->getAttribute(X("code")));
				data.valuetypes.push_back(vdata);
			}
		}

		// get next child
		child = child->getNextSibling();
	}
		
	//
	// add new ComponentImplementation
	//
	data_->push_back( data );
}


void
InstallationReader::deployed (DOMElement* element)
throw(InstallationReadException)
{
	std::string element_name;
    DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// implementation
			//
			if (element_name == "implementation")
			{
				implementation((DOMElement*)child);
			}
		}

		// get next child
		child = child->getNextSibling();
    }
}


void 
InstallationReader::read(std::string file, ComponentImplementationDataVector* data)
throw(InstallationReadException)
{
	data_ = data;

	//
	// is there already a deployment file ?
	//
	if ( ! checkExistence(file.c_str(), IS_FILE)) 
	{
		std::ofstream deployment_file(file.c_str());
		if ( ! deployment_file)
		{
			NORMAL_ERR2( "InstallationReader: cannot open file ", file );
			throw InstallationReadException();
		}
		deployment_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
		deployment_file << "<deployed>\n";
		deployment_file << "</deployed>" << std::endl;
		deployment_file.close();

		return;
	}
	
	//
	// parse the descriptor file
    //
    if( parser_.parse( const_cast<char*>(file.c_str()) ) != 0 ) 
	{
		NORMAL_ERR( "InstallationReader: error during XML parsing" );
        throw InstallationReadException();
	}
	document_ = parser_.getDocument();

	deployed(document_->getDocumentElement());
}


void
InstallationReader::add( std::string file, ComponentImplementationData* data )
throw(InstallationReadException)
{
	//
	// parse the descriptor file
    //
    if( parser_.parse( const_cast<char*>(file.c_str()) ) != 0 ) 
	{
		NORMAL_ERR( "InstallationReader: error during XML parsing" );
        throw InstallationReadException();
	}
	document_ = parser_.getDocument();
	
	//
	// add the new implementation
	//
	DOMElement* root = document_->getDocumentElement();
	root->appendChild(document_->createTextNode(X("\n    ")));

	// implementation
	DOMElement* implem = document_->createElement(X("implementation"));
	implem->setAttribute(X("id"), X(data->uuid.c_str()));
	implem->setAttribute(X("installation"), X(data->installation_dir.c_str()));
	if(data->csd.length())
	{
		implem->setAttribute(X("csd"), X(data->csd.c_str()));
	}
	if(data->assembly.cad.length())
	{
		implem->setAttribute(X("cad"), X(data->assembly.cad.c_str()));
	}
	
	// servants
	implem->appendChild (document_->createTextNode(X("\n        ")));
	DOMElement* servants = document_->createElement(X("servants"));
	servants->appendChild(document_->createTextNode(X("\n        ")));
	servants->setAttribute(X("code"), X(data->servant_module.c_str()));
	servants->setAttribute(X("entry"), X(data->servant_entry_point.c_str()));
	implem->appendChild (servants);
	
	// business
	implem->appendChild (document_->createTextNode(X("\n        ")));
	DOMElement* business = document_->createElement(X("business"));
	business->appendChild(document_->createTextNode(X("\n        ")));
	business->setAttribute(X("code"), X(data->executor_module.c_str()));
	business->setAttribute(X("entry"), X(data->executor_entry_point.c_str()));
	implem->appendChild (business);

	// valuetypes
	std::vector < ValuetypeData > ::const_iterator iter;
	for(iter = data->valuetypes.begin();
		iter != data->valuetypes.end();
		iter++)
	{
		implem->appendChild (document_->createTextNode(X("\n        ")));
		DOMElement* valuetype = document_->createElement(X("valuetype"));
		valuetype->appendChild(document_->createTextNode(X("\n        ")));
		valuetype->setAttribute(X("repid"), X(((*iter).repid).c_str()));
		valuetype->setAttribute(X("code"), X(((*iter).location.file).c_str()));
		implem->appendChild (valuetype);
	}

	implem->appendChild (document_->createTextNode(X("\n    ")));
	root->appendChild (implem);
	root->appendChild (document_->createTextNode(X("\n")));

	//
	// write the new list
	//
	try
    {
		//
		// get a serializer, an instance of DOMWriter
		//
		XMLCh tempStr[100];
		XMLString::transcode("LS", tempStr, 99);
		DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
		DOMWriter *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

		if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
		{
			theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}

		XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(file.c_str());

		//
		// do the serialization through DOMWriter::writeNode();
		//
		theSerializer->writeNode(myFormTarget, *document_);

		delete theSerializer;
		delete myFormTarget;
	}
    catch (XMLException& e)
	{
		std::cerr << "An error occurred during creation of output transcoder. Msg is:" << std::endl;
		std::cerr << StrX(e.getMessage()) << std::endl;
    }
}


void 
InstallationReader::remove( std::string file, const char* uuid )
throw(InstallationReadException)
{
	//
	// parse the descriptor file
    //
    if( parser_.parse( const_cast<char*>(file.c_str()) ) != 0 ) 
	{
		NORMAL_ERR( "InstallationReader: error during XML parsing" );
        throw InstallationReadException();
	}
	document_ = parser_.getDocument();
	
	//
	// remove implementation
	//
	DOMElement* root = document_->getDocumentElement();
	std::string element_name;
    DOMNode* child = root->getFirstChild();
	DOMNode* text_child;
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = Qedo::transcode(child->getNodeName());

			//
			// implementation
			//
			if (element_name == "implementation")
			{
				if( Qedo::transcode(((DOMElement*)child)->getAttribute(X("id"))) == uuid )
				{
					root->removeChild( text_child );
					root->removeChild( child );
				}

				break;
			}
		}

		// get next child
		text_child = child;
		child = child->getNextSibling();
    }

	//
	// write the new list
	//
	try
    {
		//
		// get a serializer, an instance of DOMWriter
		//
		XMLCh tempStr[100];
		XMLString::transcode("LS", tempStr, 99);
		DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
		DOMWriter *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

		if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
		{
			theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}

		XMLFormatTarget *myFormTarget = new LocalFileFormatTarget(file.c_str());

		//
		// do the serialization through DOMWriter::writeNode();
		//
		theSerializer->writeNode(myFormTarget, *document_);

		delete theSerializer;
		delete myFormTarget;
	}
    catch (XMLException& e)
	{
		std::cerr << "An error occurred during creation of output transcoder. Msg is:" << std::endl;
		std::cerr << StrX(e.getMessage()) << std::endl;
    }
}


}

