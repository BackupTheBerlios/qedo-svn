/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 */
package ccm.edit.policy;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy;
import org.eclipse.gef.requests.CreateConnectionRequest;
import org.eclipse.gef.requests.ReconnectRequest;

import ccm.commands.connect.ManagesConnectCommand;
import ccm.edit.ComponentImplNodeEditPart;
import ccm.model.template.RelationTemplate;




public class ComponentImplEditPolicy  extends GraphicalNodeEditPolicy {

    
	public ComponentImplEditPolicy () {
		super();
	}

	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCompleteCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 * command is not null,if all OCL are true
	 * OCL isAbstract implies base->forAll(isAbstract)
	 * OCL base->notEmpty() implies (base->forAll(oclType=HomeDef))
	 */
	protected Command getConnectionCompleteCommand(CreateConnectionRequest request) {
		//ComponentImplDef conponentImpl=(ComponentImplDef)getComponentDefEditPart().getModelNode().getContained();
	
	    if (request.getStartCommand() instanceof ManagesConnectCommand){	
	    	ManagesConnectCommand command=(ManagesConnectCommand) request.getStartCommand();
	    	 
	        
	       // AbstItfDerivedConnectCommand command = (AbstItfDerivedConnectCommand)request.getStartCommand();
	       // AbstractInterfaceDef derAbstItf=(AbstractInterfaceDef) command.getSource().getContained();
			command.setTarget(((ComponentImplNodeEditPart)getHost()).getModelNode());
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
		if(request.getNewObject() instanceof RelationTemplate){
		    RelationTemplate rel=(RelationTemplate) request.getNewObject();
		  // if(rel.getKind()==0){
		}
		return null;
	
	}

//	private ComponentDefNodeEditPart getComponentDefEditPart(){
//	    return (ComponentDefNodeEditPart) getHost();
//	}
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
 
 
