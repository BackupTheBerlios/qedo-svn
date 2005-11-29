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
import CCMModel.HomeInstantiation;
import CCMModel.InterfaceDef;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForHomeInstanceCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForHomeInstanceCommand";
	
	private ComponentCategory category;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForHomeInstanceCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
	//	((HomeInstantiation)newObject).setCategory(category);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.HOMEIINSTANCE, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCategory(ComponentCategory category) {
        this.category = category;
    }
  
}
 

 