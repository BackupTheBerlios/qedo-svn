/*
 * Created on 24.03.2005
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
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.NodeEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.commands.Command;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.EventPortDef;
import CCMModel.Node;
import CCMModel.ProvidesDef;
import CCMModel.UsesDef;
import ccm.edit.policy.ModelEditPolicy;
import ccm.edit.policy.ModelNodeRoleEditPolicy;
import ccm.edit.policy.NodeXYLayoutEditPolicy;
import ccm.figures.PortLabel;
import ccm.figures.ReceptacleLabel;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;
import ccm.property.EventPortDefPropertySource;
import ccm.property.FacetPropertySource;
import ccm.property.ReceptaclePropertySource;

/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 *
 * @author Holger Kinscher
 */
public class PortLabelEditPart extends CCMAbstractGraphicalEditPart implements
		NodeEditPart {

	/* (non-Javadoc)
	 * @see org.eclipse.gef.EditPart#getCommand(org.eclipse.gef.Request)
	 */
	public Command getCommand(Request request) {
//		if(request.getType().equals(RequestConstants.REQ_DELETE))
	//			return new DeletePortCommand(this);
//		else
			return super.getCommand(request);
	}
	private IPropertySource propertySource = null;

	 /**
    * Creates a new  instance.
    * @param node
    */
   public PortLabelEditPart(Node clr){
		setModel(clr);
   }
	
   public PortLabelEditPart(){}
   	
	/**
	 * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
	 * Gets the source connection anchor of a Association Role. Returns the nearest anchor 
	 * if there is no connection or 
	 * 
	 */
	public ConnectionAnchor getSourceConnectionAnchor(ConnectionEditPart connection) { 	
		return ((PortLabel)getFigure()).getConnectionAnchor();
	}
	
	
	/**
	 * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.Request)
	 */
	public ConnectionAnchor getSourceConnectionAnchor(Request request) {		
		return ((PortLabel)getFigure()).getConnectionAnchor();
	}

	/**
	 * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
	 */
	public ConnectionAnchor getTargetConnectionAnchor(ConnectionEditPart connection) {
		return ((PortLabel)getFigure()).getConnectionAnchor();
	}
	

	/**
	 * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.Request)
	 */
	public ConnectionAnchor getTargetConnectionAnchor(Request request) {
		return ((PortLabel)getFigure()).getConnectionAnchor();
	}


	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#getModelSourceConnections()
	 */
	protected List getModelSourceConnections(){ 
		return getModelNode().getConSource();
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#getModelTargetConnections()
	 */
	protected List getModelTargetConnections() {
		return getModelNode().getConnTarget();
	}
	

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new NodeXYLayoutEditPolicy());
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.GRAPHICAL_NODE_ROLE, new ModelNodeRoleEditPolicy());
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
		   Contained contained=getModelNode().getContained();
		   if(contained instanceof ProvidesDef)
		   		propertySource = new FacetPropertySource(contained);
		   if(contained instanceof UsesDef)
		    	propertySource =  new ReceptaclePropertySource (contained);
		   if(contained instanceof EventPortDef)
		    	propertySource = new EventPortDefPropertySource(contained);
		 
			//propertySource = new ContainedPropertySource( getModelNode().getContained() );
		
		return propertySource;
	}


	/* (non-Javadoc)
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		ModelFactory mf=new ModelFactory();
		Object obj=getModelNode().getContained();
		return mf.getFigure(obj);
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
	 */
	public IFigure getContentPane() {
		IFigure myFigure = getFigure();
		return getFigure();
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension();
		ModelFactory mf=new ModelFactory();
		Contained obj=getModelNode().getContained();
		((PortLabel)getFigure()).setName(((Node)getModel()).getContained().getIdentifier());
		
		//every location needs a special PortLabel-layout
		PortLabel portLabel=(PortLabel)getFigure();
		if (portLabel instanceof ReceptacleLabel){
			((ReceptacleLabel)portLabel).setMultiple(((UsesDef)obj).isMultipleItf());
			((ReceptacleLabel)portLabel).layoutChildren(getModelNode().getLocation().getValue());	
		}
		else 
			portLabel.layoutChildren(getModelNode().getLocation().getValue());		
	
		dim=getFigure().getPreferredSize(-1,-1);
		mf.setType(obj,getFigure());
		Rectangle r = new Rectangle(loc ,dim);
		//the PortLabelEditParts are children of the ViewEditPart!!!
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.CONTAINED:
				refreshVisuals();
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
	/* (non-Javadoc)
	 * @see org.eclipse.gef.GraphicalEditPart#getFigure()
	 */
	public IFigure getFigure() {
		return super.getFigure();
	}
}
