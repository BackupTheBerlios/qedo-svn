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

import CCMModel.Node;
import CCMModel.ValueBoxDef;
import ccm.ProjectResources;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.figures.ContainedWithMembersFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.TypeDefPropertySource;

/**

 * <br/>
 * @author eduardw
 * 
 */
public class ValueBoxDefNodeEditPart extends ContainedNodeEditPart{

    
    private IPropertySource propertySource = null;
    
    /**
     * @param clr
     */
    public ValueBoxDefNodeEditPart(Node clr) {
        super(clr);
    }
    
    private ValueBoxDef getValueBox(){
        return (ValueBoxDef)((Node)getModel()).getContained();
    }
    
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
	    getTypedDefFigure().setIdentifier(getValueBox().getIdentifier());
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(-1,-1);	
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
	}

	private ContainedWithMembersFigure getTypedDefFigure(){
		return (ContainedWithMembersFigure) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
	   // Label l=new Label("",new Image(null, 
       //     	CCMEditorPlugin.class.getResourceAsStream(ProjectResources.VALUEBOX_S)));
	   // l.setBorder(new LineBorder(ColorConstants.black,1));
		ContainedWithMembersFigure opFigure=new ContainedWithMembersFigure(getValueBox().getIdentifier(),ProjectResources.VALUEBOX_S);
		return opFigure;
		//return l;
	}
	
	/**
     * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
     */
    public void notifyChanged(Notification notification) {
    	int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.CONTAINED:	
				refreshVisuals();
				break;
			default:
			    super.notifyChanged(notification);    
		}		

    }
	
	/**
	 * @see org.eclipse.core.runtime.IAdaptable#getAdapter(java.lang.Class)
	 */
	public Object getAdapter(Class key) {
		if (IPropertySource.class == key) {
			return getPropertySource();
		}
		return super.getAdapter( key );
	}
	
	/**
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
			propertySource = new TypeDefPropertySource( getModelNode().getContained() );
		return propertySource;
	} 
	
	public boolean understandsRequest(Request req) {
		if(req.getType().equals(RequestConstants.REQ_DELETE))
			return true;
	    else  
	        return super.understandsRequest(req);
	}

	
	public Command getCommand(Request request) {
		if(request.getType().equals(RequestConstants.REQ_DELETE))
			return new DeleteNodeCommand((Node) getModel(),((Node) getModel()).getView(),((Node) getModel()).getContained());
		else
		    return super.getCommand(request);
	}	
	
}