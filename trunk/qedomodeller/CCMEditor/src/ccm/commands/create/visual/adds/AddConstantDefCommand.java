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

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.ConstantDef;
import CCMModel.Node;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;



public class AddConstantDefCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "CreateConstantCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private ConstantDef constant;
	
	private String constValue="";
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public AddConstantDefCommand() {
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
	    constant=(ConstantDef) newObject;
    	constant.setConstValue(constValue);
		setIDLTyped(constant,idlTemplate);
	    
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	constant.getNode().add(opNode);
	    	opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.CONSTANT_DEF, null, null,0));
	    }
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
        if (parentNode!=null) {
        	opNode.setContained(constant);
        	parentNode.getContents().add(opNode);
        }
		super.redo();
		setIDLTyped(constant,idlTemplate);
	}
	
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {	
        if (parentNode!=null) {
        	opNode.setContained(null);
    		parentNode.getContents().remove(opNode);
        }
		unSetIDLTyped(constant,idlTemplate);
		super.undo();
	}

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}
	
	public void setParentNode(Node parentNode) {
		this.parentNode = parentNode;
	}

	public String getConstValue() {
		return constValue;
	}
	

	public void setConstValue(String context) {
		this.constValue = context;
	}

    /**
     * @param idlTemplate The idlTemplate to set.
     */
    public void setIdlTemplate(IDLTemplate idlTemplate) {
        this.idlTemplate = idlTemplate;
    }
    /**
     * @return Returns the idlTemplate.
     */
    public IDLTemplate getIdlTemplate() {
        return idlTemplate;
    }
}
