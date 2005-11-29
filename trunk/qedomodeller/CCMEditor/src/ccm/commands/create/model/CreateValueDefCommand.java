/*
 * Created on 14.06.2005
*/
package ccm.commands.create.model;

import CCMModel.ModuleDef;
import CCMModel.ValueDef;

public class CreateValueDefCommand extends CreateModelCommand {
	
	private boolean isAbstract;
	
	private boolean custom;
	
	private boolean truncatable;
	
	/**
	 * @param type
	 */
	public CreateValueDefCommand() {
		super(ValueDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createValueDef());
		super.execute();
		((ValueDef)newObject).setIsAbstract(isAbstract);
		((ValueDef)newObject).setIsCustom(custom);
		((ValueDef)newObject).setIsTruncatable(truncatable);
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
	 * @param custom The custom to set.
	 */
	public void setCustom(boolean custom) {
		this.custom = custom;
	}

	/**
	 * @param isAbstract The isAbstract to set.
	 */
	public void setAbstract(boolean isAbstract) {
		this.isAbstract = isAbstract;
	}

	/**
	 * @param truncatable The truncatable to set.
	 */
	public void setTruncatable(boolean truncatable) {
		this.truncatable = truncatable;
	}
}
