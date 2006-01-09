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

import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy;
import org.eclipse.gef.requests.CreateConnectionRequest;
import org.eclipse.gef.requests.ReconnectRequest;
import org.eclipse.swt.widgets.Shell;

import CCMModel.ConsumesDef;
import CCMModel.EventPortDef;
import CCMModel.Node;
import CCMModel.ProvidesDef;
import CCMModel.SiSouDef;
import CCMModel.SinkDef;
import CCMModel.UsesDef;
import CCMModel.View;
import ccm.commands.connect.EventConnectCommand;
import ccm.commands.connect.EventPortEventConnectCommand;
import ccm.commands.connect.InterfaceConnectCommand;
import ccm.commands.connect.ProvidesItfConnectCommand;
import ccm.commands.connect.StreamConnectCommand;
import ccm.commands.connect.UsesItfConnectCommand;
import ccm.edit.PortLabelEditPart;
import ccm.model.template.RelationTemplate;





public class ModelNodeRoleEditPolicy extends GraphicalNodeEditPolicy {

  private  Shell shell;

	public ModelNodeRoleEditPolicy() {
		super();
	}

	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCompleteCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 */
	 
	
	protected Node getModelNode() {
		return (Node)getHost().getModel();
	}


	protected PortLabelEditPart getModelNodeEditPart() {
		return (PortLabelEditPart)getHost();
	}
	
	/**
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getConnectionCreateCommand(org.eclipse.gef.requests.CreateConnectionRequest)
	 */
	protected Command getConnectionCreateCommand(CreateConnectionRequest request) {
	    if(request.getNewObject() instanceof RelationTemplate){
	        RelationTemplate rel =(RelationTemplate) request.getNewObject();
	        Object obj=getModelNode().getContained();
	        if(rel.getKind()==3 && obj instanceof UsesDef){
	            UsesDef use=(UsesDef) obj;
	            //if(use.getInterfaceRelation()!=null) return null;
		        UsesItfConnectCommand command = new UsesItfConnectCommand();
		        command.setView((View) getModelNodeEditPart().getParent().getModel());
		        command.setSource(getModelNodeEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
	        }else if(rel.getKind()==3 && obj instanceof ProvidesDef){
	        	ProvidesDef prov=(ProvidesDef) obj;
	           // if(prov.getInterfaceRelation()!=null) return null;
	            if(prov.getInterface()!=null)
	            	return null;
	            ProvidesItfConnectCommand command = new ProvidesItfConnectCommand();
		        command.setView((View) getModelNodeEditPart().getParent().getModel());
		        command.setSource(getModelNodeEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
	        }else if(rel.getKind()==4 && obj instanceof EventPortDef){
	            EventPortDef port=(EventPortDef) obj; 
	            if(port.getEvent()!=null)return null;
	            EventPortEventConnectCommand command = new EventPortEventConnectCommand();
	            command.setView((View) getModelNodeEditPart().getParent().getModel());
		        command.setSource(getModelNodeEditPart().getModelNode());
		        request.setStartCommand(command);
		        return command;
	         
	        
	        
	        }else if(rel.getKind()==7 && obj instanceof UsesDef){
	        //	UsesDef receptcal=(UsesDef) obj;
	        	InterfaceConnectCommand command = new InterfaceConnectCommand();
	        	command.setView((View) getModelNodeEditPart().getParent().getParent().getParent().getModel());
	        	command.setSource(getModelNodeEditPart().getModelNode());
	        	request.setStartCommand(command);
	        	return command;
	        }else if(rel.getKind()==7 && obj instanceof ConsumesDef){
	        	//ConsumesDef consum=(ConsumesDef) obj;
	        	EventConnectCommand command = new EventConnectCommand();
	        	command.setView((View) getModelNodeEditPart().getParent().getParent().getParent().getModel());
	        	command.setSource(getModelNodeEditPart().getModelNode());
	        	request.setStartCommand(command);
	        	return command;
	        }else if(rel.getKind()==7 && (obj instanceof SinkDef||obj instanceof SiSouDef)){
	        	//UsesDef receptcal=(UsesDef) obj;
	        	StreamConnectCommand command = new StreamConnectCommand();
	        	command.setView((View) getModelNodeEditPart().getParent().getParent().getParent().getModel());
	        	command.setSource(getModelNodeEditPart().getModelNode());
	        	request.setStartCommand(command);
	        	return command;
	        }
	 
	    }
		return null;
	   
	}

	
	protected Command getConnectionCompleteCommand(CreateConnectionRequest request) {
		if(request.getStartCommand() instanceof InterfaceConnectCommand ){
			InterfaceConnectCommand command = (InterfaceConnectCommand)request.getStartCommand();
			command.setTarget(getModelNodeEditPart().getModelNode());
			shell=getHost().getViewer().getControl().getShell();
			command.setShell(shell);
	        
			return command;
	      
		}else if(request.getStartCommand() instanceof EventConnectCommand){
			EventConnectCommand command = (EventConnectCommand)request.getStartCommand();
			command.setTarget(getModelNodeEditPart().getModelNode());
			shell=getHost().getViewer().getControl().getShell();
			command.setShell(shell);
			return command;
	  
		}else if(request.getStartCommand() instanceof StreamConnectCommand){
			StreamConnectCommand command = (StreamConnectCommand)request.getStartCommand();
			command.setTarget(getModelNodeEditPart().getModelNode());
			shell=getHost().getViewer().getControl().getShell();
			command.setShell(shell);
			return command;
        }
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
}
