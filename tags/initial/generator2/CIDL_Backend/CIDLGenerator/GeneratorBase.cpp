#include "GeneratorBase.h"

#include <string>


namespace QEDO_CIDL_Generator {


GeneratorBase::GeneratorBase
(QEDO_ComponentRepository::CIDLRepository_impl *repository)
: MappingBase(repository)
{
}


GeneratorBase::~GeneratorBase
()
{
}


//
// start generation
//
void
GeneratorBase::doGenerate(string target)
{
	// lookup the target
	IR__::Contained_var contained =	repository_->lookup(target.c_str());
	if(CORBA::is_nil(contained))
	{
		std::cerr << "--- fatal internal error - not found " << target << std::endl;
		return;
	}
	target_id_ = contained->id();

	switch(contained->def_kind())
	{
	case CORBA__::dk_Module : {
		IR__::ModuleDef_var module = IR__::ModuleDef::_narrow(contained);
		doModule(module);
		break; }
	case CORBA__::dk_Composition : {
		CIDL::CompositionDef_var composition = CIDL::CompositionDef::_narrow(contained);
		doComposition(composition);
		break; }
	default : {}
	}
}


//
// module
//
void
GeneratorBase::doModule(IR__::ModuleDef_ptr module)
{
	beginModule(module);

	IR__::ContainedSeq_var contained_seq;
	CORBA::ULong len;
	CORBA::ULong i;

	// contained enums
	contained_seq = module->contents(CORBA__::dk_Enum, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::EnumDef_var act_enum = IR__::EnumDef::_narrow(((*contained_seq)[i]));
		doEnum(act_enum);
	}

	// contained exceptions
	contained_seq = module->contents(CORBA__::dk_Exception, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ExceptionDef_var act_exception = IR__::ExceptionDef::_narrow(((*contained_seq)[i]));
		doException(act_exception);
	}

	// contained value types
	contained_seq = module->contents(CORBA__::dk_Value, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ValueDef_var act_value = IR__::ValueDef::_narrow(((*contained_seq)[i]));
		doValue(act_value);
	}

	// contained interfaces
	contained_seq = module->contents(CORBA__::dk_Interface, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::InterfaceDef_var act_interface = IR__::InterfaceDef::_narrow(((*contained_seq)[i]));
		doInterface(act_interface);
	}

	// contained components
	contained_seq = module->contents(CORBA__::dk_Component, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ComponentDef_var act_component = IR__::ComponentDef::_narrow(((*contained_seq)[i]));
		doComponent(act_component);
	}

	// contained homes
	contained_seq = module->contents(CORBA__::dk_Home, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::HomeDef_var act_home = IR__::HomeDef::_narrow(((*contained_seq)[i]));
		doHome(act_home);
	}

	// contained modules
	contained_seq = module->contents(CORBA__::dk_Module, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ModuleDef_var act_module = IR__::ModuleDef::_narrow(((*contained_seq)[i]));
		doModule(act_module);
	}

	// contained compositions
	contained_seq = repository_->contents(CORBA__::dk_Composition, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		CIDL::CompositionDef_var act_composition = CIDL::CompositionDef::_narrow(((*contained_seq)[i]));
		doComposition(act_composition);
	}

	endModule(module);
}


void
GeneratorBase::beginModule(IR__::ModuleDef_ptr module)
{
}


void
GeneratorBase::endModule(IR__::ModuleDef_ptr module)
{
}


//
// interface
//
void 
GeneratorBase::handleSupportedInterface(IR__::ComponentDef_ptr component)
{
	IR__::InterfaceDefSeq_var supported_seq = component->supported_interfaces();
	CORBA::ULong len = supported_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		doInterface((*supported_seq)[i]);
	}
}


void
GeneratorBase::doInterface(IR__::InterfaceDef_ptr intface)
{
	beginInterface(intface);

	IR__::ContainedSeq_var contained_seq;
	CORBA::ULong len;
	CORBA::ULong i;

	// contained constants
	contained_seq = intface->contents(CORBA__::dk_Constant, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ConstantDef_var act_constant = IR__::ConstantDef::_narrow(((*contained_seq)[i]));
		doConstant(act_constant);
	}

	// contained typedefs
	contained_seq = intface->contents(CORBA__::dk_Typedef, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::TypedefDef_var act_typedef = IR__::TypedefDef::_narrow(((*contained_seq)[i]));
		doTypedef(act_typedef);
	}

	// contained exceptions
	contained_seq = intface->contents(CORBA__::dk_Exception, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ExceptionDef_var act_exception = IR__::ExceptionDef::_narrow(((*contained_seq)[i]));
		doException(act_exception);
	}

	// contained attributes
	handleAttribute(intface);

	// contained operations
	handleOperation(intface);

	endInterface(intface);
}


void
GeneratorBase::beginInterface(IR__::InterfaceDef_ptr intface)
{
}


void
GeneratorBase::endInterface(IR__::InterfaceDef_ptr intface)
{
}


//
// attribute
//
void 
GeneratorBase::handleAttribute(IR__::InterfaceDef_ptr intf)
{
	IR__::ContainedSeq_var contained_seq = intf->contents(CORBA__::dk_Attribute, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::AttributeDef_var a_attribute = IR__::AttributeDef::_narrow(((*contained_seq)[i]));
		doAttribute(a_attribute);
	}
}


void
GeneratorBase::doAttribute(IR__::AttributeDef_ptr attribute)
{
}


//
// operation
//
void 
GeneratorBase::handleOperation(IR__::InterfaceDef_ptr intf)
{
	IR__::ContainedSeq_var contained_seq = intf->contents(CORBA__::dk_Operation, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::OperationDef_var a_operation = IR__::OperationDef::_narrow(((*contained_seq)[i]));
		doOperation(a_operation);
	}
}


void
GeneratorBase::doOperation(IR__::OperationDef_ptr operation)
{
}


//
// factory
//
void
GeneratorBase::handleFactory(IR__::HomeDef_ptr home)
{
	IR__::ContainedSeq_var contained_seq = home->contents(CORBA__::dk_Factory, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::FactoryDef_var a_factory = IR__::FactoryDef::_narrow(((*contained_seq)[i]));
		doFactory(a_factory);
	}
}


void
GeneratorBase::doFactory(IR__::FactoryDef_ptr factory)
{
}


//
// finder
//
void
GeneratorBase::handleFinder(IR__::HomeDef_ptr home)
{
	IR__::ContainedSeq_var contained_seq = home->contents(CORBA__::dk_Finder, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::FinderDef_var a_finder = IR__::FinderDef::_narrow(((*contained_seq)[i]));
		doFinder(a_finder);
	}
}


void
GeneratorBase::doFinder(IR__::FinderDef_ptr finder)
{
}


//
// value type
//
void
GeneratorBase::doValue(IR__::ValueDef_ptr value)
{
	beginValue(value);

	IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_all, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		// contained members
		if (((*contained_seq)[i])->def_kind() == CORBA__::dk_ValueMember)
		{
			IR__::ValueMemberDef_var act_member = IR__::ValueMemberDef::_narrow(((*contained_seq)[i]));
			doValueMember(act_member);
		}
	}

	endValue(value);
}


void
GeneratorBase::beginValue(IR__::ValueDef_ptr value)
{
}


void
GeneratorBase::endValue(IR__::ValueDef_ptr value)
{
}


//
// value member
//
void 
GeneratorBase::handleValueMember(IR__::ValueDef_ptr value)
{
	IR__::ContainedSeq_var contained_seq = value->contents(CORBA__::dk_ValueMember, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ValueMemberDef_var act_member = IR__::ValueMemberDef::_narrow(((*contained_seq)[i]));
		doValueMember(act_member);
	}
}


void
GeneratorBase::doValueMember(IR__::ValueMemberDef_ptr member)
{
}


//
// exception
//
void
GeneratorBase::handleException(IR__::Contained_ptr contained)
{
	IR__::ExceptionDefSeq_var exception_seq;
	CORBA::ULong len;
	CORBA::ULong i;

	switch(contained->def_kind())
	{
	case CORBA__::dk_Attribute :
		{
			IR__::AttributeDef_var a_attribute = IR__::AttributeDef::_narrow(contained);
			exception_seq = a_attribute->get_exceptions();
			len = exception_seq->length();
			for(i = 0; i < len; i++)
			{
				doException(exception_seq[i]);
			}
			break;
		}
	case CORBA__::dk_Operation :
		{
			IR__::OperationDef_var a_operation = IR__::OperationDef::_narrow(contained);
			exception_seq = a_operation->exceptions();
			len = exception_seq->length();
			for(i = 0; i < len; i++)
			{
				doException(exception_seq[i]);
			}
			break;
		}
	default : {}
	}
}


void
GeneratorBase::doException(IR__::ExceptionDef_ptr except)
{
}


//
// enum
//
void
GeneratorBase::doEnum(IR__::EnumDef_ptr enumeration)
{
}


//
// constant
//
void
GeneratorBase::doConstant(IR__::ConstantDef_ptr constant)
{
}


//
// typedef
//
void
GeneratorBase::doTypedef(IR__::TypedefDef_ptr tdef)
{
}


//
// home
//
void
GeneratorBase::doHome(IR__::HomeDef_ptr home)
{
	beginHome(home);

	IR__::ContainedSeq_var contained_seq;
	CORBA::ULong len;
	CORBA::ULong i;

	// contained constants
	contained_seq = home->contents(CORBA__::dk_Constant, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ConstantDef_var act_constant = IR__::ConstantDef::_narrow(((*contained_seq)[i]));
		doConstant(act_constant);
	}

	// contained typedefs
	contained_seq = home->contents(CORBA__::dk_Typedef, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::TypedefDef_var act_typedef = IR__::TypedefDef::_narrow(((*contained_seq)[i]));
		doTypedef(act_typedef);
	}

	// contained exceptions
	contained_seq = home->contents(CORBA__::dk_Exception, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::ExceptionDef_var act_exception = IR__::ExceptionDef::_narrow(((*contained_seq)[i]));
		doException(act_exception);
	}

	// contained attributes
	contained_seq = home->contents(CORBA__::dk_Attribute, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::AttributeDef_var act_attribute = IR__::AttributeDef::_narrow(((*contained_seq)[i]));
		doAttribute(act_attribute);
	}

	// contained operations
	contained_seq = home->contents(CORBA__::dk_Operation, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::OperationDef_var act_operation = IR__::OperationDef::_narrow(((*contained_seq)[i]));
		doOperation(act_operation);
	}

	// contained factories
	contained_seq = home->contents(CORBA__::dk_Factory, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::FactoryDef_var act_factory = IR__::FactoryDef::_narrow(((*contained_seq)[i]));
		doFactory(act_factory);
	}

	// contained finders
	contained_seq = home->contents(CORBA__::dk_Finder, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::FinderDef_var act_finder = IR__::FinderDef::_narrow(((*contained_seq)[i]));
		doFinder(act_finder);
	}

	endHome(home);
}


void
GeneratorBase::beginHome(IR__::HomeDef_ptr home)
{
}


void
GeneratorBase::endHome(IR__::HomeDef_ptr home)
{
}


//
// component
//
void
GeneratorBase::doComponent(IR__::ComponentDef_ptr component)
{
	beginComponent(component);

	// contained attributes
	handleAttribute(component);

	// contained provides
	handleProvides(component);

	// contained uses
	handleUses(component);

	// contained emits
	handleEmits(component);

	// contained publishes
	handlePublishes(component);

	// contained consumes
	handleConsumes(component);

	// contained sink
	handleSink(component);

	// contained source
	handleSource(component);

	// contained siso
	handleSiSo(component);

	endComponent(component);
}


void
GeneratorBase::beginComponent(IR__::ComponentDef_ptr component)
{
}


void
GeneratorBase::endComponent(IR__::ComponentDef_ptr component)
{
}


//
// provides
//
void 
GeneratorBase::handleProvides(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Provides, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::ProvidesDef_var act_provides = IR__::ProvidesDef::_narrow(((*contained_seq)[i]));
		doProvides(act_provides);
	}
}


void
GeneratorBase::doProvides(IR__::ProvidesDef_ptr provides)
{
}


//
// uses
//
void 
GeneratorBase::handleUses(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Uses, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::UsesDef_var act_uses = IR__::UsesDef::_narrow(((*contained_seq)[i]));
		doUses(act_uses);
	}
}


void
GeneratorBase::doUses(IR__::UsesDef_ptr Uses)
{
}


//
// emits
//
void
GeneratorBase::handleEmits(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Emits, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) {
		IR__::EmitsDef_var act_emits = IR__::EmitsDef::_narrow(((*contained_seq)[i]));
		doEmits(act_emits);
	}
}


void
GeneratorBase::doEmits(IR__::EmitsDef_ptr emits)
{
}


//
// publishes
//
void
GeneratorBase::handlePublishes(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Publishes, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++) 
	{
		IR__::PublishesDef_var act_publishes = IR__::PublishesDef::_narrow(((*contained_seq)[i]));
		doPublishes(act_publishes);
	}
}


void
GeneratorBase::doPublishes(IR__::PublishesDef_ptr publishes)
{
}


//
// consumes
//
void 
GeneratorBase::handleConsumes(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Consumes, false);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		IR__::ConsumesDef_var a_consumes = IR__::ConsumesDef::_narrow(((*contained_seq)[i]));
		doConsumes(a_consumes);
	}
}


void
GeneratorBase::doConsumes(IR__::ConsumesDef_ptr consumes)
{
}


//
// sink
//
void 
GeneratorBase::handleSink(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Sink, false);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::SinkDef_var act_sink = IR__::SinkDef::_narrow(((*contained_seq)[i]));
		doSink(act_sink);
	}
}


void
GeneratorBase::doSink(IR__::SinkDef_ptr sink)
{
}


//
// source
//
void 
GeneratorBase::handleSource(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_Source, false);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::SourceDef_var a_source = IR__::SourceDef::_narrow(((*contained_seq)[i]));
		doSource(a_source);
	}
}


void
GeneratorBase::doSource(IR__::SourceDef_ptr source)
{
}


//
// siso
//
void 
GeneratorBase::handleSiSo(IR__::ComponentDef_ptr component)
{
	IR__::ContainedSeq_var contained_seq = component->contents(CORBA__::dk_SiSo, false);
	for(CORBA::ULong i = 0; i < contained_seq->length(); i++)
	{
		IR__::SiSoDef_var a_siso = IR__::SiSoDef::_narrow(((*contained_seq)[i]));
		doSiSo(a_siso);
	}
}


void
GeneratorBase::doSiSo(IR__::SiSoDef_ptr siso)
{
}


//
// composition
//
void 
GeneratorBase::handleComposition(QEDO_ComponentRepository::CIDLRepository_impl *repository)
{
	IR__::ContainedSeq_var contained_seq = repository_->contents(CORBA__::dk_Composition, true);
	CORBA::ULong len = contained_seq->length();
	for(CORBA::ULong i = 0; i < len; i++)
	{
		CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow(((*contained_seq)[i]));
		doComposition(a_composition);
	}
}


void
GeneratorBase::doComposition(CIDL::CompositionDef_ptr composition)
{
	beginComposition(composition);
	endComposition(composition);
}


void
GeneratorBase::beginComposition(CIDL::CompositionDef_ptr composition)
{
}


void
GeneratorBase::endComposition(CIDL::CompositionDef_ptr composition)
{
}


} // namespace