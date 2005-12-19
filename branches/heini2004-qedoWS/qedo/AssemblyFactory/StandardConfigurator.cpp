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

#include "StandardConfigurator.h"
#include "Output.h"
#include <string>
#ifdef TAO_ORB
#include "DynamicInterface/Request.h"
#endif

namespace Qedo {


StandardConfiguratorImpl::StandardConfiguratorImpl
()
{
}


StandardConfiguratorImpl::~StandardConfiguratorImpl
()
{
}


void 
StandardConfiguratorImpl::configure(::Components::CCMObject_ptr comp)
throw( Components::WrongComponentType )
{
	for(CORBA::ULong i = 0; i < config_.length(); i++ )
	{
		DEBUG_OUT2( ".......... configure ", config_[i]->name() );

		//
		// create a request according to the wire format of attribute operations
		//
		std::string operation = "_set_";
		operation.append( config_[i]->name() );
		CORBA::Request_ptr request = comp->_request( operation.c_str() );
		request->add_in_arg() = config_[i]->value();

		//
		// send the request
		//
		try
		{
 			request->invoke();
		}
		catch( CORBA::SystemException& ex )
		{
 			NORMAL_ERR2( "StandardConfigurator: unexpected System Exception ", &ex );
		}

		//
		// check for exceptions
		//
		CORBA::ExceptionList_ptr ex_list = request->exceptions();
		if ( ex_list->count() > 0 )
		{
			NORMAL_ERR2( "StandardConfigurator: exception during configuration of attribute ", config_[i]->name() );
		}
	}
}


void 
StandardConfiguratorImpl::set_configuration(const ::Components::ConfigValues& descr)
throw (CORBA::SystemException)
{
	config_ = descr;
}


}
