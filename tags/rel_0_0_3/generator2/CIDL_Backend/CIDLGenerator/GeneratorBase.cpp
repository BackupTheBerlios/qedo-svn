#include "GeneratorBase.h"


namespace QEDO_CIDL_Generator {


GeneratorBase::GeneratorBase
(QEDO_ComponentRepository::CIDLRepository_impl *repository)
{
	repository_ = repository;
	repository_ -> _add_ref();
	target_id_ = "";
	target_scope_id_ = "";
}


GeneratorBase::~GeneratorBase
()
{
}


void
GeneratorBase::destroy
()
{
	repository_ -> _remove_ref();
	delete this;
}


//
// start generation
//
void
GeneratorBase::doGenerate(string target)
{
	// lookup the target
	IR__::Contained_var contained =	repository_->lookup_id(target.c_str());
	if(CORBA::is_nil(contained))
	{
		contained =	repository_->lookup(target.c_str());
	}
	if(CORBA::is_nil(contained))
	{
		std::cerr << "--- fatal internal error - not found " << target << std::endl;
		return;
	}
	target_id_ = contained->id();

	switch(contained->def_kind())
	{
		case CORBA__::dk_Home : {
			// process the module where the home is defined in
			IR__::HomeDef_var home = IR__::HomeDef::_narrow(contained);
			IR__::ModuleDef_var module = IR__::ModuleDef::_narrow(home->defined_in());
			if(CORBA::is_nil(module))
			{
				target_scope_id_ = "";
			}
			target_scope_id_ = module->id();
			doModule(module);
			break;
		}
		case CORBA__::dk_Module : {
			// process the module
			IR__::ModuleDef_var module = IR__::ModuleDef::_narrow(contained);
			target_scope_id_ = target_id_;
			doModule(module);
			break;
		}
		case CORBA__::dk_Composition : {
			// process the composition
			CIDL::CompositionDef_var composition = CIDL::CompositionDef::_narrow(contained);
			std::string id = composition->id();
			std::string::size_type pos = id.rfind("/");
			if(pos != std::string::npos)
			{
				id.replace(pos, std::string::npos, ":1.0");
				target_scope_id_ = id;
			}
			else
			{
				target_scope_id_ = "";
			}
			doComposition(composition);
			break;
		}
		default : {}
	}
}


//
// module
//
void
GeneratorBase::doModule(IR__::ModuleDef_ptr module)
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
}


//
// component
//
void
GeneratorBase::doComponent(IR__::ComponentDef_ptr component)
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
}


} // namespace