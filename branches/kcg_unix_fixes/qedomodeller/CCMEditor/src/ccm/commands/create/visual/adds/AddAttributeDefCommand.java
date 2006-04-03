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

import CCMModel.AttributeDef;
import CCMModel.Node;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;



public class AddAttributeDefCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "CreateParameterCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private AttributeDef attributeD;
	
	private boolean isReadonly=false;
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public AddAttributeDefCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container!=null && newObject!=null)return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    attributeD = (AttributeDef) newObject;
		attributeD.setIsReadonly(isReadonly);
		setIDLTyped(attributeD,idlTemplate);
	    
	    Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	attributeD.getNode().add(opNode);
	    	/*opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);*/
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.ATTRIBUTE_DEF, null, null,0));
	    }
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
		if (opNode!=null) {
			opNode.setContained(attributeD);
			parentNode.getContents().add(opNode);
		}
		super.redo();
		setIDLTyped(attributeD,idlTemplate);
	}
	
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {
		if (opNode!=null) {
			opNode.setContained(null);
			parentNode.getContents().remove(opNode);
		}
		unSetIDLTyped(attributeD,idlTemplate);
		super.undo();
	}

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}

	public boolean isReadonly() {
		return isReadonly;
	}
	
	public void setParentNode(Node parentNode) {
		this.parentNode = parentNode;
	}


	public void setReadonly(boolean isRead) {
		this.isReadonly = isRead;
	}


    /**
     * @param idlTemplate The idlTemplate to set.
     */
    public void setIdlTemplate(IDLTemplate idlTemplate) {
        this.idlTemplate = idlTemplate;
    }
}
