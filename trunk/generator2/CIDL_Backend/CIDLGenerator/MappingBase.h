#ifndef __MAPPING_BASE_H__
#define __MAPPING_BASE_H__

#include "CIDLRepository_impl.h"
#include <string>


namespace QEDO_CIDL_Generator {


// Exceptions
struct CannotMapType {};
struct CannotMapAbsoluteName {};


//
//
//
class MappingBase {


protected:
	
	QEDO_ComponentRepository::CIDLRepository_impl *repository_;

	//
	string tcToName(CORBA::TypeCode_ptr type);

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
	MappingBase ( QEDO_ComponentRepository::CIDLRepository_impl *repository );
	virtual ~MappingBase ();

	void destroy();
};


} // namespace QEDO_CIDL_Generator


#endif