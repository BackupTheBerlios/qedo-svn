#include <iostream>
using namespace std;
#include "HelpFunctions.h"

namespace CCMGenerator
{
HelpFunctions::HelpFunctions ()
{}

HelpFunctions::~HelpFunctions()
{}
void HelpFunctions::inc_indent_level ( unsigned long & indent_level )
{
	indent_level++;
}

void HelpFunctions::dec_indent_level ( unsigned long & indent_level )
{
	if ( indent_level > 0 )
		indent_level--;
}

void HelpFunctions::new_line ( ostream& out, unsigned long indent_level )
{
	out << endl;
	for ( unsigned long i = 0; i < indent_level; i++ ) out << "\t";
}
std::string HelpFunctions::convert_uml_string_in_path (std::string uml_string)
{
	uml_string.replace ( uml_string.find( "::" ),2,"/" );
	return uml_string;
}
CORBA::Object_ptr HelpFunctions::get_repository_ref ( CORBA::ORB_ptr orb )
{
	try
	{
		if ( CORBA::is_nil ( orb ) )
			return 0;
	
		char * mda_etc_var = getenv ( "MDA_ETC" );
		std::string myRef;

		if ( mda_etc_var != NULL )
		{
			myRef = std::string ( mda_etc_var ) + "\\RepositoryRoot.ref";
		} 
		else 
		{
			throw ReferenceRepositoryFileNotFound ( "MDA_ETC environment variable not found !" );
		}

		ifstream in;
		in.open ( myRef.c_str() );
		if ( ! ( in.is_open () ) ) 
		{
			std::string message ( "The Reference repository file \"" );
			message += myRef;
			message += "\" is not found!";
			throw ReferenceRepositoryFileNotFound ( mda_etc_var );
		}

		char ref_[2048];
		in >> ref_;
		in.close ();

		CORBA::Object_var obj_;

		if ( strcmp ( ref_, "" ) )
			 obj_ = orb->string_to_object ( ref_ );
		else
			throw NilObjectRef ( "String to Object by ORB initialization failed!" );

		if( CORBA::is_nil ( obj_.in () ) ) 
		{
			throw NilObjectRef ( "String to Object by ORB initialization failed!" );
		}
		
		/*M2C::MOFRepository::RepositoryRoot_var repository_ref_ = M2C::MOFRepository::RepositoryRoot::_narrow ( obj_ );
		if( CORBA::is_nil ( repository_ref_ ) ) 
		{
			throw NilObjectRef( "Nil repository reference!");
		}*/

		return obj_._retn();
	
	}
	catch ( const CORBA::SystemException & e )
	{
		std::string name = e._repoid ();
		std::string name_= strcpy ( "CORBA::SystemException: ", name.c_str () );
		throw SystemException( name_.c_str () );	
	}
	catch ( RepositoryException& e )
	{
		std::string str_ = e.reason ();
		std::string str1_ = e.element();
		throw RepositoryException ( str_.c_str (), str1_.c_str () );
	}
	catch (...)
	{
		std::cout << "Repository reference failed! \n Is Repository running???" <<endl;
		throw;
	}
}

}