/**
 * (c) Copyright group Vilapower
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution, and is available at
 * http://www.tfs.cs.tu-berlin.de/vila
 * 
 * Contributors:
 *     	Eduard Weiss
 * 		Tony Modica
 * 		Frank Hermann
 * 		Holger Endert
 * 
 */
package ccm.edit;


import java.util.List;

import org.eclipse.draw2d.ChopboxAnchor;
import org.eclipse.draw2d.ConnectionAnchor;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.gef.ConnectionEditPart;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.NodeEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.CCMModelPackage;
import CCMModel.Node;
import ccm.edit.policy.ModelNodeComponentEditPolicy;
import ccm.edit.policy.ModelNodeRoleEditPolicy;
import ccm.model.EObjectPropertySource;

/**
 * <br/>
 * @author vilapower
 */
public abstract class ModelNodeEditPart
	extends AbstractGraphicalEditPart implements NodeEditPart, Adapter{

	private IPropertySource propertySource = null;
	private Notifier target;

	 /**
     * Creates a new  instance.
     * @param node
     */
    public ModelNodeEditPart(Node clr){
		setModel(clr);
    }

    
    public ModelNodeEditPart(){}
    
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure;
	
	/** 
	 * Return the Model of this EditPart as ClassifierNode.
	 * @see VOCLModel3.ClassifierNode
	 *@return  ClassifierNode .
	 */
	public Node getModelNode() {
		return (Node)getModel();
	}
	
	/**
	 * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
	 * Gets the source connection anchor of a Association Role. Returns the nearest anchor 
	 * if there is no connection or 
	 * 
	 */
	public ConnectionAnchor getSourceConnectionAnchor(ConnectionEditPart connection) { 	
	    return new ChopboxAnchor(getFigure());
	}
	
	
	/**
	 * @see org.eclipse.gef.NodeEditPart#getSourceConnectionAnchor(org.eclipse.gef.Request)
	 */
	public ConnectionAnchor getSourceConnectionAnchor(Request request) {		
	    return new ChopboxAnchor(getFigure());
	}

	/**
	 * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.ConnectionEditPart)
	 */
	public ConnectionAnchor getTargetConnectionAnchor(ConnectionEditPart connection) {
	    return new ChopboxAnchor(getFigure());
	}
	

	/**
	 * @see org.eclipse.gef.NodeEditPart#getTargetConnectionAnchor(org.eclipse.gef.Request)
	 */
	public ConnectionAnchor getTargetConnectionAnchor(Request request) {
	    return new ChopboxAnchor(getFigure());
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
		// install the edit policy to handle connection creation
		installEditPolicy( EditPolicy.GRAPHICAL_NODE_ROLE, new ModelNodeRoleEditPolicy() );
		installEditPolicy(EditPolicy.COMPONENT_ROLE, new ModelNodeComponentEditPolicy());
	}
	
	/**
	* when AssociationsEndRoles are added to a ClassifierNode, add this EditPart as a listener on the port so
	* that it gets notified of AssociationRole being added or removed. When Association are added
	*  or removed from a EndRole owned by the SimpleClassifierRole of this EditPart, refresh the connections.
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/

	public void notifyChanged(Notification notification) {
		int type = notification.getEventType();
		int featureId = notification.getFeatureID(CCMModelPackage.class);
		switch( featureId ) {
			case CCMModelPackage.NODE__Y:	
			case CCMModelPackage.NODE__X:
			case CCMModelPackage.NODE__WIDTH:    
			case CCMModelPackage.NODE__HEIGHT:
					refreshVisuals();
					refreshChildren();
					break;
			default:
				refreshVisuals();
		}		
	}


	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		//getModelNode().
		Rectangle r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(
			this,
			getFigure(),
			r);
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#activate()
	 */
	public void activate(){
		if (isActive()) return;
		((Notifier)getModelNode()).eAdapters().add(this);	
		super.activate();
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#deactivate()
	 */
	public void deactivate(){
		if (!isActive()) return;
		((Notifier)getModelNode()).eAdapters().remove(this);	
		super.deactivate();
	}


	/**
	 * @see org.eclipse.emf.common.notify.Adapter#getTarget()
	 */
	public Notifier getTarget() {
		return target;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#isAdapterForType(java.lang.Object)
	 */
	public boolean isAdapterForType(Object type) {
		return type.equals( getModel().getClass() );
	}


	/**
	 * @see org.eclipse.emf.common.notify.Adapter#setTarget(org.eclipse.emf.common.notify.Notifier)
	 */
	public void setTarget(Notifier newTarget) {
		target = newTarget;
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
		if( propertySource == null ) {
			propertySource = new EObjectPropertySource( getModelNode() );
		}
		return propertySource;
	}
	
	

	/**
	 * @see org.eclipse.gef.EditPart#understandsRequest(org.eclipse.gef.Request)
	 */
	/*public boolean understandsRequest(Request req) {
	    if (req instanceof SetClassifierRolePropertiesRequest) return true;
		boolean b = super.understandsRequest(req);
		return b;
	}*/

	/**
	 * @see org.eclipse.gef.EditPart#getCommand(org.eclipse.gef.Request)
	 */
	/*public Command getCommand(Request request) {
		if (request instanceof SetClassifierRolePropertiesRequest) 
		   return new SetClassifierPropsCommand();
		return super.getCommand(request);
	}*/

}
