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

// AssemblySAXHandler.h: Schnittstelle für die Klasse AssemblySAXHandler.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASSEMBLYSAXHANDLER_H__602D0CB5_ED8F_42F0_AAD4_5BF45BFC0594__INCLUDED_)
#define AFX_ASSEMBLYSAXHANDLER_H__602D0CB5_ED8F_42F0_AAD4_5BF45BFC0594__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AssemblyStructures.h"
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/sax/AttributeList.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/sax/SAXException.hpp>

////////////////////////////////////// AssemblySAXHandler //////////////////////////////////////////

class AssemblySAXHandler: public HandlerBase 
{
private:

	//bool member functions are used in startElement and endElement procedures.
    bool nodefound; 
	bool assfound;
	bool executableplacementfound;
	bool destinationfound;
	bool fileinarchivefound;
	bool homeplacementfound;
	bool connectinterfacefound;
	bool usesfound;
	bool providesfound;
	bool usesidentifierfound;
	bool providesidentifierfound;
	bool connecteventfound;
	bool consumesportfound;
	bool secondportfound;
	bool consumesidentifierfound;
	bool secondidentifierfound;
	bool componentfilefound;
	bool rulefound;
	bool conditionfound;
	bool actionfound;
	bool homepropertiesfound;

	std::string _assembly_file_name;// to store the name of the assembly package.

	std::string _assembly_id;
	std::string _nodename;
	std::string _softpkg_zip;
	std::string _softpkg;
	std::string _softpkg_id;
	std::string _impl_uuid;
	std::string _softpkgname;
	std::string _connection_id;
	std::string _first_id;
	std::string _second_id;
	std::string _first_comp_ref;	
	std::string _str;
	std::string _rule_name;
	std::string _language;
	std::string _interval;
	std::string _propertyfile;

	EventPort _port_type;
	int XMLerror; // Error code. Used in the InstallationParser class.
	InstallationMapList _map; // List of the code files of the
                              // component implementation.
	ComponentInstantiationMapList _comp_map;
	SoftPkgList _softpkglist;
	ComponentInstanceList _comp_inst_list;
	RuleList _rules;
	ConnectionInterfaces _connect_interfaces;
	ConnectEvents _connect_events;
	Condition _condition;
	Action _action;

public:
	AssemblySAXHandler(std::string);
	virtual ~AssemblySAXHandler();

	void get_installation_map (InstallationMapList&); // Returns the list of the node names from the installation map.
    
	void get_comp_instantiation_map (ComponentInstantiationMapList& map);                                // Used in the InstallationParser class.
	
	void get_softpkg_list (SoftPkgList&);

	void get_connection_interfaces(ConnectionInterfaces&);

	void get_connect_events(ConnectEvents&);

    void get_assembly_file_name(std::string&) const; // Returns the name of the assembly file.

	void get_assembly_id (std::string&);

    int get_error(); // Returns the XMLerror attribute.

    // Re-definition of four SAX procedures.

    void startElement(const XMLCh* const, AttributeList&);

    void endElement(const XMLCh* const);

	void characters(const XMLCh* const chars , const unsigned int length);

    void error(const SAXParseException&);

    void fatalError(const SAXParseException&);

};

#endif // !defined(AFX_ASSEMBLYSAXHANDLER_H__602D0CB5_ED8F_42F0_AAD4_5BF45BFC0594__INCLUDED_)
