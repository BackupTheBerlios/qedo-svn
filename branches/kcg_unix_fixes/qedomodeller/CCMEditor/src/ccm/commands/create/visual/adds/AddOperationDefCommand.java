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
package ccm.commands.create.visual.adds;


import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.Node;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;
import ccm.model.template.ParameterTemplate;



public class AddOperationDefCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "CreateParameterCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private OperationDef operation;
	
	private boolean isOneway = true;
	private String context = "";
	private List parameters = new LinkedList();
	private IDLTemplate idlTemplate = new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public AddOperationDefCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container!=null && newObject!=null) return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    operation = (OperationDef) newObject;
		operation.setIsOneway(isOneway);
		operation.setContext(context);		
		setIDLTyped(operation,idlTemplate);
	
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	operation.getNode().add(opNode);
	    	opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.OPERATION_DEF, null, null,0));
			//addparamNodes(opNode);
	    }
	    addParameters();
	}
	
	
	
	private void addParameters(){
	    operation.getParameters().clear();
	    Iterator it=parameters.iterator();
	    while(it.hasNext()){
	        ParameterTemplate p=(ParameterTemplate) it.next();
	        ParameterDef paramDef=factory.createParameterDef();
	        
	        paramDef.setDirection(p.getMode());
	        paramDef.setIdentifier(p.getIdentifier());
	        setIDLTyped(paramDef,p.getIdlType());
			operation.getParameters().add(paramDef);
	    }
	}
	
	private void addparamNodes(Node opNode) {
		Iterator it = operation.getParameters().iterator();
		while(it.hasNext()) {
			ParameterDef paramDef = (ParameterDef) it.next();
	        if (parentNode==null) continue;
	        Node node=factory.createNode();
	        paramDef.getNodeFromTyped().add(node);
			node.setX(0);
			node.setY(0);
			node.setWidth(-1);
			node.setHeight(-1);
			opNode.getContents().add(node);
			node.eNotify(new CCMNotificationImpl(node, Notification.ADD,
				       							   CCMNotificationImpl.PARAMETER_DEF, null, null,0));	
	    }
        if (parentNode!=null) {
        	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			                                   CCMNotificationImpl.OP_PARAMETERS, null, null,0));
        }
	}

	private void deleteParameters(){
	    Iterator it=operation.getParameters().iterator();
	    int i=0;
	    while(it.hasNext()){
	        ParameterDef paramDef=(ParameterDef) it.next();
	        ParameterTemplate p=(ParameterTemplate)parameters.get(i);
	        unSetIDLTyped(paramDef,p.getIdlType());
	        if (parentNode==null) continue;
	        opNode.getContents().removeAll(paramDef.getNodeFromTyped());
	        paramDef.getNodeFromTyped().clear();
	        i=i+1;
	    }
        if (parentNode!=null) {
        	operation.getParameters().clear();
        	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			       CCMNotificationImpl.OP_PARAMETERS, null, null,0));
        }
	}
	

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}
	
	public void setParentNode(Node parentNode) {
		this.parentNode = parentNode;
	}

	public String getContext() {
		return context;
	}
	

	public void setContext(String context) {
		this.context = context;
	}
	
	

	public boolean isOneway() {
		return isOneway;
	}

	public void setOneway(boolean isOneway) {
		this.isOneway = isOneway;
	}

    /**
     * @return Returns the parameters.
     */
    public List getParameters() {
        return parameters;
    }
    /**
     * @param parameters The parameters to set.
     */
    public void setParameters(List parameters) {
        this.parameters.clear();
        this.parameters.addAll(parameters);
    }

    /**
     * @param idlTemplate The idlTemplate to set.
     */
    public void setIdlTemplate(IDLTemplate idlTemplate) {
        this.idlTemplate = idlTemplate;
    }
}
