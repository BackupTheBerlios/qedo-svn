/*
 * Created on 13.01.2005
 */
package ccm.figures;

import org.eclipse.draw2d.PolygonDecoration;
import org.eclipse.draw2d.PolylineConnection;
import org.eclipse.draw2d.geometry.PointList;
import org.eclipse.swt.graphics.Color;

/**
 * @author holger kinscher
 *
 * created for uml2eclipse-project
 */
public class AggregationConnection extends PolylineConnection {
    
    private PolygonDecoration arrow;
    
    public AggregationConnection() {
        super();
        
        arrow = new PolygonDecoration();
        PointList supportsArrowPointList = new PointList();
        supportsArrowPointList.addPoint(-2,2);
        supportsArrowPointList.addPoint(0,0);
        supportsArrowPointList.addPoint(-2,-2);
        supportsArrowPointList.addPoint(-4,0);
        arrow.setTemplate(supportsArrowPointList);
        this.setTargetDecoration(arrow);
    }
    
    public void makeShared() {
        arrow.setBackgroundColor(new Color(null,255,255,206));
    }
    
    public void makeComposition() {
        arrow.setBackgroundColor(new Color(null,0,0,0));
    }
}
