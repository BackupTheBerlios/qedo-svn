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
#include "Valuetypes.h"
#include "Util.h"

#include <string>
#include <vector>

namespace Qedo {

//
// Manages one connection of a receptacle port
// 
class ReceptacleConnection
{
private:
	CORBA::Object_var connection_;
	Qedo::Cookie_impl* cookie_;

public:
    ReceptacleConnection (CORBA::Object_ptr, Qedo::Cookie_impl*);
	ReceptacleConnection();
	ReceptacleConnection (const ReceptacleConnection& recept);
	ReceptacleConnection& operator= (const ReceptacleConnection&);
    ~ReceptacleConnection();
    
	bool operator < (const ReceptacleConnection&) const {return true;}
	bool operator == (const ReceptacleConnection&) const {return true;}

    ConnectionDescription_impl* connection_description() const;

    const CORBA::Object_ptr connection() const;
    Cookie_impl* cookie() const;

    // Returns true, if cookie belongs to my connection
	CORBA::Boolean same_connection (Components::Cookie*) const;
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<ReceptacleConnection>;
typedef std::vector<ReceptacleConnection> ConnectionVector;


//
// Manages one receptacle in the CCM object executor
//
class ReceptaclePort : public PortBase
{
private:
	CORBA::Boolean is_multiplex_;
	ConnectionVector connections_;

public:
	ReceptaclePort (const char*, const char*, CORBA::Boolean);
	ReceptaclePort();
	ReceptaclePort (const ReceptaclePort&);
    ~ReceptaclePort();

	bool operator < (const ReceptaclePort&) const {return true;}
	bool operator == (const ReceptaclePort&) const {return true;}

    Components::ConnectedDescriptions* connected_descriptions() const;
    Components::ReceptacleDescription* receptacle_description() const;

    Cookie_impl* add_connection (CORBA::Object_ptr)
        throw (Components::InvalidConnection,
               Components::AlreadyConnected,
               Components::ExceededConnectionLimit);

    void remove_connection (Components::Cookie*)
        throw (Components::InvalidConnection,
	           Components::CookieRequired, 
		       Components::NoConnection);
};

// Export template class
CONTAINERDLL_EXTERN template class CONTAINERDLL_API std::vector<ReceptaclePort>;
typedef std::vector<ReceptaclePort> ReceptacleVector;

} // namespace Qedo

#endif

