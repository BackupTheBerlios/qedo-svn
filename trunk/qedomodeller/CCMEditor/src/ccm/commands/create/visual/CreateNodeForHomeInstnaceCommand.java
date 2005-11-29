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
 
//import CCMModel.FinderService;
import CCMModel.FinderServiceKind;
import CCMModel.HomeInstantiation;
import CCMModel.InterfaceDef;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForHomeInstnaceCommand extends CreateNodeForRuleOwnerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForHomeInstanceCommand";
	
	 
	private int cardinality;
	private String regName;
	private FinderServiceKind service;
	//FinderService registerWith;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForHomeInstnaceCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		 
		((HomeInstantiation)newObject).setService(service);
		((HomeInstantiation)newObject).setCardinality(cardinality);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.DeploymentUnit, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setRegName(String name) {
        this.regName = name;
    }
    public void setCardinality(int cardinality) {
        this.cardinality = cardinality;
    }
    public void setService(FinderServiceKind kind) {
        this.service = kind;
    }
    
}
 