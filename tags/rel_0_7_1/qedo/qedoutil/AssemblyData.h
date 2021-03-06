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

#ifndef __ASSEMBLY_DATA_H__
#define __ASSEMBLY_DATA_H__


#include "CORBA.h"
#include "Components.h"
#include "qedoutil.h"
#include "CompositionData.h"
#include <vector>
#include <string>
#include <map>


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */


/*
 * data for a script
 */
struct ScriptData
{
	/** language */
	std::string									language;
	/** code */
	std::string									code;
};


/*
 * data for a dynamic reconfiguration rule
 */
struct RuleData
{
	/** name */
	std::string									name;
	/** interval */
	long										interval;
	/** naming service */
	ScriptData									condition;
	/** naming service */
	ScriptData									action;
};


/**
 * kind of the reference
 */
enum ReferenceKind { COMPONENTID, HOMEID, NAMING, OBJECTREF, TRADER, FINDER };
/**
 * reference data
 */
struct ReferenceData
{
	/** reference kind */
	ReferenceKind								kind;
	/** reference name */
	std::string									name;
};


/**
 * destination data
 */
class DestinationData
{
public:
	/** was specified */
	bool										specified;
	/** node name */
	std::string									node;
	/** type of installation */
	std::string									installation_type;
	/** reference to installation */
	ReferenceData								installation_ref;
	/** type of activation */
	std::string									activation_type;
	/** reference to activation */
	ReferenceData								activation_ref;

	DestinationData() { specified = false; };
};


/**
 * kind of port
 */
enum PortKind { COMPONENT_PORT, FACET_PORT, EMITTER_PORT, PUBLISHER_PORT, 
				SINK_PORT, SOURCE_PORT};


/*
 * data for a component instantiation registration
 */
struct NamingRegistrationData
{
	/** port kind */
	PortKind									port_kind;
	/** port name */
	std::string									port;
	/** naming service */
	std::string									name;
};


/**
 * data for a component instantiation
 */
struct ComponentInstanceData
{
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** component properties */
	std::string									comp_prop;
	/** list of registrations */
	std::vector< NamingRegistrationData >		naming_registrations;
	/** list of rules */
	std::vector< RuleData >						rules;
};


/**
 * data for a home instantiation
 */
struct HomeInstanceData
{
	/** cardinality */
	unsigned int								cardinality;
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** implementation package */
	std::string									file;
	/** implementation id */
	std::string									impl_id;
	/** destination */
	DestinationData								dest;
	/** registration with homefinder */
	std::string									finder;
	/** registration with naming service */
	std::string									naming;
	/** registration with trading service */
	std::string									trader;
	/** home properties */
	std::string									home_prop;
	/** component properties */
	std::string									comp_prop;
	/** list of component instances */
	std::vector < ComponentInstanceData >		instances;
	/** container of the home */
	Components::Deployment::Container_var		container;
	/** component data */
	CompositionData								component;
	/** list of rules */
	std::vector< RuleData >						rules;
};


/**
 * data for a process collocation
 */
struct ProcessData
{
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** destination */
	DestinationData								dest;
	/** list of home instances */
	std::vector < HomeInstanceData >			homes;
	/** component server */
	Components::Deployment::ComponentServer_var	server;
};


/**
 * data for a host collocation
 */
struct HostData
{
	/** name */
	std::string									usage_name;
	/** id */
	std::string									id;
	/** destination */
	DestinationData								dest;
	/** list of processes */
	std::vector < ProcessData >					processes;
};


/**
 * data of a port
 */
struct PortData
{
	/** port name */
	std::string									name;
	/** port reference */
	ReferenceData								ref;
};

/**
 * data of a stream source port
 */
struct StreamSourcePortData
{
	/** port name */
	std::string									name;
	/** port reference */
	ReferenceData								ref;
	/** packet timing */
	std::string									packet_timing;
	/** transport protocol */
	std::string									fixed_transport;
};

/**
 * data for an interface connection
 */
struct InterfaceConnectionData
{
	/** use port */
	PortData									use;
	/** provided interface */
	PortData									provide;
};


/**
 * kind of the event connection
 */
enum EventConnectionKind { EMITTER, PUBLISHER };
/**
 * data for an event connection
 */
struct EventConnectionData
{
	/** consumer port */
	PortData									consumer;
	/** connection kind */
	EventConnectionKind							kind;
	/** emitter or publisher*/
	PortData									emitter;
};


/*
 * kind of the stream connection
 */
enum StreamConnectionKind{ SINK, SOURCE};

/**
 * data for an stream connection
 */
struct StreamConnectionData
{
	/** consumer port */
	PortData									sink;
	/** connection kind */
	StreamConnectionKind						kind;
	/** sink or source*/
	PortData									source;

};



/**
 * file data
 */
struct FileData
{
	/** the file */
	std::string									name;
	/** the archiv */
	std::string									archiv;
};


/**
 * the assembly data
 */
struct AssemblyData
{
	/** the uuid of the assembly */
	std::string									uuid_;
    /** the mapping of ids to component implementations */
	std::map < std::string, FileData >			implementationMap_;
    /** start order of the instances */
	std::vector < std::string >					start_order_;
	/** list of existing homes */
	std::vector < HomeInstanceData >			existing_homes_;
	/** list of server/process/home instantiations */
	std::vector < HostData >					hosts_;
	/** list of interface connections */
	std::vector < InterfaceConnectionData >		interface_connections_;
	/** list of event connections */
	std::vector < EventConnectionData >			event_connections_;
	/** list of stream connections */
	std::vector < StreamConnectionData >		stream_connections_;
	/** the cad file */
	std::string									cad;
};

/** @} */

}

#endif

