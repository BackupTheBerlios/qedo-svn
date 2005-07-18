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


#include "InstallationParser.h"


bool InstallationParser::init = true; // SAX Initialisation must be done.


// Functions who initialises SAX. The return value is 1 if an exception is caught, 0 else.

int InstallationParser::initialization() {
  try {
    if (init) {
      XMLPlatformUtils::Initialize(); // Initialisation of SAX.
      init = false; // Initialisation not necessary the next time.
    }
    return(0);
  }
  catch (const XMLException& toCatch) { // Initialisation exception caught.
    std::cerr << "Error during initialisation of SAX ! :\n";
    std::cerr << toCatch.getMessage() << "\n";
    return(1);
  }
}


// Constructor. The string parameter sets the xmlFile attribute.

InstallationParser::InstallationParser(std::string filename) {
  xmlFile = filename;
}


// Parsing function who seeks the name of the softpkg element in the
// XML descriptor file of the package. The return value is 1 if the
// initialisation was not correctly made, 2 if there is a XML error in
// the file, 3 if there is a XML fatal error in the file and 4 if the
// file was not found in the current directory, 0 if no problem.

int InstallationParser::parse() {
  if (initialization() == 1) // Problem during the initialisation.
    return(1);

  SAXParser* parser = new SAXParser();
  parser->setDoValidation(true);
  parser->setDoNamespaces(true);

  InstallationSAXHandler* handler = new InstallationSAXHandler();
  parser->setDocumentHandler(handler);
  parser->setErrorHandler(handler);
  try {
    const char* file = xmlFile.c_str(); // Name of the descriptor file in the current directory.
    parser->parse(file); // Parsing procedure.
    handler->get_pkgname(pkgname); // Result of the parsing.
	handler->get_pkgUUID(pkgUUID);
	handler->get_implementations(codefiles); // Result of the parsing.
  }
  catch (const XMLException& toCatch) { // File not found for the parsing.
    std::cerr << "\nFile not found : '" << xmlFile << "'\n";
    std::cerr << "Exception message is : \n" << toCatch.getMessage() << "\n";
    return(4);
  }
  int err = handler->get_error(); // The error codes are got from the handler object.
  delete(handler); // Object deleted.
  delete(parser); // Object deleted.
  return(err); // 0, 2 or 3 is returned.
}


// Parsing function who seeks the name of the fileinarchive element of each
// code element in the implementation element which uuid is specified by the
// string parameter in the XML descriptor file of the package. The return value
// is 1 if the initialisation was not correctly made, 2 if there is a XML error
// in the file, 3 if there is a XML fatal error in the file, 4 if the specified
// uuid was not found in the file and 5 if the file was not found in the current
// directory, 0 if no problem.

/*int InstallationParser::parse() 
{
  if (initialization() == 1) // Problem during the initialisation.
    return(1);

  SAXParser* parser = new SAXParser();
  parser->setDoValidation(true);
  parser->setDoNamespaces(true);

  InstallationSAXHandler* handler = new InstallationSAXHandler();
  parser->setDocumentHandler(handler);
  parser->setErrorHandler(handler);
  try 
  {
    const char* file = xmlFile.c_str(); // Name of the descriptor file in the current directory.
    parser->parse(file); // Parsing procedure.
    handler->get_code_files(codefiles); // Result of the parsing.
  }
  catch (const XMLException& toCatch) 
  { // File not found for the parsing.
    std::cerr << "\nFile not found : '" << xmlFile << "'\n";
    std::cerr << "Exception message is : \n" << toCatch.getMessage() << "\n";
    return(5);
  }
  int err = handler->get_error(); // The error codes are got from the handler object.
  delete(handler); // Object deleted.
  delete(parser); // Object deleted.
  return(err); // 0, 2, 3 or 4 is returned.
}
*/

// Returns the codefiles attribute.

void InstallationParser::get_code_files(CodeList& list) 
{
  list = codefiles;
}


// Returns the pkgname attribute.

void InstallationParser::get_pkgname(std::string& name) 
{
	name = pkgname;
}

void InstallationParser::get_pkgUUID(std::string& uuid) 
{
	uuid = pkgUUID;
}