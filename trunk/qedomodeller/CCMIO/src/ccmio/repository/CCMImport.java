package ccmio.repository;

import java.util.ArrayList;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EObject;
import org.omg.CORBA.BAD_PARAM;

import CCMModel.AbstractDerivedRelation;
import CCMModel.AbstractInterfaceDef;
import CCMModel.AbstractItfDerivedRelation;
import CCMModel.ArrayDef;
import CCMModel.AttributeDef;
import CCMModel.CCM;
import CCMModel.CCMModelFactory;
import CCMModel.CompHomeRelation;
import CCMModel.ComponentCategory;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.EmitsDef;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
import CCMModel.EventPortEventRelation;
import CCMModel.ExceptionDef;
import CCMModel.FactoryDef;
import CCMModel.Field;
import CCMModel.FinderDef;
import CCMModel.FixedDef;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.IDLType;
import CCMModel.IDLTypeContainer;
import CCMModel.InterfaceDef;
import CCMModel.InterfaceRelation;
import CCMModel.PublishesDef;
//import CCMModel.IpmlementsRelation;
import CCMModel.ManagersRelation;
import CCMModel.MediaType;
import CCMModel.ModuleDef;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.ParameterMode;
import CCMModel.PrimitiveDef;
import CCMModel.PrimitiveKind;
import CCMModel.ProvidesDef;
import CCMModel.SegmentDef;
import CCMModel.SequenceDef;
import CCMModel.StreamProtDef;
import CCMModel.StringDef;
import CCMModel.StructDef;
import CCMModel.SupportsRelation;
import CCMModel.Typed;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.UsesDef;
import CCMModel.ValueDef;
import CCMModel.ValueDerivedRelation;
import CCMModel.ValueMemberDef;
import CCMModel.WstringDef;
import MDE.BaseIDL.AliasDefHelper;
import MDE.BaseIDL.ArrayDefHelper;
import MDE.BaseIDL.AttributeDefHelper;
import MDE.BaseIDL.ConstantDefHelper;
import MDE.BaseIDL.ContainedHelper;
import MDE.BaseIDL.ContainerHelper;
import MDE.BaseIDL.EnumDefHelper;
import MDE.BaseIDL.ExceptionDefHelper;
import MDE.BaseIDL.FixedDefHelper;
import MDE.BaseIDL.InterfaceDefHelper;
import MDE.BaseIDL.ModuleDefHelper;
import MDE.BaseIDL.OperationDefHelper;
import MDE.BaseIDL.PrimitiveDefHelper;
import MDE.BaseIDL.SequenceDefHelper;
import MDE.BaseIDL.StringDefHelper;
import MDE.BaseIDL.StructDefHelper;
import MDE.BaseIDL.TypedHelper;
import MDE.BaseIDL.TypedefDefHelper;
import MDE.BaseIDL.UnionDefHelper;
import MDE.BaseIDL.ValueBoxDefHelper;
import MDE.BaseIDL.ValueDefHelper;
import MDE.BaseIDL.ValueMemberDefHelper;
import MDE.BaseIDL.WstringDefHelper;
import MDE.BaseIDL._BaseIDLPackage;
import MDE.CIF.ComponentImplDefHelper;
import MDE.CIF.CompositionDef;
import MDE.CIF.CompositionDefHelper;
import MDE.CIF.HomeImplDefHelper;
import MDE.CIF.SegmentDefHelper;
import MDE.CIF._CIFPackage;
import MDE.ComponentIDL.ComponentDefHelper;
import MDE.ComponentIDL.ConsumesDefHelper;
import MDE.ComponentIDL.EmitsDefHelper;
import MDE.ComponentIDL.EventDefHelper;
import MDE.ComponentIDL.EventPortDefHelper;
import MDE.ComponentIDL.FactoryDefHelper;
import MDE.ComponentIDL.FinderDefHelper;
import MDE.ComponentIDL.HomeDefHelper;
import MDE.ComponentIDL.MediaTypeHelper;
import MDE.ComponentIDL.ProvidesDefHelper;
import MDE.ComponentIDL.PublishesDefHelper;
import MDE.ComponentIDL.SiSouDefHelper;
import MDE.ComponentIDL.SinkDefHelper;
import MDE.ComponentIDL.SourceDefHelper;
import MDE.ComponentIDL.StreamPortDefHelper;
import MDE.ComponentIDL.UsesDefHelper;
import MDE.ComponentIDL._ComponentIDLPackage;
import Reflective.MofError;
import Reflective.NotSet;

/**
 *	This Class represents the import from a ccmrepository to a ccm-model-file
 *	
 *	see imports(CCM ccm, String RepositoryRootRefFile)
 */
public class CCMImport {

	private static _BaseIDLPackage baseIDLPackage;
	private static _ComponentIDLPackage componentIDLPackage;
	private static _CIFPackage CIFPackage;
	private static CCM ccm;
	private static IDLTypeContainer idlcontainer;

	// lists of all objects in repository and emf-model to search in.. 
	private static ArrayList 	ids,repmodel,emfmodel;

	/**
	 * This methode connect to a repository and adds its contens to a emf-model.
	 * @param repository = repository to add the model
	 * @param repositoryModule = this Module will be Imported
	 * @param ccm = to this CCM-Object the contens of the repository will be add
	 * @return Error-String or null if imported successfully
	 */
	public static void imports(CCMRepository repository, MDE.BaseIDL.ModuleDef repositoryModule, CCM ccm) 
	throws MofError
	{
		CCMImport.ccm = ccm;
		
		// initialize the lists
		ids = new ArrayList();repmodel = new ArrayList();emfmodel = new ArrayList();
		
		// get all needed packages
		baseIDLPackage = repository.getMDE().base_idl_ref();
		componentIDLPackage = repository.getMDE().component_idl_ref();
		CIFPackage = repository.getMDE().cif_ref();

		idlcontainer = ccm.getIdlContainer();
		
		// 1. updates the rootmodule
		ModuleDef root = createRoot(repositoryModule);
		
		// 2. create the contens of the rootmodule
		root.getContents().addAll(createContents(repositoryModule.contents()));
		
		// 3. & 4. create the relations and updates the missing properties 
		updateEMFModel();
	}
	/* --------------------------------- CREATEROOT ------------------------------------------------ */
	/**
	 * This methode updates the Root-Module and create its contens in Repository.
	 * @param repositoryModule = the root-module to import to the ccm-file. 
 	 */
	private static ModuleDef createRoot(MDE.BaseIDL.ModuleDef repositoryModule) throws MofError
	{
		System.out.println("rootmodule: " + repositoryModule.identifier());
		ModuleDef root = ccm.getModuleDef();
		{
			root.setAbsoluteName(repositoryModule.identifier());
			root.setIdentifier(repositoryModule.identifier());
			root.setRepositoryId(repositoryModule.repository_id());
			root.setVersion(repositoryModule.version());
			root.setPrefix(repositoryModule.prefix());
		}
		return root;
	}
	/* --------------------------------- CREATE ------------------------------------------------ */
	/**
	 * creates the repository-objects in our emf-model and returns them
	 * @param contents = list of repository-contained-objects to create
	 * @return list of the new created ccmmodel-objects
	 */
	private static ArrayList createContents(MDE.BaseIDL.Contained[] contents) throws MofError
	{
		ArrayList result = new ArrayList();
		for (int i=0; i<contents.length;i++)
		{
			Contained emfcontained = create(contents[i]);
			
			if (emfcontained != null) 	
			{
				String absoluteName = fullScopeName(contents[i]);
				emfcontained.setAbsoluteName(absoluteName);
				emfcontained.setIdentifier(contents[i].identifier());
				emfcontained.setRepositoryId(contents[i].repository_id());
				emfcontained.setVersion(contents[i].version());
				emfmodel.add(emfcontained);
				repmodel.add(contents[i]);
				ids.add(absoluteName);
				result.add(emfcontained);
			}
			if (emfcontained instanceof Typed)
			{
				MDE.BaseIDL.IDLType type = TypedHelper.narrow(contents[i]).idl_type();
				IDLType emftype;
				if (type != null)
					if ((emftype = createIDLType(type)) != null)
						((Typed)emfcontained).setIDLType(emftype);
			}
			if (emfcontained instanceof Container)
			{
				MDE.BaseIDL.Contained[] cns = ContainerHelper.narrow(contents[i]).contents();
				((Container)emfcontained).getContents().addAll(createContents(cns));
			}

		}
		return result;
	}
	/**
	 * create a repository-object in our emf-model.
	 * @param rep = repository-contained-object to create
	 * @return the new created ccmmodel-object
	 */
	private static Contained create(MDE.BaseIDL.Contained contained) throws MofError
	{
		Contained emf;
		System.out.println("\t" + contained.identifier());
		try{ 
			MDE.BaseIDL.ModuleDef moduleDef = ModuleDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createModuleDef(); // Module
			((ModuleDef) emf).setPrefix(moduleDef.prefix());
			return emf;
		} catch(Exception e) {}
		
		try{ 
			MDE.ComponentIDL.HomeDef homeDef = HomeDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createHomeDef(); // Home
			((HomeDef)emf).getFactorys().addAll(createContents(homeDef.factorys()));
			((HomeDef)emf).getFinders().addAll(createContents(homeDef.finders()));
			((HomeDef)emf).setIsAbstract(homeDef.is_abstract());
			((HomeDef)emf).setIsLocal(homeDef.is_local());
			return emf;
		} catch(Exception e) {}
		
		try{ 
			MDE.ComponentIDL.ComponentDef componentDef = ComponentDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createComponentDef(); // Component
			((ComponentDef)emf).getConsumess().addAll(createContents(componentDef.consumess()));
			((ComponentDef)emf).getEmitss().addAll(createContents(componentDef.emitss()));
			((ComponentDef)emf).getFacet().addAll(createContents(componentDef.facet()));
			((ComponentDef)emf).getPublishesDef().addAll(createContents(componentDef.publishess()));
			((ComponentDef)emf).getReceptacle().addAll(createContents(componentDef.receptacle()));
			((ComponentDef)emf).getSinkss().addAll(createContents(componentDef.sinkss()));
			((ComponentDef)emf).getSourcess().addAll(createContents(componentDef.sourcess()));
			((ComponentDef)emf).getSiSouss().addAll(createContents(componentDef.sisouss()));
			((ComponentDef)emf).setIsAbstract(componentDef.is_abstract());
			((ComponentDef)emf).setIsLocal(componentDef.is_local());
			return emf;
		} catch(Exception e) {}
		try{ 
			MDE.BaseIDL.InterfaceDef interfaceDef = InterfaceDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createInterfaceDef(); // Interface
			((InterfaceDef)emf).setIsAbstract(interfaceDef.is_abstract());
			((InterfaceDef)emf).setIsLocal(interfaceDef.is_local());
			return emf;
		} catch(Exception e) {}
		 
		

		try{ 
			MDE.CIF.CompositionDef composition = CompositionDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createComposition(); // Interface
			((Composition)emf).setCategory(getComponentCategory(composition.category()));
			return emf;
		} catch(Exception e) {}
		
		try{ 
			MDE.CIF.ComponentImplDef componentImplDef = ComponentImplDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createComponentImplDef(); // componentimpl
			((ComponentImplDef)emf).setCategory(getComponentCategory(componentImplDef.category()));
			((ComponentImplDef)emf).getSegment().addAll(createContents(componentImplDef.segment()));
			return emf;
		} catch(Exception e) {}
		
		try{ 
			HomeImplDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createHomeImplDef(); // HomeImplDef
			return emf;
		} catch(Exception e) {}

		try{
			MDE.ComponentIDL.EventDef eventDef = EventDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createEventDef(); // EventDef
			((EventDef)emf).setIsAbstract(eventDef.is_abstract());
			((EventDef)emf).setIsCustom(eventDef.is_custom());
			((EventDef)emf).setIsTruncatable(eventDef.is_truncatable());
			return emf;
		} catch(Exception e) {}

		try{ 
			MDE.BaseIDL.ValueDef valueDef = ValueDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createValueDef(); // ValueDef
			((ValueDef)emf).setIsAbstract(valueDef.is_abstract());
			((ValueDef)emf).setIsCustom(valueDef.is_custom());
			((ValueDef)emf).setIsTruncatable(valueDef.is_truncatable());
			return emf;
		} catch(Exception e) {}

		/*******************************************************************************************************/
		try{
			AliasDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createAliasDef();
			return emf;
		} catch(Exception e) {}

		try{
			MDE.BaseIDL.AttributeDef attributeDef = AttributeDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createAttributeDef();
			((AttributeDef)emf).setIsReadonly(attributeDef.is_readonly());
			return emf;
		} catch(Exception e) {}
		
		try{
			MDE.BaseIDL.ConstantDef constantDef = ConstantDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createConstantDef();
			((ConstantDef)emf).setConstValue(constantDef.const_value());
			return emf;
		} catch(Exception e) {}

		try{
			ConsumesDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createConsumesDef();
			return emf;
		} catch(Exception e) {}

		try{
			EmitsDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createEmitsDef();				
			return emf;
		} catch(Exception e) {}

		try{
			MDE.BaseIDL.EnumDef enumDef = EnumDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createEnumDef();
			EList emfmembers = ((EnumDef)emf).getMembers();
			String[] repmembers = enumDef.members();
			for (int i=0;i<repmembers.length;i++)
				emfmembers.add(repmembers[i]);
			return emf;
		} catch(Exception e) {}

		try{
			MDE.BaseIDL.ExceptionDef exceptionDef = ExceptionDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createExceptionDef();
			((ExceptionDef)emf).getMembers().addAll(createFields(exceptionDef.members()));
			((ExceptionDef)emf).setTypeCode(exceptionDef.type_code());
			return emf;
		} catch(Exception e) {}

		try{
			MDE.ComponentIDL.FactoryDef factoryDef = FactoryDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createFactoryDef();
			((FactoryDef)emf).setIsOneway(factoryDef.is_oneway());
			((FactoryDef)emf).setContext(factoryDef.contexts());
			((FactoryDef)emf).getParameters().addAll(createParameters(factoryDef.parameters()));
			return emf;
		} catch(Exception e) {}

		try{
			MDE.ComponentIDL.FinderDef finderDef = FinderDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createFinderDef();
			((FinderDef)emf).setIsOneway(finderDef.is_oneway());
			((FinderDef)emf).setContext(finderDef.contexts());
			((FinderDef)emf).getParameters().addAll(createParameters(finderDef.parameters()));
			return emf;
		} catch(Exception e) {}

		try{
			MediaTypeHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createMediaType();
			return emf;
		} catch(Exception e) {}

		try{
			MDE.BaseIDL.OperationDef operationDef = OperationDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createOperationDef();
			((OperationDef)emf).setIsOneway(operationDef.is_oneway());
			((OperationDef)emf).setContext(operationDef.contexts());
			((OperationDef)emf).getParameters().addAll(createParameters(operationDef.parameters()));
			return emf;
		} catch(Exception e) {}

		try{
			PublishesDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createPublishesDef();
			return emf;
		} catch(Exception e) {}

		try{
			ProvidesDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createProvidesDef();
			return emf;
		} catch(Exception e) {}

		try{
			MDE.CIF.SegmentDef segmentDef = SegmentDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createSegmentDef();				
			((SegmentDef)emf).setIsSerialized(segmentDef.is_serialized());
			return emf;
		} catch(Exception e) {}

		try{
			SinkDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createSinkDef();
			return emf;
		} catch(Exception e) {}

		try{
			SiSouDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createSiSouDef();
			return emf;
		} catch(Exception e) {}
			
		try{
			SourceDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createSourceDef();
			return emf;
		} catch(Exception e) {}

		try{
			MDE.BaseIDL.StructDef structDef = StructDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createStructDef();
			((StructDef)emf).getMembers().addAll(createFields(structDef.members()));
			return emf;
		} catch(Exception e) {}

		try{
			MDE.BaseIDL.UnionDef unionDef = UnionDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createUnionDef();
			((UnionDef)emf).getUnionMembers().addAll(createUnionFields(unionDef.union_members()));
			return emf;
		} catch(Exception e) {}

		try{
			MDE.ComponentIDL.UsesDef usesDef = UsesDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createUsesDef();
			((UsesDef)emf).setMultipleItf(usesDef.multiple_itf());
			return emf;
		} catch(Exception e) {}

		try{
			ValueBoxDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createValueBoxDef();
			return emf;
		} catch(Exception e) {}

		try{
			MDE.BaseIDL.ValueMemberDef valueMemberDef = ValueMemberDefHelper.narrow(contained);
			emf = CCMModelFactory.eINSTANCE.createValueMemberDef();

			((ValueMemberDef)emf).setIsPublicMember(valueMemberDef.is_public_member());
			return emf;
		} catch(Exception e) {}
		/******************************************************************************************************/
	
		return null;
	}
	/**
	 * creates a IDLType like the repository-object repIDLType.
	 * @param repIDLType = repository-IDLType to create
	 * @return the new ccmmodel-IDLType
	 */
	private static IDLType createIDLType(MDE.BaseIDL.IDLType repIDLType) throws MofError
	{
		try{
			MDE.BaseIDL.TypedefDef typedefDef = TypedefDefHelper.narrow(repIDLType);
			return (IDLType)create(typedefDef);
		}catch (Exception e){}

		try{
			MDE.BaseIDL.ArrayDef arrayDef = ArrayDefHelper.narrow(repIDLType);
			ArrayDef emfArrayDef = CCMModelFactory.eINSTANCE.createArrayDef();
			emfArrayDef.setBound(arrayDef.bound());
			emfmodel.add(emfArrayDef); repmodel.add(arrayDef); ids.add("array");
			MDE.BaseIDL.IDLType repIDLType2 = arrayDef.idl_type();
			IDLType emfIDLType2;
			if (repIDLType2 != null)
				if ((emfIDLType2 = createIDLType(repIDLType2)) != null)
					emfArrayDef.setIDLType(emfIDLType2);
			idlcontainer.getArrays().add(emfArrayDef);
			return emfArrayDef;
		}catch (Exception e){}

		try{
			MDE.BaseIDL.SequenceDef sequenceDef = SequenceDefHelper.narrow(repIDLType);
			SequenceDef emfSequenceDef = CCMModelFactory.eINSTANCE.createSequenceDef();
			emfSequenceDef.setBound(sequenceDef.bound());
			emfmodel.add(emfSequenceDef); repmodel.add(sequenceDef); ids.add("sequence");
			MDE.BaseIDL.IDLType repIDLType2 = sequenceDef.idl_type();
			IDLType emfIDLType2;
			if (repIDLType2 != null)
				if ((emfIDLType2 = createIDLType(repIDLType2)) != null)
					emfSequenceDef.setIDLType(emfIDLType2);
			idlcontainer.getSequences().add(emfSequenceDef);
			return emfSequenceDef;
		}catch (Exception e){}

		try{
			MDE.BaseIDL.WstringDef wstringDef = WstringDefHelper.narrow(repIDLType);
			WstringDef emfWstringDef = CCMModelFactory.eINSTANCE.createWstringDef();
			emfWstringDef.setBound(wstringDef.bound());
			idlcontainer.getWstrings().add(emfWstringDef);
			return emfWstringDef;
		}catch (Exception e){}
		try{
			MDE.BaseIDL.StringDef stringDef = StringDefHelper.narrow(repIDLType);
			StringDef emfStringDef = CCMModelFactory.eINSTANCE.createStringDef();
			emfStringDef.setBound(stringDef.bound());
			idlcontainer.getStrings().add(emfStringDef);
			return emfStringDef;
		}catch (Exception e){}
		try{
			MDE.BaseIDL.FixedDef fixedDef = FixedDefHelper.narrow(repIDLType);
			FixedDef emfFixedDef = CCMModelFactory.eINSTANCE.createFixedDef();
			emfFixedDef.setDigits(fixedDef.digits());
			emfFixedDef.setScale(fixedDef.scale());
			idlcontainer.getFixeds().add(emfFixedDef);
			return emfFixedDef;
		}catch (Exception e){}
		
		try{
			MDE.BaseIDL.PrimitiveDef primitiveDef = PrimitiveDefHelper.narrow(repIDLType);
			PrimitiveDef emfPrimitiveDef = getPrimitiveDef(primitiveDef); 
			return emfPrimitiveDef;
		}catch (Exception e){}

		return null;
	
	}
	/**
	 * create parameters in the emf-model like the repository-ParameterDefs parameters.
	 * @param parameters = repository-ParameterDefs to create
	 * @return list of the new ccmmodel-ParameterDefs
	 */
	private static ArrayList createParameters(MDE.BaseIDL.ParameterDef[] parameters) throws MofError
	{
		ArrayList result = new ArrayList();
		for (int i=0;i<parameters.length;i++) 
		{
			MDE.BaseIDL.ParameterMode direction = parameters[i].direction();
			ParameterDef emfparameter = CCMModelFactory.eINSTANCE.createParameterDef();
			emfparameter.setIdentifier(parameters[i].identifier());
			emfparameter.setDirection(
				(direction == MDE.BaseIDL.ParameterMode.PARAM_IN) ? ParameterMode.PARAM_IN_LITERAL :
				(direction == MDE.BaseIDL.ParameterMode.PARAM_OUT) ? ParameterMode.PARAM_OUT_LITERAL:
				ParameterMode.PARAM_INOUT_LITERAL );
			result.add(emfparameter);
		}
		return result;
	}
	/**
	 * create fields in the emf-model like the repository-Fields fields.
	 * @param fields = repository-Fields to create
	 * @return list of the new ccmmodel-Fields
	 */
	private static ArrayList createFields(MDE.BaseIDL.Field[] fields) throws MofError
	{
		ArrayList result = new ArrayList();
		for (int i=0;i<fields.length;i++) 
		{
			Field emffield = CCMModelFactory.eINSTANCE.createField();
			emffield.setIdentifier(fields[i].identifier());
			result.add(emffield);
		}
		return result;
	}
	/**
	 * create unionfields in the emf-model like the repository-unionfields fields.
	 * @param unionfields = repository-unionfields to create
	 * @return list of the new ccmmodel-unionfields
	 */
	private static ArrayList createUnionFields(MDE.BaseIDL.UnionField[] unionfields) throws MofError
	{
		ArrayList result = new ArrayList();
		for (int i=0;i<unionfields.length;i++) 
		{
			UnionField emfunionfield = CCMModelFactory.eINSTANCE.createUnionField();
			emfunionfield.setIdentifier(unionfields[i].identifier());
			emfunionfield.setLabel(unionfields[i].label());
			result.add(emfunionfield);
		}
		return result;
	}
	/**
	 * get the right ComponentCategory
	 * @param componentCategory = repository-componentCategory
	 * @return the new ccmmodel-componentCategory
	 */
	private static ComponentCategory getComponentCategory(MDE.CIF.ComponentCategory componentCategory) throws MofError
	{
		if (componentCategory == MDE.CIF.ComponentCategory.PROCESS)
			return ComponentCategory.PROCESS_LITERAL;
		else if	(componentCategory == MDE.CIF.ComponentCategory.SESSION)
			return ComponentCategory.SESSION_LITERAL;
		else if	(componentCategory == MDE.CIF.ComponentCategory.ENTITY) 
			return ComponentCategory.ENTITY_LITERAL;
		else if	(componentCategory == MDE.CIF.ComponentCategory.SERVICE)
			return ComponentCategory.SERVICE_LITERAL;
		else 
			return ComponentCategory.EXTENSION_LITERAL;
	}
	/**
	 * gets the PrimiticeDef like the repository-object repPrimitiveDef.
	 * @param repPrimitiveDef = repository-PrimitiveDef to create
	 * @return the new ccmmodel-PrimitiveDef
	 */
	private static PrimitiveDef getPrimitiveDef(MDE.BaseIDL.PrimitiveDef repPrimitiveDef) throws MofError
	{
		MDE.BaseIDL.PrimitiveKind primitiveKind = repPrimitiveDef.kind();
		EList primitiveDefs = idlcontainer.getPrimitiveTypes();
		for (int i=0;i<primitiveDefs.size();i++)
			if (((PrimitiveDef)primitiveDefs.get(i)).getKind() ==
				getPrimitiveKind(primitiveKind))
				return (PrimitiveDef)primitiveDefs.get(i);
		System.out.println("Can�t find PrimitiveDef : "+primitiveKind.toString());
		return null;
	}
	/**
	 * gets the PrimiticeKind like the repository-object repPrimitiveKind.
	 * @param repPrimitiveKind = repository-PrimitiveKind to create
	 * @return the new PrimitiveKind
	 */
	private static PrimitiveKind getPrimitiveKind(MDE.BaseIDL.PrimitiveKind repPrimitiveKind)
	{
		return
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_Boolean) ? PrimitiveKind.PK_BOOLEAN_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_CHAR) ? PrimitiveKind.PK_CHAR_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_DOUBLE) ? PrimitiveKind.PK_DOUBLE_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_FLOAT) ? PrimitiveKind.PK_FLOAT_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_LONG) ? PrimitiveKind.PK_LONG_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_LONGDOUBLE) ? PrimitiveKind.PK_LONGDOUBLE_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_LONGLONG) ? PrimitiveKind.PK_LONGLONG_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_OBJREF) ? PrimitiveKind.PK_OBJREF_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_OCTET) ? PrimitiveKind.PK_OCTET_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_SHORT) ? PrimitiveKind.PK_SHORT_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_STRING) ? PrimitiveKind.PK_STRING_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_TYPECODE) ? PrimitiveKind.PK_TYPECODE_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_ULONG) ? PrimitiveKind.PK_ULONG_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_ULONGLONG) ? PrimitiveKind.PK_ULONGLONG_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_USHORT) ? PrimitiveKind.PK_USHORT_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_VOID) ? PrimitiveKind.PK_VOID_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_WCHAR) ? PrimitiveKind.PK_WCHAR_LITERAL :
			(repPrimitiveKind == MDE.BaseIDL.PrimitiveKind.PK_WSTRING) ? PrimitiveKind.PK_WSTRING_LITERAL :
			PrimitiveKind.PK_ANY_LITERAL;
	}
	
	/* --------------------------------- RELATIONS ------------------------------------------------ */
	/**
	 * create a implements-relation between a ComponentDef and a ComponentImplDef.
	 * @param componentDef = the ComponentDef
 	 * @param componentImplDef = the ComponentImplDef
	 * @return the new relation
	 */
//	private static IpmlementsRelation createImplementsRelation (ComponentDef componentDef,ComponentImplDef componentImplDef) throws MofError
//	{
//		System.out.println("\timplementsRelation");
//		IpmlementsRelation ipmlementsRelation = CCMModelFactory.eINSTANCE.createIpmlementsRelation();
//		ipmlementsRelation.setComponentEnd(componentDef);
//		ipmlementsRelation.setSegsC(componentImplDef);
//		return ipmlementsRelation;
//	}
	/**
	 * create a implements-relation between a ComponentDef and a SegmentDef.
	 * @param componentDef = the ComponentDef
 	 * @param segmentDef = the SegmentDef
	 * @return the new relation
	 */
//	private static IpmlementsRelation createImplementsRelation (ComponentDef componentDef,SegmentDef segmentDef) throws MofError
//	{
//		System.out.println("\timplementsRelation");
//		IpmlementsRelation ipmlementsRelation = CCMModelFactory.eINSTANCE.createIpmlementsRelation();
//		ipmlementsRelation.setComponentEnd(componentDef);
//		ipmlementsRelation.setSegment(segmentDef);
//		return ipmlementsRelation;
//	}
	/**
	 * create a implements-relation between a HomeDef and a HomeImplDef.
	 * @param homeDef = the HomeDef
 	 * @param homeImplDef = the HomeImplDef
	 * @return the new relation
	 */
//	private static IpmlementsRelation createImplementsRelation (HomeDef homeDef,HomeImplDef homeImplDef) throws MofError
//	{
//		System.out.println("\timplementsRelation");
//		IpmlementsRelation ipmlementsRelation = CCMModelFactory.eINSTANCE.createIpmlementsRelation();
//		ipmlementsRelation.setHomeEnd(homeDef);
//		ipmlementsRelation.setSegsH(homeImplDef);
//		return ipmlementsRelation;
//	}
	/**
	 * create a interface-relation between a ProvidesDef and a InterfaceDef.
	 * @param providesDef = the ProvidesDef
 	 * @param interfaceDef = the InterfaceDef
	 * @return the new relation
	 */
	private static InterfaceRelation createInterfaceRelation (ProvidesDef providesDef,InterfaceDef interfaceDef) throws MofError
	{
		System.out.println("\tInterfaceRelation");
		InterfaceRelation interfaceRelation = CCMModelFactory.eINSTANCE.createInterfaceRelation();
		interfaceRelation.setProvidesDef(providesDef);
		interfaceRelation.setItf(interfaceDef);
		return interfaceRelation;
	}
	/**
	 * create a interface-relation between a UsesDef and a InterfaceDef.
	 * @param usesDef = the UsesDef
 	 * @param interfaceDef = the InterfaceDef
	 * @return the new relation
	 */
	private static InterfaceRelation createInterfaceRelation (UsesDef usesDef,InterfaceDef interfaceDef) throws MofError
	{
		System.out.println("\tInterfaceRelation");
		InterfaceRelation interfaceRelation = CCMModelFactory.eINSTANCE.createInterfaceRelation();
		interfaceRelation.setUsesDef(usesDef);
		interfaceRelation.setItf(interfaceDef);
		return interfaceRelation;
	}
	/**
	 * create a supports-relation between a HomeDef and a InterfaceDef.
	 * @param homeDef = the HomeDef
 	 * @param interfaceDef = the InterfaceDef
	 * @return the new relation
	 */
	private static SupportsRelation createSupportsRelation (HomeDef homeDef,InterfaceDef interfaceDef) throws MofError
	{
		System.out.println("\tSupportsRelation");
		SupportsRelation supportsRelation = CCMModelFactory.eINSTANCE.createSupportsRelation();
		supportsRelation.setHomes(homeDef);
		supportsRelation.setSupportsItf(interfaceDef);
		return supportsRelation;
	}
	/**
	 * create a supports-relation between a ComponentDef and a InterfaceDef.
	 * @param componentDef = the ComponentDef
 	 * @param interfaceDef = the InterfaceDef
	 * @return the new relation
	 */
	private static SupportsRelation createSupportsRelation (ComponentDef componentDef,InterfaceDef interfaceDef) throws MofError
	{
		System.out.println("\tSupportsRelation");
		SupportsRelation supportsRelation = CCMModelFactory.eINSTANCE.createSupportsRelation();
		supportsRelation.setComponents(componentDef);
		supportsRelation.setSupportsItf(interfaceDef);
		return supportsRelation;
	}
	/**
	 * create a managers-relation between a ComponentImplDef and a HomeImplDef.
 	 * @param componentImplDef = the ComponentImplDef
 	 * @param homeImplDef = the HomeImplDef
	 * @return the new relation
	 */
	private static ManagersRelation createManagersRelation (ComponentImplDef componentImplDef,HomeImplDef homeImplDef) throws MofError
	{
		System.out.println("\tManagersRelation");
		ManagersRelation managersRelation = CCMModelFactory.eINSTANCE.createManagersRelation();
		managersRelation.setComponent_impl(componentImplDef);
		managersRelation.setHome_impl(homeImplDef);
		return managersRelation;
	}
	/**
	 * create a compHome-relation between a ComponentDef and a HomeDef.
	 * @param componentDef = the ComponentDef
 	 * @param homeDef = the HomeDef
	 * @return the new relation
	 */
	private static CompHomeRelation createCompHomeRelation (ComponentDef componentDef,HomeDef homeDef) throws MofError
	{
		CompHomeRelation compHomeRelation = CCMModelFactory.eINSTANCE.createCompHomeRelation();
		System.out.println("\tCompHomeRelation");
		compHomeRelation.setComponentEnd(componentDef);
		compHomeRelation.setHomeEnd(homeDef);
		return compHomeRelation;
	}
	/**
	 * This methode creates a abstractDerivedRelation between 2 ValueDefs.
	 * @param abstractBase = the abstractBase
	 * @param abstractDerived = the abstractDerived
 	 * @return the new relation
 	 */
	private static AbstractDerivedRelation createAbstractDerivedRelation (ValueDef abstractBase, ValueDef abstractDerived) 
	throws MofError
	{
		AbstractDerivedRelation abstractDerivedRelation = CCMModelFactory.eINSTANCE.createAbstractDerivedRelation();
		System.out.println("\tabstractDerivedRelation");
		abstractDerivedRelation.setAbstractBase(abstractBase);
		abstractDerivedRelation.setAbstractDerived(abstractDerived);
		return abstractDerivedRelation;
	}
	/**
	 * This methode creates a abstractItfDerivedRelation.
	 * @param base = the Base
	 * @param derived = the Derived
	 * @return the new relation
 	 */
	private static AbstractItfDerivedRelation createAbstractItfDerivedRelation (AbstractInterfaceDef base, AbstractInterfaceDef derived) 
	throws MofError
	{
		AbstractItfDerivedRelation abstractItfDerivedRelation = 
			CCMModelFactory.eINSTANCE.createAbstractItfDerivedRelation();
		System.out.println("\tabstractItfDerivedRelation");
		abstractItfDerivedRelation.setBase(base);
		abstractItfDerivedRelation.setDerived(derived);
		return abstractItfDerivedRelation;
	}
	/**
	 * This methode creates a valueDerivedRelation.
	 * @param base = the Base
	 * @param derived = the Derived
	 * @return the new relation
 	 */
	private static ValueDerivedRelation createValueDerivedRelation (ValueDef base, ValueDef derived) 
	throws MofError
	{
		ValueDerivedRelation valueDerivedRelation =
			CCMModelFactory.eINSTANCE.createValueDerivedRelation();
		System.out.println("\tvalueDerivedRelation");
		valueDerivedRelation.setBase(base);
		valueDerivedRelation.setDerived(derived);
		return valueDerivedRelation;
	}
	/**
	 * This methode creates a eventPortEventRelation.
	 * @param eventPortDef = the eventPortDef
	 * @param eventDef = the eventDef
	 * @return the new relation
 	 */
	private static EventPortEventRelation createEventPortEventRelation (EventPortDef eventPortDef, EventDef eventDef) 
	throws MofError
	{
		EventPortEventRelation eventPortEventRelation =
			CCMModelFactory.eINSTANCE.createEventPortEventRelation();
		System.out.println("\tEventPortEventRelation");
		eventPortEventRelation.setEnds(eventPortDef);
		eventPortEventRelation.setType(eventDef);
		return eventPortEventRelation;
	}
	
	/* --------------------------------- UPADTE ------------------------------------------------ */
	/**
	 * This methode updates all missing properties in the CCMEditor-file.
 	 */
	private static void updateEMFModel() throws MofError
	{
		System.out.println("Updates");
		// updates the properties of the emf-objects like the objects in the repository
		for (int i=0; i<emfmodel.size();i++)
		{
			EObject emf = (EObject)emfmodel.get(i);
			org.omg.CORBA.Object rep = (org.omg.CORBA.Object)repmodel.get(i);

			System.out.println("\t" + emf.getClass().getName() + " : ");
			
			try {
				if (emf instanceof ComponentDef)
				{
					MDE.ComponentIDL.ComponentDef componentDef = ComponentDefHelper.narrow(rep);
					
					MDE.CIF.ComponentImplDef[] componentImplDefs = componentDef.segs();
					for (int j=0;j<componentImplDefs.length;j++)
					{
						EObject emfComponentImplDef = rep2emf(componentImplDefs[j]);
						if (emfComponentImplDef != null){
						((ComponentImplDef)emfComponentImplDef).setComponent((ComponentDef)emf);
							//createImplementsRelation((ComponentDef)emf,(ComponentImplDef)emfComponentImplDef);
					  }
					}
			//		MDE.CIF.SegmentDef segmentDef = componentDef.segment();
			//		EObject emfSegmentDef = rep2emf(segmentDef);
//					if (segmentDef != null)
//						createImplementsRelation((ComponentDef)emf,(SegmentDef)segmentDef);
					
					MDE.BaseIDL.InterfaceDef[] interfaceDefs = componentDef.supports_itf();
					for (int j=0;j<interfaceDefs.length;j++)
					{
						EObject emfInterfaceDef = rep2emf(interfaceDefs[j]);
						if (emfInterfaceDef != null)
							((ComponentDef)emf).getComponentSupports_itf().add((InterfaceDef)emfInterfaceDef);
							//createSupportsRelation((ComponentDef)emf,(InterfaceDef)emfInterfaceDef);
					}
					
					MDE.ComponentIDL.HomeDef[] homeDefs = componentDef.home_end();
					for (int j=0;j<homeDefs.length;j++)
					{
						EObject emfHomeDefs = rep2emf(homeDefs[j]);
						if (emfHomeDefs != null)
							((HomeDef)emfHomeDefs).setComponent((ComponentDef)emf);
							//createCompHomeRelation((ComponentDef)emf,(HomeDef)emfHomeDefs);
					}

				}
				else if (emf instanceof HomeDef)
				{
					MDE.ComponentIDL.HomeDef home = HomeDefHelper.narrow(rep);
					//home.component_end();
					MDE.BaseIDL.InterfaceDef[] interfaceDefs = home.supports_itf();
					System.out.println("Updates1");
					for (int j=0;j<interfaceDefs.length;j++)
					{
						EObject emfInterfaceDef = rep2emf(interfaceDefs[j]);
						if (emfInterfaceDef != null)
							((HomeDef)emf).getHomeSupports_itf().add((InterfaceDef)emfInterfaceDef);
							//createSupportsRelation((HomeDef)emf,(InterfaceDef)emfInterfaceDef);
					
						System.out.println("Updates2");
						}
					MDE.CIF.HomeImplDef[] homeImplDefs = home.segs();
					System.out.println("Updates3");
					for (int j=0;j<homeImplDefs.length;j++)
					{
						EObject emfHomeImplDef = rep2emf(homeImplDefs[j]);
						if (emfHomeImplDef != null)
						((HomeImplDef)emfHomeImplDef).setHome((HomeDef)emf);	
							//createImplementsRelation((HomeDef)emf,(HomeImplDef)emfHomeImplDef);
						System.out.println("Updates4");
					}

				}
				else if (emf instanceof ProvidesDef)
				{
					MDE.BaseIDL.InterfaceDef itf = ProvidesDefHelper.narrow(rep).provides_itf();
					EObject emfInterfaceDef = rep2emf(itf);
					if (emfInterfaceDef != null)
						((ProvidesDef)emf).setInterface((InterfaceDef)emfInterfaceDef);
						//createInterfaceRelation((ProvidesDef)emf, (InterfaceDef)emfInterfaceDef);
				}
				else if (emf instanceof UsesDef)
				{
					MDE.BaseIDL.InterfaceDef itf = UsesDefHelper.narrow(rep).uses_itf();
					EObject emfInterfaceDef = rep2emf(itf);
					if (emfInterfaceDef != null)
		//***************************************				
						((UsesDef)emf).setInterface((InterfaceDef)emfInterfaceDef);
						//createInterfaceRelation((UsesDef)emf, (InterfaceDef)emfInterfaceDef);
				}
				else if (emf instanceof HomeImplDef)
				{
					MDE.CIF.ComponentImplDef  componentImplDefs = HomeImplDefHelper.narrow(rep).component_impl();
					EObject emfComponentImplDef = rep2emf(componentImplDefs);
					if (emfComponentImplDef != null)
							((HomeImplDef)emf).setComponentImpl((ComponentImplDef)emfComponentImplDef) ;
					try{
						MDE.CIF.CompositionDef  composition=HomeImplDefHelper.narrow(rep).composition()	;
						EObject emfComposition = rep2emf(composition);
						((HomeImplDef)emf).getComposition().add(emfComposition);
						//createManagersRelation((ComponentImplDef)emf,(HomeImplDef)emfHomeImplDef);
					}catch(Exception e){}
					
				}
				else if (emf instanceof PublishesDef)
				{
					MDE.ComponentIDL.PublishesDef port = PublishesDefHelper.narrow(rep);
					MDE.ComponentIDL.EventDef repType = port.type();
					EObject emfType = rep2emf(repType);
					if (emfType != null)
						((PublishesDef)emf).setEvent((EventDef)emfType);
						//createEventPortEventRelation((EventPortDef)emf,(EventDef)emfType);
				}
				else if (emf instanceof EmitsDef)
				{
					MDE.ComponentIDL.EmitsDef port = EmitsDefHelper.narrow(rep);
					MDE.ComponentIDL.EventDef repType = port.type();
					EObject emfType = rep2emf(repType);
					if (emfType != null)
						((EmitsDef)emf).setEvent((EventDef)emfType);
						//createEventPortEventRelation((EventPortDef)emf,(EventDef)emfType);
				}
				else if (emf instanceof ConsumesDef)
				{
					MDE.ComponentIDL.ConsumesDef port = ConsumesDefHelper.narrow(rep);
					MDE.ComponentIDL.EventDef repType = port.type();
					EObject emfType = rep2emf(repType);
					if (emfType != null)
						((ConsumesDef)emf).setEvent((EventDef)emfType);
						//createEventPortEventRelation((EventPortDef)emf,(EventDef)emfType);
				}

			} catch (MofError e1) { System.out.println("\tcan�t create Relation"); }
			
			if (emf instanceof UnionDef)
			{
				UnionDef emfUnionDef = (UnionDef)emf;
				MDE.BaseIDL.UnionDef repUnionDef = UnionDefHelper.narrow(rep);
				MDE.BaseIDL.IDLType repDiscriminatorType = repUnionDef.discriminator_type();
				try{
					MDE.BaseIDL.TypedefDef typedefDef = TypedefDefHelper.narrow(repDiscriminatorType);
					EObject emfDiscriminatorType = rep2emf(typedefDef);
					if (emfDiscriminatorType != null)
						emfUnionDef.setDiscriminatorType((IDLType)emfDiscriminatorType);
				}catch(Exception e){}
			}
			else if (emf instanceof StreamProtDef)
			{
				StreamProtDef emfStreamPort = (StreamProtDef)emf;
				MDE.ComponentIDL.StreamPortDef repStreamPort = StreamPortDefHelper.narrow(rep);
				MDE.ComponentIDL.MediaType repType = repStreamPort.type();
				EObject emfType = rep2emf(repType);
				if (emfType != null)
					emfStreamPort.setType((MediaType)emfType);
			}
			if (emf instanceof Typed)
			{
				Typed emfTyped = (Typed)emf;
				if (emfTyped.getIDLType() == null) // idltype already set
				{
					MDE.BaseIDL.Typed repTyped = TypedHelper.narrow(rep);
					MDE.BaseIDL.IDLType repIDLType = repTyped.idl_type();
					try{
						MDE.BaseIDL.TypedefDef typedefDef = TypedefDefHelper.narrow(repIDLType);
						EObject emfIDLType = rep2emf(typedefDef);
						if (emfIDLType != null)
							emfTyped.setIDLType((IDLType)emfIDLType);
					}catch(Exception e){}
				}
			}
		}		
	}
	/**
	 * get the right ccmmodel-object that was created from rhe repository-object rep.
	 * @param rep = the repository-object
	 * @return the ccmmodel-object or null if it doesn�t exist
	 */
	private static EObject rep2emf(org.omg.CORBA.Object rep) throws MofError
	{
		if (rep == null) return null;
		int index = ids.indexOf(fullScopeName(rep));
		return (index >= 0) ? (Contained)emfmodel.get(index) : null;
	}
	/**
	 * returns the fullScopeName of the repository-object.
	 * @param rep = the repository-object
	 * @return the fullScopeName
	 */
	private static String fullScopeName(org.omg.CORBA.Object rep) throws MofError
	{
		try 
		{
			MDE.BaseIDL.Contained contained = ContainedHelper.narrow(rep);
			try
			{
				return fullScopeName(contained.defined_in()) + ":" + contained.identifier();
			}
			catch(NotSet e)
			{
				return contained.identifier();
			}
		}
		catch(BAD_PARAM e)
		{
			return ""; // rep is no Contained
		}

	}
}
