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
public class FacetLabel extends PortLabel {
	
	public FacetLabel() {
		super();
		icon.setImage(new Image(null, 
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.FACET_ALL)));

		add(icon, new Rectangle(0,0,-1,-1));
		add(label, new Rectangle(18,0,-1,-1));
	}
}