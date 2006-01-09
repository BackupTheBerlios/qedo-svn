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

import org.eclipse.emf.common.notify.Notification;

import CCMModel.ComponentDef;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForComponentDefCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForComponentDefCommand";
	
	private boolean isAbstract=false;
	private boolean isLocal=false;

	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForComponentDefCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((ComponentDef)newObject).setIsAbstract(isAbstract);
		((ComponentDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.COMPONENT_DEF, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setAbstract(boolean isAbstract) {
        this.isAbstract = isAbstract;
    }
    /**
     * @param isLocal The isLocal to set.
     */
    public void setLocal(boolean isLocal) {
        this.isLocal = isLocal;
    }
}
