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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#ifdef _DEBUG
#include <set>
#endif

static char rcsid[] UNUSED = "$Id: RefCountBase.cpp,v 1.18 2003/10/05 16:48:22 tom Exp $";


namespace Qedo {


#ifdef _DEBUG
static std::set<RefCountLocalObject*> CORBA_local_object_set;
static std::set<RefCountBase*> native_object_set;
static std::set<CreateDestructCORBAObjectCounter*> CORBA_object_set;
static QedoMutex CORBA_object_mutex_;
#else
static CORBA::Long native_object_count_ = 0;
static CORBA::Long CORBA_local_object_count_ = 0;
static CORBA::Long CORBA_object_count_ = 0;
#endif

CORBA::Long GlobalObjectManagement::native_object_instantiation_count_ = 0;
CORBA::Long GlobalObjectManagement::CORBA_object_instantiation_count_ = 0;
CORBA::Long GlobalObjectManagement::CORBA_local_object_instantiation_count_ = 0;

RefCountBase::RefCountBase()
: ref_count_ (1)
{
#ifdef _DEBUG
	QedoLock lock(&mutex_);
	native_object_set.insert(this);
#else
	++native_object_count_;
#endif
	++GlobalObjectManagement::native_object_instantiation_count_;
}


RefCountBase::~RefCountBase()
{
#ifdef _DEBUG
	QedoLock lock(&mutex_);
	native_object_set.erase(this);
#else
	--native_object_count_;
#endif
	
	if (ref_count_ != 0)
	{
		NORMAL_ERR ("RefCountBase: Object deleted without reference count of null");
		assert (ref_count_ == 0);
	}
}


void
RefCountBase::_add_ref()
{
	QedoLock lock(&mutex_);
	++ref_count_;
}


void
RefCountBase::_remove_ref()
{
	bool remove = false;
	{
		QedoLock lock(&mutex_);
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
#ifdef _DEBUG
	CORBA_local_object_set.insert(this);
#else
	++CORBA_local_object_count_;
#endif
	++GlobalObjectManagement::CORBA_local_object_instantiation_count_;
}


RefCountLocalObject::~RefCountLocalObject()
{
#ifdef _DEBUG
	CORBA_local_object_set.erase(this);
#else
	--CORBA_local_object_count_;
#endif

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
	QedoLock lock (&mutex_);
	++ref_count_;
}


void
RefCountLocalObject::_remove_ref()
{
	bool remove = false;
	{
		QedoLock lock (&mutex_);
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
#ifdef _DEBUG
	QedoLock lock(&CORBA_object_mutex_);
	CORBA_object_set.insert(this);
#else
	++CORBA_object_count_;
#endif
	++GlobalObjectManagement::CORBA_object_instantiation_count_;
}


CreateDestructCORBAObjectCounter::~CreateDestructCORBAObjectCounter()
{
#ifdef _DEBUG
	QedoLock lock(&CORBA_object_mutex_);
	CORBA_object_set.erase(this);
#else
	--CORBA_object_count_;
#endif
}

#ifdef _DEBUG
#if defined(HAVE_CXXABI_H) && defined(HAVE___CXA_DEMANGLE) && defined(__GNUC__)
namespace __cxxabiv1 {
	class __class_type_info;
};
#include <cxxabi.h>
static void
demangle(const char* name)
{
	int status=0;
	char * ret;

	if(ret = __cxxabiv1::__cxa_demangle(name,0,0,&status))
	{
		DEBUG_OUT(ret);
		free(ret);
	}
	else
	{
		DEBUG_OUT2("__cxa_demangle returns ",status);
	}
}
#else
static void
demangle(const char* name)
{
	DEBUG_OUT(name);
}
#endif
#endif

void
GlobalObjectManagement::report()
{
	DEBUG_OUT  ("#######################################################");

#ifdef _DEBUG
	if (native_object_set.size()
		|| CORBA_object_set.size()
		|| CORBA_local_object_set.size())
	{
		DEBUG_OUT  ("# MEMORY LEAKS DETECTED!!!");
		if (native_object_set.size()) {
			std::set<RefCountBase*>::iterator i = native_object_set.begin();
			DEBUG_OUT("still running native objects :");
			for(;i != native_object_set.end();i++)
			{
				demangle(typeid(**i).name());
			}
		}
		if (CORBA_object_set.size()) {
			std::set<CreateDestructCORBAObjectCounter*>::iterator i = CORBA_object_set.begin();
			DEBUG_OUT("still running CORBA objects :");
			for(;i != CORBA_object_set.end();i++)
			{
				demangle(typeid(**i).name());
			}
		}
		if (CORBA_local_object_set.size()) {
			std::set<RefCountLocalObject*>::iterator i = CORBA_local_object_set.begin();
			DEBUG_OUT("still running CORBA local objects :");
			for(;i != CORBA_local_object_set.end();i++)
			{
				demangle(typeid(**i).name());
			}
		}
	}
	else
	{
		DEBUG_OUT  ("# All objects destroyed");
	}
#else
	if (native_object_count_
		|| CORBA_object_count_
		|| CORBA_local_object_count_)
	{
		DEBUG_OUT  ("# MEMORY LEAKS DETECTED!!!");
		if (native_object_count_)
		{
			DEBUG_OUT2 ("# Number of still running native objects      : ", native_object_count_);
		}
		if (CORBA_object_count_)
		{
			DEBUG_OUT2 ("# Number of still running CORBA objects        : ", CORBA_object_count_);
		}
		if (CORBA_local_object_count_)
		{
			DEBUG_OUT2 ("# Number of still running CORBA local objects : ", CORBA_local_object_count_);
		}
	}
	else
	{
		DEBUG_OUT  ("# All objects destroyed");
	}
#endif
	DEBUG_OUT2 ("# Number of constructed native objects        : ", Qedo::GlobalObjectManagement::native_object_instantiation_count_ );
	DEBUG_OUT2 ("# Number of constructed CORBA objects         : ", Qedo::GlobalObjectManagement::CORBA_object_instantiation_count_ );
	DEBUG_OUT2 ("# Number of constructed CORBA local objects   : ", Qedo::GlobalObjectManagement::CORBA_local_object_instantiation_count_ );
	DEBUG_OUT  ("#######################################################");


}

//
// cleaner object for a ValueFactory
// 
ValueFactoryCleaner::ValueFactoryCleaner (class CORBA::ValueFactoryBase* factory, char* repid)
: factory_ (factory), is_registered_(false), repid_(repid)
{
	int dummy = 0;
    CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);

	// check whether there is already a factory
	if (orb->lookup_value_factory( repid ))
	{
		DEBUG_OUT3("..... factory for ", repid, " already registered");
	}
	else
	{
		DEBUG_OUT2( "..... register factory for ", repid );
		orb->register_value_factory( repid, factory_ );
		is_registered_ = true;
	}
}


ValueFactoryCleaner::~ValueFactoryCleaner()
{
	if (is_registered_)
	{
		int dummy = 0;
		CORBA::ORB_var orb = CORBA::ORB_init (dummy, 0);
		DEBUG_OUT2( "..... unregister factory for ", repid_ );
		orb->unregister_value_factory( repid_.c_str() );
	}
	DEBUG_OUT ("ValueFactoryCleaner: Destructor called");
	factory_->_remove_ref();
}


} // namespace Qedo
