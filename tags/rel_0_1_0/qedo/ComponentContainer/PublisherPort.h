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

#ifndef __PUBLISHER_PORT_H__
#define __PUBLISHER_PORT_H__

#include <OB/CORBA.h>
#include <Components.h>

#include "PortBase.h"
#include "Util.h"

#include <string>
#include <vector>

namespace Qedo {

//
// Manages one consumer of a publisher port
//
class CONTAINERDLL_API SubscribedConsumer
{
private:
	Components::EventConsumerBase_var consumer_;
	Cookie_impl* cookie_;

public:
    SubscribedConsumer (Components::EventConsumerBase_ptr consumer, 
                        Cookie_impl* cookie);
	SubscribedConsumer();
	SubscribedConsumer (const SubscribedConsumer&);
	SubscribedConsumer& operator= (const SubscribedConsumer&);
    ~SubscribedConsumer();

	bool operator < (const SubscribedConsumer&) const {return true;}
	bool operator == (const SubscribedConsumer&) const {return true;}

    Cookie_impl* cookie() const;
	Components::EventConsumerBase_ptr consumer() const;

    // Returns true, if cookie belongs to my consumer
	CORBA::Boolean same_consumer (Components::Cookie*) const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<SubscribedConsumer>;
typedef std::vector <SubscribedConsumer> SubscribedConsumerVector;


//
// Entry in the CCM object executor for a publisher
//
class PublisherPort : public PortBase
{
private:
	SubscribedConsumerVector consumers_;

public:
    PublisherPort (const char*, const char*);
	PublisherPort();
	PublisherPort (const PublisherPort&);
    ~PublisherPort();

	bool operator < (const PublisherPort&) const {return true;}
	bool operator == (const PublisherPort&) const {return true;}

	// Helper function for the contexts
	const SubscribedConsumerVector& consumers() const
	{
		return consumers_;
	}

    Components::SubscriberDescriptions* subscriber_descriptions() const;

    Components::Cookie* add_consumer (Components::EventConsumerBase_ptr);

    Components::EventConsumerBase_ptr remove_consumer (Components::Cookie*)
        throw (Components::InvalidConnection);
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<PublisherPort>;	
typedef std::vector<PublisherPort> PublisherVector;

} // namespace Qedo

#endif

