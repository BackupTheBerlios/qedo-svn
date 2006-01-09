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
import CCMModel.Node;
import CCMModel.ProcessCollocation;
import ccm.CCMConstants;
import ccm.model.CCMNotificationImpl;



public class CreateNodeForProcessCollocationCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForProcessCollocationCommand";
	
	private int  cardinality;
	private String destination;
	 
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForProcessCollocationCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		//super.execute();
		newObject.setIdentifier(identifier);
		newObject.setVersion(version);
		if(container.getAbsoluteName().trim().length()!=0)
		    newObject.setAbsoluteName(container.getAbsoluteName() + ":" + container.getIdentifier());
		else
		    newObject.setAbsoluteName(container.getIdentifier());
		newObject.setRepositoryId(CCMConstants.getRepositoryIdString(newObject.getAbsoluteName(),identifier,version));
	    
//		Configuration config =((Assembly)container).getConfig();
	    container.getContents().add(newObject);
	    ((Assembly)container).getProcessCollocation().add(newObject);
	    
	   
		
		
		List parentNodes=container.getNode();
		for (Iterator it =parentNodes.iterator(); it.hasNext(); ){
			 Node parentNode= (Node)it.next();
			 node=factory.createNode();
			 newObject.getNode().add(node);
			 node.setContained(newObject);
			 view.getNode().add(node);
			 node.setX(rectangle.x);
			 node.setY(rectangle.y);
			 node.setWidth(rectangle.width);
			 node.setHeight(rectangle.height);
			 parentNode.getContents().add(node);
		}
		
		((ProcessCollocation)newObject).setCardinality(cardinality);
		((ProcessCollocation)newObject).setDestination(destination);
		 
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.PROCESSCOLLOCATION, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCardinality(int cardinality) {
        this.cardinality = cardinality;
    }
    public void setDestinaation(String destination) {
        this.destination = destination;
    }
    
  
}
 
 