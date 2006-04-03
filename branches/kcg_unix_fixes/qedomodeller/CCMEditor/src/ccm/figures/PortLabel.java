/*
 * Created on 01.03.2005
 */
package ccm.figures;

import org.eclipse.draw2d.ChopboxAnchor;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.ImageFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Image;

import CCMModel.PortLocation;
import ccm.CCMConstants;

/**
 * @author Holger Kinscher
 */
public class PortLabel extends Figure {
	
	/*
	 * icon part of this figure.
	 */
	protected ImageFigure icon=new ImageFigure();
	
	/*
	 * text part of this figure.
	 */
	protected Label label = new Label();
	
	/*
	 * location s. ccm.Figures.Location.
	 */
	public int loc;
	
	/*
	 * connection anchor.
	 */
	protected ChopboxAnchor connectionAnchor;
	
	/*
	 * point relative to the component's inner figures topleft corner.
	 * the inner figure's border should contain this point.
	 */
	public Point coordinates = new Point();
	
	public PortLabel() {
		XYLayout layout = new XYLayout();
		setLayoutManager(layout);

		setFont(CCMConstants.font1);	
		setOpaque(false);
		
		connectionAnchor = new ChopboxAnchor(icon);
	}
	
	
	/* (non-Javadoc)
	 * @see org.eclipse.draw2d.IFigure#getPreferredSize(int, int)
	 */
	public Dimension getPreferredSize(int wHint, int hHint) {
		Dimension dim = new Dimension();
		org.eclipse.swt.graphics.Rectangle iconDim = icon.getImage().getBounds();
		
		if(loc==PortLocation.TOP||loc==PortLocation.BOTTOM){
			dim.width=label.getPreferredSize().width+iconDim.width;
			dim.height=label.getPreferredSize().height+iconDim.height;
		}
		else{
			Font f = label.getFont();
			if(f == null)
				label.setFont(CCMConstants.font);
			dim.width = label.getPreferredSize().width+iconDim.width;
			dim.height=iconDim.height;
		}
		
		return new Dimension(dim.width,dim.height);
	}
	
	public void layoutChildren(int loc) {
		this.loc=loc;
	    switch(loc){
	    case PortLocation.BOTTOM:
	    	makeBottomLayout();
	    	break;
	    case PortLocation.TOP:
	        makeTopLayout();
	    	break;
	    case PortLocation.RIGHT:
	        makeRightLayout();
	    	break;
	    case PortLocation.LEFT:
	        makeLeftLayout();
	    }
	}
	
	/**
	 * 
	 */
	protected void makeRightLayout() {
		this.setConstraint(icon,  new Rectangle(0,0,-1,-1));
		this.setConstraint(label,new Rectangle(icon.getImage().getBounds().width,0,-1,-1));
	}
	
	/**
	 * 
	 */
	protected void makeLeftLayout() {
		this.setConstraint(icon,  new Rectangle(label.getPreferredSize().width,0,-1,-1));
		this.setConstraint(label,new Rectangle(0,0,-1,-1));
	}
	
	/**
	 * 
	 */
	protected void makeTopLayout() {
		this.setConstraint(icon,  new Rectangle(0,label.getPreferredSize().height,-1,-1));
		this.setConstraint(label,new Rectangle(icon.getImage().getBounds().width,0,-1,-1));
	}
	
	/**
	 * 
	 */
	protected void makeBottomLayout() {
		this.setConstraint(icon,  new Rectangle(0,0,-1,-1));
		this.setConstraint(label,new Rectangle(
				icon.getImage().getBounds().width,icon.getImage().getBounds().height,-1,-1));
	}
	
	public int getLoc(){
		return loc;
	}
	
	public Point getCoordinates() {
		return coordinates;
	}
	
	public void setCoordinates(int x,int y) {
		coordinates.x=x;
		coordinates.y=y;
	}
	
	public void setText(String str){
		label.setText(str);
	}
	
	public Image getImage(){
		return icon.getImage();
	}
	
	public void setName(String name){
		label.setText(name);
	}
	
	/**
	 * @return Returns the connectionAnchor.
	 */
	public ChopboxAnchor getConnectionAnchor() {
		return connectionAnchor;
	}
}
