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

import CCMModel.ValueDef;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForValueDefCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForValueDefCommand";
	
	private boolean isAbstract=false;
	private boolean isCustom=false;
	private boolean isTruncat=false;
	 public boolean isEvent=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForValueDefCommand(boolean isEvent) {
		super();
		this.isEvent=isEvent;
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((ValueDef)newObject).setIsAbstract(isAbstract);
		((ValueDef)newObject).setIsCustom(isCustom);
		((ValueDef)newObject).setIsTruncatable(isTruncat);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.VALUE_DEF, null, null,0));
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
    public void setCustom(boolean isLocal) {
        this.isCustom = isLocal;
    }
    /**
     * @param isTruncat The isTruncat to set.
     */
    public void setTruncat(boolean isTruncat) {
        this.isTruncat = isTruncat;
    }
}
