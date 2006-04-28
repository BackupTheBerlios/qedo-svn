/*
 * Created on 13.01.2005
 */
package ccm.figures;

import org.eclipse.draw2d.Label;
import org.eclipse.draw2d.PolygonDecoration;
import org.eclipse.draw2d.PolylineConnection;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.PointList;
import org.eclipse.swt.graphics.Color;

/**
 * @author holger kinscher
 *
 * created for uml2eclipse-project
 */
public class SupportsConnection extends PolylineConnection {
    
    public SupportsConnection() {
        super();
        PolygonDecoration arrow = new PolygonDecoration();
        PointList supportsArrowPointList = new PointList();
        supportsArrowPointList.addPoint(-2,2);
        supportsArrowPointList.addPoint(0,0);
        supportsArrowPointList.addPoint(-2,-2);
        //supportsArrowPointList.addPoint(-4,0);
        arrow.setTemplate(supportsArrowPointList);

        arrow.setBackgroundColor(new Color(null,255,255,206));
        this.setTargetDecoration(arrow);
        
        Label inscr = new Label("<<Supports>>");
        
        Point end = this.getEnd();
        Point start = this.getStart();
        Point label = new Point();
        inscr.setLocation(new Point(start.x, start.y));
        this.add(new Label(start.toString()));
    }
    
    private Point getCenter(Point start, Point end) {
        Point center = Point.min(start,end);
        Dimension diff = start.getDifference(end);
        center.x += diff.width;
        center.x += diff.height;
        return center;
    }
}
