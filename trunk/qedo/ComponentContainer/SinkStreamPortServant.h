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

#ifndef __SINK_STREAM_PORT_SERVANT_H__
#define __SINK_STREAM_PORT_SERVANT_H__

#ifndef _QEDO_NO_STREAMS


#include <CORBA.h>
//#include <StreamComponents_skel.h>

#include "StreamCCMObjectExecutor.h"
#include "ServantBase.h"
#include "Util.h"


namespace Qedo {


class CONTAINERDLL_API SinkStreamPortServant : public virtual POA_StreamComponents::SinkStreamPort,
											   public virtual Qedo::ServantBase
{
private:
	std::string port_name_;

protected:

public:
	SinkStreamPortServant (const char*);
	virtual ~SinkStreamPortServant();

	//
    // IDL:omg.org/StreamComponents/SinkStreamPort/check_stream_type:1.0
    //
    void check_streamtype(const CORBA::RepositoryIdSeq&)
        throw(StreamComponents::UnsupportedStreamtype,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/SinkStreamPort/consider_transport:1.0
    //
    void consider_transport(StreamComponents::TransportSpec&)
        throw(StreamComponents::AlreadyBound,
			  StreamComponents::TransportFailure,
              CORBA::SystemException);

    //
    // IDL:omg.org/StreamComponents/SinkStreamPort/release_transport:1.0
    //
    void release_transport()
		throw(CORBA::SystemException);
};


} // namespace Qedo


#endif

#endif

