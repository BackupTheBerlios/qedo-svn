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

#include <iostream.h>
#include "NamingUtils.h"

void NamingUtil::remove_context ( CosNaming::NamingContext_ptr context )
{
	try
	{
	if ( CORBA::is_nil ( context ) )
		return;
	
	CosNaming::BindingIterator_var it;
	CosNaming::BindingList_var bl;
	const CORBA::ULong CHUCK = 100;

	try
	{
		context -> list (CHUCK, bl, it);
	}
	catch (...)
	{
		return;
	}

	NamingUtil::remove ( bl, context );

	if (!CORBA::is_nil(it)) 
	{
		while (it->next_n(CHUCK, bl))
			NamingUtil::remove (bl, context );
		it->destroy();
	}

	context->destroy();
	}
	catch(...)
	{
		std::cerr<<"destroy naming context failed!" <<"\n";
	}

}

void NamingUtil::remove(const CosNaming::BindingList &bl, CosNaming::NamingContext_ptr context)
{
	for (CORBA::ULong i = 0; i < bl.length(); i++)
	{
		CORBA::Object_var obj_ = context->resolve ( bl[i].binding_name );
		if (bl[i].binding_type == CosNaming::ncontext)
		{
			CosNaming::NamingContext_var ct_ = CosNaming::NamingContext::_narrow ( obj_ );
			remove_context ( ct_ );
		}
		context->unbind ( bl[i].binding_name );
	}
}

CORBA::Object_ptr NamingUtil::resolve_name(const CosNaming::Name name_, CosNaming::NamingContext_ptr ns_, short i )
{
	CORBA::Object_var obj_nm_;
	try
	{
		obj_nm_	= ns_->resolve(name_);
		return ( CORBA::Object::_duplicate(obj_nm_) );
	}
	catch (CosNaming::NamingContext::NotFound& exp)
	{
		cerr << "The Name: " << name_[i].id << " is not found in the Name Service! \n";
		throw 0;
	}
	catch(CosNaming::NamingContext::CannotProceed& exp) 
	{
		std::cerr << "Cannot proceed: " <<name_[i].id << '\n';
		throw 0;
	}
	catch(CosNaming::NamingContext::InvalidName& exp)
	{
		std::cerr << "Invalid name: " << name_[i].id << '\n' ;
		throw 0;
	}
	catch(CORBA::Exception& exp)
	{
		std::cerr << "Resolve failed: " << exp << '\n' ;
		throw 0;
	}
	if (CORBA::is_nil(obj_nm_)) 
	{
		cerr << "Nil Reference for " << name_[i].id << endl;
		throw 0;
	}
	
}

bool NamingUtil::bind_name(const CosNaming::Name name_, CORBA::Object_ptr obj_nm_, CosNaming::NamingContext_ptr ns_, short i )
{

	try
	{
		ns_->bind(name_, obj_nm_);
		return false;
	}
	catch (CosNaming::NamingContext::NotFound& exp)
	{
		cerr << "The Name: " << name_[i].id << " is not found in the Name Service! \n";
		throw 0;
	}
	catch(CosNaming::NamingContext::CannotProceed& exp) 
	{
		std::cerr << "Cannot proceed: " <<name_[i].id << '\n';
		throw 0;
	}
	catch(CosNaming::NamingContext::InvalidName& exp)
	{
		std::cerr << "Invalid name: " << name_[i].id << '\n' ;
		throw 0;
	}
	catch (CosNaming::NamingContext::AlreadyBound& exp) 
	{
		cerr << "The Name: " << name_[i].id << " is already bound! \n";
		return true;
	}
	catch(CORBA::Exception& exp)
	{
		std::cerr << "Resolve failed: " << exp << '\n' ;
		throw 0;
	}
	if (CORBA::is_nil(obj_nm_)) 
	{
		cerr << "Nil Reference for " << name_[i].id << endl;
		throw 0;
	}
	
}

CosNaming::NamingContext_ptr  NamingUtil::bind_new_ctxt (const CosNaming::Name name_, CosNaming::NamingContext_ptr ns, short i,  bool& already_bound )
{
	CosNaming::NamingContext_var new_ns_ctxt_;
	try
	{
		 new_ns_ctxt_ =  ns->bind_new_context(name_);
		 return ( CosNaming::NamingContext::_duplicate(new_ns_ctxt_) );
		 already_bound = false;
	}
	catch (CosNaming::NamingContext::NotFound& exp)
	{
		cerr << "The Name: " << name_[i].id << " is not found ! \n";
		throw 0;
	}
	catch(CosNaming::NamingContext::CannotProceed& exp) 
	{
		std::cerr << "Cannot proceed: " <<name_[i].id << '\n';
		throw 0;
	}
	catch(CosNaming::NamingContext::InvalidName& exp)
	{
		std::cerr << "Invalid name: " << name_[i].id << '\n' ;
		throw 0;
	}
	catch (CosNaming::NamingContext::AlreadyBound& exp) 
	{
		cerr << "The Name: " << name_[i].id << " is already bound! \n";
		already_bound = true;
		return 0;
	}
	catch(CORBA::Exception& exp)
	{
		std::cerr << "Bind New Context failed: " << exp << '\n' ;
		throw 0;
	}
}

CosNaming::NamingContext_ptr NamingUtil::rebind_ctxt (const CosNaming::Name name_, CosNaming::NamingContext_ptr ns, short i)
{
	CosNaming::NamingContext_var new_;
	new_ = ns -> new_context();
	try 
	{
		ns->rebind_context(name_, new_);
		return ( CosNaming::NamingContext::_duplicate(new_) );
	}
	catch (CosNaming::NamingContext::NotFound& exp)
	{
		cerr << "The Name: " << name_[i].id << " is not found ! \n";
		throw 0;
	}
	catch(CosNaming::NamingContext::CannotProceed& exp) 
	{
		std::cerr << "Cannot proceed: " <<name_[i].id << '\n';
		throw 0;
	}
	catch(CosNaming::NamingContext::InvalidName& exp)
	{
		std::cerr << "Invalid name: " << name_[i].id << '\n' ;
			throw 0;
		}
}

void NamingUtil::unbind_name(const CosNaming::Name name_, CosNaming::NamingContext_ptr ns, short i )
{
	try 
	{
		ns->unbind(name_);
	}
	catch (CosNaming::NamingContext::NotFound& exp)
	{
		cerr << "The Name: " << name_[i].id << " is not found ! \n";
		throw 0;
	}
	catch(CosNaming::NamingContext::CannotProceed& exp) 
	{
		std::cerr << "Cannot proceed: " <<name_[i].id << '\n';
		throw 0;
	}
	catch(CosNaming::NamingContext::InvalidName& exp)
	{
		std::cerr << "Invalid name: " << name_[i].id << '\n' ;
		throw 0;
	}
}

void NamingUtil::rebind_name(const CosNaming::Name name_, CORBA::Object_ptr obj_nm_, CosNaming::NamingContext_ptr ns, short i)
{
	try
	{
		ns->rebind(name_, obj_nm_);
	}
	catch (CosNaming::NamingContext::NotFound& exp)
	{
		cerr << "The Name: " << name_[i].id << " is not found in the Name Service! \n";
		throw 0;
	}
	catch(CosNaming::NamingContext::CannotProceed& exp) 
	{
		std::cerr << "Cannot proceed: " <<name_[i].id << '\n';
		throw 0;
	}
	catch(CosNaming::NamingContext::InvalidName& exp)
	{
		std::cerr << "Invalid name: " << name_[i].id << '\n' ;
		throw 0;
	}
	catch(CORBA::Exception& exp)
	{
		std::cerr << "Resolve failed: " << exp << '\n' ;
		throw 0;
	}
	if (CORBA::is_nil(obj_nm_)) 
	{
		cerr << "Nil Reference for " << name_[i].id << endl;
		throw 0;
	}
}

