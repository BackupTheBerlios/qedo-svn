/*
 * Created on 06.01.2005
 */
package ccm.figures;

import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.swt.graphics.Image;

/**
 * @author holger kinscher
 *
 * created for uml2eclipse-project
 */
public class AttributeFigure extends CompartmentFigure {
	
	private int inducedHeight = 0;
	
	protected void incrementInducedHeight() {
		inducedHeight+=20;
	}
		
	public Dimension getPreferredSize(int wHint, int hHint) {
		Dimension size = super.getPreferredSize(wHint, hHint);
		if (inducedHeight <= size.height)
			return size;
		else
			return new Dimension(size.width,inducedHeight);
    }
    
    
    public void setPublicAttribute(String name, String type) {
        setAttribute(name + ":" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/public_co.gif")));
    }
    
    public void setPackageAttribute(String name, String type) {
        setAttribute(name + ":" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/packages.gif")));
    }
    
    public void setProtectedAttribute(String name, String type) {
        setAttribute(name + ":" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/protected_co.gif")));
    }
    
    public void setPrivateAttribute(String name, String type) {
        setAttribute(name + ":" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/private_co.gif")));
    }
    
    public void setAttribute(String labeling, Image image) {
        this.add(new Label(labeling, image));
    }
}
