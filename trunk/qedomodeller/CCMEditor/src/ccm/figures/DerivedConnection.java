/*
 * Created on 13.01.2005
 */
package ccm.figures;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.draw2d.Graphics;
import org.eclipse.draw2d.PolygonDecoration;
import org.eclipse.draw2d.PolylineConnection;
import org.eclipse.draw2d.PolylineDecoration;
import org.eclipse.draw2d.geometry.PointList;

/**
 * @author eduardw
 *
 * created for uml2eclipse-project
 */
public class DerivedConnection extends PolylineConnection {

    public DerivedConnection(boolean isCCMConnection) {
        super();
        //PolylineDecoration arrow = new PolylineDecoration();
        PolygonDecoration arrow = new PolygonDecoration();
        arrow.setBackgroundColor(ColorConstants.black);
        
        PointList supportsArrowPointList = new PointList();
        if(isCCMConnection){
        
        supportsArrowPointList.addPoint(-2,1);
        supportsArrowPointList.addPoint(0,0);
        supportsArrowPointList.addPoint(-2,-1);
        arrow.setTemplate(supportsArrowPointList);
        arrow.setLineWidth(3);
        setTargetDecoration(arrow);
        }
        else{
        	supportsArrowPointList.addPoint(0,0);
			supportsArrowPointList.addPoint(-2,2);
			supportsArrowPointList.addPoint(-4,0);
			supportsArrowPointList.addPoint(-2,-2);
			supportsArrowPointList.addPoint(0,0);
			arrow.setTemplate(supportsArrowPointList);
			 
			arrow.setBackgroundColor(ColorConstants.white);
			 
			setSourceDecoration(arrow);
        }
    }
   //  public void paintFigure(Graphics graphics) {	
   //  	graphics.setForegroundColor(ColorConstants.black);
    	
  //   }
    
}
