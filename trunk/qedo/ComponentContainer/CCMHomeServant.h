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

#ifndef __CCM_HOME_SERVANT_H__
#define __CCM_HOME_SERVANT_H__

#include <CORBA.h>
#include "QedoComponents_skel.h"
#include "HomeServantBase.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * servant for CCMHome
 */
class CONTAINERDLL_API CCMHomeServant : public virtual HomeServantBase,
										public virtual POA_Components::CCMHome
{
public:
	/**
	 * constructor
	 */
	CCMHomeServant();

	/**
	 * copy constructor
	 */
	CCMHomeServant (const CCMHomeServant&);

	/**
	 * assignment operator
	 */
	CCMHomeServant& operator= (const CCMHomeServant&);

	/**
	 * destructor
	 */
	~CCMHomeServant();

	/**
	 * implements IDL:omg.org/Components/CCMHome/get_component_def:1.0
	 * (not yet implemented)
	 * \return The interface repository object for the component.
	 */
    CORBA::IRObject_ptr get_component_def()
        throw(CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMHome/get_home_def:1.0
	 * (not yet implemented)
	 * \return The interface repository object for the home.
	 */
    CORBA::IRObject_ptr get_home_def()
        throw(CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Components/CCMHome/remove_component:1.0
	 * removes the given component
	 * \param comp The component to be removed.
	 */
    void remove_component(Components::CCMObject_ptr comp)
        throw(Components::RemoveFailure, CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Qedo_Components/CCMHome/get_instances:1.0
	 * \return The list of all components of this home.
	 */
	Components::CCMObjects* get_instances()
		throw	(CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Qedo_Components/CCMHome/get_home_rep_id:1.0
	 * \return The repository id of this home.
	 */
	char* get_home_rep_id()
		throw	(CORBA::SystemException);

	/**
	 * implements IDL:omg.org/Qedo_Components/CCMHome/get_component_rep_id:1.0
	 * \return The repository id of this home.
	 */
	char* get_component_rep_id()
		throw	(CORBA::SystemException);

};

/** @} */

} //namespace Qedo

#endif

