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

static char rcsid[] = "$Id: NameServiceBase.cpp,v 1.3 2002/12/03 07:57:46 stoinski Exp $";


#include "NameServiceBase.h"


namespace Qedo {


/**
 *
 */
NameServiceBase::NameServiceBase()
{
}


/**
 *
 */
NameServiceBase::~NameServiceBase()
{
}


/**
 *
 */
bool
NameServiceBase::initNameService(CORBA::ORB_ptr orb)
{
    // get naming service
    CORBA::Object_var obj;

    try
    {
        obj = orb->resolve_initial_references("NameService");
    }
    catch (const CORBA::ORB::InvalidName&)
    {
        std::cerr << "Can't resolve NameService" << std::endl;
		return false;
    }

    if (CORBA::is_nil(obj.in()))
    {
        std::cerr << "NameService is a nil object reference" << std::endl;
		return false;
    }

	try
	{
		nameService_ = CosNaming::NamingContext::_narrow(obj.in());
	}
	catch (const CORBA::Exception&)
	{
		std::cerr << "NameService is not running" << std::endl;
		return false;
	}

    if (CORBA::is_nil(nameService_.in()))
    {
        std::cerr << "NameService is not a NamingContext object reference" << std::endl;
		return false;
    }

    return true;
}

	
/**
 *
 */
bool
NameServiceBase::registerName(std::string name, CORBA::Object_ptr obj, bool rebind)
{
    if (name == "")
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
    while (contexts != "")
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
	    catch (const CosNaming::NamingContext::NotFound& ex)
        {
            std::cerr << "Got a `NotFound' exception : " << ex << std::endl;
    		return false;
        }
        catch (const CosNaming::NamingContext::CannotProceed& ex)
        {
            std::cerr << "Got a `CannotProceed' exception : " << ex << std::endl;
    		return false;
        }
        catch (const CosNaming::NamingContext::InvalidName& ex)
        {
            std::cerr << "Got a `InvalidName' exception : " << ex << std::endl;
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
		    catch (const CosNaming::NamingContext::NotFound& ex)
	        {
	            std::cerr << "Got a `NotFound' exception : " << ex << std::endl;
			    return false;
	        }
	        catch (const CosNaming::NamingContext::CannotProceed& ex)
		    {
		        std::cerr << "Got a `CannotProceed' exception : " << ex << std::endl;
			    return false;
		    }
		    catch (const CosNaming::NamingContext::InvalidName& ex)
	        {
			    std::cerr << "Got a `InvalidName' exception : " << ex << std::endl;
			    return false;
		    }
        }
        else
        {
            std::cerr << "Got a `InvalidName' exception" << std::endl;
            return false;
        }
    }
	catch (const CosNaming::NamingContext::NotFound& ex)
    {
        std::cerr << "Got a `NotFound' exception : " << ex << std::endl;
		return false;
    }
    catch (const CosNaming::NamingContext::CannotProceed& ex)
    {
        std::cerr << "Got a `CannotProceed' exception : " << ex << std::endl;
		return false;
    }
    catch (const CosNaming::NamingContext::InvalidName& ex)
    {
        std::cerr << "Got a `InvalidName' exception : " << ex << std::endl;
		return false;
    }

    return true;
}


/**
 *
 */
CORBA::Object_ptr
NameServiceBase::resolveName(std::string name)
{
    if (name == "")
    {
        return 0;
    }

    // build a Name
    CosNaming::Name aName;
    std::string binding = name;
    std::string::size_type delimiter_pos;
    int index = 0;

    while (binding != "")
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
		std::cerr << "\n name binding not found : " << name << std::endl;
		return 0;
	}
	catch(const CosNaming::NamingContext::CannotProceed& ex)
	{
		std::cerr << "Got a `CannotProceed' exception : " << ex << std::endl;
		return 0;
	}
	catch( const CosNaming::NamingContext::InvalidName& ex )
	{
	    std::cerr << "Got a `InvalidName' exception : " << ex << std::endl;
		return 0;
	}

    if (CORBA::is_nil(obj))
    {
        return 0;
    }

    return obj._retn();
}

}