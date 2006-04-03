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


import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.swt.graphics.Image;

import CCMModel.Node;
import CCMModel.UnionField;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;
import ccm.edit.policy.CCMNodeXYLayoutEditPolicy;
import ccm.edit.policy.ModelEditPolicy;
import ccm.model.CCMNotificationImpl;

/**
 * @author aduardw
 */
public class UnionFieldNodeEditPart
	extends CCMAbstractGraphicalEditPart{


	 /**
     * Creates a new  instance.
     * @param node
     */
    public UnionFieldNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public UnionFieldNodeEditPart(){}
	
    
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new CCMNodeXYLayoutEditPolicy());
	}
    
	public UnionField getField(){
		return (UnionField)((Node) getModel()).getTyped();
	}
    	
	public Label getFieldDefFigure(){
		return (Label) getFigure();
	}
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		getFieldDefFigure().setText(getField().getIdentifier()+"("+getField().getLabel()+")");
		((GraphicalEditPart) getParent()).setLayoutConstraint(
			this,
			getFigure(),
			null);
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
	    Label fig=new Label("",new Image(null, 
                CCMEditorPlugin.class.getResourceAsStream(ProjectResources.MEMBER_S)));
	    fig.setBorder(new LineBorder(ColorConstants.black,1));
		return fig;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.UNION_FIELD:	
				refreshVisuals();
				break;
		}		
		super.notifyChanged(notification);
	}
	
}