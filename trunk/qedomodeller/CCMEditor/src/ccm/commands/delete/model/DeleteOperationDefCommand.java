/*
 * Created on 05.08.2005
*/
package ccm.commands.delete.model;

import java.util.Iterator;

import org.eclipse.emf.common.util.EList;

import CCMModel.Contained;
import CCMModel.IDLType;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.Typed;

public class DeleteOperationDefCommand extends DeleteContainedCommand {
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteOperationDefCommand() {
		super();
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 */
	public DeleteOperationDefCommand(Contained model) {
		super();
		this.model=model;
	}
	/**
	 * Execution of this command deletes a classifierRole
	 * completely.
	 */
	public void execute() {
		super.execute();
		
		Iterator it = ((OperationDef)model).getParameters().iterator();
		while(it.hasNext()) {
			DeleteParameterCommand cmd = new DeleteParameterCommand((ParameterDef)it.next());
			cmd.execute();
		}
		EList paraList = ((OperationDef)model).getParameters();
		 

		((OperationDef)model).getParameters().clear();
		//((OperationDef)model).getIDLType().getTyped().remove(model);
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
