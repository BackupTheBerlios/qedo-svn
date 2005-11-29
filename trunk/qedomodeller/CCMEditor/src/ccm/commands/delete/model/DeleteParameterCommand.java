/*
 * Created on 15.08.2005
*/
package ccm.commands.delete.model;

import org.eclipse.gef.commands.Command;

import CCMModel.ParameterDef;

public class DeleteParameterCommand extends Command{
	
	private ParameterDef model;
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteParameterCommand() {
		super();
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 */
	public DeleteParameterCommand(ParameterDef model) {
		super();
		this.model=model;
	}
	/**
	 * Execution of this command deletes a classifierRole
	 * completely.
	 */
	public void execute() {
		super.execute();
		model.getIDLType().getTyped().remove(model);
	}
	
	/**
	 * Redoes an undo.
	 */
	public void redo() {
	}
	
	/**
	 * Undoes an action done by this command
	 */
	public void undo() {
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		return super.canExecute();
	}
}
