/*
 * Created on 23.06.2005
*/
package ccm.commands.create.model;

import CCMModel.EventDef;
import CCMModel.ModuleDef;

/**
 * @author Holger Kinscher
 */
public class CreateEventDefCommand extends CreateModelCommand {
	private boolean isAbstract;
	
	private boolean custom;
	
	private boolean truncatable;
	
	/**
	 * @param type
	 */
	public CreateEventDefCommand() {
		super(EventDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createEventDef());
		super.execute();
		((EventDef)newObject).setIsAbstract(isAbstract);
		((EventDef)newObject).setIsCustom(custom);
		((EventDef)newObject).setIsTruncatable(truncatable);
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
