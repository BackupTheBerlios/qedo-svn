/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                   */
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

static char rcsid[] = "$Id: RefCountBase.cpp,v 1.5 2003/05/26 13:37:05 stoinski Exp $";

#include "Output.h"
#include "RefCountBase.h"
#include <iostream>
#include <cassert>


namespace Qedo {


RefCountBase::RefCountBase()
: ref_count_ (1)
{
}


RefCountBase::~RefCountBase()
{
	DEBUG_OUT ("RefCountBase: Destructor called");
	
	if (ref_count_ != 0)
	{
		NORMAL_ERR ("RefCountBase: Object deleted without reference count of null");
		assert (ref_count_ == 0);
	}
}


void
RefCountBase::_add_ref()
{
#ifdef WIN32
	InterlockedIncrement (&ref_count_);
#else
	// Here the qedo::mutex must be added
	++ref_count_;
#endif
}


void
RefCountBase::_remove_ref()
{
#ifdef WIN32
	if (InterlockedDecrement (&ref_count_) == 0)
		delete this;
#else
	// Here the qedo::mutex must be added
	if (--ref_count_ == 0)
	{
		delete this;
	}
#endif
}


unsigned long
RefCountBase::_get_refcount()
{
	return ref_count_;
}


RefCountLocalObject::RefCountLocalObject()
: ref_count_ (1)
{
}


RefCountLocalObject::~RefCountLocalObject()
{
	DEBUG_OUT ("RefCountLocalObject: Destructor called");

	if (ref_count_ != 0)
	{
		NORMAL_ERR ("RefCountLocalObject: Object deleted without reference count of null");
		assert (ref_count_ == 0);
	}
}


void
RefCountLocalObject::_add_ref()
{
#ifdef WIN32
	InterlockedIncrement (&ref_count_);
#else
	// Here the qedo::mutex must be added
	++ref_count_;
#endif
}


void
RefCountLocalObject::_remove_ref()
{
#ifdef WIN32
	if (InterlockedDecrement (&ref_count_) == 0)
		delete this;
#else
	// Here the qedo::mutex must be added
	if (--ref_count_ == 0)
	{
		delete this;
	}
#endif
}


unsigned long
RefCountLocalObject::_get_refcount()
{
	return ref_count_;
}

} // namespace Qedo
