/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * @author Siegercn
 * 
 */
package ccm.commands.create.model;
 
import CCMModel.ExternalInstance;
import CCMModel.FinderServiceKind;
import CCMModel.ModuleDef;

public class CreateExternalInstanceCommand extends CreateModelCommand{
	 
	private String objectref;
	private String regName;
	private FinderServiceKind service;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateExternalInstanceCommand() {
		super(ExternalInstance.class);
		 
	}


	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}
	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		setNewObject(factory.createExternalInstance());
		super.execute();
		 
		((ExternalInstance)newObject).setObjectRef(objectref);
		((ExternalInstance)newObject).setService(service);
		((ExternalInstance)newObject).setRegName(regName);
		 
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setObjectRef(String ref) {
        this.objectref = ref;
    }
    public void setRegname(String name) {
        this.regName = name;
    }
    public void setService(FinderServiceKind service) {
        this.service = service;
    }
}
 
  
