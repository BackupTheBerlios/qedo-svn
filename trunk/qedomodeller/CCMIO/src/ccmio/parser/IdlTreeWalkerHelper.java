/*
 * Created on 11.04.2006
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccmio.parser;

import java.io.ByteArrayInputStream;
import java.io.InputStreamReader;
import java.util.List;

import CCMModel.CCMModelFactory;
import CCMModel.Container;
import CCMModel.EnumDef;
import CCMModel.ModuleDef;
import antlr.ASTFactory;
import antlr.RecognitionException;
import antlr.TokenStreamException;
import antlr.collections.AST;

/**
 * @author tri
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class IdlTreeWalkerHelper {
	
	private static CCMModelFactory cCMModelFactory = CCMModelFactory.eINSTANCE;
	
	private IdlTreeWalkerHelper() {
	}

	public static ModuleDef createModuleDefinition(String Name, CCMModel.Container container) {
		String absolute_name = container.getAbsoluteName() + Name;
		ModuleDef modDef = cCMModelFactory.createModuleDef();
		modDef.setIdentifier(Name);
		modDef.setAbsoluteName(absolute_name);
		modDef.setPrefix("");
		modDef.setRepositoryId("IDL:" + Name + ":1.0");
		modDef.setVersion("1.0");
		modDef.setDefinedIn(container);

		return modDef;
		
	}
	
	public static EnumDef createEnumerationDefinition(String enumerationName, List enumerationLiterals) {
		EnumDef enumDef = cCMModelFactory.createEnumDef();
		enumDef.setIdentifier(enumerationName);
		enumDef.getMembers().addAll(enumerationLiterals);
		return enumDef;
	}

	
	public static void main(String[] args) throws RecognitionException, TokenStreamException {

		ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(" enum myEnum { label1 , label2 }".getBytes());
		
		
		IDLLexer lexer = new IDLLexer(new InputStreamReader(byteArrayInputStream));   
		IDLParser parser = new IDLParser(lexer);

		ASTFactory astfactory = new ASTFactory();
//		parser.initializeASTFactory(astfactory);
		parser.setASTFactory( astfactory);

//parser.oclExpressionCS();
		parser.enum_type();

		AST t = parser.getAST();

		IDLTreeParser walker = new IDLTreeParser();
		
		// make sure the factory knows about all AST types in the parser..
//		walker.initializeASTFactory(astfactory);
		// and tell the parser about the factory..
		walker.setASTFactory( astfactory );
		
	//	EnumDef enumDef = walker.enum_typeAS(t);
		
		//System.out.println(enumDef);
		
	}
	
}
