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
import CCMModel.RuleOwner;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForRuleOwnerCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForRuleOwnerCommand";
	
	private String name,condition,language,action;

	
	
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForRuleOwnerCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		//((RuleOwner)newObject).setName(name);
		//((RuleOwner)newObject).setCondition(condition);
		//((RuleOwner)newObject).setLanguage(language);
		//((RuleOwner)newObject).setAction(action);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		//node.eNotify(new CCMNotificationImpl(node, Notification.SET,
	//	     CCMNotificationImpl.Implementation, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setName(String name) {
        this.name = name;
    }
    public void setCondition(String condition) {
        this.condition = condition;
    }
  
    public void setLanguage(String language) {
        this.language = language;
    }
    public void setAction(String action) {
        this.action = action;
    }
  
}
 