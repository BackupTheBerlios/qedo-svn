/*
 * Created on 11.04.2006
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccmio.parser;

import java.util.List;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.common.util.TreeIterator;

import CCMModel.AliasDef;
import CCMModel.CCM;
import CCMModel.CCMModelFactory;
import CCMModel.ConstantDef;
import CCMModel.EnumDef;
import CCMModel.ExceptionDef;
import CCMModel.Field;
import CCMModel.IDLType;
import CCMModel.IDLTypeContainer;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.ParameterMode;
import CCMModel.PrimitiveDef;
import CCMModel.PrimitiveKind;
import CCMModel.SequenceDef;
import CCMModel.StructDef;
import CCMModel.Typed;
import CCMModel.UnionDef;
import CCMModel.UnionField;

/**
 * @author tri
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class IdlTreeWalkerHelper {

	private IDLTypeContainer idlcontainer;
	private CCMModel.CCM ccm;

	private static CCMModelFactory cCMModelFactory = CCMModelFactory.eINSTANCE;
	
	public IdlTreeWalkerHelper(CCM ccm) {
		this.ccm = ccm;
		idlcontainer = ccm.getIdlContainer();
	}

	public ParameterDef createParameterDef(ParameterMode mode, IDLType type, String Name)
	{
		ParameterDef paraDef = cCMModelFactory.createParameterDef();
		paraDef.setIdentifier(Name);
		paraDef.setIDLType(type);
		paraDef.setDirection(mode);
		
		return paraDef;
		
	}

	public SequenceDef createSequence(IDLType type)
	{
		SequenceDef seqDef = cCMModelFactory.createSequenceDef();
		seqDef.setIDLType(type);
//		seqDef.setBound();

		idlcontainer.getSequences().add(seqDef);

		return seqDef;
		
	}
	
	
	public AliasDef create_alias(CCMModel.IDLType type, String Name, CCMModel.Container container)
	{
		String absolute_name = container.getAbsoluteName() + "::" + Name;
		AliasDef aliasDef = cCMModelFactory.createAliasDef();
		aliasDef.setIdentifier(Name);
		aliasDef.setAbsoluteName(absolute_name);
		aliasDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name) + ":1.0");
		aliasDef.setVersion("1.0");
		aliasDef.setDefinedIn(container);
		aliasDef.setIDLType(type);
		
		return aliasDef;
	}

	public ConstantDef create_const(CCMModel.IDLType type, String Name, String value, CCMModel.Container container)
	{
		String absolute_name = container.getAbsoluteName() + "::" + Name;
		ConstantDef constDef = cCMModelFactory.createConstantDef();
		constDef.setIdentifier(Name);
		constDef.setAbsoluteName(absolute_name);
		constDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name) + ":1.0");
		constDef.setVersion("1.0");
		constDef.setDefinedIn(container);
		constDef.setIDLType(type);
		constDef.setConstValue(value);
		
		return constDef;
	}

	public Field create_field(IDLType type, String name)
	{
		
		//String absolute_name = container.getAbsoluteName() + Name;
		Field field = cCMModelFactory.createField();
		field.setIdentifier(name);
		field.setIDLType(type);
		
		return field;
	}

	public StructDef create_struct(String name, List fields, CCMModel.Container container)
	{
		String absolute_name = container.getAbsoluteName() + "::" + name;
		StructDef structDef = cCMModelFactory.createStructDef();
		structDef.setIdentifier(name);
		structDef.setAbsoluteName(absolute_name);
		structDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name) + ":1.0");
		structDef.setVersion("1.0");
		structDef.setDefinedIn(container);
		structDef.getMembers().addAll(fields);
		return structDef;
	}

	public ExceptionDef create_exception(String name, List fields, CCMModel.Container container)
	{
		String absolute_name = container.getAbsoluteName() + "::" + name;
		ExceptionDef exceptionDef = cCMModelFactory.createExceptionDef();
		exceptionDef.setIdentifier(name);
		exceptionDef.setAbsoluteName(absolute_name);
		exceptionDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name)+ ":1.0");
		exceptionDef.setVersion("1.0");
		exceptionDef.setDefinedIn(container);
		exceptionDef.getMembers().addAll(fields);
		return exceptionDef;
	}
	
	public UnionDef create_union(String name, IDLType type, List union_fields, CCMModel.Container container)
	{
		String absolute_name = container.getAbsoluteName() + "::" + name;
		UnionDef unionDef = cCMModelFactory.createUnionDef();
		unionDef.setIdentifier(name);
		unionDef.setAbsoluteName(absolute_name);
		unionDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name) + ":1.0");
		unionDef.setVersion("1.0");
		unionDef.setDiscriminatorType(type);
		unionDef.setDefinedIn(container);
		unionDef.getUnionMembers().addAll(union_fields);
		return unionDef;
	}
	

	public UnionField create_union_field(String expr, IDLType type, String name)
	{
		UnionField unionField = cCMModelFactory.createUnionField();
		unionField.setIdentifier(name);
		unionField.setIDLType(type);
		unionField.setLabel(expr);
		return unionField;
	}

	public CCMModel.IDLType find_idl_type_by_sc_name(String sc_name)
	{
		CCMModel.Contained contained = null;
		TreeIterator itr = ccm.eAllContents();
		Object obj = null;
		obj = itr.next();
		for (;itr.hasNext();obj=itr.next())
		{
			if (obj instanceof CCMModel.Contained) {
				contained = (CCMModel.Contained) obj;

				if (sc_name_type_match(sc_name, contained))
				{
					if (contained instanceof IDLType )
					{
						return (IDLType)contained;
					}
					if (contained instanceof Typed )
					{
						return ((Typed)contained).getIDLType();
					}
					System.out.println("problem");
				}
			} 
		}
		System.out.println("!!!!!!Did not find the type of scoped name: " + sc_name );
		
		return null;		
	}
	

	public boolean sc_name_type_match(String sc_name, CCMModel.Contained contained)
	{
		// check for identifier in correct scope
		// TODO: find the correct code
		// check for identifier

		if (sc_name.equals(contained.getIdentifier()))
		{
			return true;
		}

		String contained_name = contained.getAbsoluteName();
		
		// check for absolute name with leading "::"
		if (sc_name.equals(contained_name))
		{
			return true;
		}
		
		// check for absolute name without leading "::"
		if (contained_name.startsWith("::"))
		{
			String temp_string = contained_name.substring(2); // cutof the first "::"
			if (sc_name.equals(temp_string))
			{
				return true;
			}
		}

		return false;
	}
	public PrimitiveDef find_primitive_type(PrimitiveKind type_kind)
	{
		
		EList primitiveDefs = idlcontainer.getPrimitiveTypes();
		for (int i=0;i<primitiveDefs.size();i++)
		{
			if (((PrimitiveDef)primitiveDefs.get(i)).getKind() == type_kind)
			{
				return (PrimitiveDef)primitiveDefs.get(i);
			}
		}
		return null;
	}
	
	public OperationDef createOperationDefinition(boolean op_attr, String Name, IDLType type, List params, CCMModel.Container container) {
		String absolute_name = container.getAbsoluteName() + "::" + Name;
		OperationDef operationDef = cCMModelFactory.createOperationDef();
		operationDef.setIdentifier(Name);
		operationDef.setAbsoluteName(absolute_name);
		operationDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name) + ":1.0");
		operationDef.setVersion("1.0");
		operationDef.setDefinedIn(container);

		operationDef.setIDLType(type);
		operationDef.setIsOneway(op_attr);
		operationDef.getParameters().addAll(params);
		
		return operationDef;
		
	}

	public ModuleDef createModuleDefinition(String Name, CCMModel.Container container) {
		String absolute_name = container.getAbsoluteName() + "::" + Name;
		ModuleDef modDef = cCMModelFactory.createModuleDef();
		modDef.setIdentifier(Name);
		modDef.setAbsoluteName(absolute_name);
		modDef.setPrefix("");
		modDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name) + ":1.0");
		modDef.setVersion("1.0");
		modDef.setDefinedIn(container);

		return modDef;
		
	}

	public InterfaceDef createInterfaceDefinition(String Name, CCMModel.Container container)
	{
		String absolute_name = container.getAbsoluteName() + "::" + Name;
		InterfaceDef intDef = cCMModelFactory.createInterfaceDef();
		intDef.setIdentifier(Name);
		intDef.setAbsoluteName(absolute_name);
		intDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name) + ":1.0");
		intDef.setVersion("1.0");
		intDef.setDefinedIn(container);

		return intDef;
		
	}
	public EnumDef createEnumerationDefinition(String Name, 
			List enumerationLiterals, 
			CCMModel.Container container) 
	{
		String absolute_name = container.getAbsoluteName() + "::" + Name;
		EnumDef enumDef = cCMModelFactory.createEnumDef();
		enumDef.setAbsoluteName(absolute_name);
		enumDef.setIdentifier(Name);
		enumDef.setRepositoryId("IDL:" + make_underline_from_double_colon(absolute_name)+ ":1.0");
		enumDef.setVersion("1.0");
		enumDef.getMembers().addAll(enumerationLiterals);
		return enumDef;
	}

	
	public String make_underline_from_double_colon (String col_name)
	{
		if (col_name.startsWith("::"))
		{
			col_name = col_name.substring(2);
		}
		return col_name.replaceAll("::","/");
	}
/*	
	public void main(String[] args) throws RecognitionException, TokenStreamException {

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
*/	
}
