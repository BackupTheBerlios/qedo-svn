#include "CPPBase.h"

#include <string>


namespace QEDO_CIDL_Generator {


CPPBase::CPPBase
(QEDO_ComponentRepository::CIDLRepository_impl *repository)
: GeneratorBase(repository)
{
}


CPPBase::~CPPBase
()
{
}


bool
CPPBase::open_module(Printer& out, IR__::Contained* cur_cont, std::string prefix)
{
	IR__::Container_ptr a_container = cur_cont->defined_in();
	if(a_container->def_kind() == CORBA__::dk_Module) 
	{
		IR__::ModuleDef_var a_module = IR__::ModuleDef::_narrow(a_container);
		if(! this->open_module(out, a_module))
		{
			// the prefix must be written first
			out << "namespace " << prefix;
		}
		else
		{
			out << "namespace ";
		}
		out << mapName(a_module) << " {\n";
		out.indent();
		return true;
	}

	return false;
};


void
CPPBase::close_module(Printer& out, IR__::Contained* cur_cont)
{
	IR__::Container_ptr a_container=cur_cont->defined_in();
	if(a_container->def_kind()==CORBA__::dk_Module) 
	{
		IR__::ModuleDef_var act_mod = IR__::ModuleDef::_narrow(a_container);
		this->close_module(out, act_mod);
		out.unindent();
		out << "};\n";
	}
}


std::string
CPPBase::mapName(std::string name)
{
	//
	// check keywords
	//
	if(name.compare("new") == 0)
	{
		name.insert(0, "_cxx_");
	}

	return name;
}


std::string
CPPBase::mapName(IR__::Contained_ptr obj)
{
	return mapName(obj->name());
}


/*
 * escape each name with _cxx_ if keyword
 */
std::string
CPPBase::mapFullName(IR__::Contained_ptr obj)
{
	std::string name;
	name = obj->absolute_name();

	std::string::size_type pos = 0;
	std::string::size_type begin;
	std::string::size_type end;
	while(pos != std::string::npos)
	{
		begin = pos;
		end = std::string::npos;

		pos = name.find("::", pos);
		if(pos != std::string::npos)
		{
			pos += 2;
			begin = pos;

			pos = name.find("::", pos);
			end = pos;
		}

		name.replace(begin, end - begin, mapName(name.substr(begin, end - begin)));
	}

	return name;
}


std::string
CPPBase::mapFullNameLocal(IR__::Contained_ptr obj)
{
	std::string name;
	name = mapFullName(obj);

	std::string::size_type pos;
	pos = name.rfind("::");
	if(pos == std::string::npos)
	{
		pos = 0;
	}
	else
	{
		pos += 2;
	}

	name.insert(pos, "CCM_");

	return name;
}


std::string
CPPBase::mapFullNameServant(IR__::Contained_ptr obj)
{
	std::string name;
	name = mapFullName(obj);

	std::string::size_type pos;
	pos = name.find("::");
	if(pos == 0)
	{
		pos += 2;
	}
	else
	{
		pos = 0;
	}

	name.insert(pos, "SERVANT_");

	return name;
}


std::string
CPPBase::mapFullNamePOA(IR__::Contained_ptr obj)
{
	std::string name;
	name = mapFullName(obj);

	std::string::size_type pos;
	pos = name.find("::");
	if(pos == 0)
	{
		pos += 2;
	}
	else
	{
		pos = 0;
	}

	name.insert(pos, "POA_");

	return name;
}


std::string 
CPPBase::mapScopeName
(IR__::Contained_ptr type)
throw(CannotMapAbsoluteName)
{
	string buf_string;
	std::string name;

	if(type->def_kind() == CORBA__::dk_Composition)
	{
		name = type->id();
		string module;
		IR__::Contained_ptr module_def = 0;
		string::size_type pos = name.find_last_of("/");
		if(pos != string::npos)
		{
			module = name.substr(0, pos);
			module.append(":1.0");
			module_def = repository_->lookup_id(module.c_str());
			return mapFullName(module_def);
		}
		return "";
	}

	name = mapFullName(type);

	std::string::size_type pos;
	pos = name.rfind("::");
	if (pos == std::string::npos)
	{
		pos = 0;
	}

	name.replace(pos, std::string::npos, "");

	return name;
}


char* 
CPPBase::map_absolute_name
( CORBA__::IRObject_ptr type )
throw ( CannotMapAbsoluteName )
{
	string ret_string;

	IR__::Contained_var contained;

	try
	{
		contained = IR__::Contained::_narrow ( type );
		if ( CORBA::is_nil ( contained ) ) {
			throw CannotMapAbsoluteName();
		}

		ret_string = contained -> absolute_name ();
	}
	catch ( /*CORBA::SystemException& */ ...)
	{
		throw CannotMapAbsoluteName();
	}
	if ( CORBA::is_nil ( contained ) )
		throw CannotMapAbsoluteName();

	return CORBA::string_dup ( ret_string.c_str() + 2 );
}


char* 
CPPBase::mapAbsoluteName
( CORBA__::IRObject_ptr type, string delim )
throw ( CannotMapAbsoluteName )
{
	string ret_string;

	IR__::Contained_var contained;

	try
	{
		contained = IR__::Contained::_narrow ( type );
		ret_string = contained -> absolute_name ();
	}
	catch ( CORBA::SystemException& )
	{
		throw CannotMapAbsoluteName();
	}
	if ( CORBA::is_nil ( contained ) )
		throw CannotMapAbsoluteName();

	string::size_type index = 0;
	string::size_type search_begin = 0;
	while(index < string::npos)
	{
		index = ret_string.find("::", search_begin);
		if(index != string::npos)
		{
			ret_string.replace(index, 2, delim);
		}
	};

	return CORBA::string_dup ( ret_string.c_str() + 1 );
}


char* 
CPPBase::mapLocalName
( CORBA__::IRObject_ptr type )
throw ( CannotMapAbsoluteName )
{
	string result;

	IR__::Contained_var contained;

	try	{
		contained = IR__::Contained::_narrow ( type );
		result = contained->absolute_name();
	}
	catch ( CORBA::SystemException& ) {
		throw CannotMapAbsoluteName();
	}
	if ( CORBA::is_nil ( contained ) ) {
		throw CannotMapAbsoluteName();
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
CPPBase::map_absolute_under_name
( CORBA__::IRObject_ptr type )
throw ( CannotMapAbsoluteName )
{
	string buf_string;
	string ret_string;

	IR__::Contained_var contained;

	try
	{
		contained = IR__::Contained::_narrow ( type );
		buf_string = contained -> absolute_name ();
	}
	catch ( CORBA::SystemException& )
	{
		contained = IR__::Contained::_nil();
	}

	if ( CORBA::is_nil ( contained ) )
		throw CannotMapAbsoluteName();

	string::size_type index, search_begin;
	bool to_search = true;
	search_begin=0;
	while(to_search) {
		index=buf_string.find("::",search_begin);
		if (index==string::npos) {
			to_search=false;
		} else {
			buf_string.replace(index,2,"_");
		}
	};
	return CORBA::string_dup ( buf_string.c_str() + 1 );
}


char* 
CPPBase::map_absolute_slash_name
( CORBA__::IRObject_ptr type )
throw ( CannotMapAbsoluteName )
{
	string buf_string;
	string ret_string;

	IR__::Contained_var contained;

	try
	{
		contained = IR__::Contained::_narrow ( type );
		buf_string = contained -> absolute_name ();
	}
	catch ( CORBA::SystemException& )
	{
		contained = IR__::Contained::_nil();
	}

	if ( CORBA::is_nil ( contained ) )
		throw CannotMapAbsoluteName();

	string::size_type index, search_begin;
	bool to_search = true;
	search_begin=0;
	while(to_search) {
		index=buf_string.find("::",search_begin);
		if (index==string::npos) {
			to_search=false;
		} else {
			buf_string.replace(index,2,"/");
		}
	};
	return CORBA::string_dup ( buf_string.c_str() + 1 );
}


char*
CPPBase::map_return_type
( IR__::IDLType_ptr type )
throw ( CannotMapType )
{
	string ret_string;

	CORBA::TCKind typecodekind;
	typecodekind=type->type()->kind();

	//
	// skip typedefs
	//
	IR__::IDLType_var a_type = IR__::IDLType::_duplicate(type);
	while(typecodekind == CORBA::tk_alias)
	{
		IR__::AliasDef_var alias = IR__::AliasDef::_narrow(a_type);
		a_type = alias->original_type_def();
		typecodekind = a_type->type()->kind();
	}

	switch (typecodekind)
	{
	case CORBA::tk_alias : {
		assert(0);
		break; }
	case CORBA::tk_void:
		ret_string = "void";
		break;
	case CORBA::tk_short:
		ret_string = "CORBA::Short";
		break;
	case CORBA::tk_long:
		ret_string = "CORBA::Long";
		break;
	case CORBA::tk_longlong:
		ret_string = "CORBA::LongLong";
		break;
	case CORBA::tk_ushort:
		ret_string = "CORBA::UShort";
		break;
	case CORBA::tk_ulong:
		ret_string = "CORBA::ULong";
		break;
	case CORBA::tk_ulonglong:
		ret_string = "CORBA::ULongLong";
		break;
	case CORBA::tk_float:
		ret_string = "CORBA::Float";
		break;
	case CORBA::tk_double:
		ret_string = "CORBA::Double";
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
			ret_string = ret_string + "_ptr";
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
		ret_string = "char*";
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
		//checking for fixed or variable length
		// the check is missing yet
		// assuming variable length
		ret_string = map_absolute_name(type);
		ret_string = ret_string + "*";
		break;
	case CORBA::tk_enum:
		ret_string = map_absolute_name ( type );
		break;
	case CORBA::tk_sequence:
		ret_string = map_absolute_name(type);
		ret_string = ret_string + "*";
		break;
	case CORBA::tk_TypeCode :
		ret_string = "CORBA::TypeCode_ptr";
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
CPPBase::map_value_return_type
( IR__::IDLType_ptr type )
throw ( CannotMapType )
{
	string ret_string;

	switch ( type -> type() -> kind() )
	{
	case CORBA::tk_void:
		ret_string = "void";
		break;
	case CORBA::tk_short:
		ret_string = "CORBA::Short";
		break;
	case CORBA::tk_long:
		ret_string = "CORBA::Long";
		break;
	case CORBA::tk_longlong:
		ret_string = "CORBA::LongLong";
		break;
	case CORBA::tk_ushort:
		ret_string = "CORBA::UShort";
		break;
	case CORBA::tk_ulong:
		ret_string = "CORBA::ULong";
		break;
	case CORBA::tk_ulonglong:
		ret_string = "CORBA::ULongLong";
		break;
	case CORBA::tk_float:
		ret_string = "CORBA::Float";
		break;
	case CORBA::tk_double:
		ret_string = "CORBA::Double";
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
			ret_string = ret_string + "_ptr";
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
		ret_string = "char*";
		break;
	case CORBA::tk_wstring:
		ret_string = "CORBA::WChar*";
		break;
	case CORBA::tk_value:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "*";
		break;
	case CORBA::tk_struct:
		ret_string = map_absolute_name ( type );
	case CORBA::tk_union:
		ret_string = map_absolute_name ( type );
	case CORBA::tk_enum:
//		ret_string = "const ";
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "&";
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
CPPBase::map_idl_type
( IR__::IDLType_ptr type )
throw ( CannotMapType )
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
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
CPPBase::map_attribute_type
( IR__::IDLType_ptr type )
throw ( CannotMapType )
{
	string ret_string;

	CORBA::TCKind typecodekind;
	typecodekind=type->type()->kind();

	//
	// skip typedefs
	//
	IR__::IDLType_var a_type = IR__::IDLType::_duplicate(type);
	while(typecodekind == CORBA::tk_alias)
	{
		IR__::AliasDef_var alias = IR__::AliasDef::_narrow(a_type);
		a_type = alias->original_type_def();
		typecodekind = a_type->type()->kind();
	}

	switch (typecodekind)
	{
	case CORBA::tk_void:
		ret_string = "void";
		break;
	case CORBA::tk_short:
		ret_string = "CORBA::Short";
		break;
	case CORBA::tk_long:
		ret_string = "CORBA::Long";
		break;
	case CORBA::tk_longlong:
		ret_string = "CORBA::LongLong";
		break;
	case CORBA::tk_ushort:
		ret_string = "CORBA::UShort";
		break;
	case CORBA::tk_ulong:
		ret_string = "CORBA::ULong";
		break;
	case CORBA::tk_ulonglong:
		ret_string = "CORBA::ULongLong";
		break;
	case CORBA::tk_float:
		ret_string = "CORBA::Float";
		break;
	case CORBA::tk_double:
		ret_string = "CORBA::Double";
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
			ret_string = ret_string + "_ptr";
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
		ret_string = "char*";
		break;
	case CORBA::tk_wstring:
		ret_string = "CORBA::WChar*";
		break;
	case CORBA::tk_value:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "_var";
		break;
	case CORBA::tk_struct:
	case CORBA::tk_union:
		//checking for fixed or variable length
		// the check is missing yet
		// assuming variable length
		ret_string = map_absolute_name(type);
		ret_string = ret_string + "_var";
		break;
	case CORBA::tk_enum:
		ret_string = map_absolute_name ( type );
		break;
	case CORBA::tk_sequence:
		ret_string = map_absolute_name(type);
		ret_string = ret_string + "*";
		break;
	case CORBA::tk_TypeCode :
		ret_string = "CORBA::TypeCode_ptr";
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
CPPBase::assign_attribute
( IR__::IDLType_ptr type )
throw ( CannotMapType )
{
	string ret_string;

	CORBA::TCKind pre_typecodekind;
	CORBA::TCKind real_typecodekind;
	pre_typecodekind=type->type()->kind() ;

	if(pre_typecodekind == CORBA::tk_alias) {
		IR__::AliasDef_var alias = IR__::AliasDef::_narrow(type);
		real_typecodekind = alias->original_type_def()->type()->kind();
	} else {
		real_typecodekind = type -> type() -> kind() ;
	};

	switch (real_typecodekind)
	{
	case CORBA::tk_void:
	case CORBA::tk_short:
	case CORBA::tk_long:
	case CORBA::tk_longlong:
	case CORBA::tk_ushort:
	case CORBA::tk_ulong:
	case CORBA::tk_ulonglong:
	case CORBA::tk_float:
	case CORBA::tk_double:
	case CORBA::tk_longdouble:
	case CORBA::tk_boolean:
		ret_string = "param";
	case CORBA::tk_char:
		ret_string = "param";
		break;
	case CORBA::tk_wchar:
		ret_string = "param";
		break;
	case CORBA::tk_any:
		ret_string = "param";
		break;
	case CORBA::tk_objref:
		// First test whether we are a Contained, if not we are simply CORBA::Object_ptr
		try
		{
			ret_string = map_absolute_name ( type );
			ret_string = ret_string + "::_duplicate(param)";
		}
		catch ( CannotMapAbsoluteName& )
		{
			ret_string = "CORBA::Object::_duplicate(param)";
		}
		break;
	case CORBA::tk_native:
		ret_string = map_absolute_name ( type );
		break;
	case CORBA::tk_string:
		ret_string = "CORBA::string_dup(param)";
		break;
	case CORBA::tk_wstring:
		ret_string = "CORBA::string_dup(param)";
		break;
	case CORBA::tk_value:
		ret_string = "param";
		break;
	case CORBA::tk_struct:
	case CORBA::tk_union:
		//checking for fixed or variable length
		// the check is missing yet
		// assuming variable length
		ret_string = "new ";
		ret_string = ret_string + map_absolute_name(type);
		ret_string = ret_string + "(param)";
		break;
	case CORBA::tk_enum:
		ret_string = "param";
		break;
	case CORBA::tk_sequence:
		//checking for fixed or variable length
		// the check is missing yet
		// assuming variable length
		ret_string = "new ";
		ret_string = ret_string + map_absolute_name(type);
		ret_string = ret_string + "(param)";
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
CPPBase::map_in_parameter_type
( IR__::IDLType_ptr type )
throw ( CannotMapType )
{
	string ret_string;

	CORBA::TCKind typecodekind;
	typecodekind=type->type()->kind();

	//
	// skip typedefs
	//
	IR__::IDLType_var a_type = IR__::IDLType::_duplicate(type);
	while(typecodekind == CORBA::tk_alias)
	{
		IR__::AliasDef_var alias = IR__::AliasDef::_narrow(a_type);
		a_type = alias->original_type_def();
		typecodekind = a_type->type()->kind();
	}

	switch (typecodekind)
	{
	case CORBA::tk_alias : {
		assert(0);
		break; }
	case CORBA::tk_void:
		ret_string = "void";
		break;
	case CORBA::tk_short:
		ret_string = "CORBA::Short";
		break;
	case CORBA::tk_long:
		ret_string = "CORBA::Long";
		break;
	case CORBA::tk_longlong:
		ret_string = "CORBA::LongLong";
		break;
	case CORBA::tk_ushort:
		ret_string = "CORBA::UShort";
		break;
	case CORBA::tk_ulong:
		ret_string = "CORBA::ULong";
		break;
	case CORBA::tk_ulonglong:
		ret_string = "CORBA::ULongLong";
		break;
	case CORBA::tk_float:
		ret_string = "CORBA::Float";
		break;
	case CORBA::tk_double:
		ret_string = "CORBA::Double";
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
		ret_string = "const CORBA::Any&";
		break;
	case CORBA::tk_objref:
		// First test whether we are a Contained, if not we are simply CORBA::Object_ptr
		try
		{
			ret_string = map_absolute_name ( type );
			ret_string = ret_string + "_ptr";
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
		ret_string = "const char*";
		break;
	case CORBA::tk_wstring:
		ret_string = "const CORBA::WChar*";
		break;
	case CORBA::tk_value:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "*";
		break;
	case CORBA::tk_struct:
	case CORBA::tk_union:
		ret_string="const ";
		ret_string=ret_string + map_absolute_name(type);
		ret_string=ret_string + "&";
		break;
	case CORBA::tk_enum:
		ret_string = map_absolute_name ( type );
		break;
	case CORBA::tk_sequence:
		ret_string="const ";
		ret_string=ret_string + map_absolute_name(type);
		ret_string=ret_string + "&";
		break;
	case CORBA::tk_TypeCode :
		ret_string = "CORBA::TypeCode_ptr";
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
CPPBase::map_inout_parameter_type
( IR__::IDLType_ptr type )
throw ( CannotMapType )
{
	string ret_string;

	CORBA::TCKind typecodekind;
	typecodekind=type->type()->kind();

	//
	// skip typedefs
	//
	IR__::IDLType_var a_type = IR__::IDLType::_duplicate(type);
	while(typecodekind == CORBA::tk_alias)
	{
		IR__::AliasDef_var alias = IR__::AliasDef::_narrow(a_type);
		a_type = alias->original_type_def();
		typecodekind = a_type->type()->kind();
	}

	switch(typecodekind)
	{
	case CORBA::tk_void:
		ret_string = "void";
		break;
	case CORBA::tk_short:
		ret_string = "CORBA::Short&";
		break;
	case CORBA::tk_long:
		ret_string = "CORBA::Long&";
		break;
	case CORBA::tk_longlong:
		ret_string = "CORBA::LongLong&";
		break;
	case CORBA::tk_ushort:
		ret_string = "CORBA::UShort&";
		break;
	case CORBA::tk_ulong:
		ret_string = "CORBA::ULong&";
		break;
	case CORBA::tk_ulonglong:
		ret_string = "CORBA::ULongLong&";
		break;
	case CORBA::tk_float:
		ret_string = "CORBA::Float&";
		break;
	case CORBA::tk_double:
		ret_string = "CORBA::Double&";
		break;
	case CORBA::tk_longdouble:
		ret_string = "CORBA::LongDouble&";
		break;
	case CORBA::tk_boolean:
		ret_string = "CORBA::Boolean&";
		break;
	case CORBA::tk_char:
		ret_string = "CORBA::Char&";
		break;
	case CORBA::tk_wchar:
		ret_string = "CORBA::WChar&";
		break;
	case CORBA::tk_any:
		ret_string = "CORBA::Any&";
		break;
	case CORBA::tk_objref:
		// First test whether we are a Contained, if not we are simply CORBA::Object_ptr
		try
		{
			ret_string = map_absolute_name ( type );
			ret_string = ret_string + "_ptr&";
		}
		catch ( CannotMapAbsoluteName& )
		{
			ret_string = "CORBA::Object_ptr&";
		}
		break;
	case CORBA::tk_native:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "&";
		break;
	case CORBA::tk_string:
		ret_string = "char*&";
		break;
	case CORBA::tk_wstring:
		ret_string = "CORBA::WChar*&";
		break;
	case CORBA::tk_value:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "*&";
		break;
	case CORBA::tk_struct:
	case CORBA::tk_union:
	case CORBA::tk_enum:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "&";
		break;
	case CORBA::tk_TypeCode :
		ret_string = "CORBA::TypeCode_ptr&";
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
CPPBase::map_out_parameter_type
( IR__::IDLType_ptr type )
throw ( CannotMapType )
{
	string ret_string;
	
	CORBA::TCKind typecodekind;
	typecodekind=type->type()->kind();

	//
	// skip typedefs
	//
	IR__::IDLType_var a_type = IR__::IDLType::_duplicate(type);
	while(typecodekind == CORBA::tk_alias)
	{
		IR__::AliasDef_var alias = IR__::AliasDef::_narrow(a_type);
		a_type = alias->original_type_def();
		typecodekind = a_type->type()->kind();
	}

	switch(typecodekind)
	{
	case CORBA::tk_void:
		ret_string = "void";
		break;
	case CORBA::tk_short:
		ret_string = "CORBA::Short_out";
		break;
	case CORBA::tk_long:
		ret_string = "CORBA::Long_out";
		break;
	case CORBA::tk_longlong:
		ret_string = "CORBA::LongLong_out";
		break;
	case CORBA::tk_ushort:
		ret_string = "CORBA::UShort_out";
		break;
	case CORBA::tk_ulong:
		ret_string = "CORBA::ULong_out";
		break;
	case CORBA::tk_ulonglong:
		ret_string = "CORBA::ULongLong_out";
		break;
	case CORBA::tk_float:
		ret_string = "CORBA::Float_out";
		break;
	case CORBA::tk_double:
		ret_string = "CORBA::Double_out";
		break;
	case CORBA::tk_longdouble:
		ret_string = "CORBA::LongDouble_out";
		break;
	case CORBA::tk_boolean:
		ret_string = "CORBA::Boolean_out";
		break;
	case CORBA::tk_char:
		ret_string = "CORBA::Char_out";
		break;
	case CORBA::tk_wchar:
		ret_string = "CORBA::WChar_out";
		break;
	case CORBA::tk_any:
		ret_string = "CORBA::Any_out";
		break;
	case CORBA::tk_objref:
		// First test whether we are a Contained, if not we are simply CORBA::Object_ptr
		try
		{
			ret_string = map_absolute_name ( type );
			ret_string = ret_string + "_out";
		}
		catch ( CannotMapAbsoluteName& )
		{
			ret_string = "CORBA::Object_out";
		}
		break;
	case CORBA::tk_native:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "&";
		break;
	case CORBA::tk_string:
		ret_string = "CORBA::String_out";
		break;
	case CORBA::tk_wstring:
		ret_string = "CORBA::WString_out";
		break;
	case CORBA::tk_value:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "_out";
		break;
	case CORBA::tk_struct:
	case CORBA::tk_union:
	case CORBA::tk_enum:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "_out";
		break;
	case CORBA::tk_sequence:
		ret_string = map_absolute_name ( type );
		ret_string = ret_string + "_out";
		break;
	case CORBA::tk_TypeCode :
		ret_string = "CORBA::TypeCode_out";
		break;
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}

} // namespace

