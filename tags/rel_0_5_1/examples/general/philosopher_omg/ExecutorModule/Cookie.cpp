//
// CCM Container Implementation
// (C)2000-2001 Humboldt University Berlin, Department of Computer Science
//
// $Id: Cookie.cpp,v 1.1 2002/10/30 23:13:58 tom Exp $
//

static char rcsid[] = "$Id: Cookie.cpp,v 1.1 2002/10/30 23:13:58 tom Exp $";


#include "Cookie.h"


unsigned long Cookie_impl::cookie_key_ = 0;


//
// Cookie
//
Cookie_impl::Cookie_impl
()
{
	CORBA::OctetSeq_var octet_key = new CORBA::OctetSeq();

	octet_key -> length ( 20 );

	for ( unsigned int i = 0; i < 20; i++ )
	{
		(*octet_key)[i] = ((char*)(&cookie_key_))[i];
	}

	cookieValue ( *octet_key );
}


Cookie_impl::Cookie_impl
( const CORBA::OctetSeq& val )
{
	cookieValue ( val );
}


Cookie_impl::~Cookie_impl
()
{
}


bool 
Cookie_impl::equal
( Components::Cookie* cook )
{
	CORBA::OctetSeq x = cookieValue();

	Cookie_impl* cook_impl = dynamic_cast < Cookie_impl* > ( cook );

	if ( ! cook_impl )
		return false;

	CORBA::OctetSeq y = dynamic_cast<Cookie_impl*>(cook) -> cookieValue();

	if ( x.length() != y.length() )
		return false;
    
	for ( unsigned int i = 0; i < x.length(); i++ )
	{
		if ( x[i] != y[i] )
			return false;
    }
    
	return true;
}


CORBA::ValueBase*
CookieFactory_impl::create_for_unmarshal
()
{
	return new Cookie_impl();
}
