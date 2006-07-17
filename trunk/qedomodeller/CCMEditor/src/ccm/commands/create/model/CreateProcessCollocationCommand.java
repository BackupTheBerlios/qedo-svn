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

import CCMModel.Assembly;
import CCMModel.Node;
import CCMModel.ProcessCollocation;
import ccm.CCMConstants;


public class CreateProcessCollocationCommand extends CreateModelCommand{
	
	 
	
	private int  cardinality;
	private String destination;
	private Node parentNode;
	private Node opNode;
	 
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateProcessCollocationCommand() {
		super(ProcessCollocation.class);
	}


	
	public boolean canExecute() {
		if(!(container instanceof Assembly))
			return false;
		return true;
	}
	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		//setNewObject(factory.createProcessCollocation());
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
		((Assembly)container).getConfig().getProcessCollocation().add(newObject);
		 
		((ProcessCollocation)newObject).setCardinality(cardinality);
		((ProcessCollocation)newObject).setDestination(destination);
		
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	((ProcessCollocation)newObject).getNode().add(opNode);
	    	opNode.setX(parentNode.getX()+5);
	    	opNode.setY(parentNode.getY()+5);
	    	opNode.setWidth(parentNode.getWidth()/2-10);
	    	opNode.setHeight(parentNode.getHeight()-35);
	    	parentNode.getContents().add(opNode);
	    	 
	    }
		  
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
 
  
