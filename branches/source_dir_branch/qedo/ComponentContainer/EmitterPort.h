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

#ifndef __EMITTER_PORT_H__
#define __EMITTER_PORT_H__

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
 * Entry in the CCM object executor for an emitter
 */
class EmitterPort : public PortBase
{
private:
	/** the consumer */
    Components::EventConsumerBase_var consumer_;

public:
	/**
	 * constructor
	 * \param name The name of the emitter.
	 * \param type_id The interface repository id of the emitter.
	 */
    EmitterPort (const char* name, const char* type_id);

	/**
	 * constructor
	 */
	EmitterPort();

	/**
	 * copy constructor
	 */
	EmitterPort (const EmitterPort&);

	/**
	 * destructor
	 */
    ~EmitterPort();

	/**
	 * comparison
	 */
	bool operator < (const EmitterPort&) const {return true;}

	/**
	 * comparison
	 */
	bool operator == (const EmitterPort&) const {return true;}

	/**
	 * provides the consumer
	 * \return The consumer.
	 */
	const Components::EventConsumerBase_ptr consumer() const
	{
		return Components::EventConsumerBase::_duplicate (consumer_.in());
	}

	/**
	 * provides the description of the emitter
	 * \return The description of the emitter.
	 */
    Components::EmitterDescription* emitter_description() const;

	/**
	 * sets the consumer
	 * \param consumer The consumer for this emitter.
	 */
    void set_consumer (Components::EventConsumerBase_ptr consumer)
        throw (Components::AlreadyConnected);

	/**
	 * unsets the consumer
	 * \return The former consumer for this emitter.
	 */
    Components::EventConsumerBase_ptr unset_consumer()
        throw (Components::NoConnection);
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<EmitterPort>;	
typedef std::vector<EmitterPort> EmitterVector;

/** @} */

} // namespace Qedo

#endif

