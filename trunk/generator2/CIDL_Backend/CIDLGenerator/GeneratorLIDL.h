#ifndef __GENERATOR_LIDL_H__
#define __GENERATOR_LIDL_H__

#include "IDLBase.h"
#include "Printer.h"

#include <fstream>
#include <iostream>

#include <set>
using namespace std;


namespace QEDO_CIDL_Generator {


class GeneratorLIDL : public virtual IDLBase
{
	std::set<std::string> m_recursion_set;
	void check_for_generation(IR__::Contained_ptr item);

	string filename_;
	std::string managed_component_;
	IR__::ComponentDef_var component_;

	void doModule(IR__::ModuleDef_ptr module);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doValue(IR__::ValueDef_ptr value);
	void doEvent(IR__::EventDef_ptr event);
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

	void generate(std::string target, std::string fileprefix);

};

} // namespace QEDO_CIDL_Generator

#endif
