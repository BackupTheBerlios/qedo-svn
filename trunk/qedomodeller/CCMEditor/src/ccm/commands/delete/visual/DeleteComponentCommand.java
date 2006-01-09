/*
 * Created on 16.05.2005
 *
 */
package ccm.commands.delete.visual;

import java.util.Iterator;
import java.util.Vector;

import CCMModel.ComponentDef;
import CCMModel.Node;
import CCMModel.PortNode;
import CCMModel.impl.ConnectionImpl;

/**
 * @author holger kinscher
 *
 */
public class DeleteComponentCommand extends DeleteNodeCommand {

	
	public DeleteComponentCommand(Node delClassifier) {	
		super(delClassifier, delClassifier.getView(), delClassifier.getContained());
	}
	
	
	
	public void execute() {
		Iterator it = node.getPortNode().iterator();
		while (it.hasNext()) {
			
			PortNode port = (PortNode) it.next();
			
			// delete all connections
			Vector cons = new Vector();
			cons.addAll(port.getConnTarget());
			cons.addAll(port.getConSource());
			Iterator conIt = cons.iterator();
			while (conIt.hasNext()) {
				ConnectionImpl con = (ConnectionImpl) conIt.next();
				DeleteConnectionCommand cmd = new DeleteConnectionCommand(con);
				if (cmd.canExecute()) cmd.execute();
			}
			
			// remove port
			port.getContained().getNode().remove(port);
			if(node.getContained() instanceof ComponentDef)
				node.getView().getNode().remove(port);
			else{
				node.getDefineIn().getContents().remove(port);
			}
		}
		
		node.getPortNode().clear();
		
		super.execute();
	}

}


