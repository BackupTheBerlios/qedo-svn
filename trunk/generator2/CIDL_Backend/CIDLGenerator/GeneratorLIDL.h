#ifndef __GENERATOR_LIDL_H__
#define __GENERATOR_LIDL_H__

#include "GeneratorBase.h"
#include "Printer.h"

#include <fstream>
#include <string>
#include <iostream>


using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorLIDL : public virtual GeneratorBase {

	string filename_;
	Printer out;
	string managed_component_;

	void open_module(IR__::Contained* cur_cont);
	void close_module(IR__::Contained* cur_cont);

	void beginModule(IR__::ModuleDef_ptr module);
	void endModule(IR__::ModuleDef_ptr module);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doValue(IR__::ValueDef_ptr value);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);
	void doHome(IR__::HomeDef_ptr home);
	void doComponent(IR__::ComponentDef_ptr component);
	void doUses(IR__::UsesDef_ptr uses);
	void doEmits(IR__::EmitsDef_ptr emits);
	void doPublishes(IR__::PublishesDef_ptr publishes);

public:

	GeneratorLIDL(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorLIDL();

	void generate(string target);

};

} // namespace QEDO_CIDL_Generator

#endif
