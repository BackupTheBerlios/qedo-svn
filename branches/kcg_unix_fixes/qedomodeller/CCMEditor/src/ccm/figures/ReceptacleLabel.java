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
	private boolean isMultiple;
	public ReceptacleLabel(boolean isMultiple) {
	    super();
		add(icon, new Rectangle(0,0,-1,-1));
		add(label, new Rectangle(18,0,-1,-1));
		this.isMultiple= isMultiple;
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeBottomLayout()
	 */
	public void setMultiple(boolean isMultilple){
		this.isMultiple= isMultilple;
	}
	protected void makeBottomLayout() {
		if(isMultiple)
		   icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_BOTTOM)));
		else	
			 icon.setImage(new Image(null, 
					CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_BOTTOM1)));
		super.makeBottomLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeLeftLayout()
	 */
	protected void makeLeftLayout() {
		if(isMultiple)
			icon.setImage(new Image(null, 
		      CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_LEFT)));
		else
			icon.setImage(new Image(null, 
		      CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_LEFT1)));
		super.makeLeftLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeRightLayout()
	 */
	protected void makeRightLayout() {
		if(isMultiple) 
			icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_RIGHT)));
		else 
			icon.setImage(new Image(null, 
					CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_RIGHT1)));
		super.makeRightLayout();
	}
	/* (non-Javadoc)
	 * @see ccm.figures.PortLabel#makeTopLayout()
	 */
	protected void makeTopLayout() {
		if(isMultiple) 
			icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_TOP)));
		else 
			icon.setImage(new Image(null, 
					CCMEditorPlugin.class.getResourceAsStream(ProjectResources.RECEPTACLE_TOP1)));
		super.makeTopLayout();
	}
}
