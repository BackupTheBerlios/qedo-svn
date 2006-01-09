/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss

 * 
 */
package ccm.edit;


import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPartFactory;

import CCMModel.AliasDef;
import CCMModel.Assembly;
import CCMModel.AttributeDef;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.Connection;
import CCMModel.ConnectionDiscription;
import CCMModel.ConstantDef;
import CCMModel.ConsumesDef;
import CCMModel.ContainedFile;
import CCMModel.DependentFile;
import CCMModel.Deploymentrequirement;
import CCMModel.EmitsDef;
import CCMModel.EnumDef;
import CCMModel.ExceptionDef;
import CCMModel.ExternalInstance;
import CCMModel.Field;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.ProcessCollocation;
import CCMModel.Property;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.RegisterComponentInstance;
import CCMModel.Rule;
import CCMModel.SoftwarePackage;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.UsesDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.ValueMemberDef;
import CCMModel.View;
import CCMModel.impl.DiagramImpl;


public class GraphicalEditPartsFactory implements EditPartFactory{

	
    /**
     * @see org.eclipse.gef.EditPartFactory#createEditPart(org.eclipse.gef.EditPart, java.lang.Object)
     */
    public GraphicalEditPartsFactory(){
    	super();
    }
    
    public EditPart createEditPart(EditPart context, Object obj){
    	//************************************
    	if(obj instanceof Integer)
    		return new StartPageEditPart((Integer)obj);
    	//************************************
		if(obj instanceof View)
			return new ViewEditPart((View)obj);
		else if(obj instanceof Connection)
		    return new DerivedRelationEditPart((Connection)obj);
		else if(obj instanceof ConnectionDiscription)
		    return new ConnectionDescriptionEditPart((ConnectionDiscription) obj);
		else if(obj instanceof DiagramImpl)
			return new DiagramEditPart(obj);
		else  if(obj instanceof Node){
			Node node=(Node) obj;
			if(node.getTyped()!=null){
			   if(node.getTyped() instanceof ParameterDef){
					return new ParameterDefNodeEditPart(node);
			    }else if(node.getTyped() instanceof Field){
			    	return  new FieldNodeEditPart(node);
				}else if(node.getTyped() instanceof UnionField){
			    	return  new UnionFieldNodeEditPart(node);
				}else return new PortLabelEditPart(node);
			}else if(node.getIdl()!=null){
			    return new PrimitiveDefNodeEditPart(node);
			}else if(node.getContained() instanceof OperationDef){
				return new OperationDefNodeEditPart(node);
			}else if(node.getContained() instanceof ModuleDef){
		    	return  new ModuleDefNodeEditPart(node);
			}else if(node.getContained() instanceof HomeDef){
		    	return  new HomeDefNodeEditPart(node);
			}else if(node.getContained() instanceof InterfaceDef){
		    	return  new InterfaceDefNodeEditPart(node);
			}else if(node.getContained() instanceof ComponentDef){
		    	return  new ComponentDefNodeEditPart(node);
			}else if(node.getContained() instanceof EnumDef){
		    	return  new EnumNodeEditPart(node);
			}else if(node.getContained() instanceof ValueBoxDef){
		    	return  new ValueBoxDefNodeEditPart(node);
			}else if(node.getContained() instanceof AliasDef){
		    	return  new AliasDefNodeEditPart(node);
			}else if(node.getContained() instanceof ConstantDef){
		    	return  new ConstantDefNodeEditPart(node);
			}else if(node.getContained() instanceof AttributeDef){
		    	return  new AttributeDefNodeEditPart(node);
			}else if(node.getContained() instanceof ValueMemberDef){
		    	return  new ValueMemberDefNodeEditPart(node);
			}else if(node.getContained() instanceof StructDef){
		    	return  new StructDefNodeEditPart(node);
			}else if(node.getContained() instanceof UnionDef){
		    	return  new UnionDefNodeEditPart(node);
			}else if(node.getContained() instanceof ExceptionDef){
		    	return  new ExceptionDefNodeEditPart(node);
			}else if(node.getContained() instanceof ValueDef){
		    	return  new ValueDefNodeEditPart(node);
	//*******************************************************	    	
			}else if(node.getContained() instanceof HomeImplDef){
		    	return  new HomeImplNodeEditPart(node);
			}else if(node.getContained() instanceof HomeInstantiation){
		    	return  new HomeInstanceNodeEditPart(node);
			}else if(node.getContained() instanceof ComponentImplDef){
		    	return  new ComponentImplNodeEditPart(node);
			}else if(node.getContained() instanceof ComponentInstantiation){
		    	return  new ComponentInstanceNodeEditPart(node);
			}else if(node.getContained() instanceof Composition){
		    	return  new CompositionNodeEditPart(node);	
			}else if(node.getContained() instanceof ExternalInstance){
		    	return  new ExternalInstanceNodeEditPart(node);	
			}else if(node.getContained() instanceof SoftwarePackage){
		    	return  new SoftwarePackageNodeEditPart(node);		
			}else if(node.getContained() instanceof Implementation){
		    	return  new DeploymentUnitNodeEditPart(node);	
			}else if(node.getContained() instanceof DependentFile){
		    	return  new DependentFileNodeEditPart(node);	
			}else if(node.getContained() instanceof ContainedFile){
		    	return  new ContainedFileNodeEditPart(node);	
			}else if(node.getContained() instanceof Deploymentrequirement){
		    	return  new DeploymentrequirementNodeEditPart(node);	
			}else if(node.getContained() instanceof RegisterComponentInstance){
		    	return  new RegisterComponentInstanceNodeEditPart(node);	
			}else if(node.getContained() instanceof Assembly){
		    	return  new AssemblyNodeEditPart(node);	
			}else if(node.getContained() instanceof Property){
		    	return  new PropertyNodeEditPart(node);	
			}else if(node.getContained() instanceof Rule){
		    	return  new RuleNodeEditPart(node);	
			}else if(node.getContained() instanceof ProcessCollocation){
		    	return  new ProcessCollocationNodeEditPart(node);	
	//***********************************************************	    	
		    	
			}else if(node.getContained() instanceof ProvidesDef
					|| node.getContained() instanceof UsesDef
					|| node.getContained() instanceof PublishesDef
					|| node.getContained() instanceof EmitsDef
					|| node.getContained() instanceof ConsumesDef)
			    return new PortLabelEditPart(node);
			
		}
	return null;
    }

}
