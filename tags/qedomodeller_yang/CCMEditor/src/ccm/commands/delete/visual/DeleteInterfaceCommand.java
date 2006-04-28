/*
 * Created on 14.05.2005
*/
package ccm.commands.delete.visual;

import CCMModel.Node;

/**
 * @author Holger Kinscher
 */
public class DeleteInterfaceCommand extends DeleteNodeCommand {

	/**
	 * @param part
	 */
	public DeleteInterfaceCommand(Node n) {
		super(n,n.getView(),n.getContained());
	}

	


	public void execute() {
		super.execute();
	}

	
	
}
