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
    const CORBA::OctetSeq& origin_id, 
    const CORBA::OctetSeq& target_id,
	const Components::FeatureName name)
{
	request_info_ = PortableInterceptor::ServerRequestInfo::_duplicate(request_info);
    origin_id_ = new CORBA::OctetSeq(origin_id);
    target_id_ = new CORBA::OctetSeq(target_id);
	name_ = name;
}

ContainerServerRequestInfo::~ContainerServerRequestInfo ()
{

}

CORBA::OctetSeq*
ContainerServerRequestInfo::origin_id() 
{
	return origin_id_;
}


CORBA::OctetSeq*
ContainerServerRequestInfo::target_id() 
{
	return target_id_;
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


//////////////////////////////////

ContainerServantRequestInfo::ContainerServantRequestInfo (
    const CORBA::OctetSeq& origin_id, 
	const CORBA::OctetSeq& target_id,
	const Components::FeatureName name)
{
    origin_id_ = new CORBA::OctetSeq(origin_id);
    target_id_ = new CORBA::OctetSeq(target_id);
	name_ = name;
}

ContainerServantRequestInfo::~ContainerServantRequestInfo ()
{

}

CORBA::OctetSeq* 
ContainerServantRequestInfo::origin_id() 
{
	return origin_id_;
}

CORBA::OctetSeq* 
ContainerServantRequestInfo::target_id() 
{
	return target_id_;
}

char* 
ContainerServantRequestInfo::name() 
{
	char* ret_str;
	ret_str = strdup ( name_.c_str() );
	return ret_str;
}

	::Dynamic::ParameterList* 
	ContainerServantRequestInfo::arguments() {
		assert(0);
		return 0;
	};

    void 
	ContainerServantRequestInfo::arguments( const ::Dynamic::ParameterList& value ) {
		assert (0);
	};

    char* 
	ContainerServantRequestInfo::operation() {
		return CORBA::string_dup(name_.c_str());
	};

    CORBA::Any* 
	ContainerServantRequestInfo::result() {
		assert (0);
		return 0;
	};

    void 
	ContainerServantRequestInfo::result( const CORBA::Any& value ) {
		assert(0);
		};

    ::Components::EnterpriseComponent_ptr 
	ContainerServantRequestInfo::target() {
		assert (0);
		return 0;
};

    void 
		ContainerServantRequestInfo::target( ::Components::EnterpriseComponent_ptr value ) {
		assert(0);
		};

    CORBA::Any* 
		ContainerServantRequestInfo::the_exception() {
		assert (0);
		return 0;
		};

	void 
		ContainerServantRequestInfo::the_exception( const CORBA::Any& value ) {
		assert (0);
	};


#endif
};
