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

// AssemblySAXHandler.cpp: Implementierung der Klasse AssemblySAXHandler.
//
//////////////////////////////////////////////////////////////////////

#include "AssemblySAXHandler.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
AssemblySAXHandler::~AssemblySAXHandler()
{
}
//////////////////////////AssemblySAXHandler///////////////////////////////////
AssemblySAXHandler::AssemblySAXHandler(std::string ass_file_name)
{
	_assembly_file_name = ass_file_name;
	XMLerror = 0; 
	nodefound = false;
	assfound = false;
	executableplacementfound = false;
	destinationfound = false;
	fileinarchivefound = false;
	homeplacementfound = false;
	connectinterfacefound = false;
	usesfound = false;
	providesfound = false;
	providesidentifierfound = false;
	usesidentifierfound = false;
	connecteventfound = false;
	consumesportfound = false;
	secondportfound = false;
	consumesidentifierfound = false;
	secondidentifierfound = false;
	componentfilefound = false;
	rulefound = false;
	conditionfound = false;
	actionfound = false;
	homepropertiesfound = false;
}

void AssemblySAXHandler::get_installation_map (InstallationMapList& map)
{
	map = _map;
}

void AssemblySAXHandler::get_comp_instantiation_map (ComponentInstantiationMapList& map)
{
	map = _comp_map;
}

void AssemblySAXHandler::get_softpkg_list (SoftPkgList& softpkglist)
{
	softpkglist = _softpkglist;
}

void AssemblySAXHandler::get_connection_interfaces (ConnectionInterfaces& connections)
{
	connections = _connect_interfaces;
}

void AssemblySAXHandler::get_connect_events (ConnectEvents& connections)
{
	connections = _connect_events;
}

void AssemblySAXHandler::get_assembly_file_name (std::string& filename) const
{
	filename = _assembly_file_name;
}

void AssemblySAXHandler::get_assembly_id (std::string& id)
{
	id = _assembly_id;
}

int AssemblySAXHandler::get_error() {
  return(XMLerror);
}  


// Re-definition of four SAX procedures.

void AssemblySAXHandler::startElement(const XMLCh* const name, AttributeList& attributes) 
{
    std::string stringname(XMLString::transcode(name));
	std::string executableplacement = "executableplacement";
    std::string componentfileref = "componentfileref";
	std::string componentimplref = "componentimplref";
	std::string destination = "destination";
	std::string node = "node";
	std::string fileinarchive = "fileinarchive";
	std::string link = "link";
	std::string homeplacement = "homeplacement";
	std::string componentinstantiation = "componentinstantiation";
	std::string connectinterface = "connectinterface";
	std::string connectevent = "connectevent";
	std::string usesport = "usesport";
	std::string consumesport = "consumesport";
	std::string publishesport = "publishesport";
	std::string emitsport = "emitsport";
	std::string usesidentifier = "usesidentifier";
	std::string providesidentifier = "providesidentifier";
	std::string consumesidentifier = "consumesidentifier";
	std::string emitsidentifier = "emitsidentifier";
	std::string publishesidentifier = "publishesidentifier";
	std::string providesport = "providesport";
	std::string componentinstantiationref = "componentinstantiationref";
	std::string nodename;
	std::string softpkg_zip;
	std::string impl_uuid;
	std::string comp_id;
	std::string componentfile = "componentfile";
	std::string rule = "rule";
	std::string condition = "condition";
	std::string action = "action";
	std::string homeproperties = "homeproperties";

/////////////////////////////// fileinarchive and link Elemente found ////////////////////
	if ( (stringname == componentfile) && (!componentfilefound) )
	{
		componentfilefound = true;
		_softpkg_id = XMLString::transcode(attributes.getValue("id"));
	}
	if ( (stringname == fileinarchive) && ( !fileinarchivefound ) && componentfilefound )
	{
		fileinarchivefound = true;
		_softpkg = XMLString::transcode(attributes.getValue("name"));
	}
	if ( fileinarchivefound && (stringname == link)&& componentfilefound )
	{
		softpkg_zip = XMLString::transcode(attributes.getValue("href"));
		SoftPkg* softpkg_ = new SoftPkg (softpkg_zip, _softpkg, _softpkg_id);
		_softpkglist.push_back( softpkg_ );
	}

	//////////////////////////// executableplacement Element ///////////////////
	if ( (stringname == executableplacement) && ( !executableplacementfound ) )
		executableplacementfound = true;

	if ( (stringname == componentfileref) && ( executableplacementfound ) )
	{
		std::string ref_ = XMLString::transcode(attributes.getValue("idref"));
		SoftPkgList ::iterator j_;
		std::string temp_id_;
		for (j_ = _softpkglist.begin(); j_ != _softpkglist.end(); ++j_)
		{
			(*j_)->get_softpkg_id(temp_id_);
			if (temp_id_ == ref_)
				(*j_)->get_softpkg_zip(_softpkg_zip);
		}
	}

	if ( (stringname == componentimplref) && ( executableplacementfound ) )
		_impl_uuid = XMLString::transcode(attributes.getValue("idref"));

	if ( (stringname == destination) && ( executableplacementfound ) )
		destinationfound = true;

	if ( destinationfound && executableplacementfound && (stringname == node) )
	{
		nodename = XMLString::transcode(attributes.getValue("nodename"));
	
		SoftPkgList ::iterator j_;
		for (j_ = _softpkglist.begin(); j_ != _softpkglist.end(); ++j_)
		{
			SoftPkg* current_ = (*j_);
			std::string softpkg_zip_f;
			current_->get_softpkg_zip(softpkg_zip_f);
			if ( softpkg_zip_f == _softpkg_zip)
				(*j_)->get_csd( _softpkgname );
		}

		InstallationMap* map_ = new InstallationMap (nodename, _softpkg_zip, _impl_uuid, _softpkgname);
		_map.push_back( map_ );
	}
	////////////////////////////////homeplacement Element ///////////////////
	if ( (stringname == homeplacement) && ( !homeplacementfound ) )
		homeplacementfound = true;

	if ( (stringname == componentfileref) && ( homeplacementfound ) )
	{
		std::string softpkg_id_ = XMLString::transcode(attributes.getValue("idref"));
		SoftPkgList ::iterator j_;
		for (j_ = _softpkglist.begin(); j_ != _softpkglist.end(); ++j_)
		{
			SoftPkg* current_ = (*j_);
			std::string temp_id_;
			current_->get_softpkg_id(temp_id_);
			if ( temp_id_ == softpkg_id_)
				(*j_)->get_csd( _softpkgname );
		}
	}

	if ( (stringname == componentimplref) && ( homeplacementfound ) )
		_impl_uuid = XMLString::transcode(attributes.getValue("idref"));

	if ( (stringname == destination) && ( homeplacementfound ) )
		destinationfound = true;

	if ( destinationfound && homeplacementfound && (stringname == node) )
		_nodename = XMLString::transcode(attributes.getValue("nodename"));

	if ( ( stringname == componentinstantiation) && ( homeplacementfound ) )
	{
		comp_id = XMLString::transcode(attributes.getValue("id"));
		ComponentInstance* comp_inst_ = new ComponentInstance (comp_id);
		_comp_inst_list.push_back (comp_inst_);
	}
	
	if ( ( stringname == rule) && ( homeplacementfound ) )
	{
		rulefound = true;
		_rule_name = XMLString::transcode(attributes.getValue("name"));
	}

	if ( ( stringname == condition) && homeplacementfound && (!conditionfound) )
	{
		conditionfound = true;
		_language = XMLString::transcode(attributes.getValue("language"));
		_interval = XMLString::transcode(attributes.getValue("interval"));
	}

	if ( ( stringname == action) && homeplacementfound && (!actionfound) )
	{
		actionfound = true;
		_language = XMLString::transcode(attributes.getValue("language"));
	}

	if ( ( stringname == homeproperties) && homeplacementfound && (!homepropertiesfound) )
	{
		homepropertiesfound = true;
	}
	
	if ( ( stringname == fileinarchive) && homeplacementfound && homepropertiesfound )
		 _propertyfile = XMLString::transcode(attributes.getValue("name"));




	////////////////////////////// Connectinterface Element /////////////////////////////////
	if ( (stringname == connectinterface) && ( !connectinterfacefound ) )
	{
		connectinterfacefound = true;
		_connection_id = XMLString::transcode(attributes.getValue("id"));

	}

	if ( (stringname == usesport) && ( connectinterfacefound ) )
		usesfound = true;

	if ( (stringname == usesidentifier  ) && ( usesfound ) )
		 usesidentifierfound = true;

	if ( (stringname == providesport) && ( connectinterfacefound ) )
		providesfound = true;

	if ( (stringname == providesidentifier  ) && ( providesfound ) )
		providesidentifierfound = true;

	if ( (stringname == componentinstantiationref) && (usesfound) && (connectinterfacefound) )
	{
		_first_comp_ref = XMLString::transcode(attributes.getValue("idref"));
	}

	if ( (stringname == componentinstantiationref) && (providesfound) && (connectinterfacefound) )
	{
		ConnectionInterface* connect_interface_ = new ConnectionInterface ();
		std::string provides_comp_ref = XMLString::transcode(attributes.getValue("idref"));
		connect_interface_->set_provides_id(_second_id);
		connect_interface_->set_provides_comp_ref(provides_comp_ref);
		connect_interface_->set_uses_id(_first_id);
		connect_interface_->set_uses_comp_ref(_first_comp_ref);
		connect_interface_->set_id(_connection_id);
		_connect_interfaces.push_back (connect_interface_);
	}


	////////////////////////////// ConnectEvent Element /////////////////////////////////
	if ( (stringname == connectevent) && ( !connecteventfound ) )
	{
		connecteventfound = true;
		_connection_id = XMLString::transcode(attributes.getValue("id"));

	}

	if ( (stringname == consumesport) && ( connecteventfound ) )
		consumesportfound = true;

	if ( (stringname == consumesidentifier) && ( consumesportfound ) )
		 consumesidentifierfound = true;

	if ( (stringname == componentinstantiationref) && (consumesportfound) && (connecteventfound) )
	{
		_first_comp_ref = XMLString::transcode(attributes.getValue("idref"));
	}

	if ( (stringname == publishesport) && ( connecteventfound ) )
	{
		secondportfound = true;
		_port_type = publishes;
	}

	if ( (stringname == emitsport) && ( connecteventfound ) )
	{
		secondportfound = true;
		_port_type = emits;
	}

	if ( (stringname == publishesidentifier  ) && ( secondportfound ) )
		secondidentifierfound = true;

	if ( (stringname == emitsidentifier  ) && ( secondportfound ) )
		secondidentifierfound = true;

	if ( (stringname == componentinstantiationref) && (secondportfound) && (connecteventfound) )
	{
		ConnectEvent* connect_event_ = new ConnectEvent();
		std::string second_comp_ref = XMLString::transcode(attributes.getValue("idref"));
		connect_event_->set_second_port_id(_second_id);
		connect_event_->set_second_port_comp_ref(second_comp_ref);
		connect_event_->set_consume_id(_first_id);
		connect_event_->set_consume_comp_ref(_first_comp_ref);
		connect_event_->set_id(_connection_id);
		connect_event_->set_second_port_type(_port_type);
		_connect_events.push_back (connect_event_);
//		delete connection_;
	}

//////////////////////////////////////	
    std::string ass = "componentassembly";
    if ( (stringname == ass) && (!assfound) )
	{
      std::string id = XMLString::transcode(attributes.getValue("id"));
	  _assembly_id = id;
	  assfound = true;
	}
}

void AssemblySAXHandler::characters(const XMLCh* const chars , const unsigned int length)
{
   //  check flag: is contents of following elements?
	if (usesidentifierfound == true)
	{
		_first_id = XMLString::transcode(chars);
	}
	if (providesidentifierfound == true)
	{
		_second_id = XMLString::transcode(chars);
	}
	if (consumesidentifierfound == true)
	{
		_first_id = XMLString::transcode(chars);
	}
	if (secondidentifierfound == true)
	{
		_second_id = XMLString::transcode(chars);
	}
	if (conditionfound == true)
	{
		_str = XMLString::transcode(chars);
	}
	if (actionfound == true)
	{
		_str = XMLString::transcode(chars);
	}
}

void AssemblySAXHandler::endElement(const XMLCh* const name) 
{
  
    std::string stringname(XMLString::transcode(name));
    std::string destination_end = "destination";
	std::string executableplacement_end = "executableplacement";
	std::string ass_end = "componentassembly";
	std::string fileinarchive_end = "fileinarchive";
	std::string homeplacement_end = "homeplacement";
	std::string connectinterface_end = "connectinterface";
	std::string usesport_end = "usesport";
	std::string providesport_end = "providesport";
	std::string usesidentifier_end = "usesidentifier";
	std::string providesidentifier_end = "providesidentifier";
	std::string connectevent_end = "connectevent";
	std::string consumesport_end = "consumesport";
	std::string publishesport_end = "publishesport";
	std::string emitsport_end = "emitsport";
	std::string consumesidentifier_end = "consumesidentifier";
	std::string emitsidentifier_end = "emitsidentifier";
	std::string publishesidentifier_end = "publishesidentifier";
	std::string componentfile_end = "componentfile";
	std::string rule_end = "rule";
	std::string condition_end = "condition";
	std::string action_end = "action";
	std::string homeproperties_end = "homeproperties";
	
	if (stringname == componentfile_end)
      componentfilefound = false;

	if (stringname == fileinarchive_end)
      fileinarchivefound = false;

    if (stringname == destination_end)
      destinationfound = false;
	
	if (stringname == executableplacement_end)
      executableplacementfound = false;

	if (stringname == homeplacement_end)
	{
		homeplacementfound = false;
		ComponentInstantiationMap* map_ = new ComponentInstantiationMap (_nodename, _softpkgname, _impl_uuid, _comp_inst_list, _rules, _propertyfile);
		_comp_map.push_back( map_ );
		_comp_inst_list.clear();
		_rules.clear();
	}

	if (stringname == homeproperties_end)
      homepropertiesfound = false;

	if (stringname == usesidentifier_end)
		usesidentifierfound = false;

	if (stringname == providesidentifier_end)
		providesidentifierfound = false;

	if (stringname == connectinterface_end)
      connectinterfacefound = false;

	if (stringname == usesport_end)
      usesfound = false;

	if (stringname == providesport_end)
      providesfound = false;

	if (stringname == connectevent_end)
		connecteventfound = false;

	if (stringname == consumesport_end)
		consumesportfound = false;

	if (stringname == publishesport_end)
		secondportfound = false;

	if (stringname == emitsport_end)
		secondportfound = false;

	if (stringname == consumesidentifier_end)
		consumesidentifierfound = false;

	if (stringname == emitsidentifier_end)
		secondidentifierfound = false;

	if (stringname == publishesidentifier_end)
		secondidentifierfound = false;

    if ( stringname == ass_end )
		assfound = false;

	if ( stringname == rule_end )
		rulefound = false;

	if ( stringname == condition_end )
	{
		conditionfound = false;
		Condition* condition_ = new Condition (_language, _interval, _str);
		_condition = *condition_;
		delete condition_;
	}

	if ( stringname == action_end )
	{
		actionfound = false;
		Action* action_ = new Action (_language, _str);
		_action = *action_;
		delete action_;
	}
	if (stringname == rule_end)
	{
		rulefound = true;
		Rule* rule_ = new Rule (_rule_name, _condition, _action);
		_rules.push_back( rule_ );
	}

	if ( ( stringname == ass_end ) && ( _map.empty() ) )
      XMLerror = 4; // The node names were  not found in the assembly file.
}


void AssemblySAXHandler::error(const SAXParseException& e) {
  XMLerror = 2;
  std::cerr << "\nError at file " << XMLString::transcode(e.getSystemId());
  std::cerr << ", line " << e.getLineNumber();
  std::cerr << ", char " << e.getColumnNumber();
  std::cerr << "\n	 Message: " << XMLString::transcode(e.getMessage()) << '\n';

}


void AssemblySAXHandler::fatalError(const SAXParseException& e) {
  XMLerror = 3;
  std::cerr << "\nXML Fatal Error at file " << XMLString::transcode(e.getSystemId());
  std::cerr << ", line " << e.getLineNumber();
  std::cerr << ", char " << e.getColumnNumber();
  std::cerr << "\n    Message: " << XMLString::transcode(e.getMessage()) << '\n';

}