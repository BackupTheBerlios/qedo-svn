/*
 * Created on 05.02.2005
*/
package ccm.commands.create.visual.adds;

import CCMModel.UsesDef;


/**
 * @author Holger Kinscher
 */
public class AddReceptacleCommand extends AddPortCommand {

	private boolean isMultipleItf;
	
	/**
	 * @param isMultipleItf The isMultipleItf to set.
	 */
	public void setMultipleItf(boolean isMultipleItf) {
		this.isMultipleItf = isMultipleItf;
	}
	/**
	 * Constructor, simply calls the superclass
	 * with the ConnectionLabel as parameter.
	 */
	public AddReceptacleCommand(){
		super();
		Command_Label 		= "add receptacle";
		Command_Description	= "Add receptacle to a component";
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		portDef=mfc.createUsesDef();
		((UsesDef)portDef).setMultipleItf(isMultipleItf);
		super.execute();
	}
}