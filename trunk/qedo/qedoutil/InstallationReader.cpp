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
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>


static char rcsid[] UNUSED = "$Id: InstallationReader.cpp,v 1.1 2003/09/26 08:31:46 neubauer Exp $";


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
	data.uuid = XMLString::transcode(element->getAttribute(X("id")));
	data.installation_dir = XMLString::transcode(element->getAttribute(X("installation")));
	data.csd = XMLString::transcode(element->getAttribute(X("csd")));
	data.assembly.cad = XMLString::transcode(element->getAttribute(X("cad")));
	DOMElement* child_element;
	DOMNode* child = element->getFirstChild();
	while (child != 0)
	{
		if (child->getNodeType() == DOMNode::ELEMENT_NODE)
		{
			element_name = XMLString::transcode(child->getNodeName());
			child_element = (DOMElement*)child;

			//
			// servants
			//
			if (element_name == "servants")
			{
				data.servant_module = XMLString::transcode(child_element->getAttribute(X("code")));
				data.servant_entry_point = XMLString::transcode(child_element->getAttribute(X("entry")));
			}

			//
			// business
			//
			else if (element_name == "business")
			{
				data.executor_module = XMLString::transcode(child_element->getAttribute(X("code")));
				data.executor_entry_point = XMLString::transcode(child_element->getAttribute(X("entry")));
			}

			//
			// valuetype
			//
			else if (element_name == "valuetype")
			{
				ValuetypeData vdata;
				vdata.repid = XMLString::transcode(child_element->getAttribute(X("repid")));
				vdata.location.file = XMLString::transcode(child_element->getAttribute(X("code")));
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
			element_name = XMLString::transcode(child->getNodeName());

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
			std::cerr << "..... Cannot open file " << file << std::endl;
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
	DOMXMLParser parser;
	char* xmlfile = strdup(file.c_str());
    if ( parser.parse( xmlfile ) != 0 ) 
	{
		std::cerr << "Error during XML parsing" << std::endl;
        throw InstallationReadException();
	}
	document_ = parser.getDocument();

	deployed(document_->getDocumentElement());
}


void
InstallationReader::add( std::string file, ComponentImplementationData* data )
throw(InstallationReadException)
{
	//
	// parse the descriptor file
    //
	DOMXMLParser parser;
    if (parser.parse(strdup(file.c_str())) != 0) 
	{
		std::cerr << "Error during parsing " << file << std::endl;
        throw InstallationReadException();
	}

	//
	// add the new implementation
	//
	DOMDocument* doc = parser.getDocument();
	DOMElement* root = doc->getDocumentElement();
	root->appendChild(doc->createTextNode(X("\n    ")));

	// implementation
	DOMElement* implem = doc->createElement(X("implementation"));
	implem->setAttribute(X("id"), X(data->uuid.c_str()));
	implem->setAttribute(X("installation"), X(data->installation_dir.c_str()));
	if(data->csd != "")
	{
		implem->setAttribute(X("csd"), X(data->csd.c_str()));
	}
	if(data->assembly.cad != "")
	{
		implem->setAttribute(X("cad"), X(data->assembly.cad.c_str()));
	}
	
	// servants
	implem->appendChild (doc->createTextNode(X("\n        ")));
	DOMElement* servants = doc->createElement(X("servants"));
	servants->appendChild(doc->createTextNode(X("\n        ")));
	servants->setAttribute(X("code"), X(data->servant_module.c_str()));
	servants->setAttribute(X("entry"), X(data->servant_entry_point.c_str()));
	implem->appendChild (servants);
	
	// business
	implem->appendChild (doc->createTextNode(X("\n        ")));
	DOMElement* business = doc->createElement(X("business"));
	business->appendChild(doc->createTextNode(X("\n        ")));
	business->setAttribute(X("code"), X(data->executor_module.c_str()));
	business->setAttribute(X("entry"), X(data->executor_entry_point.c_str()));
	implem->appendChild (business);

	// valuetypes
	std::vector < ValuetypeData > ::const_iterator iter;
	for(iter = data->valuetypes.begin();
		iter != data->valuetypes.end();
		iter++)
	{
		implem->appendChild (doc->createTextNode(X("\n        ")));
		DOMElement* valuetype = doc->createElement(X("valuetype"));
		valuetype->appendChild(doc->createTextNode(X("\n        ")));
		valuetype->setAttribute(X("repid"), X(((*iter).repid).c_str()));
		valuetype->setAttribute(X("code"), X(((*iter).location.file).c_str()));
		implem->appendChild (valuetype);
	}

	implem->appendChild (doc->createTextNode(X("\n    ")));
	root->appendChild (implem);
	root->appendChild (doc->createTextNode(X("\n")));

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
		theSerializer->writeNode(myFormTarget, *doc);

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

