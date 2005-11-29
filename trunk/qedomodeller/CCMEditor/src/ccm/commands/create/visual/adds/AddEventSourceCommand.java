/*
 * Created on 05.02.2005
*/
package ccm.commands.create.visual.adds;


/**
 * @author Holger Kinscher
 */
public class AddEventSourceCommand extends AddPortCommand {

	/**
	 * Constructor, simply calls the superclass
	 * with the ConnectionLabel as parameter.
	 */
	public AddEventSourceCommand(){
		super();
		Command_Label 		= "add event source";
		Command_Description	= "Add event source to a component";
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		portDef=mfc.createPublishesDef();
		super.execute();
	}
}