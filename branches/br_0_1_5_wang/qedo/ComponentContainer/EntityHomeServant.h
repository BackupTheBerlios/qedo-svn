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

#ifndef __ENTITY_HOME_SERVANT_H__
#define __ENTITY_HOME_SERVANT_H__

//#include "HomeServantBase.h"
#include "CCMHomeServant.h"
#include "Connector.h"
#include "Util.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * home servant for entity components
 */
class CONTAINERDLL_API EntityHomeServant : public CCMHomeServant
	//:public HomeServantBase
{
private:
	/**
	 * indicate removal
	 * \param executor_locator The executor locator of the component instance to be removed.
	 */
	void before_remove_component (Components::ExecutorLocator_ptr exec_loc);

	/**
	 * finalize the component incarnation
	 * \param exec_loc The executor locator of the component instance to be incarnated.
	 */
	void do_finalize_component_incarnation (Components::ExecutorLocator_ptr exec_loc);

public:
	/**
	 * constructor
	 */
	EntityHomeServant();

	/**
	 * copy constructor
	 */
	EntityHomeServant (const EntityHomeServant&);

	/**
	 * assignment operator
	 */
	EntityHomeServant& operator= (const EntityHomeServant&);

	/**
	 * destructor
	 */
	~EntityHomeServant();
	
	virtual void get_table_info(std::map<std::string, std::string>& mTables) = 0;

	virtual void init_datastore(const Connector_ptr pConn, const Sessio_ptr pSession) = 0;

};

/** @} */

} // namespace Qedo

#endif

