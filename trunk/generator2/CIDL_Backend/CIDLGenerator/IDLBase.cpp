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
// start generation
//
void
IDLBase::generate_the_item ( IR__::Contained_ptr item ) {
	IR__::HomeDef_var act_home;
	IR__::ComponentDef_var act_component;
	IR__::InterfaceDef_var act_interface;
	IR__::AliasDef_var act_alias;
	IR__::ValueDef_var act_value;
	IR__::EventDef_var act_event;
	IR__::ExceptionDef_var act_exception;
	IR__::EnumDef_var act_enum;
	IR__::ModuleDef_var act_module;
	IR__::StructDef_var act_struct;

	std::cout << "Debug: item to generate: " << item->id() << std::endl;
	this->open_module(item);
	switch (item->describe()->kind) {
	case CORBA__::dk_Module:
		act_module = IR__::ModuleDef::_narrow(item);
		doModule(act_module);
		break;
	case CORBA__::dk_Home:
		act_home = IR__::HomeDef::_narrow(item);
		doHome(act_home);
		break;
	case CORBA__::dk_Component:
		act_component = IR__::ComponentDef::_narrow(item);
		doComponent(act_component);
		break;
	case CORBA__::dk_Interface:
		act_interface = IR__::InterfaceDef::_narrow(item);
		doInterface ( act_interface );
		break;
	case CORBA__::dk_Value:
		act_event = IR__::EventDef::_narrow(item);
		if (!CORBA::is_nil ( act_event ) ) {
			doEvent ( act_event );
		} else {
			act_value = IR__::ValueDef::_narrow(item);
			doValue(act_value);
		}
		break;
	case CORBA__::dk_Alias:
		act_alias = IR__::AliasDef::_narrow(item);
		doAlias (act_alias);
		break;
	case CORBA__::dk_Exception:
		act_exception = IR__::ExceptionDef::_narrow(item);
		doException(act_exception);
		break;
	case CORBA__::dk_Enum:
		act_enum = IR__::EnumDef::_narrow(item);
		doEnum(act_enum);
		break;
	case CORBA__::dk_Struct:
		act_struct = IR__::StructDef::_narrow(item);
		doStruct(act_struct);
		break;
	case CORBA__::dk_Composition : {
		CIDL::CompositionDef_var a_composition = CIDL::CompositionDef::_narrow(item);
		doComposition(a_composition);
		break; }
	default:
		break;
	};

	this->close_module(item);
}


//
// check whether the contained are defined in the same scope
//
bool 
IDLBase::definedInTheSame(IR__::Contained_ptr cont1, IR__::Contained_ptr cont2)
{
	IR__::Contained_ptr c1 = IR__::Contained::_narrow(cont1->defined_in());
	IR__::Contained_ptr c2 = IR__::Contained::_narrow(cont2->defined_in());
	
	if(c1 && c2) {
		if(!strcmp(c1->id(), c2->id())) {
			return true;
		}
	}

	return false;
}


//
// module
//
void
IDLBase::open_module(IR__::Contained* cur_cont)
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module)
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->open_module(act_mod);
		out << "module " << act_mod->name() << " {\n\n";
		out.indent();
	}
}


void
IDLBase::close_module(IR__::Contained* cur_cont) 
{
	IR__::Container_ptr act_container=cur_cont->defined_in();
	if(act_container->def_kind()==CORBA__::dk_Module) 
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(act_container);
		this->close_module(act_mod);
		out.unindent();
		out <<  "};\n\n";
	}

}


void
IDLBase::doModule(IR__::ModuleDef_ptr module)
{
	beginModule(module);

	IR__::ContainedSeq_var contained_seq;
	CORBA::ULong len;
	CORBA::ULong i;

	IR__::AliasDef_var act_typedef;
	IR__::EnumDef_var act_enum;
	IR__::StructDef_var act_struct;
	IR__::ExceptionDef_var act_exception;
	IR__::ValueDef_var act_value;
	IR__::EventDef_var act_event;
	IR__::InterfaceDef_var act_interface;
	IR__::ComponentDef_var act_component;
	IR__::HomeDef_var act_home;
	IR__::ModuleDef_var act_module;
	CIDL::CompositionDef_var act_composition;


	//begin new implementation

		// contained enums
	contained_seq = module->contents(CORBA__::dk_Enum, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::EnumDef_var act_enum = IR__::EnumDef::_narrow(((*contained_seq)[i]));
		doEnum(act_enum);
	}
	// contained alias
	contained_seq = module->contents(CORBA__::dk_Alias, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::AliasDef_var act_typedef = IR__::AliasDef::_narrow(((*contained_seq)[i]));
		doAlias(act_typedef);
	}
	contained_seq = module->contents(CORBA__::dk_all, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		switch (contained_seq[i]->describe()->kind) {
//		case CORBA__::dk_Alias:
//			act_typedef = IR__::AliasDef::_narrow(((*contained_seq)[i]));
//			doAlias(act_typedef);
//			break;
		case CORBA__::dk_Struct:
			act_struct = IR__::StructDef::_narrow(((*contained_seq)[i]));
			doStruct(act_struct);
			break;
		case CORBA__::dk_Exception:
			act_exception = IR__::ExceptionDef::_narrow(((*contained_seq)[i]));
			doException(act_exception);
			break;
		case CORBA__::dk_Value:
			act_event = IR__::EventDef::_narrow(((*contained_seq)[i]));
			if (!(CORBA::is_nil(act_event))) {
				doEvent(act_event);
			} else {
				act_value = IR__::ValueDef::_narrow(((*contained_seq)[i]));
				doValue(act_value);
			}
			break;
		default:;

		};
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


/*  old implementation
	// contained alias
	contained_seq = module->contents(CORBA__::dk_Alias, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::AliasDef_var act_typedef = IR__::AliasDef::_narrow(((*contained_seq)[i]));
		doAlias(act_typedef);
	}

	// contained enums
	contained_seq = module->contents(CORBA__::dk_Enum, true);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::EnumDef_var act_enum = IR__::EnumDef::_narrow(((*contained_seq)[i]));
		doEnum(act_enum);
	}

	// contained structs
	contained_seq = module->contents(CORBA__::dk_Struct, false);
	len = contained_seq->length();
	for(i = 0; i < len; i++)
	{
		IR__::StructDef_var act_struct = IR__::StructDef::_narrow(((*contained_seq)[i]));
		doStruct(act_struct);
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

  */

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

	// contained constants
	handleConstant(intface);

	// contained typedefs
	handleTypedef(intface);

	// contained exceptions
	handleException(intface);

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
// event type
//
void
IDLBase::doEvent(IR__::ValueDef_ptr value)
{
	beginEvent(value);

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

	endEvent(value);
}


void
IDLBase::beginEvent(IR__::ValueDef_ptr value)
{
}


void
IDLBase::endEvent(IR__::ValueDef_ptr value)
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
		return "long long";
		break;
    case CORBA::tk_ushort:
		return "unsigned short";
		break;
    case CORBA::tk_ulong:
		return "unsigned long";
		break;
    case CORBA::tk_ulonglong:
		return "unsigned long long";
		break;
    case CORBA::tk_float:
		return "float";
		break;
    case CORBA::tk_double:
		return "double";
		break;
    case CORBA::tk_longdouble:
		return "long double";
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
		try {
			return map_absolute_name(repository_->lookup_id(type->id()));
		} catch (...) {
			// CORBA::Object is not in the repository 
			// but it can be used as parameter
			return "CORBA::Object";
		}
		break;

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

char*
IDLBase::map_idl_type
( IR__::IDLType_ptr type )
{
	string ret_string;

	switch ( type -> type() -> kind() )
	{
	case CORBA::tk_void:
		ret_string = "void";
		break;
	case CORBA::tk_short:
		ret_string = "short";
		break;
	case CORBA::tk_long:
		ret_string = "long";
		break;
	case CORBA::tk_longlong:
		ret_string = "CORBA::LongLong";
		break;
	case CORBA::tk_ushort:
		ret_string = "unsigned short";
		break;
	case CORBA::tk_ulong:
		ret_string = "unsigned long";
		break;
	case CORBA::tk_ulonglong:
		ret_string = "CORBA::ULongLong";
		break;
	case CORBA::tk_float:
		ret_string = "float";
		break;
	case CORBA::tk_double:
		ret_string = "double";
		break;
	case CORBA::tk_longdouble:
		ret_string = "CORBA::LongDouble";
		break;
	case CORBA::tk_boolean:
		ret_string = "CORBA::Boolean";
		break;
	case CORBA::tk_char:
		ret_string = "CORBA::Char";
		break;
	case CORBA::tk_wchar:
		ret_string = "CORBA::WChar";
		break;
	case CORBA::tk_any:
		ret_string = "CORBA::Any*";
		break;
	case CORBA::tk_objref:
		// First test whether we are a Contained, if not we are simply CORBA::Object_ptr
		try
		{
			ret_string = map_absolute_name ( type );
			ret_string = ret_string;
		}
		catch ( CannotMapAbsoluteName& )
		{
			ret_string = "CORBA::Object_ptr";
		}
		break;
	case CORBA::tk_native:
		ret_string = map_absolute_name ( type );
		break;
	case CORBA::tk_string:
		ret_string = "string";
		break;
	case CORBA::tk_wstring:
		ret_string = "CORBA::WChar*";
		break;
	case CORBA::tk_value:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "*";
		break;
	case CORBA::tk_struct:
	case CORBA::tk_union:
	case CORBA::tk_enum:
		ret_string = map_absolute_name ( type );
	//	ret_string = ret_string + "&";
		break;
	case CORBA::tk_sequence:
		ret_string = map_absolute_name ( type );
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}

} // namespace