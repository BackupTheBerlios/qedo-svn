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
import org.eclipse.gef.requests.ChangeBoundsRequest;
import org.eclipse.gef.requests.CreateRequest;
import org.eclipse.swt.widgets.Shell;

import CCMModel.AliasDef;
import CCMModel.Assembly;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.Implementation;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ExceptionDef;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.Relation;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.View;
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
import ccm.commands.create.visual.CreateNodeForDeploymentUnitCommand;
import ccm.commands.create.visual.CreateNodeForEnumDefCommand;
import ccm.commands.create.visual.CreateNodeForExceptionDefCommand;
import ccm.commands.create.visual.CreateNodeForHomeDefCommand;
import ccm.commands.create.visual.CreateNodeForHomeImplCommand;
import ccm.commands.create.visual.CreateNodeForInterfaceDefCommand;
import ccm.commands.create.visual.CreateNodeForModuleDefCommand;
import ccm.commands.create.visual.CreateNodeForStructDefCommand;
import ccm.commands.create.visual.CreateNodeForTypedefDefCommand;
import ccm.commands.create.visual.CreateNodeForUnionDefCommand;
import ccm.commands.create.visual.CreateNodeForValueBoxDefCommand;
import ccm.commands.create.visual.CreateNodeForValueDefCommand;
import ccm.commands.dnd.AddModel2DiagramCommand;
import ccm.commands.dnd.AddRelation2DiagramCommand;
import ccm.commands.dnd.DragComponent2DiagramCommand;
import ccm.commands.dnd.DragComponentImpl2DiagramCommand;
import ccm.commands.dnd.DragComposition2DiagramCommand;
import ccm.commands.dnd.DragEvent2DiagramCommand;
import ccm.commands.dnd.DragHome2DiagramCommand;
import ccm.commands.dnd.DragHomeImpl2DiagramCommand;
import ccm.commands.dnd.DragInterface2DiagramCommand;
import ccm.commands.dnd.DragValue2DiagramCommand;
import ccm.edit.AliasDefNodeEditPart;
import ccm.edit.AssemblyNodeEditPart;
import ccm.edit.ComponentDefNodeEditPart;
import ccm.edit.ComponentImplNodeEditPart;
import ccm.edit.ComponentInstanceNodeEditPart;
import ccm.edit.CompositionNodeEditPart;
import ccm.edit.ConstantDefNodeEditPart;
import ccm.edit.DeploymentUnitNodeEditPart;
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
import ccm.edit.ViewEditPart;
import ccm.model.ModelFactory;
import ccm.request.DragAndDropRequest;


public class SoftwarePackageXYLayoutEditPolicy extends XYLayoutEditPolicy {

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
		//	if (req.getNewObject() instanceof ComponentDef) {
		//		return new DragComponent2DiagramCommand( (Contained) req.getNewObject(),
		//				((View) getHost().getModel()).getDiagram(),
		//				req.getLocation());
		//	}
			 
		}
		
		Object	newObjectType = request.getNewObjectType();
		Command	createCommand = null;
		  if(newObjectType==Implementation.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForDeploymentUnitCommand create=new CreateNodeForDeploymentUnitCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			initilizeCommandForContainer(create,request,dim);
			createCommand = create;
		 
		}
		return createCommand;

	}
	
	private void initilizeCommandForContainer(CreateNodeForDeploymentUnitCommand command,
	        								  CreateRequest request,Dimension dim){
		command.setRectangle(new Rectangle(request.getLocation(),dim));
		command.setView(getView());
		
		//command.setContainer(getView().getModuleDef());
        //command.setContainer((Container)getView().getDiagram().eContainer());
		System.out.println(">>>>>>"+getHost().getModel()+(getHost().getModel() instanceof Container));
		command.setContainer((Container)((Node)getHost().getModel()).getContained());
//command.setParentNode((Node)getHost().getModel());
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
		return (View) getHost().getParent().getModel();
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
	


	protected Command createChangeConstraintCommand(ChangeBoundsRequest request,EditPart child, Object constraint) {
		System.out.println("createChangeConstraintCommand for homes child :"+child);
		SetConstraintForNode command = new SetConstraintForNode();
		command.setPart((Node)child.getModel());
		command.setRectangle((Rectangle)constraint);
		return command;
	}
	protected Command createChangeConstraintCommand(EditPart child, Object constraint) {
		System.out.println("createChangeConstraintCommand for homes child :"+child);
		SetConstraintForNode command = new SetConstraintForNode();
		command.setPart((Node)child.getModel());
		command.setRectangle((Rectangle)constraint);
		return command;
	}

    /**
     * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#getDeleteDependantCommand(org.eclipse.gef.Request)
     */
    protected Command getDeleteDependantCommand(Request request) {
        return null;
    }
}
 