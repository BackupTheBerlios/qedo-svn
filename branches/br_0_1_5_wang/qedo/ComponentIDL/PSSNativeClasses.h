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


namespace Qedo
{
	class StorageObjectImpl;
	class StorageHomeBaseImpl;
	class SessionImpl;
	class SessionPoolImpl;
}

#ifdef MICO_ORB
namespace CosPersistentState
#endif
#ifdef ORBACUS_ORB
namespace OBNative_CosPersistentState
#endif
{

class StorageObjectBase_pre : virtual public CORBA::Object
{
	//protected:
	public:
		virtual ~StorageObjectBase_pre() {}
};

template <class T>
class Factory
{
	public:
		virtual T* create() = 0;
		virtual void _add_ref() = 0;
		virtual void _remove_ref() = 0;
		virtual ~Factory() {};
};

typedef Factory<Qedo::StorageObjectImpl> StorageObjectFactory_pre;
typedef Factory<Qedo::StorageHomeBaseImpl> StorageHomeFactory_pre;
typedef Factory<Qedo::SessionImpl> SessionFactory_pre;
typedef Factory<Qedo::SessionPoolImpl> SessionPoolFactory_pre;

#ifdef ORBACUS_ORB
typedef StorageObjectBase_pre* StorageObjectBase;
typedef StorageObjectFactory_pre* StorageObjectFactory;
typedef StorageHomeFactory_pre* StorageHomeFactory;
typedef SessionFactory_pre* SessionFactory;
typedef SessionPoolFactory_pre* SessionPoolFactory;
#endif

#ifdef MICO_ORB
typedef StorageObjectBase_pre* MICO_Native_CosPersistentState_StorageObjectBase;
typedef StorageObjectFactory_pre* MICO_Native_CosPersistentState_StorageObjectFactory;
typedef StorageHomeFactory_pre* MICO_Native_CosPersistentState_StorageHomeFactory;
typedef SessionFactory_pre* MICO_Native_CosPersistentState_SessionFactory;
typedef SessionPoolFactory_pre* MICO_Native_CosPersistentState_SessionPoolFactory;
#endif

};

#endif
