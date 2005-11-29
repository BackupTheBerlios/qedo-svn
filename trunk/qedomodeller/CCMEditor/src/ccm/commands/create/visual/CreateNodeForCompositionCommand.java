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
import CCMModel.InterfaceDef;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForCompositionCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForCompositionCommand";
	
	private ComponentCategory category;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForCompositionCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((Composition)newObject).setCategory(category);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.COMPOSITION, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCategory(ComponentCategory category) {
        this.category = category;
    }
  
}
 
