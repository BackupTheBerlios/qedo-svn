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

#ifndef __SESSION_HOME_SERVANT_H__
#define __SESSION_HOME_SERVANT_H__

#include "CCMHomeServant.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * the servant for session homes
 */
class CONTAINERDLL_API SessionHomeServant : public CCMHomeServant
{
private:
	/**
	 * indicate removal
	 * \param executor_locator The executor locator of the component instance to be removed.
	 */
	void before_remove_component (Components::ExecutorLocator_ptr executor_locator);

	/**
	 * finalize the component incarnation
	 * \param exec_loc The executor locator of the component instance to be incarnated.
	 */
	void do_finalize_component_incarnation (Components::ExecutorLocator_ptr exec_loc);

public:
	/**
	 * constructor
	 */
	SessionHomeServant ();

	/**
	 * copy constructor
	 */
	SessionHomeServant (const SessionHomeServant&);

	/**
	 * assignment operator
	 */
	SessionHomeServant& operator= (const SessionHomeServant&);

	/**
	 * destructor
	 */
	virtual ~SessionHomeServant();
};

/** @} */

} // namespace Qedo

#endif

