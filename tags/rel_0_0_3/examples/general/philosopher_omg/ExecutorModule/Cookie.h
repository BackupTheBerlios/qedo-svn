//
// CCM Container Implementation
// (C)2000-2001 Humboldt University Berlin, Department of Computer Science
//
// $Id: Cookie.h,v 1.1 2002/10/30 23:13:58 tom Exp $
//

#ifndef __COOKIE_H__
#define __COOKIE_H__


#ifndef WIN32
#include CORBA_H
#include CORBA_STUB_HEADER(Components)
#else
#include <Ob/CORBA.h>
#endif

#include "Components.h"


/**
 * Cookie
 */
class Cookie_impl : public virtual OBV_Components::Cookie,
					public virtual CORBA::DefaultValueRefCountBase
{
private:
	static unsigned long cookie_key_;

	void operator=(const Cookie_impl& val);

public:
	Cookie_impl();

	Cookie_impl ( const CORBA::OctetSeq& val );

	~Cookie_impl();

	// Extension
	bool equal ( Components::Cookie* cook );
};


class CookieFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};

#endif

