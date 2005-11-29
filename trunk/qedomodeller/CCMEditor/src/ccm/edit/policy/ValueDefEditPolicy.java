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

import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy;
import org.eclipse.gef.requests.CreateConnectionRequest;
import org.eclipse.gef.requests.ReconnectRequest;

import CCMModel.EventDef;
import CCMModel.ValueDef;
import CCMModel.View;
import ccm.commands.connect.AbstractDerivedConnectCommand;
import ccm.commands.connect.EventPortEventConnectCommand;
import ccm.commands.connect.HomeKeyConnectCommand;
import ccm.commands.connect.ValueDerivedConnectCommand;
import ccm.commands.connect.ValueSupportsConnectCommand;
import ccm.edit.ValueDefNodeEditPart;
import ccm.model.template.RelationTemplate;




public class ValueDefEditPolicy extends GraphicalNodeEditPolicy {


	public ValueDefEditPolicy() {
		super();
	}

	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCompleteCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 * command is not null,if all OCL are true
	 * OCL base->notEmpty implies not base.isAbstract
	 * 
	 */
	protected Command getConnectionCompleteCommand(CreateConnectionRequest request) {
	    if (request.getStartCommand() instanceof ValueDerivedConnectCommand){	
	        ValueDef baseValue=(ValueDef) getValueDefEditPart().getModelNode().getContained();
	        //OCL base->notEmpty implies not base.isAbstract
	        if(baseValue.isIsAbstract())return null;
			ValueDerivedConnectCommand command = (ValueDerivedConnectCommand)request.getStartCommand();
			command.setTarget(getValueDefEditPart().getModelNode());
		    return command;
		}else if(request.getStartCommand() instanceof AbstractDerivedConnectCommand){
		    ValueDef baseValue=(ValueDef) getValueDefEditPart().getModelNode().getContained();
	        //OCL base->notEmpty implies not base.isAbstract
	        if(!baseValue.isIsAbstract())return null;
	        AbstractDerivedConnectCommand command = (AbstractDerivedConnectCommand)request.getStartCommand();
			command.setTarget(getValueDefEditPart().getModelNode());
		    return command;
		}else if(request.getStartCommand() instanceof EventPortEventConnectCommand){
		    ValueDef event=(ValueDef) getValueDefEditPart().getModelNode().getContained();
		    if(!(event instanceof EventDef))return null;
		    EventPortEventConnectCommand command = (EventPortEventConnectCommand) request.getStartCommand();
			command.setTarget(getValueDefEditPart().getModelNode());
		    return command;
		
		}else if(request.getStartCommand() instanceof HomeKeyConnectCommand){
		    ValueDef event=(ValueDef) getValueDefEditPart().getModelNode().getContained();
		    if(!(event instanceof ValueDef))return null;
		    HomeKeyConnectCommand command = (HomeKeyConnectCommand) request.getStartCommand();
			command.setTarget(getValueDefEditPart().getModelNode());
		    return command;
		}
		return null;
	
	}
	
	
	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCreateCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 * command is not null,if all OCL are true
	 * OCL at most only one base(Cardinality)
	 * OCL isAbstract implies  base->isEmpty
	 */
	protected Command getConnectionCreateCommand(CreateConnectionRequest request) {
		if(request.getNewObject() instanceof RelationTemplate){
		    RelationTemplate rel=(RelationTemplate) request.getNewObject();
		    if(rel.getKind()==0){
		        ValueDef derValue=(ValueDef) getValueDefEditPart().getModelNode().getContained();
		        //OCL at most only one base(Cardinality)
		        if(derValue.getDerivedRelation()!=null) return null;
		        //OCL isAbstract implies  base->isEmpty
		        if(derValue.isIsAbstract())return null;
		        ValueDerivedConnectCommand command = new ValueDerivedConnectCommand();
		        command.setView((View) getValueDefEditPart().getParent().getModel());
		        command.setSource(getValueDefEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
		    }else if(rel.getKind()==1){
		        AbstractDerivedConnectCommand command = new AbstractDerivedConnectCommand();
		        command.setView((View) getValueDefEditPart().getParent().getModel());
		        command.setSource(getValueDefEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
		    }else if(rel.getKind()==13){
		        ValueDef value=(ValueDef) getValueDefEditPart().getModelNode().getContained();
		        if(value.getSupportsRelation()!=null)return null;
		        ValueSupportsConnectCommand command = new ValueSupportsConnectCommand();
		        command.setView((View) getValueDefEditPart().getParent().getModel());
		        command.setSource(getValueDefEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
		    }
		}
		return null;
	
	}

	private ValueDefNodeEditPart getValueDefEditPart(){
	    return (ValueDefNodeEditPart) getHost();
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
}
