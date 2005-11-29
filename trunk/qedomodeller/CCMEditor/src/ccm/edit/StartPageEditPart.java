package ccm.edit;

import org.eclipse.draw2d.BorderLayout;
import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.FreeformLayer;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Font;

import ccm.CCMConstants;
import ccm.figures.HomeDefFigure;

import CCMModel.View;

public class StartPageEditPart extends AbstractGraphicalEditPart{
	public StartPageEditPart(Integer start) {
		setModel(start);
	}

	protected IFigure createFigure() {
		FreeformLayer layer = new FreeformLayer();
		layer.setLayoutManager(new XYLayout());
		layer.setBorder(new LineBorder(2));
		Label nameLb=new Label("Welcom in CCM ");
		Font font = new Font(null, "Arial",26, SWT.NORMAL);
		nameLb.setFont(font);
		nameLb.setBackgroundColor(CCMConstants.classColor);
		nameLb.setOpaque(true);
		nameLb.setBorder(new LineBorder(ColorConstants.black,1));
		layer.add(nameLb,BorderLayout.CENTER);
		Rectangle r = new Rectangle(80 ,180,-1,-1);
		//((GraphicalEditPart) getParent()).setLayoutConstraint(this,figure,r);
		//layer.add(nameLb,BorderLayout.TOP);
		layer.add(nameLb,r);
		return layer;
	}
	protected void refreshVisuals() {
		Rectangle r;
		//Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		//Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());
		//getHomefFigure().setName(getHome().getIdentifier());
		r = new Rectangle(0,0,-1,-1);
		((GraphicalEditPart) getParent()).setLayoutConstraint(
			this,
			getFigure(),
			r);
	}
	protected void createEditPolicies() {
		// TODO Auto-generated method stub
		
	}
	
	

}
