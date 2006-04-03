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

import CCMModel.AbstractInterfaceDef;
import CCMModel.InterfaceDef;
import CCMModel.View;
import ccm.commands.connect.AbstItfDerivedConnectCommand;
import ccm.commands.connect.ComponentSupportsConnectCommand;
import ccm.commands.connect.HomeSupportsConnectCommand;
import ccm.commands.connect.ProvidesItfConnectCommand;
import ccm.commands.connect.UsesItfConnectCommand;
import ccm.commands.connect.ValueSupportsConnectCommand;
import ccm.edit.InterfaceDefNodeEditPart;
import ccm.model.template.RelationTemplate;




public class InterfaceDefEditPolicy extends GraphicalNodeEditPolicy {

    
	public InterfaceDefEditPolicy() {
		super();
	}

	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCompleteCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 * command is not null,if all OCL are true
	 * OCL isAbstract implies base->forAll(isAbstract)
	 * OCL base->notEmpty() implies (base->forAll(oclType=InterfaceDef))
	 */
	protected Command getConnectionCompleteCommand(CreateConnectionRequest request) {
	    if (request.getStartCommand() instanceof AbstItfDerivedConnectCommand){	
	        AbstractInterfaceDef baseAbstItf=(AbstractInterfaceDef) getInterfaceDefEditPart().
	        																getModelNode().getContained();
	        
	        AbstItfDerivedConnectCommand command = (AbstItfDerivedConnectCommand)request.getStartCommand();
	        AbstractInterfaceDef derAbstItf=(AbstractInterfaceDef) command.getSource().getContained();
	        //OCL base->notEmpty() implies (base->forAll(oclType=InterfaceDef))
	        if(!(derAbstItf instanceof InterfaceDef))return null;
	        // OCL isAbstract implies base->forAll(isAbstract)
	        if(derAbstItf.isIsAbstract())
	            if(! baseAbstItf.isIsAbstract())return null;
	       // if(!checkedAbstractItfDerivedRelation(derAbstItf,baseAbstItf))return null;
	           if( derAbstItf.getBaseInterface().contains(baseAbstItf)) 
				return null;
	        command.setTarget(getInterfaceDefEditPart().getModelNode());
		    return command;
		}else if(request.getStartCommand() instanceof UsesItfConnectCommand){
		    UsesItfConnectCommand command=(UsesItfConnectCommand) request.getStartCommand();
		    command.setTarget(getInterfaceDefEditPart().getModelNode());
		    return command;
		}else if(request.getStartCommand() instanceof ValueSupportsConnectCommand){
		    ValueSupportsConnectCommand command=(ValueSupportsConnectCommand) request.getStartCommand();
		    command.setTarget(getInterfaceDefEditPart().getModelNode());
		    return command;
		}else if(request.getStartCommand() instanceof ComponentSupportsConnectCommand){
		    AbstractInterfaceDef itf=(AbstractInterfaceDef) getInterfaceDefEditPart().
																	getModelNode().getContained();
		    if(itf.isIsLocal())return null;
		    ComponentSupportsConnectCommand command=(ComponentSupportsConnectCommand) request.getStartCommand();
		    command.setTarget(getInterfaceDefEditPart().getModelNode());
		    return command;
		}else if(request.getStartCommand() instanceof HomeSupportsConnectCommand){
		    AbstractInterfaceDef itf=(AbstractInterfaceDef) getInterfaceDefEditPart().
																	getModelNode().getContained();
		    if(itf.isIsLocal())return null;
		    HomeSupportsConnectCommand command=(HomeSupportsConnectCommand) request.getStartCommand();
		    command.setTarget(getInterfaceDefEditPart().getModelNode());
		    return command;
		}else if(request.getStartCommand() instanceof ProvidesItfConnectCommand){
			ProvidesItfConnectCommand command=(ProvidesItfConnectCommand) request.getStartCommand();
		    command.setTarget(getInterfaceDefEditPart().getModelNode());
		    return command;
		}
		return null;
	
	}
	
	
	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCreateCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 */
	protected Command getConnectionCreateCommand(CreateConnectionRequest request) {
		if(request.getNewObject() instanceof RelationTemplate){
		    RelationTemplate rel=(RelationTemplate) request.getNewObject();
		    if(rel.getKind()==0){
		        AbstItfDerivedConnectCommand command = new AbstItfDerivedConnectCommand();
		        command.setView((View) getInterfaceDefEditPart().getParent().getModel());
		        command.setSource(getInterfaceDefEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
		    }
		}
		return null;
	
	}
	
//	private boolean checkedAbstractItfDerivedRelation(AbstractInterfaceDef base,AbstractInterfaceDef derived){
//	    Iterator it=base.getBaseRelation().iterator();
//	    List derivedList=derived.getDerivedRelation(); 
//	    while(it.hasNext()){
//	        if(derivedList.contains(it.next()))return false;
//	    }
//	    it=derived.getBaseRelation().iterator();
//	    derivedList=base.getDerivedRelation();
//	    while(it.hasNext()){
//	        if(derivedList.contains(it.next()))return false;
//	    }
//	    return true;
//	}

	private InterfaceDefNodeEditPart getInterfaceDefEditPart(){
	    return (InterfaceDefNodeEditPart) getHost();
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
