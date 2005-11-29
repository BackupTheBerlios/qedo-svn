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


import org.eclipse.gef.ConnectionEditPart;
import org.eclipse.gef.editpolicies.ConnectionEndpointEditPolicy;


/**
 * <code>EdgeEndpointEditPolicy</code> provides visual feedback for selected edges. Its
 * superclass, <code>ConnectionEndpointEditPolicy</code> displays selection handles. This
 * class also causes the line width to double when selected.
 * 
 * @author eddi
 *
 */
public class EdgeEndpointEditPolicy extends ConnectionEndpointEditPolicy {

	/**
	 * 
	 */
	public EdgeEndpointEditPolicy() {
		super();
	}

	
	public ConnectionEditPart getConnectionEditPart()
	{
		return (ConnectionEditPart)getHost();
	}
}
