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


/**
 * data for a component instantiation registration
 */
struct ComponentInstanceRegistrationData
{
	/** emitter */
	std::string									emitter;
	/** provider */
	std::string									provider;
	/** publisher */
	std::string									publisher;
	/** naming service */
	std::string									naming;
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
	/** registration */
	ComponentInstanceRegistrationData			registration;
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
	std::string									dest;
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
	/** destination host */
	std::string									host;
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
	/** destination host */
	std::string									host;
	/** list of processes */
	std::vector < ProcessData >					processes;
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


/**
 * the assembly data
 */
struct AssemblyData
{
	/** the uuid of the assembly */
	std::string									uuid_;
    /** the mapping of component implementation ids to softpackages */
	std::map < std::string, std::string >		implementationMap_;
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
	/** the cad file */
	std::string									cad;
};

/** @} */

}

#endif

