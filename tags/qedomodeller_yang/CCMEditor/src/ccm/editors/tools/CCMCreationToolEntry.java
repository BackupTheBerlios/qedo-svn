/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 */
package ccm.editors.tools;

import org.eclipse.gef.Tool;
import org.eclipse.gef.palette.CreationToolEntry;
import org.eclipse.gef.requests.CreationFactory;
import org.eclipse.jface.resource.ImageDescriptor;


public class CCMCreationToolEntry extends CreationToolEntry {

	/**
	 * @param label
	 * @param shortDesc
	 * @param factory
	 * @param iconSmall
	 * @param iconLarge
	 */
	public CCMCreationToolEntry(
		String label,
		String shortDesc,
		CreationFactory factory,
		ImageDescriptor iconSmall,
		ImageDescriptor iconLarge) {
		super(label, shortDesc, factory, iconSmall, iconLarge);
	}

	/**
	 * @see org.eclipse.gef.palette.ToolEntry#createTool()
	 */
	public Tool createTool() {
		return new CCMCreationTool(factory);
	}

}
