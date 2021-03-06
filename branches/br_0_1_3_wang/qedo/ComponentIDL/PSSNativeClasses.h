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
#ifndef __PSSNATIVECLASSES_H__
#define __PSSNATIVECLASSES_H__

#include "RefCountBase.h"


namespace Qedo
{
	class StorageObjectImpl;
	class StorageHomeBaseImpl;
	class SessioImpl;
	class SessionPoolImpl;
}

namespace OBNative_CosPersistentState
{

class StorageObjectBase_pre
{
	protected:
		virtual ~StorageObjectBase_pre() {}
};

template <class T>
class Factory : public virtual Qedo::RefCountLocalObject
{
	public:
		//virtual T* create() throw (CORBA::SystemException) = 0;
		virtual T* create() throw (CORBA::SystemException)
		{
			return new T;
		};
		virtual void _add_ref() 
		{
			Qedo::RefCountLocalObject::_add_ref();
		};
		virtual void _remove_ref()
		{
			Qedo::RefCountLocalObject::_remove_ref();
		};
		virtual ~Factory()
		{
			Qedo::RefCountLocalObject::~RefCountLocalObject();
		};
};

typedef Factory<Qedo::StorageObjectImpl> StorageObjectFactory_pre;
typedef Factory<Qedo::StorageHomeBaseImpl> StorageHomeFactory_pre;
typedef Factory<Qedo::SessioImpl> SessionFactory_pre;
typedef Factory<Qedo::SessionPoolImpl> SessionPoolFactory_pre;

typedef StorageObjectBase_pre* StorageObjectBase;
typedef StorageObjectFactory_pre* StorageObjectFactory;
typedef StorageHomeFactory_pre* StorageHomeFactory;
typedef SessionFactory_pre* SessionFactory;
typedef SessionPoolFactory_pre* SessionPoolFactory;

};

#endif
