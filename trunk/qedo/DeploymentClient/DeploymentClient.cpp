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


#include "DeploymentClient.h"


namespace Qedo {


/**
 *
 */
DeploymentClient::DeploymentClient (CORBA::ORB_ptr orb)
: orb_ (CORBA::ORB::_duplicate (orb))
{
}


/**
 *
 */
DeploymentClient::~DeploymentClient ()
{
}


/**
 *
 */
void
DeploymentClient::initialize()
{
    // get NameService
    if (! initNameService(orb_))
    {
        throw CannotInitialize();
    }

	// get an AssemblyFactory
	char hostname[256];
	gethostname(hostname, 256);
	CORBA::Object_var obj = resolveName(std::string("Qedo/AssemblyFactory/") + hostname);
	assemblyFactory_ = Components::Deployment::AssemblyFactory::_narrow( obj.in() );
    assert( !CORBA::is_nil( assemblyFactory_.in() ) );
}


/**
 *
 */
void
DeploymentClient::create(std::string packageName)
{
	//
	// create assembly
	//
	Components::Cookie* cookie;
	Components::Deployment::Assembly_var assembly;
    std::string uri = "file:///";
    char path[1024];
#ifdef _WIN32
    ::GetCurrentDirectory(1024, path);
    uri.append(path);
    std::string::size_type f = uri.find_first_of("\\");
    while ((f >= 0) && (f < uri.size()))
    {
        uri.replace(f, 1, "/");
        f = uri.find_first_of("\\");
    }
#else
    getcwd(path,1023);
    uri.append(path);
#endif
    uri.append("/");
    uri.append(packageName);

	try
	{
		cookie = assemblyFactory_->create(uri.c_str());
		assembly = assemblyFactory_->lookup(cookie);
	}
	catch( Components::Deployment::InvalidLocation& )
	{
		std::cerr << "InvalidLocation during assembly creation" << std::endl;
		return;
	}
	catch( Components::CreateFailure& )
	{
		std::cerr << "CreateFailure during assembly creation" << std::endl;
		return;
	}
	catch( Components::Deployment::InvalidAssembly& )
	{
		std::cerr << "InvalidAssembly during assembly creation" << std::endl;
		return;
	}
	catch( CORBA::SystemException& ex )
	{
		std::cerr << "CORBA system exception during assembly creation : " << ex << std::endl;
		throw;
	}

	//
	// build assembly
	//
	std::cout << "Start the assembly!\n" << std::endl;
	try
	{
		assembly->build();
	}
	catch( Components::CreateFailure& ex )
	{
		std::cerr << "CreateFailure exception during assembly building : " << ex << std::endl;
		return;
	}
	catch( CORBA::SystemException& ex )
	{
		std::cerr << "CORBA system exception during assembly building : " << ex << std::endl;
		throw;
	}
	
	//
	// wait
	//
    std::cout << "Please press any key to destroy the Assembly ..." << std::endl;
    getchar();
	
	//
	// tear down assembly
	//
	std::cout << "Stop the assembly!" << std::endl;
	try
	{
		assembly->tear_down();
	}
	catch( Components::RemoveFailure& ex )
	{
		std::cerr << "RemoveFailure exception during tear down assembly : " << ex << std::endl;
		return;
	}
	catch( CORBA::SystemException& ex )
	{
		std::cerr << "CORBA system exception during tear down assembly : " << ex << std::endl;
		throw;
	}
}


}