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

#include "Explore_impl.h"
#include "explore.h"
#include "iostream"
#include "string"
#include "coss/CosNaming.h"
//#include <strstream>
#include <sstream>
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
//#include "util.h"

#include "Output.h"




using namespace std;

//int global_argc;
//char** global_argv;

string get_short_name(char *full_scope_name) {
// Liefer den short_name von der RepID zurück

	
	int len = strlen(full_scope_name); // Die Länge des Strings ermitteln
	int ende, start; // Start und Ende Position in der RepID
	
	const char* short_name="" ; // Rückgabe wert
	
	// Start und Ende Position finden 
	// Trennzeichen sind : für Ende
	// "/" für start Position

	for (int i=len; i>0; i--) {
		
		if (full_scope_name[i]==':') {
			ende=i;
		}

		if (full_scope_name[i]=='/') {
			start=i+1;
			i=0;
		}
	}

	string helpstring=((string) full_scope_name).substr(start,ende-start);
	short_name=helpstring.c_str();

	//std::cout << full_scope_name << "->" << short_name << endl;

	return helpstring;
	
}


::ComponentServerActivatorInfoList* Explore_impl::explore_qedo()
{	
	
	// get name services reference
	CORBA::Object_var nsobj = e_orb -> resolve_initial_references("NameService");
	CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(nsobj);

	// get server activator reference
	char hostname[256];
	//int gethostname;
	gethostname (hostname, 256);
	if (gethostname (hostname, 256))
	{
		std::cout<< "No hostname found"<<endl;
		e_orb -> destroy();
		exit(1);
	}
	
	
	CosNaming::Name cname;
	cname.length(2);
	cname[0].id=CORBA::string_dup("Qedo");
	cname[0].kind=CORBA::string_dup("");
	cname[1].id=CORBA::string_dup("Activators");
	cname[1].kind=CORBA::string_dup("");
	
		
	CosNaming::NamingContext_var ncQA = CosNaming::NamingContext::_nil();
	CORBA::Object_var obj = nc -> resolve(cname);
	ncQA = CosNaming::NamingContext::_narrow (obj);

	
	CORBA::Object_var server_activator_obj;
	server_activator_obj = nc -> resolve(cname);
	CosNaming::BindingList *test;
	CosNaming::BindingIterator *test2;
	ncQA -> list(100,test,test2);

	CosNaming::BindingList_var bl = test;
	CosNaming::BindingIterator_var bi = test2;
	DEBUG_OUT2 (bl -> length() , " ServerActivator gefunden");
		

	ComponentServerActivatorInfoList_var Activatorlist = new ComponentServerActivatorInfoList;
	Activatorlist -> length(0);
	CORBA::ULong as = 0;
	for (as = 0 ; as < bl -> length() ; as++) {
        CosNaming::Binding b=bl->operator [](as);
		
		CosNaming::Name name;
		name.length(3);
		name[0].id=CORBA::string_dup("Qedo");
		name[0].kind=CORBA::string_dup("");
		name[1].id=CORBA::string_dup("Activators");
		name[1].kind=CORBA::string_dup("");
		name[2].id=CORBA::string_dup(b.binding_name[0].id);
		name[2].kind=CORBA::string_dup("");

		try {
			std::cout<< "ServerActivator: " << b.binding_name[0].id << endl;
			server_activator_obj=nc->resolve(name);

		}
		catch (CosNaming::NamingContext::NotFound_catch &exec) {
			std::cerr << "Notfound" << endl;
			continue;
		}
		catch (CosNaming::NamingContext::CannotProceed_catch &exec) {
			std::cerr << "CannotProceed" <<endl;
			continue;
		}
		catch (CosNaming::NamingContext::InvalidName_catch &exec) {
			std::cout << "InvalidName exception"<<endl;
			continue;
		}
	
		Components::Deployment::ServerActivator_var server_activator ;
		try {
			server_activator = Components::Deployment::ServerActivator::_narrow(server_activator_obj);
		} 
		catch (CORBA::SystemException&) 
		{
			std::cout<<"Cannon narrow"<<endl;
			e_orb -> destroy();
			continue;
		}
	
		Components::Deployment::ComponentServers *component_servers; 
		try {
			// get Component Servers	
			component_servers = 
				server_activator -> get_component_servers();	
		} catch (CORBA::SystemException&) 
		{
			continue;
		} catch(...)
		{
			continue;
		};

		DEBUG_OUT3 ( "ServerActivator has ", component_servers->length() , " component server. ");

		ComponentServerActivatorInfo ComponentServerActivator;
		const char* host="schlepptop";
		ComponentServerActivator.host_name=CORBA::string_dup(b.binding_name[0].id);
		ComponentServerActivator.component_server_activator_ref=server_activator;
	
		ComponentServerInfoList ComponentServerList;
		ComponentServerList.length(0);
	
		CORBA::ULong i=0;
		for (i = 0 ; i < component_servers->length(); i++) {
			
			DEBUG_OUT2( "ComponentServer " , i );	

			Components::Deployment::ComponentServer_var comp_server = 
				Components::Deployment::ComponentServer::_duplicate((*component_servers)[i]);

			ComponentServerInfo ComponentServer;

			// the information about the host name ist missing
			// should be removed
			const char* host="schlepptop";
			ComponentServer.host_name=(const char*)CORBA::string_dup(b.binding_name[0].id);
			ComponentServer.component_server_ref=comp_server;

			Components::Deployment::Containers *comp_containers; 

			try {
					comp_containers = comp_server->get_containers();
			} catch (...) 
			{
				continue;
			}

			ContainerInstanceInfoList ContainerList;
			ContainerList.length(comp_containers->length());

			DEBUG_OUT3 (" ->", comp_containers->length() , " Container");
			CORBA::ULong y = 0;
			for ( y = 0; y < comp_containers->length(); y++) {
				DEBUG_OUT3 ("    " , y , " Container");
	
				Components::Deployment::Container_var container = 
					Components::Deployment::Container::_duplicate((*comp_containers)[y]);
			
				ContainerInstanceInfo ContainerInfo;
				const char* egal="SESSION";
			
				ContainerInfo.short_name=egal;
				ContainerInfo.container_ref=container;
	            Components::CCMHomes *homes = container->get_homes();

				HomeInstanceInfoList HomeList;
				HomeList.length(homes->length());

				DEBUG_OUT3 ("  ->", homes->length() , " Homes");
				CORBA::ULong z = 0;
				for (z = 0; z < homes->length(); z++) {

					DEBUG_OUT3 ("     ", z , " Home" );
					Components::CCMHome_var home = 
						Components::CCMHome::_duplicate((*homes)[z]);

					HomeInstanceInfo HomeInfo;
					HomeInfo.full_scoped_name=home->get_home_rep_id();
					DEBUG_OUT3 ("    " ,  z , get_short_name(HomeInfo.full_scoped_name));
				
					HomeInfo.short_name=get_short_name(HomeInfo.full_scoped_name).c_str();
					HomeInfo.home_ref=home;
					Components::CCMObjects *homeinstances = home->get_instances();
				
					ComponentInstanceInfoList ComponentList;
					ComponentList.length(homeinstances->length());

					CORBA::ULong a = 0;
					for (int a = 0; a < homeinstances -> length(); a++) {
				
						Components::CCMObject_var inst=
							Components::CCMObject::_duplicate((*homeinstances)[a]);

						ComponentInstanceInfo ComponentInfo;
						ComponentInfo.full_scoped_name=home->get_component_rep_id();
						DEBUG_OUT3 ("        ", a , get_short_name(home->get_component_rep_id()).c_str());
						ComponentInfo.short_name=get_short_name(home->get_component_rep_id()).c_str();	
						ComponentInfo.compont_ref=inst;
						ComponentList[a]=ComponentInfo;

	                } // end Components
				
					HomeInfo.my_components=ComponentList;
					HomeList[z]=HomeInfo;

				} // end Homes

				ContainerInfo.my_homes=HomeList;
				ContainerList[y]=ContainerInfo;
		
			} // end Container

			ComponentServer.my_containers=ContainerList;
			ComponentServerList.length( ComponentServerList.length() + 1 );
			ComponentServerList[ComponentServerList.length()-1] = ComponentServer;

		} // ende ComponentServers

		ComponentServerActivator.my_component_servers=ComponentServerList;	
		Activatorlist->length(bl->length());
		
		Activatorlist.inout()[as]=ComponentServerActivator;
	
	}
		 
   return Activatorlist._retn() ;

}
