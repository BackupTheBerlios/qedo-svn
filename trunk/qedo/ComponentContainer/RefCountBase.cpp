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

#include "Output.h"
#include "RefCountBase.h"
#include <iostream>
#include <cassert>

static char rcsid[] UNUSED = "$Id: RefCountBase.cpp,v 1.11 2003/08/06 12:21:33 stoinski Exp $";


namespace Qedo {


CORBA::Long GlobalObjectManagement::native_object_count_ = 0;
CORBA::Long GlobalObjectManagement::CORBA_local_object_count_ = 0;
CORBA::Long GlobalObjectManagement::CORBA_object_count_ = 0;
CORBA::Long GlobalObjectManagement::native_object_instantiation_count_ = 0;
CORBA::Long GlobalObjectManagement::CORBA_object_instantiation_count_ = 0;
CORBA::Long GlobalObjectManagement::CORBA_local_object_instantiation_count_ = 0;


RefCountBase::RefCountBase()
: ref_count_ (1)
{
	++GlobalObjectManagement::native_object_count_;
	++GlobalObjectManagement::native_object_instantiation_count_;
}


RefCountBase::~RefCountBase()
{
	--GlobalObjectManagement::native_object_count_;
	
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
#ifndef MICO_ORB
: ref_count_ (1)
#endif
{
	++GlobalObjectManagement::CORBA_local_object_count_;
	++GlobalObjectManagement::CORBA_local_object_instantiation_count_;
}


RefCountLocalObject::~RefCountLocalObject()
{
	--GlobalObjectManagement::CORBA_local_object_count_;

#ifndef MICO_ORB
	if (ref_count_ != 0)
	{
		NORMAL_ERR ("RefCountLocalObject: Object deleted without reference count of null");
		assert (ref_count_ == 0);
	}
#endif
}


#ifndef MICO_ORB
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
#endif


CreateDestructCORBAObjectCounter::CreateDestructCORBAObjectCounter()
{
	++GlobalObjectManagement::CORBA_object_count_;
	++GlobalObjectManagement::CORBA_object_instantiation_count_;
}


CreateDestructCORBAObjectCounter::~CreateDestructCORBAObjectCounter()
{
	--GlobalObjectManagement::CORBA_object_count_;
}


} // namespace Qedo
