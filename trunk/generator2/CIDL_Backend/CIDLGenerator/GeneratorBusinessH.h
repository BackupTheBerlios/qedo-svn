#ifndef __GENERATOR_BUSINESSH_H__
#define __GENERATOR_BUSINESSH_H__

#include "CPPBase.h"
#include "Printer.h"
#include <iostream>


using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorBusinessH : public virtual CPPBase
{

	string filename_;
	Printer out;
	string target_;
	bool need_push_;
	CIDL::CompositionDef_var composition_;

	void doModule(IR__::ModuleDef_ptr module);
	void doException(IR__::ExceptionDef_ptr except);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doValue(IR__::ValueDef_ptr value);
	void doValueMember(IR__::ValueMemberDef_ptr member);
	void doComponent(IR__::ComponentDef_ptr component);
	void doConsumes(IR__::ConsumesDef_ptr consumes);
	void doSource(IR__::SourceDef_ptr source);
	void doSink(IR__::SinkDef_ptr sink);
	void doSiSo(IR__::SiSoDef_ptr siso);
	void doHome(IR__::HomeDef_ptr home);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);
	void doComposition(CIDL::CompositionDef_ptr composition);

public:

	GeneratorBusinessH(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorBusinessH();

	void generate(string target);

};

} // namespace QEDO_CIDL_Generator

#endif
