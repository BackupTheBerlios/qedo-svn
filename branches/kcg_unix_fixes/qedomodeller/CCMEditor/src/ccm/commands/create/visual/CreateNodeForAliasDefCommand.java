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

import CCMModel.AliasDef;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;


public class CreateNodeForAliasDefCommand extends CreateNodeForTypedefDefCommand{
    
    
    
	private List idlTypes=new LinkedList();
	
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);
    
	private AliasDef alias;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForAliasDefCommand() {
		super();
	}

    /**
     * @see org.eclipse.gef.commands.Command#execute()
     */
    public void execute() {
        super.execute();
	    alias=(AliasDef) newObject;
	    idlTypes=getIDLTypesName();
        setIDLTyped(alias,idlTemplate);
	    opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
			       CCMNotificationImpl.TYPEDEF_DEF, null, null,0));
    }
    
    /**
     * @see org.eclipse.gef.commands.Command#redo()
     */
    public void redo() {
        super.redo();
        setIDLTyped(alias,idlTemplate);
    }
    
    /**
     * @see org.eclipse.gef.commands.Command#undo()
     */
    public void undo() {
        super.undo();
        unSetIDLTyped(alias,idlTemplate);
    }
    /**
     * @return Returns the idlTemplate.
     */
    public IDLTemplate getIdlTemplate() {
        return idlTemplate;
    }
    
    /**
     * @param idlTemplate The idlTemplate to set.
     */
    public void setIdlTemplate(IDLTemplate idlTemplate) {
        this.idlTemplate = idlTemplate;
    }


}
