/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * @author Siegercn
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
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.NodeEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.CCMModelPackage;
import CCMModel.ComponentDef;
import CCMModel.Composition;
import CCMModel.Node;
import ccm.commands.create.visual.adds.AddAttributeDefCommand;
import ccm.commands.create.visual.adds.AddEmitsSourceCommand;
import ccm.commands.create.visual.adds.AddEventSinkCommand;
import ccm.commands.create.visual.adds.AddEventSourceCommand;
import ccm.commands.create.visual.adds.AddFacetCommand;
import ccm.commands.create.visual.adds.AddReceptacleCommand;
import ccm.commands.delete.visual.DeleteComponentCommand;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.edit.policy.ComponentDefEditPolicy;
import ccm.edit.policy.CompositionEditPolicy;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.edit.policy.ModelEditPolicy;
import ccm.figures.ComponentFigure;
import ccm.figures.ContainerFigureWithAttribute;
import ccm.model.CCMNotificationImpl;
import ccm.property.AbstractIntefacefPropertySource;
import ccm.property.CompositionPropertySource;
import ccm.request.AddAttributeDefRequest;
import ccm.request.AddEmitsSourceRequest;
import ccm.request.AddEventSinkRequest;
import ccm.request.AddEventSourceRequest;
import ccm.request.AddFacetRequest;
import ccm.request.AddReceptacleRequest;

public class ProcessCollocationNodeEditPart
	extends ContainerNodeEditPart implements NodeEditPart{


	 /**
     * Creates a new  instance.
     * @param node
     */
    public ProcessCollocationNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public ProcessCollocationNodeEditPart(){}
	
	public Composition getComposition(){
		return (Composition)((Node) getModel()).getContained();
	}
    
	/*
	 * return the figure casted to CORBAComponent
	 */
	public ContainerFigureWithAttribute getCompositionFigure(){
		return (ContainerFigureWithAttribute) getFigure();
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		// install the edit policy to handle connection creation
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());	
		installEditPolicy( EditPolicy.GRAPHICAL_NODE_ROLE, new CompositionEditPolicy() );
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		
		ContainerFigureWithAttribute fig = getCompositionFigure();
		fig.setName(getComposition().getIdentifier());
		fig.setAttributeLabels(new String[]{"category:"+getComposition().getCategory().toString()});
		Dimension newDim = fig.getPreferredSize(dim);
		if(dim.equals(-1,-1)){
			getModelNode().setWidth(newDim.width);
			getModelNode().setHeight(newDim.height);
		}
		
		Rectangle r = new Rectangle(loc,newDim);
		
		((GraphicalEditPart) getParent()).setLayoutConstraint(
				this,
				fig,
				r);
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		System.out.println("category:"+getComposition().getCategory().toString());
		ContainerFigureWithAttribute compositionFigure=new ContainerFigureWithAttribute(getComposition().getIdentifier(),ccm.ProjectResources.COMPOSITION_S,
				                                          new String[]{"category:"+getComposition().getCategory().toString()});
		//compositionFigure.setName(getComposition().getIdentifier());
		return compositionFigure;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.COMPOSITION:	
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
		propertySource = new CompositionPropertySource( getModelNode().getContained() );
		return propertySource;
	}

    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {
         return getCompositionFigure().getAttributeFigure();
    	//return null;
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
			return new DeleteNodeCommand (getModelNode());   
	    else if (request.getType().equals("add children")
	    		|| request.getType().equals("move children"))
	    	return null;
		else return super.getCommand(request);
	}
	
	   /**
  * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
  */
 public ConnectionAnchor getSourceConnectionAnchor(ConnectionEditPart connection) {
     return getCompositionFigure().getIncomingConnectionAnchor();
 }

 /**
  * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
  */
 public ConnectionAnchor getTargetConnectionAnchor(ConnectionEditPart connection) {
     return getCompositionFigure().getOutgoingConnectionAnchor();
 }

 /**
  * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.Request)
  */
 public ConnectionAnchor getSourceConnectionAnchor(Request request) {
     return getCompositionFigure().getIncomingConnectionAnchor();
 }

 /**
  * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.Request)
  */
 public ConnectionAnchor getTargetConnectionAnchor(Request request) {
     return getCompositionFigure().getOutgoingConnectionAnchor();
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
 
