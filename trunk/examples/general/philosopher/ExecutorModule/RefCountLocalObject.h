//
// TETRA
// Example 1 for Stream Container Implementation
// (C)2000-2002 Humboldt University Berlin, Department of Computer Science
//
// $Id: RefCountLocalObject.h,v 1.1 2002/10/13 12:08:44 tom Exp $
//

#ifndef __REFCOUNT_LOCAL_OBJECT_H__
#define __REFCOUNT_LOCAL_OBJECT_H__

#include <OB/CORBA.h>

namespace dinner {

class RefCountLocalObject : public virtual CORBA::LocalObject
{
private:
	unsigned long ref_count_;

public:
	RefCountLocalObject();
	virtual ~RefCountLocalObject();

	void _add_ref();
	void _remove_ref();
	unsigned long _get_refcount();
};

} // namespace dinner

#endif
