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
package ccm.edit;


import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.EditPolicy;

import CCMModel.Node;
import ccm.edit.policy.ModelEditPolicy;
import ccm.model.CCMNotificationImpl;

/**
 * Class       :ContainedNodeEditPart<br/>
 * @author eduardw
 */
public abstract class ContainedNodeEditPart
	extends CCMAbstractGraphicalEditPart{


	 /**
     * Creates a new  instance.
     * @param node
     */
    public ContainedNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public ContainedNodeEditPart(){}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
	}
	
	
	/**
	* 
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/

	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.TYPEDEF_DEF:	
			case CCMNotificationImpl.CONTAINED:
				refreshVisuals();
				break;	
		}
		super.notifyChanged(notification);
	}
	
}