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


#include "AssemblyFactory.h"
#include "qedoutil.h"
#include "ConfigurationReader.h"
#include "DOMXMLParser.h"
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


static char rcsid[] UNUSED = "$Id: AssemblyFactory.cpp,v 1.18 2003/10/27 12:21:50 neubauer Exp $";


namespace Qedo {


AssemblyFactoryImpl::AssemblyFactoryImpl(CORBA::ORB_ptr orb)
: orb_ (CORBA::ORB::_duplicate (orb))
{
	// Initialize the XML4C2 system once for all instances
	static XMLInitializer ini;

	deployment_dir_ = Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/Deployment/BaseDir");

	if ( deployment_dir_.empty() )
	{
		deployment_dir_ =  g_qedo_dir + "/deployment" ;
	}

	packageDirectory_ = deployment_dir_ + "/assemblypackages";
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
		NORMAL_ERR( "AssemblyFactoryImpl: no root POA available" );
		throw CannotInitialize();
	}
	catch (CORBA::SystemException&)
	{
		NORMAL_ERR( "AssemblyFactoryImpl: cannot narrow root POA" );
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

	DEBUG_OUT2( "AssemblyFactoryImpl: bound under ", name );;

	//
	// directory to put the packages
	//
	if (makeDir(packageDirectory_))
	{
		NORMAL_ERR3( "AssemblyFactoryImpl: directory ", packageDirectory_, " can not be created");
		throw CannotInitialize();
	}
}


Components::Cookie* 
AssemblyFactoryImpl::create_assembly (const char* assembly_loc)
throw (Components::Deployment::InvalidLocation, Components::CreateFailure)
{
	DEBUG_OUT2( "AssemblyFactoryImpl: creating new assembly for ", assembly_loc );

	//
	// exclusive
	//
	QedoLock lock(&mutex_);

	//
	// get path
	//
	XMLURL uri(assembly_loc);
	const XMLCh* p = uri.getPath();
	if(!p)
	{
		NORMAL_ERR( "AssemblyFactoryImpl: invalid assembly location" );
		throw Components::Deployment::InvalidLocation();
	}
	std::string name = XMLString::transcode(p);
    std::string::size_type pos = name.find_last_of("/");
    if (pos != std::string::npos)
    {
        name.erase(0, pos + 1);
    }

	//
	// make input stream
	//
	URLInputSource inputSource(uri);
	BinInputStream* inputStream;
	try
	{
		inputStream = inputSource.makeStream();
	}
	catch(...)
	{
		NORMAL_ERR( "AssemblyFactoryImpl: invalid assembly location" );
		throw Components::Deployment::InvalidLocation();
	}
    if (!inputStream)
    {
		NORMAL_ERR( "AssemblyFactoryImpl: invalid assembly location" );
		throw Components::Deployment::InvalidLocation();
    }

	//
	// create new cookie
	//
	Cookie_impl* new_cookie = new Cookie_impl();
	std::string uuid = new_cookie->to_string();

	//
	// store the package
	//
	std::string dir = getPath( packageDirectory_ ) + uuid;
	if( makeDir(dir) )
	{
		NORMAL_ERR3( "AssemblyFactoryImpl: directory ", dir, " can not be created");
		throw Components::CreateFailure();
	}

	std::string package_name = getPath( dir ) + name;
	std::ofstream packageFile(package_name.c_str(), std::ios::binary|std::ios::app);
	if ( ! packageFile)
	{
		NORMAL_ERR2( "AssemblyFactoryImpl: cannot open file ", package_name );
		throw Components::CreateFailure();
	}
    unsigned char* buf = new unsigned char[4096];
    unsigned int len = inputStream->readBytes(buf, 4096);
    while (len)
    {
		packageFile.write((const char*)buf, len);
		len = inputStream->readBytes(buf, 4096);
	}
	delete [] buf;
	packageFile.close();
	delete inputStream;

	//
	// create new assembly
	//
	AssemblyImpl* ass = new AssemblyImpl(package_name, new_cookie, nameService_);
	assemblies_.push_back(ass);

	DEBUG_OUT( "..... done" );

	return new_cookie;
}


Components::Deployment::Assembly_ptr 
AssemblyFactoryImpl::lookup (Components::Cookie* c)
throw (Components::Deployment::InvalidAssembly)
{
	//
	// exclusive
	//
	QedoLock lock(&mutex_);

	AssemblyImpl* ass;
	std::list < AssemblyImpl* > ::iterator iter;
	for(iter = assemblies_.begin();
		iter != assemblies_.end();
		iter++)
	{
		ass = (*iter);
		if( *ass == c )
		{
			return ass->_this();
		}
	}

	throw Components::Deployment::InvalidAssembly();
}


void 
AssemblyFactoryImpl::destroy (Components::Cookie* c)
throw (Components::Deployment::InvalidAssembly, Components::RemoveFailure)
{
	//
	// exclusive
	//
	QedoLock lock(&mutex_);

	AssemblyImpl* ass;
	std::list < AssemblyImpl* > ::iterator iter;
	for(iter = assemblies_.begin();
		iter != assemblies_.end();
		iter++)
	{
		ass = (*iter);
		if( *ass == c)
		{
			root_poa_->deactivate_object( *(root_poa_->servant_to_id(ass)) );

			std::string dir = getPath( packageDirectory_ ) + ass->get_uuid();
			if( removeDir(dir) )
			{
				NORMAL_ERR2( "AssemblyFactoryImpl: could not remove directory ", dir );
			}
			ass->_remove_ref();
			assemblies_.erase( iter );
			return;
		}
	}

	throw Components::Deployment::InvalidAssembly();
}


}

