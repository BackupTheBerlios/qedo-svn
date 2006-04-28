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

import CCMModel.Node;
import CCMModel.ValueMemberDef;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;

/**
 * <br/>
 * @author eduardw
 */
public class ValueMemberDefNodeEditPart extends ContainedNodeEditPart{

    /**
     * @param clr
     */
    public ValueMemberDefNodeEditPart(Node clr) {
        super(clr);
    }
    
    private ValueMemberDef getValueMember(){
        return (ValueMemberDef)((Node)getModel()).getContained();
    }
    
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
	    getValueMemberDefFigure().setText(getValueMember().getIdentifier());
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(-1,-1);	
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
	}

	private Label getValueMemberDefFigure(){
		return (Label) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
	    Label eFigure=new Label("",new Image(null,
	            CCMEditorPlugin.class.getResourceAsStream(ProjectResources.MEMBER_S)));
	    eFigure.setBorder(new LineBorder(ColorConstants.black,1));
		return eFigure;
	}
    
}