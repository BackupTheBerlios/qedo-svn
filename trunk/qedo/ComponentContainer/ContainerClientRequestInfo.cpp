/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002-2004 by the Qedo Team                                */
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

#include "ContainerClientRequestInfo.h"

static char rcsid[] UNUSED = "$Id: ContainerClientRequestInfo.cpp,v 1.1 2004/02/16 07:28:08 tom Exp $";

namespace Qedo {
#ifndef _QEDO_NO_QOS

ContainerClientRequestInfo::ContainerClientRequestInfo (
	PortableInterceptor::ClientRequestInfo_ptr request_info, 
	const char* uuid, 
	const char* component_id,
	const char* port_id)
{
	request_info_ = PortableInterceptor::ClientRequestInfo::_duplicate(request_info);
	uuid_ = uuid;
	component_id_ = component_id;
	port_id_ = port_id;
}

ContainerClientRequestInfo::~ContainerClientRequestInfo ()
{

}


char* 
ContainerClientRequestInfo::component_uuid()
{
	char* ret_str;
	ret_str = strdup ( uuid_.c_str() );
	return ret_str;
}

char* 
ContainerClientRequestInfo::component_id() 
{
	char* ret_str;
	ret_str = strdup ( component_id_.c_str() );
	return ret_str;
}

char* 
ContainerClientRequestInfo::port_id() 
{
	char* ret_str;
	ret_str = strdup ( port_id_.c_str() );
	return ret_str;
}

PortableInterceptor::ClientRequestInfo_ptr 
ContainerClientRequestInfo::request_info() 
{
	return PortableInterceptor::ClientRequestInfo::_duplicate(request_info_);
}

#endif
};
