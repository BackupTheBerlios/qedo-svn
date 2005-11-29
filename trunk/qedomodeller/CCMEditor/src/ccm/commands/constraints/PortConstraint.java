/*
 * Created on 29.03.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.commands.constraints;

import java.util.Random;

import org.eclipse.draw2d.FigureUtilities;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.graphics.Image;

import CCMModel.Contained;
import CCMModel.PortLocation;
import ccm.CCMConstants;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;
import ccm.model.CCMNotificationImpl;

/**
 * @author eduardw
 */
public class PortConstraint {
	
	Rectangle parentBounds;
	int portLocation;
	Point xyPoint=new Point();
	
	public PortConstraint(Rectangle parentBounds){
		this.parentBounds=parentBounds;
	}
	
	/**
	 * calculates the coordinates for portFigures
	 * 
	 * @param point point from drag
	 * @return coordinates for portFigure
	 */
	public void setPortLoc(Point point,Contained obj, int portLocation) {
		Random random=new Random();
		Dimension minimum= FigureUtilities.getTextExtents(obj.getIdentifier(), CCMConstants.font);	
		Dimension imageDim = new Dimension();
		
		Point top = parentBounds.getTop();
		Point bottom = parentBounds.getBottom();
		Point left = parentBounds.getLeft();
		Point right = parentBounds.getRight();
		
		int topDist = top.getDistanceOrthogonal(point);
		int bottomDist = bottom.getDistanceOrthogonal(point);
		int leftDist = left.getDistanceOrthogonal(point);
		int rightDist = right.getDistanceOrthogonal(point);
		//switch( portLocation ) {
		//case PortLocation.TOP:	
			portLocation=PortLocation.TOP;
			imageDim=getImageDim(obj,portLocation);
			top.y=top.y-minimum.height-imageDim.height;
			xyPoint.setLocation(point.x+random.nextInt(parentBounds.width),top.y);
		//	break;
		//case PortLocation.BOTTOM:
		//	portLocation=PortLocation.BOTTOM;
		//	imageDim=getImageDim(obj,portLocation);
			//top.y=top.y-minimum.height-imageDim.height;
		//	xyPoint.setLocation(point.x+random.nextInt(parentBounds.width),point.y+parentBounds.height);
		//	break;
		//case PortLocation.LEFT:
		//	portLocation=PortLocation.LEFT;
		//    imageDim=getImageDim(obj,portLocation);
		    //
		//    left.x=point.x-imageDim.width;
		//    xyPoint.setLocation(left.x,point.y+random.nextInt(parentBounds.height));
		//break;
		//case PortLocation.RIGHT:
		//	portLocation=PortLocation.RIGHT;
		// 	imageDim=getImageDim(obj,portLocation);
		 	//top.y=top.y-minimum.height-imageDim.height;
		// 	xyPoint.setLocation(point.x+parentBounds.width,point.y+random.nextInt(parentBounds.height));
		//break;
		//}
		
	}
	public void setPortLoc(Point point,Contained obj) {
		Dimension minimum= FigureUtilities.getTextExtents(obj.getIdentifier(), CCMConstants.font);	
		Dimension imageDim = new Dimension();
		
		Point top = parentBounds.getTop();
		Point bottom = parentBounds.getBottom();
		Point left = parentBounds.getLeft();
		Point right = parentBounds.getRight();
		
		int topDist = top.getDistanceOrthogonal(point);
		int bottomDist = bottom.getDistanceOrthogonal(point);
		int leftDist = left.getDistanceOrthogonal(point);
		int rightDist = right.getDistanceOrthogonal(point);
		
		if(topDist <= bottomDist){
			if(topDist <= leftDist){
				if(topDist <= rightDist){
					portLocation=PortLocation.TOP;
					imageDim=getImageDim(obj,portLocation);
					top.y=top.y-minimum.height-imageDim.height;
					xyPoint.setLocation(point.x,top.y);
				}
				else{
					portLocation=PortLocation.RIGHT;
					imageDim=getImageDim(obj,portLocation);
					xyPoint.setLocation(right.x,point.y);
				}
			}
			else if(leftDist <= rightDist){
				portLocation=PortLocation.LEFT;
				imageDim=getImageDim(obj,portLocation);
				left.x-=minimum.width+imageDim.width;
				xyPoint.setLocation(left.x,point.y);
			}
			else{
				portLocation=PortLocation.RIGHT;
				xyPoint.setLocation(right.x,point.y);
			}
		}
		else if(bottomDist <= rightDist){
			if(bottomDist <= leftDist){
				portLocation=PortLocation.BOTTOM;
				xyPoint.setLocation(point.x,bottom.y);
			}
			else{
				portLocation=PortLocation.LEFT;
				imageDim=getImageDim(obj,portLocation);
				left.x-=minimum.width+imageDim.width;
				xyPoint.setLocation(left.x,point.y);
			}
		}
		else if(rightDist <= leftDist){
			portLocation=PortLocation.RIGHT;
			xyPoint.setLocation(right.x,point.y);
		}
		else{
			portLocation=PortLocation.LEFT;
			imageDim=getImageDim(obj,portLocation);
			left.x-=minimum.width+imageDim.width;
			xyPoint.setLocation(left.x,point.y);
		}
		
		if(xyPoint.x<parentBounds.x-minimum.width-imageDim.width)		
			xyPoint.x=parentBounds.x-minimum.width-imageDim.width;
		if(xyPoint.x>parentBounds.x+parentBounds.width)
			xyPoint.x=parentBounds.x+parentBounds.width;
		if(xyPoint.y<parentBounds.y-minimum.height-imageDim.height)
			xyPoint.y=parentBounds.y-minimum.height/*-imageDim.height*/;
		if(xyPoint.y>parentBounds.y+parentBounds.height)
			xyPoint.y=parentBounds.y+parentBounds.height;
	}
	
	private Dimension getImageDim(Contained obj, int location) {
		Image image=new Image(null,
				CCMEditorPlugin.class.getResourceAsStream(ProjectResources.getPortIconPath(obj,location)));
		Dimension imageDim=new Dimension(image.getBounds().width,image.getBounds().height);
		return imageDim;
	}
	
	/**
	 * @return Returns the portLocation.
	 */
	public PortLocation getPortLocation() {
		return PortLocation.get(portLocation);
	}
	/**
	 * @param portLocation The portLocation to set.
	 */
	public void setPortLocation(PortLocation portLocation) {
		this.portLocation = portLocation.getValue();
	}
	/**
	 * @return Returns the xyPoint.
	 */
	public Point getXyPoint() {
		return xyPoint;
	}
	/**
	 * @param xyPoint The xyPoint to set.
	 */
	public void setXyPoint(Point xyPoint) {
		this.xyPoint = xyPoint;
	}
}
