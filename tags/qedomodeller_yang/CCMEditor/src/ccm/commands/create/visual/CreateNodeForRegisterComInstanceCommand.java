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

import CCMModel.ComponentFeature;
import CCMModel.FinderServiceKind;
import CCMModel.RegisterComponentInstance;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForRegisterComInstanceCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForRegisterComInstanceCommand";
	
	private String regName;
	private FinderServiceKind service;
	private ComponentFeature feature;

	
	
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForRegisterComInstanceCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((RegisterComponentInstance)newObject).setService(service);
		((RegisterComponentInstance)newObject).setRegName(regName);
		((RegisterComponentInstance)newObject).setFeature(feature);
		//((RuleOwner)newObject).setCondition(condition);
		//((RuleOwner)newObject).setLanguage(language);
		//((RuleOwner)newObject).setAction(action);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
		     CCMNotificationImpl.RegisterComponentInstance, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
	 public void setRegName(String name) {
        this.regName = name;
    }
  
    public void setService(FinderServiceKind service) {
        this.service = service;
    }
    public void setFeature(ComponentFeature feature) {
        this.feature = feature;
    }
  
}
  
