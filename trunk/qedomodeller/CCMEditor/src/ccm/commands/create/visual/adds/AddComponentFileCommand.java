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
import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.Assembly;
import CCMModel.ComponentFile;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.SoftwarePackage;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;



public class AddComponentFileCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "AddComponentFileCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private ComponentFile compFile;
	private SoftwarePackage pkg;
	private String location,fileName ;
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public AddComponentFileCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container==null ||!(container instanceof Assembly)) return false;
		
		return true;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    ((Assembly)container).getConfig().getComponentFile().add(newObject);
	    compFile = (ComponentFile) newObject;
		compFile.setLocation(location);
		compFile.setName(fileName);
		compFile.setPackage(pkg);
		 
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	compFile.getNode().add(opNode);
	    	/*opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);*/
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.CONTAINEDFILE, null, null,0));
	    }
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
	    if (parentNode!=null) {
	    	opNode.setContained(compFile);
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

	public void setFileName(String usage) {
		this.fileName = usage;
	}
	public void setlocation(String location) {
		this.location = location;
	}
	public void setPackage(SoftwarePackage pkg) {
		this.pkg =pkg;
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
    public Assembly getContainer() {
        return (Assembly)container;
    }
    public List getPackages(){
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=mf.getRootModule(container);
    	List packages=mf.getAllContained(root,SoftwarePackage.class);
    	return packages;
    }
    
}
  
