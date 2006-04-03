/*
 * Created on 14.06.2005
*/
package ccm.commands.create.model;

import CCMModel.HomeDef;
import CCMModel.ModuleDef;
;

public class CreateHomeDefCommand extends CreateModelCommand {

	private boolean isAbstract;
	
	private boolean isLocal;
	
	/**
	 * @param type
	 */
	public CreateHomeDefCommand() {
		super(HomeDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createHomeDef());
		super.execute();
		((HomeDef)newObject).setIsAbstract(isAbstract);
		((HomeDef)newObject).setIsLocal(isLocal);
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
