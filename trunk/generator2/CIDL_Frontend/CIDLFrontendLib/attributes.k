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

// This file is shared between differnt tools.
// If you introduce new attributes pleas capsule tool specific 
// attributes with an #IF <MAKEFILE-DEFINE> .... #ENDIF
// The MAKEFILE-DEFINE should be set in the CPP call for kc++

%{ KC_TYPES_HEADER
#ifdef _MSC_VER
#pragma warning ( disable:4786 )
#include <CRTDBG.H>
#define TRACE3(sz,p1,p2,p3) _RPT3(_CRT_ERROR,sz,p1,p2,p3)
#define TRACE2(sz,p1,p2) _RPT2(_CRT_ERROR,sz,p1,p2)
#define TRACE printf
#define AfxAssertFailedLine(sz,p1) 1
#define AfxDebugBreak() _CrtDbgBreak()
#define stricmp _stricmp
#endif

/* VC++6 is not able to handle delete on pointers to const types */
#if defined(_MSC_VER) && (_MSC_VER<1300)
#pragma warning ( disable:4291 )
#include <new>
inline void operator delete [] (void const *p) throw()
{ operator delete(const_cast<void*>(p)); }

inline void operator delete (void const *p) throw()
{ operator delete(const_cast<void*>(p)); }

inline void operator delete [] (void const *p,const std::nothrow_t&)
{ operator delete(const_cast<void*>(p)); }

inline void operator delete (void const *p, const std::nothrow_t&)
{ operator delete(const_cast<void*>(p)); }
#endif

#include <set>
#include <algorithm>
#include <string>
typedef std::set<definition> definition_set;
typedef std::set<table_item> table_item_set;
typedef std::string my_kc_string;

struct table_item_set_printer {
  table_item_set_printer(uview _p) : p(_p) {}
  uview p;
  void operator() (const table_item&);
};

extern table_item_set_printer table_item_set_printer;

#define FIXED_SIZE_FLAG 0x1
%}

%{
static char id[] UNUSED = "$Id: attributes.k,v 1.3 2003/05/14 14:55:41 boehme Exp $";
%}

/*********************  Symbol table *********************/

name_scope:
      NameScope()
    ;

table_item:
      TableItem( node_flag idl_name table_item_lists )
    | TableItemDcl( node_flag idl_name )
    ;
      
table_item_list: list table_item
    ;

table_item_lists: list table_item_list
    ;

node_flag:
      InterfaceN()
    | ModuleN()
    | CatalogN()
    | StorageTypeN()
    | StorageHomeN()
    | AbstractStorageTypeN()
    | AbstractStorageHomeN()
	| EventTypeN()
    | ValueTypeN()
    | ValueBoxN()
    | OpN()
    | TypeN()
    | ExceptionN()
    | ConstantN()
    | ProvidesN()
    | PsdlStateN()
    | KeyN()
    | FactoryN()
    | FinderN()
    | ElementN()
    | ComponentN()
    | HomeN()
    | SegmentN()
    | ExecutorN()
    | HomeExecutorN()
    | CompositionN()
    | FacetN()
    | NilN()
    | CatalogLabelN()
    | ProvidesDclN()
    | UsesDclN()
    | EmitsDclN()
    | PublishesDclN()
    | ConsumesDclN()
	| SinkN()
	| SourceN()
	| SiSoN()
	| StreamTypeN()
	  ;

idl_name : {
  table_item symtab_entry=0;
  nocasestring nc=0;
  casestring filename=0;
  integer line=0;
  /* no code for included cidl */
  bool code=false;
};

const char*
idl_name::get_name() {
  with(this) {
    Name(cs),
    EscapedName(cs) : {
      return cs->name;
    }
  }
}

idl_identifier : {
  table_item symtab_entry=0;
};

const char*
idl_identifier::get_name() {
  return symtab_entry->get_name();
}

table_item : {
  /* for forward declaration */ 
  table_item symtab_entry=0;
  definition def_v=0;
  /* defining scope */ 
  table_item scope=0;
  /* used type names in that scope */ 
  table_item_list used_list=0;
};

const char*
table_item::get_name() {
  with(this) {
    TableItem(*, name_v, *),
    TableItemDcl(*, name_v) : { return name_v->get_name(); }
  }
}

definition : {
  int flags=0;
  idl_identifier ret_type=0;
  /* for psdl types the definition which direct implements
     the type. for state mebers it points to the ref rep wich
     referes to that state meber. */
  definition_set direct_implements;
  /* contains all derived types */
  definition_set derived;
  /* contains the prefix for the definition */
  my_kc_string prefix;
};

/* contains all provides */
%member table_item_set NComponent::realized;
/* contains all facets implemented by the main segment */
%member table_item_set Composition::realized;
/* contains all facets implemented by this segment */
%member table_item_set SegmentDef::realized;
/* contains the name of the component */
%member idl_identifier Composition::component;
/* contains the name of the home */
%member idl_identifier Composition::home;
/* contains the name of executor of the component */
%member idl_name Composition::executor_name;

%{
#include "printer.h"
void
table_item_set_printer::operator () (const table_item& item)
{
  item->unparse(printer1,p);
  printer1("\n",p);
}

struct table_item_set_printer table_item_set_printer(print_node);
%}
