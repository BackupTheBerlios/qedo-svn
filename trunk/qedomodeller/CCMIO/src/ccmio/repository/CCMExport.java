package ccmio.repository;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.eclipse.emf.common.util.EList;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.jface.dialogs.MessageDialog;
import org.omg.CORBA.Object;

import CCMModel.Aktionkind;
import CCMModel.AliasDef;
import CCMModel.ArrayDef;
import CCMModel.Assembly;
import CCMModel.AssemblyConnection;
import CCMModel.AttributeDef;
import CCMModel.CCM;
import CCMModel.ComponentCategory;
import CCMModel.ComponentDef;
import CCMModel.ComponentFile;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.ConnectionEnd;
import CCMModel.ConstantDef;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.ContainedFile;
import CCMModel.Container;
import CCMModel.DependentFile;
import CCMModel.Deploymentrequirement;
import CCMModel.EmitsDef;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ExceptionDef;
import CCMModel.FactoryDef;
import CCMModel.Field;
import CCMModel.FinderDef;
import CCMModel.FixedDef;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.IDLType;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;
import CCMModel.MediaType;
import CCMModel.ModuleDef;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.ParameterMode;
import CCMModel.PrimitiveDef;
import CCMModel.PrimitiveKind;
import CCMModel.ProcessCollocation;
import CCMModel.Property;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.RegisterComponentInstance;
import CCMModel.SegmentDef;
import CCMModel.SequenceDef;
import CCMModel.SiSouDef;
import CCMModel.SinkDef;
import CCMModel.SoftwarePackage;
import CCMModel.SourceDef;
import CCMModel.StreamProtDef;
import CCMModel.StringDef;
import CCMModel.StructDef;
import CCMModel.Typed;
import CCMModel.TypedefDef;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.UsesDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.ValueMemberDef;
import CCMModel.WstringDef;
import CCMModel.impl.DiagramImpl;
import MDE._CCMPackage;
import MDE.BaseIDL.ContainerHelper;
import MDE.BaseIDL.IDLTypeHelper;
import MDE.BaseIDL.InterfaceDefHelper;
import MDE.BaseIDL.TypedHelper;
import MDE.BaseIDL.UnionDefHelper;
import MDE.BaseIDL.ValueDefHelper;
import MDE.BaseIDL._BaseIDLPackage;
import MDE.CIF.ComponentImplDefHelper;
import MDE.CIF.CompositionDef;
import MDE.CIF.CompositionDefHelper;
import MDE.CIF.HomeImplDefHelper;
import MDE.CIF.SegmentDefHelper;
import MDE.CIF._CIFPackage;
import MDE.ComponentIDL.ComponentDefHelper;
import MDE.ComponentIDL.ComponentFeatureHelper;
import MDE.ComponentIDL.ConsumesDefHelper;
import MDE.ComponentIDL.EmitsDefHelper;
import MDE.ComponentIDL.EventDefHelper;
import MDE.ComponentIDL.FactoryDefHelper;
import MDE.ComponentIDL.FinderDefHelper;
import MDE.ComponentIDL.HomeDefHelper;
import MDE.ComponentIDL.MediaTypeHelper;
import MDE.ComponentIDL.ProvidesDefHelper;
import MDE.ComponentIDL.PublishesDefHelper;
import MDE.ComponentIDL.SinkDefHelper;
import MDE.ComponentIDL.SourceDefHelper;
import MDE.ComponentIDL.StreamPortDefHelper;
import MDE.ComponentIDL.UsesDefHelper;
import MDE.ComponentIDL._ComponentIDLPackage;
import MDE.Deployment.ActionKind;
import MDE.Deployment.AssemblyHelper;
import MDE.Deployment.ComponentFileHelper;
import MDE.Deployment.ComponentInstantiationHelper;
import MDE.Deployment.Configuration;
import MDE.Deployment.Connection;
import MDE.Deployment.ConnectionEndHelper;
import MDE.Deployment.ConnectionHelper;
import MDE.Deployment.ContainedFileHelper;
import MDE.Deployment.DependentFileHelper;
import MDE.Deployment.DeploymentRequirementHelper;
import MDE.Deployment.ElementName;
import MDE.Deployment.ExternalInstanceHelper;
import MDE.Deployment.FinderService;
import MDE.Deployment.FinderServiceKind;
import MDE.Deployment.HomeInstantiationHelper;
import MDE.Deployment.IDLFile;
import MDE.Deployment.ImplementationHelper;
import MDE.Deployment.ProcessCollocationHelper;
import MDE.Deployment.PropertyHelper;
import MDE.Deployment._DeploymentPackage;
import MDE.Deployment._SoftwarePackage;
import MDE.Deployment._SoftwarePackageHelper;
import Reflective.MofError;
import org.eclipse.jface.dialogs.MessageDialog;


/**
 *	This Class represents the export from a ccm-model-file to a ccmrepository.
 *	
 *	see export(CCM ccm)
 */
public class CCMExport {

	private _BaseIDLPackage baseIDLPackage;
	private _ComponentIDLPackage componentIDLPackage;
	private _CIFPackage CIFPackage;
	private _DeploymentPackage deploymentPackage;
	private ArrayList 	relations,			// lists of all relations, 
								repmodel, emfmodel;	// objects in repository and emf-model

	/**
	 * This methode add a ccm-model to a repository.
	 * @param repository = the repository to add the model
 	 * @param ccm = the CCM-Object that represents the ccmmodel
 	 * @param name = identifier of the rootModule in the repository
 	 */
	public void exports(CCMRepository repository,CCM ccm) throws MofError
	{
		emfmodel = new ArrayList();
		repmodel = new ArrayList();
		relations = new ArrayList();

		_CCMPackage temp_package;
		// identify the name of Package
		// asuming first Module represents the package name
		CCMModel.ModuleDef package_module = ccm.getModuleDef();
		String package_name = package_module.getIdentifier();

		// creste root ccm package in CCM repositry
		temp_package = (_CCMPackage) repository.create_package(package_name);
		
		// idenfy local vars
		baseIDLPackage = temp_package.base_idl_ref();
		componentIDLPackage = temp_package.component_idl_ref();
		CIFPackage = temp_package.cif_ref();
		deploymentPackage = temp_package.deployment_ref();
		
		// 1. & 2. create the rootModule and its contents
		createRootAndContents(package_module);
		
//		MDE.BaseIDL.Contained[] contents = 
//			createContents(root_module.getContents());

		//
//		MDE.BaseIDL.ModuleDef repRootModule = ModuleDefHelper.narrow(create(package_module));
		// 3. creates relations 
		//System.out.println("Create model in repository.");
		//System.out.println("Create model in repository.");
/*
		for (int i=0;i<contents.length;i++)
		{  
			//System.out.println("contents[i]. "+contents[i]);
			if(contents[i] != null) {
				repRootModule.add_contents(contents[i]);
				contents[i].set_defined_in(repRootModule);
			}
		}
	*/
		
		//createRelations();
		
		// 4. updates the model
		updateRepModel();

	}
	/* --------------------------------- CREATEROOT ------------------------------------------------ */
	/**
	 * This methode creates the Root-Module and its contens in in Repository.
	 * @param rootModule = the root-module of our modell.
 	 */
	
	// not used

	private void createRootAndContents(ModuleDef rootModule) throws MofError
	{
		
   	 	MDE.BaseIDL.ModuleDef repRootModule;
		repRootModule = baseIDLPackage.module_def_ref().create_module_def( rootModule.getIdentifier(), rootModule.getRepositoryId(), rootModule.getVersion(), rootModule.getPrefix());

   	 	repmodel.add(repRootModule);
   	 	emfmodel.add(rootModule);
   	 	
  
   	 	// create the contens of the RootModule
   	 	//System.out.println("Create model in repository.");
		MDE.BaseIDL.Contained[] contents = 
			createContents_fromContainer(rootModule, repRootModule); 

		repRootModule.set_contents(contents);
		
	}
   	 	
	/* --------------------------------- CREATE ------------------------------------------------ */
	/**
	 * This methode creates a List of Contained in Repository.
	 * @param contents = the objects to add to the model
	 * @return the new repository-objects
 	 */
	private MDE.BaseIDL.Contained[] createContents(EList contents) throws MofError
	{	 
		MDE.BaseIDL.Contained[]  repcontents = new MDE.BaseIDL.Contained[contents.size()];
		for (int i=0; i<contents.size(); i++)
		{
			Contained emfContained = (Contained)contents.get(i);
			
			if(emfContained instanceof DiagramImpl){
				repcontents[i]=null;
//				emfContained.getDefinedIn().getContents().remove(emfContained);
//				((Diagram)emfContained).getView().setDiagram(null);
				continue;
			}
			
			repcontents[i] = create(emfContained);
			if (repcontents[i] != null)
			{
				repmodel.add(repcontents[i]);
				emfmodel.add(emfContained);
				
				if (emfContained instanceof Container) 
				{
					// container --> create contents
					MDE.BaseIDL.Container repcontainer = ContainerHelper.narrow(repcontents[i]);
					EList containeds=((Container)emfContained).getContents();
				 
					MDE.BaseIDL.Contained[] cns = createContents(containeds);
					for (int j=0;j<cns.length;j++)
					{
						if(cns[j] != null) {
							repcontainer.add_contents(cns[j]);
							cns[j].set_defined_in(repcontainer);
						}
					}
				}
			} 
			else System.out.println("can´t create: " + emfContained.getIdentifier());
		}
		return repcontents;
	}

	private MDE.BaseIDL.Contained[] createContents_fromContainer(Container emf_container, MDE.BaseIDL.Container rep_container) throws MofError
	{	 
		EList emf_contents = emf_container.getContents();

		// MDE.BaseIDL.Contained[]  repcontents = new MDE.BaseIDL.Contained[emf_contents.size()];
		List repcontents = new ArrayList();
		
		for (int i=0; i<emf_container.getContents().size(); i++)
		{
			Contained emfContained = (Contained)emf_contents.get(i);
			
			if(emfContained instanceof DiagramImpl){
//				repcontents[i]=null;
//				emfContained.getDefinedIn().getContents().remove(emfContained);
//				((Diagram)emfContained).getView().setDiagram(null);
				continue;
			}
			
//			repcontents[i] = create(emfContained);
			MDE.BaseIDL.Contained cont = create(emfContained);
			if (cont != null)
			{
				repmodel.add(cont);
				emfmodel.add(emfContained);
				cont.set_defined_in(rep_container);
				repcontents.add(cont);

			} 
			else 
			{
				System.out.println("can´t create: " + emfContained.getIdentifier());
			}
		}
		MDE.BaseIDL.Contained[] return_cont = new MDE.BaseIDL.Contained[repcontents.size()];
		for (int counter = 0; counter < repcontents.size();counter++)
		{
			return_cont[counter] = (MDE.BaseIDL.Contained)repcontents.get(counter);
		}
		return return_cont;
	}
	
	
	/**
	 * This methode  creates a contained in repository.
	 * @param contained = the object to add to the model
	 * @return the new repository-object
 	 */
	private MDE.BaseIDL.Contained create(Contained contained) throws MofError
	{

		
		MDE.BaseIDL.Contained result;
		//System.out.println("\t" + contained.getClass().getName() + " : " + contained.getIdentifier());
		if (contained instanceof ModuleDef)
		{
			//relations.addAll(((ModuleDef)contained).getRelations());
			MDE.BaseIDL.ModuleDef module = baseIDLPackage.module_def_ref().create_module_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((ModuleDef)contained).getPrefix());
			result = module;
		}
		else if (contained instanceof SoftwarePackage){
			
			IDLFile idlfile=null;
			CCMModel.IDLFile eidlfile=((SoftwarePackage)contained).getIdlFile();
			if(eidlfile!=null){
				idlfile=deploymentPackage.idlfile_ref().create_idlfile(eidlfile.getIdentifier(),
					eidlfile.getRepositoryId(),eidlfile.getVersion(),eidlfile.getName(),eidlfile.getLocation());
				repmodel.add(idlfile);
				emfmodel.add(eidlfile);
			}
			MDE.Deployment._SoftwarePackage softwarePackage=
				deploymentPackage.software_package_ref().create_software_package( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
						((SoftwarePackage)contained).getLicensekey(),((SoftwarePackage)contained).getLicensetextref(),
						((SoftwarePackage)contained).getTitle(),((SoftwarePackage)contained).getType(),
						((SoftwarePackage)contained).getAutor(),idlfile);
			 
			result=softwarePackage;
			//return result;
			
		}
		else if (contained instanceof Implementation){
			result=deploymentPackage.implementation_ref().create_implementation(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((Implementation)contained).getUuid());

			//return result;
			
		}
		else if (contained instanceof ContainedFile){
			result=deploymentPackage.contained_file_ref().create_contained_file(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((ContainedFile)contained).getName(),((ContainedFile)contained).getLocation(),
					((ContainedFile)contained).getCodeType(),((ContainedFile)contained).getEntryPoint(),
					((ContainedFile)contained).getUsage());
			//return result;
			
		}
		else if (contained instanceof DependentFile){
			result=deploymentPackage.dependent_file_ref().create_dependent_file(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((DependentFile)contained).getName(),((DependentFile)contained).getLocation(),
					getActionKind(((DependentFile)contained).getAction()));
			//return result;
			
		}
		else if (contained instanceof Deploymentrequirement){
			result=deploymentPackage.deployment_requirement_ref().create_deployment_requirement(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((Deploymentrequirement)contained).getKind(),((Deploymentrequirement)contained).getReqVersion());
			//return result;
		}
		else if (contained instanceof Assembly){
			Configuration con=deploymentPackage.configuration_ref().create_configuration(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
			MDE.Deployment.Assembly ass=deploymentPackage.assembly_ref().create_assembly(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((Assembly)contained).getUuid());
			ass.set_config(con);
			result=ass;
			//return result;
		}

		else if (contained instanceof ComponentFile)
		{
			result=deploymentPackage.component_file_ref().create_component_file(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((ComponentFile)contained).getName(),((ComponentFile)contained).getLocation());
			return result;
		}
		
		else if (contained instanceof ProcessCollocation)
		{
			result=deploymentPackage.process_collocation_ref().create_process_collocation(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					(int)((ProcessCollocation)contained).getCardinality(),((ProcessCollocation)contained).getDestination());
		}
		
		else if (contained instanceof HomeInstantiation)
		{
			FinderService finderservice=deploymentPackage.finder_service_ref().create_finder_service(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					getServiceKind(((HomeInstantiation)contained).getService()),((HomeInstantiation)contained).getRegName());
			
			result=deploymentPackage.home_instantiation_ref().create_home_instantiation(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((HomeInstantiation)contained).getCardinality(),finderservice);
		}
		
		else if (contained instanceof ComponentInstantiation){
			result=deploymentPackage.component_instantiation_ref().create_component_instantiation(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((ComponentInstantiation)contained).getCardinality(),((ComponentInstantiation)contained).getStartOrder());
		}
		else if (contained instanceof RegisterComponentInstance){
			result=deploymentPackage.register_component_instance_ref().create_register_component_instance(
					contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					getServiceKind(((RegisterComponentInstance)contained).getService()),((RegisterComponentInstance)contained).getRegName());
		}
		else if (contained instanceof Property){
			result=deploymentPackage.property_ref().create_property(
					contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((Property)contained).getValue(),((Property)contained).getType(),
					getElname(((Property)contained).getEl_name()));
		}
		 else if (contained instanceof AssemblyConnection){
		 	result=deploymentPackage.connection_ref().create_connection(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		 }
		 else if (contained instanceof ConnectionEnd){
		 	result=deploymentPackage.connection_end_ref().create_connection_end("","","",
		 			MDE.Deployment.ConnectionEndKind.SIMPLEINTERFACE);
		 }
		 
		 else if (contained instanceof CCMModel.IDLFile){
		 	result=deploymentPackage.idlfile_ref().create_idlfile(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),
					((CCMModel.IDLFile)contained).getName(),((CCMModel.IDLFile)contained).getLocation());
		 }
		
		 else if (contained instanceof CCMModel.Configuration){
		 	result=deploymentPackage.configuration_ref().create_configuration(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		 }
		
		else if (contained instanceof ComponentDef){
				MDE.ComponentIDL.ComponentDef repcomponent = 
					componentIDLPackage.component_def_ref().create_component_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((ComponentDef)contained).isIsAbstract(), ((ComponentDef)contained).isIsLocal());
				
				result =  repcomponent;
			}
		else if (contained instanceof ComponentImplDef)
		{
			MDE.CIF.ComponentImplDef repcomponentimpl = 
				CIFPackage.component_impl_def_ref().create_component_impl_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),	getComponentCategory(((ComponentImplDef)contained).getCategory()));
			MDE.CIF.SegmentDef[] segments = createSegments(((ComponentImplDef)contained).getSegment());
			for (int j=0;j<segments.length;j++) {
				repcomponentimpl.add_segment(segments[j]); segments[j].set_component_impl_end(repcomponentimpl); }
			result =  repcomponentimpl;
		}

		else if (contained instanceof HomeDef) 
		{
				MDE.ComponentIDL.HomeDef rephome =
					componentIDLPackage.home_def_ref().create_home_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((HomeDef)contained).isIsAbstract(), ((HomeDef)contained).isIsLocal());
				MDE.ComponentIDL.FactoryDef[] factorys = createFactorys(((HomeDef)contained).getFactorys());
				for (int j=0;j<factorys.length;j++) {
					rephome.add_factorys(factorys[j]); factorys[j].set_homedef(rephome); }
				MDE.ComponentIDL.FinderDef[] finders = createFinders(((HomeDef)contained).getFinders());
				for (int j=0;j<finders.length;j++) 
				{
					rephome.add_finders(finders[j]);
					finders[j].set_homedef(rephome); 
				}
				result =  rephome;
	    }
		
		else if (contained instanceof Composition) 
		{
			result =  CIFPackage.composition_def_ref().create_composition_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(),getComponentCategory(((Composition)contained).getCategory()));			
		}

		else if (contained instanceof HomeImplDef) 
			result =  CIFPackage.home_impl_def_ref().create_home_impl_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		else if (contained instanceof EventDef) 
			result = componentIDLPackage.event_def_ref().create_event_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((EventDef)contained).isIsAbstract(), ((EventDef)contained).isIsCustom(), ((EventDef)contained).isIsTruncatable());
		else if (contained instanceof ValueDef) 
			result =  baseIDLPackage.value_def_ref().create_value_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((ValueDef)contained).isIsAbstract(), ((ValueDef)contained).isIsCustom(), ((ValueDef)contained).isIsTruncatable());
		else if (contained instanceof InterfaceDef)
			result =  baseIDLPackage.interface_def_ref().create_interface_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((InterfaceDef)contained).isIsAbstract(), ((InterfaceDef)contained).isIsLocal());
		
		else if (contained instanceof AliasDef)
			result =  baseIDLPackage.alias_def_ref().create_alias_def( contained.getIdentifier(), contained.getRepositoryId(),	contained.getVersion());
		else if (contained instanceof AttributeDef)
			result =  baseIDLPackage.attribute_def_ref().create_attribute_def( contained.getIdentifier(), contained.getRepositoryId(),	contained.getVersion(),	((AttributeDef)contained).isIsReadonly());

		else if (contained instanceof ConstantDef)
			result =  baseIDLPackage.constant_def_ref().create_constant_def( contained.getIdentifier(), contained.getRepositoryId(),	contained.getVersion(), ((ConstantDef)contained).getConstValue());
		else if (contained instanceof ConsumesDef)
			result =  componentIDLPackage.consumes_def_ref().create_consumes_def( contained.getIdentifier(), contained.getRepositoryId(),	contained.getVersion());

		else if (contained instanceof EmitsDef)
			result =  componentIDLPackage.emits_def_ref().create_emits_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		else if (contained instanceof EnumDef)
		{	
			String[] members = (String[])((EnumDef)contained).getMembers().toArray();
			result =  baseIDLPackage.enum_def_ref().create_enum_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), members); 
		}
		else if (contained instanceof ExceptionDef)
		{
			MDE.BaseIDL.Field[] repMembers= createFields(((ExceptionDef)contained).getMembers());
			result =  baseIDLPackage.exception_def_ref().create_exception_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((ExceptionDef)contained).getTypeCode(), repMembers); 
		}

		else if (contained instanceof FactoryDef)
		{
			MDE.BaseIDL.ParameterDef[] repParameters = createParameters(((FactoryDef)contained).getParameters());
			result =  componentIDLPackage.factory_def_ref().create_factory_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((FactoryDef)contained).isIsOneway(), repParameters, ((FactoryDef)contained).getContext());
		}
		else if (contained instanceof FinderDef)
		{
			MDE.BaseIDL.ParameterDef[] repParameters = createParameters(((FinderDef)contained).getParameters());
			result =  componentIDLPackage.finder_def_ref().create_finder_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((FinderDef)contained).isIsOneway(), repParameters, ((FinderDef)contained).getContext());
		}
		
		else if (contained instanceof MediaType)
			result =  componentIDLPackage.media_type_ref().create_media_type(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());

		else if (contained instanceof OperationDef)
		{
			MDE.BaseIDL.ParameterDef[] repParameter = createParameters(((OperationDef)contained).getParameters());
			result =  baseIDLPackage.operation_def_ref().create_operation_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((OperationDef)contained).isIsOneway(),	repParameter, ((OperationDef)contained).getContext());
		}
		else if (contained instanceof PublishesDef)
			result =  componentIDLPackage.publishes_def_ref().create_publishes_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		else if (contained instanceof ProvidesDef)
			result =  componentIDLPackage.provides_def_ref().create_provides_def( contained.getIdentifier(),	contained.getRepositoryId(), contained.getVersion());

		else if (contained instanceof SegmentDef)
			result =  CIFPackage.segment_def_ref().create_segment_def( contained.getIdentifier(), contained.getRepositoryId(),	contained.getVersion(), ((SegmentDef)contained).isIsSerialized());
		else if (contained instanceof SinkDef)
			result =  componentIDLPackage.sink_def_ref().create_sink_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		else if (contained instanceof SiSouDef)
			result =  componentIDLPackage.si_sou_def_ref().create_si_sou_def(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		else if (contained instanceof SourceDef)
			result =  componentIDLPackage.source_def_ref().create_source_def(contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion());
		else if (contained instanceof StructDef)
		{	
			MDE.BaseIDL.Field[] repMembers= createFields(((StructDef)contained).getMembers());
			result =  baseIDLPackage.struct_def_ref().create_struct_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), repMembers); 
		}
		
		else if (contained instanceof UnionDef)
		{	
			MDE.BaseIDL.UnionField[] repUnionFields= createUnionFields(((UnionDef)contained).getUnionMembers());
			result =  baseIDLPackage.union_def_ref().create_union_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), repUnionFields); 
		}
		else if (contained instanceof UsesDef)
			result =  componentIDLPackage.uses_def_ref().create_uses_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((UsesDef)contained).isMultipleItf()); 
		
		else if (contained instanceof ValueBoxDef)
			result =  baseIDLPackage.value_box_def_ref().create_value_box_def( contained.getIdentifier(), contained.getRepositoryId(),	contained.getVersion());
		else if (contained instanceof ValueMemberDef)
			result =  baseIDLPackage.value_member_def_ref().create_value_member_def( contained.getIdentifier(), contained.getRepositoryId(), contained.getVersion(), ((ValueMemberDef)contained).isIsPublicMember());
		else 
		{
			result =  null;
		}

/*
		if (contained instanceof Typed && result != null)
		{
			IDLType emfIDLType = ((Typed)contained).getIDLType();
			MDE.BaseIDL.IDLType repIDLType;
			if (emfIDLType != null)
			{
				repIDLType = createIDLType(emfIDLType);
				if (repIDLType != null)
				{
					TypedHelper.narrow(result).set_idl_type(repIDLType);
				}
				else 
				{
					repIDLType = (MDE.BaseIDL.IDLTypeHelper.narrow(create((Contained)emfIDLType))); 
					if (repIDLType != null)
					{
						TypedHelper.narrow(result).set_idl_type(repIDLType);
					}

				}
			}
		}
*/ // this is done in update RepModel

		if (contained instanceof Container)
		{
			MDE.BaseIDL.Container temp_container = MDE.BaseIDL.ContainerHelper.narrow(result);
			MDE.BaseIDL.Contained[] temp_list = createContents_fromContainer((Container)contained, temp_container) ;
			
			temp_container.set_contents(temp_list);
		}

		return result;
	}
	/**
	 * @param action
	 * @return
	 */
	
	/**
	 * This methode creates an IDLType in Repository.
	 * @param emfIDLType = the IDLType to add to the model
	 * @return the new repository-IDLType
 	 */
	private MDE.BaseIDL.IDLType createIDLType(IDLType emfIDLType) throws MofError
	{
		// check if the type already exists
		Object rep_type = emf2rep(emfIDLType);
		if (rep_type != null)
		{
			return MDE.BaseIDL.IDLTypeHelper.narrow(rep_type);
		}

		if (emfIDLType instanceof TypedefDef)
			return (MDE.BaseIDL.IDLType)create((TypedefDef)emfIDLType);

		else if (emfIDLType instanceof ArrayDef)
		{
			MDE.BaseIDL.ArrayDef repArray = baseIDLPackage.array_def_ref().create_array_def((int)((ArrayDef)emfIDLType).getBound());
			emfmodel.add(emfIDLType);
			repmodel.add(repArray);
			IDLType emfIDLType2 = ((Typed)emfIDLType).getIDLType();
			MDE.BaseIDL.IDLType repIDLType2;
			if (emfIDLType2 != null)
				if ((repIDLType2 = createIDLType(emfIDLType2)) != null)
					repArray.set_idl_type(repIDLType2);
			return repArray;
		}

		else if (emfIDLType instanceof SequenceDef)
		{
			MDE.BaseIDL.SequenceDef repSequence = baseIDLPackage.sequence_def_ref().create_sequence_def((int)((SequenceDef)emfIDLType).getBound());
			emfmodel.add(emfIDLType);
			repmodel.add(repSequence);
			IDLType emfIDLType2 = ((Typed)emfIDLType).getIDLType();
			MDE.BaseIDL.IDLType repIDLType2;
			if (emfIDLType2 != null)
				if ((repIDLType2 = createIDLType(emfIDLType2)) != null)
					repSequence.set_idl_type(repIDLType2);
			return repSequence;
		}
		
		else if (emfIDLType instanceof WstringDef)
		{
			return baseIDLPackage.wstring_def_ref().create_wstring_def((int)((WstringDef)emfIDLType).getBound());
		}
		else if (emfIDLType instanceof StringDef)
		{
			return baseIDLPackage.string_def_ref().create_string_def((int)((StringDef)emfIDLType).getBound());
		}
		else if (emfIDLType instanceof FixedDef)
		{
			return baseIDLPackage.fixed_def_ref().create_fixed_def(((FixedDef)emfIDLType).getDigits(),((FixedDef)emfIDLType).getScale());
		}
		
		else if (emfIDLType instanceof PrimitiveDef)
		{
			return baseIDLPackage.primitive_def_ref().create_primitive_def(getPrimitiveKind(((PrimitiveDef)emfIDLType).getKind()));
		}
		
		else if (emfIDLType instanceof AliasDef)
		{
			
			return MDE.BaseIDL.AliasDefHelper.narrow(create((Contained)emfIDLType));
		}
		
		return null;
	}

	/*
	private MDE.ComponentIDL.UsesDef[] createUses(EList uses) throws MofError
	{
		MDE.BaseIDL.Contained[] rep = createContents(uses);
		MDE.ComponentIDL.UsesDef[] result = new MDE.ComponentIDL.UsesDef[rep.length];
		for (int i=0; i<rep.length; i++)
			result[i] = UsesDefHelper.narrow(rep[i]);
		return result;
	}
	*/
	/**
	 * This methode creates a List of segments in Repository.
	 * @param segments = the segments to add to the model
	 * @return the new repository-segments
 	 */
	private MDE.CIF.SegmentDef[] createSegments(EList segments) throws MofError
	{
		MDE.BaseIDL.Contained[] rep = createContents(segments);
		MDE.CIF.SegmentDef[] result = new MDE.CIF.SegmentDef[rep.length];
		for (int i=0; i<rep.length; i++)
			result[i] = SegmentDefHelper.narrow(rep[i]);
		return result;
	}
	/**
	 * This methode creates a List of factorys in Repository.
	 * @param factorys = the factorys to add to the model
	 * @return the new repository-factorys
 	 */
	private MDE.ComponentIDL.FactoryDef[] createFactorys(EList factorys) throws MofError
	{
		MDE.BaseIDL.Contained[] rep = createContents(factorys);
		MDE.ComponentIDL.FactoryDef[] result = new MDE.ComponentIDL.FactoryDef[rep.length];
		for (int i=0; i<rep.length; i++)
			result[i] = FactoryDefHelper.narrow(rep[i]);
		return result;
	}
	/**
	 * This methode creates a List of finders in Repository.
	 * @param finders = the finders to add to the model
	 * @return the new repository-finders
 	 */
	private MDE.ComponentIDL.FinderDef[] createFinders(EList finders) throws MofError
	{
		MDE.BaseIDL.Contained[] rep = createContents(finders);
		MDE.ComponentIDL.FinderDef[] result = new MDE.ComponentIDL.FinderDef[rep.length];
		for (int i=0; i<rep.length; i++)
			result[i] = FinderDefHelper.narrow(rep[i]);
		return result;
	}
	/**
	 * This methode creates a List of parameters in Repository.
	 * @param parameters = the parameters to add to the model
	 * @return the new repository-parameters
 	 */
	private MDE.BaseIDL.ParameterDef[] createParameters(EList parameters) throws MofError
	{
		MDE.BaseIDL.ParameterDef[] repparameter = new MDE.BaseIDL.ParameterDef[parameters.size()];
		for (int i=0;i<parameters.size();i++) 
		{
			ParameterDef parameter = (ParameterDef)parameters.get(i);
			ParameterMode direction = parameter.getDirection();
			repparameter[i] = baseIDLPackage.parameter_def_ref().create_parameter_def( 
					parameter.getIdentifier(),
					(direction == ParameterMode.PARAM_IN_LITERAL) ? MDE.BaseIDL.ParameterMode.PARAM_IN :
					(direction == ParameterMode.PARAM_OUT_LITERAL) ? MDE.BaseIDL.ParameterMode.PARAM_OUT :
					MDE.BaseIDL.ParameterMode.PARAM_INOUT );
			emfmodel.add(parameter);
			repmodel.add(repparameter[i]);

// TODO : check whether this is correct
/*
			IDLType emfIDLType = parameter.getIDLType();
			MDE.BaseIDL.IDLType repIDLType;
			if (emfIDLType != null)
				if ((repIDLType = createIDLType(emfIDLType)) != null)
					repparameter[i].set_idl_type(repIDLType);
*/
		}

		return repparameter;
	}
	/**
	 * This methode creates a List of fields in Repository.
	 * @param fields = the fields to add to the model
	 * @return the new repository-fields
 	 */
	private MDE.BaseIDL.Field[] createFields(EList fields) throws MofError
	{
		MDE.BaseIDL.Field[] repfields = new MDE.BaseIDL.Field[fields.size()];
		for (int i=0;i<fields.size();i++)
		{
			Field field = (Field)fields.get(i);
			repfields[i] = baseIDLPackage.field_ref().create_field(field.getIdentifier());
			IDLType emfIDLType = field.getIDLType();
			MDE.BaseIDL.IDLType repIDLType;
			if (emfIDLType != null)
			{
				repIDLType = MDE.BaseIDL.IDLTypeHelper.narrow(createIDLType(emfIDLType));
				if (repIDLType != null)
				{
					repfields[i].set_idl_type(repIDLType);					
				} 
				else if ((repIDLType = createIDLType(emfIDLType)) != null)
				{
					repfields[i].set_idl_type(repIDLType);
				} 
			}
		}
		return repfields;
	}
	/**
	 * This methode creates a List of unionfields in Repository.
	 * @param unionfields = the unionfields to add to the model
	 * @return the new repository-unionfields
 	 */
	private MDE.BaseIDL.UnionField[] createUnionFields(EList unionfields) throws MofError
	{
		MDE.BaseIDL.UnionField[] repunionfields = new MDE.BaseIDL.UnionField[unionfields.size()];
		for (int i=0;i<unionfields.size();i++)
		{
			UnionField unionField = (UnionField)unionfields.get(i);
			repunionfields[i] = baseIDLPackage.union_field_ref().create_union_field(unionField.getIdentifier(), unionField.getLabel());
			IDLType emfIDLType = unionField.getIDLType();
			MDE.BaseIDL.IDLType repIDLType;
			if (emfIDLType != null)
				if ((repIDLType = createIDLType(emfIDLType)) != null)
				{
					repunionfields[i].set_idl_type(repIDLType);
				}
		}
		return repunionfields;
	}
	/**
	 * This methode converts ccmmodel-ComponentCategory to repository-ComponentCategory.
	 * @param componentCategory = the ccmmodel-componentCategory
	 * @return the repository-componentCategory
 	 */
	private MDE.CIF.ComponentCategory getComponentCategory(ComponentCategory componentCategory) throws MofError
	{
		return 	(componentCategory.getName() == "PROCESS") 	? MDE.CIF.ComponentCategory.PROCESS :
				(componentCategory.getName() == "SESSION") 	? MDE.CIF.ComponentCategory.SESSION :
				(componentCategory.getName() == "ENTITY") 	? MDE.CIF.ComponentCategory.ENTITY :
				(componentCategory.getName() == "SERVICE") 	? MDE.CIF.ComponentCategory.SERVICE :
				MDE.CIF.ComponentCategory.EXTENSION;
	}
	private ActionKind getActionKind(Aktionkind action) {
		return 	(action.getName() == "ASSERT") 	? ActionKind.ASSERT :ActionKind.INSTALL ;
			 
	}
	private FinderServiceKind getServiceKind(CCMModel.FinderServiceKind kind){
		return 	(kind.getName() == "HOMEFINDER") 	? MDE.Deployment.FinderServiceKind.HOMEFINDER :
			(kind.getName() == "NAMING") 	? MDE.Deployment.FinderServiceKind.NAMING :
			(kind.getName() == "TRADING") 	? MDE.Deployment.FinderServiceKind.TRADING :
			MDE.Deployment.FinderServiceKind.UNDEFINED;
	}
	private ElementName getElname(CCMModel.ElementName elname){
		return 	(elname.getName() == "SEQUENCE_EL") 	? ElementName.SEQUENCE_EL :
			(elname.getName() == "SIMPLE_EL") 	? ElementName.SIMPLE_EL :
			(elname.getName() == "STRUCT_EL") 	? ElementName.STRUCT_EL :
			 ElementName.VALUETYPE_EL ;
	}
	/**
	 * This methode converts emf-primitivekind to repository-primitivekind.
	 * @param emfPrimitiveKind = the ccmmodel-PrimitiveKind
	 * @return the repository-PrimitiveKind
 	 */
	private MDE.BaseIDL.PrimitiveKind getPrimitiveKind(PrimitiveKind emfPrimitiveKind) throws MofError
	{
		return 
			(emfPrimitiveKind == PrimitiveKind.PK_BOOLEAN_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_Boolean :
			(emfPrimitiveKind == PrimitiveKind.PK_CHAR_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_CHAR :
			(emfPrimitiveKind == PrimitiveKind.PK_DOUBLE_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_DOUBLE :
			(emfPrimitiveKind == PrimitiveKind.PK_FLOAT_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_FLOAT :
			(emfPrimitiveKind == PrimitiveKind.PK_LONG_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_LONG :
			(emfPrimitiveKind == PrimitiveKind.PK_LONGDOUBLE_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_LONGDOUBLE :
			(emfPrimitiveKind == PrimitiveKind.PK_LONGLONG_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_LONGLONG :
			(emfPrimitiveKind == PrimitiveKind.PK_OBJREF_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_OBJREF :
			(emfPrimitiveKind == PrimitiveKind.PK_OCTET_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_OCTET :
			(emfPrimitiveKind == PrimitiveKind.PK_SHORT_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_SHORT :
			(emfPrimitiveKind == PrimitiveKind.PK_STRING_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_STRING :
			(emfPrimitiveKind == PrimitiveKind.PK_TYPECODE_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_TYPECODE :
			(emfPrimitiveKind == PrimitiveKind.PK_ULONG_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_ULONG :
			(emfPrimitiveKind == PrimitiveKind.PK_ULONGLONG_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_ULONGLONG :
			(emfPrimitiveKind == PrimitiveKind.PK_USHORT_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_USHORT :
			(emfPrimitiveKind == PrimitiveKind.PK_VOID_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_VOID :
			(emfPrimitiveKind == PrimitiveKind.PK_WCHAR_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_WCHAR :
			(emfPrimitiveKind == PrimitiveKind.PK_WSTRING_LITERAL) ? MDE.BaseIDL.PrimitiveKind.PK_WSTRING :
			MDE.BaseIDL.PrimitiveKind.PK_ANY;
	}

	/* --------------------------------- RELATIONS ------------------------------------------------ */
	/**
	 * This methode creates the relations between the model-objects in Repository.
 	 */
//	private static void createRelations() throws MofError
//	{
//		System.out.println("relations : ");
//		for (int i=0; i<relations.size(); i++)
//		{
//			Relation relation = (Relation)relations.get(i);
//			try
//			{
////			if (relation instanceof IpmlementsRelation)
////				createImplementsRelation((IpmlementsRelation)relation);
//			  if (relation instanceof InterfaceRelation)
//				createInterfaceRelation((InterfaceRelation)relation);
//			else if (relation instanceof SupportsRelation)
//				createSupportsRelation((SupportsRelation)relation);
//			else if (relation instanceof ManagersRelation)
//				createManagersRelation((ManagersRelation)relation);
//			else if (relation instanceof CompHomeRelation)
//				createCompHomeRelation((CompHomeRelation)relation);
//			else if (relation instanceof AbstractDerivedRelation)
//				createAbstractDerivedRelation((AbstractDerivedRelation)relation);
//			else if (relation instanceof AbstractItfDerivedRelation)
//				createAbstractItfDerivedRelation((AbstractItfDerivedRelation)relation);
//			else if (relation instanceof ValueDerivedRelation)
//				createValueDerivedRelation((ValueDerivedRelation)relation);
//			else if (relation instanceof EventPortEventRelation)
//				createEventPortEventRelation((EventPortEventRelation)relation);
//			}
//			catch (Exception e){ System.out.println("\tcan´t create Relation"); }
//		}
//	}
//	/**
//	 * This methode creates a abstractDerivedRelation in Repository.
//	 * @param abstractDerivedRelation = the abstractDerivedRelation to add to the model
// 	 */
//	private static void createAbstractDerivedRelation (AbstractDerivedRelation abstractDerivedRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\tabstractDerivedRelation");
//		ValueDef abstractDerived = abstractDerivedRelation.getAbstractDerived();
//		ValueDef abstractBase = abstractDerivedRelation.getAbstractBase();
//
//		if (abstractDerived != null && abstractBase != null)
//		{
//			MDE.BaseIDL.ValueDef repAbstractDerived = ValueDefHelper.narrow(emf2rep(abstractDerived));
//			MDE.BaseIDL.ValueDef repAbstractBase = ValueDefHelper.narrow(emf2rep(abstractBase));
//			if (repAbstractDerived != null && repAbstractBase != null)
//				repAbstractDerived.add_abstract_base(repAbstractBase);
//		}
//	}
//	/**
//	 * This methode creates a abstractItfDerivedRelation in Repository.
//	 * @param abstractItfDerivedRelation = the abstractItfDerivedRelation to add to the model
// 	 */
//	private static void createAbstractItfDerivedRelation (AbstractItfDerivedRelation abstractItfDerivedRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\tabstractItfDerivedRelation");
//		AbstractInterfaceDef derived = abstractItfDerivedRelation.getDerived();
//		AbstractInterfaceDef base = abstractItfDerivedRelation.getBase();
//
//		if (derived != null && base != null)
//		{
//			MDE.BaseIDL.InterfaceDef repDerived = InterfaceDefHelper.narrow(emf2rep(derived));
//			MDE.BaseIDL.InterfaceDef repBase = InterfaceDefHelper.narrow(emf2rep(base));
//			if (repDerived != null && repBase != null)
//				repDerived.add_base(repBase);
//		}
//	}
//	/**
//	 * This methode creates a valueDerivedRelation in Repository.
//	 * @param valueDerivedRelation = the valueDerivedRelation to add to the model
// 	 */
//	private static void createValueDerivedRelation (ValueDerivedRelation valueDerivedRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\tvalueDerivedRelation");
//		ValueDef derived = valueDerivedRelation.getDerived();
//		ValueDef base = valueDerivedRelation.getBase();
//
//		if (derived != null && base != null)
//		{
//			MDE.BaseIDL.ValueDef repDerived = ValueDefHelper.narrow(emf2rep(derived));
//			MDE.BaseIDL.ValueDef repBase = ValueDefHelper.narrow(emf2rep(base));
//			if (repDerived != null && repBase != null)
//				repDerived.add_abstract_base(repBase);
//		}
//	}
	/**
	 * This methode creates a ipmlementsRelation in Repository.
	 * @param ipmlementsRelation = the ipmlementsRelation to add to the model
 	 */
//	private static void createImplementsRelation (IpmlementsRelation ipmlementsRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\timplementsRelation");
//		ComponentDef componentend = ipmlementsRelation.getComponentEnd();
//		HomeDef homeend = ipmlementsRelation.getHomeEnd();
//		SegmentDef segment = ipmlementsRelation.getSegment();
//		ComponentImplDef segsC = ipmlementsRelation.getSegsC();
//		HomeImplDef segsH = ipmlementsRelation.getSegsH();
//
//		if (componentend != null)
//		{
//			MDE.ComponentIDL.ComponentDef repComponentEnd =	(ComponentDefHelper.narrow(emf2rep(componentend)));
//			if (segsC != null) 
//				repComponentEnd.add_segs(ComponentImplDefHelper.narrow(emf2rep(segsC)));
//			if (segment != null) 
//				repComponentEnd.set_segment(SegmentDefHelper.narrow(emf2rep(segment)));
//		}
//		if (homeend != null && segsH != null)
//		{
//			MDE.ComponentIDL.HomeDef repHomeEnd = (HomeDefHelper.narrow(emf2rep(homeend)));
//			if (repHomeEnd != null)
//				repHomeEnd.add_segs(HomeImplDefHelper.narrow(emf2rep(segsH)));
//		}
//	}
	/**
	 * This methode creates a interfaceRelation in Repository.
	 * @param interfaceRelation = the interfaceRelation to add to the model
 	 */
//	private static void createInterfaceRelation (InterfaceRelation interfaceRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\tInterfaceRelation");
//		InterfaceDef itf = interfaceRelation.getItf();
//		ProvidesDef providesDefs = interfaceRelation.getProvidesDef();
//		UsesDef usesDefs = interfaceRelation.getUsesDef();
//
//		/*if (itf != null)
//		{
//			MDE.BaseIDL.InterfaceDef repItf = InterfaceDefHelper.narrow(emf2rep(itf));
//
//			if (repItf !=  null)
//			{
//				for (int i=0;i<providesDefs.size();i++)
//				{
//					MDE.ComponentIDL.ProvidesDef repProvidesDef = 
//						(ProvidesDefHelper.narrow(emf2rep((EObject)providesDefs.get(i))));
//					if (repProvidesDef != null)
//						repProvidesDef.set_provides_itf(repItf);
//				}
//				for (int i=0;i<usesDefs.size();i++)
//				{
//					MDE.ComponentIDL.UsesDef repUsesDef = 
//						(UsesDefHelper.narrow(emf2rep((EObject)usesDefs.get(i))));
//					if (repUsesDef != null)
//						repUsesDef.set_uses_itf(repItf);
//				}
//			}
//		}*/
//		MDE.BaseIDL.InterfaceDef repItf = InterfaceDefHelper.narrow(emf2rep(itf));
//		
//		MDE.ComponentIDL.ProvidesDef repProvidesDef = 
//			(ProvidesDefHelper.narrow(emf2rep((EObject)providesDefs)));
//		if (repProvidesDef != null)
//			repProvidesDef.set_provides_itf(repItf);
//		
//		MDE.ComponentIDL.UsesDef repUsesDef = 
//			(UsesDefHelper.narrow(emf2rep((EObject)usesDefs)));
//		if (repUsesDef != null)
//			repUsesDef.set_uses_itf(repItf);
//	}
//	/**
//	 * This methode creates a supportsRelation in Repository.
//	 * @param supportsRelation = the supportsRelation to add to the model
// 	 */
//	private static void createSupportsRelation (SupportsRelation supportsRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\tSupportsRelation");
//		HomeDef home = supportsRelation.getHomes();
//		ComponentDef component = supportsRelation.getComponents();
//		InterfaceDef itf = supportsRelation.getSupportsItf();
//
//		if (home != null && itf != null) 
//		{
//			MDE.ComponentIDL.HomeDef repHome = (HomeDefHelper.narrow(emf2rep(home)));
//			if (repHome != null)
//				repHome.add_supports_itf(InterfaceDefHelper.narrow(emf2rep(itf)));
//		}
//		if (component != null && itf != null)
//		{
//			MDE.ComponentIDL.ComponentDef repComponent = (ComponentDefHelper.narrow(emf2rep(component)));
//			if (repComponent != null)
//				repComponent.add_supports_itf(InterfaceDefHelper.narrow(emf2rep(itf)));
//		}
//	}
//	/**
//	 * This methode creates a managersRelation in Repository.
//	 * @param managersRelation = the managersRelation to add to the model
// 	 */
//	private static void createManagersRelation (ManagersRelation managersRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\tManagersRelation");
//		ComponentImplDef componentimpl = managersRelation.getComponent_impl();
//		HomeImplDef homeimpl = managersRelation.getHome_impl();
//
//		if (componentimpl != null && homeimpl != null)
//		{
//			MDE.CIF.ComponentImplDef repComponentImpl = ComponentImplDefHelper.narrow(emf2rep(componentimpl));
//			MDE.CIF.HomeImplDef repHomeImpl = HomeImplDefHelper.narrow(emf2rep(homeimpl));
//			if (repComponentImpl != null && repHomeImpl != null)
//			{
//				repComponentImpl.add_home_impl(repHomeImpl);
//				repHomeImpl.set_component_impl(repComponentImpl);
//			}
//		}
//	}
//	/**
//	 * This methode creates a compHomeRelation in Repository.
//	 * @param compHomeRelation = the compHomeRelation to add to the model
// 	 */
//	private static void createCompHomeRelation (CompHomeRelation compHomeRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\tCompHomeRelation");
//		ComponentDef component = compHomeRelation.getComponentEnd();
//		HomeDef home = compHomeRelation.getHomeEnd();
//
//		if (component != null && home != null)
//		{
//			MDE.ComponentIDL.ComponentDef repComponent = ComponentDefHelper.narrow(emf2rep(component));
//			MDE.ComponentIDL.HomeDef repHome = HomeDefHelper.narrow(emf2rep(home));
//			if (repComponent != null && repHome != null)
//			{
//				repComponent.add_home_end(repHome);
//				repHome.set_component_end(repComponent);
//			}
//		}
//	}
//	/**
//	 * This methode creates a eventPortEventRelation in Repository.
//	 * @param eventPortEventRelation = the eventPortEventRelation to add to the model
// 	 */
//	private static void createEventPortEventRelation (EventPortEventRelation eventPortEventRelation) 
//	throws MofError,BAD_PARAM
//	{
//		System.out.println("\teventPortEventRelation");
//		EventPortDef eventPortDef = eventPortEventRelation.getEnds();
//		EventDef eventDef = eventPortEventRelation.getType();
//
//		if (eventPortDef != null && eventDef != null)
//		{
//			MDE.ComponentIDL.EventPortDef repEventPortDef = EventPortDefHelper.narrow(emf2rep(eventPortDef));
//			MDE.ComponentIDL.EventDef repEventDef = EventDefHelper.narrow(emf2rep(eventDef));
//			if (repEventPortDef != null && repEventDef != null)
//				repEventPortDef.set_type(repEventDef);
//		}
//	}

	/* --------------------------------- UPADTE ------------------------------------------------ */
	/**
	 * This methode updates all missing properties in the Repository.
 	 */
	private void updateRepModel() throws MofError
	{
		//System.out.println("Updates");
		Iterator it;
		List eObjs;
		for (int i=0; i<emfmodel.size();i++)
		{
			EObject emf = (EObject)emfmodel.get(i);
			org.omg.CORBA.Object rep = (org.omg.CORBA.Object)repmodel.get(i);
/*
			if (emf instanceof ModuleDef)
			{
				// set defined_in attribute
				ModuleDef emf_module = (ModuleDef)emf;
				MDE.BaseIDL.ModuleDef rep_module = ModuleDefHelper.narrow(rep);
				
				try {
					rep_module.set_defined_in(ContainerHelper.narrow(emf2rep(emf_module.getDefinedIn())));
				} catch (Exception e)
				{
					System.out.println("found a module with a missing defined in link, which should occur exaclty one time");
				}
			}
*/ // This is replace by createContents from container method
			
			if (emf instanceof HomeDef)
			{
				HomeDef eHome=(HomeDef)emf;
				MDE.ComponentIDL.HomeDef repHome = HomeDefHelper.narrow(rep);
				
				eObjs=eHome.getHomeSupports_itf();
				for (it=eObjs.iterator();it.hasNext();)
				{
					repHome.add_supports_itf(InterfaceDefHelper.narrow(emf2rep(it.next())));
				}
				
				ComponentDef ecomponent= eHome.getComponent();
				if(ecomponent!=null)
				{
					MDE.ComponentIDL.ComponentDef component= ComponentDefHelper.narrow(emf2rep(ecomponent));
					repHome.set_component_end(component);	
					component.add_home_end(repHome);
				}
			}
			
			else if (emf instanceof SoftwarePackage)
			{
				SoftwarePackage epkg=(SoftwarePackage)emf;
			    _SoftwarePackage pkg=_SoftwarePackageHelper.narrow(rep);
			    ComponentDef ecomp=epkg.getComponent();
			    if(ecomp!=null){
			    	MDE.ComponentIDL.ComponentDef component= ComponentDefHelper.narrow(emf2rep(ecomp));
			    	pkg.set_realized_c(component);
			    }
			    eObjs= epkg.getComponentFiles();
			  //  for (it=eObjs.iterator();it.hasNext();)
			//		pkg.set.add_supports_itf(InterfaceDefHelper.narrow(emf2rep(it.next())));
			    eObjs=epkg.getImpl();
			   // eObjs=epkg.getAssembly();
			    for (it=eObjs.iterator();it.hasNext();)
			    {
			    	Implementation eimpl=(Implementation)it.next();
			    	MDE.Deployment.Implementation impl=MDE.Deployment.ImplementationHelper.narrow(emf2rep(eimpl));
					pkg.add_impls(impl);
					Composition ecomposition=eimpl.getComposition();
					if(ecomposition!=null){
						CompositionDef compo= CompositionDefHelper.narrow(emf2rep(ecomposition));
						impl.set_compos(compo);
						}
					//eimpl.getHomeinstance();
					//impl.s
					List objs=eimpl.getContainedFile();
					for (Iterator oit=objs.iterator();oit.hasNext();)
					{
						impl.add_contained_file(ContainedFileHelper.narrow(emf2rep(oit.next())));
					}
					objs=eimpl.getDependentFiles();
					
					for (Iterator oit=objs.iterator();oit.hasNext();)
					{
						impl.add_dependent_file(DependentFileHelper.narrow(emf2rep(oit.next())));
					}
					objs=eimpl.getRequirment();
					
					for (Iterator oit=objs.iterator();oit.hasNext();)
					{
						impl.add_req(DeploymentRequirementHelper.narrow(emf2rep(oit.next())));
					}
					objs=eimpl.getPropertys();
					for (Iterator oit=objs.iterator();oit.hasNext();)
					{
						impl.add_prop(PropertyHelper.narrow(emf2rep(oit.next())));
					}
			    }
			}
			else if (emf instanceof Assembly)
			{
				Assembly eass= (Assembly)emf;
				MDE.Deployment.Assembly ass=AssemblyHelper.narrow(rep);
				try{
					Configuration con= ass.config();
					eObjs=eass.getConfig().getComponentFile();
					for (it=eObjs.iterator();it.hasNext();)
					{
						ComponentFile file=(ComponentFile)it.next();
						MDE.Deployment.ComponentFile efile=ComponentFileHelper.narrow(emf2rep(file));
						if(file.getPackage()!=null){
							efile.set_pack(MDE.Deployment._SoftwarePackageHelper.narrow(emf2rep(file.getPackage())));
						}
						con.add_install_dest(efile) ;
					}
					eObjs=eass.getSoftwarePackage();
					for (it=eObjs.iterator();it.hasNext();)
					{
						ass.add_files(MDE.Deployment._SoftwarePackageHelper.narrow(emf2rep(it.next())));
					}
					eObjs=eass.getConfig().getConnection();
					for (it=eObjs.iterator();it.hasNext();)
					{
						 AssemblyConnection econnection=(AssemblyConnection)it.next();
						 Connection connection = ConnectionHelper.narrow(emf2rep(econnection));
						 con.add_conn(connection);
						 ConnectionEnd esource= econnection.getSource();
						 MDE.Deployment.ConnectionEnd source=ConnectionEndHelper.narrow(emf2rep(esource));
						 CCMModel.CCMInstantiation sourceInstance=esource.getInstance();
						 if(sourceInstance instanceof ComponentInstantiation)
						 {
						 	source.set_int_comp_inst(ComponentInstantiationHelper.narrow(emf2rep(sourceInstance)));
						 }
						 if(sourceInstance instanceof HomeInstantiation)
						 {
						 	source.set_int_home_inst(MDE.Deployment.HomeInstantiationHelper.narrow(emf2rep(sourceInstance)));
						 }
						 if(sourceInstance instanceof CCMModel.ExternalInstance)
						 {
						 	source.set_ext_inst(ExternalInstanceHelper.narrow(emf2rep(sourceInstance)));
						 }
						 if(esource.getFeature()!=null)
						 {
						 	source.set_thefeature(ComponentFeatureHelper.narrow(emf2rep(esource.getFeature())));
						 }
						 ConnectionEnd etarget= econnection.getTarget();
						 MDE.Deployment.ConnectionEnd target=ConnectionEndHelper.narrow(emf2rep(etarget));
						 CCMModel.CCMInstantiation targetInstance=etarget.getInstance();
						 if(targetInstance instanceof ComponentInstantiation){
						 	target.set_int_comp_inst(ComponentInstantiationHelper.narrow(emf2rep(targetInstance)));
						 }
						 if(targetInstance instanceof HomeInstantiation){
						 	target.set_int_home_inst(MDE.Deployment.HomeInstantiationHelper.narrow(emf2rep(targetInstance)));
						 }
						 if(targetInstance instanceof CCMModel.ExternalInstance){
						 	target.set_ext_inst(ExternalInstanceHelper.narrow(emf2rep(targetInstance)));
						 }
						 if(etarget.getFeature()!=null)
						 	target.set_thefeature(ComponentFeatureHelper.narrow(emf2rep(etarget.getFeature())));
						 connection.set_source_end(source);
						 connection.set_target_end(target);
						 
						 
					}
				
				
					eObjs=eass.getConfig().getProcessCollocation();
					for (it=eObjs.iterator();it.hasNext();){
						ProcessCollocation eProcess=(ProcessCollocation)it.next();
						MDE.Deployment.ProcessCollocation process=ProcessCollocationHelper.narrow(emf2rep(eProcess));
						con.add_coloc(process);
						List ehomeInstances=eProcess.getHomeInstances();
						for (Iterator hit=ehomeInstances.iterator();hit.hasNext();){
							HomeInstantiation ehomeInstance=(HomeInstantiation)hit.next();
							MDE.Deployment.HomeInstantiation homeInstance=HomeInstantiationHelper.narrow(emf2rep(ehomeInstance));
							process.add_thehome(homeInstance);
							if(ehomeInstance.getType()!=null)
								homeInstance.set_type(HomeImplDefHelper.narrow(emf2rep(ehomeInstance.getType())));
							if(ehomeInstance.getDeploymentUnit()!=null)
								homeInstance.set_unit(ImplementationHelper.narrow(emf2rep(ehomeInstance.getDeploymentUnit())));
							List objs=ehomeInstance.getPropertys();
							for (Iterator pit=objs.iterator();pit.hasNext();){
								homeInstance.add_prop(PropertyHelper.narrow(emf2rep(pit.next())));
							}
							objs=ehomeInstance.getComp();
							for (Iterator pit=objs.iterator();pit.hasNext();){
								ComponentInstantiation ecompInstance=(ComponentInstantiation)pit.next();
								MDE.Deployment.ComponentInstantiation compInstance=ComponentInstantiationHelper.narrow(emf2rep(ecompInstance));
								homeInstance.add_comp(compInstance);
								if(ecompInstance.getType()!=null)
									compInstance.set_type(ComponentImplDefHelper.narrow(emf2rep(ecompInstance.getType())));
								
								List list=ecompInstance.getPropertys();
								for (Iterator cit=list.iterator();cit.hasNext();)
								  compInstance.add_prop(PropertyHelper.narrow(emf2rep(cit.next())));
								list=ecompInstance.getRegistration();
								for (Iterator cit=list.iterator();cit.hasNext();){
									RegisterComponentInstance eregister=(RegisterComponentInstance)cit.next();
									MDE.Deployment.RegisterComponentInstance register=MDE.Deployment.RegisterComponentInstanceHelper.narrow(emf2rep(eregister));
									compInstance.add_registration(register);
									if(eregister.getFeature()!=null)
										register.set_thefeature(ComponentFeatureHelper.narrow(emf2rep(eregister.getFeature())));
								}
							}
						}	
					}	
				}
				catch (Exception e){}
			}
			
			else if (emf instanceof ComponentDef){
				ComponentDef econponent=(ComponentDef)emf;
				MDE.ComponentIDL.ComponentDef component=ComponentDefHelper.narrow(rep);
				eObjs=econponent.getComponentSupports_itf();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_supports_itf(InterfaceDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getFacet();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_facet(ProvidesDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getReceptacle();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_receptacle(UsesDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getPublishesDef();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_publishess(PublishesDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getEmitss();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_emitss(EmitsDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getConsumess();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_consumess(ConsumesDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getSinkss();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_sinkss(SinkDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getSiSouss();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_sisouss(MDE.ComponentIDL.SiSouDefHelper.narrow(emf2rep(it.next())));
				eObjs=econponent.getSourcess();
				for (it=eObjs.iterator();it.hasNext();)
					component.add_sourcess(SourceDefHelper.narrow(emf2rep(it.next())));
				
				
			}else if (emf instanceof ValueDef){
				ValueDef evalue=(ValueDef)emf;
				MDE.BaseIDL.ValueDef  value = ValueDefHelper.narrow(rep);
				eObjs=evalue.getAbstractBaseValue();
				for (it=eObjs.iterator();it.hasNext();)
					value.add_abstract_base(ValueDefHelper.narrow(emf2rep(it.next())));
				eObjs=evalue.getValueSupports_itf();
				for (it=eObjs.iterator();it.hasNext();)
//*********************************************************					
					value.set_interface_def(InterfaceDefHelper.narrow(emf2rep(it.next())));
				ValueDef ebase=evalue.getBasevalue();
				if(ebase!=null)
					value.set_base(ValueDefHelper.narrow(emf2rep(ebase)));
			}else if (emf instanceof ProvidesDef){
				ProvidesDef efacet=(ProvidesDef)emf;
				InterfaceDef einterface=efacet.getInterface();
				
				if(einterface!=null){
				MDE.ComponentIDL.ProvidesDef facet=ProvidesDefHelper.narrow(rep);
				facet.set_provides_itf(InterfaceDefHelper.narrow(emf2rep(einterface)));
				}
				
			}else if (emf instanceof UsesDef){	
				UsesDef ereceptacle=(UsesDef)emf;
				InterfaceDef einterface=ereceptacle.getInterface();
				if(einterface!=null){
				MDE.ComponentIDL.UsesDef receptacle=UsesDefHelper.narrow(rep);
				receptacle.set_uses_itf(InterfaceDefHelper.narrow(emf2rep(einterface)));
				}
				 
				//MDE.ComponentIDL
			}else if (emf instanceof ConsumesDef){
				ConsumesDef efacet=(ConsumesDef)emf;
				EventDef eevent=efacet.getEvent();
				
				if(eevent!=null){
					MDE.ComponentIDL.ConsumesDef facet=ConsumesDefHelper.narrow(rep);
					facet.set_type(EventDefHelper.narrow(emf2rep(eevent)));
				}
				//MDE.ComponentIDL
			}else if (emf instanceof PublishesDef){	
				PublishesDef efacet=(PublishesDef)emf;
				EventDef eevent=efacet.getEvent();
				
				if(eevent!=null){
					MDE.ComponentIDL.PublishesDef facet=PublishesDefHelper.narrow(rep);
					facet.set_type(EventDefHelper.narrow(emf2rep(eevent)));
				}
				//MDE.ComponentIDL
			}else if (emf instanceof EmitsDef){
				EmitsDef efacet=(EmitsDef)emf;
				EventDef eevent=efacet.getEvent();
				
				if(eevent!=null){
					MDE.ComponentIDL.EmitsDef facet=EmitsDefHelper.narrow(rep);
					MDE.ComponentIDL.EventDef event=EventDefHelper.narrow(emf2rep(eevent));
					facet.set_type(event);
//***************************
					//event.s
				}
				 
			}else if (emf instanceof InterfaceDef){
				InterfaceDef ereceptacle=(InterfaceDef)emf;
				eObjs=ereceptacle.getBaseInterface();
				MDE.BaseIDL.InterfaceDef receptacle=InterfaceDefHelper.narrow(rep);
				for (it=eObjs.iterator();it.hasNext();){
					MDE.BaseIDL.InterfaceDef itf=InterfaceDefHelper.narrow(emf2rep(it.next()));
//************************************************					
					receptacle.add_base(itf);
				//	itf.s.add_base(receptacle);
				}
				 
				//MDE.BaseIDL
			}else if (emf instanceof ComponentImplDef){
				ComponentImplDef efacet=(ComponentImplDef)emf;
				ComponentDef eevent=efacet.getComponent();
				
				if(eevent!=null){
					MDE.CIF.ComponentImplDef facet=ComponentImplDefHelper.narrow(rep);
					MDE.ComponentIDL.ComponentDef component=ComponentDefHelper.narrow(emf2rep(eevent));
					facet.set_component_end(component);
					component.add_segs(facet);
				}
				
				//MDE.CIF
			}else if (emf instanceof HomeImplDef){	
				HomeImplDef efacet=(HomeImplDef)emf;
				HomeDef eevent=efacet.getHome();
				MDE.CIF.HomeImplDef facet=HomeImplDefHelper.narrow(rep);
				if(eevent!=null){
					MDE.ComponentIDL.HomeDef home=HomeDefHelper.narrow(emf2rep(eevent));
					facet.set_home_end(home);
					home.add_segs(facet);
				}
				ComponentImplDef ecomponentImpl=efacet.getComponentImpl();
				if(ecomponentImpl!=null){
					MDE.CIF.ComponentImplDef componentImpl=ComponentImplDefHelper.narrow(emf2rep(ecomponentImpl));
					facet.set_component_impl(componentImpl);
					componentImpl.add_home_impl(facet);
				}
				//MDE.BaseIDL
			}else if (emf instanceof Composition){
				Composition efacet=(Composition)emf;
				HomeImplDef eevent=efacet.getHomeImpl();
				CompositionDef facet=CompositionDefHelper.narrow(rep);
				if(eevent!=null){
					MDE.CIF.HomeImplDef homeImpl=HomeImplDefHelper.narrow(emf2rep(eevent));
					facet.set_home_executor(homeImpl);
					homeImpl.set_composition(facet);
				}
				//MDE.BaseIDL
			 
			}else if (emf instanceof UnionDef)
			{
				UnionDef emfUnionDef = (UnionDef)emf;
				MDE.BaseIDL.UnionDef repUnionDef = UnionDefHelper.narrow(rep);
				org.omg.CORBA.Object  repDiscriminatorType = createIDLType(emfUnionDef.getDiscriminatorType());
				if (repDiscriminatorType != null)
				{
					repUnionDef.set_discriminator_type(IDLTypeHelper.narrow(repDiscriminatorType));
					//System.out.println("\t" + emfUnionDef.getIdentifier());
				}
			}else if (emf instanceof AliasDef)
			{
				AliasDef emfAliasDef = (AliasDef)emf;
				MDE.BaseIDL.AliasDef repAliasDef = MDE.BaseIDL.AliasDefHelper.narrow(rep);
				org.omg.CORBA.Object  alias_type = createIDLType(emfAliasDef.getIDLType());
				if (alias_type != null)
				{
					repAliasDef.set_idl_type(IDLTypeHelper.narrow(alias_type));
					//System.out.println("\t" + emfUnionDef.getIdentifier());
				} else
				{
					repAliasDef.set_idl_type(createIDLType(emfAliasDef.getIDLType()));
				}
			}
			else if (emf instanceof StreamProtDef)
			{
				StreamProtDef emfStreamPort = (StreamProtDef)emf;
				MDE.ComponentIDL.StreamPortDef repStreamPort = StreamPortDefHelper.narrow(emf2rep(emf));
				org.omg.CORBA.Object repMediaType = emf2rep(emfStreamPort.getType());
				if (repMediaType != null)
				{
					repStreamPort.set_type(MediaTypeHelper.narrow(repMediaType));
					//System.out.println("\t" + emfStreamPort.getIdentifier());
				}
			}
			if (emf instanceof Typed)
			{
				Typed emfTyped = (Typed)emf;
				MDE.BaseIDL.Typed repTyped = TypedHelper.narrow(rep);
				IDLType emfIDLType = emfTyped.getIDLType();
				org.omg.CORBA.Object repIDLType = emf2rep(emfIDLType);
				MDE.BaseIDL.IDLType temp_type; 
				if (repIDLType != null)
				{
					temp_type = IDLTypeHelper.narrow(repIDLType);
					repTyped.set_idl_type(temp_type);
					//if (emf instanceof Contained)
					//	System.out.println("\t" + ((Contained)emf).getIdentifier());
				} else
				{
					if ((temp_type = createIDLType(emfIDLType)) != null)
					{
						repTyped.set_idl_type(temp_type);
					}
				}
			}
		}		
	}
	/**
	 * This methode get the repository-object that is equal the ccmmodel-object.
	 * @param emf = the objects to search for
	 * @return the repository-object
 	 */
	private org.omg.CORBA.Object emf2rep(java.lang.Object emf) throws MofError
	{
		int index = emfmodel.indexOf(emf);
		return (index >= 0) ? (org.omg.CORBA.Object)repmodel.get(index) : null;
	}

}