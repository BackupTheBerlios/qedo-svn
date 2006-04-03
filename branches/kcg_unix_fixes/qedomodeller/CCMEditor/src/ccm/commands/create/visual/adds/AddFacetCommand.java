/*
 * Created on 05.02.2005
*/
package ccm.commands.create.visual.adds;


/**
 * @author Holger Kinscher
 */
public class AddFacetCommand extends AddPortCommand {

	/**
	 * Constructor, simply calls the superclass
	 * with the ConnectionLabel as parameter.
	 */
	public AddFacetCommand(){
		super();
		Command_Label 		= "add facet";
		Command_Description	= "Add facet to a component";
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		portDef = mfc.createProvidesDef();
		super.execute();
	}
}