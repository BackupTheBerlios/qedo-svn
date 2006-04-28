/*
 * Created on 02.08.2005
*/
package ccm.commands.create.model;

import CCMModel.AliasDef;
import CCMModel.ModuleDef;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;

public class CreateAliasDefCommand extends CreateModelCommand {
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	/**
	 * @param type
	 */
	public CreateAliasDefCommand() {
		super(AliasDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createAliasDef());
		super.execute();
		setIDLTyped((AliasDef) newObject, idlTemplate);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}

	public IDLTemplate getIdlTemplate() {
		return idlTemplate;
	}

	public void setIdlTemplate(IDLTemplate idlTemplate) {
		this.idlTemplate = idlTemplate;
	}
}
