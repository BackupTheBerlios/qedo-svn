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

#include <CORBA.h>
#include <Components.h>
#include "PortBase.h"
#include "Util.h"
#include <string>
#include <vector>


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * Manages one consumer of a publisher port
 */
class CONTAINERDLL_API SubscribedConsumer
{
private:
	/** the consumer */
	Components::EventConsumerBase_var consumer_;

	/** the cookie of the consumer */
	Cookie_impl* cookie_;

public:
	/**
	 * constructor
	 * \param consumer The subscribed consumer.
	 * \param cookie The cookie for the subscribed consumer.
	 */
    SubscribedConsumer (Components::EventConsumerBase_ptr consumer, 
                        Cookie_impl* cookie);

	/**
	 * constructor
	 */
	SubscribedConsumer();

	/**
	 * copy constructor
	 */
	SubscribedConsumer (const SubscribedConsumer&);

	/**
	 * assignment operator
	 */
	SubscribedConsumer& operator= (const SubscribedConsumer&);

	/**
	 * destructor
	 */
    ~SubscribedConsumer();

	/**
	 * comparison
	 */
	bool operator < (const SubscribedConsumer&) const {return true;}

	/**
	 * comparison
	 */
	bool operator == (const SubscribedConsumer&) const {return true;}

	/**
	 * provides the cookie of the consumer
	 * \return The cookie of the consumer.
	 */
    Cookie_impl* cookie() const;

	/**
	 * provides the consumer
	 * \return The consumer.
	 */
	Components::EventConsumerBase_ptr consumer() const;

	/**
	 * decides whether the consumer is the same like that of the cookie
	 * \param cookie The cookie to be compared with the cookie of the consumer.
	 * \return True if the consumers cookie and the given one are equal.
	 */
	CORBA::Boolean same_consumer (Components::Cookie* cookie) const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<SubscribedConsumer>;
typedef std::vector <SubscribedConsumer> SubscribedConsumerVector;


/**
 * entry in the CCM object executor for a publisher
 */
class PublisherPort : public PortBase
{
private:
	/** the list of consumers */
	SubscribedConsumerVector consumers_;

public:
	/**
	 * constructor
	 * \param name The name of the publisher port.
	 * \param type_id The interface repository id of the port.
	 */
    PublisherPort (const char* name, const char* type_id);

	/**
	 * constructor
	 */
	PublisherPort();

	/**
	 * copy constructor
	 */
	PublisherPort (const PublisherPort&);

	/**
	 * destructor
	 */
    ~PublisherPort();

	/**
	 * comparison
	 */
	bool operator < (const PublisherPort&) const {return true;}

	/**
	 * comparison
	 */
	bool operator == (const PublisherPort&) const {return true;}

	/**
	 * Helper function for the contexts
	 */
	const SubscribedConsumerVector& consumers() const
	{
		return consumers_;
	}

	/**
	 * provides the list of descriptions of all subscribed consumers
	 * \return The list of descriptions of all subscribed consumers.
	 */
    Components::SubscriberDescriptions* subscriber_descriptions() const;

	/**
	 * adds a consumer to the subscription list
	 * \param consumer The consumer to be added.
	 * \return The cookie identifying the consumer.
	 */
    Components::Cookie* add_consumer (Components::EventConsumerBase_ptr consumer);

	/**
	 * unsubscribes the consumer of the given cookie
	 * \param cookie The cookie of the consumer to be unsubscribed.
	 * \return The removed consumer.
	 */
    Components::EventConsumerBase_ptr remove_consumer (Components::Cookie* cookie)
        throw (Components::InvalidConnection);
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<PublisherPort>;	
typedef std::vector<PublisherPort> PublisherVector;

/** @} */

} // namespace Qedo

#endif

