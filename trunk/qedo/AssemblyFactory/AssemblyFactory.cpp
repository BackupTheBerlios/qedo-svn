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

static char rcsid[] = "$Id: AssemblyFactory.cpp,v 1.7 2003/04/01 07:50:10 neubauer Exp $";


#include "AssemblyFactory.h"
#include <fstream>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>

#ifndef _WIN32
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#else 
#include <process.h>
#endif


namespace Qedo {


AssemblyFactoryImpl::AssemblyFactoryImpl(CORBA::ORB_ptr orb)
: orb_ (CORBA::ORB::_duplicate (orb))
{
	// Initialize the XML4C2 system once for all instances
	static XMLInitializer ini;
}


AssemblyFactoryImpl::~AssemblyFactoryImpl()
{
}


void
AssemblyFactoryImpl::initialize()
{
    try
	{
		CORBA::Object_var root_poa_obj = orb_->resolve_initial_references ("RootPOA");
		root_poa_ = PortableServer::POA::_narrow (root_poa_obj);
	}
	catch (CORBA::ORB::InvalidName&)
	{
		std::cerr << "..... Fatal error - no root POA available." << std::endl << std::endl;
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		std::cerr << "..... Fatal error - cannot narrow root POA." << std::endl << std::endl;
		throw CannotInitialize();
	}

	root_poa_manager_ = root_poa_->the_POAManager();
	root_poa_manager_->activate();

    // get NameService
    if (! initNameService(orb_))
    {
        throw CannotInitialize();
    }

    // bind AssemblyFactory
	CORBA::Object_var assemblyFactory_ref = this->_this();
    std::string name = "Qedo/AssemblyFactory/";
    char hostname[256];
	gethostname(hostname, 256);
    name.append(hostname);

    if ( ! registerName(name, assemblyFactory_ref, true))
    {
        throw CannotInitialize();
    }

	std::cout << "..... bound under " << name << std::endl << std::endl;

	// directory to put the packages
	packageDirectory_ = getCurrentDirectory() + "/assemblyPackages";
	if (makeDir(packageDirectory_))
	{
		std::cerr << "..... AssemblyPackages directory can not be created" << std::endl;
		throw CannotInitialize();
	}
}


Components::Cookie* 
AssemblyFactoryImpl::create (const char* assembly_loc)
throw (Components::Deployment::InvalidLocation, Components::CreateFailure)
{
	std::cout << "..... creating new assembly for " << assembly_loc << std::endl;

	XMLURL uri(assembly_loc);
    std::string name = XMLString::transcode(uri.getPath());
    std::string::size_type pos = name.find_last_of("/");
    if (pos != std::string::npos)
    {
        name.erase(0, pos + 1);
    }
    
    //
	// ensure the package exists
	//
    std::string comp_loc = packageDirectory_ + "/" + name;
	if ( !checkExistence(comp_loc, IS_FILE))
	{
        URLInputSource inputSource(uri);
        BinInputStream* inputStream = inputSource.makeStream();
        if (!inputStream)
        {
            throw Components::Deployment::InvalidLocation();
        }
        
		std::ofstream packageFile(comp_loc.c_str(), std::ios::binary|std::ios::app);
		if ( ! packageFile)
		{
			std::cerr << "..... Cannot open file " << comp_loc << std::endl;
			throw Components::CreateFailure();
		}
        unsigned char* buf = (unsigned char*)malloc(4096);
        unsigned int len = inputStream->readBytes(buf, 4096);
        while (len)
        {
            packageFile.write((const char*)buf, len);
            len = inputStream->readBytes(buf, 4096);
        }
        free(buf);
		packageFile.close();
	}

	//
	// create new assembly
	//
	Cookie_impl* new_cookie = new Cookie_impl();
	AssemblyImpl* ass = new AssemblyImpl(comp_loc, new_cookie, nameService_);
	assemblies_.push_back(ass);

	std::cout << "..... done" << std::endl << std::endl;

	new_cookie->_add_ref();
	return new_cookie;
}


Components::Deployment::Assembly_ptr 
AssemblyFactoryImpl::lookup (Components::Cookie* c)
throw (Components::Deployment::InvalidAssembly)
{
    // check whether cookie is ok
	std::list < AssemblyImpl* > ::iterator assemblies_iter;
	for (assemblies_iter = assemblies_.begin();
		 assemblies_iter != assemblies_.end();
		 assemblies_iter++)
	{
		if ((**assemblies_iter) == c)
		{
			return (*assemblies_iter)->_this();
		}
	}

	throw Components::Deployment::InvalidAssembly();
}


void 
AssemblyFactoryImpl::destroy (Components::Cookie* c)
throw (Components::Deployment::InvalidAssembly, Components::RemoveFailure)
{
	throw Components::RemoveFailure();
}


}

