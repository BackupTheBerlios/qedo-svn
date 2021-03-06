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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "ContainerServerRequestInfo.h"
#include "Util.h"


static char rcsid[] UNUSED = "$Id: ContainerServerRequestInfo.cpp,v 1.3 2004/06/24 13:11:03 tom Exp $";


namespace Qedo {
#ifndef _QEDO_NO_QOS

ContainerServerRequestInfo::ContainerServerRequestInfo (
	PortableInterceptor::ServerRequestInfo_ptr request_info, 
	const char* origin_id, 
	const char* target_id,
	const Components::FeatureName name)
{
	request_info_ = PortableInterceptor::ServerRequestInfo::_duplicate(request_info);
	origin_id_ = origin_id;
	target_id_ = target_id;
	name_ = name;
}

ContainerServerRequestInfo::~ContainerServerRequestInfo ()
{

}


char* 
ContainerServerRequestInfo::origin_id()
{
	char* ret_str;
	ret_str = strdup ( origin_id_.c_str() );
	return ret_str;
}


char* 
ContainerServerRequestInfo::target_id() 
{
	char* ret_str;
	ret_str = strdup ( target_id_.c_str() );
	return ret_str;
}

char* 
ContainerServerRequestInfo::name() 
{
	char* ret_str;
	ret_str = strdup ( name_.c_str() );
	return ret_str;
}

PortableInterceptor::ServerRequestInfo_ptr 
ContainerServerRequestInfo::request_info() 
{
	return PortableInterceptor::ServerRequestInfo::_duplicate(request_info_);
}


// ContainerServantRequestInfo

ContainerServantRequestInfo::ContainerServantRequestInfo (
	Dynamic::ParameterList* arguments, 
	const char* origin_id, 
	const char* target_id,
	const Components::FeatureName name)
{
	arguments_ = arguments;
	origin_id_ = origin_id;
	target_id_ = target_id;
	name_ = name;
}

ContainerServantRequestInfo::~ContainerServantRequestInfo ()
{

}


char* 
ContainerServantRequestInfo::origin_id()
{
	char* ret_str;
	ret_str = strdup ( origin_id_.c_str() );
	return ret_str;
}


char* 
ContainerServantRequestInfo::target_id() 
{
	char* ret_str;
	ret_str = strdup ( target_id_.c_str() );
	return ret_str;
}

char* 
ContainerServantRequestInfo::name() 
{
	char* ret_str;
	ret_str = strdup ( name_.c_str() );
	return ret_str;
}

Dynamic::ParameterList*
ContainerServantRequestInfo::arguments () 
{
	return arguments_;
}

void 
ContainerServantRequestInfo::arguments( const ::Dynamic::ParameterList& value )
{
	arguments_ = new Dynamic::ParameterList(value);
}

char* 
ContainerServantRequestInfo::operation()
{
	char* ret_str;
	ret_str = strdup ( operation_name_.c_str() );
	return ret_str;	
}


void 
ContainerServantRequestInfo::operation( const char* value ) 
{
	operation_name_ = value;

}


#endif
};
