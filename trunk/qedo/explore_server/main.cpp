/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
/*                                                                         */
/* http://www.qedo.org                                                     */
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

#include "explore.h"
#include "iostream"
#include "string"
#include "coss/CosNaming.h"
#include "Explore_impl.h"
#include "Output.h"
#include "ConfigurationReader.h"

using namespace std;



int main (int argc, char** argv)

{
	Qedo::debug_output = false;
	//
	// Resolve config values from config file
	//
	if ( Qedo::ConfigurationReader::instance()->lookup_config_value ("/General/VerboseOutput") == "true")
	{
		Qedo::debug_output = true;
	}

	for (int i = 1; i < argc; i++)
	{
		if (! strcmp (argv[i], "--verbose"))
		{
			Qedo::debug_output = true;
		}
	}

	try{


		// Initialize orb
		CORBA::ORB_var orb=CORBA::ORB_init(argc,argv);

		// Get reference to Root POA
		CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
		PortableServer::POA_var poa=PortableServer::POA::_narrow(obj);

		//Activate POA Manager
		PortableServer::POAManager_var mgr=poa->the_POAManager();

		//Create an Object
		Explore_impl *impl = new Explore_impl;
		impl->e_argc=argc;
		impl->e_argv=argv;
		impl->e_orb=orb;

		//Activate the servant
		Explore_var f=impl->_this();

		// resolve the naming service
		CORBA::Object_var nsobj= orb->resolve_initial_references("NameService");
		if (CORBA::is_nil(nsobj)) {
			std::cerr << "Cannot resolve NameService" << endl;
			exit(1);
		}

		//narrow the root naming context
		CosNaming::NamingContext_var nc=CosNaming::NamingContext::_narrow(nsobj);

	    CosNaming::NamingContext_var context;
		CosNaming::Name contextName;
		contextName.length(1);
		contextName[0].id = CORBA::string_dup("Qedo");
		contextName[0].kind = CORBA::string_dup("");

		try
		{
			context = nc->bind_new_context(contextName);
		}
		catch (const CosNaming::NamingContext::AlreadyBound&)
		{
			// nothing to do
		}

		//create a name entry
		CosNaming::Name name;
		name.length(2);
		name[0].id=CORBA::string_dup("Qedo");
		name[0].kind=CORBA::string_dup("");
		name[1].id=CORBA::string_dup("ExploreServer");
		name[1].kind=CORBA::string_dup("");

		//bind or rebind the servant to the naming service
		try {
			nc->bind(name,f);
		}
		catch (CosNaming::NamingContext::AlreadyBound_catch &ex) {
			nc->rebind(name,f);
		}

		/*CORBA::String_var s=orb->object_to_string(f);
		std::cout<<s<<endl;
		*/
		
		
		/*PortableServer::ObjectId_var oid=poa->activate_object(impl);
		CORBA::Object_var ref=poa->id_to_reference(oid.in());*/
		
		
		//activate POA Manager
		mgr->activate();

		//Accept request
		std::cout<<"Explore Server is running..."<<endl;
		//run the orb
		orb->run();
		
		// remove reference from NameService
		nc -> unbind(name);

		poa->destroy(TRUE,TRUE);
		delete impl;
	

	}
	catch (const CORBA::SystemException_catch& ex) {
		
		
		std::cout<< ex << "Uncaught CORBA exception"<<endl;
		
	}

	return 0;
}

