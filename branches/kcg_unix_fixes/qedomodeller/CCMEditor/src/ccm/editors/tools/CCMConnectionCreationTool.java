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
package ccm.editors.tools;

import org.eclipse.gef.commands.Command;
import org.eclipse.gef.requests.CreationFactory;
import org.eclipse.gef.tools.ConnectionCreationTool;



public class CCMConnectionCreationTool extends ConnectionCreationTool {
	
    private Execution execute= new Execution();

	/**
	 * 
	 */
	public CCMConnectionCreationTool() {super();}

	/**
	 * @param factory
	 */
	public CCMConnectionCreationTool(CreationFactory factory) {super(factory);}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#executeCurrentCommand()
	 */
	protected void executeCurrentCommand() {
		Command command=getCurrentCommand();
		super.executeCurrentCommand();
	}
	
	
	

}
