/*
 * Created on 16.05.2005
*/
package ccm.commands.delete.visual;

import CCMModel.Node;

/**
 * @author Holger Kinscher
 */
public class DeleteHomeCommand extends DeleteNodeCommand {

	/**
	 * @param delClassifier
	 * @param part 
	 * @param parent
	 * @param model
	 */
	public DeleteHomeCommand(Node delClassifier) {
		super(delClassifier, delClassifier.getView(), delClassifier.getContained());
	}
	
	
	
	
	public void execute() {
		super.execute();
	}
	
}
