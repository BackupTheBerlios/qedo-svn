/*
 * Created on 02.08.2005
*/
package ccm.commands.create.model;

import java.util.Iterator;
import java.util.List;

import CCMModel.Field;
import CCMModel.ModuleDef;
import CCMModel.StructDef;
import ccm.model.template.FieldTemplate;

public class CreateStructDefCommand extends CreateModelCommand {

	private List memberList;
	private StructDef structD;

	/**
	 * @param type
	 */
	public CreateStructDefCommand() {
		super(StructDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		structD = (StructDef) factory.createStructDef();
		setNewObject(structD);
		super.execute();
		addMembers();
	}
	
	private void addMembers(){
	    structD.getMembers().clear();
	    Iterator it=memberList.iterator();
	    while(it.hasNext()){
	        FieldTemplate p=(FieldTemplate) it.next();
	        Field fld=factory.createField();
	        fld.setIdentifier(p.getIdentifier());
	        this.setIDLTyped(fld,p.getIdlType());
			structD.getMembers().add(fld);
	    }
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
