/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2003 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include "explore.h"


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------
#ifdef HAVE_EXPLICIT_STRUCT_OPS
ComponentInstanceInfo::ComponentInstanceInfo()
{
}

ComponentInstanceInfo::ComponentInstanceInfo( const ComponentInstanceInfo& _s )
{
  full_scoped_name = ((ComponentInstanceInfo&)_s).full_scoped_name;
  short_name = ((ComponentInstanceInfo&)_s).short_name;
  compont_ref = ((ComponentInstanceInfo&)_s).compont_ref;
}

ComponentInstanceInfo::~ComponentInstanceInfo()
{
}

ComponentInstanceInfo&
ComponentInstanceInfo::operator=( const ComponentInstanceInfo& _s )
{
  full_scoped_name = ((ComponentInstanceInfo&)_s).full_scoped_name;
  short_name = ((ComponentInstanceInfo&)_s).short_name;
  compont_ref = ((ComponentInstanceInfo&)_s).compont_ref;
  return *this;
}
#endif

class _Marshaller_ComponentInstanceInfo : public ::CORBA::StaticTypeInfo {
    typedef ComponentInstanceInfo _MICO_T;
  public:
    ~_Marshaller_ComponentInstanceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_ComponentInstanceInfo::~_Marshaller_ComponentInstanceInfo()
{
}

::CORBA::StaticValueType _Marshaller_ComponentInstanceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_ComponentInstanceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_ComponentInstanceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_ComponentInstanceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->full_scoped_name._for_demarshal() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->short_name._for_demarshal() ) &&
    _marshaller_Components_CCMObject->demarshal( dc, &((_MICO_T*)v)->compont_ref._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_ComponentInstanceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->full_scoped_name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->short_name.inout() );
  _marshaller_Components_CCMObject->marshal( ec, &((_MICO_T*)v)->compont_ref.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_ComponentInstanceInfo;


#ifdef HAVE_EXPLICIT_STRUCT_OPS
HomeInstanceInfo::HomeInstanceInfo()
{
}

HomeInstanceInfo::HomeInstanceInfo( const HomeInstanceInfo& _s )
{
  full_scoped_name = ((HomeInstanceInfo&)_s).full_scoped_name;
  short_name = ((HomeInstanceInfo&)_s).short_name;
  my_components = ((HomeInstanceInfo&)_s).my_components;
  home_ref = ((HomeInstanceInfo&)_s).home_ref;
}

HomeInstanceInfo::~HomeInstanceInfo()
{
}

HomeInstanceInfo&
HomeInstanceInfo::operator=( const HomeInstanceInfo& _s )
{
  full_scoped_name = ((HomeInstanceInfo&)_s).full_scoped_name;
  short_name = ((HomeInstanceInfo&)_s).short_name;
  my_components = ((HomeInstanceInfo&)_s).my_components;
  home_ref = ((HomeInstanceInfo&)_s).home_ref;
  return *this;
}
#endif

class _Marshaller_HomeInstanceInfo : public ::CORBA::StaticTypeInfo {
    typedef HomeInstanceInfo _MICO_T;
  public:
    ~_Marshaller_HomeInstanceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_HomeInstanceInfo::~_Marshaller_HomeInstanceInfo()
{
}

::CORBA::StaticValueType _Marshaller_HomeInstanceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_HomeInstanceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_HomeInstanceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_HomeInstanceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->full_scoped_name._for_demarshal() ) &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->short_name._for_demarshal() ) &&
    _marshaller__seq_ComponentInstanceInfo->demarshal( dc, &((_MICO_T*)v)->my_components ) &&
    _marshaller_Components_CCMHome->demarshal( dc, &((_MICO_T*)v)->home_ref._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_HomeInstanceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->full_scoped_name.inout() );
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->short_name.inout() );
  _marshaller__seq_ComponentInstanceInfo->marshal( ec, &((_MICO_T*)v)->my_components );
  _marshaller_Components_CCMHome->marshal( ec, &((_MICO_T*)v)->home_ref.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_HomeInstanceInfo;


#ifdef HAVE_EXPLICIT_STRUCT_OPS
ContainerInstanceInfo::ContainerInstanceInfo()
{
}

ContainerInstanceInfo::ContainerInstanceInfo( const ContainerInstanceInfo& _s )
{
  short_name = ((ContainerInstanceInfo&)_s).short_name;
  my_homes = ((ContainerInstanceInfo&)_s).my_homes;
  container_ref = ((ContainerInstanceInfo&)_s).container_ref;
}

ContainerInstanceInfo::~ContainerInstanceInfo()
{
}

ContainerInstanceInfo&
ContainerInstanceInfo::operator=( const ContainerInstanceInfo& _s )
{
  short_name = ((ContainerInstanceInfo&)_s).short_name;
  my_homes = ((ContainerInstanceInfo&)_s).my_homes;
  container_ref = ((ContainerInstanceInfo&)_s).container_ref;
  return *this;
}
#endif

class _Marshaller_ContainerInstanceInfo : public ::CORBA::StaticTypeInfo {
    typedef ContainerInstanceInfo _MICO_T;
  public:
    ~_Marshaller_ContainerInstanceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_ContainerInstanceInfo::~_Marshaller_ContainerInstanceInfo()
{
}

::CORBA::StaticValueType _Marshaller_ContainerInstanceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_ContainerInstanceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_ContainerInstanceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_ContainerInstanceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->short_name._for_demarshal() ) &&
    _marshaller__seq_HomeInstanceInfo->demarshal( dc, &((_MICO_T*)v)->my_homes ) &&
    _marshaller_Components_Deployment_Container->demarshal( dc, &((_MICO_T*)v)->container_ref._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_ContainerInstanceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->short_name.inout() );
  _marshaller__seq_HomeInstanceInfo->marshal( ec, &((_MICO_T*)v)->my_homes );
  _marshaller_Components_Deployment_Container->marshal( ec, &((_MICO_T*)v)->container_ref.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_ContainerInstanceInfo;


#ifdef HAVE_EXPLICIT_STRUCT_OPS
ComponentServerInfo::ComponentServerInfo()
{
}

ComponentServerInfo::ComponentServerInfo( const ComponentServerInfo& _s )
{
  host_name = ((ComponentServerInfo&)_s).host_name;
  my_containers = ((ComponentServerInfo&)_s).my_containers;
  component_server_ref = ((ComponentServerInfo&)_s).component_server_ref;
}

ComponentServerInfo::~ComponentServerInfo()
{
}

ComponentServerInfo&
ComponentServerInfo::operator=( const ComponentServerInfo& _s )
{
  host_name = ((ComponentServerInfo&)_s).host_name;
  my_containers = ((ComponentServerInfo&)_s).my_containers;
  component_server_ref = ((ComponentServerInfo&)_s).component_server_ref;
  return *this;
}
#endif

class _Marshaller_ComponentServerInfo : public ::CORBA::StaticTypeInfo {
    typedef ComponentServerInfo _MICO_T;
  public:
    ~_Marshaller_ComponentServerInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_ComponentServerInfo::~_Marshaller_ComponentServerInfo()
{
}

::CORBA::StaticValueType _Marshaller_ComponentServerInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_ComponentServerInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_ComponentServerInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_ComponentServerInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->host_name._for_demarshal() ) &&
    _marshaller__seq_ContainerInstanceInfo->demarshal( dc, &((_MICO_T*)v)->my_containers ) &&
    _marshaller_Components_Deployment_ComponentServer->demarshal( dc, &((_MICO_T*)v)->component_server_ref._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_ComponentServerInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->host_name.inout() );
  _marshaller__seq_ContainerInstanceInfo->marshal( ec, &((_MICO_T*)v)->my_containers );
  _marshaller_Components_Deployment_ComponentServer->marshal( ec, &((_MICO_T*)v)->component_server_ref.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_ComponentServerInfo;


#ifdef HAVE_EXPLICIT_STRUCT_OPS
ComponentServerActivatorInfo::ComponentServerActivatorInfo()
{
}

ComponentServerActivatorInfo::ComponentServerActivatorInfo( const ComponentServerActivatorInfo& _s )
{
  host_name = ((ComponentServerActivatorInfo&)_s).host_name;
  my_component_servers = ((ComponentServerActivatorInfo&)_s).my_component_servers;
  component_server_activator_ref = ((ComponentServerActivatorInfo&)_s).component_server_activator_ref;
}

ComponentServerActivatorInfo::~ComponentServerActivatorInfo()
{
}

ComponentServerActivatorInfo&
ComponentServerActivatorInfo::operator=( const ComponentServerActivatorInfo& _s )
{
  host_name = ((ComponentServerActivatorInfo&)_s).host_name;
  my_component_servers = ((ComponentServerActivatorInfo&)_s).my_component_servers;
  component_server_activator_ref = ((ComponentServerActivatorInfo&)_s).component_server_activator_ref;
  return *this;
}
#endif

class _Marshaller_ComponentServerActivatorInfo : public ::CORBA::StaticTypeInfo {
    typedef ComponentServerActivatorInfo _MICO_T;
  public:
    ~_Marshaller_ComponentServerActivatorInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_ComponentServerActivatorInfo::~_Marshaller_ComponentServerActivatorInfo()
{
}

::CORBA::StaticValueType _Marshaller_ComponentServerActivatorInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller_ComponentServerActivatorInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller_ComponentServerActivatorInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller_ComponentServerActivatorInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  return
    dc.struct_begin() &&
    CORBA::_stc_string->demarshal( dc, &((_MICO_T*)v)->host_name._for_demarshal() ) &&
    _marshaller__seq_ComponentServerInfo->demarshal( dc, &((_MICO_T*)v)->my_component_servers ) &&
    _marshaller_Components_Deployment_ServerActivator->demarshal( dc, &((_MICO_T*)v)->component_server_activator_ref._for_demarshal() ) &&
    dc.struct_end();
}

void _Marshaller_ComponentServerActivatorInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ec.struct_begin();
  CORBA::_stc_string->marshal( ec, &((_MICO_T*)v)->host_name.inout() );
  _marshaller__seq_ComponentServerInfo->marshal( ec, &((_MICO_T*)v)->my_component_servers );
  _marshaller_Components_Deployment_ServerActivator->marshal( ec, &((_MICO_T*)v)->component_server_activator_ref.inout() );
  ec.struct_end();
}

::CORBA::StaticTypeInfo *_marshaller_ComponentServerActivatorInfo;



/*
 * Base interface for class Explore
 */

Explore::~Explore()
{
}

void *
Explore::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:Explore:1.0" ) == 0 )
    return (void *)this;
  return NULL;
}

Explore_ptr
Explore::_narrow( CORBA::Object_ptr _obj )
{
  Explore_ptr _o;
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:Explore:1.0" )))
      return _duplicate( (Explore_ptr) _p );
    if (!strcmp (_obj->_repoid(), "IDL:Explore:1.0") || _obj->_is_a_remote ("IDL:Explore:1.0")) {
      _o = new Explore_stub;
      _o->CORBA::Object::operator=( *_obj );
      return _o;
    }
  }
  return _nil();
}

Explore_ptr
Explore::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

class _Marshaller_Explore : public ::CORBA::StaticTypeInfo {
    typedef Explore_ptr _MICO_T;
  public:
    ~_Marshaller_Explore();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    void release (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller_Explore::~_Marshaller_Explore()
{
}

::CORBA::StaticValueType _Marshaller_Explore::create() const
{
  return (StaticValueType) new _MICO_T( 0 );
}

void _Marshaller_Explore::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = ::Explore::_duplicate( *(_MICO_T*) s );
}

void _Marshaller_Explore::free( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
  delete (_MICO_T*) v;
}

void _Marshaller_Explore::release( StaticValueType v ) const
{
  ::CORBA::release( *(_MICO_T *) v );
}

::CORBA::Boolean _Marshaller_Explore::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj;
  if (!::CORBA::_stc_Object->demarshal(dc, &obj))
    return FALSE;
  *(_MICO_T *) v = ::Explore::_narrow( obj );
  ::CORBA::Boolean ret = ::CORBA::is_nil (obj) || !::CORBA::is_nil (*(_MICO_T *)v);
  ::CORBA::release (obj);
  return ret;
}

void _Marshaller_Explore::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::Object_ptr obj = *(_MICO_T *) v;
  ::CORBA::_stc_Object->marshal( ec, &obj );
}

::CORBA::StaticTypeInfo *_marshaller_Explore;


/*
 * Stub interface for class Explore
 */

Explore_stub::~Explore_stub()
{
}

#ifndef MICO_CONF_NO_POA

void *
POA_Explore::_narrow_helper (const char * repoid)
{
  if (strcmp (repoid, "IDL:Explore:1.0") == 0) {
    return (void *) this;
  }
  return NULL;
}

POA_Explore *
POA_Explore::_narrow (PortableServer::Servant serv) 
{
  void * p;
  if ((p = serv->_narrow_helper ("IDL:Explore:1.0")) != NULL) {
    serv->_add_ref ();
    return (POA_Explore *) p;
  }
  return NULL;
}

Explore_stub_clp::Explore_stub_clp ()
{
}

Explore_stub_clp::Explore_stub_clp (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
  : CORBA::Object(*obj), PortableServer::StubBase(poa)
{
}

Explore_stub_clp::~Explore_stub_clp ()
{
}

#endif // MICO_CONF_NO_POA

ComponentServerActivatorInfoList* Explore_stub::explore_qedo()
{
  CORBA::StaticAny __res( _marshaller__seq_ComponentServerActivatorInfo );

  CORBA::StaticRequest __req( this, "explore_qedo" );
  __req.set_result( &__res );

  __req.invoke();

  mico_sii_throw( &__req, 
    0);
  return (ComponentServerActivatorInfoList*) __res._retn();
}


#ifndef MICO_CONF_NO_POA

ComponentServerActivatorInfoList*
Explore_stub_clp::explore_qedo()
{
  PortableServer::Servant _serv = _preinvoke ();
  if (_serv) {
    POA_Explore * _myserv = POA_Explore::_narrow (_serv);
    if (_myserv) {
      ComponentServerActivatorInfoList* __res;

      #ifdef HAVE_EXCEPTIONS
      try {
      #endif
        __res = _myserv->explore_qedo();
      #ifdef HAVE_EXCEPTIONS
      }
      catch (...) {
        _myserv->_remove_ref();
        _postinvoke();
        throw;
      }
      #endif

      _myserv->_remove_ref();
      _postinvoke ();
      return __res;
    }
    _postinvoke ();
  }

  return Explore_stub::explore_qedo();
}

#endif // MICO_CONF_NO_POA

class _Marshaller__seq_ComponentInstanceInfo : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< ComponentInstanceInfo,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_ComponentInstanceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_ComponentInstanceInfo::~_Marshaller__seq_ComponentInstanceInfo()
{
}

::CORBA::StaticValueType _Marshaller__seq_ComponentInstanceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_ComponentInstanceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_ComponentInstanceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_ComponentInstanceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_ComponentInstanceInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_ComponentInstanceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_ComponentInstanceInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_ComponentInstanceInfo;

class _Marshaller__seq_HomeInstanceInfo : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< HomeInstanceInfo,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_HomeInstanceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_HomeInstanceInfo::~_Marshaller__seq_HomeInstanceInfo()
{
}

::CORBA::StaticValueType _Marshaller__seq_HomeInstanceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_HomeInstanceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_HomeInstanceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_HomeInstanceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_HomeInstanceInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_HomeInstanceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_HomeInstanceInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_HomeInstanceInfo;

class _Marshaller__seq_ContainerInstanceInfo : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< ContainerInstanceInfo,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_ContainerInstanceInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_ContainerInstanceInfo::~_Marshaller__seq_ContainerInstanceInfo()
{
}

::CORBA::StaticValueType _Marshaller__seq_ContainerInstanceInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_ContainerInstanceInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_ContainerInstanceInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_ContainerInstanceInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_ContainerInstanceInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_ContainerInstanceInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_ContainerInstanceInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_ContainerInstanceInfo;

class _Marshaller__seq_ComponentServerInfo : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< ComponentServerInfo,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_ComponentServerInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_ComponentServerInfo::~_Marshaller__seq_ComponentServerInfo()
{
}

::CORBA::StaticValueType _Marshaller__seq_ComponentServerInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_ComponentServerInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_ComponentServerInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_ComponentServerInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_ComponentServerInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_ComponentServerInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_ComponentServerInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_ComponentServerInfo;

class _Marshaller__seq_ComponentServerActivatorInfo : public ::CORBA::StaticTypeInfo {
    typedef SequenceTmpl< ComponentServerActivatorInfo,MICO_TID_DEF> _MICO_T;
  public:
    ~_Marshaller__seq_ComponentServerActivatorInfo();
    StaticValueType create () const;
    void assign (StaticValueType dst, const StaticValueType src) const;
    void free (StaticValueType) const;
    ::CORBA::Boolean demarshal (::CORBA::DataDecoder&, StaticValueType) const;
    void marshal (::CORBA::DataEncoder &, StaticValueType) const;
};


_Marshaller__seq_ComponentServerActivatorInfo::~_Marshaller__seq_ComponentServerActivatorInfo()
{
}

::CORBA::StaticValueType _Marshaller__seq_ComponentServerActivatorInfo::create() const
{
  return (StaticValueType) new _MICO_T;
}

void _Marshaller__seq_ComponentServerActivatorInfo::assign( StaticValueType d, const StaticValueType s ) const
{
  *(_MICO_T*) d = *(_MICO_T*) s;
}

void _Marshaller__seq_ComponentServerActivatorInfo::free( StaticValueType v ) const
{
  delete (_MICO_T*) v;
}

::CORBA::Boolean _Marshaller__seq_ComponentServerActivatorInfo::demarshal( ::CORBA::DataDecoder &dc, StaticValueType v ) const
{
  ::CORBA::ULong len;
  if( !dc.seq_begin( len ) )
    return FALSE;
  ((_MICO_T *) v)->length( len );
  for( ::CORBA::ULong i = 0; i < len; i++ ) {
    if( !_marshaller_ComponentServerActivatorInfo->demarshal( dc, &(*(_MICO_T*)v)[i] ) )
      return FALSE;
  }
  return dc.seq_end();
}

void _Marshaller__seq_ComponentServerActivatorInfo::marshal( ::CORBA::DataEncoder &ec, StaticValueType v ) const
{
  ::CORBA::ULong len = ((_MICO_T *) v)->length();
  ec.seq_begin( len );
  for( ::CORBA::ULong i = 0; i < len; i++ )
    _marshaller_ComponentServerActivatorInfo->marshal( ec, &(*(_MICO_T*)v)[i] );
  ec.seq_end();
}

::CORBA::StaticTypeInfo *_marshaller__seq_ComponentServerActivatorInfo;

struct __tc_init_EXPLORE {
  __tc_init_EXPLORE()
  {
    _marshaller_ComponentInstanceInfo = new _Marshaller_ComponentInstanceInfo;
    _marshaller_HomeInstanceInfo = new _Marshaller_HomeInstanceInfo;
    _marshaller_ContainerInstanceInfo = new _Marshaller_ContainerInstanceInfo;
    _marshaller_ComponentServerInfo = new _Marshaller_ComponentServerInfo;
    _marshaller_ComponentServerActivatorInfo = new _Marshaller_ComponentServerActivatorInfo;
    _marshaller_Explore = new _Marshaller_Explore;
    _marshaller__seq_ComponentInstanceInfo = new _Marshaller__seq_ComponentInstanceInfo;
    _marshaller__seq_HomeInstanceInfo = new _Marshaller__seq_HomeInstanceInfo;
    _marshaller__seq_ContainerInstanceInfo = new _Marshaller__seq_ContainerInstanceInfo;
    _marshaller__seq_ComponentServerInfo = new _Marshaller__seq_ComponentServerInfo;
    _marshaller__seq_ComponentServerActivatorInfo = new _Marshaller__seq_ComponentServerActivatorInfo;
  }

  ~__tc_init_EXPLORE()
  {
    delete static_cast<_Marshaller_ComponentInstanceInfo*>(_marshaller_ComponentInstanceInfo);
    delete static_cast<_Marshaller_HomeInstanceInfo*>(_marshaller_HomeInstanceInfo);
    delete static_cast<_Marshaller_ContainerInstanceInfo*>(_marshaller_ContainerInstanceInfo);
    delete static_cast<_Marshaller_ComponentServerInfo*>(_marshaller_ComponentServerInfo);
    delete static_cast<_Marshaller_ComponentServerActivatorInfo*>(_marshaller_ComponentServerActivatorInfo);
    delete static_cast<_Marshaller_Explore*>(_marshaller_Explore);
    delete static_cast<_Marshaller__seq_ComponentInstanceInfo*>(_marshaller__seq_ComponentInstanceInfo);
    delete static_cast<_Marshaller__seq_HomeInstanceInfo*>(_marshaller__seq_HomeInstanceInfo);
    delete static_cast<_Marshaller__seq_ContainerInstanceInfo*>(_marshaller__seq_ContainerInstanceInfo);
    delete static_cast<_Marshaller__seq_ComponentServerInfo*>(_marshaller__seq_ComponentServerInfo);
    delete static_cast<_Marshaller__seq_ComponentServerActivatorInfo*>(_marshaller__seq_ComponentServerActivatorInfo);
  }
};

static __tc_init_EXPLORE __init_EXPLORE;

//--------------------------------------------------------
//  Implementation of skeletons
//--------------------------------------------------------

// PortableServer Skeleton Class for interface Explore
POA_Explore::~POA_Explore()
{
}

::Explore_ptr
POA_Explore::_this ()
{
  CORBA::Object_var obj = PortableServer::ServantBase::_this();
  return ::Explore::_narrow (obj);
}

CORBA::Boolean
POA_Explore::_is_a (const char * repoid)
{
  if (strcmp (repoid, "IDL:Explore:1.0") == 0) {
    return TRUE;
  }
  return FALSE;
}

CORBA::InterfaceDef_ptr
POA_Explore::_get_interface ()
{
  CORBA::InterfaceDef_ptr ifd = PortableServer::ServantBase::_get_interface ("IDL:Explore:1.0");

  if (CORBA::is_nil (ifd)) {
    mico_throw (CORBA::OBJ_ADAPTER (0, CORBA::COMPLETED_NO));
  }

  return ifd;
}

CORBA::RepositoryId
POA_Explore::_primary_interface (const PortableServer::ObjectId &, PortableServer::POA_ptr)
{
  return CORBA::string_dup ("IDL:Explore:1.0");
}

CORBA::Object_ptr
POA_Explore::_make_stub (PortableServer::POA_ptr poa, CORBA::Object_ptr obj)
{
  return new ::Explore_stub_clp (poa, obj);
}

bool
POA_Explore::dispatch (CORBA::StaticServerRequest_ptr __req)
{
  #ifdef HAVE_EXCEPTIONS
  try {
  #endif
    if( strcmp( __req->op_name(), "explore_qedo" ) == 0 ) {
      ::ComponentServerActivatorInfoList* _res;
      CORBA::StaticAny __res( _marshaller__seq_ComponentServerActivatorInfo );
      __req->set_result( &__res );

      if( !__req->read_args() )
        return true;

      _res = explore_qedo();
      __res.value( _marshaller__seq_ComponentServerActivatorInfo, _res );
      __req->write_results();
      delete _res;
      return true;
    }
  #ifdef HAVE_EXCEPTIONS
  } catch( CORBA::SystemException_catch &_ex ) {
    __req->set_exception( _ex->_clone() );
    __req->write_results();
    return true;
  } catch( ... ) {
    CORBA::UNKNOWN _ex (CORBA::OMGVMCID | 1, CORBA::COMPLETED_MAYBE);
    __req->set_exception (_ex->_clone());
    __req->write_results ();
    return true;
  }
  #endif

  return false;
}

void
POA_Explore::invoke (CORBA::StaticServerRequest_ptr __req)
{
  if (dispatch (__req)) {
      return;
  }

  CORBA::Exception * ex = 
    new CORBA::BAD_OPERATION (0, CORBA::COMPLETED_NO);
  __req->set_exception (ex);
  __req->write_results();
}

