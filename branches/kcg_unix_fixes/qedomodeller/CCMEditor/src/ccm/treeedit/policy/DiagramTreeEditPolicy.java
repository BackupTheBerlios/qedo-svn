/*
 * Created on 09.06.2005
*/
package ccm.treeedit.policy;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy;
import org.eclipse.gef.requests.CreateConnectionRequest;
import org.eclipse.gef.requests.ReconnectRequest;

import ccm.request.AddDiagramRequest;

public class DiagramTreeEditPolicy extends GraphicalNodeEditPolicy {

	protected Command getConnectionCompleteCommand(
			CreateConnectionRequest request) {
		return null;
	}

	protected Command getConnectionCreateCommand(CreateConnectionRequest request) {
		return null;
	}

	protected Command getReconnectTargetCommand(ReconnectRequest request) {
		return null;
	}

	protected Command getReconnectSourceCommand(ReconnectRequest request) {
		return null;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.GraphicalNodeEditPolicy#getTargetEditPart(org.eclipse.gef.Request)
	 */
	public EditPart getTargetEditPart(Request request) {
		if(request instanceof AddDiagramRequest)
			return super.getTargetEditPart(request);
		return super.getTargetEditPart(request);
	}
}