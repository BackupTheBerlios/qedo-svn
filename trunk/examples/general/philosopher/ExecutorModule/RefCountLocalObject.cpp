//
// TETRA
// Example 1 for Stream Container Implementation
// (C)2000-2002 Humboldt University Berlin, Department of Computer Science
//
// $Id: RefCountLocalObject.cpp,v 1.1 2002/10/13 12:08:44 tom Exp $
//

static char rcsid[] = "$Id: RefCountLocalObject.cpp,v 1.1 2002/10/13 12:08:44 tom Exp $";


#include"RefCountLocalObject.h"
#include <iostream>

using namespace std;

namespace dinner {

RefCountLocalObject::RefCountLocalObject()
: ref_count_ (1)
{
}


RefCountLocalObject::~RefCountLocalObject()
{
	cout << "RefCountLocalObject: Destructor called" << endl;

	if (ref_count_ != 0)
	{
		cerr << "RefCountLocalObject: Object deleted without reference count of null" << endl;
		cerr << "RefCountLocalObject: ref count was " << ref_count_ << endl;
		assert (ref_count_ == 0);
	}
}


void
RefCountLocalObject::_add_ref()
{
	++ref_count_;
}


void
RefCountLocalObject::_remove_ref()
{
	if (--ref_count_ == 0)
	{
		delete this;
	}
}


unsigned long
RefCountLocalObject::_get_refcount()
{
	return ref_count_;
}

} // namespace dinner