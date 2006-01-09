/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 @author Siegercn
 * 
 */
package ccm.commands.create.visual.adds;


import java.util.Iterator;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.ComponentInstantiation;
import CCMModel.ElementName;
import CCMModel.HomeInstantiation;
import CCMModel.Implementation;
import CCMModel.Node;
import CCMModel.Property;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;



public class AddPropertyCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "AddPropertyCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private Property property;
	private ElementName el_name;
	private String value,type;
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public AddPropertyCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container instanceof Implementation
				||container instanceof ComponentInstantiation
				||container instanceof HomeInstantiation) 
			return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    if(container instanceof Implementation)
	    ((Implementation)container).getPropertys().add(newObject);
	    if(container instanceof ComponentInstantiation)
		    ((ComponentInstantiation)container).getPropertys().add(newObject);
	    if(container instanceof HomeInstantiation)
		    ((HomeInstantiation)container).getPropertys().add(newObject);
	    property = (Property) newObject;
		property.setEl_name(el_name);
		property.setType(type);
		property.setValue(value);
		 
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	property.getNode().add(opNode);
	    	opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.ATTRIBUTE_DEF, null, null,0));
	    }
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
	    if (parentNode!=null) {
	    	opNode.setContained(property);
	    	parentNode.getContents().add(opNode);
	    }
		super.redo();
		 
	}
	
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {	
	    if (parentNode!=null) {
	    	opNode.setContained(null);
	    	parentNode.getContents().remove(opNode);
	    }
		 
		super.undo();
	}

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}

	public void setName(ElementName name) {
		this.el_name = name;
	}
	public void setValue(String value) {
		this.value = value;
	}
	public void setType(String type) {
		this.type =type;
	}
 
    /**
     * @return Returns the parentNode.
     */
    public Node getParentNode() {
        return parentNode;
    }
    /**
     * @param parentNode The parentNode to set.
     */
    public void setParentNode(Node parentNode) {
        this.parentNode = parentNode;
    }
    /**
     * @return Returns the idlTemplate.
     */
    
}
  