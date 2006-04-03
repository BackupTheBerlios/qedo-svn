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



import org.eclipse.draw2d.geometry.Rectangle;

import CCMModel.Node;
import CCMModel.View;



public abstract class CreateNodeForContainerCommand extends CreateNodeForContainedCommand{
	
	protected Node node;
	protected Rectangle rectangle;
	protected View view;


	
	
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForContainerCommand() {
		super();
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (newObject !=null &
			container !=null &
			view !=null)return true;
		return false;
	}
	
	/**
	 * The execution of this command creates a new Contained
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
		node=factory.createNode();
		newObject.getNode().add(node);
		node.setContained(newObject);
		view.getNode().add(node);
	    node.setX(rectangle.x);
	    node.setY(rectangle.y);
	    node.setWidth(rectangle.width);
	    node.setHeight(rectangle.height);
	}
	
	
	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
		newObject.getNode().add(node);
		view.getNode().add(node); 
		super.redo();
		
	}
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {
	    newObject.getNode().remove(node);
		view.getNode().remove(node); 
		super.undo();
	}



	public void setView(View view) {
		this.view = view;
	}

	public void setRectangle(Rectangle rectangle) {
		this.rectangle = rectangle;
	}
}
