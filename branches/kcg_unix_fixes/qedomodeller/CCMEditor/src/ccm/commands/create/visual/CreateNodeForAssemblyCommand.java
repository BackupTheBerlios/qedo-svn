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
package ccm.commands.create.visual;

import java.util.Iterator;
import java.util.List;

import org.eclipse.emf.common.notify.Notification;

import CCMModel.Assembly;
import CCMModel.ComponentFile;
import CCMModel.ModuleDef;
import CCMModel.SoftwarePackage;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;



public class CreateNodeForAssemblyCommand extends CreateNodeForRuleOwnerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForAssemblyCommand";
	
	 
	private String uuid;
	private List comFiles;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForAssemblyCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		 
		((Assembly)newObject).setUuid(uuid);
		// Configuration config = factory.createConfiguration();
		// config.setDefinedIn((Assembly)newObject);
		//((Assembly)newObject).setConfig(config);
		for (Iterator it =comFiles.iterator();it.hasNext();){
			ComponentFile comFile = (ComponentFile)it.next();
			if (comFile.getLocation()==""||comFile.getLocation()==null)
				((Assembly)newObject).getSoftwarePackage().add(comFile.getPackage());
			
		}
		((Assembly)newObject).getConfig().getContents().addAll(comFiles);
		((Assembly)newObject).getConfig().getComponentFile().addAll(comFiles);
		//((Assembly)newObject).getComponentFile().addAll(comFiles);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.Assembly, null, null,0));
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
    public List getPackages(){
   	 
   	ModelFactory mf = new ModelFactory();
   	ModuleDef root=this.getRootModule();
   	List pkgs=mf.getAllContained(root,SoftwarePackage.class);
   	return pkgs;
   }
}
 
 