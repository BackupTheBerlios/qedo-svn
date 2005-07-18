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

// AssemblyParser.h: Schnittstelle für die Klasse AssemblyParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSEMBLYPARSER_H__44F25155_8B9E_4F07_8C53_E4C109E6EEA2__INCLUDED_)
#define AFX_ASSEMBLYPARSER_H__44F25155_8B9E_4F07_8C53_E4C109E6EEA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AssemblySAXHandler.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/SAXParser.hpp>

class AssemblyParser  
{
private:

	std::string _assembly_id;
    std::string xmlFile; // Name of the descriptor file extracted from the
                    // package in the current directory.

	InstallationMapList _map; 
	ComponentInstantiationMapList _comp_map;
	ConnectionInterfaces _connections;
	ConnectEvents _connect_events;
	SoftPkgList _softpkglist;

    static bool init; // Used by the initialization function. False if the
                      // initialization of SAX has already been made, true else.

    static int initialization(); // Functions who initialises SAX. The return value is
                                 // 1 if an error is caught, 0 els
public:
	AssemblyParser(std::string);
	virtual ~AssemblyParser();

    int parse(); // Parsing function who seeks the name of the softpkg element in the
                 // XML descriptor file of the package. The return value is 1 if the
                 // initialisation was not correctly made, 2 if there is a XML error in
                 // the file, 3 if there is a XML fatal error in the file and 4 if the
                 // file was not found in the current directory, 0 if no problem.

	void get_installation_map (InstallationMapList&) const;
	void get_comp_instantiation_map (ComponentInstantiationMapList& map) const;
	void get_connection_interfaces (ConnectionInterfaces& connections) const;
	void get_connect_events(ConnectEvents&) const;
	void get_assembly_id (std::string&) const;
	void get_softpkg_list (SoftPkgList&) const;
	

};

#endif // !defined(AFX_ASSEMBLYPARSER_H__44F25155_8B9E_4F07_8C53_E4C109E6EEA2__INCLUDED_)
