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

#ifndef __STANDARD_CONFIGURATOR_H__
#define __STANDARD_CONFIGURATOR_H__


#include <OB/CORBA.h>
#include "Components_skel.h"
#include "Valuetypes.h"
#include "Output.h"


namespace Qedo {


/**
 *
 */
class StandardConfiguratorImpl : public virtual POA_Components::StandardConfigurator
{
private:
    ::Components::ConfigValues config_;

public:
    StandardConfiguratorImpl();
	virtual ~StandardConfiguratorImpl();

    //
    // IDL:omg.org/Components/Configurator/configure:1.0
    //
    void configure( ::Components::CCMObject_ptr comp )
		throw( Components::WrongComponentType );
	
	//
    // IDL:omg.org/Components/StandardConfigurator/set_configuration:1.0
    //
    void set_configuration( const ::Components::ConfigValues& descr )
	   throw (CORBA::SystemException);
};


}

#endif

