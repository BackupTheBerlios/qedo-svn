#ifndef __GENERATORBASE_H__
#define __GENERATORBASE_H__

#include "CIDLRepository_impl.h"
#include <string>


namespace QEDO_CIDL_Generator {


//
// Exceptions
//
struct CannotMapType {};
struct CannotMapAbsoluteName {};


class GeneratorBase
{

protected:

	std::string										file_prefix_;
	std::string										target_id_;
	std::string										target_scope_id_;
	QEDO_ComponentRepository::CIDLRepository_impl	*repository_;
	IR__::Contained_var								target_;
	// internal list for items to generate
	IR__::ContainedSeq_var							m_to_generate_seq;
	IR__::ContainedSeq_var							m_to_generate_interface_seq;

	std::string getNameFromRepId(std::string id);

	// initialize the generation
	void initialize(std::string target, std::string fileprefix);
	bool already_included (IR__::Contained_ptr item);
	void insert_to_generate(IR__::Contained_ptr item);
	virtual void check_for_generation(IR__::Contained_ptr item);

	// start generation
	void doGenerate();
	virtual void generate_the_item(IR__::Contained_ptr item);

	// module
	void handleModule(IR__::ModuleDef_ptr module);
	virtual void doModule(IR__::ModuleDef_ptr module);

	// interface
	void handleSupportedInterface(IR__::ComponentDef_ptr component);
	virtual void doInterface(IR__::InterfaceDef_ptr intface);

	// value type
	virtual void doValue(IR__::ValueDef_ptr value);

	// event type
	virtual void doEvent(IR__::ValueDef_ptr value);

	// component
	virtual void doComponent(IR__::ComponentDef_ptr component);

	// home
	void handleHome(IR__::Container_ptr cont);
	virtual void doHome(IR__::HomeDef_ptr home);

	// composition
	void handleComposition(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	virtual void doComposition(CIDL::CompositionDef_ptr composition);

	// attribute
	void handleAttribute(IR__::InterfaceDef_ptr intf);
	virtual void doAttribute(IR__::AttributeDef_ptr attribute);

	// operation
	void handleOperation(IR__::InterfaceDef_ptr intf);
	virtual void doOperation(IR__::OperationDef_ptr operation);

	// factory
	void handleFactory(IR__::HomeDef_ptr intf);
	virtual void doFactory(IR__::FactoryDef_ptr factory);

	// finder
	void handleFinder(IR__::HomeDef_ptr intf);
	virtual void doFinder(IR__::FinderDef_ptr finder);

	// value member
	void handleValueMember(IR__::ValueDef_ptr value);
	virtual void doValueMember(IR__::ValueMemberDef_ptr member);

	// exception
	void handleException(IR__::Contained_ptr contained);
	virtual void doException(IR__::ExceptionDef_ptr except);

	// enum
	void handleEnum(IR__::Container_ptr container);
	virtual void doEnum(IR__::EnumDef_ptr enumeration);

	// constant
	void handleConstant(IR__::Container_ptr container);
	virtual void doConstant(IR__::ConstantDef_ptr constant);

	// typedef
	void handleTypedef(IR__::Container_ptr container);
	virtual void doTypedef(IR__::TypedefDef_ptr tdef);

	// alias
	void handleAlias(IR__::Container_ptr container);
	virtual void doAlias(IR__::AliasDef_ptr adef);

	// struct
	void handleStruct(IR__::Container_ptr container);
	virtual void doStruct(IR__::StructDef_ptr sdef);

	// union
	void handleUnion(IR__::Container_ptr container);
	virtual void doUnion(IR__::UnionDef_ptr udef);

	// provides
	void handleProvides(IR__::ComponentDef_ptr component);
	virtual void doProvides(IR__::ProvidesDef_ptr provides);

	// uses
	void handleUses(IR__::ComponentDef_ptr component);
	virtual void doUses(IR__::UsesDef_ptr uses);

	// emits
	void handleEmits(IR__::ComponentDef_ptr component);
	virtual void doEmits(IR__::EmitsDef_ptr emits);

	// publishes
	void handlePublishes(IR__::ComponentDef_ptr component);
	virtual void doPublishes(IR__::PublishesDef_ptr publishes);

	// consumes
	void handleConsumes(IR__::ComponentDef_ptr component);
	virtual void doConsumes(IR__::ConsumesDef_ptr consumes);

	// sink
	void handleSink(IR__::ComponentDef_ptr component);
	virtual void doSink(IR__::SinkDef_ptr sink);

	// source
	void handleSource(IR__::ComponentDef_ptr component);
	virtual void doSource(IR__::SourceDef_ptr source);

	// siso
	void handleSiSo(IR__::ComponentDef_ptr component);
	virtual void doSiSo(IR__::SiSoDef_ptr siso);

public:

	GeneratorBase(QEDO_ComponentRepository::CIDLRepository_impl *repository);
	virtual ~GeneratorBase();

	virtual void generate(std::string target, std::string fileprefix) = 0;

	void destroy();
};


} // namespace

#endif

