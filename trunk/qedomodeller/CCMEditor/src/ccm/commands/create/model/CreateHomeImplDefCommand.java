/*
 * Created on 02.10.2005
*/
package ccm.commands.create.model;

import CCMModel.Composition;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;

/**
 * @author Siegercn
 */
public class CreateHomeImplDefCommand extends CreateModelCommand {

	 
	private HomeDef home;
	
	/**
	 * @param type
	 */
	public CreateHomeImplDefCommand() {
		super(Composition.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createHomeImplDef());
		((HomeImplDef)newObject).setHome(home);
		super.execute();
		 
		 
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof HomeDef))
			return false;
		home=(HomeDef)container;	
		return true;
	}
	public HomeDef getHome(){
		return home;
	}
	 
}
 
 
