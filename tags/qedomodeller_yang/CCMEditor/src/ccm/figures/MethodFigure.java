/*
 * Created on 06.01.2005
 */
package ccm.figures;

import org.eclipse.draw2d.Label;
import org.eclipse.swt.graphics.Image;

/**
 * @author holger kinscher
 *
 * created for uml2eclipse-project
 */
public class MethodFigure extends CompartmentFigure{

    public void setPublicMethod(String name, String type) {
        setMethod(name + "():" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/public_co.gif")));
    }
    
    public void setPackageMethod(String name, String type) {
        setMethod(name + "():" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/packages.gif")));
    }
    
    public void setProtectedMethod(String name, String type) {
        setMethod(name + "():" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/protected_co.gif")));
    }
    
    public void setPrivateMethod(String name, String type) {
        setMethod(name + "():" + type, new Image(null, 
                CompartmentFigure.class.getResourceAsStream("gif/private_co.gif")));
    }
    
    public void setMethod(String labeling, Image image) {
        this.add(new Label(labeling, image));
    }
}
