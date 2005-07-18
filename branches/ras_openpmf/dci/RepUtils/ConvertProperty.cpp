#include "ConvertProperty.h"

CORBA::Boolean
Property::extract_boolean_from_any(const CORBA::Any& a) {

	CORBA::Boolean ret;

	if(!(a >>= CORBA::Any::to_boolean(ret))) 
		throw type_exception();

	return ret;
};

CORBA::Short
Property::extract_short_from_any(const CORBA::Any& a) {

	CORBA::Short ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::UShort
Property::extract_ushort_from_any(const CORBA::Any& a) {

	CORBA::UShort ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::Long
Property::extract_long_from_any(const CORBA::Any& a) {

	CORBA::Long ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::LongLong
Property::extract_longlong_from_any(const CORBA::Any& a) {

	CORBA::LongLong ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::ULong
Property::extract_ulong_from_any(const CORBA::Any& a) {

	CORBA::ULong ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::ULongLong
Property::extract_ulonglong_from_any(const CORBA::Any& a) {

	CORBA::ULongLong ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::Double
Property::extract_double_from_any(const CORBA::Any& a) {

	CORBA::Double ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::Float
Property::extract_float_from_any(const CORBA::Any& a) {

	CORBA::Float ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::Char
Property::extract_char_from_any(const CORBA::Any& a) {

	CORBA::Char ret;

	if(!(a >>= ret))
		throw type_exception();

	return ret;
};

CORBA::WChar
Property::extract_wchar_from_any(const CORBA::Any& a) {

	CORBA::WChar ret;

	if(!(a >>= CORBA::Any::to_wchar(ret)))
		throw type_exception();

	return ret;
};

CORBA::Octet
Property::extract_octet_from_any(const CORBA::Any& a) {

	CORBA::Octet ret;

	if(!(a >>= CORBA::Any::to_octet(ret)))
		throw type_exception();

	return ret;
};

CORBA::Char*
Property::extract_string_from_any(const CORBA::Any& a) {

	CORBA::Char* ret = 0;
	
	if(!(a >>= ret))
		throw type_exception();

	//CORBA::String_var tmp = ret;
	return ret;
};


CORBA::WChar*
Property::extract_wstring_from_any(const CORBA::Any& a) {

	CORBA::WChar* ret = 0;

	if(!(a >>= CORBA::Any::to_wstring(ret, 0)))
		throw type_exception();

	return ret;
};

//###########################################
void
Property::string2any(CORBA::Any& any, const string type, const string val)
{
	if( type == "boolean" )
	{
		CORBA::Boolean v;
		if( val == "true" )
		{
			v = true;
		}
		else
		{
			v = false;
		}
		any <<= CORBA::Any::from_boolean( v );
	}

	if( type == "char" )
	{
		CORBA::Char v = val[0];
		any <<= CORBA::Any::from_char( v );
	}

	if( type == "double" )
	{
		CORBA::Double v = atof( val.c_str() );
		any <<= v;
	}

	if( type == "float" )
	{
		CORBA::Float v = atof( val.c_str() );
		any <<= v;
	}

	if( type == "short" )
	{
		CORBA::Short v = atoi( val.c_str() );
		any <<= v;
	}

	if( type == "long" )
	{
		CORBA::Long v = atol( val.c_str() );
		any <<= v;
	}

	if( type == "objref" )
	{
		// TODO
	}

	if( type == "octet" )
	{
		CORBA::Octet v = val[0];
		any <<= CORBA::Any::from_octet( v );
	}

	if( type == "string" )
	{
		any <<= val.c_str();
	}

	if( type == "ulong" )
	{
		CORBA::ULong v = atol( val.c_str() );
		any <<= v;
	}

	if( type == "ushort" )
	{
		CORBA::UShort v = atoi( val.c_str() );
		any <<= v;
	}
}
//###################
void
Property::any2string(const CORBA::Any& a, string& type, string& value) {

	char buf[50];

	// get typecode
	CORBA::TypeCode_var code =
		a.type();
 
	// scan aliases
	while(code->kind() == CORBA::tk_alias)
		code = code->content_type();

	switch(code->kind()) {
	case CORBA::tk_boolean: {
		type = "boolean";
		CORBA::Boolean b = extract_boolean_from_any(a);
		if(b) 
			value = "true";
		else
			value = "false";
		break;
	}
	case CORBA::tk_short: {
		type = "short";
		CORBA::Short s = extract_short_from_any(a);
		_itoa(s, buf, 10);
		value = buf;
		break;
	}
	case CORBA::tk_ushort: {
		type = "ushort";
		CORBA::UShort s = extract_ushort_from_any(a);
		_itoa(s, buf, 10);
		value = buf;
		break;
	}
	case CORBA::tk_long: {
		type = "long";
		CORBA::Long s = extract_long_from_any(a);
		_ltoa(s, buf, 10);
		value = buf;
		break;
	}
	case CORBA::tk_ulong: {
		type = "ulong";
		CORBA::ULong s = extract_ulong_from_any(a);
		_ltoa(s, buf, 10);
		value = buf;
		break;
	}
	case CORBA::tk_float: {
		type = "float";
		CORBA::Float s = extract_float_from_any(a);
		_gcvt(s,20,buf);
		value = buf;
		break;
	}
	case CORBA::tk_double: {
		type = "double";
		CORBA::Double s = extract_double_from_any(a);
		_gcvt(s,20,buf);
		value = buf;
		break;
	}
	case CORBA::tk_char: {
		type = "char";
		CORBA::Char c = extract_char_from_any(a);
		value = c;
		break;
	}
	case CORBA::tk_string: {
		type = "string";
		CORBA::Char* s = extract_string_from_any(a);
		value = s;
		break;
	}
	case CORBA::tk_wstring: {
		type = "wstring";
		wstring ws = extract_wstring_from_any(a);
//		value = (const string) string(ws);
	}
	case CORBA::tk_sequence: {
		type = "sequence of";
		value = "";
		break;
	}
	} //switch
}