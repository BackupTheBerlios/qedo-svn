#include "explore.h"
#include "iostream"
#include "string"
#include "coss/CosNaming.h"
#include "Explore_impl.h"


using namespace std;


/*

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
*/











int main (int argc, char** argv)

{
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

		//create a name entry
		CosNaming::Name name;
		name.length(1);
		name[0].id=CORBA::string_dup("ExploreServer");
		name[0].kind=CORBA::string_dup("");

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

		poa->destroy(TRUE,TRUE);
		delete impl;
	

	}
	catch (const CORBA::SystemException_catch& ex) {
		
		
		std::cout<< ex << "Uncaught CORBA exception"<<endl;
		
	}

	return 0;
}

