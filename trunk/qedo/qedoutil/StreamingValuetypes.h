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

#ifndef __STREAMING_VALUE_TYPES_H__
#define __STREAMING_VALUE_TYPES_H__

#ifndef _QEDO_NO_STREAMS


#include <CORBA.h>
#include "StreamComponents.h"
#include "qedoutil.h"


namespace Qedo {


class QEDOUTIL_API BindingDescription_impl : public virtual OBV_StreamComponents::BindingDescription,
								public virtual CORBA::DefaultValueRefCountBase
{
private:
	BindingDescription_impl (const BindingDescription_impl&);

	void operator=(const BindingDescription_impl&);

public:
	BindingDescription_impl ( Components::Cookie* ck, StreamComponents::SinkStreamPort_ptr the_sink);

	BindingDescription_impl();

	~BindingDescription_impl();
};


class QEDOUTIL_API BindingDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


class QEDOUTIL_API SourceDescription_impl : public virtual OBV_StreamComponents::SourceDescription,
							   public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const SourceDescription_impl&);

	SourceDescription_impl (const SourceDescription_impl&);

public:
	SourceDescription_impl (const char* name, 
							const char* type_id, 
							CORBA::Boolean is_multiplex,
							const CORBA::RepositoryIdSeq& repository_ids,
							const StreamComponents::BindingDescriptions& bindings);

	SourceDescription_impl();

	~SourceDescription_impl();
};


class QEDOUTIL_API SourceDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


class QEDOUTIL_API SinkDescription_impl : public virtual OBV_StreamComponents::SinkDescription,
							 public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const SinkDescription_impl&);

	SinkDescription_impl (const SinkDescription_impl&);

public:
	SinkDescription_impl (const char* name, 
						  const char* type_id,
						  const CORBA::RepositoryIdSeq& repository_ids,
						  StreamComponents::SinkStreamPort_ptr the_sink);

	SinkDescription_impl();

	~SinkDescription_impl();
};


class QEDOUTIL_API SinkDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};

} // namespace Qedo


#endif

#endif

