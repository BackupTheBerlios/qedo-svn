#include "MappingBase.h"
#include "Debug.h"

#include <string>


using namespace std;


namespace QEDO_CIDL_Generator {



MappingBase::MappingBase
( QEDO_ComponentRepository::CIDLRepository_impl* repository )
{
	repository_ = repository;
	repository_ -> _add_ref();
}


MappingBase::~MappingBase
()
{
}


void
MappingBase::destroy
()
{
	repository_ -> _remove_ref();
	delete this;
}


string
MappingBase::tcToName(CORBA::TypeCode_ptr type)
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
MappingBase::map_absolute_name
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
MappingBase::mapAbsoluteName
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
MappingBase::mapLocalName
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
MappingBase::map_absolute_under_name
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
MappingBase::map_absolute_slash_name
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
MappingBase::mapScopeName
(CORBA__::IRObject_ptr type, string prefix, string suffix)
throw(CannotMapAbsoluteName)
{
	string buf_string;
	string result;
	IR__::Contained_var contained;


	if(type->def_kind() == CORBA__::dk_Composition) {
		contained = IR__::Contained::_narrow ( type );
		result = contained->id();
		string module;
		IR__::Contained_ptr module_def = 0;
		string::size_type pos = result.find_last_of("/");
		if(pos != string::npos)	{
			module = result.substr(0, pos);
			module.append(":1.0");
			module_def = repository_->lookup_id(module.c_str());
			return map_absolute_name(module_def);
		}
		return "";
	}
	

	try
	{
		contained = IR__::Contained::_narrow ( type );
		buf_string = contained -> absolute_name ();
	}
	catch ( CORBA::SystemException& )
	{
		throw CannotMapAbsoluteName();
	}
	if ( CORBA::is_nil ( contained ) )
		throw CannotMapAbsoluteName();

	string::size_type index;
	index = buf_string.find_last_of("::");
	if (index != string::npos)
	{
		result = prefix + buf_string.substr(2, index - 1) + suffix;
	}
	else
	{
		result = prefix + suffix;
	}

	return CORBA::string_dup(result.c_str());
}


char*
MappingBase::map_return_type
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
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
MappingBase::map_value_return_type
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
MappingBase::map_idl_type
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
MappingBase::map_attribute_type
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
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
MappingBase::assign_attribute
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
MappingBase::map_in_parameter_type
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

	switch ( real_typecodekind )
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
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
MappingBase::map_inout_parameter_type
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
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


char*
MappingBase::map_out_parameter_type
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

	switch ( real_typecodekind )
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
	default:
		throw CannotMapType();
	}
	return CORBA::string_dup ( ret_string.c_str() );
}


} // namespace QEDO_CIDL_Generator
