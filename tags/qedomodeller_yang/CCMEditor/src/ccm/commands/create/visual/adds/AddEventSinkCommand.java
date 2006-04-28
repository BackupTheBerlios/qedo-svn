/*
 * Created on 05.02.2005
*/
package ccm.commands.create.visual.adds;


/**
 * @author Holger Kinscher
 */
public class AddEventSinkCommand extends AddPortCommand {

	/**
	 * Constructor, simply calls the superclass
	 * with the ConnectionLabel as parameter.
	 */
	public AddEventSinkCommand(){
		super();
		Command_Label 		= "add event sink";
		Command_Description	= "Add event sink to a component";
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		portDef=mfc.createConsumesDef();
		super.execute();
	}
}