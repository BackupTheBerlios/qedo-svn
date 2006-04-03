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
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.AttributeDef;
import CCMModel.Node;
import ccm.ProjectResources;
import ccm.figures.ContainedWithMembersFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.AttributeDefPropertySource;

/**
 * Class       :AbstractClassifierNodeEditPart<br/>
 * Package     : vocleditor.edit<br/>
 * Project     : VOCLEditor<br/>
 * Created On  : 22.05.2004<br/>
 * Description : Class to provide application for ClassifierNode
 * <br/>
 * @author eduardw
 */
public class AttributeDefNodeEditPart extends ContainedNodeEditPart{

	private IPropertySource propertySource = null;
    /**
     * @param clr
     */
    public AttributeDefNodeEditPart(Node clr) {
        super(clr);
    }
    
    private AttributeDef getAttribute(){
        return (AttributeDef)((Node)getModel()).getContained();
    }
    
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
	    getAttributeDefFigure().setIdentifier(getAttribute().getIdentifier());
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(-1,-1);	
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
	}

	private ContainedWithMembersFigure getAttributeDefFigure(){
		return (ContainedWithMembersFigure) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
	 //   Label eFigure=new Label("",new Image(null, 
     //           CCMEditorPlugin.class.getResourceAsStream(ProjectResources.ATTRIBUE_S)));
	 //   eFigure.setBorder(new LineBorder(ColorConstants.black,1));
	//	return eFigure;
		ContainedWithMembersFigure opFigure=new ContainedWithMembersFigure(getAttribute().getIdentifier(),ProjectResources.ATTRIBUE_S);
		return opFigure;
	}
	
	/**
	* 
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/

	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.CONTAINED:	
				refreshVisuals();
				break;
           default:   
               super.notifyChanged(notification);
		}		
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
			propertySource = new AttributeDefPropertySource( getModelNode().getContained() );
		return propertySource;
	}
}