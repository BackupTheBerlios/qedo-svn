/*******************************************************************************
*   vim:sw=2:ts=2:et
*   File    : print_idl.k
*   Author  : Harald Böhme
*   e-mail  : boehme@informatik.hu-berlin.de
*   Remark  :
*   $Date: 2002/10/11 07:36:26 $
*   $Revision: 1.1 $
*
*******************************************************************************/

%uview print_idl,
       print_used_idl,
		   print_enum;

%{
static char id[] UNUSED = "$Id: print_idl.k,v 1.1 2002/10/11 07:36:26 neubauer Exp $";
%}

GlobalName(ident_v)
->[ print_idl : "::" ident_v ];

Considl_name_list(name_v,Nilidl_name_list())
->[ print_idl : name_v ];

Considl_name_list(name_v,tail)
->[ print_idl : tail "::" name_v ];

Considl_name_list(name_v,Nilidl_name_list())
->[ print_enum : name_v ];

Considl_name_list(name_v,tail)
->[ print_enum : tail ",\n" name_v ];

LocalFlag()
->[ print_idl: "local " ];

PublicFlag()
->[ print_idl: "public " ];

PrivateFlag()
->[ print_idl: "private " ];

CustomFlag()
->[ print_idl: "custom " ];

InFlag()
->[ print_idl: "in " ];

InOutFlag()
->[ print_idl: "inout " ];

OutFlag()
->[ print_idl: "out " ];

OneWayFlag()
->[ print_idl: "oneway " ];

ReadOnlyFlag()
->[ print_idl: "readonly " ];

AbstractFlag()
->[ print_idl: "abstract " ];

Void()
->[ print_idl: "void" ];

ObjectType()
->[ print_idl: "object" ];

AnyType()
->[ print_idl: "any" ];

OctetType()
->[ print_idl: "octet" ];

BooleanType()
->[ print_idl: "boolean" ];

CharType()
->[ print_idl: "char" ];

WCharType()
->[ print_idl: "wchar" ];

UnsignedShortInt()
->[ print_idl: "unsigned short" ];

UnsignedLongInt()
->[ print_idl: "unsigned long" ];

UnsignedLongLongInt()
->[ print_idl: "unsigned long long" ];

SignedShortInt()
->[ print_idl: "short" ];

SignedLongInt()
->[ print_idl: "long" ];

SignedLongLongInt()
->[ print_idl: "long long" ];

NFloat()
->[ print_idl: "float" ];

NDouble()
->[ print_idl: "double" ];

NLongDouble()
->[ print_idl: "long double" ];

StringType(expr_v)
->[ print_idl: "string<" expr_v ">" ];

StringType( Nilconst_expression() )
->[ print_idl: "string" ];

WideStringType(expr_v)
->[ print_idl: "wstring<" expr_v ">" ];

WideStringType( Nilconst_expression() )
->[ print_idl: "wstring" ];

CharacterLiteral(lit_v)
->[ print_idl: "\'" lit_v "\'" ];

StringLiteral(lit_v)
->[ print_idl: "\"" lit_v "\"" ];

EnumType(name_v,list_v)
->[ print_idl: "enum " name_v " {\n" {INDENT} list_v : print_enum {UNINDENT} "};\n\n" ];

StructurType(name_v,list_v)
->[ print_idl: "struct " name_v " {\n" {INDENT} list_v {UNINDENT} "};\n\n" ];

SequenceType(type_v,expr_v)
->[ print_idl: "sequence<" type_v "," expr_v ">" ];

SequenceType(type_v,Nilconst_expression())
->[ print_idl: "sequence<" type_v ">" ];

TypeDeclarator(type_v,name_v)
->[ print_idl: "typedef " type_v " " name_v ";\n" ];

AbstractValueTypeFwdDcl(name_v)
->[ print_idl: "abstract valuetype " name_v ";\n" ];

ValueTypeFwdDcl(name_v)
->[ print_idl: "valuetype " name_v ";\n" ];

ValueBox(name_v,type_v)
->[ print_idl: "valuetype " name_v " " type_v ";\n" ];

AbstractValueType(header_v,body_v)
->[ print_idl: "abstract " header_v " {\n" 
    {INDENT}
    body_v
    {UNINDENT}
    "};\n\n"
  ];

EventType(header_v,body_v)
->[ print_idl: header_v " {\n" 
    {INDENT}
    body_v
    {UNINDENT}
    "};\n\n"
  ]
  [ print_used_idl:
  ];

EventTypeHeader(custom_v, name_v, inh_v)
->[ print_idl: custom_v "eventtype " name_v inh_v ];

ValueType(header_v,body_v)
->[ print_idl: header_v " {\n" 
    {INDENT}
    body_v
    {UNINDENT}
    "};\n\n"
  ];

ValueHeader(custom_v, name_v, inh_v)
->[ print_idl: custom_v "valuetype " name_v inh_v ];

ValueInheritanceSpec(truncatable_v,Nilidl_identifier_list(),Nilidl_identifier_list())
->[ print_idl: { Error("This can not be!\n", $0); } ];

ValueInheritanceSpec(truncatable_v,Nilidl_identifier_list(),id_list_v)
->[ print_idl: truncatable_v "supports " id_list_v ];

ValueInheritanceSpec(truncatable_v,id_list_v,Nilidl_identifier_list())
->[ print_idl: truncatable_v ": " id_list_v ];

ValueInheritanceSpec(truncatable_v,id_list_1,id_list_2)
->[ print_idl: truncatable_v ": " id_list_1 " supports " id_list_2 ];

StateMember(private_v,type_v,decls_v)
->[ print_idl: private_v type_v " " decls_v ";\n" ];

Module(name_v,list_v)
->[ print_idl: 
    { begin_empty_definition(); }
    "module " name_v " {\n" 
    { end_empty_definition(); }
    {INDENT} 
    list_v 
    {UNINDENT} 
    { if(!is_empty_definition()) ${ }
      "};\n\n" 
    { $} }
    { finish_empty_definition(); }
  ];

InterfaceFwdDcl(abstract_v,name_v)
->[ print_idl: abstract_v "interface " name_v ";\n" ];

Interface( header_v, list_v )
->[ print_idl : 
    header_v
    "{\n"
    { INDENT }
    list_v
    { UNINDENT }
    "};\n\n"
  ];

InterfaceHeader( flag_v,
                idl_name_v,
                idl_identifier_list_v)
->[ print_idl:
    flag_v "interface " idl_name_v
    {
      if(idl_identifier_list_v->length() > 0) {
        Print(" : ");
      }
    }
    idl_identifier_list_v " "
  ];

FactoryDcl(name_v,params_v,raise_v)
->[ print_idl: "factory " name_v "(" params_v ")" raise_v ";\n" ];

OpDcl( one_way_v,
       definition_v,
       idl_name_v,
       parameter_dcls_v,
       attr_raises_expr_v,
       context_expr_v)
->[ print_idl :
    one_way_v definition_v " " idl_name_v "(" parameter_dcls_v ")" 
    attr_raises_expr_v context_expr_v ";\n"
  ];

Attribute( readonly_v,
           type_v,
           decl_v)
->[ print_idl :
    readonly_v "attribute " type_v " " decl_v ";\n"
  ];

AttrDeclarator(simple_declarator_v,raises_expr_v)
->[ print_idl :
    simple_declarator_v " " raises_expr_v
  ];

ContextExpr(expr_list_v)
->[ print_idl :
    " context (" expr_list_v ")"
  ];

/* XXX have to be changed for set/get raises HB */
RaisesExpr( list_v )
->[ print_idl :
    " raises (" list_v ")"
  ];

ExceptDcl( name_v, list_v )
->[ print_idl :
    "exception " name_v " {\n" {INDENT} list_v {UNINDENT} "};\n"
  ];

Member(type_v, decls_v)
->[ print_idl :
    type_v " " decls_v ";\n"
  ];

Considl_identifier_list(ident_v,Nilidl_identifier_list())
->[ print_idl: ident_v ];
  
Considl_identifier_list(ident_v,tail)
->[ print_idl: ident_v ", " tail ];
  
Consparameter_dcls(param_v,Nilparameter_dcls())
->[ print_idl: param_v ];
  
Consparameter_dcls(param_v,tail)
->[ print_idl: tail ", " param_v ];
  
Consdeclarators(decl_v,Nildeclarators())
->[ print_idl: decl_v ];

Consdeclarators(decl_v,tail)
->[ print_idl: tail ", " decl_v ];

ParamDcl( inout_v,
          definition_v,
          decl_v)
->[ print_idl:
    inout_v  definition_v " " decl_v
  ];

TypeIdDcl,
TypePrefixDcl
->[ print_used_idl :
    { $0->unparse(kc_printer,print_idl); }
  ];

Module(name_v,list_v)
->[ print_used_idl: 
    { begin_empty_definition(); }
    "module " name_v " {\n" 
    { end_empty_definition(); }
    {INDENT} 
    list_v 
    {UNINDENT} 
    { if(!is_empty_definition()) ${ }
      "};\n\n" 
    { $} }
    { finish_empty_definition(); }
  ];


HomeDcl,
NComponent,
ComponentFwdDcl,
Composition,
StorageHome,
StorageType,
StorageTypeFwdDcl,
StorageTypeRef,
Catalog,
AbstractStorageHome,
AbstractStorageHomeFwdDcl,
AbstractStorageType,
AbstractStorageTypeFwdDcl
->[ print_used_idl 
    print_idl : 
  ];




