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


import org.eclipse.draw2d.geometry.Rectangle;

import CCMModel.IDLFile;
import CCMModel.Node;
import CCMModel.SoftwarePackage;
import ccm.commands.create.visual.CreateNodeForContainedCommand;

public class AddIDLCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "AddIDLCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	private IDLFile file;
	private String location;
	
	/**
	 * Constructor of this command, 
	 */
	public AddIDLCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container==null ||!(container instanceof SoftwarePackage)) return false;
		return true;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    file = (IDLFile) newObject;
	    ((SoftwarePackage)container).setIdlFile(file);
		file.setName(this.identifier);
		file.setLocation(location);
		 
		//Iterator it = container.getNode().iterator();
	   // while(it.hasNext()) {
	   // 	parentNode = (Node) it.next();
	   // 	opNode=factory.createNode();
	   // 	file.getNode().add(opNode);
	    	/*opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);*/
	  //  	parentNode.getContents().add(opNode);
	  //  }
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
	    if (parentNode!=null) {
	    	opNode.setContained(file);
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

	 
	 
	public void setLocation(String location) {
		this.location =location;
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
  
