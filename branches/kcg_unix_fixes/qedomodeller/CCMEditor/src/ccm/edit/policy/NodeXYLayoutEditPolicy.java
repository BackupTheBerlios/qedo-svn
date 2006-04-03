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
package ccm.edit.policy;


import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.XYLayoutEditPolicy;
import org.eclipse.gef.requests.CreateRequest;

import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Node;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.UsesDef;
import CCMModel.View;
import ccm.commands.constraints.SetConstraintForNode;
import ccm.commands.create.visual.CreateNodeCommand;
import ccm.edit.PortLabelEditPart;





public class NodeXYLayoutEditPolicy extends XYLayoutEditPolicy {

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.ConstrainedLayoutEditPolicy#createAddCommand(org.eclipse.gef.EditPart, java.lang.Object)
	 */
	protected Command createAddCommand(EditPart child, Object constraint) {		
		return null;
	}



	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#getCreateCommand(org.eclipse.gef.requests.CreateRequest)
	 */
	protected Command getCreateCommand(CreateRequest request) {
		Object	newObjectType = request.getNewObjectType();
		Command	createCommand = null;
		if( newObjectType == ProvidesDef.class ||
		    newObjectType == UsesDef.class ||
		    newObjectType == PublishesDef.class ||
		    newObjectType == ConsumesDef.class ) {
			CreateNodeCommand create = new CreateNodeCommand();
			Dimension dim=request.getSize();
			if(dim==null)dim=new Dimension(100,20);
			create.setConstraint(new Rectangle(request.getLocation(),dim));
			create.setParent((View)getHost().getModel());
			create.setModelParent(((View)getHost().getModel()).getModuleDef());
			create.setModelObject((Contained) request.getNewObject());
			create.setLabel("create a node");
			createCommand = create;
		}
		return createCommand;

	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#getDeleteDependantCommand(org.eclipse.gef.Request)
	 */
	protected Command getDeleteDependantCommand(Request request) {
		return null;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#createChildEditPolicy(org.eclipse.gef.EditPart)
	 */
	protected EditPolicy createChildEditPolicy(EditPart child) {
		return super.createChildEditPolicy(child);
	}
	


	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.ConstrainedLayoutEditPolicy#createChangeConstraintCommand(org.eclipse.gef.EditPart, java.lang.Object)
	 */
	protected Command createChangeConstraintCommand(EditPart child, Object constraint) {
		if (child instanceof PortLabelEditPart){
			IFigure f;
			SetConstraintForNode command = new SetConstraintForNode();
			command.setPart((Node)child.getModel());
			/*if((f = this.getHostFigure()) instanceof CORBAComponent) {
				command.setRectangle(new Rectangle(
						((CORBAComponent)f).getPortCoordinates(((Rectangle)constraint).getLocation()),
						new Dimension(-1,-1))
						);
			}*/
			command.setRectangle((Rectangle)constraint);
			return command;
		}
		return null;
	}
}
