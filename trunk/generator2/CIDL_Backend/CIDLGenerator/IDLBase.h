#ifndef __IDLBASE_H__
#define __IDLBASE_H__

#include "GeneratorBase.h"


namespace QEDO_CIDL_Generator {


//
//
//
class IDLBase : public GeneratorBase
{

protected:

	// module
	virtual void doModule(IR__::ModuleDef_ptr module);
	virtual void beginModule(IR__::ModuleDef_ptr module);
	virtual void endModule(IR__::ModuleDef_ptr module);

	// interface
	virtual void doInterface(IR__::InterfaceDef_ptr intface);
	virtual void beginInterface(IR__::InterfaceDef_ptr intface);
	virtual void endInterface(IR__::InterfaceDef_ptr intface);

	// value type
	virtual void doValue(IR__::ValueDef_ptr value);
	virtual void beginValue(IR__::ValueDef_ptr value);
	virtual void endValue(IR__::ValueDef_ptr value);

	// event type
	virtual void doEvent(IR__::ValueDef_ptr value);
	virtual void beginEvent(IR__::ValueDef_ptr value);
	virtual void endEvent(IR__::ValueDef_ptr value);

	// component
	virtual void doComponent(IR__::ComponentDef_ptr component);
	virtual void beginComponent(IR__::ComponentDef_ptr component);
	virtual void endComponent(IR__::ComponentDef_ptr component);

	// home
	virtual void doHome(IR__::HomeDef_ptr home);
	virtual void beginHome(IR__::HomeDef_ptr home);
	virtual void endHome(IR__::HomeDef_ptr home);

	// composition
	virtual void doComposition(CIDL::CompositionDef_ptr composition);
	virtual void beginComposition(CIDL::CompositionDef_ptr composition);
	virtual void endComposition(CIDL::CompositionDef_ptr composition);

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

