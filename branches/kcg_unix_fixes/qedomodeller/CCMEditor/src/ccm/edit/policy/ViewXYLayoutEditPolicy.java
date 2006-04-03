/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 *      siegercn
 * 
 */
package ccm.edit.policy;


import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.XYLayoutEditPolicy;
import org.eclipse.gef.requests.CreateRequest;

import CCMModel.AliasDef;
import CCMModel.Assembly;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.Contained;
import CCMModel.ContainedFile;
import CCMModel.Container;
import CCMModel.DependentFile;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ExceptionDef;
import CCMModel.ExternalInstance;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.ProcessCollocation;
import CCMModel.Property;
import CCMModel.RegisterComponentInstance;
import CCMModel.Rule;
import CCMModel.SoftwarePackage;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.View;
import MDE.Deployment.DeploymentRequirement;
import ccm.commands.constraints.ConstraintForComponentDefNode;
import ccm.commands.constraints.SetConstraintForNode;
import ccm.commands.constraints.SetConstraintForPortNode;
import ccm.commands.create.visual.CreateNodeForAliasDefCommand;
import ccm.commands.create.visual.CreateNodeForAssemblyCommand;
import ccm.commands.create.visual.CreateNodeForComponentDefCommand;
import ccm.commands.create.visual.CreateNodeForComponentImplCommand;
import ccm.commands.create.visual.CreateNodeForCompositionCommand;
import ccm.commands.create.visual.CreateNodeForConstantDefCommand;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.commands.create.visual.CreateNodeForContainerCommand;
import ccm.commands.create.visual.CreateNodeForEnumDefCommand;
import ccm.commands.create.visual.CreateNodeForExceptionDefCommand;
import ccm.commands.create.visual.CreateNodeForExternalInstanceCommand;
import ccm.commands.create.visual.CreateNodeForHomeDefCommand;
import ccm.commands.create.visual.CreateNodeForHomeImplCommand;
import ccm.commands.create.visual.CreateNodeForInterfaceDefCommand;
import ccm.commands.create.visual.CreateNodeForModuleDefCommand;
import ccm.commands.create.visual.CreateNodeForSoftwarePackageCommand;
import ccm.commands.create.visual.CreateNodeForStructDefCommand;
import ccm.commands.create.visual.CreateNodeForTypedefDefCommand;
import ccm.commands.create.visual.CreateNodeForUnionDefCommand;
import ccm.commands.create.visual.CreateNodeForValueBoxDefCommand;
import ccm.commands.create.visual.CreateNodeForValueDefCommand;
import ccm.commands.dnd.AddModel2DiagramCommand;
import ccm.commands.dnd.DragAssembly2DiagramCommand;
import ccm.commands.dnd.DragComponent2DiagramCommand;
import ccm.commands.dnd.DragComponentImpl2DiagramCommand;
import ccm.commands.dnd.DragComposition2DiagramCommand;
import ccm.commands.dnd.DragEvent2DiagramCommand;
import ccm.commands.dnd.DragHome2DiagramCommand;
import ccm.commands.dnd.DragHomeImpl2DiagramCommand;
import ccm.commands.dnd.DragInterface2DiagramCommand;
import ccm.commands.dnd.DragSoftwarePackage2DiagramCommand;
import ccm.commands.dnd.DragValue2DiagramCommand;
import ccm.edit.AliasDefNodeEditPart;
import ccm.edit.AssemblyNodeEditPart;
import ccm.edit.ComponentDefNodeEditPart;
import ccm.edit.ComponentImplNodeEditPart;
import ccm.edit.ComponentInstanceNodeEditPart;
import ccm.edit.CompositionNodeEditPart;
import ccm.edit.ConstantDefNodeEditPart;
import ccm.edit.EnumNodeEditPart;
import ccm.edit.ExceptionDefNodeEditPart;
import ccm.edit.ExternalInstanceNodeEditPart;
import ccm.edit.HomeDefNodeEditPart;
import ccm.edit.HomeImplNodeEditPart;
import ccm.edit.HomeInstanceNodeEditPart;
import ccm.edit.InterfaceDefNodeEditPart;
import ccm.edit.ModuleDefNodeEditPart;
import ccm.edit.PortLabelEditPart;
import ccm.edit.SoftwarePackageNodeEditPart;
import ccm.edit.StructDefNodeEditPart;
import ccm.edit.UnionDefNodeEditPart;
import ccm.edit.ValueBoxDefNodeEditPart;
import ccm.edit.ValueDefNodeEditPart;
import ccm.model.ModelFactory;
import ccm.request.DragAndDropRequest;


public class ViewXYLayoutEditPolicy extends XYLayoutEditPolicy {

	/**
	 * @see org.eclipse.gef.editpolicies.ConstrainedLayoutEditPolicy#createAddCommand(org.eclipse.gef.EditPart, java.lang.Object)
	 */
	protected Command createAddCommand(EditPart child, Object constraint) {		
		return null;
	}

	/**
	 * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#getCreateCommand(org.eclipse.gef.requests.CreateRequest)
	 */
	protected Command getCreateCommand(CreateRequest request) {
		if(request instanceof DragAndDropRequest) {
			DragAndDropRequest req = (DragAndDropRequest) request;
			 //ViewEditPart vep=(ViewEditPart) getHost();
             //Shell shell=vep.getViewer().getControl().getShell();

			// model element has been dropped on a diagram
			
	//*******************************************************************
			if (req.getNewObject() instanceof SoftwarePackage) {
				return new DragSoftwarePackage2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			if (req.getNewObject() instanceof Assembly) {
				return new DragAssembly2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			if (req.getNewObject() instanceof ComponentDef) {
				return new DragComponent2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			if (req.getNewObject() instanceof HomeDef) {
				return new DragHome2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			
			
			if (req.getNewObject() instanceof InterfaceDef) {
				return new DragInterface2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			if (req.getNewObject() instanceof EventDef) {
				return new DragEvent2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			 
			if (req.getNewObject() instanceof ValueDef) {
				return new DragValue2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			
			
			
			if (req.getNewObject() instanceof HomeImplDef) {
				return new DragHomeImpl2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			if (req.getNewObject() instanceof Composition) {
				return new DragComposition2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			//DragComposition2DiagramCommand
			
			if (req.getNewObject() instanceof ComponentImplDef) {
				return new DragComponentImpl2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			if (req.getNewObject() instanceof Contained && !(req.getNewObject() instanceof ContainedFile)
					&& !(req.getNewObject() instanceof DependentFile)
					&& !(req.getNewObject() instanceof DeploymentRequirement)
					&& !(req.getNewObject() instanceof Property)
					&& !(req.getNewObject() instanceof Rule)
					&& !(req.getNewObject() instanceof ProcessCollocation)
					&& !(req.getNewObject() instanceof HomeInstantiation)
					&& !(req.getNewObject() instanceof ComponentInstantiation)
					&& !(req.getNewObject() instanceof RegisterComponentInstance)) {
				return new AddModel2DiagramCommand( (Contained) req.getNewObject(),
						((View) getHost().getModel()).getDiagram(),
						req.getLocation());
			}
			
			// relation has been dropped on a diagram
//			if (req.getNewObject() instanceof Relation) {
//				return new AddRelation2DiagramCommand( (Relation) req.getNewObject(), ((View) getHost().getModel()).getDiagram());
//			}
		}
		
		Object	newObjectType = request.getNewObjectType();
		Command	createCommand = null;
		if( newObjectType == HomeDef.class) {
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(120,80);
			CreateNodeForHomeDefCommand create=new CreateNodeForHomeDefCommand();
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
//******************************************************
		}else if(newObjectType==SoftwarePackage.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(150,120);
			CreateNodeForSoftwarePackageCommand create=new CreateNodeForSoftwarePackageCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			setRootModule(create,getView().getModuleDef());
			createCommand = create;
	//	}else if(newObjectType==Implementation.class){
	//		Dimension dim=request.getSize();
	//		if(dim==null)dim=new Dimension(90,60);
	//		CreateNodeForDeploymentUnitCommand create=new CreateNodeForDeploymentUnitCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
	//		initilizeCommandForContainer(create,request,dim);
	//		createCommand = create;
		}else if(newObjectType==Assembly.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(460,320);
			CreateNodeForAssemblyCommand create=new CreateNodeForAssemblyCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			setRootModule(create,getView().getModuleDef());
			createCommand = create;
		}else if(newObjectType==ExternalInstance.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForExternalInstanceCommand create=new CreateNodeForExternalInstanceCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		}else if(newObjectType==Composition.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForCompositionCommand create=new CreateNodeForCompositionCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
			
		}else if(newObjectType==Composition.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForCompositionCommand create=new CreateNodeForCompositionCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		}else if(newObjectType==HomeImplDef.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForHomeImplCommand create=new CreateNodeForHomeImplCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			setRootModule(create,getView().getModuleDef());
			createCommand = create;
		}else if(newObjectType==ComponentImplDef.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForComponentImplCommand create=new CreateNodeForComponentImplCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			setRootModule(create,getView().getModuleDef());
			createCommand = create;
			
//***********************************************************			
		}else if(newObjectType==ModuleDef.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForModuleDefCommand create=new CreateNodeForModuleDefCommand();
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		}else if(newObjectType==InterfaceDef.class){
			Dimension dim=new Dimension(-1,-1);
			CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		}else if(newObjectType==ValueDef.class  ){
			Dimension dim=new Dimension(-1,-1);
			CreateNodeForValueDefCommand create=new CreateNodeForValueDefCommand(false);
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		}else if( newObjectType==EventDef.class){
			Dimension dim=new Dimension(-1,-1);
			CreateNodeForValueDefCommand create=new CreateNodeForValueDefCommand(true);
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		}else if(newObjectType==ComponentDef.class){
			Dimension dim=new Dimension(-1,-1);
			CreateNodeForComponentDefCommand create=new CreateNodeForComponentDefCommand();
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		}else if(newObjectType==ExceptionDef.class){
			CreateNodeForExceptionDefCommand create=new CreateNodeForExceptionDefCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(-1,-1);
			create.setConstraint(new Rectangle(request.getLocation(),dim));
			create.setNewObject((ExceptionDef) request.getNewObject());
			create.setView(getView());
			create.setContainer(getView().getModuleDef());
			setRootModule(create,getView().getModuleDef());
			setIDLTypes(create);
			createCommand = create;
		}else if(newObjectType==StructDef.class){
			CreateNodeForStructDefCommand create=new CreateNodeForStructDefCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(-1,-1);
			create.setConstraint(new Rectangle(request.getLocation(),dim));
			create.setNewObject((StructDef) request.getNewObject());
			create.setView(getView());
			create.setContainer(getView().getModuleDef());
			setRootModule(create,getView().getModuleDef());
			setIDLTypes(create);
			createCommand = create;
		}else if(newObjectType==UnionDef.class){
			CreateNodeForUnionDefCommand create=new CreateNodeForUnionDefCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(-1,-1);
			create.setConstraint(new Rectangle(request.getLocation(),dim));
			create.setNewObject((UnionDef) request.getNewObject());
			create.setView(getView());
			create.setContainer(getView().getModuleDef());
			setRootModule(create,getView().getModuleDef());
			setIDLTypes(create);
			createCommand = create;
		}else if(newObjectType==EnumDef.class){
			CreateNodeForEnumDefCommand create=new CreateNodeForEnumDefCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(-1,-1);
			initilizeCommandForTypedefDef(create,request,dim);
			createCommand = create;
		}else if(newObjectType==AliasDef.class){
			CreateNodeForAliasDefCommand create=new CreateNodeForAliasDefCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(-1,-1);
			initilizeCommandForTypedefDef(create,request,dim);
			setRootModule(create,getView().getModuleDef());
			setIDLTypes(create);
			createCommand = create;
		}else if(newObjectType==ValueBoxDef.class){
			CreateNodeForValueBoxDefCommand create=new CreateNodeForValueBoxDefCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(-1,-1);
			initilizeCommandForTypedefDef(create,request,dim);
			setRootModule(create,getView().getModuleDef());
			setIDLTypes(create);
			createCommand = create;
		}else if(newObjectType==ConstantDef.class){
			CreateNodeForConstantDefCommand create=new CreateNodeForConstantDefCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(-1,-1);
			create.setConstraint(new Rectangle(request.getLocation(),dim));
			create.setNewObject((ConstantDef) request.getNewObject());
			create.setView(getView());
			create.setContainer(getView().getModuleDef());
			setRootModule(create,getView().getModuleDef());
			setIDLTypes(create);
			createCommand = create;
		}
		return createCommand;

	}
	
	private void initilizeCommandForContainer(CreateNodeForContainerCommand command,
	        								  CreateRequest request,Dimension dim){
		command.setRectangle(new Rectangle(request.getLocation(),dim));
		command.setView(getView());
		
		//command.setContainer(getView().getModuleDef());
        command.setContainer((Container)getView().getDiagram().eContainer());
		command.setNewObject((Contained) request.getNewObject());	
	}
	
	private void initilizeCommandForTypedefDef(CreateNodeForTypedefDefCommand command,
			  								  CreateRequest request,Dimension dim){
	    command.setConstraint(new Rectangle(request.getLocation(),dim));
	    command.setView(getView());
	    //command.setContainer(getView().getModuleDef());
	    command.setContainer((Container)getView().getDiagram().eContainer());
	    command.setNewObject((Contained) request.getNewObject());	
	}
	
	private View getView(){
		return (View) getHost().getModel();
	}


	
	private void setRootModule(CreateNodeForContainedCommand command,Contained con ){
	       ModelFactory mf=new ModelFactory();
	       command.setRootModule(mf.getRootModule(con));
	}
	
	private void setIDLTypes(CreateNodeForContainedCommand command){
	       ModelFactory mf=new ModelFactory();
	       command.setIdlTypes(mf.getIDLTypes(command.getRootModule()));
	}
	/**
	 * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#createChildEditPolicy(org.eclipse.gef.EditPart)
	 */
	protected EditPolicy createChildEditPolicy(EditPart child) {
		return super.createChildEditPolicy(child);
	}
	


	/**
	 * @see org.eclipse.gef.editpolicies.ConstrainedLayoutEditPolicy#createChangeConstraintCommand(org.eclipse.gef.EditPart, java.lang.Object)
	 */
	protected Command createChangeConstraintCommand(EditPart child, Object constraint) {
		if ( child instanceof ModuleDefNodeEditPart
				|| child instanceof EnumNodeEditPart
				|| child instanceof AliasDefNodeEditPart
				|| child instanceof ValueBoxDefNodeEditPart
				|| child instanceof ConstantDefNodeEditPart
				|| child instanceof StructDefNodeEditPart
				|| child instanceof UnionDefNodeEditPart
				|| child instanceof ExceptionDefNodeEditPart
				|| child instanceof ValueDefNodeEditPart
				|| child instanceof InterfaceDefNodeEditPart
				|| child instanceof HomeDefNodeEditPart
	//****************************************************
				|| child instanceof HomeImplNodeEditPart
				|| child instanceof HomeInstanceNodeEditPart
				|| child instanceof ComponentImplNodeEditPart
				|| child instanceof ComponentInstanceNodeEditPart
				|| child instanceof CompositionNodeEditPart
				|| child instanceof ExternalInstanceNodeEditPart
				|| child instanceof SoftwarePackageNodeEditPart
				|| child instanceof AssemblyNodeEditPart
				|| child instanceof ExternalInstanceNodeEditPart
				
				
		){ 
			SetConstraintForNode command = new SetConstraintForNode();
			command.setPart((Node)child.getModel());
			command.setRectangle((Rectangle)constraint);
			return command;
		}else if(child instanceof PortLabelEditPart){
		    SetConstraintForPortNode command = new SetConstraintForPortNode();
			command.setPart((Node)child.getModel());
			command.setRectangle((Rectangle)constraint);
			return command;
		}else if(child instanceof ComponentDefNodeEditPart){
		    ConstraintForComponentDefNode command = new ConstraintForComponentDefNode(false);
			command.setPart((Node)child.getModel());
			command.setRectangle((Rectangle)constraint);
			return command;
		}
		return null;
	}



    /**
     * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#getDeleteDependantCommand(org.eclipse.gef.Request)
     */
    protected Command getDeleteDependantCommand(Request request) {
        return null;
    }
}
