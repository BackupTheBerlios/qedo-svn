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

%{ KC_UNPARSE
#include "symtab.h"
#include "resolve_symtab.h"
#include "error.h"
%}

%uview (symtab_ref); /* resolve identifiers in complex situations */

%{ HEADER
#include "unpk.h"
struct symtab_ref_class : symtab_ref_baseclass {
  idl_identifier component_scope;
  idl_identifier home_ident;
  bool fixed;
  idl_name executor_name;
  table_item_set* current_segment_provide;
  table_item_set current_facets;
  symtab_ref_class() : component_scope(0), home_ident(0), fixed(true), 
                       current_segment_provide(0)
                       {}
};
extern symtab_ref_class my_symtab_ref;
%}

/*

Consdefinition_list(head,tail)
->[ symtab_ref :
    tail head
  ];
*/

AbstractStorageHome(AbstractStorageHomeHeader(*,type_name_v,*),defs_v)
->[ symtab_ref :
    { do_res_keys(type_name_v,defs_v); }
    defs_v
  ];

def_v=
StorageHome(StorageHomeHeader(name_v,type_name_v,*,identifier_list_v,*),defs_v)
->[ symtab_ref :
    {
      do_res_keys(type_name_v,defs_v);
      foreach(id_v; idl_identifier_list identifier_list_v) {
        definition def_1 = get_definition(id_v);
        with(def_1) {
          AbstractStorageHome(*,*) : {
            if(!def_1->direct_implements.empty()) {
              Warning("abstract storage home '%k' also implemented by '%k'\n",
                name_v,id_v,
                *(def_1->direct_implements.begin()));
            }
            def_1->direct_implements.insert(def_v);
          }
        }
      }
    }
  ];


def_v=
StorageType(StorageTypeHeader(name_v,*,identifier_list_v),defs_v)
->[ symtab_ref :
    {
      table_item_list for_store_v=Niltable_item_list();
      foreach(id_v; idl_identifier_list identifier_list_v) {
        definition def_1 = get_definition(id_v);
        with(def_1) {
          AbstractStorageType(*,*) : {
            if(!def_1->direct_implements.empty()) {
              Warning("abstract storage type '%k' also implemented by '%k'\n",
                name_v,id_v,*(def_1->direct_implements.begin()));
            }
            insert_direct_implements(def_1,def_v);
            with(id_v->symtab_entry) {
              TableItem(*,*,Constable_item_lists(local_v,*)) : {
                for_store_v = concat(for_store_v,do_find_abstracts(local_v));
              }
            }
          }
        }
      }
      do_store(def_v,name_v,defs_v,for_store_v);
      do_ref_rep(def_v,name_v,defs_v);
    }
  ];

HomeExecutorBody(HomeImplDcl(ident),*,*,executor_dev,*,*,*)
->[ symtab_ref :
    {
      kc_current_view.home_ident = ident;
      with(ident->symtab_entry->def_v) {
        HomeDcl(HomeHeader(*,*,*,comp_ident,*),*) : {
          kc_current_view.component_scope = comp_ident;
        }
        }
      }
    executor_dev 
  ];

def_v=
NComponent(header_v,body_v)
->[ symtab_ref :
    { table_item_set* old = kc_current_view.current_segment_provide; }
    { kc_current_view.current_segment_provide = &$0->realized; }
    header_v body_v
    { Warning("<msg> component '%k' %d\n",header_v,realized.size()); }
    { kc_current_view.current_segment_provide = old; }
  ];

def_v=
Composition(name_v,type_flag_v,body_v)
->[ symtab_ref :
    { table_item_set* old = kc_current_view.current_segment_provide; }
    { kc_current_view.current_segment_provide = &$0->realized; }
    { kc_current_view.current_facets.clear(); }
    name_v type_flag_v body_v
    { 
      table_item_set& all =
      dynamic_cast<kc_tag_definition_NComponent&>(*kc_current_view.component_scope->symtab_entry->def_v).realized;
      table_item_set& own = kc_current_view.current_facets;
      realized.clear();

      if(options.verbose & V_REFERENCES) { 
        Warning("<msg> composition '%k' main segment implements %d/%d\n",
                name_v,all.size(),own.size());
        for_each(all.begin(),all.end(),table_item_set_printer);
      }

      std::set_difference(all.begin(),all.end(),own.begin(),own.end(),
                          inserter(realized,realized.begin()));
      if(options.verbose & V_REFERENCES) { 
        Warning("<msg> composition '%k' main segment implements(%d) :\n",
            name_v,realized.size());
        for_each(realized.begin(),realized.end(),table_item_set_printer);
      }

      component = kc_current_view.component_scope;
      assert(component);
      home = kc_current_view.home_ident;
      assert(home);

      executor_name = kc_current_view.executor_name;
      own.clear();
    }
    { kc_current_view.current_segment_provide = old; }
  ];

ExecutorDef(name_v,seg_list)
->[ symtab_ref :
    { kc_current_view.executor_name = name_v; }
    name_v seg_list
  ];

def_v=
SegmentDef(name_v,body_v)
->[ symtab_ref :
    { table_item_set* old = kc_current_view.current_segment_provide; }
    { kc_current_view.current_segment_provide = &$0->realized; }
    name_v body_v
    { kc_current_view.current_segment_provide = old; }
  ];

FacetDcl(name_list)
->[ symtab_ref :
    { res_facetdcl(name_list,kc_current_view); }
  ];

UsesDcl(*,*,name_v),
ConsumesDcl(*,name_v),
EmitsDcl(*,name_v),
PublishesDcl(*,name_v),
ProvidesDcl(*,name_v)
->[ symtab_ref :
    { kc_current_view.current_segment_provide->insert(name_v->symtab_entry); }
  ];

/* the following part computes if a type is fixed in size or not. */

def_v=
ParamDcl(*,type_v,declarator_v)
->[ symtab_ref :
    { if(def_v->flags & FIXED_SIZE_FLAG) return; }
    %uviewvar symtab_ref symtab_ref(kc_current_view);
    { symtab_ref.fixed = true; }
    type_v : symtab_ref
    { if(symtab_ref.fixed) {
        def_v->flags |= FIXED_SIZE_FLAG; 
        declarator_v->flags |= FIXED_SIZE_FLAG;
      }
    }
  ];

def_v=
NScopedName(ident_v)
->[ symtab_ref :
    { if(def_v->flags & FIXED_SIZE_FLAG) return; }
    %uviewvar symtab_ref symtab_ref(kc_current_view);
	 { if (!ident_v->symtab_entry) {
		 Error("<internal>ident '%k' has no symtab_entry\n",ident_v,ident_v);
		 abort();
		 }
	 }
    ident_v->symtab_entry : symtab_ref
    { if(symtab_ref.fixed) def_v->flags |= FIXED_SIZE_FLAG; }
    { if(!symtab_ref.fixed) kc_current_view.fixed=false; }
  ];

def_v=
TypeDeclarator(type_v,*)
->[ symtab_ref :
    { if(def_v->flags & FIXED_SIZE_FLAG) return; }
    %uviewvar symtab_ref symtab_ref(kc_current_view);
    type_v : symtab_ref
    { if(symtab_ref.fixed) def_v->flags |= FIXED_SIZE_FLAG; }
    { if(!symtab_ref.fixed) kc_current_view.fixed=false; }
  ];

def_v=
StructurType(*,body_v)
->[ symtab_ref :
    { if(def_v->flags & FIXED_SIZE_FLAG) return; }
    %uviewvar symtab_ref symtab_ref(kc_current_view);
    { symtab_ref.fixed = true; }
    body_v : symtab_ref
    { if(symtab_ref.fixed) def_v->flags |= FIXED_SIZE_FLAG; }
    { if(!symtab_ref.fixed) kc_current_view.fixed=false; }
  ];

def_v=
UnionType(*,*,case_list_v)
->[ symtab_ref :
    { if(def_v->flags & FIXED_SIZE_FLAG) return; }
    %uviewvar symtab_ref symtab_ref(kc_current_view);
    { symtab_ref.fixed = true; }
    case_list_v : symtab_ref
    { if(symtab_ref.fixed) def_v->flags |= FIXED_SIZE_FLAG; }
    { if(!symtab_ref.fixed) kc_current_view.fixed=false; }
  ];

Member(type_v,*)
->[ symtab_ref :
    type_v
  ];

Case(*,definition_v)
->[ symtab_ref :
    definition_v
  ];


SequenceType,
AnyType,
StringType,
WideStringType
->[ symtab_ref :
    { kc_current_view.fixed=false; }
  ];

TableItem
->[ symtab_ref :
    def_v
  ];

TableItemDcl
->[ symtab_ref :
    symtab_entry
  ];

%{
#include "symtab.h"
#include "error.h"
symtab_ref_class my_symtab_ref;
%}

static void
resolve_keys(
  node_flag nflag_v,
  idl_name name_1,
  declarators declarators_v, 
  idl_identifier type_v)
{
  foreach($declarator_v; declarators declarators_v) {
    SimpleDeclarator(name_v=EscapedName(cs)),
    SimpleDeclarator(name_v=Name(cs)) : {
      check_item i = CheckItem(cs);
      resolve_key(name_v,type_v);
      if(i->entry) {
          Error("state member '%k' in %k '%k' already used\n",
                name_v,name_v,nflag_v,name_1);
      }
      else {
        i->entry = name_v;
      }
    }
  }
  kc_ht_reuse(kc_ht_assigned(collisions));
}

static void
resolve_key(
  idl_name name_v,
  idl_identifier type_v)
{
  bool ok=false;
  table_item_list found_v;
  table_item item_def_v=type_v->symtab_entry;

  if(!item_def_v) {
    Error("<impl>in _resolve_key storagetype '%k' without table item\n",
          type_v,type_v);
    return;
  }

  found_v = lookup_name(name_v,item_def_v);

  foreach(item_v=TableItem(PsdlStateN(),*,*);table_item_list found_v) {
    if(!ok) {
      name_v->symtab_entry=item_v;
      ok=true;
    }
    /* XXX HB: it is posible that we see the same psdl sate member 
       twice in the inheritance so we have to check */
    else if(!(name_v->symtab_entry==item_v)){
      Error("<impl>Ooops in resolve_key\n",0);
    }
  }
  if(!ok) {
    Error("undefined state member '%k' of storagetype '%k'\n",
          name_v,name_v,type_v);
  }
}

void
do_res_keys(idl_identifier type_name_v, definition_list defs_v)
{
  foreach($key_v;definition_list defs_v) {
    KeyDcl(name_v,Nildeclarators()) : {
      /* set return type for key */
      key_v->ret_type = type_name_v;
      /* resolve state members */
      resolve_key(name_v,type_name_v);
    }
    KeyDcl(name_v,declarators_v) : {
      /* set return type for key */
      key_v->ret_type = type_name_v;
      resolve_keys(KeyN(),name_v,declarators_v,type_name_v);
    }
    FactoryDcl1(name_v,declarators_v) : {
      /* set return type for factory */
      key_v->ret_type = type_name_v;
      resolve_keys(FactoryN(),name_v,declarators_v,type_name_v);
    }
    default : {}
  }
}

static void
resolve_ref(
  definition def_v,
  idl_name name_v,
  idl_name type_v)
{
  bool ok=false;
  table_item_list found_v;
  table_item item_def_v=type_v->symtab_entry;
  if(!item_def_v) {
    Error("<impl>in resolve_ref storagetype '%k' without table item\n",
          type_v,type_v);
    return;
  }


  found_v = lookup_name(name_v,item_def_v);

  foreach(item_v=TableItem(PsdlStateN(),*,*);table_item_list found_v) {
    if(!ok) {
      if(item_v->scope == item_def_v 
        || item_v->scope->def_v->direct_implements.find(item_def_v->def_v) != 
           item_v->scope->def_v->direct_implements.end() ) {
        name_v->symtab_entry=item_v;
        /* memorize the reference representation in the state member */
        item_v->def_v->direct_implements.insert(def_v);
        ok=true;
      }
      /* the state member is not defined in our scope ore and direct
         implemented scope Error! */
      else {
        Error("state member '%k' is not defined in an direct implemented"
              " scope\n",name_v,name_v);
      }
    }
    /* XXX HB: it is posible that we see the same psdl sate member 
       twice in the inheritance so we have to check */
    else if(!(name_v->symtab_entry==item_v)){
      Error("<impl>Ooops in resolve_ref\n",0);
    }
  }
  if(!ok) {
    Error("undefined state member '%k' of storagetype '%k'\n",
          name_v,name_v,type_v);
  }
}

void
do_ref_rep(
  definition def_v,
  idl_name type_v,
  definition_list defs_v)
{
  foreach(RefRepDirective(decls_v);definition_list defs_v) {
    foreach($decl_v; declarators decls_v) {
      SimpleDeclarator(name_v=EscapedName(cs)),
      SimpleDeclarator(name_v=Name(cs)) : {
        check_item i = CheckItem(cs);
        resolve_ref(def_v,name_v,type_v);
        if(i->entry) {
            Error("state member '%k' in '%k' already used\n",
                  name_v,name_v,type_v);
        }
        else {
          i->entry = name_v;
        }
      }
    }
  }
  kc_ht_reuse(kc_ht_assigned(collisions));
}

void
res_facetdcl(idl_name_list name_list, symtab_ref_class& v)
{
  table_item component_scope = v.component_scope->symtab_entry;

  foreach(name;idl_name_list name_list) {
    with(lookup_name(name,component_scope)){
      Constable_item_list(item_v=TableItem(ProvidesDclN(),*,*),
        Niltable_item_list()) : {
        name->symtab_entry = item_v;
        v.current_segment_provide->insert(item_v);
        v.current_facets.insert(item_v);
      }
      default : {
        Error("found no facet '%k' in '%k'\n", name,name,component_scope);
      }
    }
  }
}

table_item_list
do_find_abstracts(table_item_list list_v)
{
  table_item_list result_v=Niltable_item_list();
  foreach(item_v=TableItem(PsdlStateN(),name_v,*);table_item_list list_v) {
    if(is_abstract(item_v->def_v)) {
      result_v->append(item_v);
    }
  }
  return result_v;
}

static bool
is_abstract(definition $def_v)
{
  PsdlStateDcl(*,NScopedName(idl_identifier_v),*) : {
    with(idl_identifier_v->symtab_entry) {
      TableItem(AbstractStorageTypeN(),*,*) : {
        return true;
      }
      default : { return false; }
    }
  }
  PsdlStateDcl : { return false; }
}


%{
static idl_name my_store_filter_name;
%}

static bool
my_store_filter(table_item $item_v)
{
  TableItem(*,name_v,*) : {
    if(my_store_filter_name->eq(name_v)) {
      return false;
    }
    return true;
  }
}

void
do_store(
  definition def_v,
  idl_name name_v,
  definition_list defs_v,
  table_item_list for_store_v)
{
  table_item_list result_v = for_store_v;
  foreach(StoreDirective(decl_v,*,*);definition_list defs_v) {
    with(decl_v) {
      SimpleDeclarator(name_1) : {
        my_store_filter_name=name_1;
        result_v = for_store_v->filter(my_store_filter);
      }
    }
  }
  foreach(TableItem(*,name_1,*); table_item_list result_v) {
    Error("no store directive in %k for abstract state member %k\n"
          ,name_1,name_v,name_1);
  }
}

bool
in_inh(
  definition_set& def_s,
  definition def_v)
{
  if(def_s.find(def_v) != def_s.end()) return true;
  definition_set::iterator r = def_s.begin();
  while(r != def_s.end()) {  
    if(in_inh((*r)->derived,def_v)) return true;
    r++;
  }
  return false;
}
  
void
insert_direct_implements(
  definition $abstract_type_v,
  definition type_v)
{
  AbstractStorageType(AbstractStorageTypeHeader(*,inh_list_v),*) : {
    abstract_type_v->direct_implements.insert(type_v);
    foreach(id_v;idl_identifier_list inh_list_v) {
      definition def_1 = get_definition(id_v);
      if(!in_inh(def_1->derived,type_v)) {
        insert_direct_implements(def_1,type_v);
      }
    }
  }
}

