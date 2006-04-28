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

import CCMModel.ElementName;
import CCMModel.Property;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForPropertyCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForPropertyCommand";
	
	private String type,value;
	private ElementName elementName;

	
	
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForPropertyCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((Property)newObject).setEl_name(elementName);
		((Property)newObject).setValue(value);
		((Property)newObject).setType(type);
		//((RuleOwner)newObject).setCondition(condition);
		//((RuleOwner)newObject).setLanguage(language);
		//((RuleOwner)newObject).setAction(action);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
		     CCMNotificationImpl.Property, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setValue(String value) {
        this.value = value;
    }
    public void setType(String type) {
        this.type = type;
    }
  
    public void setElementName(ElementName name) {
        this.elementName = name;
    }
     
}
 