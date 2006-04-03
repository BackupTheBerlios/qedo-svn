/*
 * Created on 15.08.2005
*/
package ccm.commands.delete.model;

import java.util.Iterator;

import CCMModel.Contained;
import CCMModel.ExceptionDef;
import CCMModel.Field;

public class DeleteExceptionDefCommand extends DeleteContainedCommand {
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteExceptionDefCommand() {
		super();
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 */
	public DeleteExceptionDefCommand(Contained model) {
		super();
		this.model=model;
	}
	/**
	 * Execution of this command deletes a classifierRole
	 * completely.
	 */
	public void execute() {
		super.execute();
		
		Iterator it = ((ExceptionDef)model).getMembers().iterator();
		while(it.hasNext()) {
			Field f = ((Field)it.next());
			((ExceptionDef)model).getMembers().remove(f);
			f.getIDLType().getTyped().remove(f);
			it = ((ExceptionDef)model).getMembers().iterator();
		}
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
