#ifndef __GENERATOR_SERVANTC_H__
#define __GENERATOR_SERVANTC_H__

#include "CPPBase.h"
#include "Printer.h"
#include <fstream>
#include <iostream>
#include <set>


namespace QEDO_CIDL_Generator 
{


class GeneratorServantC : public virtual CPPBase 
{

private:

	std::string					class_name_;
	std::string					executor_name_;
	std::string					interface_name_;
	Printer						out;
	IR__::ComponentDef_var		component_;
	IR__::HomeDef_var			home_;
	std::set<std::string>		m_recursion_set;

	void check_for_generation(IR__::Contained_ptr item);

	void doAttribute(IR__::AttributeDef_ptr attribute);
	void doOperation(IR__::OperationDef_ptr operation);
	void doException(IR__::ExceptionDef_ptr except);
	void doInterface(IR__::InterfaceDef_ptr intface);
	void doComponent(IR__::ComponentDef_ptr component);
	void doProvides(IR__::ProvidesDef_ptr provides);
	void doUses(IR__::UsesDef_ptr uses);
	void doSink(IR__::SinkDef_ptr sink);
	void doSource(IR__::SourceDef_ptr source);
	void doSiSo(IR__::SiSoDef_ptr siso);
	void doEmits(IR__::EmitsDef_ptr emits);
	void doPublishes(IR__::PublishesDef_ptr publishes);
	void doConsumes(IR__::ConsumesDef_ptr consumes);
	void doHome(IR__::HomeDef_ptr home);
	void doFactory(IR__::FactoryDef_ptr factory);
	void doFinder(IR__::FinderDef_ptr finder);

	void genFacetServants(IR__::ComponentDef_ptr component);
	void genSourceServants(IR__::ComponentDef_ptr component);
	void genConsumerServants(IR__::ComponentDef_ptr component);
	void genContextServantBegin(IR__::ComponentDef_ptr component);
	void genContextServant(IR__::ComponentDef_ptr component);
	void genComponentServantBegin(IR__::ComponentDef_ptr component);
	void genComponentServant(IR__::ComponentDef_ptr component);
	void genHomeServantBegin(IR__::HomeDef_ptr home);
	void genHomeServant(IR__::HomeDef_ptr home);
	void genFacetRegistration(IR__::HomeDef_ptr home);
	void genReceptacleRegistration(IR__::HomeDef_ptr home);
	void genEmitterRegistration(IR__::HomeDef_ptr home);
	void genPublisherRegistration(IR__::HomeDef_ptr home);
	void genConsumerRegistration(IR__::HomeDef_ptr home);
	void genSinkRegistration(IR__::HomeDef_ptr home);
	void genSourceRegistration(IR__::HomeDef_ptr home);

public:

	GeneratorServantC(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	~GeneratorServantC();

	void generate(std::string target, std::string fileprefix);

};


} // namespace


#endif
