%{
/*****************************************************************************/
/* Qedo - Quality of Service Enabled Distributed Objects                     */
/*                                                                           */
/* Copyright (c) 2002/2003 by the Qedo Team                                  */
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

#include "lexana.h"
#include "symtab.h"
#include "options.h"
#include "yystype.h"
#ifndef YYSTYPE
#define YYSTYPE YYSTYPE
#endif
#define yyerror(s) yyerror_1(s, yystate)

%}
%token <yt_idl_name>	TOK_identifier

%token <yt_const_expression> integer_literal
	wide_string_literal
	character_literal
	wide_character_literal
	fixed_pt_literal
	floating_pt_literal
	string_literal

%token
	TOK_FALSE
	TOK_Object
	TOK_Object
	TOK_TRUE
	TOK_ValueBase
	TOK__colon__colon_
	TOK__gt__gt_
	TOK__lt__lt_
	TOK_abstract
	TOK_any
	TOK_as
	TOK_attribute
	TOK_bindsTo
	TOK_boolean
	TOK_case
	TOK_catalog
	TOK_char
	TOK_component
	TOK_composition
	TOK_const
	TOK_consumes
	TOK_context
	TOK_custom
	TOK_default
	TOK_delegatesTo
	TOK_double
	TOK_emits
	TOK_entity
	TOK_enum
	TOK_eventtype
	TOK_exception
	TOK_executor
	TOK_extension
	TOK_facet
	TOK_factory
	TOK_finder
	TOK_fixed
	TOK_float
	TOK_getRaises
	TOK_home
	TOK_implements
	TOK_import
	TOK_in
	TOK_inout
	TOK_interface
	TOK_key
	TOK_local
	TOK_long
	TOK_manages
	TOK_module
	TOK_multiple
	TOK_native
	TOK_octet
	TOK_of
	TOK_oneway
	TOK_out
	TOK_primary
	TOK_primaryKey
	TOK_private
	TOK_process
	TOK_provides
	TOK_proxy
	TOK_public
	TOK_publishes
	TOK_raises
	TOK_readonly
	TOK_ref
	TOK_scope
	TOK_segment
	TOK_sequence
	TOK_service
	TOK_session
	TOK_setRaises
	TOK_short
	TOK_sink
	TOK_source
	TOK_state
	TOK_storage
	TOK_storagehome
	TOK_storagetype
	TOK_storedOn
	TOK_stores
	TOK_streamtype
	TOK_string
	TOK_strong
	TOK_struct
	TOK_supports
	TOK_switch
	TOK_truncatable
	TOK_typeId
	TOK_typePrefix
	TOK_typedef
	TOK_union
	TOK_unsigned
	TOK_uses
	TOK_valuetype
	TOK_void
	TOK_wchar
	TOK_wstring

%type <yt_definition_list>		definition_list
										storagehome_body
										storagetype_body
										catalog_body
										abstract_storagehome_body
										abstract_storagetype_body
										opt_home_exports
										home_body
										opt_value_elements
										opt_exports
										interface_body
										component_body
                    opt_members
										member_list
                    proxy_home_members
										delegations
                    delegation_list
                    executor_member_list
										executor_body
                    segment_member_list
                    feature_delegation_list
										feature_delegations
                    catalog_use_dcl_list
										catalog_use_dcl




%token <yt_definition> PREDIRECT

%type <yt_definition>			definition
										type_dcl
										const_dcl
										except_dcl
										except_dcl_header
										interface
										catalog
                    catalog_header
										storagehome
										storagetype
										module
                    module_header
										value
										event
										component
										composition
										composition_header
										home_dcl
                    home_header
										attr_decl
										op_dcl
										op_type_spec
										type_id_dcl
										type_prefix_dcl
										struct_type
										struct_type_header
										union_type
										union_type_header
										enum_type
										sequence_type
										type_spec
										constr_type_spec
										simple_type_spec
										base_type_spec
										type_declarator
										template_type_spec
										floating_pt_type
										wide_string_type
										string_type
										boolean_type
										const_type
										value_base_type
										object_type
										any_type
										octet_type
										char_type
										wide_char_type
										integer_type
										signed_int
										unsigned_int
										signed_short_int
										signed_long_int
										signed_longlong_int
										unsigned_short_int
										unsigned_long_int
										unsigned_longlong_int
										fixed_pt_type
										fixed_pt_const_type
										switch_type_spec
										abstract_storagetype_ref_type
										param_type_spec
										psdl_state_type_spec
										storagetype_dcl
										storagetype_fwd_dcl
										abstract_storagehome
										abstract_storagehome_dcl
										abstract_storagehome_fwd_dcl
										abstract_storagetype
										abstract_storagetype_dcl
										abstract_storagetype_fwd_dcl
										storagehome_member
										abstract_storagetype_member
										storagetype_member
										catalog_member
										key_dcl
										primary_key_dcl
										local_op_dcl
										factory_dcl
										factory_dcl_1
										finder_dcl
										psdl_state_dcl
										store_directive
										ref_rep_directive
										provides_dcl_1
										home_export
										export
										attr_spec
										readonly_attr_spec
										init_dcl
										state_member
										value_element
										value_dcl
										event_dcl
                    value_header
                    event_header
										value_abs_dcl
										event_abs_dcl
										value_abs_header
										event_abs_header
										value_box_dcl
										value_forward_dcl
										event_forward_dcl
										interface_dcl
										forward_dcl
										component_export
										provides_dcl
										uses_decl
										emits_decl
										sink_decl
										source_decl
										publishes_decl
										consumes_decl
										component_forward_dcl
										component_dcl
                    component_header
										interface_type
										interface_header
                    abstract_storagetype_header
                    abstract_storagehome_header
                    storagetype_header
                    storagehome_header
                    element_spec
                    member
                    home_executor_def
                    home_executor_header
                    executor_def
                    executor_header
                    segment_header
                    segment_member
										segment_persistence_dcl
										facet_dcl
                    executor_member
										segment_def
										feature_delegation_spec
                    proxy_home_member
										abstract_spec
										home_delegation_spec
                    delegation
                    feature_delegation
                    catalog_dcl
					streamtype_decl



%type <yt_declarator>			declarator
										simple_declarator
										complex_declarator
										array_declarator

%type <yt_declarators>			declarators
										simple_declarators
                    factory_parameters

%type <yt_fixed_array_size>	fixed_array_size

%type <yt_fixed_array_sizes>	fixed_array_sizes

%type <yt_const_expression>	positive_int_const
										const_exp
										or_expr
										xor_expr
										and_expr
										boolean_literal
										literal
										primary_expr
										unary_expr
										mult_expr
										add_expr
										shift_expr


%type <yt_flag>					category
										param_attribute
										init_param_attribute
										op_attribute
										public_or_private
										abstract_or_local

%type <yt_composition_body>	composition_body

%type <yt_idl_name>				catalog_label
										operation_name
										abstract_storage_home_label
										feature_name
										storage_member_name
										enumerator

%type <yt_idl_identifier>		scoped_name
										catalog_type_spec
										catalog_name
										home_type_name
										storagehome_name 
										storagehome_inh_spec
										storagehome_scope
										storagetype_name
										storagetype_ihn_spec
										abstract_storagehome_name
										abstract_storagetype_name
										primary_key_spec
										home_inheritance_spec
										value_name
										interface_name
										component_inheritance_spec
										imported_scope

%type <yt_idl_identifier_list> idl_identifier_list
										storagetype_impl_spec
										storagehome_impl_spec
										abstract_storagetype_names
										abstract_storagetype_inh_spec
										abstract_storagehome_inh_spec
										abstract_storagehome_names
										catalog_inh_spec
										catalog_names
										get_excep_expr
										set_excep_expr
										exception_list
										value_names
										interface_names
										interface_inheritance_spec
										supported_interface_spec

%type <yt_home_executor_body>	home_executor_body

%type <yt_home_impl_dcl>		home_impl_dcl

%type <yt_abstract_storage_home_binding> abstract_storage_home_binding

%type <yt_abstract_storage_home_name> abstract_storage_home_name

%type <yt_idl_name_list>		identifiers
										enumerators
										scoped_id_list
										operation_list
									  operation_names

%type <yt_abstract_storage_home_delegation_spec> abstract_storage_home_delegation_spec

%type <yt_executor_delegation_spec> executor_delegation_spec

%type <yt_parameter_dcls>		parameter_dcls
										param_dcls
										init_param_decls

%type <yt_param_dcl>				param_dcl
										init_param_decl

%type <yt_attr_raises_expr>	raises_expr
										attr_raises_expr

%type <yt_psdl_concrete_state_type> psdl_concrete_state_type
										storagetype_ref_type

%type <yt_context_expr>			context_expr

%type <yt_const_expression_list> const_expression_list

%type <yt_case_label_list>		case_label_list

%type <yt_case_label>			case_label

%type <yt_idl_case>				case

%type <yt_idl_case_list>		switch_body

%type <yt_value_inheritance_spec> value_inheritance_spec

%type <yt_import>					import

%type <yt_import_list>			import_list

%type <yt_cidl_specification>	specification

%type <yt_proxy_home_def>		proxy_home_def

%type <yt_home_persistence_dcl>	home_persistence_dcl

%type <yt_attr_declarator>		attr_declarator
										readonly_attr_declarator
%%


specification :
	  import_list definition_list
	  { Spec = $$ = CIDLSpecification($1,$2); }
	;

import :
	  TOK_import imported_scope ';'
	  { $$ = Import($2); }
	;

imported_scope :
	  scoped_name
	| string_literal
	  { $$ = LiteralName($1); }
	;

definition :
	  type_dcl ';'
	| const_dcl ';'
	| except_dcl ';'
	| interface ';'
	| catalog ';'
	| storagehome ';'
	| abstract_storagehome ';'
	| storagetype ';'
	| abstract_storagetype ';'
	| module ';'
	| value ';'
	| event ';'
	| type_id_dcl ';'
	| type_prefix_dcl ';'
	| component ';'
	| composition ';'
	| home_dcl ';'
	| streamtype_decl ';'
  | PREDIRECT
	  { $$ = $1; }
	;

type_id_dcl :
	  TOK_typeId scoped_name string_literal
	  { $$ = TypeIdDcl($2,$3); }
	;

type_prefix_dcl :
	  TOK_typePrefix scoped_name string_literal
	  { $$ = TypePrefixDcl($2,$3); 
                add_type_prefix($2,$3);
	  }
	;

component :
	  component_dcl
	| component_forward_dcl
	;

component_forward_dcl :
	  TOK_component TOK_identifier
	  { $$ = ComponentFwdDcl($2); add_declaration(ComponentN(),$2);}
	;

component_dcl :
	  component_header '{' component_body '}'
	  { $$ = fix_definition($1,$3); 
      pop_scope();
    }
	;

component_header :
	  TOK_component TOK_identifier component_inheritance_spec supported_interface_spec
	  { $$ = NComponent(ComponentHeader($2,$3,$4),Nildefinition_list()); 
      add_component($2,$$,$3,$4);
    }
	| TOK_component TOK_identifier supported_interface_spec
	  { $$ = NComponent(ComponentHeader($2,NilIdentifier(),$3),Nildefinition_list()); 
      add_component($2,$$,0,$3);
    }
	| TOK_component TOK_identifier component_inheritance_spec
	  { $$ = NComponent(ComponentHeader($2,$3,Nilidl_identifier_list()),Nildefinition_list()); 
      add_component($2,$$,$3,0);
    }
	| TOK_component TOK_identifier
	  { $$ = NComponent(ComponentHeader($2,NilIdentifier(),Nilidl_identifier_list()),Nildefinition_list()); 
      add_component($2,$$,0,0);
    }
	;

supported_interface_spec :
	  TOK_supports scoped_name idl_identifier_list
	  { $$ = Considl_identifier_list($2,$3); }
	;

component_inheritance_spec :
	  ':' scoped_name
	  { $$ = $2; }
	;

component_body :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| component_export component_body
	  { $$ = Consdefinition_list($1,$2); }
	;

component_export :
	  provides_dcl ';'
	| uses_decl ';'
	| emits_decl ';'
	| publishes_decl ';'
	| consumes_decl ';'
	| attr_decl ';'
	| sink_decl ';'
	| source_decl ';'
	;

provides_dcl :
	  TOK_provides interface_type TOK_identifier
	  { $$ = ProvidesDcl($2,$3); add_provides_dcl($3,$$,$2); }
	;

interface_type :
	  scoped_name
	  { $$ = NScopedName($1); }
	| TOK_Object
	  { $$ = ObjectType(); }
	;

uses_decl :
	  TOK_uses TOK_multiple interface_type TOK_identifier
	  { $$ = UsesDcl(MultipleFlag(),$3,$4); add_uses_dcl($4,$$,$3); }
	| TOK_uses interface_type TOK_identifier
	  { $$ = UsesDcl(NilFlag(),$2,$3); add_uses_dcl($3,$$,$2); }
	;

emits_decl :
	  TOK_emits scoped_name TOK_identifier
	  { $$ = EmitsDcl($2,$3); add_emits_dcl($3,$$,$2); }
	;

publishes_decl :
	  TOK_publishes scoped_name TOK_identifier
	  { $$ = PublishesDcl($2,$3); add_publishes_dcl($3,$$,$2); }
	;

consumes_decl :
	  TOK_consumes scoped_name TOK_identifier
	  { $$ = ConsumesDcl($2,$3); add_consumes_dcl($3,$$,$2); }
	;

streamtype_decl :
      TOK_streamtype '<' '>' TOK_identifier
	  { $$ = AtomicStreamTypeDcl(NilDefinition(), $4); add_streamtype_dcl($4,$$); }
	| TOK_streamtype '<' type_spec '>' TOK_identifier
	  { $$ = AtomicStreamTypeDcl($3, $5); add_valuestreamtype_dcl($5,$$); }
	| TOK_streamtype '{' scoped_name idl_identifier_list '}' TOK_identifier
	  { $$ = LogicalStreamTypeDcl(Considl_identifier_list ($3, $4), $6); add_streamtype_dcl($6,$$); }
    ;

sink_decl :
      TOK_sink scoped_name TOK_identifier
	  { $$ = SinkDcl($2,$3); add_sink_dcl($3,$$,$2); }
    ;

source_decl :
      TOK_source scoped_name TOK_identifier
	  { $$ = SourceDcl(NilFlag(),$2,$3); add_source_dcl($3,$$,$2); }
	| TOK_source TOK_multiple scoped_name TOK_identifier
	  { $$ = SourceDcl(MultipleFlag(),$3,$4); add_source_dcl($4,$$,$3); }
    ;

module :
	  module_header '{' definition_list '}'
	  { $$ = fix_definition($1,$3); pop_scope(); }
	;

/* grammar altered */
module_header :
    TOK_module TOK_identifier
    { $$ = Module($2,Nildefinition_list()); add_module($2,$$); }
	;

interface :
	  interface_dcl
	| forward_dcl
	;

interface_dcl :
	  interface_header '{' interface_body '}'
	  { $$ = fix_definition($1,$3);
      pop_scope();
    }
	;

forward_dcl :
	  abstract_or_local TOK_interface TOK_identifier
	  { $$ = InterfaceFwdDcl($1,$3); add_declaration(InterfaceN(),$3);}
	| TOK_interface TOK_identifier
	  { $$ = InterfaceFwdDcl(NilFlag(),$2); add_declaration(InterfaceN(),$2);}
	;

interface_header :
	  abstract_or_local TOK_interface TOK_identifier interface_inheritance_spec
	  { $$ = Interface(InterfaceHeader($1,$3,$4),Nildefinition_list()); 
	    add_interface($3,$$,$4); 
    }
	| TOK_interface TOK_identifier interface_inheritance_spec
	  { $$ = Interface(InterfaceHeader(NilFlag(),$2,$3),Nildefinition_list()); 
      add_interface($2,$$,$3); 
    }
	| abstract_or_local TOK_interface TOK_identifier
	  { $$ = Interface(InterfaceHeader($1,$3,Nilidl_identifier_list()),Nildefinition_list()); 
      add_interface($3,$$,0); 
    }
	| TOK_interface TOK_identifier
	  { $$ = Interface(InterfaceHeader(NilFlag(),$2,Nilidl_identifier_list()),Nildefinition_list()); 
      add_interface($2,$$,0); 
    }
	;

interface_body :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| 	  export interface_body
	  { $$ = Consdefinition_list($1,$2); }
	;

export :	/* definition */
	  type_dcl ';'
	| const_dcl ';'
	| except_dcl ';'
	| attr_decl ';'
	| op_dcl ';'
	| type_id_dcl ';'
	| type_prefix_dcl ';'
	;

interface_inheritance_spec :
	  ':' interface_names
	  { $$ = $2; }
	;

interface_name :
	  scoped_name;


scoped_name :
     scoped_id_list
	  { $$ = LocalName($1); }
   | TOK__colon__colon_  scoped_id_list
	  { $$ = GlobalName($2); }
   | TOK__colon__colon_ 
	  { $$ = GlobalName(Nilidl_name_list()); }
	;

scoped_id_list :
     TOK_identifier
	  { $$ = Considl_name_list($1,Nilidl_name_list()); }
   | scoped_id_list TOK__colon__colon_ TOK_identifier
	  { $$ = Considl_name_list($3,$1); }
	;
/*
scoped_name :
	  TOK_identifier
	| TOK__colon__colon_ TOK_identifier
	| scoped_name TOK__colon__colon_ TOK_identifier
	;
*/

value :
	  value_dcl
	| value_abs_dcl
	| value_box_dcl
	| value_forward_dcl
	;

value_forward_dcl :
	  TOK_abstract TOK_valuetype TOK_identifier
	  { $$ = AbstractValueTypeFwdDcl($3); add_declaration(ValueTypeN(),$3);}
	| TOK_valuetype TOK_identifier
	  { $$ = ValueTypeFwdDcl( $2); add_declaration(ValueTypeN(),$2);}
	;

value_box_dcl :
	  TOK_valuetype TOK_identifier type_spec
	  { $$ = ValueBox($2,$3); add_value_box($2,$$); pop_scope(); }
	;

value_abs_dcl :
	  value_abs_header '{' opt_exports '}'
	  { $$ = fix_definition($1,$3); 
      pop_scope();
    }
	;

value_abs_header :
 	  TOK_abstract TOK_valuetype TOK_identifier value_inheritance_spec 
	  { $$ = AbstractValueType(ValueHeader(NilFlag(),$3,$4),Nildefinition_list()); 
      add_value_type($3,$$,$4);
    }
 ;

event :
     event_dcl 
   | event_abs_dcl
   | event_forward_dcl
   ;

event_abs_dcl :
     event_abs_header '{'  opt_exports  '}'
	  { $$ = fix_definition($1,$3); 
      pop_scope();
    }
   ;

event_abs_header :
     TOK_abstract TOK_eventtype TOK_identifier value_inheritance_spec
	  { $$ = AbstractEventType(EventTypeHeader(NilFlag(),$3,$4),Nildefinition_list()); 
      add_eventtype($3,$$,$4);
    }
   ;

event_forward_dcl :
     TOK_eventtype  TOK_identifier
	  { $$ = EventTypeFwdDcl( $2); add_declaration(EventTypeN(),$2);}
   | TOK_abstract TOK_eventtype  TOK_identifier
	  { $$ = AbstractEventTypeFwdDcl($3); add_declaration(EventTypeN(),$3);}
   ;

event_dcl :
	  event_header '{' opt_value_elements '}'
	  { $$ = fix_definition($1,$3); 
      pop_scope();
    }
	;

event_header :
	  TOK_custom TOK_eventtype TOK_identifier value_inheritance_spec
	  { $$ = EventType(EventTypeHeader(CustomFlag(),$3,$4),Nildefinition_list()); 
      add_eventtype($3,$$,$4);
    }
	| TOK_eventtype TOK_identifier value_inheritance_spec
	  { $$ = EventType(EventTypeHeader(NilFlag(),$2,$3),Nildefinition_list()); 
      add_eventtype($2,$$,$3);
    }
	;

value_dcl :
	  value_header '{' opt_value_elements '}'
	  { $$ = fix_definition($1,$3); 
      pop_scope();
    }
	;

value_header :
	  TOK_custom TOK_valuetype TOK_identifier value_inheritance_spec
	  { $$ = ValueType(ValueHeader(CustomFlag(),$3,$4),Nildefinition_list()); 
      add_value_type($3,$$,$4);
    }
	| TOK_valuetype TOK_identifier value_inheritance_spec
	  { $$ = ValueType(ValueHeader(NilFlag(),$2,$3),Nildefinition_list()); 
      add_value_type($2,$$,$3);
    }
	;

value_inheritance_spec :
	  /* empty */
	  { $$ = NilValueInheritanceSpec(); }
	| ':' value_names
	  { $$ = ValueInheritanceSpec(NilFlag(),$2,Nilidl_identifier_list()); }
	| ':' TOK_truncatable value_names TOK_supports interface_names
	  { $$ = ValueInheritanceSpec(TruncatableFlag(),$3,$5); }
	| ':' value_names TOK_supports interface_names
	  { $$ = ValueInheritanceSpec(NilFlag(),$2,$4); }
	| TOK_supports interface_names
	  { $$ = ValueInheritanceSpec(NilFlag(),Nilidl_identifier_list(),$2); }
	| ':' TOK_truncatable value_names
	  { $$ = ValueInheritanceSpec(TruncatableFlag(),$3,Nilidl_identifier_list()); }
	;

value_name :
	  scoped_name;

value_element :
	  export
	| state_member
	| init_dcl
	;

state_member :
	  public_or_private type_spec declarators ';'
	  { $$ = StateMember($1,$2,$3); add_value_member($2,$3); }
	;

init_dcl :
	  TOK_factory TOK_identifier '(' init_param_decls ')' ';'
	  { $$ = FactoryDcl($2,$4,NilRaisesExpr());
      add_factory($2,$$,$4,0); }
	;

init_param_decls :
	  init_param_decls ',' init_param_decl
	  { $$ = Consparameter_dcls($3,$1); }
	| init_param_decl
	  { $$ = Consparameter_dcls($1,Nilparameter_dcls()); }
  | /* empty */
    { $$ = Nilparameter_dcls(); }
	;

init_param_decl :
	  init_param_attribute param_type_spec simple_declarator
	  { $$ = ParamDcl($1,$2,$3); }
	;

init_param_attribute :
	  TOK_in
	  { $$ = InFlag(); }
	;

const_dcl :
	  TOK_const const_type TOK_identifier '=' const_exp
	  { $$ = ConstDcl($2,$3,$5); 
      resolve_type($2); 
      /* XXX check for const expression should be used here HB */
      resolve_expression($5);
      add_name(false,ConstantN(),$3,$$,0);
    }
	;

const_type :
	  integer_type
	| char_type
	| wide_char_type
	| boolean_type
	| floating_pt_type
	| string_type
	| wide_string_type
	| fixed_pt_const_type
	| scoped_name
	  { $$ = NScopedName($1); }
	| octet_type
	;

const_exp :
	  or_expr;

or_expr :
	  xor_expr
	| or_expr '|' xor_expr
	  { $$ = Or($1,$3); }
	;

xor_expr :
	  and_expr
	| xor_expr '^' and_expr
	  { $$ = Xor($1,$3); }
	;

and_expr :
	  shift_expr
	| and_expr '&' shift_expr
	  { $$ = And($1,$3); }
	;

shift_expr :
	  add_expr
	| shift_expr TOK__gt__gt_ add_expr
	  { $$ = RShift($1,$3); }
	| shift_expr TOK__lt__lt_ add_expr
	  { $$ = LShift($1,$3); }
	;

add_expr :
	  mult_expr
	| add_expr '+' mult_expr
	  { $$ = Add($1,$3); }
	| add_expr '-' mult_expr
	  { $$ = Minus($1,$3); }
	;

mult_expr :
	  unary_expr
	| mult_expr '*' unary_expr
	  { $$ = Mult($1,$3); }
	| mult_expr '/' unary_expr
	  { $$ = Div($1,$3); }
	| mult_expr '%' unary_expr
	  { $$ = Modulo($1,$3); }
	;

unary_expr :
	  '-' primary_expr
	  { $$ = UMinus($2); }
	| '+' primary_expr
	  { $$ = UPlus($2); }
	| '~' primary_expr
	  { $$ = UNeg($2); }
	| primary_expr
	;

/*
unary_expr :
	  unary_operator primary_expr
	| primary_expr
	;

unary_operator :
	  '-'
	| '+'
	| '~'
	;
*/

primary_expr :
	  scoped_name
	  { $$ = NamedRef($1); }
	| literal
	| '(' const_exp ')'
		{ $$ = $2; }
	;

literal :
	  integer_literal
	| string_literal
	| wide_string_literal
	| character_literal
	| wide_character_literal
	| fixed_pt_literal
	| floating_pt_literal
	| boolean_literal
	;

boolean_literal :
	  TOK_TRUE
	  { $$ = LIT_TRUE(); }
	| TOK_FALSE
	  { $$ = LIT_FALSE(); }
	;

positive_int_const :
	  const_exp;

type_dcl :
	  TOK_typedef type_declarator
	  { $$ = $2; }
	| struct_type
	| union_type
	| enum_type
	| TOK_native simple_declarator
	  { $$ = NativeType($2); add_native_type($$); }
	;

type_declarator :
	  type_spec declarators
	  { $$ = TypeDeclarator($1,$2); add_type_declarators($1,$2,$$); }
	;

type_spec :
	  simple_type_spec
	| constr_type_spec
	;

simple_type_spec :
	  base_type_spec
	| template_type_spec
	| scoped_name 
	  { $$ = NScopedName($1); }
	;

base_type_spec :
	  floating_pt_type
	| integer_type
	| char_type
	| wide_char_type
	| boolean_type
	| octet_type
	| any_type
	| object_type
	| value_base_type
	;

template_type_spec :
	  sequence_type
	| string_type
	| wide_string_type
	| fixed_pt_type
	;

constr_type_spec :
	  struct_type
	| union_type
	| enum_type
	;

declarators :
	  declarator
	  { $$ = Consdeclarators($1,Nildeclarators()); }
	| declarator ',' declarators
	  { $$ = Consdeclarators($1,$3); }
	;

declarator :
	  simple_declarator
	| complex_declarator
	;

simple_declarator :
	  TOK_identifier
	  { $$ = SimpleDeclarator($1); }
	;

complex_declarator :
	  array_declarator;

floating_pt_type :
	  TOK_float
	  { $$ = NFloat(); }
	| TOK_double
	  { $$ = NDouble(); }
	| TOK_long TOK_double
	  { $$ = NLongDouble(); }
	;

integer_type :
	  signed_int
	| unsigned_int
	;

signed_int :
	  signed_short_int
	| signed_long_int
	| signed_longlong_int
	;

signed_short_int :
	  TOK_short
	  { $$ = SignedShortInt(); }
	;

signed_long_int :
	  TOK_long
	  { $$ = SignedLongInt(); }
	;

signed_longlong_int :
	  TOK_long TOK_long
	  { $$ = SignedLongLongInt(); }
	;

unsigned_int :
	  unsigned_short_int
	| unsigned_long_int
	| unsigned_longlong_int
	;

unsigned_short_int :
	  TOK_unsigned TOK_short
	  { $$ = UnsignedShortInt(); }
	;

unsigned_long_int :
	  TOK_unsigned TOK_long
	  { $$ = UnsignedLongInt(); }
	;

unsigned_longlong_int :
	  TOK_unsigned TOK_long TOK_long
	  { $$ = UnsignedLongLongInt(); }
	;

char_type :
	  TOK_char
	  { $$ = CharType(); }
	;

wide_char_type :
	  TOK_wchar
	  { $$ = WCharType(); }
	;

boolean_type :
	  TOK_boolean
	  { $$ = BooleanType(); }
	;

octet_type :
	  TOK_octet
	  { $$ = OctetType(); }
	;

any_type :
	  TOK_any
	  { $$ = AnyType(); }
	;

object_type :
	  TOK_Object
	  { $$ = ObjectType(); }
	 ;

struct_type :
	  struct_type_header '{' member_list '}'
	  { $$ = fix_definition($1,$3); pop_scope(); }
	;

struct_type_header :
	  TOK_struct TOK_identifier
	  { $$ = StructurType($2,Nildefinition_list()); add_struct($2,$$); }
	;

member_list :
	  member
	  { $$ = Consdefinition_list($1,Nildefinition_list()); }
	| member member_list
	  { $$ = Consdefinition_list($1,$2); }
	;

member :
	  type_spec declarators ';'
	  { $$ = Member($1,$2); add_member($$); }
	;

union_type :
	  union_type_header '{' switch_body '}'
	  { $$=fix_case_list($1,$3); pop_scope(); }
	;

union_type_header :
	  TOK_union TOK_identifier TOK_switch '(' switch_type_spec ')'
	  { $$ = UnionType($2,$5,Nilidl_case_list()); add_union($2,$$,$5); }
	;

switch_type_spec :
	  integer_type
	| char_type
	| boolean_type
	| enum_type
	| scoped_name
	  { $$ = NScopedName($1); }
	;

switch_body :
	  case
	  { $$ = Considl_case_list($1,Nilidl_case_list()); }
	| case switch_body
	  { $$ = Considl_case_list($1,$2); }
	;

case :
	  case_label_list element_spec ';'
	  { $$ = Case($1,$2); }
	;

case_label :
	  TOK_case const_exp ':'
	  { $$ = CaseLabel($2); }
	| TOK_default ':'
	  { $$ = Default(); }
	;

element_spec :
	  type_spec declarator
	  { $$ = ElementSpec($1,$2); add_element_spec($$,$1,$2); }
	;

enum_type :
	  TOK_enum TOK_identifier '{' enumerators '}'
	  { $$ = EnumType($2,$4); add_enum($2,$$); }
	;

enumerator :
	  TOK_identifier;

sequence_type :
	  TOK_sequence '<' simple_type_spec ',' positive_int_const '>'
	  { $$ = SequenceType($3,$5); }
	| TOK_sequence '<' simple_type_spec '>'
	  { $$ = SequenceType($3,Nilconst_expression()); }
	;

string_type :
	  TOK_string '<' positive_int_const '>'
	  { $$ = StringType($3); }
	| TOK_string
	  { $$ = StringType(Nilconst_expression()); }
	;

wide_string_type :
	  TOK_wstring '<' positive_int_const '>'
	  { $$ = WideStringType($3); }
	| TOK_wstring
	  { $$ = WideStringType(Nilconst_expression()); }
	;

array_declarator :
	  TOK_identifier fixed_array_sizes
	  { $$ = ArrayDeclarator($1,$2); }
	;

fixed_array_size :
	  '[' positive_int_const ']'
	  { $$ = FixedArraySize($2); }
	;

attr_decl :
	  readonly_attr_spec
	| attr_spec
	;

readonly_attr_spec :
	  TOK_readonly TOK_attribute param_type_spec readonly_attr_declarator
	  { $$ = Attribute(ReadOnlyFlag(),$3,$4); add_attribute($$); }
	;

readonly_attr_declarator :
	  simple_declarator raises_expr
	  { $$ = AttrDeclarator($1,$2); }
	| simple_declarators
	  { $$ = AttrDeclaratorList($1); }
	;

attr_spec :
	  TOK_attribute param_type_spec attr_declarator
	  { $$ = Attribute(NilFlag(),$2,$3); add_attribute($$); }
	;

attr_declarator :
	  simple_declarator attr_raises_expr
	  { $$ = AttrDeclarator($1,$2); }
	| simple_declarators
	  { $$ = AttrDeclaratorList($1); }
	;

attr_raises_expr :
	  get_excep_expr set_excep_expr
	  { $$ = GetSetExcepExpr($1,$2); }
	| get_excep_expr
	  { $$ = GetExcepExpr($1); }
	| set_excep_expr
	  { $$ = SetExcepExpr($1); }
	;

get_excep_expr :
	  TOK_getRaises exception_list
	  { $$ = $2; }
	;

set_excep_expr :
	  TOK_setRaises exception_list
	  { $$ = $2; }
	;

exception_list :
	  '(' scoped_name idl_identifier_list ')'
	  { $$ = Considl_identifier_list($2,$3); }
	;

home_dcl :
	  home_header home_body
	  { $$ = fix_definition($1,$2); 
      pop_scope();
    }
   ;

home_header :
	  TOK_home TOK_identifier home_inheritance_spec supported_interface_spec TOK_manages scoped_name primary_key_spec
	  { $$ = HomeDcl(HomeHeader($2,$3,$4,$6,$7),Nildefinition_list());
      add_home($2,$$,$3,$4,$6,$7);
    }
	 | TOK_home TOK_identifier supported_interface_spec TOK_manages scoped_name primary_key_spec
	  { $$ = HomeDcl(HomeHeader($2,NilIdentifier(),$3,$5,$6),Nildefinition_list());
      add_home($2,$$,0,$3,$5,$6);
    }
	| TOK_home TOK_identifier home_inheritance_spec TOK_manages scoped_name primary_key_spec
	  { $$ = HomeDcl(HomeHeader($2,$3,Nilidl_identifier_list(),$5,$6),Nildefinition_list());
      add_home($2,$$,$3,0,$5,$6);
    }
	| TOK_home TOK_identifier TOK_manages scoped_name primary_key_spec
	  { $$ = HomeDcl(HomeHeader($2,NilIdentifier(),Nilidl_identifier_list(),$4,$5),Nildefinition_list());
      add_home($2,$$,0,0,$4,$5);
    }
	| TOK_home TOK_identifier home_inheritance_spec TOK_manages scoped_name
	  { $$ = HomeDcl(HomeHeader($2,$3,Nilidl_identifier_list(),$5,NilIdentifier()),Nildefinition_list());
      add_home($2,$$,$3,0,$5,0);
    }
	| TOK_home TOK_identifier home_inheritance_spec supported_interface_spec TOK_manages scoped_name
	  { $$ = HomeDcl(HomeHeader($2,$3,$4,$6,NilIdentifier()),Nildefinition_list());
      add_home($2,$$,$3,$4,$6,0);
    }
	| TOK_home TOK_identifier supported_interface_spec TOK_manages scoped_name
	  { $$ = HomeDcl(HomeHeader($2,NilIdentifier(),$3,$5,NilIdentifier()),Nildefinition_list());
      add_home($2,$$,0,$3,$5,0);
    }
	| TOK_home TOK_identifier TOK_manages scoped_name
	  { $$ = HomeDcl(HomeHeader($2,NilIdentifier(),Nilidl_identifier_list(),$4,NilIdentifier()),Nildefinition_list());
      add_home($2,$$,0,0,$4,0);
    }
	;

home_inheritance_spec :
	  ':' scoped_name
	  { $$ = $2; }
	;

primary_key_spec :
	  TOK_primaryKey scoped_name
	  { $$ = $2; }
	;

home_body :
	  '{' opt_home_exports '}'
	  { $$ = $2; }
	;

home_export :
	  export
	| factory_dcl ';'
	| finder_dcl ';'
	;

factory_dcl :
	  TOK_factory TOK_identifier '(' init_param_decls ')' raises_expr
	  { $$ = FactoryDcl($2,$4,$6); 
      add_factory($2,$$,$4,$6);
    }
	| TOK_factory TOK_identifier '(' init_param_decls ')'
	  { $$ = FactoryDcl($2,$4,NilRaisesExpr());
      add_factory($2,$$,$4,0);
    }
	;

factory_dcl_1 :
	  TOK_factory TOK_identifier factory_parameters 
	  { $$ = FactoryDcl1($2,$3); }
  ;

factory_parameters :
    '(' simple_declarators ')'
    { $$ = $2; }
  | '(' ')'
    { $$ = Nildeclarators(); }
  ;

finder_dcl :
	  TOK_finder TOK_identifier '(' init_param_decls ')' raises_expr
	  { $$ = FinderDcl($2,$4,$6); 
      add_finder($2,$$,$4,$6);
    }
	| TOK_finder TOK_identifier '(' init_param_decls ')'
	  { $$ = FinderDcl($2,$4,NilRaisesExpr());
      add_finder($2,$$,$4,0);
    }
	;

except_dcl :
	  except_dcl_header '{' opt_members '}'
	  { $$ = fix_definition($1,$3); pop_scope(); }
	;

except_dcl_header :
	  TOK_exception TOK_identifier 
	  { $$ = ExceptDcl($2,Nildefinition_list()); add_exception($2,$$); }
	;

op_dcl :
	  op_attribute op_type_spec TOK_identifier parameter_dcls raises_expr context_expr
	  { $$ = OpDcl($1,$2,$3,$4,$5,$6);
      add_operation($3,$$,$2,$4,$5,$1);
    }
	| op_type_spec TOK_identifier parameter_dcls raises_expr context_expr
	  { $$ = OpDcl(NilFlag(),$1,$2,$3,$4,$5);
      add_operation($2,$$,$1,$3,$4,0);
    }
	| op_attribute op_type_spec TOK_identifier parameter_dcls context_expr
	  { $$ = OpDcl($1,$2,$3,$4,NilRaisesExpr(),$5);
      add_operation($3,$$,$2,$4,0,$1);
    }
	| op_type_spec TOK_identifier parameter_dcls context_expr
	  { $$ = OpDcl(NilFlag(),$1,$2,$3,NilRaisesExpr(),$4);
      add_operation($2,$$,$1,$3,0,0);
    }
	| op_attribute op_type_spec TOK_identifier parameter_dcls raises_expr
	  { $$ = OpDcl($1,$2,$3,$4,$5,NilContextExpr());
      add_operation($3,$$,$2,$4,$5,$1);
    }
	| op_type_spec TOK_identifier parameter_dcls raises_expr
	  { $$ = OpDcl(NilFlag(),$1,$2,$3,$4,NilContextExpr());
      add_operation($2,$$,$1,$3,$4,0);
    }
	| op_attribute op_type_spec TOK_identifier parameter_dcls
	  { $$ = OpDcl($1,$2,$3,$4,NilRaisesExpr(),NilContextExpr());
      add_operation($3,$$,$2,$4,0,$1);
    }
	| op_type_spec TOK_identifier parameter_dcls
	  { $$ = OpDcl(NilFlag(),$1,$2,$3,NilRaisesExpr(),NilContextExpr());
      add_operation($2,$$,$1,$3,0,0);
    }
	;

op_attribute :
	  TOK_oneway
	  { $$ = OneWayFlag(); }
	;

op_type_spec :
	  param_type_spec
	| TOK_void
	  { $$ = Void(); }
	;

parameter_dcls :
	  '(' param_dcls ')'
	  { $$ = $2; }
	| '(' ')'
	  { $$ = Nilparameter_dcls(); }
	;

param_dcl :
	  param_attribute param_type_spec simple_declarator
	  { $$ = ParamDcl($1,$2,$3); }
	;

param_attribute :
	  TOK_in
	  { $$ = InFlag(); }
	| TOK_out
	  { $$ = OutFlag(); }
	| TOK_inout
	  { $$ = InOutFlag(); }
	;

raises_expr :
	  TOK_raises '(' scoped_name idl_identifier_list ')'
	  { $$ = RaisesExpr(Considl_identifier_list($3,$4)); }
	;

context_expr :
	  TOK_context '(' string_literal const_expression_list ')'
	  { $$ = ContextExpr(Consconst_expression_list($3,$4)); }
	;

param_type_spec :
	  base_type_spec
	| string_type
	| wide_string_type
	| scoped_name
	  { $$ = NScopedName( $1); }
	;

fixed_pt_type :
	  TOK_fixed '<' positive_int_const ',' positive_int_const '>'
	  { $$ = FixedPtType($3,$5); }
	;

fixed_pt_const_type :
	  TOK_fixed
	  { $$ = FixedType(); }
	;

value_base_type :
	  TOK_ValueBase
	  { $$ = ValueBaseType(); }
	;

abstract_storagehome_name :
	  scoped_name;

abstract_storagetype :
	  abstract_storagetype_dcl
	| abstract_storagetype_fwd_dcl
	;

abstract_storagetype_dcl :
	  abstract_storagetype_header '{' abstract_storagetype_body '}'
	  { $$ = fix_definition($1,$3); pop_scope(); }
	;

abstract_storagetype_fwd_dcl :
	  TOK_abstract TOK_storagetype TOK_identifier
	  { $$ = AbstractStorageTypeFwdDcl($3); add_declaration(AbstractStorageTypeN(),$3);}
	;

abstract_storagetype_header :
	  TOK_abstract TOK_storagetype TOK_identifier abstract_storagetype_inh_spec
	  { $$ = AbstractStorageType(AbstractStorageTypeHeader($3,$4),Nildefinition_list()); 
      add_abstract_storagetype($3,$$,$4); 
    }
	| TOK_abstract TOK_storagetype TOK_identifier
	  { $$ = AbstractStorageType(AbstractStorageTypeHeader($3,Nilidl_identifier_list()),Nildefinition_list()); 
      add_abstract_storagetype($3,$$,0); 
    }
	;

abstract_storagetype_body :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| abstract_storagetype_member abstract_storagetype_body
	  { $$ = Consdefinition_list($1,$2); }
	;

abstract_storagetype_member :
	  psdl_state_dcl ';'
	| local_op_dcl ';'
	;

abstract_storagetype_inh_spec :
	  ':' abstract_storagetype_names
	  { $$ = $2; }
	;

abstract_storagetype_name :
	  scoped_name;

psdl_state_dcl :
	  TOK_readonly TOK_state psdl_state_type_spec simple_declarators
	  { $$ = PsdlStateDcl(ReadOnlyFlag(),$3,$4); add_psdl_states($4,$$,$3);}
	| TOK_state psdl_state_type_spec simple_declarators
	  { $$ = PsdlStateDcl(NilFlag(),$2,$3); add_psdl_states($3,$$,$2);}
	;

psdl_state_type_spec :
	  base_type_spec
	| string_type
	| wide_string_type
	| abstract_storagetype_ref_type
	| scoped_name
	  { $$ = NScopedName($1); }
	;

abstract_storagetype_ref_type :
	  TOK_strong TOK_ref '<' abstract_storagetype_name '>'
	  { $$ = StorageTypeRef(StrongFlag(),$4); }
	| TOK_ref '<' abstract_storagetype_name '>'
	  { $$ = StorageTypeRef(NilFlag(),$3); }
	;

abstract_storagehome :
	  abstract_storagehome_dcl
	| abstract_storagehome_fwd_dcl
	;

abstract_storagehome_fwd_dcl :
	  TOK_abstract TOK_storagehome TOK_identifier
	  { $$ = AbstractStorageHomeFwdDcl($3); add_declaration(AbstractStorageHomeN(),$3); }
	;

abstract_storagehome_dcl :
	  abstract_storagehome_header '{' abstract_storagehome_body '}'
	  { $$ = fix_definition($1,$3); pop_scope();}
   ;

abstract_storagehome_header :
	  TOK_abstract TOK_storagehome TOK_identifier TOK_of abstract_storagetype_name abstract_storagehome_inh_spec
	  { $$ = AbstractStorageHome(AbstractStorageHomeHeader($3,$5,$6),Nildefinition_list());
      add_abstract_storagehome($3,$$,$5,$6);
    }
	| TOK_abstract TOK_storagehome TOK_identifier TOK_of abstract_storagetype_name
	  { $$ = AbstractStorageHome(AbstractStorageHomeHeader($3,$5,Nilidl_identifier_list()),Nildefinition_list()); 
      add_abstract_storagehome($3,$$,$5,0);
    }
	;

abstract_storagehome_body :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| storagehome_member abstract_storagehome_body
	  { $$ = Consdefinition_list($1,$2); }
	;

storagehome_member :
	  local_op_dcl ';'
	| key_dcl ';'
	| factory_dcl_1 ';'
	;

abstract_storagehome_inh_spec :
	  ':' abstract_storagehome_names
	  { $$ = $2; }
	;

local_op_dcl :
	  op_type_spec TOK_identifier parameter_dcls raises_expr
	  { $$ = LocalOpDcl($1,$2,$3,$4); 
      add_operation($2,$$,$1,$3,$4,0);
    }
	| op_type_spec TOK_identifier parameter_dcls
	  { $$ = LocalOpDcl($1,$2,$3,NilRaisesExpr()); 
      add_operation($2,$$,$1,$3,0,0);
    }
	;

key_dcl :
	  TOK_key TOK_identifier '(' simple_declarators ')'
	  { $$ = KeyDcl($2,$4); add_name(false,KeyN(),$2,$$,0); }
	| TOK_key TOK_identifier
	  { $$ = KeyDcl($2,Nildeclarators()); add_name(false,KeyN(),$2,$$,0); }
	;

catalog :
    catalog_header '{' catalog_body '}'
    { $$ = fix_definition($1,$3); pop_scope(); }
	;

/* differs from original grammar! catalog_header is new */
catalog_header :
	  TOK_catalog TOK_identifier catalog_inh_spec
	  { $$ = Catalog($2,$3,Nildefinition_list()); add_catalog($2,$$,$3); }
	| TOK_catalog TOK_identifier
	  { $$ = Catalog($2,Nilidl_identifier_list(),Nildefinition_list()); add_catalog($2,$$,0); }
	;

catalog_inh_spec :
	  ':' catalog_names
	  { $$ = $2; }
	;

catalog_name :
	  scoped_name;

catalog_body :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| catalog_member catalog_body
	  { $$ = Consdefinition_list($1,$2); }
	;

catalog_member :
	  provides_dcl_1 ';'
	| local_op_dcl ';'
	;

provides_dcl_1 :
	  TOK_provides abstract_storagehome_name simple_declarator
	  { $$ = ProvidesDcl1($2,$3); add_provides($3,$$,$2);}
	;

storagetype :
	  storagetype_dcl
	| storagetype_fwd_dcl
	;

storagetype_dcl :
	  storagetype_header '{' storagetype_body '}'
	  { $$ = fix_definition($1,$3); pop_scope(); }
	;

storagetype_fwd_dcl :
	  TOK_storagetype TOK_identifier
	  { $$ = StorageTypeFwdDcl($2); }
	;

storagetype_header :
	  TOK_storagetype TOK_identifier storagetype_ihn_spec storagetype_impl_spec
	  { $$ = StorageType(StorageTypeHeader($2,$3,$4),Nildefinition_list()); 
      add_storagetype($2,$$,$3,$4);
    }
	| TOK_storagetype TOK_identifier storagetype_impl_spec
	  { $$ = StorageType(StorageTypeHeader($2,NilIdentifier(),$3),Nildefinition_list()); 
      add_storagetype($2,$$,0,$3);
    }
	| TOK_storagetype TOK_identifier storagetype_ihn_spec
	  { $$ = StorageType(StorageTypeHeader($2,$3,Nilidl_identifier_list()),Nildefinition_list()); 
      add_storagetype($2,$$,$3,0);
    }
	| TOK_storagetype TOK_identifier
	  { $$ = StorageType(StorageTypeHeader($2,NilIdentifier(),Nilidl_identifier_list()),Nildefinition_list()); 
      add_storagetype($2,$$,0,0);
    }
	;

storagetype_body :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| storagetype_member storagetype_body
	  { $$ = Consdefinition_list($1,$2); }
	;

storagetype_member :
	  psdl_state_dcl ';'
	| store_directive ';'
	| ref_rep_directive ';'
	;

storagetype_ihn_spec :
	  ':' storagetype_name
	  { $$ = $2; }
	;

storagetype_name :
	  scoped_name;

storagetype_ref_type :
	  TOK_ref '<' storagetype_name '>'
	  { $$ = PsdlConcreteStateTypeRef($3); }
	;

storagehome_scope :
	  TOK_scope storagetype_name
	  { $$ = $2; }
	;

store_directive :
	  TOK_stores simple_declarator TOK_as psdl_concrete_state_type storagehome_scope
	  { $$ = StoreDirective($2,$4,$5); }
	| TOK_stores simple_declarator TOK_as psdl_concrete_state_type
	  { $$ = StoreDirective($2,$4,NilIdentifier()); }
	;

psdl_concrete_state_type :
	  storagetype_name
	  { $$ = PsdlConcreteStateTypeName($1); }
	| storagetype_ref_type
	;

ref_rep_directive :
	  TOK_ref '(' simple_declarators ')'
	  { $$ = RefRepDirective($3); }
	;

storagehome :
	  storagehome_header '{' storagehome_body '}'
	  { $$ = fix_definition($1,$3); pop_scope(); }
	;

storagehome_header :
	  TOK_storagehome TOK_identifier TOK_of storagetype_name storagehome_inh_spec storagehome_impl_spec
    { $$ = StorageHome(StorageHomeHeader($2,$4,$5,$6,NilDefinition()),Nildefinition_list()); 
      add_storagehome($2,$$,$4,$5,$6,0);
    }
	| TOK_storagehome TOK_identifier TOK_of storagetype_name storagehome_impl_spec
    { $$ = StorageHome(StorageHomeHeader($2,$4,NilIdentifier(),$5,NilDefinition()),Nildefinition_list()); 
      add_storagehome($2,$$,$4,0,$5,0);
    }
	| TOK_storagehome TOK_identifier TOK_of storagetype_name storagehome_inh_spec
    { $$ = StorageHome(StorageHomeHeader($2,$4,$5,Nilidl_identifier_list(),NilDefinition()),Nildefinition_list()); 
      add_storagehome($2,$$,$4,$5,0,0);
    }
	| TOK_storagehome TOK_identifier TOK_of storagetype_name
    { $$ = StorageHome(StorageHomeHeader($2,$4,NilIdentifier(),Nilidl_identifier_list(),NilDefinition()),Nildefinition_list()); 
      add_storagehome($2,$$,$4,0,0,0);
    }
	| TOK_storagehome TOK_identifier TOK_of storagetype_name storagehome_inh_spec storagehome_impl_spec primary_key_dcl
    { $$ = StorageHome(StorageHomeHeader($2,$4,$5,$6,0),Nildefinition_list()); 
      add_storagehome($2,$$,$4,$5,$6,0);
    }
	| TOK_storagehome TOK_identifier TOK_of storagetype_name storagehome_impl_spec primary_key_dcl
    { $$ = StorageHome(StorageHomeHeader($2,$4,NilIdentifier(),$5,$6),Nildefinition_list()); 
      add_storagehome($2,$$,$4,0,$5,$6);
    }
	| TOK_storagehome TOK_identifier TOK_of storagetype_name storagehome_inh_spec primary_key_dcl
    { $$ = StorageHome(StorageHomeHeader($2,$4,$5,Nilidl_identifier_list(),$6),Nildefinition_list()); 
      add_storagehome($2,$$,$4,$5,0,$6);
    }
	| TOK_storagehome TOK_identifier TOK_of storagetype_name primary_key_dcl
    { $$ = StorageHome(StorageHomeHeader($2,$4,NilIdentifier(),Nilidl_identifier_list(),$5),Nildefinition_list()); 
      add_storagehome($2,$$,$4,0,0,0);
    }
	;

storagehome_body :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| storagehome_member storagehome_body
	  { $$ = Consdefinition_list($1,$2); }
	;

storagehome_inh_spec :
	  ':' storagehome_name
	  { $$ = $2; }
	;

storagehome_name :
	  scoped_name;

storagetype_impl_spec :
	  TOK_implements abstract_storagetype_names
	  { $$ = $2; }
	;

storagehome_impl_spec :
	  TOK_implements abstract_storagehome_names
	  { $$ = $2; }
	;

primary_key_dcl :
	  TOK_primary TOK_key TOK_identifier
	  { $$ = PrimaryKeyDcl (LocalName(Considl_name_list($3,Nilidl_name_list()))); 
      add_primary_key($$);}
	| TOK_primary TOK_key TOK_ref
	  { $$ = PrimaryKeyRef(); }
	;

composition :
	  composition_header '{' composition_body '}'
	  { $$=fix_composition($1,$3); 
      pop_scope();
    }
	;

composition_header :
	  TOK_composition category TOK_identifier
	  { $$=Composition($3,$2,NilCompositionBody()); 
      add_composition($3,$$);
    }
	;
category :
	  TOK_entity
	  { $$ = EntityFlag(); }
	| TOK_process
	  { $$ = ProcessFlag(); }
	| TOK_service
	  { $$ = ServiceFlag(); }
	| TOK_session
	  { $$ = SessionFlag(); }
	| TOK_extension
	  { $$ = ExtensionFlag(); }
	;

composition_body :
	  catalog_use_dcl home_executor_def proxy_home_def
	  { $$ = CompositionBody($1,$2,$3); }
	| home_executor_def proxy_home_def
	  { $$ = CompositionBody(Nildefinition_list(),$1,$2); }
	| catalog_use_dcl home_executor_def
	  { $$ = CompositionBody($1,$2,NilProxyHomeDef()); }
	| home_executor_def
	  { $$ = CompositionBody(Nildefinition_list(),$1,NilProxyHomeDef()); }
	;

catalog_use_dcl :
	  TOK_uses TOK_catalog '{' catalog_use_dcl_list '}' ';'
	  { $$ = $4; }
	;

catalog_dcl :
	  catalog_type_spec catalog_label
     { $$ = CatalogDcl($2,$1); 
       add_catalog_dcl($2,$$,$1);
     }
	;

catalog_type_spec :
	  scoped_name;

catalog_label :
	  TOK_identifier;

home_executor_def :
	  home_executor_header '{' home_executor_body '}' ';'
	  { $$ = fix_home_executor($1,$3); 
      pop_scope();
    };

home_executor_header :
	  TOK_home TOK_executor TOK_identifier
	  { $$ = HomeExecutorDef($3,NilHomeExecutorBody()); 
      add_home_executor($3,$$);
    };

home_executor_body :
	  home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def abstract_storage_home_delegation_spec executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,$2,$3,$4,$5,$6,$7); }
	| home_impl_dcl home_persistence_dcl executor_def abstract_storage_home_delegation_spec executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,$4,$5,$6); }
	| home_impl_dcl abstract_storage_home_binding executor_def abstract_storage_home_delegation_spec executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,$4,$5,NilProxyHomeMember()); }
	| home_impl_dcl executor_def abstract_storage_home_delegation_spec executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,$3,$4,$5); }
	| home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,$2,$3,$4,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl home_persistence_dcl executor_def executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,NilAbstractStorageHomeDelegationSpec(),$4,$5); }
	| home_impl_dcl abstract_storage_home_binding executor_def executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,NilAbstractStorageHomeDelegationSpec(),$4,$5); }
	| home_impl_dcl executor_def executor_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,NilAbstractStorageHomeDelegationSpec(),$3,$4); }
	| home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def abstract_storage_home_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,$2,$3,$4,$5,NilExecutorDelegationSpec(),$6); }
	| home_impl_dcl home_persistence_dcl executor_def abstract_storage_home_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,$4,NilExecutorDelegationSpec(),$5); }
	| home_impl_dcl abstract_storage_home_binding executor_def abstract_storage_home_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,$4,NilExecutorDelegationSpec(),$5); }
	| home_impl_dcl executor_def abstract_storage_home_delegation_spec abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,$3,NilExecutorDelegationSpec(),$4); }
	| home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def abstract_spec
	  { $$ = HomeExecutorBody($1,$2,$3,$4,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),$5); }
	| home_impl_dcl home_persistence_dcl executor_def abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),$4); }
	| home_impl_dcl abstract_storage_home_binding executor_def abstract_spec
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),$4); }
	| home_impl_dcl executor_def abstract_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),$3); }
	| home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def abstract_storage_home_delegation_spec executor_delegation_spec
	  { $$ = HomeExecutorBody($1,$2,$3,$4,$5,$6,NilProxyHomeMember()); }
	| home_impl_dcl home_persistence_dcl executor_def abstract_storage_home_delegation_spec executor_delegation_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,$4,$5,NilProxyHomeMember()); }
	| home_impl_dcl abstract_storage_home_binding executor_def abstract_storage_home_delegation_spec executor_delegation_spec
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,$4,$5,NilProxyHomeMember()); }
	| home_impl_dcl executor_def abstract_storage_home_delegation_spec executor_delegation_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,$3,$4,NilProxyHomeMember()); }
	| home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def executor_delegation_spec
	  { $$ = HomeExecutorBody($1,$2,$3,$4,NilAbstractStorageHomeDelegationSpec(),$5,NilProxyHomeMember()); }
	| home_impl_dcl home_persistence_dcl executor_def executor_delegation_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,NilAbstractStorageHomeDelegationSpec(),$4,NilProxyHomeMember()); }
	| home_impl_dcl abstract_storage_home_binding executor_def executor_delegation_spec
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,NilAbstractStorageHomeDelegationSpec(),$4,NilProxyHomeMember()); }
	| home_impl_dcl executor_def executor_delegation_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,NilAbstractStorageHomeDelegationSpec(),$3,NilProxyHomeMember()); }
	| home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def abstract_storage_home_delegation_spec
	  { $$ = HomeExecutorBody($1,$2,$3,$4,$5,NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl home_persistence_dcl executor_def abstract_storage_home_delegation_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,$4,NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl abstract_storage_home_binding executor_def abstract_storage_home_delegation_spec
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,$4,NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl executor_def abstract_storage_home_delegation_spec
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,$3,NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl abstract_storage_home_binding home_persistence_dcl executor_def
	  { $$ = HomeExecutorBody($1,$2,$3,$4,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl home_persistence_dcl executor_def
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),$2,$3,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl abstract_storage_home_binding executor_def
	  { $$ = HomeExecutorBody($1,$2,NilHomePersistenceDcl(),$3,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	| home_impl_dcl executor_def
	  { $$ = HomeExecutorBody($1,NilAbstractStorageHomeBinding(),NilHomePersistenceDcl(),$2,NilAbstractStorageHomeDelegationSpec(),NilExecutorDelegationSpec(),NilProxyHomeMember()); }
	;

home_impl_dcl :
	  TOK_implements home_type_name ';'
	  { $$ = HomeImplDcl($2); }
	;

home_type_name :
	  scoped_name
    { $$=$1,
      resolve_home_name($1); 
    }
  ;

abstract_storage_home_binding :
	  TOK_bindsTo abstract_storage_home_name ';'
	  { $$ = AbstractStorageHomeBinding($2); }
   ;

abstract_storage_home_name :
	  catalog_label '.' abstract_storage_home_label
	  { $$ = AbstractStorageHomeName($1,$3); 
      add_abstract_storage_home_name($1,$3);
    }
	;

abstract_storage_home_label :
	  TOK_identifier;

home_persistence_dcl :
	  TOK_storedOn abstract_storage_home_name ';'
	  { $$ = HomePersistenceDcl($2);}
	;

executor_def :
	  executor_header executor_body ';'
	  { $$ = fix_definition($1,$2);
      pop_scope();
    }
	| executor_header ';'
	  { $$ = $1; 
      pop_scope();
    }
	;

executor_header :
	  TOK_manages TOK_identifier 
    { $$ = ExecutorDef($2,Nildefinition_list());
      add_executor($2,$$);
    };

executor_body :
	  '{' executor_member_list '}'
	  { $$ = $2; }
	;

executor_member :
	  segment_def
	| feature_delegation_spec
	;

segment_def :
	  segment_header '{' segment_member_list '}'
	  { $$ = fix_definition($1,$3); 
      pop_scope();
    };

segment_header :
	  TOK_segment TOK_identifier
	  { $$ = SegmentDef($2,Nildefinition_list()); 
      add_segment($2,$$);
    };

segment_member :
	  segment_persistence_dcl ';'
	| facet_dcl ';'
	;

segment_persistence_dcl :
	  TOK_storedOn abstract_storage_home_name ';'
	  { $$ = SegmentPersistenceDcl($2); }
	;

facet_dcl :
	  TOK_provides TOK_facet identifiers
	  { $$ = FacetDcl($3); 
      add_facet_dcl($3,$$);
    }
	;

feature_delegation_spec :
	  TOK_delegatesTo TOK_storage feature_delegation_list
	  { $$ = FeatureDelegationSpec($3); }
	;

feature_delegation_list :
	  '(' feature_delegations ')'
	  { $$ = $2; }
	;

feature_delegation :
	  feature_name ':' storage_member_name
	  { $$ = FeatureDelegation($1,$3); }
	;

feature_name :
	  TOK_identifier;

abstract_storage_home_delegation_spec :
	  TOK_delegatesTo TOK_abstract TOK_storagehome delegation_list ';'
	  { $$ = AbstractStorageHomeDelegationSpec($4); }
	;

executor_delegation_spec :
	  TOK_delegatesTo TOK_executor delegation_list ';'
	  { $$ = ExecutorDelegationSpec($3); }
	;

delegation_list :
	  '(' delegations ')'
	  { $$ = $2; }
	;

delegation :
	  operation_name ':' operation_name
	  { $$ = OperationPair($1,$3); }
	| operation_name
	  { $$ = Operation($1); }
	;

operation_name :
	  TOK_identifier;

abstract_spec :
	  TOK_abstract operation_list ';'
	  { $$=AbstractSpec($2); }
   ;

operation_list :
	  '(' operation_names ')'
	  { $$ = $2; }
	;

proxy_home_def :
	  TOK_proxy TOK_home TOK_identifier '{' proxy_home_members '}' ';'
	  { $$ = ProxyHomeDef($3,$5); }
	;

proxy_home_member :
	  home_delegation_spec ';'
	| abstract_spec
	;

home_delegation_spec :
	  TOK_delegatesTo TOK_home delegation_list
	  { $$=HomeDelegationSpec($3); }
	;

storage_member_name :
	  TOK_identifier;

definition_list :
	  definition
	  { $$=Consdefinition_list($1,Nildefinition_list()); }
	| definition definition_list
	  { $$=Consdefinition_list($1,$2); }
	;

import_list :
	  /* empty */
	  { $$ = Nilimport_list(); }
	| import_list import
	  { $$ = Consimport_list($2,$1); }
	;

idl_identifier_list :
	  /* empty */
	  { $$ = Nilidl_identifier_list(); }
	| idl_identifier_list ',' scoped_name
	  { $$ = Considl_identifier_list($3,$1); }
	;

abstract_or_local :
	  TOK_abstract
	  { $$ = LocalFlag(); }
	| TOK_local
	  { $$ = AbstractFlag(); }
	;

interface_names :
	  interface_name
	  { $$ = Considl_identifier_list($1,Nilidl_identifier_list()); }
	| interface_name ',' interface_names
	  { $$ = Considl_identifier_list($1,$3); }
	;

opt_exports :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| export opt_exports
	  { $$ = Consdefinition_list($1,$2); }
	;

opt_value_elements :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| value_element opt_value_elements
	  { $$ = Consdefinition_list($1,$2); }
	;

value_names :
	  value_name
	  { $$ = Considl_identifier_list($1,Nilidl_identifier_list()); }
	| value_name ',' value_names
	  { $$ = Considl_identifier_list($1,$3); }
	;

public_or_private :
	  TOK_public
	  { $$ = PublicFlag(); }
	| TOK_private
	  { $$ = PrivateFlag(); }
	;

case_label_list :
	  case_label
	  { $$ = Conscase_label_list($1,Nilcase_label_list()); }
	| case_label_list case_label
	  { $$ = Conscase_label_list($2,$1); }
	;

enumerators :
	  enumerator
	  { $$ = Considl_name_list($1,Nilidl_name_list()); }
	| enumerators ',' enumerator
	  { $$ = Considl_name_list($3,$1); }
	;

fixed_array_sizes :
	  fixed_array_size
	  { $$=Consfixed_array_sizes($1,Nilfixed_array_sizes()); }
	| fixed_array_sizes fixed_array_size
	  { $$=Consfixed_array_sizes($2,$1); }
	;

opt_home_exports :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| home_export opt_home_exports
	  { $$ = Consdefinition_list($1,$2); }
	;

opt_members :
	  /* empty */
	  { $$ = Nildefinition_list(); }
	| member opt_members
	  { $$ = Consdefinition_list($1,$2); }
	;

param_dcls :
	  param_dcl
	  { $$ = Consparameter_dcls($1,Nilparameter_dcls()); }
	| param_dcls ',' param_dcl
	  { $$ = Consparameter_dcls($3,$1); }
	;

const_expression_list :
	  /* empty */
	  { $$ = Nilconst_expression_list(); }
	| const_expression_list ',' string_literal
	  { $$ = Consconst_expression_list($3,$1); }
	;

abstract_storagetype_names :
	  abstract_storagetype_name
	  { $$ = Considl_identifier_list($1,Nilidl_identifier_list()); }
	| abstract_storagetype_names ',' abstract_storagetype_name
	  { $$ = Considl_identifier_list($3,$1); }
	;

simple_declarators :
	  simple_declarator
	  { $$ = Consdeclarators($1,Nildeclarators()); }
	| simple_declarator ',' simple_declarators
	  { $$ = Consdeclarators($1,$3); }
	;

abstract_storagehome_names :
	  abstract_storagehome_name
	  { $$ = Considl_identifier_list($1,Nilidl_identifier_list()); }
	| abstract_storagehome_names ',' abstract_storagehome_name
	  { $$ = Considl_identifier_list($3,$1); }
	;

catalog_names :
	  catalog_name
	  { $$ = Considl_identifier_list($1,Nilidl_identifier_list()); }
	| catalog_names ',' catalog_name
	  { $$ = Considl_identifier_list($3,$1); }
	;

catalog_use_dcl_list :
	  catalog_dcl
	  { $$=Consdefinition_list($1,Nildefinition_list()); }
	| catalog_dcl catalog_use_dcl_list
	  { $$=Consdefinition_list($1,$2); }
	;

executor_member_list :
	  executor_member
	  { $$=Consdefinition_list($1,Nildefinition_list()); }
	| executor_member executor_member_list
	  { $$=Consdefinition_list($1,$2); }
	;

segment_member_list :
	  segment_member
	  { $$ = Consdefinition_list($1,Nildefinition_list()); }
	| segment_member segment_member_list
	  { $$ = Consdefinition_list($1,$2); }
	;

identifiers :
	  TOK_identifier
	  { $$ = Considl_name_list($1,Nilidl_name_list()); }
	| identifiers ',' TOK_identifier
	  { $$ = Considl_name_list($3,$1); }
	;

feature_delegations :
	  feature_delegation
	  { $$ = Consdefinition_list($1,Nildefinition_list()); }
	| feature_delegation ',' feature_delegations
	  { $$ = Consdefinition_list($1,$3); }
	;

delegations :
	  delegation
	  { $$ = Consdefinition_list($1,Nildefinition_list()); }
	| delegation ',' delegations
	  { $$ = Consdefinition_list($1,$3); }
	;

operation_names :
	  operation_name
	  { $$ = Considl_name_list($1,Nilidl_name_list()); }
	| operation_names ',' operation_name
	  { $$ = Considl_name_list($3,$1); }
	;

proxy_home_members :
	  proxy_home_member
	  { $$ = Consdefinition_list($1,Nildefinition_list()); }
	| proxy_home_member proxy_home_members
	  { $$ = Consdefinition_list($1,$2); }
	;

%%


/* List of symbols:
	(0) 	<specification>
	(1) 	<import>
	(1) 	<imported_scope>
	(2) 	<definition>
	(2) 	<type_id_dcl>
	(2) 	<type_prefix_dcl>
	(1) 	<component>
	(1) 	<component_forward_dcl>
	(1) 	<component_dcl>
	(1) 	<component_header>
	(1) 	<supported_interface_spec>
	(1) 	<component_inheritance_spec>
	(1) 	<component_body>
	(1) 	<component_export>
	(1) 	<provides_dcl>
	(2) 	<interface_type>
	(1) 	<uses_decl>
	(1) 	<emits_decl>
	(1) 	<publishes_decl>
	(1) 	<consumes_decl>
	(1) 	<module>
	(1) 	<interface>
	(1) 	<interface_dcl>
	(1) 	<forward_dcl>
	(1) 	<interface_header>
	(1) 	<interface_body>
	(4) 	<export>
	(1) 	<interface_inheritance_spec>
	(4) 	<interface_name>
	(33) 	<scoped_name>
	(1) 	<value>
	(1) 	<value_forward_dcl>
	(1) 	<value_box_dcl>
	(1) 	<value_abs_dcl>
	(1) 	<value_dcl>
	(1) 	<value_header>
	(2) 	<value_inheritance_spec>
	(2) 	<value_name>
	(1) 	<value_element>
	(1) 	<state_member>
	(1) 	<init_dcl>
	(3) 	<init_param_decls>
	(2) 	<init_param_decl>
	(1) 	<init_param_attribute>
	(2) 	<const_dcl>
	(1) 	<const_type>
	(4) 	<const_exp>
	(2) 	<or_expr>
	(3) 	<xor_expr>
	(3) 	<and_expr>
	(4) 	<shift_expr>
	(5) 	<add_expr>
	(6) 	<mult_expr>
	(4) 	<unary_expr>
	(1) 	<unary_operator>
	(2) 	<primary_expr>
	(1) 	<literal>
	(1) 	<boolean_literal>
	(6) 	<positive_int_const>
	(2) 	<type_dcl>
	(1) 	<type_declarator>
	(5) 	<type_spec>
	(3) 	<simple_type_spec>
	(3) 	<base_type_spec>
	(1) 	<template_type_spec>
	(1) 	<constr_type_spec>
	(3) 	<declarators>
	(3) 	<declarator>
	(18) 	<simple_declarator>
	(1) 	<complex_declarator>
	(2) 	<floating_pt_type>
	(3) 	<integer_type>
	(1) 	<signed_int>
	(1) 	<signed_short_int>
	(1) 	<signed_long_int>
	(1) 	<signed_longlong_int>
	(1) 	<unsigned_int>
	(1) 	<unsigned_short_int>
	(1) 	<unsigned_long_int>
	(1) 	<unsigned_longlong_int>
	(3) 	<char_type>
	(2) 	<wide_char_type>
	(3) 	<boolean_type>
	(2) 	<octet_type>
	(1) 	<any_type>
	(1) 	<object_type>
	(2) 	<struct_type>
	(1) 	<member_list>
	(2) 	<member>
	(2) 	<union_type>
	(1) 	<switch_type_spec>
	(1) 	<switch_body>
	(1) 	<case>
	(1) 	<case_label>
	(1) 	<element_spec>
	(3) 	<enum_type>
	(2) 	<enumerator>
	(1) 	<sequence_type>
	(4) 	<string_type>
	(4) 	<wide_string_type>
	(1) 	<array_declarator>
	(1) 	<fixed_array_size>
	(2) 	<attr_decl>
	(1) 	<readonly_attr_spec>
	(1) 	<readonly_attr_declarator>
	(1) 	<attr_spec>
	(1) 	<attr_declarator>
	(1) 	<attr_raises_expr>
	(1) 	<get_excep_expr>
	(2) 	<set_excep_expr>
	(2) 	<exception_list>
	(1) 	<home_dcl>
	(1) 	<home_header>
	(1) 	<home_inheritance_spec>
	(1) 	<primary_key_spec>
	(1) 	<home_body>
	(1) 	<home_export>
	(2) 	<factory_dcl>
	(1) 	<finder_dcl>
	(2) 	<except_dcl>
	(1) 	<op_dcl>
	(1) 	<op_attribute>
	(2) 	<op_type_spec>
	(2) 	<parameter_dcls>
	(2) 	<param_dcl>
	(1) 	<param_attribute>
	(5) 	<raises_expr>
	(1) 	<context_expr>
	(5) 	<param_type_spec>
	(1) 	<fixed_pt_type>
	(1) 	<fixed_pt_const_type>
	(1) 	<value_base_type>
	(5) 	<abstract_storagehome_name>
	(1) 	<abstract_storagetype>
	(1) 	<abstract_storagetype_dcl>
	(1) 	<abstract_storagetype_fwd_dcl>
	(1) 	<abstract_storagetype_header>
	(1) 	<abstract_storagetype_body>
	(1) 	<abstract_storagetype_member>
	(1) 	<abstract_storagetype_inh_spec>
	(6) 	<abstract_storagetype_name>
	(2) 	<psdl_state_dcl>
	(1) 	<psdl_state_type_spec>
	(1) 	<abstract_storagetype_ref_type>
	(1) 	<abstract_storagehome>
	(1) 	<abstract_storagehome_fwd_dcl>
	(1) 	<abstract_storagehome_dcl>
	(1) 	<abstract_storagehome_header>
	(1) 	<abstract_storagehome_body>
	(1) 	<abstract_storagehome_inh_spec>
	(3) 	<local_op_dcl>
	(2) 	<key_dcl>
	(1) 	<catalog>
	(1) 	<catalog_inh_spec>
	(2) 	<catalog_name>
	(1) 	<catalog_body>
	(1) 	<catalog_member>
	(1) 	<provides_dcl_1>
	(1) 	<storagetype>
	(1) 	<storagetype_dcl>
	(1) 	<storagetype_fwd_dcl>
	(1) 	<storagetype_header>
	(1) 	<storagetype_body>
	(1) 	<storagetype_member>
	(1) 	<storagetype_ihn_spec>
	(5) 	<storagetype_name>
	(1) 	<storagetype_ref_type>
	(1) 	<storagehome_scope>
	(1) 	<store_directive>
	(1) 	<psdl_concrete_state_type>
	(1) 	<ref_rep_directive>
	(1) 	<storagehome>
	(1) 	<storagehome_header>
	(1) 	<storagehome_body>
	(1) 	<storagehome_member>
	(1) 	<storagehome_inh_spec>
	(1) 	<storagehome_name>
	(1) 	<storagetype_impl_spec>
	(1) 	<storagehome_impl_spec>
	(1) 	<primary_key_dcl>
	(1) 	<composition>
	(1) 	<category>
	(1) 	<composition_body>
	(1) 	<catalog_use_dcl>
	(1) 	<catalog_dcl>
	(1) 	<catalog_type_spec>
	(2) 	<catalog_label>
	(1) 	<home_executor_def>
	(1) 	<home_executor_body>
	(1) 	<home_impl_dcl>
	(1) 	<home_type_name>
	(1) 	<abstract_storage_home_binding>
	(3) 	<abstract_storage_home_name>
	(1) 	<abstract_storage_home_label>
	(1) 	<home_persistence_dcl>
	(1) 	<executor_def>
	(1) 	<executor_body>
	(1) 	<executor_member>
	(1) 	<segment_def>
	(1) 	<segment_member>
	(1) 	<segment_persistence_dcl>
	(1) 	<facet_dcl>
	(1) 	<feature_delegation_spec>
	(1) 	<feature_delegation_list>
	(2) 	<feature_delegation>
	(1) 	<feature_name>
	(1) 	<abstract_storage_home_delegation_spec>
	(1) 	<executor_delegation_spec>
	(3) 	<delegation_list>
	(2) 	<delegation>
	(4) 	<operation_name>
	(2) 	<abstract_spec>
	(1) 	<operation_list>
	(1) 	<proxy_home_def>
	(1) 	<proxy_home_member>
	(1) 	<home_delegation_spec>
	(1) 	<storage_member_name>
*/

/* List of tokens:
	(1) 	integer_literal
	(1) 	wide_string_literal
	(1) 	character_literal
	(1) 	wide_character_literal
	(1) 	fixed_pt_literal
	(1) 	floating_pt_literal
	(6) 	string_literal
	(53) 	TOK_identifier
*/

/* List of specials:
	(1) 	import
	(1) 	typeId
	(1) 	typePrefix
	(2) 	component
	(1) 	multiple
	(1) 	emits
	(1) 	publishes
	(1) 	consumes
	(1) 	module
	(2) 	local
	(2) 	interface
	(2) 	<scope>
	(1) 	custom
	(4) 	valuetype
	(1) 	truncatable
	(2) 	supports
	(1) 	public
	(1) 	private
	(1) 	const
	(1) 	<equal> 
	(1) 	<bar> 
	(1) 	<circum> 
	(1) 	<add> 
	(1) 	<shift right>
	(1) 	<shift left>
	(1) 	<star> 
	(1) 	<slash> 
	(1) 	<procent> 
	(2) 	<minus> 
	(2) 	<add> 
	(1) 	<tilde> 
	(1) 	TRUE
	(1) 	FALSE
	(1) 	typedef
	(1) 	native
	(1) 	float
	(2) 	double
	(2) 	short
	(3) 	unsigned
	(7) 	long
	(1) 	char
	(1) 	wchar
	(1) 	boolean
	(1) 	octet
	(1) 	any
	(2) 	Object
	(1) 	struct
	(1) 	union
	(1) 	switch
	(1) 	case
	(1) 	default
	(1) 	enum
	(2) 	sequence
	(2) 	string
	(2) 	wstring
	(1) 	<bracket left> 
	(1) 	<bracket right> 
	(2) 	attribute
	(1) 	getRaises
	(1) 	setRaises
	(1) 	primaryKey
	(2) 	factory
	(1) 	finder
	(1) 	exception
	(1) 	oneway
	(1) 	void
	(2) 	in
	(1) 	out
	(1) 	inout
	(1) 	raises
	(1) 	context
	(2) 	fixed
	(1) 	ValueBase
	(2) 	readonly
	(1) 	state
	(1) 	strong
	(4) 	storagetype
	(7) 	<less than> 
	(7) 	<greater than> 
	(1) 	scope
	(1) 	stores
	(1) 	as
	(2) 	of
	(2) 	primary
	(3) 	key
	(4) 	ref
	(1) 	composition
	(1) 	entity
	(1) 	process
	(1) 	service
	(1) 	session
	(2) 	uses
	(2) 	catalog
	(3) 	implements
	(1) 	bindsTo
	(1) 	'.'
	(2) 	manages
	(1) 	segment
	(2) 	storedOn
	(3) 	provides
	(1) 	facet
	(1) 	delegatesTo
	(1) 	storage
	(4) 	storagehome
	(2) 	executor
	(13) 	<colon> 
	(10) 	abstract
	(15) 	<paren left> 
	(27) 	<comma> 
	(15) 	<paren right> 
	(1) 	proxy
	(21) 	<brace left> 
	(21) 	<brace right> 
	(62) 	<semicolon> 
	(3) 	delegatesTo
	(4) 	home
*/
