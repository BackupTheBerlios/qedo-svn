/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * @author Siegercn
 * 
 */
package ccm.commands.create.visual;

import org.eclipse.emf.common.notify.Notification;

import CCMModel.ComponentCategory;
import CCMModel.Composition;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForAssemblyCommand extends CreateNodeForRuleOwnerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForAssemblyCommand";
	
	 
	private String uuid;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForAssemblyCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		 
		((Implementation)newObject).setUuid(uuid);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.Assembly, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setUUID(String uuid) {
        this.uuid = uuid;
    }
    
}
 
 