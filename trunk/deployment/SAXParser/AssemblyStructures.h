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

#ifndef ASSEMBLY_DESCRIPTOR_STRUCTURES_HH
#define ASSEMBLY_DESCRIPTOR_STRUCTURES_HH

#include <OB/CORBA.h>
#include <iostream>
#include <string>
#include <list>
#include "DCI_Basics_NodeManagerImpl_LOCAL.h"
//#include "Deployment_dpe.hh"
//#include "component_PP_dpe.hh"

///////////////////////////////////////////class SoftPkg //////////////////////////
class SoftPkg
{
private:
	std::string _softpkg_id;
	std::string _softpkg_zip;
	std::string _csd;

public:

	SoftPkg(std::string, std::string, std::string);
	virtual ~SoftPkg();
	void get_softpkg_zip (std::string& ) const;
	void get_csd (std::string& ) const;
	void get_softpkg_id (std::string& ) const;

};

typedef std::list<SoftPkg*> SoftPkgList;

/////////////////////////// class ConnectionInterface ////////////////////////////
class ConnectionInterface
{
private:

	std::string _id;
	std::string _uses_id;
	std::string _uses_comp_ref;
	std::string _provides_id;
	std::string _provides_comp_ref;

public:
	ConnectionInterface ();
	virtual ~ConnectionInterface();
	void get_id(std::string& ) const;
	void get_provides_id(std::string& ) const;
	void get_uses_id(std::string& ) const;
	void set_id (const std::string&);
	void set_uses_id( const std::string& );
	void set_provides_id( const std::string& );
	void set_uses_comp_ref(const std::string&);
	void get_uses_comp_ref(std::string& ) const;
	void set_provides_comp_ref(const std::string&);
	void get_provides_comp_ref(std::string& ) const;

};
typedef std::list<ConnectionInterface*> ConnectionInterfaces;

/////////////////////////// class ConnectEvent ////////////////////////////
enum EventPort { emits, publishes };

class ConnectEvent
{
private:


	std::string _id;
	std::string _consume_id;
	std::string _consume_comp_ref;
	EventPort _second_port_type; //can be emitsport or publishesport
	std::string _second_port_id;
	std::string _second_port_comp_ref;

public:

	ConnectEvent ();
	virtual ~ConnectEvent();
	void get_id(std::string& ) const;
	void get_consume_id(std::string& ) const;
	void get_second_port_id(std::string& ) const;
	void set_id (const std::string&);
	void set_consume_id( const std::string& );
	void set_second_port_id( const std::string& );
	void set_consume_comp_ref(const std::string&);
	void get_consume_comp_ref(std::string& ) const;
	void set_second_port_comp_ref(const std::string&);
	void get_second_port_comp_ref(std::string& ) const;
	void get_second_port_type (EventPort&) const;
	void set_second_port_type (const EventPort&);

};
typedef std::list<ConnectEvent*> ConnectEvents;
//////////////////////////////////////////// InstallationMap ////////////////////////////
class InstallationMap
{
private:

	std::string _nodename;
	std::string _softpkg_zip;
	std::string _impl_uuid;
	std::string _softpkgname;

public:
	InstallationMap(std::string, std::string, std::string, std::string);
	virtual ~InstallationMap();
	void get_node_name (std::string& ) const;
	void get_softpkg_zip (std::string& ) const;
	void get_impl_uuid (std::string& ) const;
	void get_csd_name (std::string& softpkgname) const;

};

typedef std::list<InstallationMap*> InstallationMapList;

///////////////////////////////////////// ComponentInstance //////////////////////////////
class ComponentInstance
{
private:
	std::string _id;
	Components::CCMObject_var _reference;

public:

	ComponentInstance(std::string);
	virtual ~ComponentInstance();
	void get_instance_id (std::string& ) const;
	void set_component_reference(Components::CCMObject_ptr);
	Components::CCMObject_ptr get_component_reference () const;

};

typedef std::list<ComponentInstance*> ComponentInstanceList;

/////////////////////////////// Condition Class ////////////////////////

class Condition
{
private:

	std::string _language;
	std::string _interval;
	std::string _value;

public:

	Condition (std::string, std::string, std::string);
	Condition ();
	virtual ~Condition();
	void get_language(std::string&) const;
	void get_interval (std::string&) const;
	void get_value(std::string&) const;

};
/////////////////////////////// Action Class /////////////////////////////

class Action
{
private:

	std::string _language;
	std::string _value;

public:

	Action (std::string, std::string);
	Action ();
	virtual ~Action();
	void get_language(std::string&) const;
	void get_value(std::string&) const;
};

///////////////////////// Rule Class ///////////////////////////////
class Rule
{
private:

	std::string _name;
	Condition _condition;
	Action _action;

public:
	
	Rule (std::string, Condition, Action);
	virtual ~Rule();
	void get_rule_name (std::string& ) const;
	void get_condition (Condition& ) const;
	void get_action (Action& ) const;
};

typedef std::list<Rule*> RuleList;

////////////////////////////////////// ComponentInstantiationMap ///////////////////////////
class ComponentInstantiationMap
{
private:

	std::string _nodename;
	std::string _softpkgname;
	std::string _impl_uuid;
	ComponentInstanceList _comp_instancies;
	RuleList _rules;
	std::string _propertyfile;
public:
	ComponentInstantiationMap (std::string, std::string, std::string, ComponentInstanceList&, RuleList&, std::string );
	virtual ~ComponentInstantiationMap();
	void get_node_name (std::string& ) const;
	void get_softpkg_name (std::string& ) const;
	void get_impl_uuid (std::string& ) const;
	void get_comp_instancies (ComponentInstanceList&) const;
	void get_rules (RuleList&) const;
	void get_propertyfile (std::string&) const;
};
typedef std::list<ComponentInstantiationMap*> ComponentInstantiationMapList;

#endif 