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

#ifndef __TRANSPORT_REGISTRY_H__
#define __TRANSPORT_REGISTRY_H__

#ifndef _QEDO_NO_STREAMS


#include "TransportEndpoint.h"

#include <vector>


namespace Qedo {


class TransportEntry
{
public:
	std::string transport_profile_;
	TransportEndpointFactory* factory_;

	TransportEntry (const char*, TransportEndpointFactory*);
	TransportEntry();
	TransportEntry (const TransportEntry&);
	TransportEntry& operator= (const TransportEntry&);
	~TransportEntry();
};
typedef std::vector < TransportEntry > TransportVector;


class CONTAINERDLL_API TransportRegistry
{
public:
	static TransportVector transports_;
	static void register_transport (const char*, TransportEndpointFactory*);
	static void clear_registry();
};


} // namespace Qedo

#endif

#endif

