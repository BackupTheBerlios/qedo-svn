/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This program is free software; you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by the   */
/* Free Software Foundation; either version 2 of the License,              */
/* or (at your option) any later version.                                  */
/*                                                                         */
/* This program is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                    */
/* See the GNU General Public License for more details.                    */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with this program; if not, write to the Free Software Foundation, */
/* Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA             */
/***************************************************************************/


#include "ComponentDeployment.h"

#ifndef _WIN32
#include <unistd.h>
#endif


namespace Qedo {


ComponentDeployment::ComponentDeployment(std::string uri)
{
	uri_ = uri;
}


ComponentDeployment::~ComponentDeployment()
{
}


void
ComponentDeployment::init()
throw (DeploymentFailure)
{
	int dummy = 0;
	CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);

    //
	// get NameService
	//
    if (! initNameService(orb))
    {
        throw DeploymentFailure();
    }

	//
	// try to get a local AssemblyFactory
	//
	char hostname[256];
	gethostname(hostname, 256);
	CORBA::Object_var obj = resolveName(std::string("Qedo/AssemblyFactory/") + hostname);
	assemblyFactory_ = Components::Deployment::AssemblyFactory::_narrow( obj.in() );
    if( !CORBA::is_nil( assemblyFactory_.in() ) && 
		!assemblyFactory_->_non_existent() )
	{
		std::cerr << "..... take assembly factory on " << hostname << std::endl;
		return;
	}

	//
	// try to get another one
	//
	std::cerr << "..... no local assembly factory, try to get another one" << std::endl;

	obj = resolveName(std::string("Qedo/AssemblyFactory"));
	CosNaming::NamingContext_var ctx = CosNaming::NamingContext::_narrow( obj.in() );
	if( !CORBA::is_nil( ctx.in() ) )
	{
		CosNaming::BindingList_var list;
		CosNaming::BindingIterator_var iter;
		try
		{
			ctx->list(10, list.out(), iter.out());
		}
		catch (...)
		{
		}

		for(CORBA::ULong i = 0; i < list->length(); i++)
		{
			try
			{
				obj = ctx->resolve(list[i].binding_name);
			}
			catch (...)
			{
				continue;
			}
			assemblyFactory_ = Components::Deployment::AssemblyFactory::_narrow( obj.in() );
			if( !CORBA::is_nil( assemblyFactory_.in() ) &&
				!assemblyFactory_->_non_existent() )
			{
				std::cerr << "..... take assembly factory on " << list[i].binding_name[0].id << std::endl;
				return;
			}
		}
	}

	//
	// use our own assembly
	//
	// todo


	std::cerr << "!!!!! no assembly factory found" << std::endl;
	throw DeploymentFailure();
}


void
ComponentDeployment::deploy()
throw (DeploymentFailure)
{
	init();

	//
	// create assembly
	//
	try
	{
		cookie_ = assemblyFactory_->create_assembly(uri_.c_str());
		assembly_ = assemblyFactory_->lookup(cookie_);
	}
	catch( Components::Deployment::InvalidLocation& )
	{
		std::cerr << "InvalidLocation during assembly creation" << std::endl;
		throw DeploymentFailure();
	}
	catch( Components::CreateFailure& )
	{
		std::cerr << "CreateFailure during assembly creation" << std::endl;
		throw DeploymentFailure();
	}
	catch( Components::Deployment::InvalidAssembly& )
	{
		std::cerr << "InvalidAssembly during assembly creation" << std::endl;
		throw DeploymentFailure();
	}
	catch( CORBA::SystemException& ex )
	{
		std::cerr << "CORBA system exception during assembly creation : " << ex << std::endl;
		throw DeploymentFailure();
	}

	//
	// build assembly
	//
	try
	{
		assembly_->build();
	}
	catch( Components::CreateFailure& ex )
	{
		std::cerr << ".......... CreateFailure exception during assembly building : " << ex << std::endl;
		throw DeploymentFailure();
	}
	catch( CORBA::SystemException& ex )
	{
		std::cerr << ".......... CORBA system exception during assembly building : " << ex << std::endl;
		throw DeploymentFailure();
	}
}


void
ComponentDeployment::undeploy()
throw (DeploymentFailure)
{
	//
	// tear down assembly
	//
	try
	{
		assembly_->tear_down();
	}
	catch( Components::RemoveFailure& ex )
	{
		std::cerr << ".......... RemoveFailure exception during tear down assembly : " << ex << std::endl;
		throw DeploymentFailure();
	}
	catch( CORBA::SystemException& ex )
	{
		std::cerr << ".......... CORBA system exception during tear down assembly : " << ex << std::endl;
		throw DeploymentFailure();
	}
}


}

