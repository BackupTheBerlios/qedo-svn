/*
 * Created on 10.12.2004
 */
package ccm.figures;

import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.LineBorder;
import org.eclipse.draw2d.ToolbarLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Image;

import ccm.CCMConstants;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;

/**
 * @author holger
 */
public class EnumDefFigure extends Figure {
    
    public static Color classColor = new Color(null,255,255,206);
    
    protected CompartmentFigure classFigure = new CompartmentFigure();
    protected AttributeFigure attributeFigure = new AttributeFigure();
    
    public EnumDefFigure() {
		ToolbarLayout layout = new ToolbarLayout();
		setLayoutManager(layout);
		setBorder(new LineBorder(ColorConstants.black,1));
		setBackgroundColor(CCMConstants.classColor);
		setOpaque(true);       
		add(classFigure);
        add(attributeFigure);
    }
    
    /**
     * Retrieving the wanted Dimension for this figure.
     * It is calculated by the sum of the dimension of the
     * classFigure (at the top) and the dimension for the
     * attributeFigure (bottom) in y-axis, and the max of
     * the values from both for x-axis.
     */
    public Dimension getPreferredSize(int wHint, int hHint) {
        Dimension dim1 = classFigure.getPreferredSize(0,0);
        Dimension dim3 = attributeFigure.getPreferredSize(0,0);	
        int x = Math.max(dim1.width,dim3.width);
        int y = dim1.height + dim3.height;
        return new Dimension(x, y);
    }
    
    public void setName(String name) {
    	classFigure.removeAll();
    	classFigure.add(new Label(name,new Image(null,CCMEditorPlugin.class.getResourceAsStream(ProjectResources.ENUM_S))));
    	classFigure.repaint();
    	this.repaint();
    }
    

	/**
	 * @return Returns the attributeFigure.
	 */
	public void setAttributeFigure(List list) {
	    attributeFigure.removeAll();
	    Iterator it=list.iterator();
	    while(it.hasNext()){
	        Label l=new Label((String) it.next(),new Image(null,CCMEditorPlugin.class.getResourceAsStream(ProjectResources.MEMBER_S)));
	        l.setBorder(new LineBorder(ColorConstants.black,1));
	        attributeFigure.add(l);
	    }
    	attributeFigure.repaint();
    	repaint();  
	}
}
