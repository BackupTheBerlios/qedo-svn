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

#ifndef __COMPOSITION_DATA_H__
#define __COMPOSITION_DATA_H__


#include <string>


namespace Qedo {


/**
 * @addtogroup Utilities
 * @{
 */

struct StreamSourcePort
{
	/** port name */
	std::string									name;
	/** port reference */
	std::string									port_repid;
	/** packet timing */
	std::string									packet_timing;
	/** transport protocol */
	std::string									fixed_transport;

};


	
struct StreamSinkPort
{
	/** port name*/
	std::string									name;
	/** port repid */
	std::string									port_repid;
	
};

struct Port
{
	/** Stream Source Ports */
	std::vector < StreamSourcePort >					stream_source_ports;
	/** Stream Sink Ports */
	std::vector < StreamSinkPort >						stream_sink_ports;

};

/**
 * the component features
 */
struct ComponentFeature
{
	std::vector < Port >								ports;
	
};


/**
 * the component data
 */
struct CompositionData
{
	/** the component kind */
	std::string									kind;
	/** the RepId of the component */
	std::string									repid;
	/** the RepId of the home */
	std::string									home_repid;
	/** the name of the home */
	std::string									home_name;
	/** the componentfeatures */
	std::vector < ComponentFeature >			component_features;

};











/** @} */

}

#endif
