/***************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                  */
/*                                                                         */
/* http://qedo.berlios.de/                                                 */
/*                                                                         */
/* Copyright (C) 2002 by the Qedo Team                                     */
/*                                                                         */
/* This library is free software; you can redistribute it and/or           */
/* modify it under the terms of the GNU Lesser General Public              */
/* License as published by the Free Software Foundation; either            */
/* version 2.1 of the License, or (at your option) any later version.      */
/*                                                                         */
/* This library is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU        */
/* Lesser General Public License for more details.                         */
/*                                                                         */
/* You should have received a copy of the GNU Lesser General Public        */
/* License along with this library; if not, write to the Free Software     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
/***************************************************************************/

static char rcsid[] = "$Id: RefCountLocalObject.cpp,v 1.2 2002/10/13 12:37:01 tom Exp $";


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