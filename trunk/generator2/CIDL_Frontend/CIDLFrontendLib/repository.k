/*****************************************************************************/
/* Qedo - Qualitiy of Service Enabled Distributed Objects                    */
/*                                                                           */
/* Copyright (c) 2002 by the Qedo Team                                       */
/*                                                                           */
/* http://qedo.berlios.de                                                    */
/*                                                                           */
/* This file is part of Qedo Generator                                       */
/*                                                                           */
/* Qedo Generator is free software; you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* Qedo Generator is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License for more details.                              */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with Foobar; if not, write to the Free Software                     */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/*****************************************************************************/

%{
static char id[] UNUSED = "";
%}


%uview  (feed_container), // first feed all modules, interfaces, components
        (feed),  // then feed the rest
        (build), // preparation
        (any); // build any


%{ HEADER
#include <CORBA.h>
#include "IFR.h"
#include "CIDL_Extension.h"

#include "unpk.h"
#include "global.h"
#include "symtab.h"

#ifdef YYDEBUG
#define NOT_NIL(x) assert(!CORBA::is_nil(x));
#else
#define NOT_NIL(x)
#endif

struct feed_container_class : feed_container_baseclass {
  CORBA__::IRObject_ptr container;
  feed_container_class() : container(0) {}
  feed_container_class(CORBA__::IRObject_ptr cont) { container = cont; }
};

struct feed_class : feed_baseclass {
  CORBA__::IRObject_ptr container;
  feed_class() : container(0) {}
  feed_class(CORBA__::IRObject_ptr cont) { container = cont; }
};

struct build_class : build_baseclass {
  IR__::ParDescriptionSeq paradescseq;
  IR__::ExceptionDefSeq excdefseq;
  IR__::ExceptionDefSeq excdefseq2;
  IR__::ContextIdSeq contseq;
  IR__::StructMemberSeq memseq;
  IR__::UnionMemberSeq unimemseq;
  IR__::ValueDefSeq valdefseq;
  IR__::InterfaceDefSeq intdefseq;
  IR__::InitializerSeq iniseq;
  IR__::ProvidesDefSeq provseq;
  IR__::IDLType_ptr type;
  IR__::ValueDef_ptr valuetype;
  IR__::HomeDef_ptr home;
  definition def;
  int pos;
  bool flag;
  build_class() : def(0), pos(0), flag(false) {
    type = IR__::IDLType::_nil();
    valuetype = IR__::ValueDef::_nil();
    home = IR__::HomeDef::_nil();
  }
};

struct any_class : any_baseclass {
  const_expression expr;
  CORBA::Any value;
  any_class() : expr(0) {}
};
%}


%{ KC_UNPARSE
#include "repository.h"
#include <iostream>
%}

//
// ============================ Specification ===========================
//

CIDLSpecification(impo_list, def_list)
->[ feed:
    // feed implicit stuff
    { feed_implicit(); }
    
    %uviewvar feed_container my_feed_container (kc_current_view.container);
    def_list : my_feed_container
    %uviewvar feed my_feed (kc_current_view.container);
    def_list : my_feed
  ];

//
// ============================== Module =================================
//

Module(name_v,list_v)
->[ feed_container:
    %uviewvar feed_container my_feed_container;
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::ModuleDef_ptr module;
      if(CORBA::is_nil(name_v->symtab_entry->irobj)) {
        // create ModuleDef
        try {
          module = container-> create_module (get_repid(name_v),
            name_v->get_name(), "1.0");
        }
        catch (...) {
          // module reopening ?
          try {
            module = IR__::ModuleDef::_narrow (
              container->lookup (name_v->get_name ()));
            NOT_NIL(module);
          }
          catch (...) { 
            Error("Exception in creating module %k\n", name_v, name_v);
          }
        }
        name_v->symtab_entry->irobj = module;
      }
      else {
        // module reopening
        module = IR__::ModuleDef::_narrow (name_v->symtab_entry->irobj);
      }
      my_feed_container.container = module;
      irobj = module;
    }
    list_v : my_feed_container
  ]
  [ feed:
    %uviewvar feed my_feed(irobj);
    list_v : my_feed
  ];

// =========================== types ======================================

NScopedName(ident)
->[ build feed :
    { if(CORBA::is_nil(irobj)) { irobj = ident->symtab_entry->irobj; }
      if(CORBA::is_nil(irobj)) { 
        irobj = g_repository->lookup_id (get_repid_ident (ident));
      }
      NOT_NIL(irobj);
    }
  ]
  [ any :
    { ident->symtab_entry->def_v->unparse(kc_printer, kc_current_view); }
  ];

Void()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_void);
      }
    }
  ];

ObjectType()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_objref);
      }
    }
  ];

ValueBaseType()
->[build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_value_base);
      }
    }
  ];
  
AnyType()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_any);
        NOT_NIL(irobj);
      }
    }
  ];

OctetType()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_octet);
      }
    }
  ];

BooleanType()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_boolean);
      }
    }
  ]
  [ any :
    { 
      CORBA::Boolean v;
      kc_current_view.expr->value >>= CORBA::Any::to_boolean(v);
      kc_current_view.value <<= CORBA::Any::from_boolean(v);
    }
  ];

CharType()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_char);
      }
    }
  ]
  [ any :
    { 
      CORBA::Char v;
      kc_current_view.expr->value >>= CORBA::Any::to_char(v);
      kc_current_view.value <<= CORBA::Any::from_char(v);
    }
  ];

WCharType()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_wchar);
      }
    }
  ]
  [ any :
    { 
      CORBA::WChar v;
      kc_current_view.expr->value >>= CORBA::Any::to_wchar(v);
      kc_current_view.value <<= CORBA::Any::from_wchar(v);
    }
  ];

UnsignedShortInt()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_ushort);
      }
    }
  ]
  [ any : 
    { 
      CORBA::UShort v;
      kc_current_view.expr->value >>= v;
      kc_current_view.value <<= v;
    }
  ];

UnsignedLongInt()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_ulong);
      }
    }
  ]
  [ any : 
    { 
      CORBA::ULong v;
      kc_current_view.expr->value >>= v;
      kc_current_view.value <<= v;
    }
  ];

UnsignedLongLongInt()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_ulonglong);
      }
    }
  ]
  [ any : 
    { 
      CORBA::ULongLong v;
      kc_current_view.expr->value >>= v;
      kc_current_view.value <<= v;
    }
  ];

SignedShortInt()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_short);
      }
    }
  ]
  [ any : 
    { 
      CORBA::Short v;
      kc_current_view.expr->value >>= v;
      kc_current_view.value <<= v;
    }
  ];

SignedLongInt()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_long);
      }
    }
  ]
  [ any : 
    { 
      CORBA::Long v;
      kc_current_view.expr->value >>= v;
      kc_current_view.value <<= v;
    }
  ];

SignedLongLongInt()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_longlong);
      }
    }
  ]
  [ any :
    { 
      CORBA::LongLong v;
      kc_current_view.expr->value >>= v;
      kc_current_view.value <<= v;
    }
  ];

NFloat()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_float);
      }
    }
  ];

NDouble()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_double);
      }
    }
  ];

NLongDouble()
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_longdouble);
      }
    }
  ];

StringType(Nilconst_expression ())
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_string);
        NOT_NIL(irobj);
      }
    }
  ];

StringType(expr_v)
->[ build feed :
    { // TODO
    }
  ];
  
WideStringType(expr_v)
->[ build feed :
    // todo
  ];

WideStringType( Nilconst_expression() )
->[ build feed :
    { if(CORBA::is_nil(irobj)) {
        irobj = g_repository->get_primitive(IR__::pk_wstring);
        NOT_NIL(irobj);
      }
    }
  ];

// ========================= Constant ===============================

ConstDcl(def, name, expr)
->[ feed:
    %uviewvar build my_build;
    def : my_build
    expr : my_build
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::IDLType_ptr type;
      type = IR__::IDLType::_narrow(def->irobj);
      NOT_NIL(type);
      // TODO
      CORBA::Any any;
      with(def) {
        UnsignedShortInt : {}
        UnsignedLongInt : {}
        UnsignedLongLongInt : {}
        SignedShortInt : {}
        SignedLongInt : {}
        SignedLongLongInt : {}
        CharType : {}
        WCharType : {}
        BooleanType : {}
        NFloat : {}
        NDouble : {}
        NLongDouble : {}
        StringType : {}
        WideStringType : {}
        FixedPtType : {}
        NScopedName : {}
        OctetType : {}
        default : { assert(0); }
      }
      // create ConstantDef
      IR__::ConstantDef_ptr constant;
      try {
        constant = container->create_constant(get_repid(name),
          name->get_name(), "1.0", type, any);
      }
      catch (...) { Error("Exception in create constant %k\n", name, name); }
      irobj = constant;
      name->symtab_entry->irobj = constant;
    }
  ]
  [ feed_container: ];

// =========================== Struct ================================

StructurType(name_v,list_v)
->[ feed:
    %uviewvar build my_build;
    { int i = 0;
      foreach(Member(*, decls_v); definition_list list_v) {
        i += decls_v->length();
      }
      my_build.memseq.length(i);
    }
    list_v : my_build
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      // create StructDef
      IR__::StructDef_ptr str;
      try {
        str = container->create_struct(get_repid(name_v),
          name_v->get_name(), "1.0", my_build.memseq);
      }
      catch (...) {
        Error("Exception in creating struct %k\n", name_v, name_v);
      }
      irobj = str;
      name_v->symtab_entry->irobj = str;
    }
  ]
  [ feed_container: ];

// ============================= Union ==============================

UnionType(name, def, case_list)
->[ feed:
    %uviewvar build my_build;
    def : my_build
    { int i = 0;
      foreach(Case(label_list, *); idl_case_list case_list) {
        i += label_list->length();
      }
      my_build.unimemseq.length(i);
      my_build.def = def;
    }
    case_list : my_build
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::IDLType_ptr type;
      type = IR__::IDLType::_narrow(def->irobj);
      NOT_NIL(type);
      // create UnionDef
      IR__::UnionDef_ptr uni;
      try {
        uni = container->create_union(get_repid(name), name->get_name(),
          "1.0", type, my_build.unimemseq);
      }
      catch (...) { Error("Exception in creating union %k\n", name, name); }
      irobj = uni;
      name->symtab_entry->irobj = uni;
    }
  ]
  [ feed_container: ];

Case(label_list, ElementSpec(def, decl))
->[ build:
    %uviewvar build my_build;
    %uviewvar any my_any;
    def : my_build
    { IR__::IDLType_ptr type;
      type = IR__::IDLType::_narrow(def->irobj);
      NOT_NIL(type);
      my_build.type = type;
      idl_name name_v;
      with(decl) {
        ArrayDeclarator(name, arrays) : {
          arrays->unparse(kc_printer, my_build);
          name_v = name;
        }
        SimpleDeclarator(name) : { name_v = name; }
        // due to VC7 compiler making RTC1 runtime check resulting in internal compiler error
        // when name_v is uninitialized
        default : { name_v = Name(mkcasestring("garbage,please report")); }
      }
      foreach($label_v; case_label_list label_list) {
        Default : {
          IR__::UnionMember& uni =
            kc_current_view.unimemseq[kc_current_view.pos] ;
          CORBA::Any any;
          any <<= CORBA::Any::from_octet(0);
          uni.name = CORBA::string_dup(name_v->get_name());
          uni.label = any;
          uni.type_def = my_build.type;
          uni.type = my_build.type->type();
          kc_current_view.pos++;
        }
        CaseLabel(expr) : {
          IR__::UnionMember& uni =
            kc_current_view.unimemseq[kc_current_view.pos] ;
          // fill in any
          expr->unparse(kc_printer, kc_current_view);
          my_any.expr = expr;
          kc_current_view.def->unparse(kc_printer, my_any);
          uni.name = CORBA::string_dup(name_v->get_name());
          uni.label = my_any.value;
          uni.type_def = my_build.type;
          uni.type = my_build.type->type();
          kc_current_view.pos++;
        }
      }
    }
  ];

// ======================== Enum ========================================

EnumType(name, name_list)
->[ feed:
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::EnumMemberSeq enumemseq;
      enumemseq.length(name_list->length());

      CORBA::ULong i = 0;
      foreach(name2; idl_name_list name_list) {
	enumemseq[i] = name2->get_name();
	i++;
      }

     // create EnumDef
      IR__::EnumDef_ptr enu;
      try {
        enu = container->create_enum(get_repid(name), name->get_name(),
          "1.0", enumemseq);
      }
      catch (...) { Error("Exception in creating enum %k\n", name, name); }
      NOT_NIL(enu);
      irobj = enu;
      name->symtab_entry->irobj = enu;

      // DynAnyFactory
      DynamicAny::DynAnyFactory_var factory;
      try {
	CORBA::Object_var factory_obj;
	factory_obj = g_orb -> resolve_initial_references ( "DynAnyFactory" );
        factory = DynamicAny::DynAnyFactory::_narrow ( factory_obj );
      }
      catch ( ... ) {
	Error("Exception in getting DynAnyFactory %k\n", name, name);
      }
      DynamicAny::DynAny_var dyn_any =
	factory -> create_dyn_any_from_type_code ( enu -> type() );
      DynamicAny::DynEnum_var dyn_enum = DynamicAny::DynEnum::_narrow ( dyn_any );

      i = 0;
      foreach(name2; idl_name_list name_list) {
        dyn_enum -> set_as_ulong ( i );
	name2->symtab_entry->value = *(dyn_enum -> to_any());
	i++;
      }
    }
  ]
  [ any :
    { kc_current_view.value = kc_current_view.expr->value; }
  ]
  [ feed_container: ];
  
// ========================== Sequence ==================================

SequenceType(def, expr)
->[ feed:
    %uviewvar build my_build;
    def : my_build
    expr : my_build
    { IR__::IDLType_ptr type;
      type = IR__::IDLType::_narrow(def->irobj);
      NOT_NIL(type);
      IR__::SequenceDef_ptr seq;
      CORBA::ULong value;
      expr->value >>= value;
      // create SequenceDef
      try {
        seq = g_repository->create_sequence(value, type);
      }
      catch (CORBA::Exception& ex) {
        std::cerr << "Exception in creating sequence : " << ex << std::endl;
      }
      irobj = seq;
    }
  ]
  [ build feed_container: ];

// ======================== typedef ===================================

TypeDeclarator(def, dcls)
->[ feed:
    %uviewvar feed my_feed;
    def : my_feed
    %uviewvar build my_build;
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::IDLType_ptr type;
      type = IR__::IDLType::_narrow(def->irobj);
      NOT_NIL(type);
      IR__::AliasDef_ptr alias;
      foreach($dcl; declarators dcls) {
        ArrayDeclarator(name, arrays) : {
          my_build.type = type;
          arrays->unparse(kc_printer, my_build);
          // create AliasDef
          try {
            alias = container->create_alias(get_repid(name), name->get_name(),
              "1.0", my_build.type);
          }
          catch (...) {
            Error("Exception in creating typedef %k\n", name, name);
          }
          irobj = alias;
          name->symtab_entry->irobj = alias;
        }
        SimpleDeclarator(name) : {
          // create AliasDef
          try {
            alias = container->create_alias(get_repid(name), name->get_name(),
              "1.0", type);
          }
          catch (...) {
            Error("Exception in creating typedef %k\n", name, name);
          }
          irobj = alias;
          name->symtab_entry->irobj = alias;
        }
      }
    }
  ]
  [ feed_container: ];

// ======================== Value Type ================================

AbstractValueTypeFwdDcl(name)
->[ feed feed_container: ];

ValueTypeFwdDcl(name)
->[ feed feed_container: ];

AbstractValueType(ValueHeader(flag_v, name, inh), def_list),
ValueType(ValueHeader(flag_v, name, inh), def_list)
->[ feed:
    %uviewvar feed my_feed;
	%uviewvar build my_build;
    { my_feed.container = irobj;
	  int i = 0;
      foreach($def; definition_list def_list) {
        FactoryDcl : { i++; }
        default : { def->unparse(kc_printer, my_feed); }
      }
      my_build.iniseq.length(i);
      foreach($def; definition_list def_list) {
        FactoryDcl : { def->unparse(kc_printer, my_build); }
        default : {}
      }
      IR__::ValueDef_ptr valdef;
      valdef = IR__::ValueDef::_narrow (irobj);
      NOT_NIL(valdef);
      // insert proper initializer seq
      valdef->initializers (my_build.iniseq);
    }
  ]
  [ feed_container:
    %uviewvar build my_build;
    inh : my_build
    {  
      IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      // initializer seq priliminarily empty (no types resolves so far)
      IR__::InitializerSeq iniseq;
      // determine custom marshal
      bool cust;
      with(flag_v) {
        CustomFlag : { cust = true; }
        default : { cust = false; }
      }
      // determine abstract
      bool abstr;
      with(this) {
        AbstractValueType : { abstr = true; }
        ValueType, EventType : { abstr = false; }
      }
      // create ValueDef
      IR__::ValueDef_ptr value;
      try {
        value = container->create_value(get_repid(name), name->get_name(),
          "1.0", cust, abstr, my_build.valuetype, my_build.flag,
          my_build.valdefseq, my_build.intdefseq, iniseq);
      }
      catch (...) {
        Error("Exception in creating value %k\n", name, name);
      }
      irobj = value;
      name->symtab_entry->irobj = value;
    }
  ];

EventType(EventTypeHeader(flag_v, name, inh), def_list)
->[ feed:
    %uviewvar feed my_feed;
	%uviewvar build my_build;
    { my_feed.container = irobj;
	  int i = 0;
      foreach($def; definition_list def_list) {
        FactoryDcl : { i++; }
        default : { def->unparse(kc_printer, my_feed); }
      }
      my_build.iniseq.length(i);
      foreach($def; definition_list def_list) {
        FactoryDcl : { def->unparse(kc_printer, my_build); }
        default : {}
      }
      IR__::EventDef_ptr eventdef;
      eventdef = IR__::EventDef::_narrow (irobj);
      NOT_NIL(eventdef);
      // insert proper initializer seq
      eventdef->initializers (my_build.iniseq);
    }
  ]
  [ feed_container:
    %uviewvar build my_build;
    inh : my_build
    {  
      IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      // initializer seq priliminarily empty (no types resolves so far)
      IR__::InitializerSeq iniseq;
      // determine custom marshal
      bool cust;
      with(flag_v) {
        CustomFlag : { cust = true; }
        default : { cust = false; }
      }
      // determine abstract
      bool abstr;
      with(this) {
        EventType : { abstr = false; }
      }
      // create EventDef
      IR__::EventDef_ptr event;
      try {
        event = container->create_event(get_repid(name), name->get_name(),
          "1.0", cust, abstr, my_build.valuetype, my_build.flag,
          my_build.valdefseq, my_build.intdefseq, iniseq);
      }
      catch (...) {
        Error("Exception in creating value %k\n", name, name);
      }
      irobj = event;
      name->symtab_entry->irobj = event;
    }
  ];

ValueInheritanceSpec(trunc, ident_list, ident_list2)
->[ build:
    { // determine truncatable
      with(trunc) {
        TruncatableFlag : { kc_current_view.flag = true; }
        default : { kc_current_view.flag = false; }
      }
      int i = 0;
	  int j = 0;
      IR__::ValueDef_ptr val;
      // determine nonabstract base value type and list of abstract bases
      foreach(ident; idl_identifier_list ident_list) {
        if(!i) {
          // if not abstract, the first element is the base value type
          with(ident->symtab_entry->def_v) {
            ValueType : {
              val = IR__::ValueDef::_narrow(ident->symtab_entry->irobj);
              NOT_NIL(val);
              kc_current_view.valuetype = val;
              kc_current_view.valdefseq.length(ident_list->length()-1);
			  j = 1;
            }
            AbstractValueType : {
              kc_current_view.valuetype = IR__::ValueDef::_nil();
              kc_current_view.valdefseq.length(ident_list->length());
              val = IR__::ValueDef::_narrow(ident->symtab_entry->irobj);
              NOT_NIL(val);
              kc_current_view.valdefseq[0] = val;
            }
            default : { assert(0); }
          }
        }
        else {
          val = IR__::ValueDef::_narrow(ident->symtab_entry->irobj);
          NOT_NIL(val);
          kc_current_view.valdefseq[i-j] = val;
        }
        i++;
      }
      kc_current_view.intdefseq.length(ident_list2->length());
      i = 0;
      IR__::InterfaceDef_ptr interface_ptr;
      // determine supported interfaces
      foreach(ident; idl_identifier_list ident_list2) {
        interface_ptr = IR__::InterfaceDef::_narrow(ident->symtab_entry->irobj);
        NOT_NIL(interface_ptr);
        kc_current_view.intdefseq[i] = interface_ptr;
        i++;
      }
    }
  ];

FactoryDcl(name, para_dcls, attr_raise)
->[ build:
    %uviewvar build my_build;
    { my_build.paradescseq.length(para_dcls->length()); }
    para_dcls : my_build
    {
      kc_current_view.memseq.length(para_dcls->length());
      for(int i = 0; i < para_dcls->length(); i++) {
        kc_current_view.memseq[i].name = my_build.paradescseq[i].name;
        kc_current_view.memseq[i].type = my_build.paradescseq[i].type;
        kc_current_view.memseq[i].type_def = my_build.paradescseq[i].type_def;
      }
      kc_current_view.iniseq[kc_current_view.pos].members = 
        kc_current_view.memseq;
      kc_current_view.iniseq[kc_current_view.pos].name = name->get_name();
      kc_current_view.pos++;
    }
  ];
  
ValueBox(name,type_v)
->[ feed:
  ]
  [ feed_container:
    %uviewvar build my_build;
    type_v : my_build
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::IDLType_ptr type;
      type = IR__::IDLType::_narrow(type_v->irobj);
      NOT_NIL(type);
      // create ValueBoxDef
      IR__::ValueBoxDef_ptr valbox;
      try {
        valbox = container->create_value_box(get_repid(name),
          name->get_name(), "1.0", type);
      }
      catch (...) {
        Error("Exception in creating valuebox %k\n", name, name);
      }
      irobj = valbox;
      name->symtab_entry->irobj = valbox;
    }
  ];

StateMember(flag_v, def_v, dcls)
->[ feed:
    %uviewvar build my_build;
    %uviewvar feed my_feed;
    def_v : my_feed
    { IR__::ValueDef_ptr container;
      container = IR__::ValueDef::_narrow(kc_current_view.container);
      NOT_NIL(container);
      // determine visibility
      CORBA__::Visibility visi;
      with(flag_v) {
        PublicFlag : { visi = CORBA__::PUBLIC_MEMBER; }
        PrivateFlag : { visi = CORBA__::PRIVATE_MEMBER; }
        default : { assert(0); }
      }
      IR__::IDLType_ptr type_def;
      type_def = IR__::IDLType::_narrow(def_v->irobj);
      NOT_NIL(type_def);
      IR__::ValueMemberDef_ptr valmem;
      foreach($decl_v; declarators dcls) {
        ArrayDeclarator(name, array_list) : {
          my_build.type = type_def;
          array_list->unparse(kc_printer, my_build);
          // create ValueMemberDef
          try {
            valmem = container->create_value_member(get_repid(name),
              name->get_name(), "1.0", my_build.type, visi);
          }
          catch (CORBA::Exception& ex) {
            Error("Exception %s in creating valuemember %k\n", name, ex._name(), name);
          }
          name->symtab_entry->irobj = valmem;
        }
        SimpleDeclarator(name) : {
          // create ValueMemberDef
          try {
            valmem = container->create_value_member(get_repid(name),
              name->get_name(), "1.0", type_def, visi);
          }
          catch (CORBA::Exception& ex) {
            Error("Exception %s in creating valuemember %k\n", name, ex._name(), name);
          }
          name->symtab_entry->irobj = valmem;
        }
      }
    }
  ]
  [ build :
  ];

// ================================ Home ===============================

HomeDcl(home_head=HomeHeader(name, base, ident_list, comp, key), def_list)
->[ feed:
    %uviewvar feed my_feed (irobj);
    def_list : my_feed
  ]
  [ feed_container:
    { IR__::InterfaceDefSeq supports;
      supports.length(ident_list->length());
      int i = 0;
      IR__::InterfaceDef_ptr interface_ptr;
      foreach (id; idl_identifier_list ident_list) {
        interface_ptr = IR__::InterfaceDef::_narrow(id->symtab_entry->irobj);
        NOT_NIL(interface_ptr);
        supports[i] = interface_ptr;
        i++;
      }
      IR__::HomeDef_ptr basehome;
      with(base) {
        NilIdentifier() : { basehome = IR__::HomeDef::_nil(); }
        default : {
          basehome = IR__::HomeDef::_narrow(base->symtab_entry->irobj);
          NOT_NIL(basehome);
        }
      }
      IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(comp->symtab_entry->irobj);
      NOT_NIL(component_ptr);
      IR__::ValueDef_ptr value;
      with(key) {
        NilIdentifier() : { value = IR__::ValueDef::_nil(); }
        default : {
          value = IR__::ValueDef::_narrow(key->symtab_entry->irobj);
          NOT_NIL(value);
        }
      }
      // create HomeDef
      IR__::HomeDef_ptr home;
      IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      try {
        home = container->create_home(get_repid(name), name->get_name(),
          "1.0", basehome, component_ptr, supports, value);
      }
      catch (...) {
        Error("Exception in creating home %k\n", name, name);
      }
      irobj = home;
    }
  ];

// ========================= Component ====================================

ComponentFwdDcl(name)
->[ feed feed_container: ];

NComponent(ComponentHeader(name, ident, ident_list), def_list)
->[ feed:
    %uviewvar feed my_feed (irobj);
    def_list : my_feed
  ]
  [ feed_container:
    { IR__::InterfaceDefSeq supports;
      supports.length(ident_list->length());
      int i = 0;
      IR__::InterfaceDef_ptr interface_ptr;
      foreach (id; idl_identifier_list ident_list) {
        interface_ptr = IR__::InterfaceDef::_narrow(id->symtab_entry->irobj);
        NOT_NIL(interface_ptr);
        supports[i] = interface_ptr;
        i++;
      }
      IR__::ComponentDef_ptr basecomp;
      with(ident) {
        NilIdentifier : { basecomp = IR__::ComponentDef::_nil(); }
        default : {
          basecomp = IR__::ComponentDef::_narrow(ident->symtab_entry->irobj);
          NOT_NIL(basecomp);
        }
      }
      // create ComponentDef
      IR__::ComponentDef_ptr component_ptr;
      IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      try {
        component_ptr = container->create_component(get_repid(name),
          name->get_name(), "1.0", basecomp, supports);
      }
      catch (CORBA::Exception& ex) {
        Error("Exception %s in creating valuemember %k\n", name, ex._name(), name);
      }
      irobj = component_ptr;
      name->symtab_entry->irobj = component_ptr;
    }
  ];
  
ProvidesDcl(definition_v, name)
->[ feed:
    %uviewvar build my_build;
    definition_v : my_build
    { IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::InterfaceDef_ptr interface_ptr;
      interface_ptr = IR__::InterfaceDef::_narrow(definition_v->irobj);
      NOT_NIL(interface_ptr);
      IR__::ProvidesDef_ptr provides;
      // create ProvidesDef
      try {
        provides = component_ptr->create_provides(get_repid(name),
          name->get_name(), "1.0", interface_ptr);
      }
      catch (...) {
        Error("Exception in creating provides %k\n", name, name);
      }
      irobj = provides;
      name->symtab_entry->irobj = provides;
    }
  ];

UsesDcl(flag_v, definition_v, name)
->[ feed:
    %uviewvar build my_build;
    definition_v : my_build
    { IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::InterfaceDef_ptr interface_ptr;
      interface_ptr = IR__::InterfaceDef::_narrow(definition_v->irobj);
      NOT_NIL(interface_ptr);
      IR__::UsesDef_ptr uses;
      bool mult = false;
      with(flag_v) {
        MultipleFlag : { mult = true; }
        default : {}
      }
      // create UsesDef
      try {
        uses = component_ptr->create_uses(get_repid(name),
          name->get_name(), "1.0", interface_ptr, mult);
      }
      catch (...) {
        Error("Exception in creating uses %k\n", name, name);
      }
      irobj = uses;
    }
  ];
  
EmitsDcl(ident, name)
->[ feed:
    { IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::EventDef_ptr event;
      event = IR__::EventDef::_narrow(ident->symtab_entry->irobj);
      NOT_NIL(event);
      IR__::EmitsDef_ptr emits;
      // create EmitsDef
      try {
        emits = component_ptr->create_emits(get_repid(name),
          name->get_name(), "1.0", event);
      }
      catch (...) {
        Error("Exception in creating emits %k\n", name, name);
      }
      irobj = emits;
    }
  ];

PublishesDcl(ident, name)
->[ feed:
    { IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::EventDef_ptr event;
      event = IR__::EventDef::_narrow(ident->symtab_entry->irobj);
      NOT_NIL(event);
      IR__::PublishesDef_ptr publishes;
      // create PublishesDef
      try {
        publishes = component_ptr->create_publishes(get_repid(name),
          name->get_name(), "1.0", event);
      }
      catch (...) {
        Error("Exception in creating publishes %k\n", name, name);
      }
      irobj = publishes;
    }
  ];
  
ConsumesDcl(ident, name)
->[ feed:
    { IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::EventDef_ptr event;
      event = IR__::EventDef::_narrow(ident->symtab_entry->irobj);
      NOT_NIL(event);
      IR__::ConsumesDef_ptr consumes;
      // create ConsumesDef
      try {
        consumes = component_ptr->create_consumes(get_repid(name),
          name->get_name(), "1.0", event);
      }
      catch (...) {
        Error("Exception in creating consumes %k\n", name, name);
      }
      irobj = consumes;
    }
  ];

StreamTypeDcl(name)
->[ feed_container:
	{
      IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      // create StreamTYPE
      IR__::StreamTypeDef_ptr stream_type;
      try {
        stream_type = container->create_stream_type(get_repid(name), name->get_name(),
          "1.0");
      }
      catch (...) {
        Error("Exception in creating streamtype %k\n", name, name);
      }
      irobj = stream_type;
      name->symtab_entry->irobj = stream_type;
	}
];

SiSoDcl(ident, name)
->[ feed:
	{ IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::StreamTypeDef_ptr stream_type;
	  stream_type = IR__::StreamTypeDef::_narrow(ident->symtab_entry->irobj);
	  NOT_NIL(stream_type);
	  IR__::SiSoDef_ptr siso;
	  try {
		siso = component_ptr->create_siso(get_repid(name), name->get_name(), "1.0", stream_type);
	  }
	  catch (...) {
	    Error("Exception in creating siso %k\n", name, name);
	  }
	  irobj = siso;
	}
];
SinkDcl(ident, name)
->[ feed:
	{ IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::StreamTypeDef_ptr stream_type;
	  stream_type = IR__::StreamTypeDef::_narrow(ident->symtab_entry->irobj);
	  NOT_NIL(stream_type);
	  IR__::SinkDef_ptr sink;
	  try {
		sink = component_ptr->create_sink(get_repid(name), name->get_name(), "1.0", stream_type);
	  }
	  catch (...) {
	    Error("Exception in creating sink %k\n", name, name);
	  }
	  irobj = sink;
	}
];
SourceDcl(ident, name)
->[ feed:
	{ IR__::ComponentDef_ptr component_ptr;
      component_ptr = IR__::ComponentDef::_narrow(kc_current_view.container);
      NOT_NIL(component_ptr);
      IR__::StreamTypeDef_ptr stream_type;
	  stream_type = IR__::StreamTypeDef::_narrow(ident->symtab_entry->irobj);
	  NOT_NIL(stream_type);
	  IR__::SourceDef_ptr source;
	  try {
		source = component_ptr->create_source(get_repid(name), name->get_name(), "1.0", stream_type);
	  }
	  catch (...) {
	    Error("Exception in creating source %k\n", name, name);
	  }
	  irobj = source;
	}
];

// ======================== Interface ==========================

InterfaceFwdDcl(abstract_v,name)
->[ feed feed_container: ];

Interface(InterfaceHeader(flag_v,name,ident_list), list_v )
->[ feed: 
    %uviewvar feed my_feed(irobj);
    list_v : my_feed
  ]
  [ feed_container:
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      bool abstr = false;
      with(flag_v) {
        AbstractFlag : { abstr = true; }
        default : {}
      }
      IR__::InterfaceDefSeq inheritance;
      inheritance.length(ident_list->length());
      IR__::InterfaceDef_ptr interface_ptr;
      int i = 0;
      foreach (ident; idl_identifier_list ident_list) {
        interface_ptr = IR__::InterfaceDef::_narrow(ident->symtab_entry->irobj);
        NOT_NIL(interface_ptr);
        inheritance[i] = interface_ptr;
        i++;
      }  
      IR__::InterfaceDef_ptr interface_ptr1;
      // create InterfaceDef
      try {
        interface_ptr1 = container-> create_interface(get_repid(name),
          name->get_name(), "1.0", inheritance, abstr);
      }
      catch (...) {
        Error("Exception in creating interface %k\n", name, name);
      }
      NOT_NIL(interface_ptr1);
      irobj = IR__::InterfaceDef::_duplicate(interface_ptr1);
      name->symtab_entry->irobj = interface_ptr1;
    }
  ];

// ======================== Factory ================================
FactoryDcl(idl_name_v, parameter_dcls_v, attr_raises_expr_v)
->[ feed:
	%uviewvar build my_build;
    // parameters
    { my_build.pos = 0; my_build.paradescseq.length(parameter_dcls_v->length()); }
    parameter_dcls_v : my_build
    // exceptions
    { my_build.pos = 0; }
    attr_raises_expr_v : my_build
    // context
    { my_build.pos = 0; }

	{
	    IR__::HomeDef_ptr home_ptr;
		home_ptr= IR__::HomeDef::_narrow(kc_current_view.container);
		home_ptr->create_factory(get_repid(idl_name_v), idl_name_v->get_name(),
            "1.0",my_build.paradescseq,my_build.excdefseq);
	}

  ];


// ======================== Finder ==================================
FinderDcl(idl_name_v, parameter_dcls_v, attr_raises_expr_v)
->[ feed:
	%uviewvar build my_build;
    // parameters
    { my_build.pos = 0; my_build.paradescseq.length(parameter_dcls_v->length()); }
    parameter_dcls_v : my_build
    // exceptions
    { my_build.pos = 0; }
    attr_raises_expr_v : my_build
    // context
    { my_build.pos = 0; }

	{
	    IR__::HomeDef_ptr home_ptr;
		home_ptr= IR__::HomeDef::_narrow(kc_current_view.container);
		home_ptr->create_finder(get_repid(idl_name_v), idl_name_v->get_name(),
            "1.0",my_build.paradescseq,my_build.excdefseq);
	}
  ];

// ======================== Operation ===============================

OpDcl( one_way_v,
       definition_v,
       name,
       params,
       attr_raises_expr_v,
       context_expr_v)
->[ feed:
    %uviewvar build my_build;
    //return type
    definition_v : my_build
    // parameters
    { my_build.pos = 0; my_build.paradescseq.length(params->length()); }
    params : my_build
    // exceptions
    { my_build.pos = 0; }
    attr_raises_expr_v : my_build
    // context
    { my_build.pos = 0; }
    context_expr_v : my_build
    {
      // operation mode
      IR__::OperationMode opmode;
      with(one_way_v) {
        OneWayFlag : { opmode = IR__::OP_ONEWAY; }
        default : { opmode = IR__::OP_NORMAL; }
      }
      IR__::InterfaceDef_ptr interface_ptr;
      interface_ptr = IR__::InterfaceDef::_narrow(kc_current_view.container);
      if(!CORBA::is_nil(interface_ptr)) {
        // create OperationDef
        try {
          interface_ptr->create_operation(get_repid(name), name->get_name(),
            "1.0", IR__::IDLType::_narrow(definition_v->irobj), opmode,
            my_build.paradescseq, my_build.excdefseq, my_build.contseq);
        }
        catch (...) {
          Error("Exception in creating operation %k\n", name, name);
        }
      }
      else {
        IR__::ValueDef_ptr valuet;
        valuet = IR__::ValueDef::_narrow(kc_current_view.container);
        NOT_NIL(valuet);
        // create OperationDef
        try {
          valuet->create_operation(get_repid(name), name->get_name(),
            "1.0", IR__::IDLType::_narrow(definition_v->irobj), opmode,
            my_build.paradescseq, my_build.excdefseq, my_build.contseq);
        }
        catch (...) {
          Error("Exception in creating operation %k\n", name, name);
        }
      }
    }
  ]
  [ build :
  ];

// ============================ Attribute ===============================

Attribute( readonly_v, type_v, decl_v)
->[ feed:
    %uviewvar build my_build;
    type_v : my_build
    { IR__::InterfaceDef_ptr interface_ptr;
      interface_ptr = IR__::InterfaceDef::_narrow(kc_current_view.container);
      NOT_NIL(interface_ptr);
      IR__::IDLType_ptr type;
      type = IR__::IDLType::_narrow(type_v->irobj);
      NOT_NIL(type);
      IR__::AttributeMode mode;
      with(readonly_v) {
        ReadOnlyFlag : { mode = IR__::ATTR_READONLY; }
        default : { mode = IR__::ATTR_NORMAL; }
      }
      with(decl_v) {
        AttrDeclarator(SimpleDeclarator(name),raise_v) : {
          raise_v->unparse(kc_printer,my_build);
          IR__::AttributeDef_ptr attr;
          // create AttributeDef
          try {
            attr = interface_ptr->create_attribute(get_repid(name),
              name->get_name(), "1.0", type, mode, my_build.excdefseq,
              my_build.excdefseq2);
          }
          catch (...) {
            Error("Exception in creating attribute %k\n", name, name);
          }
          name->symtab_entry->irobj = attr;
        }
        AttrDeclaratorList(dec_list) : {
          foreach($dec; declarators dec_list) {
            SimpleDeclarator(name) : {
              IR__::AttributeDef_ptr attr;
              // create AttributeDef
              try {
                attr = interface_ptr->create_attribute(get_repid(name),
                  name->get_name(), "1.0", type, mode, 0, 0);
              }
              catch (...) {
                Error("Exception in creating attribute %k\n", name, name);
              }
              name->symtab_entry->irobj = attr;
            }
            default : { assert(0); }
          }
        }
        default : { assert(0); }
      }
    }
  ];

// ========================== Exceptions ===============================

RaisesExpr(list_v),
GetExcepExpr(list_v)
->[ build:
    { kc_current_view.excdefseq.length(list_v->length());
      int i = 0;
      foreach(ident; idl_identifier_list list_v) {
        kc_current_view.excdefseq[i] =
          IR__::ExceptionDef::_narrow(ident->symtab_entry->irobj);
        NOT_NIL(kc_current_view.excdefseq[i]);
        i++;
      }
    }
  ];

SetExcepExpr(list_v)
->[ build:
    { kc_current_view.excdefseq2.length(list_v->length());
      int i = 0;
      foreach(ident; idl_identifier_list list_v) {
        kc_current_view.excdefseq2[i] =
          IR__::ExceptionDef::_narrow(ident->symtab_entry->irobj);
        NOT_NIL(kc_current_view.excdefseq2[i]);
        i++;
      }
    }
  ];

GetSetExcepExpr(list_1, list_2)
->[ build:
    { kc_current_view.excdefseq.length(list_1->length());
      int i = 0;
      foreach(ident; idl_identifier_list list_1) {
        kc_current_view.excdefseq[i] =
          IR__::ExceptionDef::_narrow(ident->symtab_entry->irobj);
        NOT_NIL(kc_current_view.excdefseq[i]);
        i++;
      }
      kc_current_view.excdefseq2.length(list_2->length());
      i = 0;
      foreach(ident; idl_identifier_list list_2) {
        kc_current_view.excdefseq2[i] =
          IR__::ExceptionDef::_narrow(ident->symtab_entry->irobj);
        NOT_NIL(kc_current_view.excdefseq2[i]);
        i++;
      }
    }
  ];

ExceptDcl( name, list_v )
->[ feed:
    %uviewvar build my_build;
    { int i = 0;
      foreach($mem; definition_list list_v) {
        Member(*, decls_v) : { i += decls_v->length(); }
        default : { assert(0); }
      }
      my_build.memseq.length(i);
    }
    list_v : my_build
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::ExceptionDef_ptr except;
      // create ExceptionDef
      try {
        except = container->create_exception(get_repid(name),
          name->get_name(), "1.0", my_build.memseq);
      }
      catch (...) {
        Error("Exception in creating exception %k\n", name, name);
      }
      irobj = except;
      name->symtab_entry->irobj = except;
    }
  ]
  [ feed_container: ];

// ========================== Native ==================================

NativeType(SimpleDeclarator(name))
->[ feed:
    { IR__::Container_ptr container;
      container = IR__::Container::_narrow(kc_current_view.container);
      NOT_NIL(container);
      IR__::NativeDef_ptr native;
      // create NativeDef
      try {
        native = container->create_native(get_repid(name), name->get_name(),
          "1.0");
      }
      catch (...) {
        Error("Exception in creating native %k\n", name, name);
      }
      irobj = native;
      name->symtab_entry->irobj = native;
    }
  ]
  [ feed_container: ];

// ========================== Context ====================================

ContextExpr(const_ex_list)
->[ build:
    { assert(0); }
  ];

// ============================ Members ==================================

Member(type_v, decls_v)
->[ build:
    %uviewvar feed my_feed;
    type_v : my_feed
    %uviewvar build my_build;
    { IR__::IDLType_ptr type_def;
      type_def = IR__::IDLType::_narrow(type_v->irobj);
      NOT_NIL(type_def);
      foreach($decl_v; declarators decls_v) {
        ArrayDeclarator(name_v, array_list) : {
          my_build.type = type_def;
          array_list->unparse(kc_printer, my_build);
          IR__::StructMember& mem =
            kc_current_view.memseq[kc_current_view.pos] ;
          mem.name = name_v->get_name();
          mem.type_def = my_build.type;
          mem.type = mem.type_def->type();
          kc_current_view.pos++;
        }
        SimpleDeclarator(name_v) : {
          IR__::StructMember& mem =
            kc_current_view.memseq[kc_current_view.pos] ;
          mem.name = name_v->get_name();
          mem.type_def = type_def;
          mem.type = mem.type_def->type();
          kc_current_view.pos++;
        }
      }
    }
  ];

Consfixed_array_sizes(head, tail)
->[ build:
    head
    tail
  ];

FixedArraySize(expr)
->[ build:
    expr
    { 
      IR__::ArrayDef_ptr array;
      // create ArrayDef
      CORBA::ULong value;
      expr->value >>= value;
      try {
        array = g_repository->create_array(value, kc_current_view.type);
      }
      catch (...) {
        Error("Exception in creating array\n", expr);
      }
      kc_current_view.type = array;
    }
  ];
  
// ========================= expressions =================================
  
NamedRef(ident)
->[ build:
    { value = ident->symtab_entry->value; }
  ];
  
IntegerLiteral(cs)
->[ build:
    { value <<= CORBA::LongLong(atoi(cs->name)); }
  ];

StringLiteral(cs)
->[ build:
    { value <<= cs->name; }
  ];

WideStringLiteral(cs)
->[ build:
    { value <<= cs->name; }
  ];

LIT_TRUE()
->[ build:
    { value <<= CORBA::Any::from_boolean(true); }
  ];

LIT_FALSE()
->[ build:
    { value <<= CORBA::Any::from_boolean(false); }
  ];

Add(expr1, expr2)
->[ build:
    expr1
    expr2
    { 
      CORBA::LongLong v1, v2;
      expr1->value >>= v1;
      expr2->value >>= v2;
      value <<= CORBA::LongLong(v1 + v2);
    }
  ];

Minus(expr1, expr2)
->[ build:
    expr1
    expr2
    { 
      CORBA::LongLong v1, v2;
      expr1->value >>= v1;
      expr2->value >>= v2;
      value <<= CORBA::LongLong(v1 + v2);
    }
  ];

// ========================== Parameter =================================

Consparameter_dcls(param_v, Nilparameter_dcls())
->[ build:
    param_v
  ];
  
Consparameter_dcls(param_v,tail)
->[ build:
    param_v
    { kc_current_view.pos++; }
    tail
  ];
  
ParamDcl(inout_v,definition_v,decl_v)
->[ build:
    %uviewvar build my_build;
    definition_v : my_build
    {
      const char* nam;
      with(decl_v) {
        ArrayDeclarator(name_v, *),
        SimpleDeclarator(name_v) : { nam = name_v->get_name(); }
        default : {}
      }
      IR__::ParameterMode mode;
      with(inout_v) {
        InFlag : { mode = IR__::PARAM_IN; }
        InOutFlag : { mode = IR__::PARAM_INOUT; }
        OutFlag : { mode = IR__::PARAM_OUT; }
        default : {}
      }
      IR__::ParameterDescription& desc =
        kc_current_view.paradescseq[kc_current_view.pos] ;
      desc.name = CORBA::string_dup(nam);
      desc.type_def = IR__::IDLType::_narrow(definition_v->irobj);
      desc.type = desc.type_def->type();
      desc.mode = mode;
    }
  ];
      
//
// =========================== Composition ==============================
//

Composition(name, flag_v, compo_body)
->[ feed :
    %uviewvar feed my_feed;
    %uviewvar build my_build;
    compo_body : my_build
    {
      // determine lifecycle
      CIDL::LifecycleCategory lifecycle;
      with(flag_v) {
        EntityFlag : { lifecycle = CIDL::lc_Entity; }
        ProcessFlag : { lifecycle = CIDL::lc_Process; }
        ServiceFlag : { lifecycle = CIDL::lc_Service; }
        SessionFlag : { lifecycle = CIDL::lc_Session; }
      }
      CIDL::CompositionDef_ptr composition;
      CIDL::CIDLRepository_ptr container = g_repository;
      // create CompositionDef
      try {
        composition = container-> create_composition(get_repid(name),
          name->get_name(), "1.0", lifecycle, my_build.home);
      }
      catch (...) {
        Error("Exception in creating composition %k\n", name, name);
      }
      NOT_NIL(composition);
      irobj = composition;
      name->symtab_entry->irobj = composition;
      my_feed.container = composition;
    }
    compo_body : my_feed
  ]
  [ feed_container : ];

CompositionBody(catalogs, homex_def, proxy_home)
->[ build feed :
    /* catalogs */
    homex_def
    /* proxy_home */
  ];

//
// ============================ HomeExecutor =============================
//

HomeExecutorDef(name, homex_body)
->[ feed :
    %uviewvar feed my_feed; 
    {
      CIDL::CompositionDef_ptr container;
      container = CIDL::CompositionDef::_narrow (kc_current_view.container);
      CIDL::HomeExecutorDef_ptr homeexec;
      // create HomeExecutorDef
      try {
        homeexec = container-> create_home_executor (get_repid(name),
          name->get_name(), "1.0");
      }
      catch (...) {
        Error("Exception in creating home executor %k\n", name, name);
      }
      NOT_NIL(homeexec);
      irobj = homeexec;
      name->symtab_entry->irobj = homeexec;
      // enter executor
      with(homex_body) {
        HomeExecutorBody(*,*,*,exec,*,*,*) : {
          exec->unparse (kc_printer, kc_current_view);
        }
      }
      my_feed.container = homeexec;
    }
    homex_body : my_feed
  ]
  [ build :
    homex_body
  ]
  [ feed_container : ];

HomeExecutorBody(HomeImplDcl(ident), *, *, exec, *, *, def)
->[ build :
    { kc_current_view.home = IR__::HomeDef::_narrow (
        ident->symtab_entry->irobj);
      if(CORBA::is_nil(kc_current_view.home)) { 
        kc_current_view.home = IR__::HomeDef::_narrow (
          g_repository->lookup_id (get_repid_ident (ident)));
      }
      NOT_NIL(kc_current_view.home);
    }
  ]
  [ feed :
    def
  ];

AbstractSpec(name_list)
->[ feed :
  ];
  
//
// =========================== Executor ==================================
//

ExecutorDef(name, def_list)
->[ feed :
    %uviewvar feed my_feed;
    {
      CIDL::CompositionDef_ptr container;
      container = CIDL::CompositionDef::_narrow (kc_current_view.container);
      CIDL::ExecutorDef_ptr exec;
      // create ExecutorDef
      try {
        exec = container-> create_executor (get_repid(name),
          name->get_name(), "1.0");
      }
      catch (...) {
        Error("Exception in creating executor %k\n", name, name);
      }
      NOT_NIL(exec);
      irobj = exec;
      name->symtab_entry->irobj = exec;
      my_feed.container = exec;
    }
    def_list : my_feed
  ]
  [ build :
    def_list
  ];

FeatureDelegationSpec(def_list)
->[ feed :
    /* TODO */
  ]
  [ build :
    /* TODO */
  ];

//
// ============================ Segment ===================================
//

SegmentDef(name, def_list)
->[ feed :
    %uviewvar build my_build;
    {
      // determine number of provided facets
      int count = 0;
      foreach($def; definition_list def_list) {
        FacetDcl(name_list) : { count += name_list->length (); }
      }
      my_build.provseq.length (count);
    }
    def_list : my_build
    {
      CIDL::ExecutorDef_ptr container;
      container = CIDL::ExecutorDef::_narrow (kc_current_view.container);
      CIDL::SegmentDef_ptr seg;
      // create SegmentDef
      try {
        seg = container-> create_segment (get_repid(name),
          name->get_name(), "1.0", my_build.provseq);
      }
      catch (...) {
        Error("Exception in creating segment %k\n", name, name);
      }
      NOT_NIL(seg);
      irobj = seg;
      name->symtab_entry->irobj = seg;
    }
  ]
  [ feed_container : ];

SegmentPersistenceDcl(ash_name)
->[ build :
    /* TODO */
  ];

FacetDcl(name_list)
->[ build :
    {
      IR__::ProvidesDef_ptr provdef;
      foreach(name; idl_name_list name_list) {
        provdef = IR__::ProvidesDef::_narrow (name->symtab_entry->irobj);
        NOT_NIL(provdef);
        kc_current_view.provseq[kc_current_view.pos] = provdef;
        kc_current_view.pos++;
      }
    }
  ];

//
// =========================== functions ================================
//


static void
scope_of(table_item $item_v, char* buff)
{
  TableItem(*,EscapedName(cs),*),
  TableItem(*,Name(cs),*) : {
    if(item_v->scope) {
      scope_of(item_v->scope,buff);
    }
    if(strcmp(cs->name,"")) {
      strcat(buff,cs->name);
      strcat(buff,"/");
    }
  }
}

void
feed_implicit()
{
  // feed implicit stuff
  idl_name tc_name_v = Name(mkcasestring("TypeCode"));
  idl_name corba_name_v = Name(mkcasestring("CORBA"));
  idl_identifier ident = GlobalName(Considl_name_list(tc_name_v,
    Considl_name_list(corba_name_v, Nilidl_name_list())));
  resolve_name(ident,the_InterfaceN);
  ident->symtab_entry->irobj = g_repository->get_primitive(IR__::pk_TypeCode);
}
