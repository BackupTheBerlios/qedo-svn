/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2003 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <inherit_DerivedImpl_BUSINESS.h>


using namespace std;

//--------------------------------------------------------
//  Implementation of stubs
//--------------------------------------------------------

/*
 * Base interface for class CCM_DerivedSessionImpl
 */

inherit::CCM_DerivedSessionImpl::~CCM_DerivedSessionImpl()
{
}

void *
inherit::CCM_DerivedSessionImpl::_narrow_helper( const char *_repoid )
{
  if( strcmp( _repoid, "IDL:inherit/CCM_DerivedSessionImpl:1.0" ) == 0 )
    return (void *)this;
  {
    void *_p;
    if ((_p = inherit::CCM_derived_component_Executor::_narrow_helper( _repoid )))
      return _p;
  }
  {
    void *_p;
    if ((_p = inherit::CCM_derived_interf::_narrow_helper( _repoid )))
      return _p;
  }
  return NULL;
}

inherit::CCM_DerivedSessionImpl_ptr
inherit::CCM_DerivedSessionImpl::_narrow( CORBA::Object_ptr _obj )
{
  if( !CORBA::is_nil( _obj ) ) {
    void *_p;
    if( (_p = _obj->_narrow_helper( "IDL:inherit/CCM_DerivedSessionImpl:1.0" )))
      return _duplicate( (inherit::CCM_DerivedSessionImpl_ptr) _p );
  }
  return _nil();
}

inherit::CCM_DerivedSessionImpl_ptr
inherit::CCM_DerivedSessionImpl::_narrow( CORBA::AbstractBase_ptr _obj )
{
  return _narrow (_obj->_to_object());
}

namespace inherit
{
CORBA::TypeCodeConst _tc_CCM_DerivedSessionImpl;
}

struct __tc_init_INHERIT_DERIVEDIMPL_BUSINESS {
  __tc_init_INHERIT_DERIVEDIMPL_BUSINESS()
  {
    inherit::_tc_CCM_DerivedSessionImpl = 
    "010000000e0000004b000000010000002700000049444c3a696e68657269"
    "742f43434d5f4465726976656453657373696f6e496d706c3a312e300000"
    "1700000043434d5f4465726976656453657373696f6e496d706c00";
  }

  ~__tc_init_INHERIT_DERIVEDIMPL_BUSINESS()
  {
  }
};

static __tc_init_INHERIT_DERIVEDIMPL_BUSINESS __init_INHERIT_DERIVEDIMPL_BUSINESS;

