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

#ifdef _WIN32
#include "process.h"
#include "Winsock2.h"
#include "windows/unistd.h"

#endif



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
	
	
	//CORBA::ORB_var e_orb=CORBA::ORB_init(e_argc,e_argv);

	// get name services reference
	CORBA::Object_var nsobj = e_orb->resolve_initial_references("NameService");
	CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(nsobj);
	CORBA::Object_var saobj = e_orb ->resolve_initial_references("NameService");
		
	/*
	if (CORBA::is_nil(nc)) {

		cerr << "Kann den Naming Service nicht finden!" << endl;
		cin >> t;
		exit(1);

	}
	
	if (CORBA::is_nil(saobj)) {
		cout << "ServerActivator kann nicht gefunden werden" << endl;
		cin >>  t;
		exit(1);
	} */



	// get server activator reference
	char hostname[256];
	//int gethostname;
	 gethostname (hostname, 256);
	if (gethostname (hostname, 256))
	{
		std::cout<< "Kann Hostname nicht finden"<<endl;
		e_orb->destroy();
		exit(1);
	}
	
	
	CosNaming::Name cname;
	cname.length(2);
	cname[0].id=CORBA::string_dup("Qedo");
	cname[0].kind=CORBA::string_dup("");
	cname[1].id=CORBA::string_dup("Activators");
	cname[1].kind=CORBA::string_dup("");
	
		
	CosNaming::NamingContext_var ncQA = CosNaming::NamingContext::_nil();
	CORBA::Object_var obj = nc->resolve(cname);
	ncQA = CosNaming::NamingContext::_narrow (obj);

	
	CORBA::Object_var server_activator_obj;
		server_activator_obj=nc->resolve(cname);
		CosNaming::BindingList *test;
		CosNaming::BindingIterator *test2;
		ncQA->list(100,test,test2);



		CosNaming::BindingList_var bl = test;
		CosNaming::BindingIterator_var bi = test2;
		std::cout<< bl->length() << " ServerActivator gefunden" << endl;
		

	ComponentServerActivatorInfoList_var Activatorlist=new ComponentServerActivatorInfoList;
	for (int as=0;as<bl->length();as++) {

			
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
	}
	catch (CosNaming::NamingContext::CannotProceed_catch &exec) {
		std::cerr << "CannotProceed" <<endl;
	}
	catch (CosNaming::NamingContext::InvalidName_catch &exec) {
		std::cout << "InvalidName exception"<<endl;
	}

	
	Components::Deployment::ServerActivator_var server_activator ;
	try {
		server_activator= Components::Deployment::ServerActivator::_narrow(server_activator_obj);
	} 
	catch (CORBA::SystemException&) 
	{
		std::cout<<"Cannon narrow"<<endl;
		e_orb->destroy();
		exit(1);
	}
	

	
	// get Component Servers
	
	Components::Deployment::ComponentServers *component_servers = 
	server_activator -> get_component_servers();
	

	std::cout << "ServerActivator liefert " << component_servers->length() << " Component Server"<< endl;

	
	ComponentServerActivatorInfo ComponentServerActivator;
	const char* host="schlepptop";
	ComponentServerActivator.host_name=(const char*)hostname;
	ComponentServerActivator.component_server_activator_ref=server_activator;
	
	ComponentServerInfoList ComponentServerList;
	ComponentServerList.length(component_servers->length());
	

	for (int i=1; i<=component_servers->length(); i++) {
		
	std::cout<<"ComponentServer " << i-1 << endl;	


		Components::Deployment::ComponentServer_var comp_server = 
			Components::Deployment::ComponentServer::_duplicate((*component_servers)[i-1]);

		ComponentServerInfo ComponentServer;

		// Der Hostname muss noch gefunden werden

		const char* host="schlepptop";
		ComponentServer.host_name=(const char*)hostname;
		ComponentServer.component_server_ref=comp_server;

		Components::Deployment::Containers *comp_containers = 
			comp_server->get_containers();
		ContainerInstanceInfoList ContainerList;
		ContainerList.length(comp_containers->length());

		std::cout<< " ->" << comp_containers->length() << " Container"<<endl;



		for (int y=1; y<=comp_containers->length(); y++) {
			std::cout<<"    " << y-1 << " Container" << endl;
			
			
			Components::Deployment::Container_var container = 
				Components::Deployment::Container::_duplicate((*comp_containers)[y-1]);
			
			ContainerInstanceInfo ContainerInfo;
			const char* egal="SESSION";
			
			ContainerInfo.short_name=egal;
			ContainerInfo.container_ref=container;
		   // Components::Deployment::ComponentServer_var test = container->get_component_server();
            Components::CCMHomes *homes = container->get_homes();
			
			HomeInstanceInfoList HomeList;
			HomeList.length(homes->length());
			std::cout<< "  ->" << homes->length() << " Homes" << endl;

			for (int z=1; z<=homes->length(); z++) {

				std::cout<<"     " << z-1 << " Home" << endl;

				Components::CCMHome_var home = 
					Components::CCMHome::_duplicate((*homes)[z-1]);

				HomeInstanceInfo HomeInfo;
				HomeInfo.full_scoped_name=home->get_home_rep_id();
				//std::cout << z << " " << home->get_home_rep_id() << endl;
				std::cout << "    " <<  z-1 << get_short_name(HomeInfo.full_scoped_name)<<endl;
				
				HomeInfo.short_name=get_short_name(HomeInfo.full_scoped_name).c_str();
				//std::cout << "HomeInfo" << HomeInfo.short_name << " " <<  endl;
				HomeInfo.home_ref=home;
				Components::CCMObjects *homeinstances = home->get_instances();
				
				ComponentInstanceInfoList ComponentList;
				ComponentList.length(homeinstances->length());


				for (int a=1; a<=homeinstances->length(); a++) {
				
					Components::CCMObject_var inst=
						Components::CCMObject::_duplicate((*homeinstances)[a-1]);

					ComponentInstanceInfo ComponentInfo;
					//std::cout<<a-1<<endl;
					ComponentInfo.full_scoped_name=home->get_component_rep_id();
					//std::cout<< a-1 << ":" << home->get_component_rep_id()<<endl;
					std::cout<< "        " << a-1 << get_short_name(home->get_component_rep_id()).c_str() << endl;;
					ComponentInfo.short_name=get_short_name(home->get_component_rep_id()).c_str();	
					ComponentInfo.compont_ref=inst;
					ComponentList[a-1]=ComponentInfo;

                } // Ende Components
				
				HomeInfo.my_components=ComponentList;
				HomeList[z-1]=HomeInfo;

			} // Ende Homes
			ContainerInfo.my_homes=HomeList;
			ContainerList[y-1]=ContainerInfo;
		
		} // Ende Container

		ComponentServer.my_containers=ContainerList;
		ComponentServerList[i-1]=ComponentServer;

	} // Ende ComponentServers
	ComponentServerActivator.my_component_servers=ComponentServerList;
	
	
	Activatorlist->length(bl->length());
		
	Activatorlist.inout()[as]=ComponentServerActivator;
	
}
	
//	ComponentServerActivatorInfoList* wert = Activatorlist;
	 
   return Activatorlist._retn() ;


}
