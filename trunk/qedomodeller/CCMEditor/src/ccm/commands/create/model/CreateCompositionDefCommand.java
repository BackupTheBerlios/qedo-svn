/*
 * Created on 02.10.2005
*/
package ccm.commands.create.model;

import CCMModel.ComponentCategory;
import CCMModel.ComponentDef;
import CCMModel.Composition;
import CCMModel.ModuleDef;

/**
 * @author Siegercn
 */
public class CreateCompositionDefCommand extends CreateModelCommand {

	private ComponentCategory category;
	
	/**
	 * @param type
	 */
	public CreateCompositionDefCommand() {
		super(Composition.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createComposition());
		super.execute();
		((Composition)newObject).setCategory(category);
		 
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}
	 public void setCategory(ComponentCategory category) {
        this.category = category;
    }
}
 
