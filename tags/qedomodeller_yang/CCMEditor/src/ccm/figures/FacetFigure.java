/*
 * Created on 20.01.2005
 */
package ccm.figures;

import org.eclipse.draw2d.Label;
import org.eclipse.swt.graphics.Image;

/**
 * @author holger kinscher
 *
 * created for uml2eclipse-project
 */
public class FacetFigure extends Label {
    
    public FacetFigure() {
        super("Facet", new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/packages.gif")));
        //add(new Label("MyFacet"));
    }
}
