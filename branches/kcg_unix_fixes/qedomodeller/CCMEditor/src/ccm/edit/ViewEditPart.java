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

import org.eclipse.draw2d.FreeformLayer;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.Request;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.View;
import ccm.edit.policy.ModelEditPolicy;
import ccm.edit.policy.ViewXYLayoutEditPolicy;



/**
 * <br/>
 * @author vilapower
 */
public class ViewEditPart extends AbstractGraphicalEditPart implements Adapter  {
	
	private IPropertySource propertySource = null;
	private Notifier target;
	
	/**
	 * Creates a new VOCLContainerEditPart instance.
	 * @param element VOCLDiagramm
	 */
	public ViewEditPart(View obj) {
		setModel(obj);
	}


	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure(){
		FreeformLayer layer = new FreeformLayer();
		layer.setLayoutManager(new XYLayout());
		layer.setBorder(new LineBorder(2));
		return layer;

	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies(){
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ViewXYLayoutEditPolicy());	
	}

	/** 
	 * Return the Model of this EditPart as VOCLDiagramm.
	 * @see VOCLModel3.VOCLDiagramm
	 *@return  VOCLDiagramm .
	 */
	public View getView(){
		return (View)getModel();
	}
    
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#getModelChildren()
	 */
	protected List getModelChildren(){
		List	allChildren=super.getModelChildren();
		if(allChildren==null || allChildren.size()==0) 
			allChildren= new LinkedList();
		allChildren.addAll(getView().getNode());
		return allChildren;
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#activate()
	 */
	public void activate(){
		if (isActive())return;
		// start listening for changes in the model
		getView().eAdapters().add(this);
		super.activate();
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#deactivate()
	 */
	public void deactivate(){
		if (!isActive())return;
		// stop listening for changes in the model
		getView().eAdapters().remove(this);
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
		/* override the default behavior defined in AbstractEditPart
		*  which would expect the model to be a property sourced. 
		*  instead the editpart can provide a property source
		*/
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
		return null;
		
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.EditPart#understandsRequest(org.eclipse.gef.Request)
	 */
	public boolean understandsRequest(Request req) {
		//return true;
		return super.understandsRequest(req);
	}
	/**
	* checks if the model was be changed
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/	
	public void notifyChanged(Notification notification) {
		int type = notification.getEventType();
		switch( type ) {
			case Notification.ADD:
			case Notification.ADD_MANY:
			case Notification.REMOVE:
			case Notification.REMOVE_MANY:
				refreshVisuals();
				refreshChildren();
				break;
			case Notification.SET:
				refreshVisuals();
				break;
		}
	}

	/**
	 * @param childEditPart
	 * @param index
	 */
	public void addPortVisual(EditPart childEditPart, int index) {
		addChildVisual(childEditPart,index);
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.GraphicalEditPart#setLayoutConstraint(org.eclipse.gef.EditPart, org.eclipse.draw2d.IFigure, java.lang.Object)
	 */
	public void setLayoutConstraint(EditPart child, IFigure childFigure,
			Object constraint) {
		super.setLayoutConstraint(child, childFigure, constraint);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editparts.AbstractEditPart#removeChildVisual(org.eclipse.gef.EditPart)
	 */
	protected void removeChildVisual(EditPart childEditPart) {
		super.removeChildVisual(childEditPart);
	}
}