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



public abstract class CreateNodeForTypedefDefCommand extends CreateNodeForContainedCommand{
	

	protected Node opNode;
	protected View view;
	protected Rectangle constraint;
	
	//protected TypedefDef typedefDef;
	
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForTypedefDefCommand() {
		super();
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (view !=null &
			container !=null &
			newObject !=null)return true;
		return false;
	}
	
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
//	    typedefDef=(TypedefDef) newObject;
		opNode=factory.createNode();
		newObject.getNode().add(opNode);
		opNode.setX(constraint.x);
		opNode.setY(constraint.y);
		opNode.setWidth(constraint.width);
		opNode.setHeight(constraint.height);
		view.getNode().add(opNode);
	}
	
	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
		opNode.setContained(newObject);
		view.getNode().add(opNode);
		super.redo();

	}
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {	
	    opNode.setContained(null);
		view.getNode().remove(opNode);
		super.undo();
	}

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}
	
	public void setView(View view) {
		this.view = view;
	}

}
