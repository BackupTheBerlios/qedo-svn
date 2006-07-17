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

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.eclipse.emf.common.notify.Notification;

import CCMModel.ComponentFile;
import CCMModel.FinderServiceKind;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.Implementation;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.ProcessCollocation;
import ccm.CCMConstants;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;



public class CreateHomeInstanceCommand extends CreateModelCommand{
	
	private int  cardinality;
	private String regName;
	private FinderServiceKind service;
	private HomeImplDef homeImpl;
	private Implementation impl;
	//private boolean isLocal=false;
	private Node parentNode;
	private Node opNode;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateHomeInstanceCommand() {
		super(HomeInstantiation.class);
	}
   
	public boolean canExecute() {
		if(!(container instanceof ProcessCollocation))
			return false;
		return true;
	}

	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		//if( impl.getComposition().getHomeImpl()==null)
		//setNewObject(factory.createHomeInstantiation());
		//super.execute();
		newObject.setIdentifier(identifier);
		newObject.setVersion(version);
		/* modified by tri */
		
		newObject.setAbsoluteName(container.getIdentifier() + ":" + identifier);
		/*
		if(container.getAbsoluteName().trim().length()!=0)
		    newObject.setAbsoluteName(container.getAbsoluteName() + ":" + container.getIdentifier());
		else
		    newObject.setAbsoluteName(container.getIdentifier());
		*/

		// TODO
		newObject.setRepositoryId(CCMConstants.getRepositoryIdString(newObject.getAbsoluteName(),identifier,version));
	     
	    	
	    container.getContents().add(newObject);
	    ((ProcessCollocation)container).getHomeInstances().add(newObject);
		
		((HomeInstantiation)newObject).setCardinality(cardinality);
		((HomeInstantiation)newObject).setRegName(regName);
		((HomeInstantiation)newObject).setService(service);
		((HomeInstantiation)newObject).setType(homeImpl);
		((HomeInstantiation)newObject).setDeploymentUnit(impl);
		
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	((HomeInstantiation)newObject).getNode().add(opNode);
	    	opNode.setX(parentNode.getX()+5);
	    	opNode.setY(parentNode.getY()+8);
	    	opNode.setWidth(60);
	    	opNode.setHeight(40);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.ATTRIBUTE_DEF, null, null,0));
	    }
		 
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCardinality(int cardinality) {
        this.cardinality = cardinality;
    }
    public void setRegName(String name) {
        this.regName = name;
    }
    public void setImpl(Implementation impl) {
        this.impl = impl;
    }
    public void setHomeImpl(HomeImplDef homeImpl) {
        this.homeImpl = homeImpl;
    }
    public void setService(FinderServiceKind service) {
        this.service = service;
    }
    public List getImplementations(){
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=mf.getRootModule(container);
    	List impls= new ArrayList();
    	List componentfiles=((ProcessCollocation)container).getConfig().getComponentFile();
    	for (Iterator it=componentfiles.iterator();it.hasNext();){
    		impls.addAll(((ComponentFile)it.next()).getPackage().getImpl());
    	}
    	  
    	return impls;
    }
  
}
 
 