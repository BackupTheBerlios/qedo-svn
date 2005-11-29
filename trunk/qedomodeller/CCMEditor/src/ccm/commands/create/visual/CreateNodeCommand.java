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
package ccm.commands.create.visual;


import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;

import CCMModel.CCMModelFactory;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.Node;
import CCMModel.View;



public class CreateNodeCommand
	extends org.eclipse.gef.commands.Command
{
	private static final String	CreateCommand_LabelSimple = "CreateClassifierRoleCommand";
	private static final String	CreateCommand_LabelColl = "CreateCollClassifierRoleCommand";
	
	private Node node;
	private Point loc;
	private Dimension dim;
	private View parent;
	private Container modelParent;
	private Contained modelObject;
	
	private String nameOfNode;
	private String typeOfNode;
	
	private CCMModelFactory factory=CCMModelManager.getFactory();
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeCommand() {
		super();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (modelObject !=null &
			modelParent !=null &
			parent !=null)return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
		node=factory.createNode();
		modelObject.getNode().add(node);
		modelObject.setIdentifier("");
		parent.getNode().add(node);
	    node.setX(loc.x);
	    node.setY(loc.y);
	    node.setWidth(145);
	    node.setHeight(30);
	    modelParent.getContents().add(modelObject);
	    modelObject.setDefinedIn(modelParent);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
										     CCMNotificationImpl.MODULE_DEF, null, null,0));
	}
	
	
	/**
	 * Getter for the container, where this node is nested in
	 * @return - the View where this node is nested in
	 */
	public View getParent() {
		return parent;
	}
	
	
	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
		parent.getNode().add(node); 
	}
	
	/**
	 * Sets a new location of a classifierNode
	 * @param loc - a rectangle holding the new location
	 */
	public void setConstraint (Rectangle r) {
		this.loc = r.getLocation();
		this.dim=r.getSize();
	}
	
	/**
	 * Sets the container, where the classifierNode 
	 * should be placed inside
	 * @param newParent - the new parent
	 */
	public void setParent(View newParent) {
		parent = newParent;
	}
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {	
		parent.getNode().remove(node);
	}
	

	/**
	 * Getter for the name of the created classifierRole
	 * @return - the string-value of the classifierRoles name
	 */
	public String getNameOfNode() {
		return nameOfNode;
	}

	/**
	 * Retrieves the type of the classifierRole
	 * @return - the string-value of the classfierRoles type.
	 */
	public String getTypeOfNode() {
		return typeOfNode;
	}

	/**
	 * Setter for the name of the classifierNode
	 * @param string - the new name
	 */
	public void setNameOfNode(String string) {
		nameOfNode = string;
	}

	/**
	 * Setter for the type of the classifierNode
	 * @param string - the new type as string-value
	 */
	public void setTypeOfNode(String string) {
		typeOfNode = string;
	}

	/**
	 * @return Returns the modelObject.
	 */
	public Contained getModelObject() {
		return modelObject;
	}
	/**
	 * @param modelObject The modelObject to set.
	 */
	public void setModelObject(Contained modelObj) {
		this.modelObject = modelObj;
	}
	/**
	 * @return Returns the modelParent.
	 */
	public Contained getModelParent() {
		return modelParent;
	}
	/**
	 * @param modelParent The modelParent to set.
	 */
	public void setModelParent(Container modelParent) {
		this.modelParent = modelParent;
	}

}
