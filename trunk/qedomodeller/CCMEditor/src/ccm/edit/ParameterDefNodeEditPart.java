/**
 * (c) Copyright group CCM
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


import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;

import CCMModel.Node;
import CCMModel.ParameterDef;
import ccm.edit.policy.CCMNodeXYLayoutEditPolicy;
import ccm.edit.policy.ModelEditPolicy;
import ccm.model.CCMNotificationImpl;

/**
 * @author ccm
 */
public class ParameterDefNodeEditPart
	extends CCMAbstractGraphicalEditPart{


	 /**
     * Creates a new  instance.
     * @param node
     */
    public ParameterDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public ParameterDefNodeEditPart(){}
	
    
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new CCMNodeXYLayoutEditPolicy());
	}
    
	public ParameterDef getParameter(){
		return (ParameterDef)((Node) getModel()).getTyped();
	}
    	
	public Label getParameterDefFigure(){
		return (Label) getFigure();
	}
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		getParameterDefFigure().setText(getParameter().getIdentifier());
		((GraphicalEditPart) getParent()).setLayoutConstraint(
			this,
			getFigure(),
			null);
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
	    //ParameterDefFigure figure=new ParameterDefFigure();
	    Label fig=new Label();
		return fig;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.PARAMETER_DEF:	
				refreshVisuals();
				break;
		}		
		super.notifyChanged(notification);
	}
	
}