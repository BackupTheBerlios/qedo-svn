/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * @author Siegercn
 * 
 */
package ccm.edit.policy;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy;
import org.eclipse.gef.requests.CreateConnectionRequest;
import org.eclipse.gef.requests.ReconnectRequest;
import org.eclipse.swt.widgets.Shell;

import ccm.commands.connect.InterfaceConnectCommand;
import ccm.edit.ComponentInstanceNodeEditPart;
 




public class ComponentInstanceEditPolicy extends GraphicalNodeEditPolicy {

    
	public ComponentInstanceEditPolicy() {
		super();
	}

	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCompleteCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 * command is not null,if all OCL are true
	 * OCL isAbstract implies base->forAll(isAbstract)
	 * OCL base->notEmpty() implies (base->forAll(oclType=HomeDef))
	 */
	protected Command getConnectionCompleteCommand(CreateConnectionRequest request) {
		if(request.getStartCommand() instanceof InterfaceConnectCommand ){
			InterfaceConnectCommand command = (InterfaceConnectCommand)request.getStartCommand();
		    command.setTarget(((ComponentInstanceNodeEditPart)getHost()).getModelNode());
		    Shell shell=getHost().getViewer().getControl().getShell();
			command.setShell(shell);
		    return command;
			}
		return null;
	
	}
	
	
	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCreateCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 * command is not null,if all OCL are true
	 * OCL base->size()<=1
	 */
	protected Command getConnectionCreateCommand(CreateConnectionRequest request) {
		 
		return null;
	
	}

	 
	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getReconnectTargetCommand(org.eclipse.gef.requests.ReconnectRequest)
	 */
	protected Command getReconnectTargetCommand(ReconnectRequest request) {	
		return null;		
	}

	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getReconnectSourceCommand(org.eclipse.gef.requests.ReconnectRequest)
	 */
	protected Command getReconnectSourceCommand(ReconnectRequest request) {
		return null;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getTargetEditPart(org.eclipse.gef.Request)
	 */
	public EditPart getTargetEditPart(Request request) {
		return super.getTargetEditPart(request);
	}
}
 