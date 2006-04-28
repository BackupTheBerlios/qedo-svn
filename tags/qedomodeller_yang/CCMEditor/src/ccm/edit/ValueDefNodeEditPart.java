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
import org.eclipse.draw2d.Label;
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
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.CCMModelPackage;
import CCMModel.EventDef;
import CCMModel.Node;
import CCMModel.ValueDef;
import ccm.ProjectResources;
import ccm.commands.create.visual.adds.AddAttributeDefCommand;
import ccm.commands.create.visual.adds.AddOperationDefCommand;
import ccm.commands.create.visual.adds.AddValueMemberDefCommand;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.edit.policy.ValueDefEditPolicy;
import ccm.figures.ContainerFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.EventDefPropertySource;
import ccm.property.ValueDefPropertySource;
import ccm.request.AddAttributeDefRequest;
import ccm.request.AddOperationDefRequest;
import ccm.request.AddValueMembertDefRequest;

/**
 * <br/>
 * @author eduardw
 */
public class ValueDefNodeEditPart
	extends ContainerNodeEditPart implements NodeEditPart{


	 /**
     * Creates a new  instance.
     * @param node
     */
    public ValueDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public ValueDefNodeEditPart(){}
	
	public ValueDef getValue(){
		return (ValueDef)((Node) getModel()).getContained();
	}
    	
	public ContainerFigure getValueFigure(){
		return (ContainerFigure) getFigure();
	}
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		getValueFigure().setIdentifier(getValue().getIdentifier());
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(
			this,
			getFigure(),
			r);
	}
	
    /**
     * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
     */
    protected void createEditPolicies() {
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
		installEditPolicy( EditPolicy.GRAPHICAL_NODE_ROLE, new ValueDefEditPolicy() );
        super.createEditPolicies();
    }
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
	    ContainerFigure opFigure=null;
	    if(getModelNode().getContained()instanceof EventDef)
	        opFigure=new ContainerFigure(getValue().getIdentifier(),ProjectResources.EVENT_S);
	    else 
	        opFigure=new ContainerFigure(getValue().getIdentifier(),ProjectResources.VALUE_S);
		return opFigure;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.VALUE_DEF:	
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
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
		    if(getModelNode().getContained() instanceof EventDef )
		    	propertySource = new EventDefPropertySource( getModelNode().getContained() );
			else
				propertySource = new ValueDefPropertySource( getModelNode().getContained() );
		return propertySource;
	}
	
	/**
	 * @see org.eclipse.gef.EditPart#understandsRequest(org.eclipse.gef.Request)
	 */
	public boolean understandsRequest(Request req) {
		if(req.getType().equals(RequestConstants.REQ_DELETE))
			return true;
	    if (req instanceof AddOperationDefRequest)
	    	return true;
	    else if (req instanceof AddValueMembertDefRequest)
	    	return true;
	    else if (req instanceof AddAttributeDefRequest)
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
			return new DeleteNodeCommand((Node) getModelNode(),((Node) getModelNode()).getView(),((Node) getModel()).getContained());
	    if (request instanceof AddOperationDefRequest) 
			return new AddOperationDefCommand();
		else if (request instanceof AddValueMembertDefRequest) 				
		    return new AddValueMemberDefCommand();
		else if (request instanceof AddAttributeDefRequest) 				
		    return new AddAttributeDefCommand();
		else
		    return super.getCommand(request);
	}
    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {
        return getValueFigure().getFiguresPanel();
    }
    
    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getLabelContentPane() {
        return getValueFigure().getPaneFigure();
    }
    /**
     * @see org.eclipse.gef.editparts.AbstractEditPart#addChildVisual(org.eclipse.gef.EditPart, int)
     */
    protected void addChildVisual(EditPart childEditPart, int index) {
    	IFigure child = ((GraphicalEditPart)childEditPart).getFigure();
        if (child instanceof Label){
        	getLabelContentPane().add(child, 0);
        }else
            super.addChildVisual(childEditPart, 0);
    }
    /**
     * @see org.eclipse.gef.GraphicalEditPart#setLayoutConstraint(org.eclipse.gef.EditPart, org.eclipse.draw2d.IFigure, java.lang.Object)
     */
    public void setLayoutConstraint(EditPart child, IFigure childFigure,
            Object constraint) {
       	IFigure childF = ((GraphicalEditPart)child).getFigure();
        if (childF instanceof Label)
            getLabelContentPane().setConstraint(childFigure, constraint);
		else
			super.setLayoutConstraint(child, childFigure, constraint);
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
     */
    public ConnectionAnchor getSourceConnectionAnchor(ConnectionEditPart connection) {
        return getValueFigure().getIncomingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
     */
    public ConnectionAnchor getTargetConnectionAnchor(ConnectionEditPart connection) {
        return getValueFigure().getOutgoingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.Request)
     */
    public ConnectionAnchor getSourceConnectionAnchor(Request request) {
        return getValueFigure().getIncomingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.Request)
     */
    public ConnectionAnchor getTargetConnectionAnchor(Request request) {
        return getValueFigure().getOutgoingConnectionAnchor();
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
}