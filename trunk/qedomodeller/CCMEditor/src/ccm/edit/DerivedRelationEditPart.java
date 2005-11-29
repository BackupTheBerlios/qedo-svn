/*
 * Created on 25.03.2005
 *
 * 
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.edit;

import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.PolygonDecoration;
import org.eclipse.draw2d.PolylineConnection;
import org.eclipse.draw2d.PolylineDecoration;
import org.eclipse.draw2d.geometry.PointList;

import CCMModel.Connection;
import CCMModel.ConnectionsKind;

import ccm.figures.DerivedConnection;

/**
 * @author eduardw
 *
 * 
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class DerivedRelationEditPart  extends RelationEditPart {
    private Connection link;
	public DerivedRelationEditPart(Connection link) {
		super(link);
		this.link=link;
	}

	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure(){
		if(link.getConnectionKind()==ConnectionsKind.COMPOSITION_LITERAL){
			DerivedConnection f=new DerivedConnection(false);		
			return f; 
		}
		DerivedConnection f=new DerivedConnection(true);		
		return f;
	}

}

