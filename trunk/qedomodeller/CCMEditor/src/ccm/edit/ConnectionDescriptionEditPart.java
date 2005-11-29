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


import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.gef.DragTracker;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.Request;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;
import org.eclipse.gef.tools.DirectEditManager;
import org.eclipse.ui.views.properties.IPropertySource;

import ccm.commands.connect.ConnectionDescriptionConstraint;
import ccm.commands.connect.ConnectionDescriptionTracker;
import ccm.edit.policy.ConnectionDescriptionMovePolicy;
import ccm.figures.DerivedConnection;

import CCMModel.ConnectionDiscription;



/**
 * Class       : ConnectionDescriptionEditPart<br/>
 * Package     : navexpeditor.edit<br/>
 * Project     : NavExpEditor<br/>
 * Created On  : 22.05.2004<br/>
 * Description : Class to provide application for AssociationEndRole
 * <br/>
 * @author eduardw
 */
public class ConnectionDescriptionEditPart extends AbstractGraphicalEditPart implements Adapter{
	
	private IPropertySource propertySource = null;
	private Notifier target;
	private DirectEditManager manager;

	/**
	 * Creates a new ConnectionDescriptionEditPart instance.
	 * @param associationEndRole ConnectionDiscription
	 */
	public ConnectionDescriptionEditPart(ConnectionDiscription associationEndRole){
		setModel(associationEndRole);
	}

	/** 
	 * This method instanciates and returns a Label as a Figure for AssociationEndRole
	 * with name of AssociationEndRole
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 * @see org.eclipse.draw2d.Label
	 */
	protected IFigure createFigure(){
	    ConnectionDiscription role = getAssociationEndRole();
		String text = role.getLabel();
		if (text == null || text.length() == 0) text = "";
		
		Label label = new Label();
		label.setText(text); 
		return label;
	}

	/**
	 *checks, if the Number of anchors were changed 
	 * @param notification org.eclipse.emf.common.notify.Notification
	 */
	public void notifyChanged(Notification notification){
		refreshVisuals();
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies(){
		installEditPolicy(EditPolicy.GRAPHICAL_NODE_ROLE, new ConnectionDescriptionMovePolicy());
	}

	/**
	 * @see org.eclipse.gef.EditPart#getDragTracker(org.eclipse.gef.Request)
	 */
	public DragTracker getDragTracker(Request request){
		return new ConnectionDescriptionTracker(this, (DerivedRelationEditPart) getParent());
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals(){
	    ConnectionDiscription role = getAssociationEndRole();
		String text = role.getLabel();
		
		Point offset = new Point(role.getX(), role.getY());
		Label figure = (Label)getFigure();
		figure.setText(text);
		DerivedRelationEditPart parent = (DerivedRelationEditPart)getParent();
		DerivedConnection connFigure = (DerivedConnection)parent.getFigure();
		ConnectionDescriptionConstraint constraint =
					 new ConnectionDescriptionConstraint(text, offset, connFigure);
		parent.setLayoutConstraint(this, getFigure(), constraint);
	}

	/**
	* @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#activate()
	*/
	public void activate(){
		if (isActive()) return;
		// start listening for changes in the model
		 ((Notifier)getAssociationEndRole()).eAdapters().add(this);
		super.activate();
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#deactivate()
	 */
	public void deactivate(){
		if (!isActive()) return;
		// stop listening for changes in the model
		 ((Notifier)getAssociationEndRole()).eAdapters().remove(this);
		super.deactivate();
	}


	private ConnectionDiscription getAssociationEndRole(){
		return (ConnectionDiscription)getModel();
	}
	
	/**
	 * @see org.eclipse.emf.common.notify.Adapter#getTarget()
	 */
	public Notifier getTarget(){
		return target;
	}

	/**
	 * @see org.eclipse.emf.common.notify.Adapter#isAdapterForType(java.lang.Object)
	 */
	public boolean isAdapterForType(Object type){
		return type.equals(getModel().getClass());
	}
	
	/**
	 * @see org.eclipse.emf.common.notify.Adapter#setTarget(org.eclipse.emf.common.notify.Notifier)
	 */
	public void setTarget(Notifier newTarget){
		target = newTarget;
	}
	
	/**
	 * @see org.eclipse.core.runtime.IAdaptable#getAdapter(java.lang.Class)
	 */
	public Object getAdapter(Class key){
		return super.getAdapter(key);
	}


}
