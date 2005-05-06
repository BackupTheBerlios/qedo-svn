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

#include "AssemblyStructures.h"

////////////////// class SoftPkg ////////////////////////
SoftPkg::SoftPkg(std::string softpkg_zip, std::string csd, std::string id)
{
	_softpkg_zip = softpkg_zip;
	_csd = csd;
	_softpkg_id = id;
}

SoftPkg::~SoftPkg()
{
}

void SoftPkg::get_softpkg_zip (std::string& softpkg_zip) const
{
	softpkg_zip = _softpkg_zip;
}

void SoftPkg::get_csd (std::string& csd) const
{
	csd = _csd;
}
void SoftPkg::get_softpkg_id (std::string& id) const
{
	id = _softpkg_id;
}

///////////// class ComponentInstance /////////////////////////////////
ComponentInstance::ComponentInstance(std::string id)
{
	_id = id;
}

ComponentInstance::~ComponentInstance()
{
}

void ComponentInstance::get_instance_id (std::string& id ) const
{
	id = _id;
}

void ComponentInstance::set_component_reference(Components::CCMObject_ptr ref)
{
	_reference = ref;
}

Components::CCMObject_ptr ComponentInstance::get_component_reference () const
{
	return Components::CCMObject::_duplicate(_reference);
}

//////////////////////////////////// class ConnectionInterface //////////////////////////////////////
ConnectionInterface::ConnectionInterface ()
{
}
ConnectionInterface::~ConnectionInterface ()
{
}

void ConnectionInterface::get_provides_id(std::string& provides_id) const
{
	provides_id = _provides_id;
}

void ConnectionInterface::get_uses_id(std::string& uses_id) const
{
	uses_id = _uses_id;
}

void ConnectionInterface::get_id(std::string& id) const
{
	id = _id;
}
void ConnectionInterface::get_uses_comp_ref(std::string& uses_comp_ref) const
{
	uses_comp_ref = _uses_comp_ref;
}
void ConnectionInterface::get_provides_comp_ref(std::string& provides_comp_ref) const
{
	provides_comp_ref = _provides_comp_ref;
}
void ConnectionInterface::set_id( const std::string& id)
{
	_id = id;
}
void ConnectionInterface::set_uses_id(const std::string& uses_id) 
{
	_uses_id = uses_id;
}
void ConnectionInterface::set_provides_id(const std::string& provides_id) 
{
	_provides_id = provides_id;
}
void ConnectionInterface::set_provides_comp_ref(const std::string& provides_comp_ref) 
{
	_provides_comp_ref = provides_comp_ref;
}
void ConnectionInterface::set_uses_comp_ref(const std::string& uses_comp_ref) 
{
	_uses_comp_ref = uses_comp_ref;
}

/////////////////////////// class ConnectEvent ////////////////////////////

ConnectEvent::ConnectEvent()
{
}
ConnectEvent::~ConnectEvent()
{
}

void ConnectEvent::get_second_port_id(std::string& second_port_id) const
{
	second_port_id = _second_port_id;
}

void ConnectEvent::get_consume_id(std::string& consume_id) const
{
	consume_id = _consume_id;
}

void ConnectEvent::get_id(std::string& id) const
{
	id = _id;
}
void ConnectEvent::get_consume_comp_ref(std::string& consume_comp_ref) const
{
	consume_comp_ref = _consume_comp_ref;
}
void ConnectEvent::get_second_port_comp_ref(std::string& second_port_comp_ref) const
{
	second_port_comp_ref = _second_port_comp_ref;
}
void ConnectEvent::set_id( const std::string& id)
{
	_id = id;
}
void ConnectEvent::set_consume_id(const std::string& consume_id) 
{
	_consume_id = consume_id;
}
void ConnectEvent::set_second_port_id(const std::string& second_port_id) 
{
	_second_port_id = second_port_id;
}
void ConnectEvent::set_second_port_comp_ref(const std::string& second_port_comp_ref) 
{
	_second_port_comp_ref = second_port_comp_ref;
}
void ConnectEvent::set_consume_comp_ref(const std::string& consume_comp_ref) 
{
	_consume_comp_ref = consume_comp_ref;
}
void ConnectEvent::get_second_port_type (EventPort& type) const
{
	type = _second_port_type;
}
void ConnectEvent::set_second_port_type (const EventPort& type)
{
	_second_port_type = type;
}
 
//////////////////////////InstallationMap/////////////////////////////////////////
InstallationMap::InstallationMap(std::string nodename, std::string softpkg_zip, std::string impl_uuid, std::string softpkgname) 
{
	_nodename = nodename;
	_softpkg_zip = softpkg_zip;
	_impl_uuid = impl_uuid;
	_softpkgname = softpkgname;
}

InstallationMap::~InstallationMap()
{
}

void InstallationMap::get_node_name (std::string& nodename) const
{
	nodename = _nodename;
}

void InstallationMap::get_softpkg_zip (std::string& softpkg_zip) const
{
	softpkg_zip = _softpkg_zip;
}

void InstallationMap::get_impl_uuid (std::string& impl_uuid) const
{
	impl_uuid = _impl_uuid;
}

void InstallationMap::get_csd_name (std::string& softpkgname) const
{
	softpkgname = _softpkgname;
}

////////////////////////////////InstatiationMap/////////////////////////////////

ComponentInstantiationMap::ComponentInstantiationMap (std::string nodename, std::string softpkgname, std::string impl_uuid, ComponentInstanceList& inst_list, RuleList& rules, std::string propertyfile)
{
	_nodename = nodename;
	_softpkgname = softpkgname;
	_impl_uuid = impl_uuid;
	_comp_instancies = inst_list;
	_rules = rules;
	_propertyfile = propertyfile;
}
	
ComponentInstantiationMap::~ComponentInstantiationMap()
{
}

void ComponentInstantiationMap::get_node_name (std::string& nodename) const
{
	nodename = _nodename;
}

void ComponentInstantiationMap::get_softpkg_name (std::string& softpkgname ) const
{
	softpkgname = _softpkgname;
}

void ComponentInstantiationMap::get_impl_uuid (std::string& impl_uuid) const
{
	impl_uuid = _impl_uuid;
}

void ComponentInstantiationMap::get_comp_instancies (ComponentInstanceList& inst_list) const
{
	inst_list = _comp_instancies;
}

void ComponentInstantiationMap::get_rules (RuleList& rules) const
{
	rules = _rules;
}

void ComponentInstantiationMap::get_propertyfile (std::string& propertyfile) const
{
	propertyfile = _propertyfile;
}

///////////////////////////////// Rule Class //////////////////////////////////////////////

Rule::Rule (std::string name, Condition condition, Action action)
{
	_name = name;
	_condition = condition;
	_action = action;
}
	
Rule::~Rule()
{
}

void Rule::get_rule_name (std::string& name) const
{
	name = _name;
}

void Rule::get_condition (Condition& condition ) const
{
	condition = _condition;
}

void Rule::get_action (Action& action) const
{
	action = _action;
}

/////////////////////////////// Condition Class ////////////////////////

Condition::Condition (std::string language, std::string interval, std::string value)
{
	_language = language;
	_interval = interval;
	_value = value;
}

Condition::Condition()
{}

Condition::~Condition()
{}

void Condition::get_language(std::string& language) const
{
	language = _language;
}
void Condition::get_interval (std::string& interval) const
{
	interval = _interval;
}
void Condition::get_value(std::string& value) const
{
	value = _value;
}

/////////////////////////////// Action Class /////////////////////////////

Action::Action (std::string language, std::string value)
{
	_language = language;
	_value = value;
}

Action::Action ()
{}

Action::~Action()
{}

void Action::get_language(std::string& language) const
{
	language = _language;
}
void Action::get_value(std::string& value) const
{
	value = _value;
}