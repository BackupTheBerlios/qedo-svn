/*
 *  MICO --- an Open Source CORBA implementation
 *  Copyright (c) 1997-2003 by The Mico Team
 *
 *  This file was automatically generated. DO NOT EDIT!
 */

#include <CORBA.h>
#include <mico/throw.h>

#ifndef __INHERIT_DERIVEDIMPL_BUSINESS_H__
#define __INHERIT_DERIVEDIMPL_BUSINESS_H__


#ifdef _WIN32
// If you compile this file and would like to link
// it into the DLL, then please define ``BUILD_INHERIT_DERIVEDIMPL_DLL'' symbol
// on your C++ compiler command-line.
// Depending on your compiler, you can use either
// ``-DBUILD_INHERIT_DERIVEDIMPL_DLL'' or ``/DBUILD_INHERIT_DERIVEDIMPL_DLL'' parameter
#ifdef BUILD_INHERIT_DERIVEDIMPL_DLL
// Please do not forget to use gendef tool to correctly
// export all symbols from the resulting object file.
// If you would like to use more common __declspec(dllexport) way,
// then please use --windows-dll-with-export <name>
// IDL compiler parameter
#define INHERIT_DERIVEDIMPL_EXPORT /**/
#else // BUILD_INHERIT_DERIVEDIMPL_DLL
#define INHERIT_DERIVEDIMPL_EXPORT __declspec(dllimport)
#endif // BUILD_INHERIT_DERIVEDIMPL_DLL
#else // _WIN32
// all other platforms
#define INHERIT_DERIVEDIMPL_EXPORT /**/
#endif // _WIN32




namespace inherit
{

class CCM_DerivedSessionImpl;
typedef CCM_DerivedSessionImpl *CCM_DerivedSessionImpl_ptr;
typedef CCM_DerivedSessionImpl_ptr CCM_DerivedSessionImplRef;
typedef ObjVar< CCM_DerivedSessionImpl > CCM_DerivedSessionImpl_var;
typedef ObjOut< CCM_DerivedSessionImpl > CCM_DerivedSessionImpl_out;

}



#include <mico/orb.h>
#include <mico/basic_seq.h>
#include <mico/valuetype.h>
#include <mico/ir_base.h>
#include <mico/ir.h>
#include <mico/policy.h>
#include <mico/current.h>
#include <mico/typecode_seq.h>
#include <mico/pi.h>
#include <mico/poa.h>
#include <mico/ioptypes.h>
#include <qedo_mico.h>
#include <Components.h>
#include <CORBADepends.h>
#include <StreamComponents.h>
#include <inherit_DerivedImpl_EQUIVALENT.h>
#include <inherit_DerivedImpl_LOCAL.h>



namespace inherit
{


/*
 * Base class and common definitions for local interface CCM_DerivedSessionImpl
 */

class CCM_DerivedSessionImpl : 
  virtual public ::inherit::CCM_derived_component_Executor,
  virtual public ::inherit::CCM_derived_interf
{
  public:
    virtual ~CCM_DerivedSessionImpl();

    #ifdef HAVE_TYPEDEF_OVERLOAD
    typedef CCM_DerivedSessionImpl_ptr _ptr_type;
    typedef CCM_DerivedSessionImpl_var _var_type;
    #endif

    static CCM_DerivedSessionImpl_ptr _narrow( CORBA::Object_ptr obj );
    static CCM_DerivedSessionImpl_ptr _narrow( CORBA::AbstractBase_ptr obj );
    static CCM_DerivedSessionImpl_ptr _duplicate( CCM_DerivedSessionImpl_ptr _obj )
    {
      CORBA::Object::_duplicate (_obj);
      return _obj;
    }

    static CCM_DerivedSessionImpl_ptr _nil()
    {
      return 0;
    }

    virtual void *_narrow_helper( const char *repoid );

  protected:
    CCM_DerivedSessionImpl() {};
  private:
    CCM_DerivedSessionImpl( const CCM_DerivedSessionImpl& );
    void operator=( const CCM_DerivedSessionImpl& );
};

extern INHERIT_DERIVEDIMPL_EXPORT CORBA::TypeCodeConst _tc_CCM_DerivedSessionImpl;


}


#ifndef MICO_CONF_NO_POA



namespace POA_inherit
{

}


#endif // MICO_CONF_NO_POA

#endif
