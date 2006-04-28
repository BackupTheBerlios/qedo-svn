/*
 * Created on 05.02.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.figures;


import org.eclipse.draw2d.BorderLayout;
import org.eclipse.draw2d.ChopboxAnchor;
import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.Graphics;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.Panel;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.PointList;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Font;

import ccm.CCMConstants;


/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class HomeDefFigure extends Figure {
    
	protected ChopboxAnchor incomingConnectionAnchor;
	protected ChopboxAnchor outgoingConnectionAnchor;

	
	private Panel body;
	private Label nameLb;
	private CompartmentPanel figuresPanel = new CompartmentPanel();
	
	private static final double prop=0.25;
	
	Font font = new Font(null, "Arial",10, SWT.NORMAL);
	
	
	/**
	 * Constructor
	 */
	public HomeDefFigure() {
		setLayoutManager(new XYLayout());	
		setBackgroundColor(ColorConstants.white);
		
		body=new Panel();
		body.setLayoutManager(new ModBorderLayout());
		body.setBorder(new LineBorder(ColorConstants.black,2));
		body.setOpaque(true);
		
		nameLb=new Label("");
		nameLb.setFont(font);
		nameLb.setBackgroundColor(CCMConstants.classColor);
		nameLb.setOpaque(true);
		nameLb.setBorder(new LineBorder(ColorConstants.black,1));
		body.add(nameLb,BorderLayout.TOP);
		body.add(figuresPanel,BorderLayout.BOTTOM);
		add(body,new Rectangle(10,30,-1,-1));

		incomingConnectionAnchor = new ChopboxAnchor(this);
		outgoingConnectionAnchor = new ChopboxAnchor(this);
	
	}
	
	/**
	 * @see org.eclipse.draw2d.Figure#getPreferredSize(int, int)
	 */
	public Dimension getPreferredSize(int w, int h) {
		return getSize();
	}
	
	/**
	 * Overwritten method, indicates that a local
	 * coordinate system is used.
	 */
	protected boolean useLocalCoordinates() {return true;}

	/**
	 * Retrieving the minimum Dimension
	 * @see getPreferredSize()
	 */
	public Dimension getMinimumSize(int wHint, int hHint) {return getPreferredSize();}

	
	public void setName(String name){
		nameLb.setText(name);
	}
	

    /**
     * @see org.eclipse.draw2d.IFigure#paintFigure()
     */
	protected void paintFigure(Graphics graphics) {	
	    Dimension dim=getSize();
        setConstraint(body,new Rectangle((int) (getSize().width*0.1),
                						 (int)(getSize().height*0.25),
                						 (int)(getSize().width*0.8),
                						 (int)(getSize().height*0.75)));
        
		Rectangle r = this.getBounds().getCopy();
		graphics.translate(r.getLocation());
		graphics.setBackgroundColor(ColorConstants.black);
		PointList list=new PointList();
		list.addPoint(0,(int)(getSize().height*0.25));
		list.addPoint((int) (getSize().width*0.5),0);
		list.addPoint(getSize().width,(int)(getSize().height*0.25));
		list.addPoint(0,(int)(getSize().height*0.25));
		graphics.fillPolygon(list);
		graphics.fillRectangle((int)(getSize().width*0.3),
		        			   1,
		        			   (int)(getSize().width*0.1),
      						   (int)(getSize().height*0.25));
			
    }
	
    /**
     * @return Returns the incomingConnectionAnchor.
     */
    public ChopboxAnchor getIncomingConnectionAnchor() {
        return incomingConnectionAnchor;
    }
    /**
     * @param incomingConnectionAnchor The incomingConnectionAnchor to set.
     */
    public void setIncomingConnectionAnchor(
            ChopboxAnchor incomingConnectionAnchor) {
        this.incomingConnectionAnchor = incomingConnectionAnchor;
    }
    /**
     * @return Returns the outgoingConnectionAnchor.
     */
    public ChopboxAnchor getOutgoingConnectionAnchor() {
        return outgoingConnectionAnchor;
    }
    /**
     * @param outgoingConnectionAnchor The outgoingConnectionAnchor to set.
     */
    public void setOutgoingConnectionAnchor(
            ChopboxAnchor outgoingConnectionAnchor) {
        this.outgoingConnectionAnchor = outgoingConnectionAnchor;
    }
    /**
     * @return Returns the figuresPanel.
     */
    public IFigure getFiguresPanel() {
        return figuresPanel.getPane();
    }
}
