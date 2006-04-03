/*
 * Created on 02.08.2005
*/
package ccm.commands.create.model;

import CCMModel.EventDef;
import CCMModel.ModuleDef;
import CCMModel.ValueBoxDef;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

public class CreateValueBoxDefCommand extends CreateModelCommand {
	
	private IDLTemplate idlTemplate = new IDLTemplate(IDLKind.IDL_LITERAL);;

	/**
	 * @param type
	 */
	public CreateValueBoxDefCommand() {
		super(EventDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createValueBoxDef());
		super.execute();
		setIDLTyped((ValueBoxDef) newObject, idlTemplate);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}
	 
	/**
     * @return Returns the idlTemplate.
     */
    public IDLTemplate getIdlTemplate() {
        return idlTemplate;
    }

	public void setIdlTemplate(IDLTemplate idlTemplate) {
		this.idlTemplate = idlTemplate;
	}
 
}
