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
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.EnumDef;
import CCMModel.Node;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.figures.EnumDefFigure;
import ccm.property.ContainedPropertySource;
import ccm.property.EnumPropertySource;

/**
 * Class       :AbstractClassifierNodeEditPart<br/>
 * <br/>
 * @author eduardw
 */
public class EnumNodeEditPart
	extends ContainedNodeEditPart{

    
	private IPropertySource propertySource = null;

    /**
     * @param clr
     */
    public EnumNodeEditPart(Node clr) {
        super(clr);
    }
	public EnumDef getEnum(){
		return (EnumDef) ((Node)getModel()).getContained();
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	//protected void refreshChildren(){};
	protected void refreshVisuals() {
		getEnumFigure().setName(getEnum().getIdentifier());
	//	getEnumFigure().setAttributeFigure(getEnum().getMembers());
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(-1,-1);	
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
	}

	private EnumDefFigure getEnumFigure(){
		return (EnumDefFigure) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		EnumDefFigure eFigure=new EnumDefFigure();
		return eFigure;
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
			propertySource = new EnumPropertySource( getModelNode().getContained() );
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
			return new DeleteNodeCommand((Node) getModel(),((Node) getModel()).getView(),((Node) getModel()).getContained());
		else
		    return super.getCommand(request);
	}
	
	

	
}