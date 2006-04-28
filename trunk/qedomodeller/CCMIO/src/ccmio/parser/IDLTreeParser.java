// $ANTLR : "idl.tree.g" -> "IDLTreeParser.java"$

  package ccmio.parser;
  import java.io.*;
  import java.util.*;

import antlr.TreeParser;
import antlr.Token;
import antlr.collections.AST;
import antlr.RecognitionException;
import antlr.ANTLRException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.collections.impl.BitSet;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;


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
public class IDLTreeParser extends antlr.TreeParser       implements IDLTreeParserTokenTypes
 {
public IDLTreeParser() {
	tokenNames = _tokenNames;
}

	public final void specification(AST _t,
		CCMModel.ModuleDef root_module
	) throws RecognitionException {
		
		AST specification_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				System.out.println("specification");
				String moduleName;
				List contained_list = new ArrayList();
			
		
		AST __t12071 = _t;
		AST tmp1_AST_in = (AST)_t;
		match(_t,SPECIFICATION);
		_t = _t.getFirstChild();
		contained_list=definition_listAS(_t,root_module);
		_t = _retTree;
		_t = __t12071;
		_t = _t.getNextSibling();
		
				root_module.getContents().addAll(contained_list);
			
		_retTree = _t;
	}
	
	public final List  definition_listAS(AST _t,
		CCMModel.Container container
	) throws RecognitionException {
		List ret_contained_list;
		
		AST definition_listAS_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				System.out.println("definitionlist");
				CCMModel.Contained contained = null;
				List contained_list = new ArrayList();
				ret_contained_list = new ArrayList();
			
		
		AST __t12073 = _t;
		AST tmp2_AST_in = (AST)_t;
		match(_t,DEFINITION_LIST);
		_t = _t.getFirstChild();
		contained=definition_AS(_t,container);
		_t = _retTree;
		{
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case DEFINITION_LIST:
		{
			contained_list=definition_listAS(_t,container);
			_t = _retTree;
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		}
		_t = __t12073;
		_t = _t.getNextSibling();
		
				ret_contained_list.add(contained);
				ret_contained_list.addAll(contained_list);
			
		_retTree = _t;
		return ret_contained_list;
	}
	
	public final CCMModel.Contained  definition_AS(AST _t,
		CCMModel.Container container
	) throws RecognitionException {
		CCMModel.Contained contained;
		
		AST definition_AS_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				System.out.println("definition module");
				String identifier = null;
				List contained_list = new ArrayList();
				List enumerator_list;
			
		
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case MODULE:
		{
			AST __t12076 = _t;
			AST tmp3_AST_in = (AST)_t;
			match(_t,MODULE);
			_t = _t.getFirstChild();
			identifier=identifierAS(_t);
			_t = _retTree;
			contained_list=definition_listAS(_t,container);
			_t = _retTree;
			_t = __t12076;
			_t = _t.getNextSibling();
			
					contained = IdlTreeWalkerHelper.createModuleDefinition(identifier, container);
					((CCMModel.Container)contained).getContents().addAll(contained_list);
				
			break;
		}
		case ENUM:
		{
			AST __t12077 = _t;
			AST tmp4_AST_in = (AST)_t;
			match(_t,ENUM);
			_t = _t.getFirstChild();
			identifier=identifierAS(_t);
			_t = _retTree;
			enumerator_list=enumerator_listAS(_t);
			_t = _retTree;
			_t = __t12077;
			_t = _t.getNextSibling();
			
					contained = IdlTreeWalkerHelper.createEnumerationDefinition(identifier, enumerator_list);
					
				
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		_retTree = _t;
		return contained;
	}
	
	public final String  identifierAS(AST _t) throws RecognitionException {
		String identifier;
		
		AST identifierAS_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST identifierCS = null;
		
			
		
		{
		identifierCS = (AST)_t;
		match(_t,IDENT);
		_t = _t.getNextSibling();
		}
		
				identifier = identifierCS.getText();
			
		_retTree = _t;
		return identifier;
	}
	
	public final List  enumerator_listAS(AST _t) throws RecognitionException {
		List enumerator_list;
		
		AST enumerator_listAS_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		String name; 
			  enumerator_list = new ArrayList();
			
		
		AST __t12081 = _t;
		AST tmp5_AST_in = (AST)_t;
		match(_t,ENUMERATOR_LIST);
		_t = _t.getFirstChild();
		name=identifierAS(_t);
		_t = _retTree;
		{
		if (_t==null) _t=ASTNULL;
		switch ( _t.getType()) {
		case ENUMERATOR_LIST:
		{
			enumerator_list=enumerator_listAS(_t);
			_t = _retTree;
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			throw new NoViableAltException(_t);
		}
		}
		}
		_t = __t12081;
		_t = _t.getNextSibling();
		
				enumerator_list.add(name);
			
		_retTree = _t;
		return enumerator_list;
	}
	
	public final CCMModel.EnumDef  enum_typeAS(AST _t) throws RecognitionException {
		CCMModel.EnumDef enumDef;
		
		AST enum_typeAS_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
				System.out.println("enum_type");
				String enumName;
				List enumerator_list;
			
		
		AST __t12079 = _t;
		AST tmp6_AST_in = (AST)_t;
		match(_t,ENUM);
		_t = _t.getFirstChild();
		enumName=identifierAS(_t);
		_t = _retTree;
		enumerator_list=enumerator_listAS(_t);
		_t = _retTree;
		_t = __t12079;
		_t = _t.getNextSibling();
		
				enumDef = IdlTreeWalkerHelper.createEnumerationDefinition(enumName, enumerator_list);
			
		_retTree = _t;
		return enumDef;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"SPECIFICATION",
		"MODULE",
		"DEFINITION",
		"DEFINITION_LIST",
		"ENUM",
		"ENUMERATOR_LIST",
		";",
		"\"abstract\"",
		"\"local\"",
		"\"interface\"",
		"\"custom\"",
		"\"valuetype\"",
		"\"eventtype\"",
		"\"module\"",
		"{",
		"}",
		":",
		",",
		"::",
		"an identifer",
		"\"truncatable\"",
		"\"supports\"",
		"\"public\"",
		"\"private\"",
		"\"factory\"",
		"(",
		")",
		"\"in\"",
		"\"const\"",
		"=",
		"|",
		"^",
		"&",
		"<<",
		">>",
		"+",
		"-",
		"*",
		"/",
		"%",
		"~",
		"\"TRUE\"",
		"\"FALSE\"",
		"\"typedef\"",
		"\"native\"",
		"\"float\"",
		"\"double\"",
		"\"long\"",
		"\"short\"",
		"\"unsigned\"",
		"\"char\"",
		"\"wchar\"",
		"\"boolean\"",
		"\"octet\"",
		"\"any\"",
		"\"Object\"",
		"\"struct\"",
		"\"union\"",
		"\"switch\"",
		"\"case\"",
		"\"default\"",
		"\"enum\"",
		"\"sequence\"",
		"<",
		">",
		"\"string\"",
		"\"wstring\"",
		"[",
		"]",
		"\"exception\"",
		"\"oneway\"",
		"\"void\"",
		"\"out\"",
		"\"inout\"",
		"\"raises\"",
		"\"context\"",
		"\"fixed\"",
		"\"ValueBase\"",
		"\"import\"",
		"\"typeid\"",
		"\"typeprefix\"",
		"\"readonly\"",
		"\"attribute\"",
		"\"getraises\"",
		"\"setraises\"",
		"\"component\"",
		"\"provides\"",
		"\"uses\"",
		"\"multiple\"",
		"\"emits\"",
		"\"publishes\"",
		"\"consumes\"",
		"\"home\"",
		"\"manages\"",
		"\"primarykey\"",
		"\"finder\"",
		"an integer value",
		"an octal value",
		"a hexadecimal value value",
		"a string literal",
		"a wide string literal",
		"a character literal",
		"a wide character literal",
		"FIXED",
		"a floating point value",
		"?",
		".",
		"!",
		"white space",
		"a preprocessor directive",
		"a comment",
		"a comment",
		"an escape sequence",
		"an escaped character value",
		"a digit",
		"a non-zero digit",
		"an octal digit",
		"a hexadecimal digit",
		"an escaped identifer"
	};
	
	}
	
