#ifndef __IDLBASE_H__
#define __IDLBASE_H__

#include "GeneratorBase.h"
#include "Printer.h"


namespace QEDO_CIDL_Generator {


//
//
//
class IDLBase : public GeneratorBase
{

protected:

	Printer out;

	void generate_the_item(IR__::Contained_ptr item);
	
	// check whether the contained is defined in an interface
	bool definedInInterface(IR__::Contained_ptr contained);

	// module
	void open_module(IR__::Contained_ptr cont);
	void close_module(IR__::Contained_ptr cont);

	// TypeCode to name
	std::string tcToName(CORBA::TypeCode_ptr type);

	char* map_absolute_name ( CORBA__::IRObject_ptr contained );
	char* map_idl_type ( IR__::IDLType_ptr type );
	char* mapLocalName ( CORBA__::IRObject_ptr contained );

public:

	IDLBase(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	virtual ~IDLBase();
};


} // namespace

#endif

