/*
 * Created on 02.10.2005
*/
package ccm.commands.create.model;

import CCMModel.ComponentCategory;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.ModuleDef;

/**
 * @author Siegercn
 */
public class CreateComponentImplDefCommand extends CreateModelCommand {

	private ComponentDef component;
	
	/**
	 * @param type
	 */
	public CreateComponentImplDefCommand() {
		super(Composition.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createComponentImplDef());
		((ComponentImplDef)newObject).setComponent(component);
		super.execute();
		
		 
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ComponentDef))
			return false;
		component=(ComponentDef)container;
		return true;
	}
	 public ComponentDef getComponent(){
	 	return component;
	 }
}
 
 
