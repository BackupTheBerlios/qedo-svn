/*
 * Created on 15.08.2005
*/
package ccm.commands.delete.model;

import java.util.Iterator;

import CCMModel.Contained;
import CCMModel.Node;
import CCMModel.Typed;
import CCMModel.UnionDef;
import CCMModel.UnionField;

public class DeleteUnionDefCommand extends DeleteContainedCommand {
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteUnionDefCommand() {
		super();
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 */
	public DeleteUnionDefCommand(Contained model) {
		super();
		this.model=model;
	}
	/**
	 * Execution of this command deletes a classifierRole
	 * completely.
	 */
	public void execute() {
		super.execute();
		
		((UnionDef)model).getDiscriminatorType().getUnionDef().remove(model);
		((UnionDef)model).setDiscriminatorType(null);
				
		Iterator it = ((UnionDef)model).getNodeFromIDL().iterator();
		while(it.hasNext()) {
			((Node)it.next()).setIdl(null);
		}
		((UnionDef)model).getNodeFromIDL().clear();
		
		Iterator tit = ((UnionDef)model).getTyped().iterator();
		while(tit.hasNext()) {
			((Typed)tit.next()).setIDLType(null);
		}
		((UnionDef)model).getTyped().clear();
		
		Iterator mit = ((UnionDef)model).getUnionMembers().iterator();
		while(mit.hasNext()) {
			UnionField f = (UnionField)mit.next();
			f.getIDLType().getTyped().remove(f);
		}
		((UnionDef)model).getUnionMembers().clear();
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
