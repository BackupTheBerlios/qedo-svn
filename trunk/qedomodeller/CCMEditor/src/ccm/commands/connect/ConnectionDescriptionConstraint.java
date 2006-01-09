/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 * 
 */
package ccm.commands.connect;

import org.eclipse.draw2d.FigureUtilities;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.Locator;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;

import ccm.figures.DerivedConnection;


/**
 * Class       :AssociationEndRoleConstraint<br/>
 * Package     : vocleditor.commands.connect<br/>
 * Project     : VOCLEditor<br/>
 * Created On  : 22.05.2004<br/>
 * Description : Locator for AssociationEndRole
 * <br/>
 * @author vilapower
 */
public class ConnectionDescriptionConstraint implements Locator{

	String text;
	Point offset;
	DerivedConnection connFigure;

	public ConnectionDescriptionConstraint(String text, Point offset, DerivedConnection connFigure){
		this.text = text;
		this.offset = offset;
		this.connFigure = connFigure;
	}

	public void relocate(IFigure figure){
		Dimension minimum = FigureUtilities.getTextExtents(text, figure.getFont());
		figure.setSize(minimum);
		Point location;
		Point start=connFigure.getStart();
		Point end=connFigure.getEnd();

		location =new Point(((int)(start.x+end.x)/2),((int)(start.y+end.y)/2));
		
		Point offsetCopy = offset.getCopy();
		offsetCopy.translate(location);
		figure.setLocation(offsetCopy);
	}
}
