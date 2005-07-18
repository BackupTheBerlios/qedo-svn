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

// AssemblyParser.cpp: Implementierung der Klasse AssemblyParser.
//
//////////////////////////////////////////////////////////////////////

#include "AssemblyParser.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

AssemblyParser::AssemblyParser(std::string filename) 
{
	 xmlFile = filename;
}

AssemblyParser::~AssemblyParser()
{

}

bool AssemblyParser::init = true; // SAX Initialisation must be done.


// Functions who initialises SAX. The return value is 1 if an exception is caught, 0 else.

int AssemblyParser::initialization() 
{
  try 
  {
    if (init) 
	{
      XMLPlatformUtils::Initialize(); // Initialisation of SAX.
      init = false; // Initialisation not necessary the next time.
    }
    return(0);
  }
  catch (const XMLException& toCatch) 
  { // Initialisation exception caught.
    std::cerr << "Error during initialisation of SAX ! :\n";
    std::cerr << toCatch.getMessage() << "\n";
    return(1);
  }
}

int AssemblyParser::parse() 
{
  if (initialization() == 1) // Problem during the initialisation.
    return(1);

  SAXParser* parser = new SAXParser();
  parser->setDoValidation(true);
  //parser->setDoValidation(false);
  parser->setDoNamespaces(true);

  AssemblySAXHandler* handler = new AssemblySAXHandler(xmlFile);
  parser->setDocumentHandler(handler);
  parser->setErrorHandler(handler);
  try 
  {
    const char* file = xmlFile.c_str(); // Name of the descriptor file in the current directory.
    parser->parse(file); // Parsing procedure.
    handler->get_installation_map (_map); // Result of the parsing.
	handler->get_comp_instantiation_map(_comp_map);
	handler->get_assembly_id (_assembly_id);
	handler->get_connection_interfaces (_connections);
	handler->get_connect_events(_connect_events);
	handler->get_softpkg_list (_softpkglist);
  }
  catch (const XMLException& toCatch) 
  { // File not found for the parsing.
    std::cerr << "\nFile not found : '" << xmlFile << "'\n";
    std::cerr << "Exception message is : \n" << toCatch.getMessage() << "\n";
    return(4);
  }
  int err = handler->get_error(); // The error codes are got from the handler object.
  delete(handler); // Object deleted.
  delete(parser); // Object deleted.
  return(err); // 0, 2 or 3 is returned.
}

void AssemblyParser::get_connection_interfaces (ConnectionInterfaces& connections) const
{
	connections = _connections;
}

void AssemblyParser::get_connect_events (ConnectEvents& connections) const
{
	connections = _connect_events;
}

void AssemblyParser::get_installation_map (InstallationMapList& map) const
{
	map = _map;
}

void AssemblyParser::get_comp_instantiation_map (ComponentInstantiationMapList& map) const
{
	map = _comp_map;
}
void AssemblyParser::get_assembly_id (std::string& id) const
{
	id = _assembly_id;
}

void AssemblyParser::get_softpkg_list (SoftPkgList& list) const
{
	list = _softpkglist;
}
