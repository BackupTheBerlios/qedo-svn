#include "IDLBase.h"


namespace QEDO_CIDL_Generator {


IDLBase::IDLBase
(QEDO_ComponentRepository::CIDLRepository_impl *repository)
: GeneratorBase(repository)
{
}


IDLBase::~IDLBase
()
{
}


//
// module
//
void
IDLBase::doModule(IR__::ModuleDef_ptr module)
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
IDLBase::beginModule(IR__::ModuleDef_ptr module)
{
}


void
IDLBase::endModule(IR__::ModuleDef_ptr module)
{
}


//
// interface
//
void
IDLBase::doInterface(IR__::InterfaceDef_ptr intface)
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
IDLBase::beginInterface(IR__::InterfaceDef_ptr intface)
{
}


void
IDLBase::endInterface(IR__::InterfaceDef_ptr intface)
{
}


//
// value type
//
void
IDLBase::doValue(IR__::ValueDef_ptr value)
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
IDLBase::beginValue(IR__::ValueDef_ptr value)
{
}


void
IDLBase::endValue(IR__::ValueDef_ptr value)
{
}


//
// home
//
void
IDLBase::doHome(IR__::HomeDef_ptr home)
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
IDLBase::beginHome(IR__::HomeDef_ptr home)
{
}


void
IDLBase::endHome(IR__::HomeDef_ptr home)
{
}


//
// component
//
void
IDLBase::doComponent(IR__::ComponentDef_ptr component)
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
IDLBase::beginComponent(IR__::ComponentDef_ptr component)
{
}


void
IDLBase::endComponent(IR__::ComponentDef_ptr component)
{
}


//
// composition
//
void
IDLBase::doComposition(CIDL::CompositionDef_ptr composition)
{
	beginComposition(composition);
	endComposition(composition);
}


void
IDLBase::beginComposition(CIDL::CompositionDef_ptr composition)
{
}


void
IDLBase::endComposition(CIDL::CompositionDef_ptr composition)
{
}


string
IDLBase::tcToName(CORBA::TypeCode_ptr type)
{
	switch(type->kind())
    {
	case CORBA::tk_null:
		return "";
		break;
	case CORBA::tk_void:
		return "void";
		break;
	case CORBA::tk_short:
		return "short";
		break;
    case CORBA::tk_long:
		return "long";
		break;
    case CORBA::tk_longlong:
		return "longlong";
		break;
    case CORBA::tk_ushort:
		return "unsigned short";
		break;
    case CORBA::tk_ulong:
		return "unsigned long";
		break;
    case CORBA::tk_ulonglong:
		return "unsigned longlong";
		break;
    case CORBA::tk_float:
		return "float";
		break;
    case CORBA::tk_double:
		return "double";
		break;
    case CORBA::tk_longdouble:
		return "longdouble";
		break;
    case CORBA::tk_boolean:
		return "boolean";
		break;
    case CORBA::tk_char:
		return "char";
		break;
    case CORBA::tk_wchar:
		return "wchar";
		break;
    case CORBA::tk_octet:
		return "octet";
		break;
    case CORBA::tk_any:
		return "any";
		break;
    case CORBA::tk_TypeCode:
		return "CORBA::TypeCode";
		break;
    case CORBA::tk_Principal:
        return "CORBA::Principal";
        break;
    case CORBA::tk_fixed:
        break;
    case CORBA::tk_objref:
    case CORBA::tk_abstract_interface:
    case CORBA::tk_local_interface:
    case CORBA::tk_native:
    case CORBA::tk_struct:
    case CORBA::tk_except:
	case CORBA::tk_union:
	case CORBA::tk_enum:
	case CORBA::tk_sequence:
    case CORBA::tk_array:
	case CORBA::tk_alias:
    case CORBA::tk_value_box:
	case CORBA::tk_value:
		return map_absolute_name(repository_->lookup_id(type->id()));
        break;
    case CORBA::tk_string:
		return "string";
		break;
    case CORBA::tk_wstring:
		return "wstring";
        break;
    default:
        assert(false);
    }

	return "";
}


char* 
IDLBase::map_absolute_name
( CORBA__::IRObject_ptr type )
{
	string ret_string;

	IR__::Contained_var contained;

	try
	{
		contained = IR__::Contained::_narrow ( type );
		if ( CORBA::is_nil ( contained ) ) {
			return 0;
		}

		ret_string = contained -> absolute_name ();
	}
	catch ( /*CORBA::SystemException& */ ...)
	{
		return 0;
	}
	if ( CORBA::is_nil ( contained ) )
		return 0;

	return CORBA::string_dup ( ret_string.c_str() + 2 );
}


char* 
IDLBase::mapLocalName
( CORBA__::IRObject_ptr type )
{
	string result;

	IR__::Contained_var contained;

	try	{
		contained = IR__::Contained::_narrow ( type );
		result = contained->absolute_name();
	}
	catch ( CORBA::SystemException& ) {
		return 0;
	}
	if ( CORBA::is_nil ( contained ) ) {
		return 0;
	}

	string::size_type pos = result.find_last_of(":");
	if(pos < string::npos) {
		result.insert(++pos, "CCM_");
	}
	else {
		result.insert(0, "CCM_");
	}

	return CORBA::string_dup(result.c_str());
}


} // namespace