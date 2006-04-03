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
package ccm.commands.connect;


import java.util.ArrayList;
import java.util.List;

import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.gef.commands.Command;

import CCMModel.ConnectionDiscription;

/**
 * Class       :MoveAssociationEndRoleCommand<br/>
 * Package     : vocleditor.commands.connect<br/>
 * Project     : VOCLEditor<br/>
 * Created On  : 22.05.2004<br/>
 * Description : Command to move AssociationEndRole
 * <br/>
 * @author vilapower
 */
public class MoveConnectionDescriptionCommand extends Command{
	private List otherviews =new ArrayList();
	private List connections =new ArrayList();
	private ConnectionDiscription label = null;
	private Point location = null;
	private Figure parent = null;
	private Point oldOffset = new Point();

	/**
	 * @param label model as AssociationEndRole
	 * @param parent Figure that contains the figure of AssociationEndRole<br/>
	 * @param location locationspoint
	 */
	public MoveConnectionDescriptionCommand(ConnectionDiscription label, Figure parent, Point location){
		this.label = label;
		this.parent = parent;
		this.location = location;
	}

	/**
	* @see org.eclipse.gef.commands.Command#execute()
	*/
	public void execute(){
		oldOffset = new Point(label.getX(), label.getY());
		Point newOffset = oldOffset.getCopy();
		parent.translateToAbsolute(newOffset);
		newOffset.translate(location);
		parent.translateToRelative(newOffset);
		label.setX(newOffset.x);
		label.setY(newOffset.y);
	}

	/**
	* @see org.eclipse.gef.commands.Command#redo()
	*/
	public void redo(){
		execute();
	}
	
	/**
	* @see org.eclipse.gef.commands.Command#undo()
	*/
	public void undo(){
		label.setX(oldOffset.x);
		label.setY(oldOffset.y);
	}
}
