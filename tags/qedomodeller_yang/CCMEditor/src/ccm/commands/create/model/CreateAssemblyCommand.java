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

import java.util.Iterator;
import java.util.List;

import CCMModel.Assembly;
import CCMModel.ComponentFile;
import CCMModel.ModuleDef;
import CCMModel.SoftwarePackage;
import ccm.model.ModelFactory;
 
public class CreateAssemblyCommand extends CreateModelCommand{
	
		 
	private String uuid;
	private List comFiles;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateAssemblyCommand() {
		super(Assembly.class);
	}


	public boolean canExecute() {
		if(!(container instanceof ModuleDef))
			return false;
		return true;
	}
	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 * 
	 */
	public void execute() {
		setNewObject(factory.createAssembly());
		super.execute();
		((Assembly)newObject).setUuid(uuid);
		
//		 Configuration config = factory.createConfiguration();
//		 config.setDefinedIn((Assembly)newObject);
//		((Assembly)newObject).setConfig(config);
		for (Iterator it =comFiles.iterator();it.hasNext();){
			ComponentFile comFile = (ComponentFile)it.next();
			if (comFile.getLocation()==""||comFile.getLocation()==null)
				((Assembly)newObject).getSoftwarePackage().add(comFile.getPackage());
			
		}
		((Assembly)newObject).getContents().addAll(comFiles);
		((Assembly)newObject).getComponentFile().addAll(comFiles);
		 
	}

	  public List getPackages(){
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=mf.getRootModule(container);
    	List packages=mf.getAllContained(root,SoftwarePackage.class);
    	return packages;
    }
    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setUUID(String uuid) {
        this.uuid = uuid;
    }
    public void setComFiles(List comFiles) {
        this.comFiles = comFiles;
    }
}
 
  