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


import java.util.LinkedList;
import java.util.List;

import org.eclipse.emf.common.notify.Notification;

import CCMModel.EnumDef;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForEnumDefCommand extends CreateNodeForTypedefDefCommand{
    
	private static final String	CreateCommand_LabelSimple = "CreateParameterCommand";

	private EnumDef enumDef;
	
	private List members=new LinkedList();
	
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForEnumDefCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);;
	}

	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    enumDef=(EnumDef) newObject;
		enumDef.getMembers().clear();
		enumDef.getMembers().addAll(members);
		opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
			       CCMNotificationImpl.TYPEDEF_DEF, null, null,0));
	}

    /**
     * @return Returns the parameters.
     */
    public List getMembers() {
        return members;
    }
    
    /**
     * @param parameters The parameters to set.
     */
    public void setMembers(List parameters) {
        this.members.clear();
        this.members.addAll(parameters);
    }
}
