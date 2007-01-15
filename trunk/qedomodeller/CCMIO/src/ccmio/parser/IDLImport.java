/*
 * Created on 13.04.2006
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccmio.parser;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;

import CCMModel.CCM;
import antlr.RecognitionException;
import antlr.TokenStreamException;
import antlr.collections.AST;
import antlr.debug.misc.ASTFrame;

/**
 * @author Tom Ritter
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */

public class IDLImport {
	
	public void imports(CCM ccm,
			String inputFileName,
			boolean merge) throws FileNotFoundException 
	{
		CCMModel.ModuleDef root = ccm.getModuleDef();
		if (!merge)
		{
			root.setAbsoluteName("");
			root.setIdentifier("TETS");
			root.setRepositoryId("TET");
			root.setVersion("1.0");
			root.setPrefix("");
		}
		

		IDLLexer lexer = new IDLLexer(new InputStreamReader(new FileInputStream(inputFileName)));
		
		IDLParser parser = new IDLParser(lexer);

		try {
			parser.specification();
		} catch (RecognitionException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (TokenStreamException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

//		ASTFactory astfactory = new ASTFactory();
	//	parser.setASTFactory( astfactory);


		AST t = parser.getAST();

		System.out.println(t.toStringList());
		
		//ASTFrame frame = new ASTFrame("AST JTree Example", t);
		//frame.setVisible(true);
		
		//instantiate helper object
		IdlTreeWalkerHelper helper = new IdlTreeWalkerHelper(ccm);

		IDLTreeParser walker = new IDLTreeParser(helper);
		
		try {
			walker.specification(t, root);
		} catch (RecognitionException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		
		//System.out.println(enumDef);
		
	}

}
