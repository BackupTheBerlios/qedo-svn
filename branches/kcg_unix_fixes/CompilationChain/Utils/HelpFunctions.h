#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include <CORBA.h>
#include <fstream>
//#include "Exceptions.h"
#include "RepositoryConnector.h"

using namespace std;
namespace CCMGenerator {

class HelpFunctions
{
	public:
	HelpFunctions ();
	~HelpFunctions();
		
	static void new_line ( ostream& out, unsigned long indent_level = 0);
	static void inc_indent_level ( unsigned long & indent_level );
	static void dec_indent_level ( unsigned long & indent_level );
	static std::string convert_uml_string_in_path (std::string uml_string);
	static CORBA::Object_ptr get_repository_ref ( CORBA::ORB_ptr orb );
	
};

	
}
#endif