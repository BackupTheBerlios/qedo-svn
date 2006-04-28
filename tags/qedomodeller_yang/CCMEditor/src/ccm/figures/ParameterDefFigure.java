/*
 * Created on 09.12.2004
 */
package ccm.figures;

import org.eclipse.draw2d.Label;

/**
 * @author holger kinscher
 */
public class ParameterDefFigure extends CompartmentFigure {
	
    Label textLb;
    
    public ParameterDefFigure() {
	    super();
    }
    
	public ParameterDefFigure(String text) {
	    super();
	    textLb=new Label(text);
	    add(textLb);
    }
	
	public void setName(String text){
	    textLb.setText(text);
	}
}
