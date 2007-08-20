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

#ifndef __CONTAINER_SERVER_REQUEST_INFO_H__
#define __CONTAINER_SERVER_REQUEST_INFO_H__

#ifndef _QEDO_NO_QOS

#include <CORBA.h>
#include <Components.h>
#include "RefCountBase.h"
#include "Util.h"

namespace Qedo {

class CONTAINERDLL_API ContainerServerRequestInfo : public virtual Components::ContainerPortableInterceptor::ContainerServerRequestInfo,
	public virtual RefCountLocalObject
{
private:
    CORBA::OctetSeq_var	origin_id_;
    CORBA::OctetSeq_var	target_id_;
	std::string	    name_;

	PortableInterceptor::ServerRequestInfo_var request_info_;

public:
    ContainerServerRequestInfo (
        PortableInterceptor::ServerRequestInfo_ptr request_info, 
        const CORBA::OctetSeq& origin_id, 
        const CORBA::OctetSeq& target_id, 
        const Components::FeatureName name);

	~ContainerServerRequestInfo ();

    virtual ::CORBA::OctetSeq* origin_id();
    virtual ::CORBA::OctetSeq* target_id();

	virtual Components::FeatureName name();

    virtual PortableInterceptor::ServerRequestInfo_ptr request_info() ;
};

} //namespace Qedo
#endif
#endif
