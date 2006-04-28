package ccm.commands.delete.visual;

import CCMModel.Node;

public class DeleteModuleCommand extends DeleteNodeCommand {

	
	public DeleteModuleCommand(Node delClassifier) {
		super(delClassifier, delClassifier.getView(), delClassifier.getContained());
	}

	

	public void execute() {
		super.execute();
	}

	
}
