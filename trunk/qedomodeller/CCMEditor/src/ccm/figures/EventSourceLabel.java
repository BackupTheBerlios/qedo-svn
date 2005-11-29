/*
 * Created on 06.02.2005
*/
package ccm.figures;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.graphics.Image;

import ccm.CCMEditorPlugin;
import ccm.ProjectResources;


/**
 * @author Holger Kinscher
 */
public class EventSourceLabel extends PortLabel {
	
	public EventSourceLabel() {
	    super();
		add(icon, new Rectangle(0,0,-1,-1));
		add(label, new Rectangle(18,0,-1,-1));
	}
	
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeBottomLayout()
	 */
	protected void makeBottomLayout() {
		icon.setImage(new Image(null,
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.EVENTSOURCE_BOTTOM)));
		super.makeBottomLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeLeftLayout()
	 */
	protected void makeLeftLayout() {
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.EVENTSOURCE_LEFT)));
		super.makeLeftLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeRightLayout()
	 */
	protected void makeRightLayout() {
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.EVENTSOURCE_RIGHT)));
		super.makeRightLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeTopLayout()
	 */
	protected void makeTopLayout() {
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.EVENTSOURCE_TOP)));
		super.makeTopLayout();
	}
}
