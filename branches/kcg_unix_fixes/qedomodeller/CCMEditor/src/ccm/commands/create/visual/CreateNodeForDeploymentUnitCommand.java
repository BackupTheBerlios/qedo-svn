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

import CCMModel.Composition;
import CCMModel.Implementation;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.SoftwarePackage;
import ccm.commands.connect.Unit_CompositionConnectCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;



public class CreateNodeForDeploymentUnitCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForImplementationCommand";
	
	private String licenseKey;
	private String licenseTextRef;
	private String uuid;

	private Composition composition;
	//private Node parentNode;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForDeploymentUnitCommand() {
		super();
		setLabel(CreateCommand_Label);
	}

	 
	
	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
	    ((SoftwarePackage)container).getImpl().add(newObject);
		List parentNodes=container.getNode();
		for (Iterator it =parentNodes.iterator(); it.hasNext(); ){
			Node parentNode= (Node)it.next();
			parentNode.getContents().add(node);
		}
		
		//((Implementation)newObject).setLicenseKey(licenseKey);
		//((Implementation)newObject).setLicenseTexRef(licenseTextRef);
		((Implementation)newObject).setUuid(uuid);
		((Implementation)newObject).setComposition(composition);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.DeploymentUnit, null, null,0));
		Unit_CompositionConnectCommand command =new Unit_CompositionConnectCommand();
		List nodeList = view.getNode();
		command.setSource(node);
		command.setView(view);
		for (Iterator nit= nodeList.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(composition.equals(vn.getContained())){
				//command.setLabel("");
				command.setTarget(vn);
				command.execute();
				return;
			}
	    }
		Node vn = factory.createNode();
		vn.setContained(composition);
	    vn.setX(rectangle.x+180);
	    vn.setY(rectangle.y+160);
	    vn.setWidth(100);
	    vn.setHeight(60);
		vn.setView(view);
		composition.getNode().add(vn);
		view.getNode().add(vn);
		command.setTarget(vn);
		command.execute();
	//}
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setUUID(String uuid) {
        this.uuid = uuid;
    }
    public List getCompositions(){
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=this.getRootModule();
    	List compositions=mf.getAllContained(root,Composition.class);
    	return compositions;
    }
    public void setComposition(Composition composition) {
		this.composition=composition;
	}
   // public void setParentNode(Node node) {
  //      this.parentNode = node;
  //  }
    public void setLicenseKey(String licenseKey) {
        this.licenseKey = licenseKey;
    }
  
    public void setLicenseTextRef(String licensetextRef) {
        this.licenseTextRef = licensetextRef;
    }
    public SoftwarePackage getPackage(){
    	return (SoftwarePackage)container;
    }
    
}
 
 