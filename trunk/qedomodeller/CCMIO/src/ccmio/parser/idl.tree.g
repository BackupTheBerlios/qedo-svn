header {
  package ccmio.parser;
  import java.io.*;
  import java.util.*;
  import CCMModel.*;
}


class IDLTreeParser extends TreeParser;
options {
	importVocab = IDL;
	k = 1;
	defaultErrorHandler = false;
}

{
	IdlTreeWalkerHelper helper;
	
	public IDLTreeParser(IdlTreeWalkerHelper helper)
	{
		this();
		this.helper = helper;
	};
	
	
}

specification [CCMModel.ModuleDef root_module] 
	{
		System.out.println("specification");
		String moduleName;
		List contained_list = new ArrayList();
	}
	: #(SPECIFICATION contained_list = definition_listAS[root_module]) 
	{
		root_module.getContents().addAll(contained_list);
	}
;

definition_listAS [CCMModel.Container container] returns [List ret_contained_list]
	{
		System.out.println("definitionlist");
		CCMModel.Contained contained = null;
		List contained_list = new ArrayList();
		ret_contained_list = new ArrayList();
	}
	: #(DEFINITION_LIST contained = definition_AS[container] (contained_list = definition_list_itAS[container])? )
	{
		ret_contained_list.add(contained);
		ret_contained_list.addAll(contained_list);
	}
;

definition_list_itAS [CCMModel.Container container] returns [List ret_contained_list]
	{
		System.out.println("definitionlist_it");
		CCMModel.Contained contained = null;
		List contained_list = new ArrayList();
		ret_contained_list = new ArrayList();
	}
	: (contained = definition_AS[container] (contained_list = definition_list_itAS[container])? )
	{
		ret_contained_list.add(contained);
		ret_contained_list.addAll(contained_list);
	}
;

definition_AS [CCMModel.Container container] returns [CCMModel.Contained contained]
	{
		System.out.println("definition AS");
		String identifier = null;
		List contained_list = new ArrayList();
		List enumerator_list;
		contained = null;
		
		IDLType type = null;
		String expr;
		List fields= null;
		
		List union_fields = new ArrayList();
		
	}
	: #(MODULE identifier = identifierAS contained = module_createAS[identifier, container])
	{
		container.getContents().add(contained);
	}
	| #(ENUM identifier=identifierAS enumerator_list=enumerator_listAS)
	{
		System.out.println("found Enum");
		contained = helper.createEnumerationDefinition(identifier, enumerator_list);
		
	}
	| #(INTERFACE identifier = identifierAS contained = interface_createAS[identifier, container])
	{
		container.getContents().add(contained);	
	}
	| #(TYPEDEF type = typeAS identifier = identifierAS)
	{
		System.out.println("found typedef");
		contained = helper.create_alias(type,identifier,container);

	}
	| #(CONST_DEF type = typeAS identifier = identifierAS expr = const_exprAS)
	{
		System.out.println("Found Const");
		contained = helper.create_const(type, identifier, expr, container);
	}
	| #(STRUCT_TYPE identifier = identifierAS fields = struct_member_listAS)
	{
		contained = helper.create_struct(identifier, fields, container);
	}
	| #(UNION_TYPE identifier = identifierAS type = typeAS union_fields = case_stmt_listAS)
	{
		contained = helper.create_union(identifier, type, union_fields, container);
	}
	| #(EXCEPTION_TYPE identifier = identifierAS fields = struct_member_listAS)
	{
		contained = helper.create_exception(identifier, fields, container);
	}
;


interface_createAS[String identifier, Container container] returns [InterfaceDef interf]
	{
		System.out.println("create interface");
		List contained_list = new ArrayList();
		interf = helper.createInterfaceDefinition(identifier, container);
	}
	: (inheritanceAS[interf])? (contained_list = export_listAS [interf])?
	{
			if (contained_list != null )
			{
				System.out.println("found interface");
				((CCMModel.Container)interf).getContents().addAll(contained_list);
			}
	}
; 

inheritanceAS[Container container] 
	{
		//List base_interfs = null;
		String base = null;
	}
	: #(INTERFACE_INHERITANCE base = const_exprAS)
	{
		// find base types
	}
;

module_createAS[String identifier, Container container] returns [ModuleDef mod]
{
	List contained_list = null;
	mod = helper.createModuleDefinition(identifier, container);
}
: contained_list = definition_listAS [mod]
{
		if (identifier != "CORBA")
		{
			System.out.println("found module");
			((CCMModel.Container)mod).getContents().addAll(contained_list);
		}
}
;

export_listAS [Container container] returns [List ret_contained_list]
	{
		System.out.println("exportlist");
		CCMModel.Contained contained = null;
		List contained_list = new ArrayList();
		ret_contained_list = new ArrayList();
	}
	: #(EXPORT_LIST (contained = export_AS[container] (contained_list = export_list_itAS[container])?)? )
	{
		if (contained != null)
		{
			ret_contained_list.add(contained);
		}
		ret_contained_list.addAll(contained_list);
	}
;

export_list_itAS [Container container] returns [List ret_contained_list]
	{
		System.out.println("exportlist_it");
		CCMModel.Contained contained = null;
		List contained_list = new ArrayList();
		ret_contained_list = new ArrayList();
	}
	: (contained = export_AS[container] (contained_list = export_list_itAS[container])? )
	{
		ret_contained_list.add(contained);
		ret_contained_list.addAll(contained_list);
	}
;

export_AS[Container container] returns [OperationDef operation]
	{
		System.out.println("found an element in export list");
		String identifier = null;
		IDLType type= null;
		operation = null;
		List params = new ArrayList();
		boolean oneway = false;
		List excep_list = new ArrayList();
	}
	: #(TYPEDEF type = typeAS identifier = identifierAS)
	{

	}
	| #(OPERATION_DEF (oneway = op_attribute)? type = typeAS identifier = identifierAS params = param_list_entryAS (excep_list = raisesAS)?)
	{
		System.out.println("found an operation");
		operation = helper.createOperationDefinition(oneway, identifier, type, params, container);
	}
	
;

raisesAS returns [List excep_list]
	{
		IDLType type;
		excep_list = new ArrayList();
	}
	: #(RAISES type = typeAS)
	{
		
	}
;

op_attribute returns [boolean oneway]
	{
		System.out.println("found oneway");
	}
	: "oneway"
	{
		oneway = true;
	}

;

param_list_entryAS returns [List params]
	: PARAMETER_LIST params = param_listAS
;

param_listAS returns [List params]
	{
		params = new ArrayList();
		List add_params = new ArrayList();
		ParameterDef act_param = null;
	}
	: ((act_param = paramAS (add_params = param_listAS)?)?) 
	{
		if (act_param != null)
		{		params.add(act_param);
		}
		params.addAll(add_params);
	}
;


paramAS returns [ParameterDef param]
	{
		String identifier;
		IDLType type;
		ParameterMode mode;
	}
	: #(PARAMETER_DEF mode = para_modeAS type = typeAS identifier = identifierAS) 
	{
		param = helper.createParameterDef(mode, type, identifier);
		
	}
;

para_modeAS returns [ParameterMode mode]
	{
	}
	: "in"
	{
		mode = ParameterMode.PARAM_IN_LITERAL;
	}
	| "out"
	{
		mode = ParameterMode.PARAM_OUT_LITERAL;
	}
	| "inout"
	{
		mode = ParameterMode.PARAM_INOUT_LITERAL;
	}
;
	
case_stmt_listAS returns [List union_fields]
	{
	}
	: #(CASE_STMT_LIST union_fields = case_stmt_itAS)
	{
	}
;
	 
case_stmt_itAS returns [List union_fields]
	{
		List current_fields = new ArrayList();
		UnionField field = null;
		union_fields = new ArrayList();
		System.out.println("before CAS_STMT");
	}
	: (#(CASE_STMT field = case_stmt_AS) (current_fields = case_stmt_itAS)?)
	{
		System.out.println("found case_stmt");
		union_fields.add(field);
		union_fields.addAll(current_fields);
	}
;
		
case_stmt_AS returns [UnionField union_field]
	{
		String expr;
		IDLType type;
		String name;
		System.out.println("before case");
	}
	: #("case" expr = const_exprAS type = typeAS name = identifierAS)
	{
		System.out.println("found case");
		union_field = helper.create_union_field(expr, type, name);
	}
	| #("default" type = typeAS name = identifierAS)
	{
		System.out.println("Found default");
		union_field = helper.create_union_field("default", type, name);
	}
;

struct_member_listAS returns [List fields]
	{
		List current_fields = null;
		Field current_field = null;
		fields = null;
		
	}
	: (current_field = struct_memberAS current_fields = struct_member_listAS)
	{
		fields = current_fields;
 		fields.add(current_field);
	}
	| 
	{
		fields = new ArrayList();
	}
	;

struct_memberAS returns [Field field]
	{
		IDLType type;
		String name="test";
	}
	: #(STRUCT_MEMBER type = typeAS name = identifierAS)
	{
		field = helper.create_field(type, name);
	}
;

enum_typeAS returns [CCMModel.EnumDef enumDef]
	{
		System.out.println("enum_type");
		String enumName;
		List enumerator_list;
	} 
	: #(ENUM enumName=identifierAS enumerator_list=enumerator_listAS)
	{
		enumDef = helper.createEnumerationDefinition(enumName, enumerator_list);
	}	
	;
	
enumerator_listAS returns [List enumerator_list]
	{ String name; 
	  enumerator_list = new ArrayList();
	}
	: #(ENUMERATOR_LIST name=identifierAS (enumerator_list=enumerator_listAS)? )
	{
		enumerator_list.add(name);
	}
	;

typeAS returns [CCMModel.IDLType type]
	{
		String sc_name;
		IDLType temp_type;
	}
	: #(BASE_TYPE_SPEC type = concrete_typeAS)
	{
		System.out.println("found simple type spec");
	}
	| #(SCOPED_NAME s:IDENT)
	{
		System.out.println("found scoped name");
		sc_name = s.getText();
		type = helper.find_idl_type_by_sc_name(sc_name);
	}
	| #(SEQUENCE temp_type = typeAS (i:INT)?)
	{
		System.out.println("found sequence");
		type = helper.createSequence(temp_type);
	}
	| type = concrete_typeAS
;

concrete_typeAS returns [CCMModel.IDLType type]
	: FLOAT_TYPE
	{
		System.out.println("found float");
		type = helper.find_primitive_type(PrimitiveKind.PK_FLOAT_LITERAL);
	}
	| DOUBLE_TYPE
	{
		System.out.println("found double");
		type = helper.find_primitive_type(PrimitiveKind.PK_DOUBLE_LITERAL);
	}
	| LONG_DOUBLE_TYPE
	{
		System.out.println("found long double");
		type = helper.find_primitive_type(PrimitiveKind.PK_LONGDOUBLE_LITERAL);
	}
	| UNSIGNED_SHORT_INT
	{
		System.out.println("found unsigned short");
		type = helper.find_primitive_type(PrimitiveKind.PK_USHORT_LITERAL);
	}		
	| UNSIGNED_LONG_INT
	{
		System.out.println("found unsigned long");
		type = helper.find_primitive_type(PrimitiveKind.PK_ULONG_LITERAL);
	}		
	| UNSIGNED_LONGLONG_INT
	{
		System.out.println("found unsigned long long");
		type = helper.find_primitive_type(PrimitiveKind.PK_ULONGLONG_LITERAL);
	}		
	| SIGNED_SHORT_INT
	{
		System.out.println("found short");
		type = helper.find_primitive_type(PrimitiveKind.PK_SHORT_LITERAL);
	}		
	| SIGNED_LONG_INT
	{
		System.out.println("found long");
		type = helper.find_primitive_type(PrimitiveKind.PK_LONG_LITERAL);
	}		
	| SIGNED_LONGLONG_INT
	{
		System.out.println("found long long");
		type = helper.find_primitive_type(PrimitiveKind.PK_LONGLONG_LITERAL);
	}		
	| STRING_TYPE 
	{
		System.out.println("found string");
		type = helper.find_primitive_type(PrimitiveKind.PK_STRING_LITERAL); 
	}
	| WSTRING_TYPE 
	{ 
		System.out.println("found wide string");
		type = helper.find_primitive_type(PrimitiveKind.PK_WSTRING_LITERAL); 
	}
	| "octet"
	{
		System.out.println("found octet");
		type = helper.find_primitive_type(PrimitiveKind.PK_OCTET_LITERAL); 
	}		
	| "char"
	{
		System.out.println("found char");
		type = helper.find_primitive_type(PrimitiveKind.PK_CHAR_LITERAL); 
	}		
	| "wchar"
	{
		System.out.println("found wchar");
		type = helper.find_primitive_type(PrimitiveKind.PK_WCHAR_LITERAL); 
	}		
	| "boolean"
	{
		System.out.println("found boolean");
		type = helper.find_primitive_type(PrimitiveKind.PK_BOOLEAN_LITERAL); 
	}		
	| "Object"
	{
		System.out.println("found Object");
		type = helper.find_primitive_type(PrimitiveKind.PK_OBJREF_LITERAL); 
	}		
	| "void"
	{
		System.out.println("found string");
		type = helper.find_primitive_type(PrimitiveKind.PK_VOID_LITERAL); 
	}		
	;
	
const_exprAS returns [String value]
	{
		System.out.println("before const expr");
		String temp_value1;
		String temp_value2;
	}
	: s:STRING_LITERAL
	{
		System.out.println("found const expr: ");
		value = s.getText();
		System.out.println(value);
	}
	| ws:WIDE_STRING_LITERAL
	{
		System.out.println("found const expr: ");
		value = ws.getText();
		System.out.println(value);
	}
	| c:CHAR_LITERAL
	{
		System.out.println("found const expr: ");
		value = c.getText();
		System.out.println(value);
	}
	| wc:WIDE_CHAR_LITERAL
	{
		System.out.println("found const expr: ");
		value = wc.getText();
		System.out.println(value);
	}
	| h:HEX
	{
		System.out.println("found const expr hex: ");
		value = h.getText();
		System.out.println(value);
	}
	| i:INT
	{
		System.out.println("found const expr: ");
		value = i.getText();
		System.out.println(value);
	}
	| f:FLOAT
	{
		System.out.println("found float expr:");
		value = f.getText();
		System.out.println(value);
	}
	| #(SCOPED_NAME sc:IDENT)
	{
		System.out.println("found scoped name expr:");
		value = sc.getText();
		System.out.println(value);
	}
	| #(MINUS temp_value1 = const_exprAS)
	{
		System.out.println("found - :");
		value = "-" + temp_value1;
	}
	| #(PLUS temp_value1 = const_exprAS temp_value2 = const_exprAS)
	{
		System.out.println("found - :");
		value = temp_value1 + " + " + temp_value2;
	}
	| "TRUE"
	{
		System.out.println("found TRUE");
		value = "TRUE";
	}
	| "FALSE"
	{
		System.out.println("found FALSE");
		value = "FALSE";
	}
	
	
	;
	
	
identifierAS returns [String identifier]
	{ 
	} 
	: (identifierCS:IDENT )
	{
		identifier = identifierCS.getText();
	}	
	;
