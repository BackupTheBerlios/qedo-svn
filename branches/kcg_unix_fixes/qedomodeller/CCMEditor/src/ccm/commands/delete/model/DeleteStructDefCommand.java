/*
 * Created on 15.08.2005
*/
package ccm.commands.delete.model;

import java.util.Iterator;

import CCMModel.Contained;
import CCMModel.Field;
import CCMModel.Node;
import CCMModel.StructDef;
import CCMModel.Typed;

public class DeleteStructDefCommand extends DeleteContainedCommand {
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteStructDefCommand() {
		super();
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 */
	public DeleteStructDefCommand(Contained model) {
		super();
		this.model=model;
	}
	/**
	 * Execution of this command deletes a classifierRole
	 * completely.
	 */
	public void execute() {
		super.execute();
		
		Iterator it = ((StructDef)model).getNodeFromIDL().iterator();
		while(it.hasNext()) {
			((Node)it.next()).setIdl(null);
		}
		((StructDef)model).getNodeFromIDL().clear();
		
		Iterator tit = ((StructDef)model).getTyped().iterator();
		while(it.hasNext()) {
			((Typed)it.next()).setIDLType(null);
		}
		((StructDef)model).getTyped().clear();
		
		Iterator mit = ((StructDef)model).getMembers().iterator();
		while(mit.hasNext()) {
			Field f = (Field)mit.next();
			f.getIDLType().getTyped().remove(f);
		}
		((StructDef)model).getMembers().clear();
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
}
