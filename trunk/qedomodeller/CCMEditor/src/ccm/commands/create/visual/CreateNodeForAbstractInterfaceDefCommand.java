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

import CCMModel.AbstractInterfaceDef;
import ccm.model.CCMNotificationImpl;



public abstract class CreateNodeForAbstractInterfaceDefCommand extends CreateNodeForContainerCommand{
	
	private boolean isAbstract=false;
	private boolean isLocal=false;
	private AbstractInterfaceDef aInterface;

	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForAbstractInterfaceDefCommand() {super();}

	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		aInterface=(AbstractInterfaceDef) newObject;
		aInterface.setIsAbstract(isAbstract);
		aInterface.setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
		        getNotifyKind(), null, null,0));
	}
	
	protected abstract int getNotifyKind();

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
