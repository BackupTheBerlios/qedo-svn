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
#include "lexana.h"
#include "unpk.h"
#include "printer.h"
#include "error.h"
#include "util.h"

static node_flag node_flag_filter_flag=0;
static node_flag *node_flag_filter_flag_n=0;
static int node_flag_filter_flag_nr=0;
table_item_list symtab = 0;
table_item symtab_scope = 0;
table_item current_scope = 0;
table_item_list current_scope_list = 0;
table_item_list current_scope_used_list = 0;
table_item_list scope_stack = 0;
idl_name last_scope_name = 0;
node_flag last_scope_type = 0;
%}

static void
init_implicit()
{
  idl_name tc_name_v = Name(mkcasestring("TypeCode"));
  tc_name_v->nc=mknocasestring("TypeCode");
  idl_identifier_list inh_v = Nilidl_identifier_list();
  definition tc_v = Interface(
                      InterfaceHeader(NilFlag(),tc_name_v,inh_v),
                      Nildefinition_list());
  idl_name corba_name_v = Name(mkcasestring("CORBA"));
  corba_name_v->nc=mknocasestring("CORBA");
  definition corba_mod_v =Module(
                      corba_name_v,
                      Consdefinition_list(tc_v,Nildefinition_list()));
  add_module(corba_name_v,corba_mod_v);
  add_interface(tc_name_v,tc_v,inh_v);
  pop_scope();
  pop_scope();
#ifdef IDL2IDL
  idl_name cook_name_v = Name(mkcasestring("Cookie"));
  cook_name_v->nc = mknocasestring("Cookie");
  value_inheritance_spec nil_inh_v = NilValueInheritanceSpec();
  definition cook_v = ValueType(
                      ValueHeader(NilFlag(),cook_name_v,nil_inh_v),
                      Nildefinition_list());
  idl_name eb_name_v = Name(mkcasestring("EventBase"));
  eb_name_v->nc=mknocasestring("EventBase");
  definition eb_v = ValueType(
                      ValueHeader(NilFlag(),eb_name_v,nil_inh_v),
                      Nildefinition_list());
  idl_name components_name_v = Name(mkcasestring("Components"));
  components_name_v->nc = mknocasestring("Components");
  definition componets_mod_v =Module(
                      components_name_v,
                      Consdefinition_list(cook_v,
                        Consdefinition_list(eb_v,Nildefinition_list())));
  add_module(components_name_v,componets_mod_v);
  add_value_type(eb_name_v,eb_v,nil_inh_v);
  pop_scope();
  add_value_type(cook_name_v,cook_v,nil_inh_v);
  pop_scope();
  pop_scope();
#endif
}

void
init_symtab()
{
  symtab = Niltable_item_list();
  symtab_scope = TableItem(
                  last_scope_type=NilN(),
                  last_scope_name=EscapedName(mkcasestring("")),
                  Constable_item_lists(symtab,Niltable_item_lists()));
  last_scope_name->nc = mknocasestring("");
  current_scope = symtab_scope;
  current_scope_list = symtab;
  scope_stack = Constable_item_list(current_scope,Niltable_item_list());
  current_scope->gen_parent();
  init_implicit();
}

void
print_symtab()
{
  symtab->print();
}

void
add_name(
  bool with_scope, 
  node_flag nflag, 
  idl_name name, 
  definition def_v,
  table_item_lists inh_v)
{
  bool ok=true;
	table_item_list first,found;
	table_item_lists new_lists;
	table_item new_item;
	new_lists = Constable_item_lists(
                first=Niltable_item_list(),
                (inh_v?inh_v:Niltable_item_lists()));

	new_item = TableItem(nflag,name,new_lists);
	new_item->gen_parent();
  name->symtab_entry=new_item;
  new_item->def_v=def_v;
  new_item->scope = current_scope; // notice defining scope
  if(equal_idl_name(name,last_scope_name)) {
    Error("you can't define a entity with name '%k' in an scope with same name\n",
      name,name);
    return;
  }
  with(nflag) {
    ElementN(),
    OpN(): {
      if(last_scope_type->prod_sel() == sel_InterfaceN) {
        found=lookup_name(name,current_scope);
      }
      else {
        found=__lookup_name(name,current_scope_list);
      }
    }
    default : {
      found=__lookup_name(name,current_scope_list);
    }
  }
  foreach($item_v; table_item_list found) {
    TableItem(*,name_v,*) :  {
      Error("%k already defined at %p\n",name,name,name_v);
      ok=false;
    }
    TableItemDcl(nflag_1,name_v) : {
      if(nflag_1->eq(nflag)) {
        item_v->symtab_entry=new_item;
      }
      else {
        Error("%k already declared as '%k' at %p\n",name,name,nflag_1,name_v);
        ok=false;
      }
    }
  }
  if(!ok && with_scope ) { exit(1); /* exit here, because we don't push a scope */ }
  check_used(name,nflag);

  append_item(current_scope_list,new_item);
  
  if(with_scope) {
    scope_stack = Constable_item_list(current_scope,scope_stack);
    current_scope_list = first;
    current_scope = new_item;
    last_scope_name = name;
    last_scope_type = nflag;
    /* make a used list for some types, remember to remove the list in pop_scope() */
    with(nflag) {
      CompositionN(),
      HomeN(),
      ComponentN(),
      InterfaceN() : {
        if(inh_v) check_inh(inh_v,name);
        current_scope_used_list = Niltable_item_list();
      }
      default : {}
    }
  }
}

void
add_declaration(node_flag nflag, idl_name name)
{
  bool ok=true;
	table_item_list found;
	table_item new_item = TableItemDcl(nflag,name);
	new_item->gen_parent();
  name->symtab_entry=new_item;
  found=__lookup_name(name,current_scope_list);
  foreach($item_v; table_item_list found) {
    TableItem(*,name_v,*) :  {
      Error("%k already defined at %p\n",name,name,name_v);
      ok=false;
    }
    TableItemDcl(nflag_1,name_v) : {
      if(nflag_1->eq(nflag)) {
      }
      else {
        Error("%k already declared as '%k' at %p\n",name,name,nflag_1,name_v);
        ok=false;
      }
    }
  }
  if(!ok) { return;}
  check_used(name,nflag);

  append_item(current_scope_list,new_item);

}

static void
add_used(idl_identifier ident_v)
{
  if(!current_scope_used_list) {
    Error("<impl>use of add_used outside of interface\n",0);
    return;
  }
  with(ident_v) {
    LocalName(idl_name_list_v) : {
      append_item(current_scope_used_list,
        TableItem(NilN(),idl_name_list_v->last(),Niltable_item_lists()));
    }
    LiteralName : { assert(0); }
    default : {}
  }
}

static void
check_used(idl_name name, node_flag nflag)
{
  table_item_list found;

  if(current_scope_used_list) {
    /* 
     * don't allow redefinition of types in an interface after a use with an other
     * definition
     */
    with(nflag) {
      TypeN(),
      InterfaceN() : {
        found = __lookup_name(name,current_scope_used_list);
        if(found) {
          with(found) {
            Constable_item_list(TableItem(*,name_1,*),*) : {
              Error("redefinition of %k in interface after use at %p\n",name,name,name_1);
            }
            default : {}
          }
        }
      }
      default : {}
    }
  }
}

%storageclass collisions; /* for use in check_inh only */

check_item { collisions } :
    CheckItem( casestring )
    { abstract_phylum entry=0; };

key_word { unique } :
    KeyWord( nocasestring )
    { int foo=0; };

void
check_inh(table_item_lists inh_v, idl_name name) 
{
  foreach(list_v; table_item_lists inh_v) {
    foreach($item_v;table_item_list list_v) {
      TableItem(FactoryN(),Name(cs),*),
      TableItem(FactoryN(),EscapedName(cs),*),
      TableItem(FinderN(),Name(cs),*),
      TableItem(FinderN(),EscapedName(cs),*),
      TableItem(OpN(),Name(cs),*),
      TableItem(OpN(),EscapedName(cs),*),
      TableItem(ElementN(),Name(cs),*),
      TableItem(ElementN(),EscapedName(cs),*) : {
        check_item i = CheckItem(cs);
        if(i->entry) {
          if(i->entry != item_v) {
            Error("collision in inheritance for %k of %k at %p and %p\n",
                  name,name,i->entry,i->entry,item_v);
          }
        }
        else {
          i->entry = item_v;
        }
      }
      default : {}
    }
  }
  kc_ht_reuse(kc_ht_assigned(collisions));
}

void
add_struct(idl_name name, definition def_v)
{
  add_name(true,TypeN(),name,def_v,0);
}

void
add_union(idl_name name, definition def_v, definition switch_type_v)
{
  add_name(true,TypeN(),name,def_v,0);
  resolve_type(switch_type_v);
}

void
add_element_spec(definition def_v,definition type_def_v,declarator declarator_v)
{
  resolve_type(type_def_v);
  with(declarator_v) {
    ArrayDeclarator(name_v,*),
    SimpleDeclarator(name_v) : {
      add_name(false,ElementN(),name_v,def_v,0);
    }
  }
}

void
add_enum(idl_name name, definition $def_v)
{
  EnumType(*,name_list_v) : {
    add_name(false,TypeN(),name,def_v,0);
    /* We use ElementN() here for enums */
    foreach(name_v;idl_name_list name_list_v) {
      add_name(false,ElementN(),name_v,def_v,0);
    }
  }
}

/* for use in struct definitions */

void
add_member(definition $def_v)
{
  Member(type_def_v,declarators_v) : {
    /* check if it is not the same type as the struct */
    _resolve_type(type_def_v,true);
    foreach($dcl_v;declarators declarators_v) {
      ArrayDeclarator(name_v,*),
      SimpleDeclarator(name_v) : {
        add_name(false,ElementN(),name_v,def_v,0);
      }
    }
  }
}

void
add_home(
  idl_name name, 
  definition def_v, 
  idl_identifier inheritance,
  idl_identifier_list supports,
  idl_identifier manages,
  idl_identifier prim_key)
{
  table_item_lists inh_v=Niltable_item_lists();
	if(inheritance) {
    foreach(list_v; table_item_lists resolve_home_name(inheritance)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
  }

  assertReason(manages,"home without component");
  resolve_component_name(manages);

  if(prim_key) {
    _resolve_name(true,prim_key,the_ValueTypeN);
    /* XXX check that prim_key is derived from "Components::PrimarykeyBase" */
  }
  if (supports) {
	foreach(list_v;table_item_lists resolve_interface_names(supports)) {
	  if(!inh_v->contains(list_v)) inh_v->append(list_v);
	}
	foreach(ident_v;idl_identifier_list supports) {
      get_definition(ident_v)->derived.insert(def_v);
	}
  }	
  /* XXX do more checks */
	add_name(true,HomeN(),name,def_v,inh_v);
}

void
add_component(
  idl_name name, 
  definition def_v, 
  idl_identifier inheritance,
  idl_identifier_list supports)
{
  table_item_lists inh_v=Niltable_item_lists();
	if(inheritance) {
    foreach(list_v; table_item_lists resolve_component_name(inheritance)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
  }
  if(supports) {
    foreach(list_v; table_item_lists resolve_interface_names(supports)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
    foreach(ident_v;idl_identifier_list supports) {
      get_definition(ident_v)->derived.insert(def_v);
    }
  }
  /* XXX do more checks */
	add_name(true,ComponentN(),name,def_v,inh_v);
}

void
add_provides_dcl(
  idl_name name,
  definition def_v,
  definition type)
{
  resolve_type(type);
  add_name(false,ProvidesDclN(),name,def_v,0);
}

void
add_uses_dcl(
  idl_name name,
  definition def_v,
  definition type)
{
  resolve_type(type);
  add_name(false,UsesDclN(),name,def_v,0);
}

void
add_emits_dcl(
  idl_name name,
  definition def_v,
  idl_identifier ident)
{
  resolve_name(ident,the_EventTypeN);
  add_name(false,EmitsDclN(),name,def_v,0);
}

void
add_sink_dcl(
  idl_name name,
  definition def_v,
  idl_identifier ident)
{
  resolve_name(ident,the_StreamTypeN);
  add_name(false,SinkN(),name,def_v,0);
}

void
add_source_dcl(
  idl_name name,
  definition def_v,
  idl_identifier ident)
{
  resolve_name(ident,the_StreamTypeN);
  add_name(false,SourceN(),name,def_v,0);
}

void
add_siso_dcl(
  idl_name name,
  definition def_v,
  idl_identifier ident)
{
  resolve_name(ident,the_StreamTypeN);
  add_name(false,SiSoN(),name,def_v,0);
}

void
add_streamtype_dcl(
  idl_name name,
  definition def_v)
{
  add_name(false,StreamTypeN(),name,def_v,0);
}


void
add_publishes_dcl(
  idl_name name,
  definition def_v,
  idl_identifier ident)
{
  resolve_name(ident,the_EventTypeN);
  add_name(false,PublishesDclN(),name,def_v,0);
}

void
add_consumes_dcl(
  idl_name name,
  definition def_v,
  idl_identifier ident)
{
  resolve_name(ident,the_EventTypeN);
  add_name(false,ConsumesDclN(),name,def_v,0);
}

void
add_interface(
  idl_name name, 
  definition def_v, 
  idl_identifier_list inheritance)
{
  table_item_lists inh_v=Niltable_item_lists();
	if(inheritance) {
    foreach(list_v; table_item_lists resolve_interface_names(inheritance)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
    foreach(ident_v;idl_identifier_list inheritance) {
      get_definition(ident_v)->derived.insert(def_v);
    }
  }
	add_name(true,InterfaceN(),name,def_v,inh_v);
}

void
add_value_box(
  idl_name name,
  definition def_v)
{
  add_name(true,ValueBoxN(),name,def_v,0);
}

void
add_eventtype(
  idl_name name, 
  definition def_v, 
  value_inheritance_spec inh_spec_v)
{
  table_item_lists inh_v=Niltable_item_lists();
  table_item_lists found_list;
  with(inh_spec_v) {
    ValueInheritanceSpec(*,Nilidl_identifier_list(),*) : {
    }
    ValueInheritanceSpec(*,inh_list_v,*) : {
      found_list = resolve_event_type_names(inh_list_v);
      bool first = true;
      foreach(ident_v;idl_identifier_list inh_list_v) {
        definition def_1 = get_definition(ident_v);
        if(!first && def_1) {
          with(def_1) {
            AbstractValueType : {}
            EventType,
            ValueType : {
              Error("'%k' is not abstract, only the first "
                    "inherited valutype/eventype may be not abstract\n",
                    ident_v,ident_v);
            }
          }
        }
        first=false;
      }
      if(found_list->length()==0)  {
        Error("can`t find base type for %k\n",inh_spec_v,name);
        exit (1);
      }
      foreach(list_v; table_item_lists found_list) {
        if(!inh_v->contains(list_v)) inh_v->append(list_v);
      }
      foreach(ident_v;idl_identifier_list inh_list_v) {
        get_definition(ident_v)->derived.insert(def_v);
      }
    }
    default : {}
  }
  with(inh_spec_v) {
    ValueInheritanceSpec(*,*,support_list_v) : {
      resolve_interface_names(support_list_v);
    }
    default: {}
  }
	add_name(true,EventTypeN(),name,def_v,inh_v);
}

void
add_value_type(
  idl_name name, 
  definition def_v, 
  value_inheritance_spec inh_spec_v)
{
  table_item_lists inh_v=Niltable_item_lists();
  table_item_lists found_list;
  with(inh_spec_v) {
    ValueInheritanceSpec(*,Nilidl_identifier_list(),*) : {
    }
    ValueInheritanceSpec(*,inh_list_v,*) : {
      found_list = resolve_value_type_names(inh_list_v);
      bool first = true;
      foreach(ident_v;idl_identifier_list inh_list_v) {
        definition def_1 = get_definition(ident_v);
        if(!first && def_1) {
          with(def_1) {
            AbstractValueType : {}
            ValueType : {
              Error("'%k' is not abstract, only the first "
                    "inherited valutype may be not abstract\n",
                    ident_v,ident_v);
            }
          }
        }
        first=false;
      }
      if(found_list->length()==0)  {
        Error("can`t find base type for %k\n",inh_spec_v,name);
        exit (1);
      }
      foreach(list_v; table_item_lists found_list) {
        if(!inh_v->contains(list_v)) inh_v->append(list_v);
      }
      foreach(ident_v;idl_identifier_list inh_list_v) {
        get_definition(ident_v)->derived.insert(def_v);
      }
    }
    default : {}
  }
  with(inh_spec_v) {
    ValueInheritanceSpec(*,*,support_list_v) : {
      resolve_interface_names(support_list_v);
    }
    default: {}
  }
  add_name(true,the_ValueTypeN,name,def_v,inh_v);
}

void
add_value_member(
  definition def_v,
  declarators decls)
{
  foreach($decl_v;declarators decls) {
    SimpleDeclarator(name) : {
      resolve_type(def_v);
      add_name(false, ElementN(), name, def_v, 0);
    }
  }  
}
  
void
add_catalog_dcl(
  idl_name name,
  definition def_v,
  idl_identifier type_name_v)
{
  resolve_name(type_name_v,the_CatalogN);
  add_name(false,CatalogLabelN(),name,def_v,0);
}

void
add_catalog(
  idl_name name, 
  definition def_v, 
  idl_identifier_list inheritance)
{
  table_item_lists inh_v=0;
  if(inheritance) {
    inh_v=resolve_catalog_names(inheritance);
    foreach(ident_v;idl_identifier_list inheritance) {
      get_definition(ident_v)->derived.insert(def_v);
    }
  }
  add_name(true,CatalogN(),name,def_v,inh_v);
}

void
add_composition(
  idl_name name, 
  definition def_v) 
{
  add_name(true,CompositionN(),name,def_v,0);
}

void
add_module(
  idl_name name, 
  definition def_v)
{
  table_item_list old=0;
  old = lookup_name(name,current_scope);
  if(old) {
    with(old) {
      Niltable_item_list() : {
        add_name(true,ModuleN(),name,def_v,0);
      }
      /* module reopening */
      Constable_item_list(item_v=TableItem(*,*,Constable_item_lists(first,*)),Niltable_item_list()) : {
        name->symtab_entry = item_v;
        scope_stack = Constable_item_list(current_scope,scope_stack);
        current_scope_list = first;
        current_scope = item_v;
      }
    }
  }
  else {
    add_name(true,ModuleN(),name,def_v,0);
  }
}

void
add_segment(
  idl_name name, 
  definition def_v)
{
  add_name(true,SegmentN(),name,def_v,0);
}

void
add_executor(
  idl_name name, 
  definition def_v)
{
  add_name(true,ExecutorN(),name,def_v,0);
}

void
add_home_executor(
  idl_name name, 
  definition def_v)
{
  add_name(true,HomeExecutorN(),name,def_v,0);
}

void
add_facet_dcl(
  idl_name_list idl_name_list_v,
  definition def_v)
{
  //foreach(idl_name_v;idl_name_list idl_name_list_v) {
  /* resolving names in resolve_symtab */
  //  add_name(false,FacetN(),idl_name_v,def_v,0);
  //}
}

void
add_provides(
  declarator $dcl_name_v,
  definition def_v,
  idl_identifier home_name_v)
{
  SimpleDeclarator(name_v) : {
    resolve_name(home_name_v,the_AbstractStorageHomeN);
	  add_name(false,ProvidesN(),name_v,def_v,0);
  }
}

void
add_primary_key(definition $primary_key_def)
{
  /* this is not true. the key is not a local identifier
     and should searched only in the abstract home */
  PrimaryKeyDcl( name ) : {
    resolve_name(name,the_KeyN);
  }
}

void
add_psdl_states(
  declarators states_v,
  definition def_v,
  definition type_v)
{
  resolve_psdl_state_type(type_v);
  foreach($declarator_v;declarators states_v) {
    SimpleDeclarator(name_v) : {
      add_name(false,PsdlStateN(),name_v,def_v,0);
    }
  }
}

void 
add_abstract_storagetype(
  idl_name name, 
  definition def_v, 
  idl_identifier_list inheritance)
{
  table_item_lists inh_v=Niltable_item_lists();
	if(inheritance) {
    foreach(list_v; table_item_lists resolve_abstract_storagetype_names(inheritance)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
    foreach(ident_v;idl_identifier_list inheritance) {
      get_definition(ident_v)->derived.insert(def_v);
    }
  }
	add_name(true,AbstractStorageTypeN(),name,def_v,inh_v);
}


void
add_operation(
  idl_name name, 
  definition def_v, 
  definition return_type_v,
  parameter_dcls parameters_v,
  attr_raises_expr raises_v,
  flag one_way_v)
{
  table_item_list res=0;
  if(one_way_v) {
    with(return_type_v) {
      Void() : {}
      default : {
        Error("operation %k defined as oneway but return type is not void\n",
          name,name);
      }
    }
  }
  else {
    resolve_type(return_type_v);
  }
  if(parameters_v) resolve_parameters(parameters_v);
  if(raises_v) resolve_raises_expr(raises_v);
  res=lookup_name(name,current_scope);
  add_name(false,OpN(),name,def_v,0);
}

void
add_factory(
  idl_name name, 
  definition def_v, 
  parameter_dcls parameters_v,
  attr_raises_expr raises_v)
{
  if(parameters_v) resolve_parameters(parameters_v);
  if(raises_v) resolve_raises_expr(raises_v);
  lookup_name(name,current_scope);
  add_name(false,FactoryN(),name,def_v,0);
}

void
add_finder(
  idl_name name, 
  definition def_v, 
  parameter_dcls parameters_v,
  attr_raises_expr raises_v)
{
  if(parameters_v) resolve_parameters(parameters_v);
  if(raises_v) resolve_raises_expr(raises_v);
  lookup_name(name,current_scope);
  add_name(false,FinderN(),name,def_v,0);
}

void
add_attribute(definition $attr_v)
{
  Attribute(*,type_def_v,AttrDeclarator(SimpleDeclarator(name_v),raise_expr_v)) : {
    resolve_type(type_def_v);
    resolve_raises_expr(raise_expr_v);
    add_name(false,ElementN(),name_v,attr_v,0);
  }
  Attribute(*,type_def_v,AttrDeclaratorList(declarators_v)) : {
    resolve_type(type_def_v);
    foreach($decl_v;declarators declarators_v) {
      SimpleDeclarator(name_v) : {
        add_name(false,ElementN(),name_v,attr_v,0);
      }
    }
  }
}


void
add_exception(idl_name name,definition def_v)
{
  add_name(true,ExceptionN(),name,def_v,0);
}

void
add_storagetype(
  idl_name name,
  definition def_v,
  idl_identifier inh_spec,
  idl_identifier_list impl_spec)
{
  table_item_lists inh_v=Niltable_item_lists();
	if(inh_spec) {
    foreach(list_v; table_item_lists _resolve_name(true,inh_spec,the_StorageTypeN)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
    get_definition(inh_spec)->derived.insert(def_v);
  }
  if(impl_spec) {
    foreach(list_v; table_item_lists resolve_abstract_storagetype_names(impl_spec)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
  }
	add_name(true,StorageTypeN(),name,def_v,inh_v);
}

void 
add_abstract_storagehome(
  idl_name name,
  definition def_v,
  idl_identifier type_name,
  idl_identifier_list inh_spec)
{
  table_item_lists inh_v = Niltable_item_lists();
	_resolve_name(true,type_name,the_AbstractStorageTypeN);
	if(inh_spec) {
    foreach(list_v; table_item_lists resolve_abstract_storagehome_names(inh_spec)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
    foreach(ident_v;idl_identifier_list inh_spec) {
      get_definition(ident_v)->derived.insert(def_v);
    }
  }
	add_name(true,AbstractStorageHomeN(),name,def_v,inh_v);
}

void
add_storagehome(
  idl_name name,
  definition def_v,
  idl_identifier type_name,
  idl_identifier inh_spec,
  idl_identifier_list impl_spec)
{
  table_item_lists inh_v=Niltable_item_lists();
	if(type_name) _resolve_name(true,type_name,the_StorageTypeN);
	if(inh_spec) {
    foreach(list_v; table_item_lists _resolve_name(true,inh_spec,the_StorageHomeN)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }
    get_definition(inh_spec)->derived.insert(def_v);
  }
  if(impl_spec) {
    foreach(list_v; table_item_lists resolve_abstract_storagehome_names(impl_spec)) {
      if(!inh_v->contains(list_v)) inh_v->append(list_v);
    }  
  }
	add_name(true,StorageHomeN(),name,def_v,inh_v);
}

void
add_native_type(definition $native_type_v)
{
  NativeType(SimpleDeclarator(name_v)) : {
    add_name(false,TypeN(),name_v,native_type_v,0);
  }
  default : {
    Error("unexpected case in add_native_type\n",0);
  }
}

void
add_type_declarators(
  definition type_def_v,
  declarators declarators_v,
  definition def_v)
{
  resolve_type(type_def_v);
  foreach($decl_v; declarators declarators_v) {
    ArrayDeclarator(name_v,*),
    SimpleDeclarator(name_v) : {
      add_name(false,TypeN(),name_v,def_v,0);
    }
  }
}

void
add_abstract_storage_home_name(
  idl_name catalog_label_v,
  idl_name abstract_storage_home_label_v)
{
  table_item_list list_1=0;
  table_item_list list_v = search_name(catalog_label_v,the_CatalogLabelN);
  if(!list_v || list_v->prod_sel() == sel_Niltable_item_list) {
    Error("catalog '%k' is not declared\n",catalog_label_v,catalog_label_v);
    return;
  }
  with(list_v) {
    Constable_item_list(item_v,Niltable_item_list()) : {
      /* Oooooh abuse of idl_name as an idl_identifier,
       * so we have to register the referenced symtab_entry
       * here. (HB)
       */
       catalog_label_v->symtab_entry=item_v;
      /* Get all named definitions from the catalog */ 
       list_1 = lookup_name(abstract_storage_home_label_v,item_v);
      /* Look up for a home definition */
       list_1 = lookup_node_flag(the_HomeN,list_1);
    }
    Constable_item_list(item_v,*) : {
      Error("catalog '%k' is multiple declared\n",catalog_label_v,catalog_label_v);
    }
  }

  with(list_1) {
    Constable_item_list(item_v,Niltable_item_list()) : {
      /* Oooooh abuse of idl_name as an idl_identifier,
       * so we have to register the referenced symtab_entry
       * here. (HB)
       */
       abstract_storage_home_label_v->symtab_entry=item_v;
    }
    Niltable_item_list : {
      Error("No home definition '%k' in '%k'\n",abstract_storage_home_label_v,
              abstract_storage_home_label_v,catalog_label_v);
    }
  }
}

void
pop_scope()
{
  /* remove the used types list if we leaf an scope with own used list 
   * see add_name()
   */
  with(current_scope) {
    TableItem(CompositionN(),*,*),
    TableItem(HomeN(),*,*),
    TableItem(ComponentN(),*,*),
    TableItem(InterfaceN(),*,*) : {
      current_scope_used_list = 0;
    }
    default : {}
  }

	with(scope_stack) {
		Constable_item_list(last,tail) : {
			current_scope = last;
      scope_stack=tail;
      with(last) {
        TableItem(nflag,name,Constable_item_lists(list_v,*)) : {
          current_scope_list = list_v;
          last_scope_type = nflag;
          last_scope_name = name;
        }
      }
		}
    Constable_item_list(*,Niltable_item_list()) : {
      Error("<internal>pop_scope over last scope\n",0);
    }
	}
}

void
push_scope(table_item $scope)
{
  TableItem(nflag,name_v,Constable_item_lists(first,*)) : {
    current_scope = scope;
    current_scope_list = first;
    last_scope_name = name_v;
    last_scope_type = nflag;
    scope_stack = Constable_item_list(current_scope,scope_stack);
  }
}

table_item_lists
resolve_name(
  idl_identifier ident_v, 
  node_flag nflag)
{
  return _resolve_name(false,ident_v,nflag);
}

static table_item_lists
_resolve_name_n(
  bool must_be_definition,
  idl_identifier ident_v, 
  node_flag *nflag,
  int n)
{
  bool ok = false;
  table_item_list list_v;
  table_item_lists res=0;
  list_v  = lookup_identifier_n(ident_v,nflag,n);
  foreach(item_v; table_item_list list_v) {
    if(!ok) {
      if(!must_be_definition) {
        ok=true;
        ident_v->symtab_entry=item_v;
      }
      with(item_v) {
        TableItem(*,*,lists_v) : {
          if(must_be_definition) {
            ok=true;
            ident_v->symtab_entry=item_v;
          }
          res=lists_v;
        }
        default : { /* has no namespace */ }
      }
    }
    else  {  /* Ooops */;
    }
  }
  if(!ok) Error("%k is not defined\n",ident_v,ident_v);
  return ((res!=0)?res:Niltable_item_lists());
}

static table_item_lists
_resolve_name(
  bool must_be_definition,
  idl_identifier ident_v, 
  node_flag nflag)
{
  bool ok = false;
  table_item_list list_v;
  table_item_lists res=0;
  list_v  = lookup_identifier(ident_v,nflag);
  foreach(item_v; table_item_list list_v) {
    if(!ok) {
      if(!must_be_definition) {
        ok=true;
        ident_v->symtab_entry=item_v;
      }
      with(item_v) {
        TableItem(*,*,lists_v) : {
          if(must_be_definition) {
            ok=true;
            ident_v->symtab_entry=item_v;
          }
          res=lists_v;
        }
        default : { /* has no namespace */ }
      }
    }
    else  {  /* Ooops */;
    }
  }
  if(!ok) Error("%k is not defined\n",ident_v,ident_v);
  return ((res!=0)?res:Niltable_item_lists());
}

table_item_lists
resolve_names_n(idl_identifier_list list_v, node_flag *nflag, int n)
{
  table_item_lists res = Niltable_item_lists();
	foreach(identifier_v; idl_identifier_list list_v) {
    res=concat(_resolve_name_n(true,identifier_v,nflag,n),res);
	}
  return res;
}

table_item_lists
resolve_names(idl_identifier_list list_v, node_flag nflag)
{
  table_item_lists res = Niltable_item_lists();
	foreach(identifier_v; idl_identifier_list list_v) {
    res=concat(_resolve_name(true,identifier_v,nflag),res);
	}
  return res;
}

table_item_lists
resolve_home_name(idl_identifier name)
{
  return _resolve_name(true,name,the_HomeN);
}

table_item_lists
resolve_component_name(idl_identifier name)
{
  return _resolve_name(true,name,the_ComponentN);
}

table_item_lists
resolve_abstract_storagetype_names(idl_identifier_list names)
{
  return resolve_names(names,the_AbstractStorageTypeN);
}

table_item_lists
resolve_abstract_storagehome_names(idl_identifier_list names)
{
  return resolve_names(names,the_AbstractStorageHomeN);
}

table_item_lists
resolve_event_type_names(idl_identifier_list names)
{
  node_flag node_flags_v[2];
  node_flags_v[0] = the_EventTypeN;
  node_flags_v[1] = the_ValueTypeN;
  return resolve_names_n(names,node_flags_v,2);
}

table_item_lists
resolve_value_type_names(idl_identifier_list names)
{
  return resolve_names(names,the_ValueTypeN);
}

table_item_lists
resolve_interface_names(idl_identifier_list names)
{
  return resolve_names(names,the_InterfaceN);
}

table_item_lists
resolve_catalog_names(idl_identifier_list names)
{
  return resolve_names(names,the_CatalogN);
}

table_item_lists
resolve_abstract_storagetype_name(idl_identifier ident_v)
{
  return resolve_name(ident_v,the_AbstractStorageTypeN);
}

table_item_lists
resolve_storagehome_name(idl_identifier ident_v)
{
  return resolve_name(ident_v,the_StorageHomeN);
}

table_item_lists
resolve_storagetype_name(idl_identifier ident_v)
{
  return resolve_name(ident_v,the_StorageTypeN);
}

void
resolve_psdl_state_type(
  definition $type_v)
{
  StorageTypeRef(*,ident_v) : {
    _resolve_name(true,ident_v,the_AbstractStorageTypeN);
  }
  default : {
    resolve_type(type_v);
  }
}

void
resolve_type(
  definition type_v)
{
  _resolve_type(type_v,false);
}

void
_resolve_type(
  definition $type_v,
  bool check_own_type)
{
  Void,
  ObjectType,
  AnyType,
  OctetType,
  BooleanType,
  CharType,
  WCharType,
  UnsignedShortInt,
  UnsignedLongInt,
  UnsignedLongLongInt,
  SignedShortInt,
  SignedLongInt,
  SignedLongLongInt,
  NFloat,
  NDouble,
  NLongDouble,
  FixedType,
  ValueBaseType: {}
  StringType(expr_1),
  WideStringType(expr_1) : {
    resolve_expression(expr_1);
  }
  FixedPtType(expr_1,expr_2) : {
    resolve_expression(expr_1);
    resolve_expression(expr_2);
  }
  SequenceType(def, expr) : {
    resolve_type(def);
    resolve_expression(expr);
  }
  NScopedName(ident_v) : {
    table_item_list list_v;
    bool error_report=true;
	 node_flag node_flags_v[6];
	 node_flags_v[0] = the_TypeN;
	 node_flags_v[1] = the_ValueTypeN;
	 node_flags_v[2] = the_EventTypeN;
	 node_flags_v[3] = the_ValueBoxN;
	 node_flags_v[4] = the_InterfaceN;
	 node_flags_v[5] = the_ComponentN;
    list_v = lookup_identifier_n(ident_v,node_flags_v,6);
    foreach(item_v;table_item_list list_v) {
      if(check_own_type
        && !ident_v->symtab_entry
        && item_v->eq(current_scope) ) {
        Error("recursive use of '%k'\n",ident_v,ident_v);
      }
      else if(!ident_v->symtab_entry 
        || ident_v->symtab_entry->prod_sel() == sel_TableItemDcl ) {
        ident_v->symtab_entry=item_v;
        if(current_scope_used_list) add_used(ident_v);
      }
      else if((item_v->prod_sel() == sel_TableItem) && error_report) {
        Error("found multiple definitions for '%k' at %p and %p\n",
              ident_v,ident_v,ident_v->symtab_entry,item_v);
        error_report=false;
      }
    }
    if(!ident_v->symtab_entry) {
        Error("found no definition for type '%k'\n",ident_v,ident_v);
    }
  }
  default : {
    Error("<impl>unexpected case for '%k' in resolve_type\n",0,type_v);
  }
}


void
resolve_expression(const_expression $expr_v)
{
  IntegerLiteral,
  StringLiteral,
  WideStringLiteral,
  CharacterLiteral,
  FixedPtLiteral,
  FloatingPtLiteral,
  LIT_TRUE,
  LIT_FALSE,
  Nilconst_expression : {}
  UMinus(expr_n),
  UPlus(expr_n),
  UNeg(expr_n) : {
    resolve_expression(expr_n);
  }
  Div(expr_1,expr_2),
  Modulo(expr_1,expr_2),
  Add(expr_1,expr_2),
  Minus(expr_1,expr_2),
  LShift(expr_1,expr_2),
  RShift(expr_1,expr_2),
  Xor(expr_1,expr_2),
  And(expr_1,expr_2),
  Or(expr_1,expr_2) : {
    resolve_expression(expr_1);
    resolve_expression(expr_2);
  }
  NamedRef(ident_v) : {
    bool ok = false;
    table_item_list list_v;
    list_v = lookup_identifier(ident_v,the_ConstantN);
    foreach(item_v=TableItem(*,*,*);table_item_list list_v) {
      if(!ok) {
        ok=true;
        ident_v->symtab_entry=item_v;
      }
      else {
        Error("found multiple definitions for '%k'\n",item_v,ident_v);
      }
    }
    if(!ok) {
        Error("found no definition for type '%k'\n",ident_v,ident_v);
    }
  }
  default : {
    Error("<impl>unexpected case in resolve_expression\n",0);
  }
}

void
resolve_case_labels(case_label_list list_v,definition $type_v)
{
  UnsignedShortInt(), UnsignedLongInt(), UnsignedLongLongInt(),
  SignedShortInt(), SignedLongInt(), SignedLongLongInt() : {
    assert(0);
  }
  BooleanType() : {
    assert(0);
  }
  CharType(), WCharType(): {
    assert(0);
  }
  NScopedName(ident_v) : {
    assert(ident_v->symtab_entry);
    resolve_case_labels(list_v,get_definition(ident_v));
  }
  EnumType(enum_name_v,name_list_v) : {
    foreach(CaseLabel(NamedRef(id_v));case_label_list list_v) {
      with(id_v) {
        GlobalName(Considl_name_list(name_v,*)),
        LocalName(Considl_name_list(name_v,*)) : {
          /* simple but it should work */
          with(lookup_name(name_v,enum_name_v->symtab_entry->scope)){
            Constable_item_list(item_v=TableItem(ElementN(),*,*),
              Niltable_item_list()) : {
              if(!(item_v->def_v == type_v)) {
                Error("'%k' not element of enumeration '%k'\n",
                  id_v,id_v,enum_name_v);
              } 
              else { id_v->symtab_entry = item_v; }
            }
            default : {
              Error("found no enum in '%k' with name '%k'\n",
                id_v,enum_name_v,id_v);
            }
          }
        }
      }
    }
  }
}

void
resolve_raises_expr(attr_raises_expr $raises_v)
{
  RaisesExpr(id_list_v),
  GetExcepExpr(id_list_v),
  SetExcepExpr(id_list_v) : {
    bool ok;
    table_item_list list_v;
    foreach(ident_v;idl_identifier_list id_list_v) {
      ok = false;
      list_v = lookup_identifier(ident_v,the_ExceptionN);
      foreach(item_v=TableItem(*,*,*,*);table_item_list list_v) {
        if(!ok) {
          ok=true;
          ident_v->symtab_entry=item_v;
        }
        else {
          Error("found multiple exceptions for '%k'\n",item_v,ident_v);
        }
      }
      if(!ok) {
        Error("use of undefined exception '%k'\n",ident_v,ident_v);
      }
    }
  }
  GetSetExcepExpr(id_list_1,id_list_2) : {
    bool ok;
    table_item_list list_v;
    foreach(ident_v;idl_identifier_list id_list_1) {
      ok=false;
      list_v = lookup_identifier(ident_v,the_ExceptionN);
      foreach(item_v=TableItem(*,*,*);table_item_list list_v) {
        if(!ok) {
          ok=true;
          ident_v->symtab_entry=item_v;
        }
        else {
          Error("found multiple exceptions for '%k'\n",item_v,ident_v);
        }
      }
      if(!ok) {
        Error("use of undefined exception '%k'\n",ident_v,ident_v);
      }
    }
    foreach(ident_v;idl_identifier_list id_list_2) {
      list_v = lookup_identifier(ident_v,the_ExceptionN);
      ok=false;
      foreach(item_v=TableItem(*,*,*);table_item_list list_v) {
        if(!ok) {
          ok=true;
          ident_v->symtab_entry=item_v;
        }
        else {
          Error("found multiple exceptions for '%k'\n",item_v,ident_v);
        }
      }
      if(!ok) {
        Error("use of undefined exception '%k'\n",ident_v,ident_v);
      }
    }
  }
  NilRaisesExpr : {}
}

void
resolve_parameters(parameter_dcls parameters_v)
{
  foreach(ParamDcl(*,type_v,declarator_v);parameter_dcls parameters_v) {
    resolve_type(type_v);
    with(declarator_v) {
      ArrayDeclarator(name=Name(cs),fixed_array_sizes_v),
      ArrayDeclarator(name=EscapedName(cs),fixed_array_sizes_v) : {
        check_item i = CheckItem(cs);
        if(i->entry) {
          Error("multiple use of parameter name %k  at %p and %p\n",
                name,name,name,i->entry);
        }
        else {
          i->entry = name;
        }
        foreach(FixedArraySize(expr_v);fixed_array_sizes fixed_array_sizes_v) {
          resolve_expression(expr_v);
        }
      }
      SimpleDeclarator(name=Name(cs)),
      SimpleDeclarator(name=EscapedName(cs)) : {
        check_item i = CheckItem(cs);
        if(i->entry) {
          Error("multiple use of parameter name %k  at %p and %p\n",
                name,name,name,i->entry);
        }
        else {
          i->entry = name;
        }
      }
    }
  }
  kc_ht_reuse(kc_ht_assigned(collisions));
}

void
print_path(abstract_phylum node)
{
  table_item i;
  idl_name n;
  idl_identifier id;

  if((i=dynamic_cast<table_item>(node))) {
    print_table_item_path(i);
  }
  else if((n=dynamic_cast<idl_name>(node))) {
    print_idl_name_path(n);
  }
  else if((id=dynamic_cast<idl_identifier>(node))) {
    print_idl_identifier_path(id);
  }
}

void
print_table_item_path(table_item item_v)
{
  with(item_v) {
    TableItemDcl(*,name_v),
    TableItem(*,name_v,*) : {
      /* init_msg_buf(); */
      printer4(" file ",base_uview);
      name_v->filename->unparse(printer4,base_uview);
      printer4(" line ",base_uview);
      name_v->line->unparse(printer4,base_uview);
      /* if (get_msg_buf())
        printer1(get_msg_buf(), print_node);
      printer1("\n",print_node); 
      free_msg_buf(); */
    }
  }
}

void
print_idl_name_path(idl_name name_v)
{
  init_msg_buf();
  printer4(" file ",base_uview);
  name_v->filename->unparse(printer4,base_uview);
  printer4(" line ",base_uview);
  name_v->line->unparse(printer4,base_uview);
  if (get_msg_buf())
    printer1(get_msg_buf(), print_node);
  printer1("\n",print_node);
  free_msg_buf();
}

void
print_idl_identifier_path(idl_identifier $ident_v)
{
  GlobalName(Considl_name_list(name_v,*)),
  LocalName(Considl_name_list(name_v,*)) : {
    print_idl_name_path(name_v);
  }
}

static bool
node_flag_filter_n(table_item $p)
{
  TableItem(nflag_v,*,*),
  TableItemDcl(nflag_v,*) : {
	 int i;
	 for (i=0; i <node_flag_filter_flag_nr; i++) {
		 if(nflag_v->eq(node_flag_filter_flag_n[i]))
			 return true;
	 }
	 return false;
  }
}

static bool
node_flag_filter(table_item $p)
{
  TableItem(nflag_v,*,*),
  TableItemDcl(nflag_v,*) : {
    return nflag_v->eq(node_flag_filter_flag);
  }
}

static table_item_list
lookup_identifier_n(
  idl_identifier identifier_v,
  node_flag *nflag,
  int n)
{
  table_item_list res = _lookup_identifier(identifier_v,current_scope);
  node_flag_filter_flag_n = nflag;
  node_flag_filter_flag_nr = n;
  return res->filter(node_flag_filter);
  
}

static table_item_list
lookup_identifier(
  idl_identifier identifier_v,
  node_flag nflag)
{
  table_item_list res = _lookup_identifier(identifier_v,current_scope);
  node_flag_filter_flag = nflag;
  return res->filter(node_flag_filter);
  
}

static table_item_list
_lookup_identifier(
  idl_identifier identifier_v,
  table_item scope)
{
  table_item_list res=0;
  table_item my_current_scope=0;
  idl_name name_v=0;
  idl_name_list name_list_v=0;
  with(identifier_v) {
    GlobalName(idl_name_list_v) : {
      name_list_v = idl_name_list_v;
      name_v=idl_name_list_v->last();
      res=lookup_name(name_v,symtab_scope);
    }
    LocalName(idl_name_list_v) : {
      name_list_v = idl_name_list_v;
      name_v=idl_name_list_v->last();
      my_current_scope = scope;
      while(my_current_scope&&(!res || res->prod_sel() == sel_Niltable_item_list)) {
        res = lookup_name(name_v,my_current_scope);
        my_current_scope = next_scope(my_current_scope);
      }
    }
  }

  if(!res || res->prod_sel() == sel_Niltable_item_list) {
    return res;
  }

  res=match_path(name_list_v,res,identifier_v);

  return res;
}

static table_item_list
search_name(
  idl_name name_v,
  node_flag nflag)
{
  return _search_name(name_v,nflag,current_scope);
}

static table_item_list
_search_name(
  idl_name name_v,
  node_flag nflag,
  table_item scope)
{
  table_item_list res=0;
  table_item my_current_scope=scope;
  while(my_current_scope&&(!res || res->prod_sel() == sel_Niltable_item_list)) {
    res = lookup_name(name_v,my_current_scope);
    my_current_scope = next_scope(my_current_scope);
  }

  if(!res || res->prod_sel() == sel_Niltable_item_list) {
    return res;
  }

  foreach($item_v; table_item_list res) {
    TableItem(nflag_1,name_1,*),
    TableItemDcl(nflag_1,name_1) : {
      if(!equal_node_flag(nflag,nflag_1)) {
        Error("%k is not a %k\n",name_v,name_1,nflag);
      }
    }
  }
  return res;
}

static table_item_list
match_path(idl_name_list $name_list_v, table_item_list scope ,idl_identifier identifier_v)
{
  Considl_name_list(name_v,tail) : {
    table_item my_scope = 0;
    table_item_list my_scope_list = match_path(tail,scope,identifier_v);
    if(!my_scope_list || my_scope_list->prod_sel() == sel_Niltable_item_list) {
      /* may be an Error message here ? HB */
      return 0;
    }
    foreach(item_v=TableItem(*,*,*); table_item_list my_scope_list) {
      my_scope = item_v;
    }
    if(my_scope) {
      return lookup_name(name_v,my_scope);
    }
    return 0;
  }
  Considl_name_list(*,Nilidl_name_list()) : {
    return scope;
  }
}

table_item_list
__lookup_name(idl_name name_v, table_item_list list_v)
{
  table_item_list res =  Niltable_item_list();
  foreach($item_v;table_item_list list_v) {
    TableItemDcl(*,name_1),
    TableItem(*,name_1,*) : {
      if(equal_idl_name(name_1,name_v)) {
        if(!case_test(name_1,name_v)) {
          Warning("inconsistent case for '%k' '%k'\n",name_1,name_v,name_1);
        }
        res = Constable_item_list(item_v,res);
      }
    }
  }
  return res;
}

table_item_list
lookup_name(idl_name name_v, table_item $scope_v)
{
  TableItem(*,*,Constable_item_lists(local_v,tail)) : {
    table_item_list res = __lookup_name(name_v,local_v);
    if(res->length()) {
      return res;
    }
    foreach(list_v; table_item_lists tail) {
      res= concat(res,__lookup_name(name_v,list_v));
    }
    return res;
  }
}

table_item_list
lookup_node_flag(node_flag nflag, table_item_list list_v)
{
  table_item_list res =  Niltable_item_list();
  foreach($item_v;table_item_list list_v) {
    TableItemDcl(nflag_1,*),
    TableItem(nflag_1,*,*) : {
      if(nflag->eq(nflag_1)) {
        res = Constable_item_list(item_v,res);
      }
    }
  }
  return res;
}


table_item
next_scope(table_item scope)
{
  abstract_phylum node = get_parent_node(scope);
  while(node) {
    if(node->phylum() == kc_phylum_table_item) {
      return (table_item)node;
    }
    node=get_parent_node(node);
  }
  return 0;
}

static void
append_item(table_item_list list_v,table_item item_v)
{
  list_v->append(item_v)->gen_parent();
}

definition
fix_composition(
  definition $def_v,
  composition_body body)
{
  Composition(*,*,NilCompositionBody()) : {
    def_v->set_subphylum(2,body);
    return def_v;
  }
}

definition
fix_home_executor(
  definition $def_v,
  home_executor_body body)
{
  HomeExecutorDef(*,NilHomeExecutorBody()) : {
    def_v->set_subphylum(1,body);
    return def_v;
  }
}

definition
fix_definition(
  definition $def_v,
  definition_list list_v)
{
  SegmentDef(*,nil_list),
  ExecutorDef(*,nil_list),
  AbstractValueType(*,nil_list),
  EventType(*,nil_list),
  ValueType(*,nil_list),
  HomeDcl(*,nil_list),
  NComponent(*,nil_list),
  ExceptDcl(*,nil_list),
  StructurType(*,nil_list),
  StorageType(*,nil_list),
  AbstractStorageType(*,nil_list),
  AbstractStorageHome(*,nil_list),
  StorageHome(*,nil_list),
  Catalog(*,*,nil_list),
  Module(*,nil_list),
  Interface(*,nil_list) : {
    assert(nil_list->is_nil());
    if (!list_v->is_nil()) {
      nil_list->set_subphylum(1,list_v->subphylum(1));
      nil_list->set_subphylum(0,list_v->subphylum(0));
      nil_list->gen_parent();
    }
    return def_v;
  }
  default : { 
    Error("<impl>unexpected case in fix_definition '%t'\n",0,def_v); 
    return 0;
  }
}

definition
fix_case_list(
  definition $def_v,
  idl_case_list list_v)
{
  UnionType(*,switch_type_v,nil_list) : {
    assert(nil_list->is_nil());
    nil_list->set_subphylum(1,list_v->subphylum(1));
    nil_list->set_subphylum(0,list_v->subphylum(0));
    nil_list->gen_parent();
    foreach(Case(case_label_list_v,*);idl_case_list list_v) {
      resolve_case_labels(case_label_list_v,switch_type_v);
    }
    return def_v;
  }
  default : { 
    Error("<impl>unexpected case in fix_idl_case_list '%t'\n",0,def_v); 
    return 0;
  }
}


bool
equal_node_flag(node_flag $n1, node_flag n2)
{
  TypeN() : {
    if(n1->eq(n2)) {
      return true;
    }
    else if(n2->eq(the_InterfaceN)) {
      return true;
    }
    /* TODO: this is only true for operations in PSDL */
    else if(n2->eq(the_AbstractStorageTypeN)) {
      return true;
    }
    else if(n2->eq(the_StorageTypeN)) {
      return true;
    }

    return false;
  }
  default : {
    return n1->eq(n2);
  }
}

bool
case_test(idl_name $n1, idl_name n2)
{
  Name(nstring_1),
  EscapedName(nstring_1) : {
    with(n2) {
      Name(nstring_2),
      EscapedName(nstring_2) : {
        if(!strcmp(nstring_1->name,nstring_2->name))
          return true;
        return false;
      }
    }
  }
}

static bool
equal_idl_name(idl_name n1, idl_name n2)
{
  return nc_name(n1)->eq(nc_name(n2));
}

static nocasestring
nc_name(idl_name n)
{
  if(!n->nc) {
    with(n) {
      Name(nstring_1),
      EscapedName(nstring_1) : {
        n->nc=mknocasestring(nstring_1->name);
      }
    }
  }
  return n->nc;
}

/* get the definition the given identifier refers to; if the identifier is a
   forward declarations, the definition is the actual declaration
*/
definition
get_definition(idl_identifier  ident_v)
{
  if(!ident_v->symtab_entry) {
    Error("<impl>get_definition ident '%k' without symtab entry\n",ident_v,ident_v);
    return 0;
  }
  table_item entry = ident_v->symtab_entry;
  while (entry) {
    with(entry) {
      TableItemDcl : {
        if(!entry->symtab_entry) {
          Error("<impl>get_definition deglaration item '%k' "
                "without symtab entry\n",entry, entry);
          return 0;
        }
        entry = entry->symtab_entry;
        continue;
      }
      TableItem : {
        if(!entry->def_v) {
          Error("<impl>get_definition symbol table  item '%k' "
                "without definition pointer\n",entry, entry);
          return 0;
        }
        return entry->def_v;
      }
    }
  }
  Error("<impl>get_definition Ooops at identifier '%k'\n",ident_v, ident_v);
  return 0;
}

bool
idl_identifier::equal(idl_identifier ident_v)
{
  assertReason(this->symtab_entry,"identifier without symtab entry");
  assertReason(ident_v->symtab_entry,"identifier without symtab entry");
  if(!this->symtab_entry->scope->eq(ident_v->symtab_entry->scope))
    return false;
  with(this) {
    GlobalName(Considl_name_list(name_1,*)),
    LocalName(Considl_name_list(name_1,*)) : {
      with(ident_v) {
        GlobalName(Considl_name_list(name_2,*)),
        LocalName(Considl_name_list(name_2,*)) : {
          return name_1->eq(name_2);
        }
      }
    }
  }
}

void
find_ident(idl_identifier $ident_v, node_flag nflag_v, bool warnings=false)
{
  GlobalName : {
    table_item_list list_v = lookup_identifier(ident_v, nflag_v);
    with(list_v) {
    Constable_item_list(item_v,Niltable_item_list()) : {
      ident_v->symtab_entry = item_v;
    }
    Constable_item_list(item_v,*) : {
      ident_v->symtab_entry = item_v;
      if(warnings) 
        Warning("found multiple definitions for '%k'\n", ident_v,ident_v);
    }
    Niltable_item_list,
    default : {
      if(warnings) 
        Error("found no %k '%k' in symtab\n",ident_v,nflag_v,ident_v);
    }
  }
}
  LocalName : {
    Error("find_ident called with LocalName '%k'\n",ident_v,ident_v);
  }
}
