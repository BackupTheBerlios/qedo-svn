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

//
// Entry in the CCM object executor for a facet
//
class FacetPort : public PortBase
{
private:
	CORBA::Object_var facet_ref_;

public:
	FacetPort (const char*, const char*, const CORBA::Object_ptr);
	FacetPort();
	FacetPort (const FacetPort&);
    ~FacetPort();

	bool operator < (const FacetPort&) const {return true;}
	bool operator == (const FacetPort&) const {return true;}

    Components::FacetDescription* facet_description() const;

    const CORBA::Object_ptr facet_ref() const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<FacetPort>;
typedef std::vector<FacetPort> FacetVector;

} // namespace Qedo

#endif

