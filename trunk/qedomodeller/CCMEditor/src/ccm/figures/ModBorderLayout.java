/*******************************************************************************
 * Copyright (c) 2000, 2004 ccm
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0
 * which accompanies this distribution

 *******************************************************************************/
package ccm.figures;

import org.eclipse.draw2d.AbstractHintLayout;
import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Insets;
import org.eclipse.draw2d.geometry.Rectangle;

/**
 * @author eduardw
 */
public class ModBorderLayout 
	extends AbstractHintLayout 
{

/**
 * Constant to be used as a constraint for child figures
 */
public static final Integer CENTER = new Integer(PositionConstants.CENTER);
/**
 * Constant to be used as a constraint for child figures
 */
public static final Integer TOP = new Integer(PositionConstants.TOP);
/**
 * Constant to be used as a constraint for child figures
 */
public static final Integer BOTTOM = new Integer(PositionConstants.BOTTOM);

private IFigure center, top, bottom;

/**
 * @see org.eclipse.draw2d.AbstractHintLayout#calculateMinimumSize(IFigure, int, int)
 */
protected Dimension calculateMinimumSize(IFigure container, int wHint, int hHint) {
	int minWHint = 0, minHHint = 0;
	if (wHint < 0) {
		minWHint = -1;
	}
	if (hHint < 0) {
		minHHint = -1;
	}
	Insets border = container.getInsets();
	wHint = Math.max(minWHint, wHint - border.getWidth());
	hHint = Math.max(minHHint, hHint - border.getHeight());
	Dimension minSize = new Dimension();
	int middleRowWidth = 0, middleRowHeight = 0;
	int rows = 0, columns = 0;

	if (top != null  && top.isVisible()) {
		Dimension childSize = top.getMinimumSize(wHint, hHint);
		hHint = Math.max(minHHint, hHint - (childSize.height));
		minSize.setSize(childSize);
		rows += 1;
	}
	if (bottom != null && bottom.isVisible()) {
		Dimension childSize = bottom.getMinimumSize(wHint, hHint);
		hHint = Math.max(minHHint, hHint - (childSize.height ));
		minSize.width = Math.max(minSize.width, childSize.width);
		minSize.height += childSize.height;
		rows += 1;
	}
	if (center != null && center.isVisible()) {
		Dimension childSize = center.getMinimumSize(wHint, hHint);
		middleRowWidth += childSize.width;
		middleRowHeight = Math.max(childSize.height, middleRowHeight);
		columns += 1;
	}

	rows += columns > 0 ? 1 : 0;
	// Add spacing, insets, and the size of the middle row
	minSize.height += middleRowHeight + border.getHeight();
	minSize.width = Math.max(minSize.width, middleRowWidth) + border.getWidth();
	
	return minSize;
}

/**
 * @see AbstractLayout#calculatePreferredSize(IFigure, int, int)
 */
protected Dimension calculatePreferredSize(IFigure container, int wHint, int hHint) {
	int minWHint = 0, minHHint = 0;
	if (wHint < 0)
		minWHint = -1;
	
	if (hHint < 0)
		minHHint = -1;
	
	Insets border = container.getInsets();
	wHint = Math.max(minWHint, wHint - border.getWidth());
	hHint = Math.max(minHHint, hHint - border.getHeight());
	Dimension prefSize = new Dimension();
	int middleRowWidth = 0, middleRowHeight = 0;
	int rows = 0, columns = 0;

	if (top != null && top.isVisible()) {
		Dimension childSize = top.getPreferredSize(wHint, hHint);
		hHint = Math.max(minHHint, hHint - (childSize.height));
		prefSize.setSize(childSize);
		rows += 1;
	}
	if (bottom != null && bottom.isVisible()) {
		Dimension childSize = bottom.getPreferredSize(wHint, hHint);
		hHint = Math.max(minHHint, hHint - (childSize.height));
		prefSize.width = Math.max(prefSize.width, childSize.width);
		prefSize.height += childSize.height;
		rows += 1;
	}
	if (center != null && center.isVisible()) {
		Dimension childSize = center.getPreferredSize(wHint, hHint);
		middleRowWidth += childSize.width;
		middleRowHeight = Math.max(childSize.height, middleRowHeight);
		columns += 1;
	}

	rows += columns > 0 ? 1 : 0;
	// Add spacing, insets, and the size of the middle row
	prefSize.height += middleRowHeight + border.getHeight();
	prefSize.width = Math.max(prefSize.width, middleRowWidth) + border.getWidth();
	
	return prefSize;
}

/**
 * @see org.eclipse.draw2d.LayoutManager#layout(IFigure)
 */
public void layout(IFigure container) {
	Rectangle area = container.getClientArea();
	Rectangle rect = new Rectangle();

	Dimension childSize;
	
	if (top != null && top.isVisible()) {
		childSize = top.getPreferredSize(-1, -1);
		rect.setLocation(area.x, area.y);
		rect.setSize(childSize);
		rect.width = area.width;
		top.setBounds(rect);
		area.y += rect.height;
		area.height -= rect.height;
	}
	if (center != null && center.isVisible()) {
		childSize = center.getPreferredSize(-1,-1);
		rect.setSize(childSize);	
		rect.setLocation(area.x, area.y);
		center.setBounds(rect);
		area.y += rect.height;
		area.height -= rect.height;
	}
	if (bottom != null && bottom.isVisible()) {
		childSize = bottom.getPreferredSize(
		        Math.max(0, area.width),
		        Math.max(0, area.height));
		if (childSize.height >= area.height) {
			area.height = childSize.height;
		}
		rect.setSize(childSize);
		rect.width = area.width;
		rect.height=area.height;
		rect.setLocation(area.x, area.y );
		bottom.setBounds(rect);
	}
}

/**
 * @see org.eclipse.draw2d.AbstractLayout#remove(IFigure)
 */
public void remove(IFigure child) {
	if (center == child) {
		center = null;
	} else if (top == child) {
		top = null;
	} else if (bottom == child) {
		bottom = null;
	}
}

/**
 * Sets the location of hte given child in this layout.  Valid constraints:
 * <UL>
 * 		<LI>{@link #CENTER}</LI>
 * 		<LI>{@link #TOP}</LI>
 * 		<LI>{@link #BOTTOM}</LI>
 * 		<LI><code>null</code> (to remove a child's constraint)</LI>
 * </UL>
 * 
 * <p>
 * Ensure that the given Figure is indeed a child of the Figure on which this layout has
 * been set.  Proper behaviour cannot be guaranteed if that is not the case.  Also ensure
 * that every child has a valid constraint.  
 * </p>
 * <p> 
 * Passing a <code>null</code> constraint will invoke {@link #remove(IFigure)}.
 * </p>
 * <p> 
 * If the given child was assigned another constraint earlier, it will be re-assigned to
 * the new constraint.  If there is another child with the given constraint, it will be
 * over-ridden so that the given child now has that constraint.
 * </p>
 * 
 * @see org.eclipse.draw2d.AbstractLayout#setConstraint(IFigure, Object)
 */
public void setConstraint(IFigure child, Object constraint) {
	remove(child);
	super.setConstraint(child, constraint);
	if (constraint == null) {
		return;
	}
	
	switch (((Integer) constraint).intValue()) {
		case PositionConstants.CENTER :
			center = child;
			break;
		case PositionConstants.TOP :
			top = child;
			break;
		case PositionConstants.BOTTOM :
			bottom = child;
			break;
		default :
			break;
	}
}


}
