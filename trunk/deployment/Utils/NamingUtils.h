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

#ifndef NAMINGUTILS_HH
#define NAMINGUTILS_HH

#include <OB\CORBA.h>
#include <OB\CosNaming.h>
//#include "Deployment_dpe.hh"


class NamingUtil
{
	static void NamingUtil::remove (const CosNaming::BindingList &bl, CosNaming::NamingContext_ptr context);
public:
	static void remove_context ( CosNaming::NamingContext_ptr context );
	static CORBA::Object_ptr resolve_name (const CosNaming::Name, CosNaming::NamingContext_ptr, short);
	static bool bind_name(const CosNaming::Name, CORBA::Object_ptr , CosNaming::NamingContext_ptr , short  );
	static CosNaming::NamingContext_ptr  bind_new_ctxt (const CosNaming::Name name_, CosNaming::NamingContext_ptr ns, short i, bool& already_bound );
	static void rebind_name(const CosNaming::Name, CORBA::Object_ptr obj_nm_, CosNaming::NamingContext_ptr, short );
	static void unbind_name(const CosNaming::Name name_, CosNaming::NamingContext_ptr ns, short i );
	static CosNaming::NamingContext_ptr rebind_ctxt (const CosNaming::Name name_, CosNaming::NamingContext_ptr ns, short i);



};


#endif