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


import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.ComponentFeature;
import CCMModel.ComponentInstantiation;
import CCMModel.FinderServiceKind;
import CCMModel.Node;
import CCMModel.RegisterComponentInstance;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
 

public class AddRegisterComponentInstanceCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "AddRegisterComponentInstanceCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private RegisterComponentInstance registerInstance;
	private FinderServiceKind service;
	private String regName;
	private ComponentFeature feature;
	//private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public AddRegisterComponentInstanceCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container==null ||!(container instanceof ComponentInstantiation)) return false;
		return true;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    registerInstance = (RegisterComponentInstance) newObject;
		registerInstance.setRegName(regName);
		registerInstance.setService(service);
		registerInstance.setFeature(feature);
	    ((ComponentInstantiation)container).getRegistration().add(newObject);
		 
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	registerInstance.getNode().add(opNode);
	    	opNode.setX(5);
	    	opNode.setY(5);
	    	opNode.setWidth(50);
	    	opNode.setHeight(30);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.RegisterComponentInstance, null, null,0));
	    }
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
	    if (parentNode!=null) {
	    	opNode.setContained(registerInstance);
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

	public void setregName(String name) {
		this.regName = name;
	}
	public void setService(FinderServiceKind service) {
		this.service = service;
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
    public void setFeature(ComponentFeature feature ){
    	this.feature=feature;
    }
    public List getComponentfeatures(){
    	List features= new ArrayList();
    	features.add(((ComponentInstantiation)container).getType().getComponent());
    	features.addAll(((ComponentInstantiation)container).getFacet());
    	features.addAll(((ComponentInstantiation)container).getReceptacle());
    	features.addAll(((ComponentInstantiation)container).getConsumess());
    	features.addAll(((ComponentInstantiation)container).getPublishesDef());
    	features.addAll(((ComponentInstantiation)container).getEmitss());
    	features.addAll(((ComponentInstantiation)container).getSinkss());
    	features.addAll(((ComponentInstantiation)container).getSiSouss());
    	features.addAll(((ComponentInstantiation)container).getSourcess());
    	return features;
    }
    
}
 