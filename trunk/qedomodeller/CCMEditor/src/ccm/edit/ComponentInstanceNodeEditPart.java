/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * @author Siegercn
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
import CCMModel.ComponentInstantiation;
import CCMModel.Node;
import ccm.commands.create.visual.adds.AddAttributeDefCommand;
import ccm.commands.create.visual.adds.AddEmitsSourceCommand;
import ccm.commands.create.visual.adds.AddEventSinkCommand;
import ccm.commands.create.visual.adds.AddEventSourceCommand;
import ccm.commands.create.visual.adds.AddFacetCommand;
import ccm.commands.create.visual.adds.AddReceptacleCommand;
import ccm.commands.delete.visual.DeleteComponentCommand;
import ccm.edit.policy.ComponentInstanceEditPolicy;
import ccm.edit.policy.ComponentInstanceXYLayoutEditPolicy;
import ccm.edit.policy.ModelEditPolicy;
import ccm.figures.ContainerFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.ComponentInstancePropertySource;
import ccm.request.AddAttributeDefRequest;
import ccm.request.AddEmitsSourceRequest;
import ccm.request.AddEventSinkRequest;
import ccm.request.AddEventSourceRequest;
import ccm.request.AddFacetRequest;
import ccm.request.AddReceptacleRequest;

public class ComponentInstanceNodeEditPart
	extends ContainerNodeEditPart implements NodeEditPart{


	 /**
     * Creates a new  instance.
     * @param node
     */
    public ComponentInstanceNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public ComponentInstanceNodeEditPart(){}
	
	public ComponentInstantiation getComponentInstance(){
		return (ComponentInstantiation)((Node) getModel()).getContained();
	}
    
	/*
	 * return the figure casted to CORBAComponent
	 */
	public ContainerFigure getComponentInstanceFigure(){
		return (ContainerFigure) getFigure();
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		// install the edit policy to handle connection creation
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ComponentInstanceXYLayoutEditPolicy());
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());	
		installEditPolicy( EditPolicy.GRAPHICAL_NODE_ROLE, new ComponentInstanceEditPolicy() );
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		//Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		
		ContainerFigure fig = getComponentInstanceFigure();
		fig.setIdentifier(getComponentInstance().getIdentifier());
		
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		Dimension prefDim = getFigure().getPreferredSize(0,0);
		
//		if(dim.height < prefDim.height)
//			dim.height = prefDim.height;
		
//		if(dim.width < prefDim.width)
//			dim.width = prefDim.width;
		
		Rectangle r = new Rectangle(loc,dim);
		
		((GraphicalEditPart) getParent()).setLayoutConstraint(
				this,
				fig,
				r);
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		ContainerFigure  compositionFigure=new ContainerFigure(getComponentInstance().getIdentifier(),ccm.ProjectResources.COMPONRNTINSTANCE,true);
		//compositionFigure.setName(getComposition().getIdentifier());
		return compositionFigure;
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
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
		propertySource = new ComponentInstancePropertySource( getModelNode().getContained() );
		return propertySource;
	}

    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {
        return getComponentInstanceFigure().getFiguresPanel();
    }
    
	/**
	 * @see org.eclipse.gef.EditPart#understandsRequest(org.eclipse.gef.Request)
	 */
	public boolean understandsRequest(Request req) {
	    if(req instanceof AddFacetRequest)
	    	return true;
	    else if(req instanceof AddReceptacleRequest)
	    	return true;
	    else if(req instanceof AddEventSourceRequest)
	    	return true;
	    else if(req instanceof AddEmitsSourceRequest)
	    	return true;
	    else if(req instanceof AddEventSinkRequest)
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
		if (request instanceof AddFacetRequest)
	        return new AddFacetCommand();
	    else if (request instanceof AddReceptacleRequest)
	        return new AddReceptacleCommand();
	    else if (request instanceof AddEventSourceRequest)
	        return new AddEventSourceCommand();
	    else if (request instanceof AddEmitsSourceRequest)
	        return new AddEmitsSourceCommand();
	    else if (request instanceof AddEventSinkRequest)
	        return new AddEventSinkCommand();
	    else if (request instanceof AddAttributeDefRequest) 				
		    return new AddAttributeDefCommand();
		else if(request.getType().equals(RequestConstants.REQ_DELETE))
			return new DeleteComponentCommand (getModelNode());   
	   // else if (request.getType().equals("add children")
	   // 		|| request.getType().equals("move children"))
	   // 	return null;
		else return super.getCommand(request);
	}
	
	   /**
  * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
  */
 public ConnectionAnchor getSourceConnectionAnchor(ConnectionEditPart connection) {
     return getComponentInstanceFigure().getIncomingConnectionAnchor();
 }

 /**
  * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
  */
 public ConnectionAnchor getTargetConnectionAnchor(ConnectionEditPart connection) {
     return getComponentInstanceFigure().getOutgoingConnectionAnchor();
 }

 /**
  * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.Request)
  */
 public ConnectionAnchor getSourceConnectionAnchor(Request request) {
     return getComponentInstanceFigure().getIncomingConnectionAnchor();
 }

 /**
  * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.Request)
  */
 public ConnectionAnchor getTargetConnectionAnchor(Request request) {
     return getComponentInstanceFigure().getOutgoingConnectionAnchor();
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
 protected void addChildVisual(EditPart childEditPart, int index) {
	IFigure child = ((GraphicalEditPart)childEditPart).getFigure();
    if (child instanceof Label){
    	getContentPane().add(child, 0);
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
        getContentPane().setConstraint(childFigure, constraint);
	else
		super.setLayoutConstraint(child, childFigure, constraint);
}
/* (non-Javadoc)
 * @see org.eclipse.gef.editparts.AbstractEditPart#removeChildVisual(org.eclipse.gef.EditPart)
 */
protected void removeChildVisual(EditPart childEditPart) {
	IFigure child = ((GraphicalEditPart)childEditPart).getFigure();
	 if (child instanceof Label){
     	getContentPane().remove(child);
     }else
         getContentPane().remove(child);
}
}
  