/********************************************************************************
*   vim:sw=2:ts=2:et
*   *** Copyright (c) Humboldt University of Berlin, Germany,
*   *** Department of Computer Science.
*   *** All rights reserved.
*
*   File    : tree.kc
*   Author  : Harald Böhme
*   e-mail  : boehme@informatik.hu-berlin.de
*   Date    : Mon Jan 17 15:11:22 MET 2000
*   Version : CR Version 0.3
*
*******************************************************************************/
/*********************  NAMES AND IDENTIFIERS, FLAGS  *********************/

idl_name:      /* identifier */
      Name(casestring)
    | EscapedName(casestring)
    ;  

idl_identifier: /* scoped_name */
      GlobalName( idl_name_list )
    | LocalName( idl_name_list )
    | LiteralName( const_expression )
    | NilIdentifier()
    ;

flag {uniq} :
      EntityFlag()
    | ProcessFlag()
    | ServiceFlag()
    | SessionFlag()
    | InFlag()
    | InOutFlag()
    | OutFlag()
    | ReadOnlyFlag()
    | StrongFlag()
    | OneWayFlag()
    | PublicFlag()
    | PrivateFlag()
    | CustomFlag()
    | TruncatableFlag()
    | LocalFlag()
    | AbstractFlag()
    | MultipleFlag()
    | NilFlag()
    ;

idl_name_list: list idl_name
    ;

idl_identifier_list: list idl_identifier
    ;
/*********************  SPECIFICATION  ************************************/

cidl_specification:
      CIDLSpecification( import_list definition_list )
    ;

import_list: list import
    ;

import: 
      Import( idl_identifier )
    ;

definition_list: list definition
    ;


definition:
      NilDefinition()
    | PreDirect( casestring ) /* includes defines */
    | NativeType( declarator ) /* only SimpleDeclarator() */
    | StructurType( idl_name definition_list )
    | WideStringType( const_expression )
    | StringType( const_expression )
    | Void()
    | ObjectType()
    | AnyType()
    | OctetType()
    | BooleanType()
    | CharType()
    | WCharType()
    | UnsignedShortInt()
    | UnsignedLongInt()
    | UnsignedLongLongInt()
    | SignedShortInt()
    | SignedLongInt()
    | SignedLongLongInt()
    | NFloat()
    | NDouble()
    | NLongDouble()
    | FixedPtType( const_expression const_expression )
    | FixedType()
    | ValueBaseType()
    | EnumType( idl_name idl_name_list )
    | UnionType( idl_name definition idl_case_list )
    | SequenceType( definition const_expression )
    | NScopedName( idl_identifier )
    | TypeDeclarator( definition declarators )
    | Composition( idl_name flag composition_body )
    | StorageHome( storagehome_header definition_list )
    | StorageType( storagetype_header definition_list )
    | StorageTypeFwdDcl( idl_name )
    | StorageTypeRef( flag idl_identifier )
    | Catalog( idl_name idl_identifier_list definition_list )
    | AbstractStorageHome( abstract_storagehome_header definition_list )
    | AbstractStorageHomeFwdDcl( idl_name )
    | AbstractStorageType( abstract_storagetype_header definition_list )
    | AbstractStorageTypeFwdDcl( idl_name )
    | OpDcl( flag definition idl_name parameter_dcls attr_raises_expr context_expr )
    | ExceptDcl( idl_name definition_list )
    | KeyDcl( idl_name declarators )
    | PrimaryKeyDcl( idl_identifier )
    | PrimaryKeyRef()
    | LocalOpDcl( definition idl_name parameter_dcls attr_raises_expr )
    | FactoryDcl( idl_name parameter_dcls attr_raises_expr )
    | FactoryDcl1( idl_name declarators )
    | FinderDcl( idl_name parameter_dcls attr_raises_expr )
    | PsdlStateDcl( flag definition declarators )
    | StoreDirective( declarator psdl_concrete_state_type idl_identifier )
    | RefRepDirective( declarators )
    | ProvidesDcl1( idl_identifier declarator )
    | HomeDcl( home_header definition_list )
    | Attribute( flag definition attr_declarator )
    | ConstDcl( definition idl_name const_expression )
    | StateMember( flag definition declarators )
    | EventType( eventtype_header definition_list )
    | AbstractEventType( eventtype_header definition_list )
    | EventTypeFwdDcl( idl_name )
    | AbstractEventTypeFwdDcl( idl_name )
    | ValueType( value_header definition_list )
    | AbstractValueType( value_header definition_list )
    | ValueBox( idl_name definition )
    | ValueTypeFwdDcl( idl_name )
    | AbstractValueTypeFwdDcl( idl_name )
    | Interface( interface_header definition_list )
    | InterfaceFwdDcl( flag idl_name )
    | Module( idl_name definition_list )
    | ProvidesDcl( definition idl_name )
    | UsesDcl( flag definition idl_name )
    | EmitsDcl( idl_identifier idl_name )
    | SinkDcl( idl_identifier idl_name )
    | SourceDcl( idl_identifier idl_name )
    | SiSoDcl( idl_identifier idl_name )
    | StreamTypeDcl( idl_name )
    | PublishesDcl( idl_identifier idl_name )
    | ConsumesDcl( idl_identifier idl_name )
    | NComponent( component_header definition_list )
    | ComponentFwdDcl( idl_name )
    | TypeIdDcl( idl_identifier const_expression )
    | TypePrefixDcl( idl_identifier const_expression )
    | ElementSpec( definition declarator )
    | Member( definition  declarators )
    | HomeExecutorDef( idl_name home_executor_body )
    | ExecutorDef( idl_name definition_list /* executor_member_list */ )
	  | SegmentPersistenceDcl( abstract_storage_home_name )
    | FacetDcl( idl_name_list )
    | FeatureDelegation( idl_name idl_name )
    | SegmentDef( idl_name definition_list /* segment_member_list */ )
    | FeatureDelegationSpec( definition_list /* feature_delegation_list */ )
    | Operation( idl_name )
	  | OperationPair( idl_name idl_name)
    | HomeDelegationSpec( definition_list /* delegation_list */ )
    | AbstractSpec( idl_name_list )
    | NilProxyHomeMember()
	  | CatalogDcl( idl_name idl_identifier )
    ;


declarators: list declarator
    ;

declarator:
      ArrayDeclarator( idl_name fixed_array_sizes )
    | SimpleDeclarator( idl_name )
    ;

fixed_array_sizes: list fixed_array_size
    ;

fixed_array_size:
      FixedArraySize( const_expression )
    ;

const_expression:
	    Nilconst_expression()
    | NamedRef( idl_identifier )
    | IntegerLiteral( casestring )
    | StringLiteral( casestring )
    | WideStringLiteral( casestring )
    | CharacterLiteral( casestring )
    | FixedPtLiteral( casestring )
    | FloatingPtLiteral( casestring )
    | LIT_TRUE()
    | LIT_FALSE()
    | UMinus( const_expression )
    | UPlus( const_expression )
    | UNeg( const_expression )
    | Mult( const_expression const_expression )
    | Div( const_expression const_expression )
    | Modulo( const_expression const_expression )
    | Add( const_expression const_expression )
    | Minus( const_expression const_expression )
    | LShift( const_expression const_expression )
    | RShift( const_expression const_expression )
    | Xor( const_expression const_expression )
    | And( const_expression const_expression )
    | Or( const_expression const_expression )
    ;

const_expression_list: list const_expression
    ;

composition_body:
      CompositionBody( definition_list /* catalog_use_dcl_list */ definition proxy_home_def )
    | NilCompositionBody()
    ;

proxy_home_def:
      NilProxyHomeDef()
    | ProxyHomeDef( idl_name definition_list /* proxy_home_member_list */ )
    ;

home_executor_body:
	     HomeExecutorBody( home_impl_dcl abstract_storage_home_binding 
		     home_persistence_dcl definition   /* executor_def */
		     abstract_storage_home_delegation_spec 
		     executor_delegation_spec definition /* proxy_home_member */ )
    |  NilHomeExecutorBody()
    ;

home_impl_dcl:
	   HomeImplDcl( idl_identifier )
    ;

abstract_storage_home_binding:
      AbstractStorageHomeBinding( abstract_storage_home_name )
    | NilAbstractStorageHomeBinding()
    ;

abstract_storage_home_name:
      AbstractStorageHomeName( idl_name idl_name )
    ;

home_persistence_dcl:
      HomePersistenceDcl( abstract_storage_home_name )
    | NilHomePersistenceDcl()
	 ;

abstract_storage_home_delegation_spec:
      NilAbstractStorageHomeDelegationSpec()
    | AbstractStorageHomeDelegationSpec( definition_list /* delegation_list */ )
	 ;

executor_delegation_spec:
      NilExecutorDelegationSpec()
    | ExecutorDelegationSpec( definition_list /* delegation_list */ )
	 ;

storagehome_header:
      StorageHomeHeader( idl_name idl_identifier idl_identifier idl_identifier_list definition )
    ;

storagetype_header:
      StorageTypeHeader( idl_name idl_identifier idl_identifier_list )
    ;

param_dcl:
      ParamDcl( flag definition declarator )
    ;

parameter_dcls: list param_dcl
    ;

psdl_concrete_state_type:
      PsdlConcreteStateTypeName( idl_identifier )
    | PsdlConcreteStateTypeRef( idl_identifier )
	 ;

abstract_storagehome_header:
	   AbstractStorageHomeHeader( idl_name idl_identifier idl_identifier_list )
	 ;

abstract_storagetype_header:
      AbstractStorageTypeHeader( idl_name idl_identifier_list )
    ;

context_expr:
	   NilContextExpr()
    | ContextExpr( const_expression_list )
    ;

home_header:
      HomeHeader( idl_name idl_identifier idl_identifier_list idl_identifier idl_identifier )
    ;

attr_raises_expr:
      NilRaisesExpr()
    | RaisesExpr( idl_identifier_list )
    | GetExcepExpr( idl_identifier_list )
    | SetExcepExpr( idl_identifier_list )
    | GetSetExcepExpr( idl_identifier_list idl_identifier_list )
    ;

attr_declarator:
      AttrDeclarator( declarator attr_raises_expr )
    | AttrDeclaratorList( declarators )
	 ;

idl_case: 
      Case(case_label_list definition )
    ;

idl_case_list: list idl_case
    ;

case_label_list: list case_label
    ;

case_label:
      Default()
    | CaseLabel( const_expression )
	 ;

eventtype_header:
      EventTypeHeader( flag idl_name value_inheritance_spec )
    ;

value_header:
      ValueHeader( flag idl_name value_inheritance_spec )
    ;

value_inheritance_spec:
		NilValueInheritanceSpec()
    | ValueInheritanceSpec( flag idl_identifier_list idl_identifier_list )
    ;

interface_header:
	   InterfaceHeader( flag idl_name idl_identifier_list )
    ;

component_header:
	   ComponentHeader( idl_name idl_identifier idl_identifier_list )
    ;


