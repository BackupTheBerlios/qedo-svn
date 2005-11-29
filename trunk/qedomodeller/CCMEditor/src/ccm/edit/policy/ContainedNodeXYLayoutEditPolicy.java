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


import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.NonResizableEditPolicy;
import org.eclipse.gef.editpolicies.XYLayoutEditPolicy;
import org.eclipse.gef.requests.ChangeBoundsRequest;
import org.eclipse.gef.requests.CreateRequest;

import CCMModel.Node;

import ccm.commands.constraints.SetConstraintForNode;
import ccm.edit.OperationDefNodeEditPart;




public class ContainedNodeXYLayoutEditPolicy extends XYLayoutEditPolicy {

    /**
     * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#getMoveChildrenCommand(org.eclipse.gef.Request)
     */
    protected Command getMoveChildrenCommand(Request request) {
        return null;
    }
    
    /**
     * @see org.eclipse.gef.editpolicies.ConstrainedLayoutEditPolicy#getResizeChildrenCommand(org.eclipse.gef.requests.ChangeBoundsRequest)
     */
     protected Command getResizeChildrenCommand(ChangeBoundsRequest request) {
         return null;
    }
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
		return null;
	}

	/**
	 * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#getDeleteDependantCommand(org.eclipse.gef.Request)
	 */
	protected Command getDeleteDependantCommand(Request request) {
		return null;
	}

	/**
	 * @see org.eclipse.gef.editpolicies.LayoutEditPolicy#createChildEditPolicy(org.eclipse.gef.EditPart)
	 */
//	protected EditPolicy createChildEditPolicy(EditPart child) {
//		return new NonResizableEditPolicy();
//	}
	protected EditPolicy createChildEditPolicy(EditPart child) {
		return super.createChildEditPolicy(child);
	}
	


	/**
	 * @see org.eclipse.gef.editpolicies.ConstrainedLayoutEditPolicy#createChangeConstraintCommand(org.eclipse.gef.EditPart, java.lang.Object)
	 */
	protected Command createChangeConstraintCommand(ChangeBoundsRequest request,EditPart child, Object constraint) {
		System.out.println(" for homes child :"+child);
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
	 
}
