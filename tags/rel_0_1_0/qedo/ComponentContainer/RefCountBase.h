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

#include <OB/CORBA.h>

#include "Util.h"

namespace Qedo {

//
// This is a simple refounted mix-in class that can be used for all classes that
// have no CORBA-defined refcount mix-ins
//
class CONTAINERDLL_API RefCountBase
{
private:
	unsigned long ref_count_;

public:
	RefCountBase();
	virtual ~RefCountBase();

	void _add_ref();
	void _remove_ref();
	unsigned long _get_refcount();
};

class CONTAINERDLL_API RefCountLocalObject : public virtual CORBA::LocalObject
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

} // namespace Qedo

#endif

