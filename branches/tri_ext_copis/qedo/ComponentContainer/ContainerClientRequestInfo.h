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

#ifndef __CONTAINER_CLIENT_REQUEST_INFO_H__
#define __CONTAINER_CLIENT_REQUEST_INFO_H__

#ifndef _QEDO_NO_QOS

#include <CORBA.h>
#include <Components.h>
#include "RefCountBase.h"
#include "Util.h"

namespace Qedo {

class CONTAINERDLL_API ContainerClientRequestInfo : public virtual Components::ContainerPortableInterceptor::ContainerClientRequestInfo,
	public virtual RefCountLocalObject
{
private:
	/** the identity of this component */
	std::string		origin_id_;
	std::string		target_id_;
	std::string		name_;

	PortableInterceptor::ClientRequestInfo_var request_info_;

public:
	ContainerClientRequestInfo (PortableInterceptor::ClientRequestInfo_ptr request_info, const char* origin_id, const char* target_id, const Components::FeatureName name);

	~ContainerClientRequestInfo ();

	virtual char* origin_id() ;

	virtual char* target_id() ;

	virtual Components::FeatureName name();

    virtual PortableInterceptor::ClientRequestInfo_ptr request_info() ;
};


class CONTAINERDLL_API ContainerStubRequestInfo : public virtual Components::ContainerPortableInterceptor::ContainerStubRequestInfo,
	public virtual RefCountLocalObject
{
private:
	/** the identity of this component */
	std::string		origin_id_;
	std::string		target_id_;
	std::string		name_;
	std::string		operation_name_;

	Dynamic::ParameterList_var arguments_;

public:
	ContainerStubRequestInfo (Dynamic::ParameterList* arguments, const char* origin_id, const char* target_id, const Components::FeatureName name);

	~ContainerStubRequestInfo ();

	virtual char* origin_id() ;

	virtual char* target_id() ;

	virtual Components::FeatureName name();

	virtual Dynamic::ParameterList* arguments() ;

	virtual void arguments( const ::Dynamic::ParameterList& value );

    virtual char* operation();

	virtual void operation( const char* value ) ;
};


} //namespace Qedo
#endif
#endif
