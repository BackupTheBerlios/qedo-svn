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


#include "NameServiceBase.h"
#include "qedoutil.h"
#include "Output.h"
#include "ConfigurationReader.h"
#include <iostream>


static char rcsid[] UNUSED = "$Id: NameServiceBase.cpp,v 1.12 2003/10/23 09:54:04 neubauer Exp $";


namespace Qedo {


NameServiceBase::NameServiceBase()
{
}


NameServiceBase::~NameServiceBase()
{
}


bool
NameServiceBase::initNameService(CORBA::ORB_ptr orb)
{
    //
	// try to get naming service from config values
	//
    CORBA::Object_var obj;
	std::string ns = Qedo::ConfigurationReader::instance()->lookup_config_value( "/General/NameService" );
	if( !ns.empty() )
	{
		try
		{
			obj = orb->string_to_object( ns.c_str() );
		}
		catch(...)
		{
			NORMAL_ERR2( "NameServiceBase: can't resolve NameService ", ns );
			return false;
		}

		NORMAL_OUT2( "NameServiceBase: NameService is ", ns );
	}
	//
	// try to get naming service from orb
	//
	else
	{
		try
		{
			obj = orb->resolve_initial_references( "NameService" );
		}
		catch (const CORBA::ORB::InvalidName&)
		{
			NORMAL_ERR( "NameServiceBase: can't resolve NameService" );
			return false;
		}

		if (CORBA::is_nil(obj.in()))
		{
			NORMAL_ERR( "NameServiceBase: NameService is a nil object reference" );
			return false;
		}
	}

	try
	{
		nameService_ = CosNaming::NamingContext::_narrow( obj.in() );
	}
	catch (const CORBA::Exception&)
	{
		NORMAL_ERR( "NameServiceBase: NameService is not running" );
		return false;
	}

    if( CORBA::is_nil(nameService_.in()) )
    {
        NORMAL_ERR( "NameService is not a NamingContext object reference" );
		return false;
    }

    return true;
}

	
bool
NameServiceBase::registerName(std::string name, CORBA::Object_ptr obj, bool rebind)
{
    if (name.empty())
    {
        return false;
    }
    
    // extract name without contexts
    std::string pure_name = name;
    std::string contexts = "";
    std::string::size_type delimiter_pos = name.find_last_of("/");
    if (delimiter_pos != std::string::npos)
    {
        pure_name = pure_name.replace(0, delimiter_pos + 1, "");
        contexts = name.replace(delimiter_pos, std::string::npos, "");
    }

    CosNaming::Name aName;
    aName.length(1);
    aName[0].id = CORBA::string_dup(pure_name.c_str());
    aName[0].kind = CORBA::string_dup("");

    // make sure each context is bound
    CosNaming::NamingContext_var context = nameService_;
    while (contexts.length())
    {
        std::string ctx = contexts;
        delimiter_pos = contexts.find_first_of("/");
        if (delimiter_pos != std::string::npos)
        {
            ctx = ctx.replace(delimiter_pos, std::string::npos, "");
            contexts = contexts.replace(0, delimiter_pos + 1, "");
        }
        else
        {
            contexts = "";
        }

	    CosNaming::Name contextName;
        contextName.length(1);
        contextName[0].id = CORBA::string_dup(ctx.c_str());
        contextName[0].kind = CORBA::string_dup("");

        try
        {
            context = context->bind_new_context(contextName);
	    }
	    catch (const CosNaming::NamingContext::AlreadyBound&)
        {
            try
            {
		        // already bound -> take it
                CORBA::Object_var dummy;
                context = CosNaming::NamingContext::_narrow(dummy = context->resolve(contextName));
            }
            catch (...)
            {
                std::cerr << ctx << " is probably no context?" << std::endl;
                return false;
            }
        }
	    catch (const CosNaming::NamingContext::NotFound&)
        {
            std::cerr << "Got a `NotFound' exception : " << std::endl;
    		return false;
        }
        catch (const CosNaming::NamingContext::CannotProceed&)
        {
            std::cerr << "Got a `CannotProceed' exception : " << std::endl;
    		return false;
        }
        catch (const CosNaming::NamingContext::InvalidName&)
        {
            std::cerr << "Got a `InvalidName' exception : " << std::endl;
		    return false;
        }
    }

    //  bind the name
    try
	{
        context->bind(aName, obj);
	}
	catch(const CosNaming::NamingContext::AlreadyBound&)
    {
		// rebind the name if intended
        if (rebind)
        {
		    try
		    {
			    context->rebind(aName, obj);
		    }
		    catch (const CosNaming::NamingContext::NotFound&)
	        {
	            std::cerr << "Got a `NotFound' exception : " << std::endl;
			    return false;
	        }
	        catch (const CosNaming::NamingContext::CannotProceed&)
		    {
		        std::cerr << "Got a `CannotProceed' exception : " << std::endl;
			    return false;
		    }
		    catch (const CosNaming::NamingContext::InvalidName&)
	        {
			    std::cerr << "Got a `InvalidName' exception : " << std::endl;
			    return false;
		    }
        }
        else
        {
            std::cerr << "Got a `InvalidName' exception" << std::endl;
            return false;
        }
    }
	catch (const CosNaming::NamingContext::NotFound&)
    {
        std::cerr << "Got a `NotFound' exception : " << std::endl;
		return false;
    }
    catch (const CosNaming::NamingContext::CannotProceed&)
    {
        std::cerr << "Got a `CannotProceed' exception : " << std::endl;
		return false;
    }
    catch (const CosNaming::NamingContext::InvalidName&)
    {
        std::cerr << "Got a `InvalidName' exception : " << std::endl;
		return false;
    }

    return true;
}


CORBA::Object_ptr
NameServiceBase::resolveName(std::string name)
{
    if (name.empty())
    {
        return 0;
    }

    // build a Name
    CosNaming::Name aName;
    std::string binding = name;
    std::string::size_type delimiter_pos;
    int index = 0;

    while (binding.length())
    {
        aName.length(index + 1);
        delimiter_pos = binding.find_first_of("/");
        if (delimiter_pos != std::string::npos)
        {
            aName[index].id = CORBA::string_dup(binding.substr(0, delimiter_pos).c_str());
            aName[index].kind = CORBA::string_dup("");
            binding = binding.replace(0, delimiter_pos + 1, "");
        }
        else
        {
            aName[index].id = CORBA::string_dup(binding.c_str());
            aName[index].kind = CORBA::string_dup("");
            binding = "";
        }

        index++;
    }

    // resolve name
    CORBA::Object_var obj;
    try
	{
	    obj = nameService_->resolve(aName);
	}
	catch(const CosNaming::NamingContext::NotFound&)
	{
		std::cerr << "NameServiceBase: Name binding not found : " << name << std::endl;
		return 0;
	}
	catch(const CosNaming::NamingContext::CannotProceed&)
	{
		std::cerr << "Got a `CannotProceed' exception : " << std::endl;
		return 0;
	}
	catch(const CosNaming::NamingContext::InvalidName&)
	{
	    std::cerr << "Got a `InvalidName' exception : " << std::endl;
		return 0;
	}

    if (CORBA::is_nil(obj))
    {
        return 0;
    }

    return obj._retn();
}

}

