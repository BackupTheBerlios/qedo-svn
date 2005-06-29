#include <CORBA.h>

using namespace std;

/**
 * exception
 */
class type_exception
{
};


class Property {

public:
	static  CORBA::Boolean
	extract_boolean_from_any(const CORBA::Any& a);
	static CORBA::Short
	extract_short_from_any(const CORBA::Any& a);
	static CORBA::UShort
	extract_ushort_from_any(const CORBA::Any& a);
	static CORBA::Long
	extract_long_from_any(const CORBA::Any& a);
	static CORBA::LongLong
	extract_longlong_from_any(const CORBA::Any& a);
	static CORBA::ULong
	extract_ulong_from_any(const CORBA::Any& a);
	static CORBA::ULongLong
	extract_ulonglong_from_any(const CORBA::Any& a);
	static CORBA::Double
	extract_double_from_any(const CORBA::Any& a);
	static CORBA::Float
	extract_float_from_any(const CORBA::Any& a);
	static CORBA::Char
	extract_char_from_any(const CORBA::Any& a);
	static CORBA::WChar
	extract_wchar_from_any(const CORBA::Any& a);
	static CORBA::Octet
	extract_octet_from_any(const CORBA::Any& a);
	static CORBA::Char*
	extract_string_from_any(const CORBA::Any& a);
	static CORBA::WChar*
	extract_wstring_from_any(const CORBA::Any& a);

	//###########################################
	static void
	string2any(CORBA::Any& any, const string type, const string val);
	static void
	any2string(const CORBA::Any& a, string& type, string& value);
};
