/*
 * Created on 02.08.2005
*/
package ccm.commands.create.model;

import java.util.List;

import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ModuleDef;

public class CreateEnumDefCommand extends CreateModelCommand {
	private List memberList;

	/**
	 * @param type
	 */
	public CreateEnumDefCommand() {
		super(EventDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createEnumDef());
		super.execute();
		((EnumDef)newObject).getMembers().clear();
		((EnumDef)newObject).getMembers().addAll(memberList);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}

	public void setMembers(List memberList) {
		this.memberList = memberList;
	}
}
