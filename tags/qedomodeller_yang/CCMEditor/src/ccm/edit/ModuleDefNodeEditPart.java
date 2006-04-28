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


import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.ModuleDef;
import CCMModel.Node;
import ccm.commands.delete.visual.DeleteModuleCommand;
import ccm.figures.ModuleDefFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.ModuleDefPropertySource;

/**
 * @author eduardw
 */
public class ModuleDefNodeEditPart
	extends ContainerNodeEditPart{

	 /**
     * Creates a new  instance.
     * @param node
     */
    public ModuleDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public ModuleDefNodeEditPart(){}
	
	public ModuleDef getModule(){
		return (ModuleDef)((Node) getModel()).getContained();
	}
    	
	public ModuleDefFigure getModuleDefFigure(){
		return (ModuleDefFigure) getFigure();
	}
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		getModuleDefFigure().setName(getModule().getIdentifier());
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(
			this,
			getFigure(),
			r);
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		ModuleDefFigure figure=new ModuleDefFigure();
		return figure;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.MODULE_DEF:	
				refreshVisuals();
				break;
		}		
		super.notifyChanged(notification);
	}
	
	/**
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
			propertySource = new ModuleDefPropertySource( getModelNode().getContained() );
		return propertySource;
	}


	public Command getCommand(Request request) {
		if(request.getType().equals(RequestConstants.REQ_DELETE))
			return new DeleteModuleCommand((Node) getModel());
	else
		return super.getCommand(request);
	}
	

	public boolean understandsRequest(Request req) {
		if(req.getType().equals(RequestConstants.REQ_DELETE))
			return true;
		else
			return super.understandsRequest(req);
	}

	
}