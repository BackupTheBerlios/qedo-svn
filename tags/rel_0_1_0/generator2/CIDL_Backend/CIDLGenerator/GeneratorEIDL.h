#ifndef __GENERATOR_EIDL_H__
#define __GENERATOR_EIDL_H__

#include "IDLBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator {


class GeneratorEIDL : public virtual IDLBase
{

	std::set<std::string> m_recursion_set;
	void check_for_generation(IR__::Contained_ptr item);

	std::string filename_;
	std::string managed_component_;
	std::map < std::string, bool > includes_;
	std::map < std::string, IR__::ContainedSeq_var > interface_def_map_;

	void checkForInclude(IR__::Contained_ptr item);
	void planInterfaceContent(IR__::Contained_ptr item);
	void doInterfaceContent(IR__::InterfaceDef_ptr item);

	void doModule(IR__::ModuleDef_ptr module);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doException(IR__::ExceptionDef_ptr except);
	void doEnum(IR__::EnumDef_ptr enumeration);
	void doValue(IR__::ValueDef_ptr value);
	void doEvent(IR__::ValueDef_ptr value);
	void doValueMember(IR__::ValueMemberDef_ptr member);
	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);
	void doHome(IR__::HomeDef_ptr home);
	void doComponent(IR__::ComponentDef_ptr component);
	void doProvides(IR__::ProvidesDef_ptr provides);
	void doUses(IR__::UsesDef_ptr uses);
	void doEmits(IR__::EmitsDef_ptr emits);
	void doPublishes(IR__::PublishesDef_ptr publishes);
	void doConsumes(IR__::ConsumesDef_ptr consumes);
	void doSink(IR__::SinkDef_ptr sink);
	void doSource(IR__::SourceDef_ptr source);
	void doSiSo(IR__::SiSoDef_ptr siso);
	void doTypedef(IR__::TypedefDef_ptr tdef);
	void doAlias(IR__::AliasDef_ptr adef);
	void doStruct(IR__::StructDef_ptr sdef);


public:

	GeneratorEIDL(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorEIDL();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
