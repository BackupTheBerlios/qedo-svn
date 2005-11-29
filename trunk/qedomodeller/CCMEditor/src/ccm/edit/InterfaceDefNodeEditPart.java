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
import org.eclipse.gef.requests.ChangeBoundsRequest;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.CCMModelPackage;
import CCMModel.InterfaceDef;
import CCMModel.Node;
import ccm.ProjectResources;
import ccm.commands.create.visual.adds.AddAliasDefCommand;
import ccm.commands.create.visual.adds.AddAttributeDefCommand;
import ccm.commands.create.visual.adds.AddConstantDefCommand;
import ccm.commands.create.visual.adds.AddEnumDefCommand;
import ccm.commands.create.visual.adds.AddExceptionDefCommand;
import ccm.commands.create.visual.adds.AddOperationDefCommand;
import ccm.commands.create.visual.adds.AddStructDefCommand;
import ccm.commands.create.visual.adds.AddUnionDefCommand;
import ccm.commands.create.visual.adds.AddValueBoxDefCommand;
import ccm.commands.delete.visual.DeleteInterfaceCommand;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.edit.policy.InterfaceDefEditPolicy;
import ccm.figures.ContainerFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.AbstractIntefacefPropertySource;
import ccm.property.IntefacefPropertySource;
import ccm.request.AddAliasDefRequest;
import ccm.request.AddAttributeDefRequest;
import ccm.request.AddConstantDefRequest;
import ccm.request.AddEnumDefRequest;
import ccm.request.AddExceptionDefRequest;
import ccm.request.AddOperationDefRequest;
import ccm.request.AddStructDefRequest;
import ccm.request.AddUnionDefRequest;
import ccm.request.AddValueBoxDefRequest;

public class InterfaceDefNodeEditPart
	extends ContainerNodeEditPart  implements NodeEditPart{
	 /**
     * Creates a new  instance.
     * @param node
     */
    public InterfaceDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public InterfaceDefNodeEditPart(){}
	
    /**
     * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
     */
    protected void createEditPolicies() {
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
		installEditPolicy( EditPolicy.GRAPHICAL_NODE_ROLE, new InterfaceDefEditPolicy() );
        super.createEditPolicies();
    }
    
	public InterfaceDef getInterface(){
		return (InterfaceDef)((Node) getModel()).getContained();
	}
    	
	public ContainerFigure getInterfaceFigure(){
		return (ContainerFigure) getFigure();
	}
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		Dimension prefDim = getFigure().getPreferredSize(0,0);
		
		if(dim.height < prefDim.height)
			dim.height = prefDim.height;
		
		if(dim.width < prefDim.width)
			dim.width = prefDim.width;
		
		getInterfaceFigure().setIdentifier(getInterface().getIdentifier());
		
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
		ContainerFigure opFigure=new ContainerFigure(getInterface().getIdentifier(),ProjectResources.ITF_S);
		return opFigure;
	}
	
	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.INTERFACE_DEF:	
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
			propertySource = new IntefacefPropertySource( getModelNode().getContained() );
		return propertySource;
	}
	
	/**
	 * @see org.eclipse.gef.EditPart#understandsRequest(org.eclipse.gef.Request)
	 */
	public boolean understandsRequest(Request req) {
	    if (req instanceof AddOperationDefRequest)
	    	return true;
	    else if (req instanceof AddConstantDefRequest)
	    	return true;
	    else if (req instanceof AddAttributeDefRequest)
	    	return true;
	    else if (req instanceof AddUnionDefRequest)
	    	return true;
	    else if (req instanceof AddStructDefRequest)
	    	return true;
	    else if (req instanceof AddEnumDefRequest)
	    	return true;
	    else if (req instanceof AddAliasDefRequest)
	    	return true;
	    else if (req instanceof AddValueBoxDefRequest)
	    	return true;
	    else if (req instanceof AddExceptionDefRequest)
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
			return new DeleteInterfaceCommand(getModelNode());
		if (request instanceof AddOperationDefRequest) 
			return new AddOperationDefCommand();
		else if (request instanceof AddConstantDefRequest) 
			return new AddConstantDefCommand();
		else if (request instanceof AddAttributeDefRequest) 				
			return new AddAttributeDefCommand();
		else if (request instanceof AddUnionDefRequest) 				
			return new AddUnionDefCommand();
		else if (request instanceof AddStructDefRequest) 				
			return new AddStructDefCommand();
		else if (request instanceof AddEnumDefRequest) 				
			return new AddEnumDefCommand();
		else if (request instanceof AddAliasDefRequest) 				
			return new AddAliasDefCommand();
		else if (request instanceof AddValueBoxDefRequest) 				
			return new AddValueBoxDefCommand();
		else if (request instanceof AddExceptionDefRequest) 				
			return new AddExceptionDefCommand();
		else if(request instanceof ChangeBoundsRequest
				&& request.getType().equals(RequestConstants.REQ_ADD))
			return null;
		else
			return super.getCommand(request);
	}
	   /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {

        return getInterfaceFigure().getFiguresPanel();
    }
    
    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getLabelContentPane() {

        return getInterfaceFigure().getPaneFigure();
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
    /* (non-Javadoc)
     * @see org.eclipse.gef.editparts.AbstractEditPart#removeChildVisual(org.eclipse.gef.EditPart)
     */
    protected void removeChildVisual(EditPart childEditPart) {
    	IFigure child = ((GraphicalEditPart)childEditPart).getFigure();
    	 if (child instanceof Label){
         	getLabelContentPane().remove(child);
         }else
             getContentPane().remove(child);
    }
    
    /**
     * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
     */
    public ConnectionAnchor getSourceConnectionAnchor(ConnectionEditPart connection) {
        return getInterfaceFigure().getIncomingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
     */
    public ConnectionAnchor getTargetConnectionAnchor(ConnectionEditPart connection) {
        return getInterfaceFigure().getOutgoingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.Request)
     */
    public ConnectionAnchor getSourceConnectionAnchor(Request request) {
        return getInterfaceFigure().getIncomingConnectionAnchor();
    }

    /**
     * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.Request)
     */
    public ConnectionAnchor getTargetConnectionAnchor(Request request) {
        return getInterfaceFigure().getOutgoingConnectionAnchor();
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