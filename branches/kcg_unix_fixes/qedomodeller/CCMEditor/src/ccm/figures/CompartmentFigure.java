/*
 * Created on 09.12.2004
 */
package ccm.figures;

import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.AbstractBorder;
import org.eclipse.draw2d.Figure;
import org.eclipse.draw2d.Graphics;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.ToolbarLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Insets;
import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Color;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.graphics.Rectangle;

/**
 * @author holger kinscher
 */
public class CompartmentFigure extends Figure {
	
	public static Color classColor = new Color(null,255,255,206);
    
	
	public CompartmentFigure() {
        ToolbarLayout layout = new ToolbarLayout();
        setBackgroundColor(classColor);
        layout.setMinorAlignment(ToolbarLayout.ALIGN_TOPLEFT);
        layout.setStretchMinorAxis(true);
        layout.setSpacing(2);
        setLayoutManager(layout);
        setBorder(new CompartmentFigureBorder());
    }
    
    public Dimension getPreferredSize(int wHint, int hHint) {
        List list = this.getChildren();
        Iterator it = list.iterator();
        Dimension dim = new Dimension(0,0);
        
        while(it.hasNext()) {
        	Object o =it.next();
        	if(o!=null&& o instanceof Label){
        		 
            Label label = (Label)o;
            if (label != null) {
                Font f = label.getFont();
                if (f != null) {
                    Dimension diml = label.getPreferredSize();
                    dim.height += diml.height;
                    dim.width = Math.max(dim.width,diml.width);
                } else {
                    label.setFont(new Font(null, "Arial", 8, SWT.NORMAL));
                    try {
                        Dimension diml = label.getPreferredSize();
                        // if image exists, add the size
                        Image img = label.getIcon();
                        if (img != null) {
                            Rectangle rect = img.getBounds();
                            diml.width += rect.width;
                            //diml.height += rect.height;
                        }
                        
                        dim.height += diml.height;
                        dim.width = Math.max(dim.width,diml.width);
                        
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        }
        dim.width += 5;
        // dim.height += (list.size() * 2);
        dim.height = (list.size() * 20);
        setPreferredSize(dim);
        return dim;
    }
    
    public class CompartmentFigureBorder extends AbstractBorder {
        public Insets getInsets(IFigure figure) {
            return new Insets(1,0,0,0);
        }
        public void paint(IFigure figure, Graphics graphics, Insets insets) {
            graphics.drawLine(getPaintRectangle(figure, insets).getTopLeft(),
                    tempRect.getTopRight());
        }
    }
}
