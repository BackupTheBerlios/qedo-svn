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


import java.util.List;

import org.eclipse.draw2d.ConnectionAnchor;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.ConnectionEditPart;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.NodeEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.requests.ChangeBoundsRequest;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.CCMModelPackage;
import CCMModel.HomeDef;
import CCMModel.Node;
import ccm.commands.create.visual.adds.AddOperationDefCommand;
import ccm.commands.delete.visual.DeleteHomeCommand;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.edit.policy.HomeDefEditPolicy;
import ccm.figures.HomeDefFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.AbstractIntefacefPropertySource;
import ccm.property.HomeDefPropertySource;
import ccm.request.AddFactoryRequest;

/**
 * <br/>
 * @author eduardw
 */
public class HomeDefNodeEditPart
	extends ContainerNodeEditPart implements NodeEditPart{


	 /**
     * Creates a new  instance.
     * @param node
     */
    public HomeDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public HomeDefNodeEditPart(){}
	
	public HomeDef getHome(){
		return (HomeDef)((Node) getModel()).getContained();
	}
    	

    /**
     * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
     */
    protected void createEditPolicies() {
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
		installEditPolicy( EditPolicy.GRAPHICAL_NODE_ROLE, new HomeDefEditPolicy() );
        super.createEditPolicies();
    }
	
	public HomeDefFigure getHomefFigure(){
		return (HomeDefFigure) getFigure();
	}
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		getHomefFigure().setName(getHome().getIdentifier());
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
		HomeDefFigure figure=new HomeDefFigure();
		return figure;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.HOME_DEF:	
			case CCMNotificationImpl.CONTAINED:
				refreshVisuals();
				break;
			default:
			    featureId=notification.getFeatureID(CCMModelPackage.class);
				switch(featureId){
				case CCMModelPackage.NODE__CON_SOURCE:
				    refreshSourceConnections();
					break;
				case CCMModelPackage.NODE__CONN_TARGET:
				    refreshTargetConnections();
					break;
				default:
					super.notifyChanged(notification); 
				}	
		}		
	}
	
    /**
     * @see org.eclipse.gef.editparts.AbstractEditPart#addChildVisual(org.eclipse.gef.EditPart, int)
     */
    protected void addChildVisual(EditPart childEditPart, int index) {
            super.addChildVisual(childEditPart, -1);
    }
	
	/**
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
			propertySource = new HomeDefPropertySource( getModelNode().getContained() );
		return propertySource;
	}
	
	   /**
     * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
     */
    public ConnectionAnchor getSourceConnectionAnchor(ConnectionEditPart connection) {
        return getHomefFigure().getIncomingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
     */
    public ConnectionAnchor getTargetConnectionAnchor(ConnectionEditPart connection) {
        return getHomefFigure().getOutgoingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.Request)
     */
    public ConnectionAnchor getSourceConnectionAnchor(Request request) {
        return getHomefFigure().getIncomingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.Request)
     */
    public ConnectionAnchor getTargetConnectionAnchor(Request request) {
        return getHomefFigure().getOutgoingConnectionAnchor();
    }
    
    /**
     * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#getModelSourceConnections()
     */
    protected List getModelSourceConnections() {
        return getModelNode().getConSource();
    }
    
    /**
     * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#getModelTargetConnections()
     */
    protected List getModelTargetConnections() {
        return getModelNode().getConnTarget();
    }
    
    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {
        return getHomefFigure().getFiguresPanel();
    }
    
	/**
	 * @see org.eclipse.gef.EditPart#understandsRequest(org.eclipse.gef.Request)
	 */
	public boolean understandsRequest(Request req) {
	    if (req instanceof AddFactoryRequest)
	    	return true;
	    else { 
	        return super.understandsRequest(req);
	    }
	}

	/**
	* @see org.eclipse.gef.EditPart#getCommand(org.eclipse.gef.Request)
	*/
	public Command getCommand(Request request) {
		if(request.getType().equals(RequestConstants.REQ_DELETE))
			return new DeleteHomeCommand (getModelNode());
		if (request instanceof AddFactoryRequest) 
			return new AddOperationDefCommand();
		else if(request instanceof ChangeBoundsRequest
				&& request.getType().equals(RequestConstants.REQ_ADD))
			return null;
		else
			return super.getCommand(request);
	}
}