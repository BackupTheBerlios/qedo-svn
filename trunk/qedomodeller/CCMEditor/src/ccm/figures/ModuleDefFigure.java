/*
 * Created on 05.02.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.figures;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.Graphics;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.Panel;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Rectangle;

import ccm.CCMConstants;


/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class ModuleDefFigure extends Figure {
	
	private Panel body;
	private Label nameLb;
	
	/**
	 * 
	 */
	public ModuleDefFigure() {
		XYLayout layout=new XYLayout();
		setLayoutManager(layout);	
		setBackgroundColor(ColorConstants.white);
		nameLb=new Label("");
		nameLb.setFont(CCMConstants.font);
		nameLb.setBackgroundColor(CCMConstants.classColor);
		nameLb.setOpaque(true);
		nameLb.setBorder(new LineBorder(ColorConstants.black,2));
		add(nameLb,new Rectangle(0,0,-1,-1));
	
	}
	
	/**
	 * @see org.eclipse.draw2d.Figure#getPreferredSize(int, int)
	 */
	public Dimension getPreferredSize(int w, int h) {
		return getSize();
	}
	
	public void setName(String name){
		nameLb.setText(name);
	}
	
	/**
	 * Paint the figures Background Box 
	 */
	protected void paintFigure(Graphics graphics) {	
			Rectangle r = getBounds().getCopy();
			Dimension labelDim=nameLb.getSize();
			Dimension dim=getPreferredSize();
			graphics.translate(r.getLocation());
				
			graphics.setBackgroundColor(CCMConstants.classColor);
			graphics.fillRectangle(0,labelDim.height,dim.width-7,dim.height-labelDim.height-8);
			graphics.fillRectangle(dim.width-7,labelDim.height+8,7,dim.height-labelDim.height-16);
			graphics.fillRectangle(7,dim.height-8,dim.width-14,8);
			graphics.fillArc(0,dim.height-20,20,20,-85,-85);
			graphics.fillArc(dim.width-20,dim.height-20,20,20,-85,85);
			graphics.fillArc(dim.width-20,labelDim.height,20,20,85,-85);
		
			graphics.setBackgroundColor(ColorConstants.black);	
			graphics.setLineWidth(2);
			graphics.drawArc(0,dim.height-20,20,20,-85,-85);
			graphics.drawArc(dim.width-20,dim.height-20,20,20,-85,85);
			graphics.drawLine(1,0,1,dim.height-7);
			graphics.drawLine(7,dim.height-1,dim.width-7,dim.height-1);
			graphics.setLineWidth(2);
			graphics.drawArc(dim.width-20,labelDim.height,20,20,85,-85);
			graphics.setLineWidth(2);
			graphics.drawLine(1,labelDim.height,dim.width-7,labelDim.height);
			graphics.drawLine(dim.width-1,labelDim.height+7,dim.width-1,dim.height-7);
			
	

	}
}
