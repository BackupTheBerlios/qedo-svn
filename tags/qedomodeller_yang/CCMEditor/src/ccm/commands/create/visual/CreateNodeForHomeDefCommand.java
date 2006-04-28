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
package ccm.commands.create.visual;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForHomeDefCommand extends CreateNodeForAbstractInterfaceDefCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForComponentDefCommand";
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForHomeDefCommand() {
		super();
		setLabel(CreateCommand_Label);
	}

    /**
     * @see ccm.commands.create.visual.CreateNodeForAbstractInterfaceDefCommand#getNotifyKind()
     */
    protected int getNotifyKind() {
        return CCMNotificationImpl.HOME_DEF;
    }
}
