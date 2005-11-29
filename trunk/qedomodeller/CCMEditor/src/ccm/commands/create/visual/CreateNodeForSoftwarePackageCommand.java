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
import java.util.Map;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.ecore.EPackage;

import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.ComponentCategory;
import CCMModel.ComponentDef;
import CCMModel.Composition;
import CCMModel.IDLFile;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;
import CCMModel.Node;
import CCMModel.SoftwarePackage;

import ccm.commands.connect.ImplConnectCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;



public class CreateNodeForSoftwarePackageCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForSoftwarePackageCommand";
	
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
	public CreateNodeForSoftwarePackageCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		((SoftwarePackage)newObject).setLicensekey(licenseKey);
		((SoftwarePackage)newObject).setLicensetextref(licenseTextRef);
		((SoftwarePackage)newObject).setTitle(title);
		((SoftwarePackage)newObject).setType(type);
		((SoftwarePackage)newObject).setAutor(autor);
		((SoftwarePackage)newObject).setComponent(component);
		ModelFactory mf = new ModelFactory();
		Map registry = EPackage.Registry.INSTANCE;
		String ccmURI = CCMModelPackage.eNS_URI;
		CCMModelPackage ccmPackage =
		(CCMModelPackage) registry.get(ccmURI);
		CCMModelFactory factory = ccmPackage.getCCMModelFactory();
		IDLFile idlFile=factory.createIDLFile();
		idlFile.setName(idlFileName);
		idlFile.setLocation(idlFileLocation);
		idlFile.setIdentifier(newObject.getIdentifier()+".idlFileName");
		idlFile.setVersion(newObject.getVersion());
		idlFile.setRepositoryId(newObject.getRepositoryId());
		idlFile.setDefinedIn((SoftwarePackage)newObject);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		
		List nodeList = view.getNode();
		//for (Iterator nit= nodeList.iterator();nit.hasNext(); ){
		//	Node n=(Node)nit.next();
		//	if(homeImpls.contains(n.getContained())){
		//		ManagesConnectCommand command=new ManagesConnectCommand();
		//		command.setSource(n);
				//command.setLabel("");
		//		command.setTarget(node);
		//		command.setView(view);
		//		command.execute();
		//	}
		//}
		//ComponentDef component=((ComponentImplDef)newObject).getComponent();
		if(component!=null){
			ImplConnectCommand command=new ImplConnectCommand("<<realized_comp>>");
			command.setSource(node);
			command.setView(view);
			for (Iterator nit= nodeList.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(component.equals(vn.getContained())){
					//command.setLabel("");
					command.setTarget(vn);
					command.execute();
					return;
				}
		    }
			Node vn = factory.createNode();
			vn.setContained(component);
		    vn.setX(rectangle.x+110);
		    vn.setY(rectangle.y+100);
		    vn.setWidth(100);
		    vn.setHeight(60);
			vn.setView(view);
			component.getNode().add(vn);
			view.getNode().add(vn);
			command.setTarget(vn);
			command.execute();
		}
		
		
		
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.SoftwarePackage, null, null,0));
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
    public void setTitle(String title) {
        this.title = title;
    }
    public void setType(String type) {
        this.type = type;
    }
    public void setAutor(String autor) {
        this.autor = autor;
    }
    public void setComponent(ComponentDef component) {
        this.component = component;
    }
    public void setLicenseKey(String licenseKey) {
        this.licenseKey = licenseKey;
    }
  
    public void setLicenseTextRef(String licensetextRef) {
        this.licenseTextRef = licenseTextRef;
    }
  
}
 
