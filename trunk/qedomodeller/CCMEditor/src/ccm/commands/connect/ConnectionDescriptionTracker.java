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

import org.eclipse.gef.EditPart;
import org.eclipse.gef.tools.DragEditPartsTracker;

import ccm.edit.RelationEditPart;


/**
 * Class       :AssociationEndRoleTracker<br/>
 * Package     : vocleditor.commands.connect<br/>
 * Project     : VOCLEditor<br/>
 * Created On  : 22.05.2004<br/>
 * Description : Tracker to provide moving of AssociationEndRole
 * <br/>
 * @author vilapower
 */
public class ConnectionDescriptionTracker extends DragEditPartsTracker
{

	RelationEditPart connection;

	public ConnectionDescriptionTracker(EditPart source, RelationEditPart connection)
	{
		super(source);
		this.connection = connection;
	}

	protected EditPart getTargetEditPart()
	{
		return connection;
	}


}
