/*
 * Created on 28.06.2005
 *
 */
package ccm.commands.dnd;

import org.eclipse.gef.commands.Command;

import CCMModel.Contained;
import CCMModel.ModuleDef;
import ccm.CCMConstants;

/**
 * @author christian
 *
 */
public class MoveModelCommand extends Command {

	private ModuleDef module;
	private Contained model;
	
	public MoveModelCommand(ModuleDef module, Contained model) {
		this.module = module;
		this.model = model;		
	}

	
	public void execute() {
	
		model.setDefinedIn(module);
		
		// TODO check if the right absolute name ist computed
		// update absolute name
		String absname = module.getIdentifier();
		if (module.getAbsoluteName()!=null && module.getAbsoluteName().length()!=0) {
			absname = module.getAbsoluteName()+":"+absname;
		}
		
		model.setAbsoluteName(absname);
		model.setRepositoryId(CCMConstants.getRepositoryIdString(absname, model.getIdentifier(), model.getVersion()));
		
		// if model element is a module we need to update all children
		if (!(model instanceof ModuleDef)) return;
		absname = absname + ":" + model.getIdentifier();		
		for (int i=0; i<((ModuleDef) model).getContents().size(); i++) {
			if (((ModuleDef) model).getContents().get(i) instanceof Contained) {
				Contained m = (Contained) ((ModuleDef) model).getContents().get(i);
				m.setAbsoluteName(absname);
				m.setRepositoryId(CCMConstants.getRepositoryIdString(absname, m.getIdentifier(), m.getVersion()));				
			}
		}
		
	}


}




