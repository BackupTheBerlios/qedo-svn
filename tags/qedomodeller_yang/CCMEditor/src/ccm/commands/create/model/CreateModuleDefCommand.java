/*
 * Created on 02.06.2005
*/
package ccm.commands.create.model;

import CCMModel.ModuleDef;

/**
 * @author Holger Kinscher
 */
public class CreateModuleDefCommand extends CreateModelCommand {

	// the prefix part of the full-qualified name of the module
	private String prefix;
	
	/**
	 * @param type
	 */
	public CreateModuleDefCommand() {
		super(ModuleDef.class);
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createModuleDef());
		super.execute();
		((ModuleDef)newObject).setPrefix(prefix);
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
	 * @param prefix
	 */
	public void setPrefix(String prefix) {
		this.prefix=prefix;
	}
}
