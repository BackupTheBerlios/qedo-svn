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

#include "ContainerClientRequestInfo.h"
#include "Util.h"


static char rcsid[] UNUSED = "$Id: ContainerClientRequestInfo.cpp,v 1.3 2004/06/24 13:11:03 tom Exp $";


namespace Qedo {
#ifndef _QEDO_NO_QOS

ContainerClientRequestInfo::ContainerClientRequestInfo (
	PortableInterceptor::ClientRequestInfo_ptr request_info, 
    const CORBA::OctetSeq& origin_id, 
	const CORBA::OctetSeq& target_id,
	const Components::FeatureName name)
{
	request_info_ = PortableInterceptor::ClientRequestInfo::_duplicate(request_info);
    origin_id_ = new CORBA::OctetSeq(origin_id);
    target_id_ = new CORBA::OctetSeq(target_id);
	name_ = name;
}

ContainerClientRequestInfo::~ContainerClientRequestInfo ()
{

}



CORBA::OctetSeq* 
ContainerClientRequestInfo::origin_id() 
{
	return origin_id_;
}

CORBA::OctetSeq* 
ContainerClientRequestInfo::target_id() 
{
	return target_id_;
}

char* 
ContainerClientRequestInfo::name() 
{
	char* ret_str;
	ret_str = strdup ( name_.c_str() );
	return ret_str;
}

PortableInterceptor::ClientRequestInfo_ptr 
ContainerClientRequestInfo::request_info() 
{
	return PortableInterceptor::ClientRequestInfo::_duplicate(request_info_);
}

#endif
};
