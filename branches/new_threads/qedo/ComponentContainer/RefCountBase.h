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

#ifndef __REFCOUNT_BASE_H__
#define __REFCOUNT_BASE_H__

#include <CORBA.h>
#include "Synchronisation.h"
#include "Util.h"


namespace Qedo {


class CONTAINERDLL_API GlobalObjectManagement 
{
public:
	static CORBA::Long native_object_count_;
	static CORBA::Long CORBA_object_count_;
	static CORBA::Long CORBA_local_object_count_;
	static CORBA::Long native_object_instantiation_count_;
	static CORBA::Long CORBA_object_instantiation_count_;
	static CORBA::Long CORBA_local_object_instantiation_count_;
};


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * This is a simple refounted mix-in class that can be used for all classes that
 * have no CORBA-defined refcount mix-ins
 */
class CONTAINERDLL_API RefCountBase
{
private:
	/** the reference counter */
	CORBA::Long ref_count_;

	/** the mutex for ref_count_ manipulation */
	qedo_mutex mutex_;

public:
	/**
	 * constructor
	 */
	RefCountBase();

	/**
	 * destructor
	 */
	virtual ~RefCountBase();

	/**
	 * increment the reference counter
	 */
	void _add_ref();

	/**
	 * decrement the reference counter
	 */
	void _remove_ref();

	/**
	 * provide the reference counter
	 * \return The reference counter.
	 */
	unsigned long _get_refcount();
};


/**
 * reference count class for local objects (for MICO this class only provides the creation/destruction count)
 */
class CONTAINERDLL_API RefCountLocalObject : public virtual CORBA::LocalObject
{

#ifndef MICO_ORB
private:
	/** the reference counter */
	CORBA::Long ref_count_;

	/** the mutex for ref_count_ manipulation */
	qedo_mutex mutex_;
#endif

public:
	/**
	 * constructor
	 */
	RefCountLocalObject();

	/**
	 * destructor
	 */
	virtual ~RefCountLocalObject();

#ifndef MICO_ORB
	/**
	 * increment the reference counter
	 */
	void _add_ref();

	/**
	 * decrement the reference counter
	 */
	void _remove_ref();

	/**
	 * provide the reference counter
	 */
	unsigned long _get_refcount();
#endif
};


/**
 * creation/destruction count class for CORBA objects
 */
class CONTAINERDLL_API CreateDestructCORBAObjectCounter
{
public:
	/**
	 * constructor
	 */
	CreateDestructCORBAObjectCounter();

	/**
	 * destructor
	 */
	virtual ~CreateDestructCORBAObjectCounter();
};

/** @} */

} // namespace Qedo

#endif
