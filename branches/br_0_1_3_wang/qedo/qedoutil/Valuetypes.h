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

#ifndef __VALUE_TYPES_H__
#define __VALUE_TYPES_H__

#include <CORBA.h>
#include "Components.h"

#include "qedoutil.h"


namespace Qedo {


/**
 * @addtogroup ComponentContainer
 * @{
 */


/**
 * implementation of IDL:omg.org/Components/Cookie:1.0
 */
class QEDOUTIL_API Cookie_impl : public virtual OBV_Components::Cookie,
									 public virtual CORBA::DefaultValueRefCountBase
{
private:
	/** the cookie value */
    static CORBA::LongLong cookie_key_;

	/**
	 * assignment operator shall not be called
	 */
	void operator=(const Cookie_impl&);

	/**
	 * copy constructor shall not be called
	 */
	Cookie_impl (const Cookie_impl&);

public:
	/**
	 * constructor
	 */
	Cookie_impl();

	/**
	 * destructor
	 */
	~Cookie_impl();

	/**
	 * extension to compare cookie values
	 * returns true if the values of this Cookie and another one are equal
	 * \param cook The cookie to compare.
	 * \return True if the cookies are equal.
	 */
	CORBA::Boolean equal (Components::Cookie* cook);

	/**
	 * provide string representation
	 * \return A string representation of the cookie value.
	 */
	const char* to_string();
};


/**
 * factory for cookies
 */
class QEDOUTIL_API CookieFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};


/**
 * implementation of IDL:omg.org/Components/PortDescription:1.0
 */
class QEDOUTIL_API PortDescription_impl : public virtual OBV_Components::PortDescription,
                             public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const PortDescription_impl&);

	/**
	 * copy constructor shall not be called
	 */
	PortDescription_impl (const PortDescription_impl&);

public:
	/**
	 * constructor
	 * \param name The name of the port.
	 * \param type_id The interface repository id of the port.
	 */
	PortDescription_impl (const char* name, const char* type_id);

	/**
	 * constructor used by create_for_unmarshal
	 */
	PortDescription_impl();

	/**
	 * destructor
	 */
	~PortDescription_impl();
};


/**
 * factory for port descriptions
 */
class QEDOUTIL_API PortDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};


/**
 * implementation of IDL:omg.org/Components/FacetDescription:1.0
 */
class QEDOUTIL_API FacetDescription_impl : public virtual OBV_Components::FacetDescription,
				              public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const FacetDescription_impl&);

	/**
	 * copy constructor shall not be called
	 */
	FacetDescription_impl (const FacetDescription_impl&);

public:
	/**
	 * constructor
	 * \param name The name of the facet.
	 * \param type_id The interface repository id of the facet.
	 * \param ref The reference of the facet.
	 */
	FacetDescription_impl (const char* name, const char* type_id, CORBA::Object_ptr ref);

	/**
	 * constructor used by create_for_unmarshal
	 */
	FacetDescription_impl();

	/**
	 * destructor
	 */
	~FacetDescription_impl();
};


/**
 * factory for facet descriptions
 */
class QEDOUTIL_API FacetDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};


/**
 * implementation of IDL:omg.org/Components/ConnectionDescription:1.0
 */
class QEDOUTIL_API ConnectionDescription_impl : public virtual OBV_Components::ConnectionDescription,
								   public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const ConnectionDescription_impl&);

	/**
	 * copy constructor shall not be called
	 */
	ConnectionDescription_impl (const ConnectionDescription_impl&);

public:
	/**
	 * constructor
	 * \param ck The cookie of the connection.
	 * \param objref The object reference of the connected object.
	 */
	ConnectionDescription_impl (Components::Cookie* ck, CORBA::Object_ptr objref);

	/**
	 * constructor
	 */
	ConnectionDescription_impl();

	/**
	 * destructor
	 */
	~ConnectionDescription_impl();
};


/**
 * factory for connection descriptions
 */
class QEDOUTIL_API ConnectionDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};


/**
 * implementation of IDL:omg.org/Components/ReceptacleDescription:1.0
 */
class QEDOUTIL_API ReceptacleDescription_impl : public virtual OBV_Components::ReceptacleDescription,
								   public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const ReceptacleDescription_impl&);

	/**
	 * copy constructor shall not be called
	 */
	ReceptacleDescription_impl (const ReceptacleDescription_impl&);

public:
	/**
	 * consructor
	 * \param name The name of the receptacle.
	 * \param type_id The interface repository id of the receptacle.
	 * \param is_multiplex True if the receptacle is declared multiple.
	 * \param connections The list of descriptions of connections.
	 */
	ReceptacleDescription_impl (const char* name, 
						   const char* type_id, 
						   CORBA::Boolean is_multiplex, 
						   const Components::ConnectedDescriptions& connections);

	/**
	 * constructor
	 */
	ReceptacleDescription_impl();

	/**
	 * destructor
	 */
	~ReceptacleDescription_impl();
};


/**
 * factory for receptacle descriptions
 */
class QEDOUTIL_API ReceptacleDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};


/**
 * implementation of IDL:omg.org/Components/ConsumerDescription:1.0
 */
class QEDOUTIL_API ConsumerDescription_impl : public virtual OBV_Components::ConsumerDescription,
								 public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const ConsumerDescription_impl&);

	/**
	 * copy constructor shall not be called
	 */
	ConsumerDescription_impl (const ConsumerDescription_impl&);

public:
	/**
	 * constructor
	 * \param name The name of the consumer port.
	 * \param type_id The interface repository id of the consumer.
	 * \param consumer The consumer reference.
	 */
	ConsumerDescription_impl (const char* name, const char* type_id, Components::EventConsumerBase_ptr consumer);

	/**
	 * constructor
	 */
	ConsumerDescription_impl();

	/**
	 * destructor
	 */
	~ConsumerDescription_impl();
};


/**
 * factory for consumer descriptions
 */
class QEDOUTIL_API ConsumerDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal ();
};


/**
 * implementation of IDL:omg.org/Components/EmitterDescription:1.0
 */
class QEDOUTIL_API EmitterDescription_impl : public virtual OBV_Components::EmitterDescription,
								public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const EmitterDescription_impl&);

	/**
	 * copy constructor shall not be called
	 */
	EmitterDescription_impl (const EmitterDescription_impl&);

public:
	/**
	 * constructor
	 * \param name The name of the emitter.
	 * \param type_id The interface repository id of the emitter.
	 * \param consumer The consumer.
	 */
	EmitterDescription_impl (const char* name, const char* type_id, Components::EventConsumerBase_ptr consumer);

	/**
	 * constructor
	 */
	EmitterDescription_impl();

	/**
	 * destructor
	 */
	~EmitterDescription_impl ();
};


/**
 * factory for emitter descriptions
 */
class QEDOUTIL_API EmitterDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal ();
};


/**
 * implementation of IDL:omg.org/Components/SubscriberDescription:1.0
 */
class QEDOUTIL_API SubscriberDescription_impl : public virtual OBV_Components::SubscriberDescription,
								   public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const SubscriberDescription_impl&);

	/**
	 * copy constructor shall not be called
	 */
	SubscriberDescription_impl (const SubscriberDescription_impl&);

public:
	/**
	 * constructor
	 * \param name The name of the publisher port.
	 * \param type_id The interface repository id of the publisher port.
	 * \param ck The cookie of a subscribed consumer.
	 * \param consumer The subscribed consumer.
	 */
	SubscriberDescription_impl (const char* name, 
								const char* type_id, 
								Components::Cookie* ck, 
								Components::EventConsumerBase_ptr consumer);

	/**
	 * constructor
	 */
	SubscriberDescription_impl();

	/**
	 * destructor
	 */
	~SubscriberDescription_impl ();
};


/**
 * factory for subscriber descriptions
 */
class QEDOUTIL_API SubscriberDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};


/**
 * implementation of IDL:omg.org/Components/ComponentPortDescription:1.0
 */
class QEDOUTIL_API ComponentPortDescription_impl : public virtual OBV_Components::ComponentPortDescription,
								      public virtual CORBA::DefaultValueRefCountBase
{
private:
	//
	/// assignment operator shall not be called
	//
	void operator=(const ComponentPortDescription_impl&);

	//
	/// copy constructor shall not be called
	//
	ComponentPortDescription_impl (const ComponentPortDescription_impl&);

public:
	/**
	 * constructor
	 * \param facets The list of descriptions of all facet ports.
	 * \param receptacles The list of descriptions of all receptacle ports.
	 * \param consumers The list of descriptions of all consumer ports.
	 * \param emitters The list of descriptions of all emmitters.
	 * \param publishers The list of descriptions of all publishers.
	 */
	ComponentPortDescription_impl (const Components::FacetDescriptions& facets,
								   const Components::ReceptacleDescriptions& receptacles,
								   const Components::ConsumerDescriptions& consumers,
								   const Components::EmitterDescriptions& emitters,
								   const Components::SubscriberDescriptions& publishers);

	/**
	 * constructor
	 */
	ComponentPortDescription_impl();

	/**
	 * destructor
	 */
	~ComponentPortDescription_impl();
};


/**
 * factory for component port descriptions
 */
class QEDOUTIL_API ComponentPortDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};


/**
 * implementation of IDL:omg.org/Components/ConfigValue:1.0
 */
class QEDOUTIL_API ConfigValue_impl : public virtual OBV_Components::ConfigValue,
										  public virtual CORBA::DefaultValueRefCountBase
{
private:
	/**
	 * assignment operator shall not be called
	 */
	void operator=(const ConfigValue_impl&);

	/**
	 * copy constructor shall not be called
	 */
	ConfigValue_impl (const ConfigValue_impl&);

public:
	/**
	 * constructor
	 * \param name The name of the config value.
	 * \param value The value of the config value.
	 */
	ConfigValue_impl (const char* name,  CORBA::Any& value);

	/**
	 * constructor
	 */
	ConfigValue_impl();

	/**
	 * destructor
	 */
	~ConfigValue_impl ();
};


/**
 * factory for config values
 */
class QEDOUTIL_API ConfigValueFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	/**
	 * for creating an incoming valuetype
	 */
	virtual CORBA::ValueBase* create_for_unmarshal();
};

/** @} */

} // namespace Qedo


#endif
