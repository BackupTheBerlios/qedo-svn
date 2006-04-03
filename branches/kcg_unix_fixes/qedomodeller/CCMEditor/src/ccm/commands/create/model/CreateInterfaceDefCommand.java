/*
 * Created on 14.06.2005
*/
package ccm.commands.create.model;

import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;

public class CreateInterfaceDefCommand extends CreateModelCommand {
	
	private boolean isAbstract;
	
	private boolean isLocal;
	
	/**
	 * @param type
	 */
	public CreateInterfaceDefCommand() {
		super(InterfaceDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createInterfaceDef());
		super.execute();
		((InterfaceDef)newObject).setIsAbstract(isAbstract);
		((InterfaceDef)newObject).setIsLocal(isLocal);
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
	 * @param isAbstract The isAbstract to set.
	 */
	public void setAbstract(boolean isAbstract) {
		this.isAbstract = isAbstract;
	}

	/**
	 * @param isLocal The isLocal to set.
	 */
	public void setLocal(boolean isLocal) {
		this.isLocal = isLocal;
	}

}
