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

static char rcsid[] = "$Id: RefCountBase.cpp,v 1.8 2003/07/18 11:29:52 boehme Exp $";

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
	qedo_lock lock(&mutex_);
	++ref_count_;
}


void
RefCountBase::_remove_ref()
{
	bool remove = false;
	{
		qedo_lock lock(&mutex_);
		if (--ref_count_ == 0)
			remove = true;
	}
	if(remove)
		delete this;
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
	qedo_lock lock(&mutex_);
	++ref_count_;
}


void
RefCountLocalObject::_remove_ref()
{
	bool remove = false;
	{
		qedo_lock lock(&mutex_);
		if (--ref_count_ == 0)
			remove = true;
	}
	if (remove)
		delete this;
}


unsigned long
RefCountLocalObject::_get_refcount()
{
	return ref_count_;
}

} // namespace Qedo
