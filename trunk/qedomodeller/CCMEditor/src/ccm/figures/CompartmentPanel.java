/*
 * Created on 09.12.2004
 */
package ccm.figures;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.FlowLayout;
import org.eclipse.draw2d.FreeformLayer;
import org.eclipse.draw2d.FreeformViewport;
import org.eclipse.draw2d.ScrollPane;
import org.eclipse.draw2d.XYLayout;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Insets;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.handles.HandleBounds;
import org.eclipse.swt.graphics.Color;

/**
 * @author eduardw
 */
public class CompartmentPanel extends ScrollPane  implements HandleBounds {
	
	public static Color classColor = new Color(null,255,255,206);
	
	FreeformLayer pane = new FreeformLayer();

	
	
	
	public CompartmentPanel() {
		setViewport(new FreeformViewport());
		setContents(pane);
	    FlowLayout layout = new FlowLayout(true);
        setBackgroundColor(ColorConstants.buttonLightest);
        layout.setMinorAlignment(FlowLayout.ALIGN_LEFTTOP);
        layout.setStretchMinorAxis(false);
        layout.setMajorSpacing(2);
	    pane.setLayoutManager(layout);
	     
    }
	public CompartmentPanel(boolean XYLayout) {
		setViewport(new FreeformViewport());
		setContents(pane);
	    pane.setLayoutManager(new XYLayout());
    }
    
    public Dimension getPreferredSize(int wHint, int hHint) {
        return getSize();
    }

    /**
     * @see org.eclipse.gef.handles.HandleBounds#getHandleBounds()
     */
    public Rectangle getHandleBounds() {
        return getBounds().getCropped(new Insets(2,0,2,0));
    }
    /**
     * @return Returns the pane.
     */
    public FreeformLayer getPane() {
        return pane;
    }
}
