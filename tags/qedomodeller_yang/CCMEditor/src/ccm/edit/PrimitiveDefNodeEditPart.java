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



import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.swt.graphics.Image;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.IDLType;
import CCMModel.Node;
import CCMModel.PrimitiveDef;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;

/**
 * @author eduardw
 */
public class PrimitiveDefNodeEditPart
	extends ContainerNodeEditPart{

	 /**
     * Creates a new  instance.
     * @param node
     */
    public PrimitiveDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public PrimitiveDefNodeEditPart(){}
	
	public IDLType getPrimitive(){
		return (IDLType)((Node) getModel()).getIdl();
	}
    	
	public Label getModelFigure(){
		return (Label) getFigure();
	}
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(-1,-1);
	    String name=((PrimitiveDef)getPrimitive()).getKind().toString();
	    name=name.substring(3,name.length());
		getModelFigure().setText(name);
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(
			this,
			getFigure(),
			r);
	}
	
	/**
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
		return null;
	}
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
	    Label label=new Label();
	    label.setBorder(new LineBorder(ColorConstants.black,1));
	    label.setIcon(new Image(null, 
                CCMEditorPlugin.class.getResourceAsStream(ProjectResources.PRIMITIVE_S)));
		return label;
	}

}