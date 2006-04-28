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

import CCMModel.ModuleDef;
import CCMModel.View;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForModuleDefCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForModuleDefCommand";
	
	private String prefix="";
	private View moduleView;
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForModuleDefCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((ModuleDef)newObject).setPrefix(prefix);
		// moduleView=factory.createView();
		// moduleView.setKind(ViewKind.TYPE_LITERAL);
		// view.getCCM().getView().add(moduleView);
		// ((ModuleDef)newObject).getView().add(moduleView);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.MODULE_DEF, null, null,0));
	}

    /**
     * @param prefix The prefix to set.
     */
    public void setPrefix(String prefix) {
        this.prefix = prefix;
    }
    /**
     * @see org.eclipse.gef.commands.Command#redo()
     */
    public void redo() {
		((ModuleDef)newObject).getView().add(moduleView);
		view.getCCM().getView().add(moduleView);
        super.redo();
    }
    /**
     * @see org.eclipse.gef.commands.Command#undo()
     */
    public void undo() {
		((ModuleDef)newObject).getView().remove(moduleView);
		view.getCCM().getView().remove(moduleView);
        super.undo();
    }
}
