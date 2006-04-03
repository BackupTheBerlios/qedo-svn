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


import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.Node;
import CCMModel.UnionDef;
import ccm.ProjectResources;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.edit.policy.ModelEditPolicy;
import ccm.figures.ContainedWithMembersFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.UnionDefPropertySource;

/**
 * @author eduardw
 */
public class UnionDefNodeEditPart
	extends CCMAbstractGraphicalEditPart{

	
	private IPropertySource propertySource = null;
	
    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {
        return getUnionFigure().getPaneFigure();
    }

	 /**
     * Creates a new  instance.
     * @param node
     */
    public UnionDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public UnionDefNodeEditPart(){}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
	}
	
	public UnionDef getUnion(){
		return (UnionDef) ((Node)getModel()).getContained();
	}
	
	/**
	* 
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/

	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.UNION_DEF:	
			case CCMNotificationImpl.CONTAINED:
				refreshVisuals();
				break;
			case CCMNotificationImpl.UN_UN_FIELD:
				refreshVisuals();
				refreshChildren();
				break;    
		}		
		super.notifyChanged(notification);
	}
	
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		getUnionFigure().setIdentifier(getUnion().getIdentifier());
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());	
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
	}

	private ContainedWithMembersFigure getUnionFigure(){
		return (ContainedWithMembersFigure) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		ContainedWithMembersFigure opFigure=new ContainedWithMembersFigure(getUnion().getIdentifier(),ProjectResources.UNION_S);
		return opFigure;
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#getModelChildren()
	 */
	protected List getModelChildren() {
		List	allChildren=super.getModelChildren();
		if(allChildren==null || allChildren.size()==0) 
			allChildren= new LinkedList();
		allChildren.addAll(getModelNode().getContents());
		return allChildren;
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
			propertySource = new UnionDefPropertySource( getModelNode().getContained() );
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
			return new DeleteNodeCommand((Node) getModelNode(),((Node) getModelNode()).getView(),((Node) getModel()).getContained());
		else
		    return super.getCommand(request);
	}
	
	

}