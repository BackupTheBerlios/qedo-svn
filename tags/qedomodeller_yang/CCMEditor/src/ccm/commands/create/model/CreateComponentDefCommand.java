/*
 * Created on 02.06.2005
*/
package ccm.commands.create.model;

import CCMModel.ComponentDef;
import CCMModel.ModuleDef;

/**
 * @author Holger Kinscher
 */
public class CreateComponentDefCommand extends CreateModelCommand {

	private boolean isAbstract;
	private boolean local;
	
	/**
	 * @param type
	 */
	public CreateComponentDefCommand() {
		super(ComponentDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createComponentDef());
		super.execute();
		((ComponentDef)newObject).setIsAbstract(isAbstract);
		((ComponentDef)newObject).setIsLocal(local);
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}
	/**
	 * @param b
	 */
	public void setAbstract(boolean b) {
		isAbstract=b;
	}

	/**
	 * @param b
	 */
	public void setLocal(boolean b) {
		local=b;
	}
}
