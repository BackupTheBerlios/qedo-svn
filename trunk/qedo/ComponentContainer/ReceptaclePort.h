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

#ifndef __RECEPTACLE_PORT_H__
#define __RECEPTACLE_PORT_H__

#include <CORBA.h>
#include <Components.h>

#include "PortBase.h"
#include "Synchronisation.h"
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
 * Manages one connection of a receptacle port
 */
class ReceptacleConnection
{
private:
	/** the connection */
	CORBA::Object_var connection_;

	/** the cookie of the receptacle (if multiple) */
	Qedo::Cookie_impl* cookie_;

public:
	/**
	 * constructor
	 * \param connection The connection.
	 * \param cookie The cookie for identification of the connection.
	 */
    ReceptacleConnection (CORBA::Object_ptr connection, Qedo::Cookie_impl* cookie);

	/**
	 * constructor
	 */
	ReceptacleConnection();

	/**
	 * copy constructor
	 */
	ReceptacleConnection (const ReceptacleConnection& recept);

	/**
	 * assignment operator
	 */
	ReceptacleConnection& operator= (const ReceptacleConnection&);

	/**
	 * destructor
	 */
    ~ReceptacleConnection();
    
	/**
	 * comparison
	 */
	bool operator < (const ReceptacleConnection&) const {return true;}

	/**
	 * comparison
	 */
	bool operator == (const ReceptacleConnection&) const {return true;}

	/**
	 * provides a description of the connection
	 * \return The description of the connection.
	 */
    ConnectionDescription_impl* connection_description() const;

	/**
	 * provides the connection
	 * \return The connection.
	 */
    const CORBA::Object_ptr connection() const;

	/**
	 * provides the cookie of the connection
	 * \return The cookie of the connection.
	 */
    Cookie_impl* cookie() const;

	/**
	 * decides whether the given cookie and the cookie of the connection are equal
	 * \param cookie The cookie to be compared with that of the connection.
	 * \return True if the given cookie and the cookie of the connection are equal.
	 */
	CORBA::Boolean same_connection (Components::Cookie* cookie) const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<ReceptacleConnection>;
typedef std::vector<ReceptacleConnection> ConnectionVector;


/**
 * Manages one receptacle in the CCM object executor
 */
class ReceptaclePort : public PortBase
{
private:
	/** multiple */
	CORBA::Boolean is_multiplex_;

	/** list of connections */
	ConnectionVector connections_;
	/** the mutex for connections_ */
	QedoMutex connections_mutex_;

public:
	/**
	 * constructor
	 * \param name The name of the receptacle port.
	 * \param type_id The interface repository id of the port.
	 * \param is_multiplex True if the port is declared to be multiple.
	 */
	ReceptaclePort (const char* name, const char* type_id, CORBA::Boolean is_multiplex);

	/**
	 * constructor
	 */
	ReceptaclePort();

	/**
	 * copy constructor
	 */
	ReceptaclePort (const ReceptaclePort&);

	/**
	 * destructor
	 */
    ~ReceptaclePort();

	/**
	 * comparison
	 */
	bool operator < (const ReceptaclePort&) const {return true;}

	/**
	 * assigment operator
	 */
	bool operator == (const ReceptaclePort&) const {return true;}

	/**
	 * provides the list of descriptions for all connections
	 * \return The list of descriptions for all connections.
	 */
    Components::ConnectedDescriptions* connected_descriptions() const;

	/**
	 * provides the description of the receptacle itself
	 * \return The description of the receptacle.
	 */
    Components::ReceptacleDescription* receptacle_description() const;

	/**
	 * adds a connection to the receptacle
	 * \param connection The connection to be added.
	 * \return The cookie for identification of the connection.
	 */
    Cookie_impl* add_connection (CORBA::Object_ptr connection)
        throw (Components::InvalidConnection,
               Components::AlreadyConnected,
               Components::ExceededConnectionLimit);

	/**
	 * remove a connection identified by the given cookie
	 * \param cookie The cookie of the connection to be removed.
	 */
    void remove_connection (Components::Cookie* cookie)
        throw (Components::InvalidConnection,
	           Components::CookieRequired, 
		       Components::NoConnection);
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<ReceptaclePort>;
typedef std::vector<ReceptaclePort> ReceptacleVector;

/** @} */

} // namespace Qedo

#endif

