#ifndef __GENERATOR_BUSINESSC_H__
#define __GENERATOR_BUSINESSC_H__

#include "CPPBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>


namespace QEDO_CIDL_Generator {


class GeneratorBusinessC : public virtual CPPBase
{

private:

	std::string filename_;
	std::string class_name_;
	Printer out;
	bool need_push_;
	CIDL::CompositionDef_var composition_;

	void doModule(IR__::ModuleDef_ptr module);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doValue(IR__::ValueDef_ptr value);
	void doValueMember(IR__::ValueMemberDef_ptr member);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doComponent(IR__::ComponentDef_ptr component);
	void doConsumes(IR__::ConsumesDef_ptr consumes);
	void doHome(IR__::HomeDef_ptr home);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);
	void doComposition(CIDL::CompositionDef_ptr composition);

public:

	GeneratorBusinessC(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorBusinessC();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
