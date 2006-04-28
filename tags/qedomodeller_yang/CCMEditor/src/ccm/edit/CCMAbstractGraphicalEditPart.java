/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss

 */
package ccm.edit;


import org.eclipse.draw2d.IFigure;
import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;
import org.eclipse.gef.requests.ChangeBoundsRequest;

import CCMModel.CCMModelPackage;
import CCMModel.Node;

/**
 * Class       :AbstractClassifierNodeEditPart<br/>
 * Package     : vocleditor.edit<br/>
 * Project     : VOCLEditor<br/>
 * Created On  : 22.05.2004<br/>
 * Description : Class to provide application for ClassifierNode
 * <br/>
 * @author eddi
 */
public abstract class CCMAbstractGraphicalEditPart
	extends AbstractGraphicalEditPart implements Adapter{

	private Notifier target;

	 /**
     * Creates a new  instance.
     * @param node
     */
    public CCMAbstractGraphicalEditPart(Node clr){
		setModel(clr);
    }

    
    public CCMAbstractGraphicalEditPart(){}
    
	/** 
	 * Return the Model of this EditPart as ClassifierNode.
	 * @see VOCLModel3.ClassifierNode
	 *@return  ClassifierNode .
	 */
	public Node getModelNode() {
		return (Node)getModel();
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {}
	
	/**
	* 
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/

	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMModelPackage.class);
		switch( featureId ) {
			case CCMModelPackage.NODE__Y:
			case CCMModelPackage.NODE__X:   
				refreshVisuals();
				break;
			case CCMModelPackage.NODE__HEIGHT:
			case CCMModelPackage.NODE__WIDTH:
			case CCMModelPackage.NODE__CONTENTS:
				refreshChildren();
				refreshVisuals();
				break;
		}		
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
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()(org.eclipse.gef.editparts.AbstractGraphicalEditPart)
	 */
	protected abstract IFigure createFigure();


	/* (non-Javadoc)
	 * @see org.eclipse.gef.editparts.AbstractEditPart#getCommand(org.eclipse.gef.Request)
	 */
	public Command getCommand(Request request) {
		if(request instanceof ChangeBoundsRequest
				&& request.getType().equals(RequestConstants.REQ_ADD))
			return null;

		return super.getCommand(request);
	}
	
}