//
// generated by Qedo
//

#ifndef _VALUETYPES_H_
#define _VALUETYPES_H_


#include <CORBA.h>
#include "dinner_CutleryImpl_EQUIVALENT.h"


// BEGIN USER INSERT SECTION file
namespace dinner {

class Cookie_impl : public virtual OBV_Components::Cookie,
					public virtual CORBA::DefaultValueRefCountBase
{
private:
    static CORBA::LongLong cookie_key_;

	void operator=(const Cookie_impl&);
	Cookie_impl (const Cookie_impl&);

public:
	Cookie_impl();
	~Cookie_impl();

	// Extension
	CORBA::Boolean equal (Components::Cookie*);
};


class CookieFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};

};
// END USER INSERT SECTION file


#endif
