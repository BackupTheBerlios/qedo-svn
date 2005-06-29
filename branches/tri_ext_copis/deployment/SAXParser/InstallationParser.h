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
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>


class InstallationParser {
  private:
    std::string xmlFile; // Name of the descriptor file extracted from the
                    // package in the current directory.

	CodeList codefiles; // Attribute set at the end of the second parse function.
                              // It is the result of the second parsing, the one that
                              // attempts to find the pathname within the package of
                              // all the code files that are associated to the uuid.

    std::string pkgname; // Attribute set at the end of the first parse function. It is the
                    // result of the first parsing, the one that attempts to find the
                    // name of the softpkg element in the XML descriptor file.
	std::string pkgUUID;

    static bool init; // Used by the initialization function. False if the
                      // initialization of SAX has already been made, true else.

    static int initialization(); // Functions who initialises SAX. The return value is
                                 // 1 if an error is caught, 0 else.

  public:
	  InstallationParser(std::string); // Constructor. The string parameter sets the xmlFile attribute.

    int parse(); // Parsing function who seeks the name of the softpkg element in the
                 // XML descriptor file of the package. The return value is 1 if the
                 // initialisation was not correctly made, 2 if there is a XML error in
                 // the file, 3 if there is a XML fatal error in the file and 4 if the
                 // file was not found in the current directory, 0 if no problem.

    //int parse(std::string); // Parsing function who seeks the name of the fileinarchive
                       // element of each code element in the implementation element
                       // which uuid is specified by the string parameter in the XML
                       // descriptor file of the package. The return value is 1 if the
                       // initialisation was not correctly made, 2 if there is a XML
                       // error in the file, 3 if there is a XML fatal error in the
                       // file, 4 if the specified uuid was not found in the file and
                       // 5 if the file was not found in the current directory, 0 if no
                       // problem.

	void get_code_files( CodeList& ); // Returns the codefiles attribute.
	void get_pkgUUID (std::string&);

    void get_pkgname( std::string& ); // Returns the pkgname attribute.
	

};
