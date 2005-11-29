/*
 * Created on 18.08.2005
*/
package ccm.commands.delete;

import org.eclipse.gef.commands.Command;

import CCMModel.ComponentDef;
import CCMModel.HomeDef;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import ccm.commands.delete.visual.DeleteComponentCommand;
import ccm.commands.delete.visual.DeleteHomeCommand;
import ccm.commands.delete.visual.DeleteInterfaceCommand;
import ccm.commands.delete.visual.DeleteModuleCommand;
import ccm.commands.delete.visual.DeleteNodeCommand;

public class DeleteCommandFactory {
	
	public Command getDeleteCommand(Object o) {
		
		if(o instanceof Node) {
			if(((Node) o).getContained() instanceof InterfaceDef)
				return new DeleteInterfaceCommand(((Node) o));
			if(((Node) o).getContained() instanceof ComponentDef)
				return new DeleteComponentCommand(((Node) o));
			if(((Node) o).getContained() instanceof HomeDef)
				return new DeleteHomeCommand(((Node) o));
			if(((Node) o).getContained() instanceof ModuleDef)
				return new DeleteModuleCommand(((Node) o));
			if(((Node) o).getContained() instanceof InterfaceDef)
				return new DeleteInterfaceCommand(((Node) o));
		}
		return new DeleteNodeCommand(((Node) o), ((Node) o).getView(), ((Node) o).getContained());
	}

}
