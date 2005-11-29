/*
 * Created on 28.06.2005
*/
package ccm.commands.create.model;

import java.util.Iterator;
import java.util.List;

import CCMModel.ExceptionDef;
import CCMModel.Field;
import CCMModel.ModuleDef;
import ccm.model.template.FieldTemplate;

/**
 * @author Holger Kinscher
 */
public class CreateExceptionDefCommand extends CreateModelCommand {

	private String typeCode = "";
	
	private List members;
	
	private ExceptionDef exceptionD;
	/**
	 * @param type
	 */
	public CreateExceptionDefCommand() {
		super(ExceptionDef.class);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createExceptionDef());
		exceptionD = (ExceptionDef) newObject;
		super.execute();
		exceptionD.setTypeCode(typeCode);
	}
	
	private void addMembers(){
	    exceptionD.getMembers().clear();
	    Iterator it=members.iterator();
	    while(it.hasNext()){
	        FieldTemplate p=(FieldTemplate) it.next();
	        Field fld=factory.createField();
	        fld.setIdentifier(p.getIdentifier());
	        setIDLTyped(fld,p.getIdlType());
			exceptionD.getMembers().add(fld);
	    }
	}

	/**
	 * @param typeCode The typeCode to set.
	 */
	public void setTypeCode(String typeCode) {
		this.typeCode = typeCode;
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
	 * @param members The members to set.
	 */
	public void setMembers(List members) {
		this.members = members;
	}
}
