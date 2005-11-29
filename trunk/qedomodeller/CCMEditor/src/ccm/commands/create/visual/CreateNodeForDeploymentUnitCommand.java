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

import CCMModel.ComponentCategory;
import CCMModel.Composition;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;
import CCMModel.Node;

import ccm.model.CCMNotificationImpl;



public class CreateNodeForDeploymentUnitCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForImplementationCommand";
	
	private String licenseKey;
	private String licenseTextRef;
	private String uuid;
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
		List parentNodes=container.getNode();
		for (Iterator it =parentNodes.iterator(); it.hasNext(); ){
			Node parentNode= (Node)it.next();
			parentNode.getContents().add(node);
		}
		
		//((Implementation)newObject).setLicenseKey(licenseKey);
		//((Implementation)newObject).setLicenseTexRef(licenseTextRef);
		((Implementation)newObject).setUuid(uuid);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.DeploymentUnit, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setUUID(String uuid) {
        this.uuid = uuid;
    }
   // public void setParentNode(Node node) {
  //      this.parentNode = node;
  //  }
    public void setLicenseKey(String licenseKey) {
        this.licenseKey = licenseKey;
    }
  
    public void setLicenseTextRef(String licensetextRef) {
        this.licenseTextRef = licenseTextRef;
    }
  
}
 
 