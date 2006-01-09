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

import CCMModel.ComponentInstantiation;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForComponentInstanceCommand extends CreateNodeForRuleOwnerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForComponentInstanceCommand";
	
	private int cardinality,startOder;
	
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForComponentInstanceCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((ComponentInstantiation)newObject).setCardinality(cardinality);
		((ComponentInstantiation)newObject).setStartOrder(startOder);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.COMPONENTINSTACE, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCardinality(int cardinality) {
        this.cardinality = cardinality;
    }
    public void setStartOder(int startOder) {
        this.startOder = startOder;
    }
  
}
 
