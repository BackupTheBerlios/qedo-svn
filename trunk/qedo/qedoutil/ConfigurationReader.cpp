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

#include "ConfigurationReader.h"
#include "Output.h"
#include "DOMXMLParser.h"

static char rcsid[] UNUSED = "$Id: ConfigurationReader.cpp,v 1.6 2003/11/14 18:08:34 boehme Exp $";


namespace Qedo {


ConfigurationReader* ConfigurationReader::instance_ = 0;


ConfigurationReader*
ConfigurationReader::instance()
{
	if (! instance_ )
		instance_ = new ConfigurationReader();

	return instance_;
}


ConfigurationReader::ConfigurationReader()
{
	// Get the QEDO environment variable
	std::string qedo_config = Qedo::getEnvironment ("QEDO");

	if (qedo_config == "")
	{
		NORMAL_OUT ("ConfigurationReader: Warning: QEDO environment varibale not set or empty");
#ifdef _WIN32
		qedo_config = "C:\\etc\\";
#else
		qedo_config = "/etc/";
#endif
		NORMAL_OUT2 ("ConfigurationReader: Using default path ", qedo_config.c_str());
	}
	else
	{
#ifdef _WIN32
		qedo_config += "\\etc\\Qedo.conf";
#else
		qedo_config += "/etc/Qedo.conf";
#endif
	}

	DEBUG_OUT2 ("ConfigurationReader: Parsing Qedo configuration file ", qedo_config.c_str());

	broken_config_file_ = true;
	if( !isFile(qedo_config) )
	{
		DEBUG_OUT ("ConfigurationReader: no configuration file");
		return;
	}

	std::string file_name (qedo_config.c_str());

    if (parser_.parse (const_cast<char*>(qedo_config.c_str())) != 0) 
	{
		NORMAL_ERR ("ConfigurationReader: Error during parsing configuration file");
        return;
	}

	config_top_ = parser_.getDocument()->getDocumentElement();

	broken_config_file_ = false;
}

std::string
ConfigurationReader::lookup_config_value (const std::string& name)
{
	if (broken_config_file_)
		return "";

	DEBUG_OUT2 ("ConfigurationReader: lookup_config_value() called for name ", name);

	const std::string delims("/");
	std::string::size_type begIdx, endIdx;

	// start at 0
	begIdx = name.find_first_not_of(delims);

	DOMElement* current_element = config_top_;

	while ( begIdx != std::string::npos )
	{

		// search the end of the path name
		endIdx = name.find_first_of ( delims, begIdx );

		if ( endIdx == std::string::npos )
		{
			// last element must be the element name
			std::string tmp_name  = name.substr(begIdx);

			// Resolve config value in the current section
			DOMNodeList* value_list = current_element->getChildNodes();
			std::string s;

			for (unsigned int i = 0; i < value_list->getLength(); i++)
			{
				DOMNode* the_item = value_list->item (i);

				// Test whether we have a CONFIGVALUE element, if not go to next element
				s = Qedo::transcode (the_item->getNodeName());
				if ( s != "CONFIGVALUE")
				{
					continue;
				}

				DOMElement* the_element = (DOMElement*)the_item;

				s = Qedo::transcode (the_element->getAttribute(X("name")));

				if (tmp_name == s)
				{
					current_element = the_element;
					break;
				}
				else
				{
					current_element = 0;
					continue;
				}
			}

			if (! current_element)
				return "";

			s = Qedo::transcode (current_element->getAttribute(X("value")));

			return s;
		}
		else
		{
			// we got a path element, search for the section
			std::string tmp_name  = name.substr(begIdx,endIdx-begIdx);

			DOMNodeList* section_list = current_element->getChildNodes();
			
			// Search sections
			for (unsigned int i = 0; i < section_list->getLength(); i++)
			{
				DOMNode* the_item = section_list->item (i);

				// Test whether we have a SECTION element, if not go to next element
				std::string s = Qedo::transcode (the_item->getNodeName());

				if ( s != "SECTION")
				{
					continue;
				}

				DOMElement* the_element = (DOMElement*)the_item;

				s = Qedo::transcode (the_element->getAttribute(X("name")));

				if ( tmp_name == s )
				{
					current_element = the_element;
					break;
				}
				else
				{
					current_element = 0;
					continue;
				}
			}

			// If not found
			if (! current_element)
				return "";

		}

		begIdx = name.find_first_not_of( delims, endIdx);
	}

	assert(0);
}

std::string
ConfigurationReader::lookup_config_value (const char* name)
{
	return this->lookup_config_value(std::string(name));
}


} // namespace Qedo
