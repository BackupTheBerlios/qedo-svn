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

import org.eclipse.emf.common.notify.Notification;

import CCMModel.ValueBoxDef;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;


public class CreateNodeForValueBoxDefCommand extends CreateNodeForTypedefDefCommand{
    
	private ValueBoxDef valueBox;
	
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);
    
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForValueBoxDefCommand() {
		super();
	}
	
    /**
     * @see org.eclipse.gef.commands.Command#execute()
     */
    public void execute() {
        super.execute();
        valueBox=(ValueBoxDef) newObject;
        setIDLTyped(valueBox,idlTemplate);
        //valueBox.setIDLType((IDLType)idlTypes.get(idlTypeNumber));
	    opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
			       CCMNotificationImpl.TYPEDEF_DEF, null, null,0));
    }
    
    /**
     * @see org.eclipse.gef.commands.Command#redo()
     */
    public void redo() {
        super.redo();
        setIDLTyped(valueBox,idlTemplate);
        //valueBox.setIDLType((IDLType)idlTypes.get(idlTypeNumber));
    }
    
    /**
     * @see org.eclipse.gef.commands.Command#undo()
     */
    public void undo() {
        super.undo();
        unSetIDLTyped(valueBox,idlTemplate);
        //valueBox.setIDLType(null);
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
