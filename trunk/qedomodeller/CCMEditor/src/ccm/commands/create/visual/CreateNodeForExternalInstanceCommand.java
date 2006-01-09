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

import CCMModel.ExternalInstance;
import CCMModel.FinderServiceKind;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForExternalInstanceCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForExternalInstanceCommand";
	
	 
	private String objectref;
	private String regName;
	private FinderServiceKind service;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForExternalInstanceCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		 
		((ExternalInstance)newObject).setObjectRef(objectref);
		((ExternalInstance)newObject).setService(service);
		((ExternalInstance)newObject).setRegName(regName);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.Assembly, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setObjectRef(String ref) {
        this.objectref = ref;
    }
    public void setRegname(String name) {
        this.regName = name;
    }
    public void setService(FinderServiceKind service) {
        this.service = service;
    }
}
 
 