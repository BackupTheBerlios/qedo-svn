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

#ifndef __INTERNAL_CONFIGURATION_H__
#define __INTERNAL_CONFIGURATION_H__

#include <CORBA.h>
#include <QedoComponents_skel.h>
#include "RefCountBase.h"
#include "CCMContext.h"
#include <string>


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * implementation of IDL:Qedo_Components/InternalConfiguration
 */
class CONTAINERDLL_API InternalConfiguration : public virtual ConfigurationService::InternalConfiguration,
											   public virtual RefCountLocalObject
{
private:

	/** the context of the component */
	CCMContext*								ctx_;

public:
	/**
	 * constructor
	 */
	InternalConfiguration(CCMContext* ctx);

	/**
	 * destructor
	 */
	~InternalConfiguration();

	/**
	 * implements IDL:Qedo_Components/InternalConfiguration/get_value:1.0
	 */
    virtual char* get_value( const char* name )
		throw (ConfigurationService::UnknownConfiguration, CORBA::SystemException);
};

/** @} */

} // namespace Qedo

#endif

