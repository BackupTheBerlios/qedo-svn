//
// TETRA
// Stream Container Implementation
// (C)2000-2002 Humboldt University Berlin, Department of Computer Science
//
// $Id: ClientValuetypes.h,v 1.1 2003/08/10 15:19:11 tom Exp $
//

#ifndef __VALUE_TYPES_H__
#define __VALUE_TYPES_H__

#include <CORBA.h>

#include "Components.h"

//
// Implementation of Components::Cookie
//
class Cookie_impl : public virtual OBV_Components::Cookie,
					public virtual CORBA::DefaultValueRefCountBase
{
private:
    static CORBA::LongLong cookie_key_;

	void operator=(const Cookie_impl&);
	Cookie_impl (const Cookie_impl&);

public:
	Cookie_impl();
	~Cookie_impl();

	// Extension
	CORBA::Boolean equal (Components::Cookie*);
};


class CookieFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


//
// Implementation of Components::PortDescription
//
class PortDescription_impl : public virtual OBV_Components::PortDescription,
							 public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const PortDescription_impl&);

public:
	PortDescription_impl (const char*, const char*);
	PortDescription_impl();
	~PortDescription_impl();
};


class PortDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


//
// Implementation of Components::FacetDescription
//
class FacetDescription_impl : public virtual OBV_Components::FacetDescription,
				              public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const FacetDescription_impl&);

public:
	FacetDescription_impl (const char*, const char*, CORBA::Object_ptr);
	FacetDescription_impl();
	~FacetDescription_impl();
};


class FacetDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


//
// Implementation of Components::ConnectionDescription
//
class ConnectionDescription_impl : public virtual OBV_Components::ConnectionDescription,
								   public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const ConnectionDescription_impl&);

public:
	ConnectionDescription_impl (Components::Cookie*, CORBA::Object_ptr);
	ConnectionDescription_impl();
	~ConnectionDescription_impl();
};


class ConnectionDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


//
// Implementation of Components::ReceptacleDescription
//
class ReceptacleDescription_impl : public virtual OBV_Components::ReceptacleDescription,
								   public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const ReceptacleDescription_impl&);

public:
	ReceptacleDescription_impl (const char*, 
						   const char*, 
						   CORBA::Boolean, 
						   const Components::ConnectedDescriptions&);
	ReceptacleDescription_impl();
	~ReceptacleDescription_impl();
};


class ReceptacleDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


//
// Implementation of Components::ConsumerDescription
//
class ConsumerDescription_impl : public virtual OBV_Components::ConsumerDescription,
								 public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const ConsumerDescription_impl&);

public:
	ConsumerDescription_impl (const char*, const char*, Components::EventConsumerBase_ptr);
	ConsumerDescription_impl();
	~ConsumerDescription_impl();
};


class ConsumerDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal ();
};


//
// Implementation of Components::EmitterDescription
//
class EmitterDescription_impl : public virtual OBV_Components::EmitterDescription,
								public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const EmitterDescription_impl&);

public:
	EmitterDescription_impl (const char*, const char*, Components::EventConsumerBase_ptr);
	EmitterDescription_impl();
	EmitterDescription_impl (const EmitterDescription_impl&);
	~EmitterDescription_impl ();
};


class EmitterDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal ();
};


//
// Implementation of Components::SubscriberDescription
//
class SubscriberDescription_impl : public virtual OBV_Components::SubscriberDescription,
								   public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const SubscriberDescription_impl&);

public:
	SubscriberDescription_impl (const char*, 
								const char*, 
								Components::Cookie*, 
								Components::EventConsumerBase_ptr);
	SubscriberDescription_impl();
	~SubscriberDescription_impl ();
};


class SubscriberDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


//
// Implementation of Components::ComponentPortDescription
//
class ComponentPortDescription_impl : public virtual OBV_Components::ComponentPortDescription,
								      public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const ComponentPortDescription_impl&);

public:
	ComponentPortDescription_impl (const Components::FacetDescriptions&,
								   const Components::ReceptacleDescriptions&,
								   const Components::ConsumerDescriptions&,
								   const Components::EmitterDescriptions&,
								   const Components::SubscriberDescriptions&);
	ComponentPortDescription_impl();
	~ComponentPortDescription_impl();
};


class ComponentPortDescriptionFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


//
// Implementation of Components::ConfigValue
//
class ConfigValue_impl : public virtual OBV_Components::ConfigValue,
										  public virtual CORBA::DefaultValueRefCountBase
{
private:
	void operator=(const ConfigValue_impl&);
	ConfigValue_impl (const ConfigValue_impl&);

public:
	ConfigValue_impl (const char*, CORBA::Any&);
	ConfigValue_impl();
	~ConfigValue_impl ();
};


class ConfigValueFactory_impl : public virtual CORBA::ValueFactoryBase
{
private:
	virtual CORBA::ValueBase* create_for_unmarshal();
};


#endif

