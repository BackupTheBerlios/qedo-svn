#ifndef __CPPBASE_H__
#define __CPPBASE_H__

#include "GeneratorBase.h"
#include "Printer.h"
#include "CIDLRepository_impl.h"


namespace QEDO_CIDL_Generator {


// Exceptions
struct CannotMapType {};
struct CannotMapAbsoluteName {};


//
//
//
class CPPBase : public GeneratorBase
{

protected:

	bool open_module(Printer& out, IR__::Contained* cur_cont, std::string prefix = "");
	void close_module(Printer& out, IR__::Contained* cur_cont);

	//
	// Helper functions for C++ mapping
	//
	std::string mapName(std::string name);
	std::string mapName(IR__::Contained_ptr obj);
	std::string mapFullName(IR__::Contained_ptr obj);
	std::string mapFullNameLocal(IR__::Contained_ptr obj);
	std::string mapFullNameServant(IR__::Contained_ptr obj);
	std::string mapFullNamePOA(IR__::Contained_ptr obj);

	char* map_absolute_name ( CORBA__::IRObject_ptr contained )
		throw ( CannotMapAbsoluteName );

	char* mapAbsoluteName ( CORBA__::IRObject_ptr contained, string delim )
		throw ( CannotMapAbsoluteName );

	char* mapLocalName ( CORBA__::IRObject_ptr contained )
		throw ( CannotMapAbsoluteName );

	char* map_absolute_under_name ( CORBA__::IRObject_ptr type )
		throw ( CannotMapAbsoluteName );

	char* map_absolute_slash_name ( CORBA__::IRObject_ptr type )
		throw ( CannotMapAbsoluteName );

	std::string mapScopeName(IR__::Contained_ptr type)
		throw(CannotMapAbsoluteName);

	char* map_return_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_value_return_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_attribute_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* assign_attribute ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_idl_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_in_parameter_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_inout_parameter_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

	char* map_out_parameter_type ( IR__::IDLType_ptr type )
		throw ( CannotMapType );

public:

	CPPBase(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	virtual ~CPPBase();

	virtual void generate(std::string target) = 0;
};


} // namespace

#endif