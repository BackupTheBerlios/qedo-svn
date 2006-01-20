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
package ccm.edit.policy;



import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.NonResizableEditPolicy;
import org.eclipse.gef.requests.ChangeBoundsRequest;

import CCMModel.ConnectionDiscription;
import ccm.commands.connect.MoveConnectionDescriptionCommand;
import ccm.edit.ConnectionDescriptionEditPart;
import ccm.edit.CCMRelationEditPart;



public class ConnectionDescriptionMovePolicy extends NonResizableEditPolicy
{
	public Command getMoveCommand(ChangeBoundsRequest request)
	{	
		if (request.getEditParts().get(0) instanceof ConnectionDescriptionEditPart)
		{	
			ConnectionDiscription model = (ConnectionDiscription)getHost().getModel();
			Point delta = request.getMoveDelta();
			MoveConnectionDescriptionCommand command =
				new MoveConnectionDescriptionCommand(model, getParentFigure(), delta);
			return command;
		}
		return null;	 
	}

	public Figure getParentFigure()
	{
		CCMRelationEditPart edge = (CCMRelationEditPart)getHost().getParent();
		return (Figure) edge.getFigure();
	}

}
