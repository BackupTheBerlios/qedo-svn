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

#ifndef __CONSUMER_PORT_H__
#define __CONSUMER_PORT_H__

#include <OB/CORBA.h>
#include <Components.h>

#include "PortBase.h"
#include "Util.h"

#include <string>
#include <vector>

namespace Qedo {

//
// Entry in the CCM object executor for an event consumer
//
class ConsumerPort : public PortBase
{
private:
    Components::EventConsumerBase_var consumer_;

public:
    ConsumerPort (const char*, const char*, Components::EventConsumerBase_ptr);
	ConsumerPort();
	ConsumerPort (const ConsumerPort&);
    ~ConsumerPort();

	bool operator < (const ConsumerPort&) const {return true;}
	bool operator == (const ConsumerPort&) const {return true;}

    Components::ConsumerDescription* consumer_description() const;

    const Components::EventConsumerBase_ptr consumer() const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<ConsumerPort>;
typedef std::vector<ConsumerPort> ConsumerVector;

} // namespace Qedo

#endif

