
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
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.XYLayoutEditPolicy;
import org.eclipse.gef.requests.ChangeBoundsRequest;
import org.eclipse.gef.requests.CreateRequest;

import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.HomeInstantiation;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.View;
import ccm.commands.constraints.ConstraintForComponentDefNode;
import ccm.commands.constraints.SetConstraintForNode;
import ccm.commands.constraints.SetConstraintForPortNode;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.commands.create.visual.CreateNodeForHomeInstanceCommand;
import ccm.commands.create.visual.CreateNodeForTypedefDefCommand;
import ccm.edit.ComponentInstanceNodeEditPart;
import ccm.edit.PortLabelEditPart;
import ccm.model.ModelFactory;
import ccm.request.DragAndDropRequest;


public class ProcessCollocationXYLayoutEditPolicy extends XYLayoutEditPolicy {

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
		  if(newObjectType==HomeInstantiation.class){
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(90,60);
			CreateNodeForHomeInstanceCommand create=new CreateNodeForHomeInstanceCommand();
			//System.out.println( "CreateNodeForInterfaceDefCommand:"+create);
			//CreateNodeForInterfaceDefCommand create=new CreateNodeForInterfaceDefCommand();
			//request.setType(InterfaceDef.class);
			
			initilizeCommandForContainer(create,request,dim);
			ModuleDef md=getView().getModuleDef();
			setRootModule(create,getView().getModuleDef());
			createCommand = create;
		 
		}
		return createCommand;

	}
	
	private void initilizeCommandForContainer(CreateNodeForHomeInstanceCommand command,
	        								  CreateRequest request,Dimension dim){
		Node parentNode=(Node)getHost().getModel();
		Node parnentparentNode=parentNode.getDefineIn();
		//int x=parentNode.getX();
		Point point= new Point(request.getLocation().x-parentNode.getX()-parnentparentNode.getX(),request.getLocation().y-parentNode.getY()-parnentparentNode.getY()-25);
		command.setRectangle(new Rectangle(point,dim));
		command.setView(getView());
		
		//command.setContainer(getView().getModuleDef());
        //command.setContainer((Container)getView().getDiagram().eContainer());
		//System.out.println(">>>>>>"+getHost().getModel()+(getHost().getModel() instanceof Container));
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
		return (View) getHost().getParent().getParent().getModel();
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
		//System.out.println("createChangeConstraintCommand for homes child :"+child);
		if(child instanceof PortLabelEditPart){
		    SetConstraintForPortNode command = new SetConstraintForPortNode();
			command.setPart((Node)child.getModel());
			command.setRectangle((Rectangle)constraint);
			return command;
		}else if(child instanceof ComponentInstanceNodeEditPart){
		    ConstraintForComponentDefNode command = new ConstraintForComponentDefNode(true);
			command.setPart((Node)child.getModel());
			command.setRectangle((Rectangle)constraint);
			return command;
		}
		
		SetConstraintForNode command = new SetConstraintForNode();
		command.setPart((Node)child.getModel());
		command.setRectangle((Rectangle)constraint);
		return command;
	}
	protected Command createChangeConstraintCommand(EditPart child, Object constraint) {
		if(child instanceof PortLabelEditPart){
		    SetConstraintForPortNode command = new SetConstraintForPortNode();
			command.setPart((Node)child.getModel());
			command.setRectangle((Rectangle)constraint);
			return command;
		}else if(child instanceof ComponentInstanceNodeEditPart){
		    ConstraintForComponentDefNode command = new ConstraintForComponentDefNode(true);
			command.setPart((Node)child.getModel());
			command.setRectangle((Rectangle)constraint);
			return command;
		}
		//System.out.println("createChangeConstraintCommand for homes child :"+child);
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
  
