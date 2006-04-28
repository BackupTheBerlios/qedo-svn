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

import java.util.List;

import CCMModel.ComponentDef;
import CCMModel.ModuleDef;
import CCMModel.SoftwarePackage;
import ccm.model.ModelFactory;

public class CreateSoftwarePackageCommand extends CreateModelCommand{
	
	private String licenseKey;
	private String licenseTextRef;
	private String title;
	private String type;
	private String autor;
	private String idlFileName;
	private String idlFileLocation;
	private ComponentDef component;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateSoftwarePackageCommand() {
		super(SoftwarePackage.class);
		 
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
		setNewObject(factory.createSoftwarePackage());
		super.execute();
		((SoftwarePackage)newObject).setLicensekey(licenseKey);
		((SoftwarePackage)newObject).setLicensetextref(licenseTextRef);
		((SoftwarePackage)newObject).setTitle(title);
		((SoftwarePackage)newObject).setType(type);
		((SoftwarePackage)newObject).setAutor(autor);
		((SoftwarePackage)newObject).setComponent(component);
		 
		 
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
	 public void setIDLFileName(String name) {
        this.idlFileName = name;
    }
	 public void setIDLFileLocation(String location) {
        this.idlFileLocation = location;
    }
    public void setTitel (String title) {
        this.title = title;
    }
    public void setType(String type) {
        this.type = type;
    }
    public void setAutor(String autor) {
        this.autor = autor;
    }
    
    public void setLicenseKey(String licenseKey) {
        this.licenseKey = licenseKey;
    }
  
    public void setLicenseTextRef(String licensetextRef) {
        this.licenseTextRef = licensetextRef;
    }
    public List getComponentDefs(){
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=mf.getRootModule(container);
    	List componentdefs=mf.getAllContained(root,ComponentDef.class);
    	return componentdefs;
    }
    public void setComponent(ComponentDef component) {
		this.component=component;
		
	}
  
  
}
  
