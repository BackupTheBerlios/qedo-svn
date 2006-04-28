header {
  package ccmio.parser;
  import java.io.*;
  import java.util.*;
}
 
/**
 *  This is a complete parser for the IDL language as defined
 *  by the CORBA 3.0.2 specification.  It will allow those who
 *  need an IDL parser to get up-and-running very quickly.
 *  Though IDL's syntax is very similar to C++, it is also
 *  much simpler, due in large part to the fact that it is
 *  a declarative-only language.
 *
 *  Some things that are not included are: Symbol table construction
 *  (it is not necessary for parsing, btw) and preprocessing (for
 *  IDL compiler #pragma directives). You can use just about any
 *  C or C++ preprocessor, but there is an interesting semantic
 *  issue if you are going to generate code: In C, #include is
 *  a literal include, in IDL, #include is more like Java's import:
 *  It adds definitions to the scope of the parse, but included
 *  definitions are not generated.
 *
 *  Jim Coker, jcoker@magelang.com
 *  Gary Duzan, gduzan@bbn.com
 */
class IDLTreeParser extends TreeParser;
options {
	importVocab = IDL;
	k = 1;
	defaultErrorHandler = false;
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
	: #(DEFINITION_LIST contained = definition_AS[container] (contained_list = definition_listAS[container])? )
	{
		ret_contained_list.add(contained);
		ret_contained_list.addAll(contained_list);
	}
;

definition_AS [CCMModel.Container container] returns [CCMModel.Contained contained]
	{
		System.out.println("definition module");
		String identifier = null;
		List contained_list = new ArrayList();
		List enumerator_list;
	}
	: #(MODULE identifier = identifierAS contained_list = definition_listAS[container])
	{
		contained = IdlTreeWalkerHelper.createModuleDefinition(identifier, container);
		((CCMModel.Container)contained).getContents().addAll(contained_list);
	}
	| #(ENUM identifier=identifierAS enumerator_list=enumerator_listAS)
	{
		contained = IdlTreeWalkerHelper.createEnumerationDefinition(identifier, enumerator_list);
		
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
		enumDef = IdlTreeWalkerHelper.createEnumerationDefinition(enumName, enumerator_list);
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

identifierAS returns [String identifier]
	{ 
	} 
	: (identifierCS:IDENT )
	{
		identifier = identifierCS.getText();
	}	
	;
