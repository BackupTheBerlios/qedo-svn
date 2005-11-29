/*
 * Created on 25.03.2005
 *
 * 
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.edit;

import java.util.LinkedList;
import java.util.List;

import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editparts.AbstractConnectionEditPart;

import CCMModel.Connection;
import CCMModel.ConnectionDiscription;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.delete.visual.DeleteConnectionCommand;
import ccm.edit.policy.EdgeEndpointEditPolicy;
import ccm.edit.policy.EdgeRoleEditPolicy;
import ccm.edit.policy.EdgeSelectionHandlesEditPolicy;

/**
 * @author eduardw
 *
 * 
 * Window - Preferences - Java - Code Style - Code Templates
 */
public abstract class RelationEditPart  extends AbstractConnectionEditPart{


	private Notifier target;

	public RelationEditPart(Object link) {
		super();
		setModel(link);
	}

	protected Connection getCCMConnection(){
	    return (Connection) getModel();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy( EditPolicy.CONNECTION_ENDPOINTS_ROLE, new EdgeEndpointEditPolicy() );
		installEditPolicy( EditPolicy.CONNECTION_BENDPOINTS_ROLE, new EdgeSelectionHandlesEditPolicy() );
		installEditPolicy( EditPolicy.CONNECTION_ROLE, new EdgeRoleEditPolicy());

	}
	
    /**
     * @see org.eclipse.gef.editparts.AbstractEditPart#getModelChildren()
     */
    protected List getModelChildren() {
        List list=new LinkedList();
        ConnectionDiscription d=getCCMConnection().getConnectionDiscription();
        if(d!=null)
            list.add(d);
        return list;
    }
    
	/* (non-Javadoc)
	 * @see org.eclipse.gef.EditPart#getCommand(org.eclipse.gef.Request)
	 */
	public Command getCommand(Request request) {
		if(request.getType().equals(RequestConstants.REQ_DELETE)){
			 
			return new DeleteConnectionCommand((ConnectionImpl)getModel(),true);
		}
	else
		return super.getCommand(request);
	}
}

