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
package ccm.edit.policy;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.draw2d.BendpointLocator;
import org.eclipse.draw2d.Connection;
import org.eclipse.draw2d.geometry.PointList;
import org.eclipse.gef.ConnectionEditPart;
import org.eclipse.gef.editpolicies.SelectionHandlesEditPolicy;
import org.eclipse.gef.handles.BendpointCreationHandle;
import org.eclipse.gef.handles.BendpointHandle;

/**
 * Provides a list of handles to its superclass, <code>SelectionHandlesEditPolicy</code>
 * The implementation can handle multiple bendpoints but in the sample application we
 * only have start and end point.
 * 
 * @author eddi
 *
 */
public class EdgeSelectionHandlesEditPolicy
	extends SelectionHandlesEditPolicy {

	/**
	 * 
	 */
	public EdgeSelectionHandlesEditPolicy() {
		super();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editpolicies.SelectionHandlesEditPolicy#createSelectionHandles()
	 */
	protected List createSelectionHandles() {
		List list = new ArrayList();
		ConnectionEditPart connPart = (ConnectionEditPart)getHost();
		PointList points = getConnection().getPoints();
		for (int i = 0; i < points.size() - 2; i++) {
			BendpointHandle handle = new BendpointCreationHandle(connPart, 0, 
				new BendpointLocator(getConnection(), i + 1));
			list.add(handle);
		}
		return list;
	}

	protected Connection getConnection() {
		return (Connection)getHostFigure();
	}
}
