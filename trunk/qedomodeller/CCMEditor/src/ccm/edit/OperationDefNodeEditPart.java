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
import org.eclipse.ui.views.properties.PropertySheetPage;

import CCMModel.Contained;
import CCMModel.FactoryDef;
import CCMModel.FinderDef;
import CCMModel.Node;
import CCMModel.OperationDef;
import ccm.ProjectResources;
import ccm.commands.delete.model.DeleteContainedCommand;
import ccm.commands.delete.visual.DeleteInterfaceCommand;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.edit.policy.ModelEditPolicy;
import ccm.figures.ContainedWithMembersFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.OperationDefPropertySource;

/**
 * <br/>
 * @author eduardw
 */
public class OperationDefNodeEditPart
	//extends CCMAbstractGraphicalEditPart
    extends ContainerNodeEditPart{

    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
	//************************************
	 public Command getCommand(Request request) {
	 	if(request.getType().equals(RequestConstants.REQ_DELETE))
	 		return new DeleteContainedCommand(getModelNode().getContained());
		
	 	  return super.getCommand(request);
	 }
	//************************************
    public IFigure getContentPane() {
        return getOperationFigure().getPaneFigure();
    }
    
	private IPropertySource propertySource = null;

	 /**
     * Creates a new  instance.
     * @param node
     */
    public OperationDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public OperationDefNodeEditPart(){}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
	}
	
	public OperationDef getOperation(){
		return (OperationDef) getModelNode().getContained();
	}
	
	/**
	* 
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/

	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.OPERATION_DEF:	
			case CCMNotificationImpl.CONTAINED:
				refreshVisuals();
				break;
			case CCMNotificationImpl.OP_PARAMETERS:
				refreshVisuals();
				refreshChildren();
				break;  
			default:
				super.notifyChanged(notification);
		}		
	}
	
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		//getHomefFigure().setName(getHome().getIdentifier());
		Rectangle r = new Rectangle(loc ,dim);
		getOperationFigure().setIdentifier(getOperation().getIdentifier());
		((GraphicalEditPart) getParent()).setLayoutConstraint(
				this,
				getFigure(),
				r);
	}

	private ContainedWithMembersFigure getOperationFigure(){
		return (ContainedWithMembersFigure) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		ContainedWithMembersFigure opFigure;
		if(getOperation() instanceof FinderDef)
		    opFigure=new ContainedWithMembersFigure(
		            getOperation().getIdentifier(),ProjectResources.FINDER_S);
		else if(getOperation() instanceof FactoryDef)
		    opFigure=new ContainedWithMembersFigure(
		            getOperation().getIdentifier(),ProjectResources.FACTORY_S);
		else
		    opFigure=new ContainedWithMembersFigure(
		            getOperation().getIdentifier(),ProjectResources.OPERATION_S);
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
		//getRoot().getViewer().getEditDomain().getCommandStack()
	 //	if (key == org.eclipse.ui.views.properties.IPropertySheetPage.class) {
	 	//	PropertySheetPage page = new PropertySheetPage();
	 	//	page.setRootEntry(new org.eclipse.gef.internal.ui.properties.UndoablePropertySheetEntry(getRoot().getViewer().getEditDomain().getCommandStack()));
	 	//	return page;
	 	//	}
		return super.getAdapter( key );
	}
	
	/**
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
			propertySource = new OperationDefPropertySource(getModelNode().getContained() );
		return propertySource;
	}
}