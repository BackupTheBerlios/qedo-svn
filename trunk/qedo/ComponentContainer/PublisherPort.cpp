/***************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                  */
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

static char rcsid[] = "$Id: PublisherPort.cpp,v 1.3 2002/12/03 07:48:58 stoinski Exp $";

#include "PublisherPort.h"
#include "Output.h"

namespace Qedo {

SubscribedConsumer::SubscribedConsumer (Components::EventConsumerBase_ptr consumer, 
                                        Cookie_impl* cookie)
: consumer_ (Components::EventConsumerBase::_duplicate (consumer)),
  cookie_ (cookie)
{
    cookie_->_add_ref();
}


SubscribedConsumer::SubscribedConsumer()
{
}


SubscribedConsumer::SubscribedConsumer (const SubscribedConsumer& subs_cons)
: consumer_ (Components::EventConsumerBase::_duplicate (subs_cons.consumer_)),
  cookie_ (subs_cons.cookie_)
{
	cookie_->_add_ref();
}


SubscribedConsumer& 
SubscribedConsumer::operator= (const SubscribedConsumer& subs_cons)
{
	consumer_ = Components::EventConsumerBase::_duplicate (subs_cons.consumer_);

	if (cookie_)
		cookie_->_remove_ref();

	cookie_ = subs_cons.cookie_;
	cookie_->_add_ref();

	return *this;
}


SubscribedConsumer::~SubscribedConsumer()
{
    cookie_->_remove_ref();
}


Cookie_impl*
SubscribedConsumer::cookie() const
{
	cookie_->_add_ref();
	return cookie_;
}


Components::EventConsumerBase_ptr
SubscribedConsumer::consumer() const
{
	return Components::EventConsumerBase::_duplicate (consumer_);
}


bool 
SubscribedConsumer::same_consumer (Components::Cookie* cookie) const
{
    return cookie_->equal (cookie);
}


PublisherPort::PublisherPort (const char* name, const char* type_id)
: PortBase (name, type_id)
{
}


PublisherPort::PublisherPort()
{
}


PublisherPort::PublisherPort (const PublisherPort& pub_port)
: PortBase (pub_port),
  consumers_ (pub_port.consumers_)
{
}


PublisherPort::~PublisherPort()
{
}


Components::SubscriberDescriptions* 
PublisherPort::subscriber_descriptions() const
{
	Components::SubscriberDescriptions_var sub_desc = 
        new Components::SubscriberDescriptions();

    sub_desc->length (consumers_.size());

    for (unsigned int i = 0; i < consumers_.size(); i++)
    {
		Components::Cookie_var cookie = consumers_[i].cookie();
		Components::EventConsumerBase_var consumer = consumers_[i].consumer();

        sub_desc[i] = new SubscriberDescription_impl (port_name_.c_str(), type_id_.c_str(), cookie, consumer);
    }

    return sub_desc._retn();
}


Components::Cookie*
PublisherPort::add_consumer (Components::EventConsumerBase_ptr consumer)
{
	// Create cookie
    Cookie_impl* new_cookie = new Cookie_impl();

	// Create new consumer entry
	SubscribedConsumer new_entry (consumer, new_cookie);
			
    consumers_.push_back (new_entry);

	DEBUG_OUT2 ("PublisherPort: New publisher subscribed for port ", port_name_);

	return new_cookie;
}


Components::EventConsumerBase_ptr 
PublisherPort::remove_consumer (Components::Cookie* cookie)
throw (Components::InvalidConnection)
{
	SubscribedConsumerVector::iterator con_iter;

    for (con_iter = consumers_.begin();
		 con_iter != consumers_.end();
		 con_iter++)
	{
		if ((*con_iter).same_consumer (cookie))
		{
			Components::EventConsumerBase_var ret;

			ret = (*con_iter).consumer();

			consumers_.erase ( con_iter );

			DEBUG_OUT2 ( "PublisherPort: Publisher unsubscribed for port ", port_name_ );

			return ret;
		}
	}

	throw Components::InvalidConnection();
}

} // namespace Qedo

