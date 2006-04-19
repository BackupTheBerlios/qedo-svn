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

#ifndef __FACET_PORT_H__
#define __FACET_PORT_H__

#include <CORBA.h>
#include <Components.h>
#include "PortBase.h"
#include "Valuetypes.h"
#include "Util.h"
#include <string>
#include <vector>


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * entry in the CCM object executor for a facet
 */
class FacetPort : public PortBase
{
private:
	/** the facet */
	CORBA::Object_var facet_ref_;

public:
	/**
	 * constructor
	 * \param name The name of the facet.
	 * \param type_id The interface repository id of the facets interface.
	 * \param ref The object reference of the facet.
	 */
	FacetPort (const char* name, const char* type_id, const CORBA::Object_ptr ref);

	/**
	 * constructor
	 */
	FacetPort();

	/**
	 * copy constructor
	 */
	FacetPort (const FacetPort&);

	/**
	 * desctructor
	 */
    ~FacetPort();

	/**
	 * comparison
	 */
	bool operator < (const FacetPort&) const {return true;}

	/**
	 * comparison
	 */
	bool operator == (const FacetPort&) const {return true;}

	/**
	 * provides the description of the facet
	 * \return The description of the facet.
	 */
    Components::FacetDescription* facet_description() const;

	/**
	 * provides the facet
	 * \return The facet.
	 */
CONTAINERDLL_API    const CORBA::Object_ptr facet_ref() const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<FacetPort>;
typedef std::vector<FacetPort> FacetVector;

/** @} */

} // namespace Qedo

#endif

