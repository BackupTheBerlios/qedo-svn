/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * Contributors:
 *     	Eduard Weiss
 * 
 */
package ccm.edit.policy;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy;
import org.eclipse.gef.requests.CreateConnectionRequest;
import org.eclipse.gef.requests.ReconnectRequest;

import CCMModel.AbstractInterfaceDef;
import CCMModel.ComponentDef;
import CCMModel.View;
import ccm.commands.connect.AbstItfDerivedConnectCommand;
import ccm.commands.connect.ComponentHomeConnectCommand;
import ccm.commands.connect.ComponentSupportsConnectCommand;
import ccm.edit.ComponentDefNodeEditPart;
import ccm.model.template.RelationTemplate;




public class ComponentDefEditPolicy extends GraphicalNodeEditPolicy {

    
	public ComponentDefEditPolicy() {
		super();
	}

	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCompleteCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 * command is not null,if all OCL are true
	 * OCL isAbstract implies base->forAll(isAbstract)
	 * OCL base->notEmpty() implies (base->forAll(oclType=HomeDef))
	 */
	protected Command getConnectionCompleteCommand(CreateConnectionRequest request) {
	    if (request.getStartCommand() instanceof AbstItfDerivedConnectCommand){	
	        AbstractInterfaceDef baseAbstItf=(AbstractInterfaceDef) getComponentDefEditPart().
	        																getModelNode().getContained();
	        
	        AbstItfDerivedConnectCommand command = (AbstItfDerivedConnectCommand)request.getStartCommand();
	        AbstractInterfaceDef derAbstItf=(AbstractInterfaceDef) command.getSource().getContained();
	        //OCL base->notEmpty() implies (base->forAll(oclType=HomeDef))
	        if(!(derAbstItf instanceof ComponentDef))return null;
	        // OCL isAbstract implies base->forAll(isAbstract)
	        if(derAbstItf.isIsAbstract())
	            if(! baseAbstItf.isIsAbstract())return null;
			command.setTarget(getComponentDefEditPart().getModelNode());
		    return command;
		}
	    else if (request.getStartCommand() instanceof ComponentHomeConnectCommand){	
		   // ComponentDef component=(ComponentDef) getComponentDefEditPart().getModelNode().getContained();
		   // if(component.getCompHomeRelation()!=null)return null;
		    ComponentHomeConnectCommand command = (ComponentHomeConnectCommand)request.getStartCommand();
		    command.setTarget(getComponentDefEditPart().getModelNode());
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
		    
		     if(rel.getKind()==0){
		        ComponentDef derComponent=(ComponentDef) getComponentDefEditPart().getModelNode().getContained();
		        //OCL base->size()<=1
		       // if(derComponent.getDerivedRelation().size()==1) return null;
		        AbstItfDerivedConnectCommand command = new AbstItfDerivedConnectCommand();
		        command.setView((View) getComponentDefEditPart().getParent().getModel());
		        command.setSource(getComponentDefEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
		    }else if(rel.getKind()==13){
		        ComponentSupportsConnectCommand command = new ComponentSupportsConnectCommand();
		        command.setView((View) getComponentDefEditPart().getParent().getModel());
		        command.setSource(getComponentDefEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
		    }
		}
		return null;
	
	}

	private ComponentDefNodeEditPart getComponentDefEditPart(){
	    return (ComponentDefNodeEditPart) getHost();
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
