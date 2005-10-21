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

#include "InternalConfiguration.h"
#include "Output.h"


static char rcsid[] UNUSED = "$Id: InternalConfiguration.cpp,v 1.1 2003/09/26 08:30:31 neubauer Exp $";


namespace Qedo {


InternalConfiguration::InternalConfiguration(CCMContext* ctx)
{
	DEBUG_OUT ( "InternalConfiguration: Constructor called" );
	ctx_ = ctx;
}


InternalConfiguration::~InternalConfiguration()
{
	DEBUG_OUT ( "InternalConfiguration: Destructor called" );
}


char* 
InternalConfiguration::get_value( const char* name )
throw (ConfigurationService::UnknownConfiguration, CORBA::SystemException)
{
	char* c;

	if(!strcmp( name, "INSTALLATION_DIR" ))
	{
		 c = strdup( ctx_->ccm_object_executor_->home_servant_->install_dir_.c_str() );
		 return c;
	}

	throw ConfigurationService::UnknownConfiguration();
}


} // namespace Qedo

