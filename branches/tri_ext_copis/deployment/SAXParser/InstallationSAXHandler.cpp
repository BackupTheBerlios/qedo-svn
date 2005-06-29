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


#include "InstallationSAXHandler.h"



InstallationSAXHandler::~InstallationSAXHandler()
{};

// Constructor. The string parameter is used to set the uuid attribute.

InstallationSAXHandler::InstallationSAXHandler() 
{
	softpkgfound = false;
	uuidfound = false;
	implfound = false;
	codefound = false;
	entrypointfound = false;
	//uuid = id;
	//parsetype = InstallationSAXHandler::CODEF;
	XMLerror = 0;
}


// Returns the list of the code files. Used in the InstallationParser class.

void InstallationSAXHandler::get_implementations(CodeList& codelist)
{
  codelist = implementations;
}


// Returns the pkgname attribute.

void InstallationSAXHandler::get_pkgname(std::string& name) 
{
	name = pkgname;
}

void InstallationSAXHandler::get_pkgversion(std::string& version) 
{
	version = pkgversion;
}

void InstallationSAXHandler::get_pkgUUID(std::string& uuid) 
{
	uuid = pkgUUID;
}

// Returns the XMLerror attribute.

int InstallationSAXHandler::get_error() 
{
  return(XMLerror);
}  


// Re-definition of four SAX procedures.

void InstallationSAXHandler::startElement(const XMLCh* const name, AttributeList& attributes) 
{
  //if (parsetype == CODEF) // To find the code files of the component.
  //{
    std::string stringname(XMLString::transcode(name));
	std::string softpkg = "softpkg";
    std::string impl = "implementation";
    std::string code = "code";
	std::string entrypoint = "entrypoint";
    std::string file = "fileinarchive";

	if (stringname == softpkg)
	{
		pkgname = XMLString::transcode(attributes.getValue("name"));
		pkgversion = XMLString::transcode(attributes.getValue("version"));
		pkgUUID = pkgname + "." + pkgversion;
	}

    if ((stringname == impl) && (!implfound))
    {
		implfound = true;
		_uuid = XMLString::transcode(attributes.getValue("id"));
    }

    if ((stringname == code) && (implfound) && (!codefound))
    {
		codefound = true;
		_code_type = XMLString::transcode(attributes.getValue("type"));	
    }

    if ((stringname == file) && (implfound) && (codefound))
    {
      _file_name = XMLString::transcode(attributes.getValue("name"));
      //implementations.push_back(codefile);
    }

	if ((stringname == entrypoint) && (implfound) && (codefound) && (!entrypointfound) )
    {
		entrypointfound = true;
		//_entry_point = XMLString::transcode(attributes.getValue("name"));
      //implementations.push_back(codefile);
    }
  //}
  //else if (parsetype == PKGNAME) // To find the name of the component.
  /*{
    std::string stringname(XMLString::transcode(name));
    std::string name = "softpkg";
    if (stringname == name)
	{
		pkgname = XMLString::transcode(attributes.getValue("name"));
		pkgversion = XMLString::transcode(attributes.getValue("version"));
		pkgUUID = pkgname + "." + pkgversion;
	}
	}*/
}

void InstallationSAXHandler::characters(const XMLCh* const chars , const unsigned int length)
{
   //  check flag: is contents of value or description element?
   if (entrypointfound == true)
   {
		_entry_point = XMLString::transcode(chars);
		Implementation* implementation_ = new Implementation (_uuid, _code_type, _file_name, _entry_point);
		implementations.push_back (implementation_);
   }
}


void InstallationSAXHandler::endElement(const XMLCh* const name) 
{
    std::string stringname(XMLString::transcode(name)); // Name of the element which end is reached.
    std::string impl = "implementation";
    std::string code = "code";
    std::string file = "fileinarchive";
	std::string entrypoint = "entrypoint";
    std::string end  = "softpkg";
    if (stringname == impl)
		implfound = false;
    if (stringname == code)
		codefound = false;
	if (stringname == entrypoint)
		entrypointfound = false;
    if ( (stringname == end) && ( implementations.empty() ) )
      XMLerror = 4; // The uuid specified by the uuid parameter
                   // was not found in the file.
}


void InstallationSAXHandler::error(const SAXParseException& e) {
  XMLerror = 2;
  std::cerr << "\nError at file " << XMLString::transcode(e.getSystemId());
  std::cerr << ", line " << e.getLineNumber();
  std::cerr << ", char " << e.getColumnNumber();
  std::cerr << "\n	 Message: " << XMLString::transcode(e.getMessage()) << '\n';

}


void InstallationSAXHandler::fatalError(const SAXParseException& e) {
  XMLerror = 3;
  std::cerr << "\nXML Fatal Error at file " << XMLString::transcode(e.getSystemId());
  std::cerr << ", line " << e.getLineNumber();
  std::cerr << ", char " << e.getColumnNumber();
  std::cerr << "\n    Message: " << XMLString::transcode(e.getMessage()) << '\n';

}