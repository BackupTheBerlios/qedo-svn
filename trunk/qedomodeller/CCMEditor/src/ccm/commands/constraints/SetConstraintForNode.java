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
package ccm.commands.constraints;

import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;

import CCMModel.Node;



/**
 * The <code>SetConstraintCommand</code> allows WorkflowElements to be moved and resized
 * @author ddean
 *
 */
public class SetConstraintForNode
	extends org.eclipse.gef.commands.Command
{
	private static final String Command_Label_Location = "change location command";
	private static final String Command_Label_Resize = "resize command";
	
	private Point newPos;
	private Point oldPos;
	private Node part;
	
	private Dimension newSize=new Dimension(0,0);
	private Dimension oldSize=new Dimension(0,0);
	
	/**
	 * Execution of this command node and resizes 
	 * a constraint
	 */
	public void execute() {
		oldPos  = new Point( part.getX(), part.getY() );

		if(!oldSize.equals(newSize)){
			oldSize = new Dimension(part.getWidth(),part.getHeight());	
			part.setWidth(newSize.width);
			part.setHeight(newSize.height);
		}
		part.setX(newPos.x);
		part.setY(newPos.y);
	}
	
	/**
	 * Returns the label for this command
	 * as string-value
	 */
	public String getLabel(){
		return Command_Label_Resize;
	}
	
	/**
	 * Redos a previous undone action
	 */
	public void redo() {
		if(!oldSize.equals(newSize)){
			part.setWidth(newSize.width);
			part.setHeight(newSize.height);
		}
		part.setX(newPos.x);
		part.setY(newPos.y);
	}
	
	/**
	 * Sets the location of the node
	 * @param r - a rectangle holding the new location
	 */
	public void setRectangle(Rectangle r){
		setLocation(r.getLocation());
		newSize=r.getSize();
	}

	/**
	 * Sets the location of the node
	 * @param p - a point holding the new location
	 */	
	public void setLocation(Point p) {
		newPos = p;
	}
	
	/**
	 * Sets a new part to layout
	 * @param part - a constraint
	 */
	public void setPart(Node part) {
		this.part = part;

	}
	

	/**
	 * Invalidates an action previously done
	 * by this command.
	 */
	public void undo() {
		if(!oldSize.equals(newSize)){
			part.setWidth(oldSize.width);
			part.setHeight(oldSize.height);	
		}
		part.setX(oldPos.x);
		part.setY(oldPos.y);
	}

}
