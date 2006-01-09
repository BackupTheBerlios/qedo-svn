/**
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 */
package ccm.model;

import java.util.Map;

import org.eclipse.emf.ecore.EPackage;
import org.eclipse.gef.requests.CreationFactory;

import CCMModel.AliasDef;
import CCMModel.Assembly;
import CCMModel.AttributeDef;
import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.ContainedFile;
import CCMModel.DependentFile;
import CCMModel.Deploymentrequirement;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ExceptionDef;
import CCMModel.ExternalInstance;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.IDLFile;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.OperationDef;
import CCMModel.ProcessCollocation;
import CCMModel.Property;
import CCMModel.RegisterComponentInstance;
import CCMModel.Rule;
import CCMModel.SoftwarePackage;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.ValueMemberDef;
import ccm.model.template.RelationTemplate;


/**
 * This class implements the CreationFactory used by the CreationTool. It in turn
 * uses the EMF-generated factories to create the model instances
 * @author eduardw
 *
 */
public class ModelCreationFactory implements CreationFactory {
	private Object template;
	private int relationKind=0;
	
	
	public ModelCreationFactory( Class targetClass ) {
		template = targetClass;
	}
	
	public ModelCreationFactory( Class targetClass,int relationKind ) {
		template = targetClass;
		this.relationKind=relationKind;
	}
	
	/**
	 * @see org.eclipse.gef.requests.CreationFactory#getNewObject()
	 */
	public Object getNewObject() {
		Map registry = EPackage.Registry.INSTANCE;
		String ccmURI = CCMModelPackage.eNS_URI;
		CCMModelPackage ccmPackage =
		(CCMModelPackage) registry.get(ccmURI);
		CCMModelFactory factory = ccmPackage.getCCMModelFactory();
			
		Object		result = null;
			
		if( template.equals( RelationTemplate.class ) ) {
			result = new RelationTemplate(relationKind);
//		}else if( template.equals( ValueDerivedRelation.class ) ) {
//			result = factory.createValueDerivedRelation();
		}else if( template.equals( ModuleDef.class ) ) {
			result = factory.createModuleDef();
		}else if (template.equals(ComponentDef.class)){
			result = factory.createComponentDef();
		}else if (template.equals(InterfaceDef.class)){
			result = factory.createInterfaceDef();
		}else if (template.equals(HomeDef.class)){
			result = factory.createHomeDef();
		}else if (template.equals(OperationDef.class)){
			result = factory.createOperationDef();
		}else if (template.equals(StructDef.class)){
			result = factory.createStructDef();
		}else if (template.equals(EnumDef.class)){
			result = factory.createEnumDef();
		}else if (template.equals(AliasDef.class)){
			result = factory.createAliasDef();
		}else if (template.equals(ValueBoxDef.class)){
			result = factory.createValueBoxDef();
		}else if (template.equals(ConstantDef.class)){
			result = factory.createConstantDef();
		}else if (template.equals(AttributeDef.class)){
			result = factory.createAttributeDef();
		}else if (template.equals(ValueMemberDef.class)){
			result = factory.createValueMemberDef();
		}else if (template.equals(ExceptionDef.class)){
			result = factory.createExceptionDef();
		}else if (template.equals(UnionDef.class)){
			result = factory.createUnionDef();
		}else if (template.equals(ValueDef.class)){
			result = factory.createValueDef();
		}else if (template.equals(EventDef.class)){
			result = factory.createEventDef();
	//*********************************************	
		}else if (template.equals(IDLFile.class)){
			result = factory.createIDLFile();
		}else if (template.equals(Property.class)){
			result = factory.createProperty();
		}else if (template.equals(Rule.class)){
			result = factory.createRule();
		}else if (template.equals(Implementation.class)){
			result = factory.createImplementation();
		}else if (template.equals(SoftwarePackage.class)){
			result = factory.createSoftwarePackage();
		}else if (template.equals(DependentFile.class)){
			result = factory.createDependentFile();
		}else if (template.equals(Deploymentrequirement.class)){
			result = factory.createDeploymentrequirement();
		}else if (template.equals(ContainedFile.class)){
			result = factory.createContainedFile();
		}else if (template.equals(Assembly.class)){
			result = factory.createAssembly();
		}else if (template.equals(RegisterComponentInstance.class)){
			result = factory.createRegisterComponentInstance();
		}else if (template.equals(ProcessCollocation.class)){
			result = factory.createProcessCollocation();
			
		}else if (template.equals(Composition.class)){
			result = factory.createComposition();
		}else if (template.equals(HomeImplDef.class)){
			result = factory.createHomeImplDef();
		}else if (template.equals(HomeInstantiation.class)){
			result = factory.createHomeInstantiation();
		}else if (template.equals(ComponentImplDef.class)){
			result = factory.createComponentImplDef();
		}else if (template.equals(ComponentInstantiation.class)){
			result = factory.createComponentInstantiation();
		}else if (template.equals(ExternalInstance.class)){
			result = factory.createExternalInstance();
		}
		return result;

	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.requests.CreationFactory#getObjectType()
	 */
	public Object getObjectType() {
		return template;
	}
}
