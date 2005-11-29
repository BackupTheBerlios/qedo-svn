/**
 * (c) Copyright group cm
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


import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.IFigure;
import org.eclipse.gef.EditPolicy;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.Node;
import ccm.edit.policy.ModelEditPolicy;
import ccm.property.ContainedPropertySource;

/**
 * Class       :ContainerNodeEditPart<br/>
 * @author eduardw
 */
public abstract class ContainerNodeEditPart
	extends CCMAbstractGraphicalEditPart{

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		// TODO Auto-generated method stub
		return null;
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected IPropertySource propertySource = null;

	 /**
     * Creates a new  instance.
     * @param node
     */
    public ContainerNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public ContainerNodeEditPart(){}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		// install the edit policy to handle connection creation
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());	
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
			propertySource = new ContainedPropertySource( getModelNode().getContained() );
		}
		return propertySource;
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
	
}