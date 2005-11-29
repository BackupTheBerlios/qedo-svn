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
public class ReceptacleLabel extends PortLabel {
	
	public ReceptacleLabel() {
	    super();
		add(icon, new Rectangle(0,0,-1,-1));
		add(label, new Rectangle(18,0,-1,-1));
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeBottomLayout()
	 */
	protected void makeBottomLayout() {
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_BOTTOM)));
			super.makeBottomLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeLeftLayout()
	 */
	protected void makeLeftLayout() {
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_LEFT)));
		super.makeLeftLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeRightLayout()
	 */
	protected void makeRightLayout() {
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_RIGHT)));
		super.makeRightLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeTopLayout()
	 */
	protected void makeTopLayout() {
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_TOP)));
		super.makeTopLayout();
	}
}
