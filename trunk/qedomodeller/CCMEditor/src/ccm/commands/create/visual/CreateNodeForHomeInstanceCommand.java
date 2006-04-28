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



public class CreateNodeForHomeInstanceCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForHomeInstanceCommand";
	
	private int  cardinality;
	private String regName;
	private FinderServiceKind service;
	private HomeImplDef homeImpl;
	private Implementation impl;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForHomeInstanceCommand() {
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
		/* modified by tri */
		newObject.setAbsoluteName(container.getAbsoluteName() +":" + identifier);
		
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
		((HomeInstantiation)newObject).setCardinality(cardinality);
		((HomeInstantiation)newObject).setRegName(regName);
		((HomeInstantiation)newObject).setService(service);
		((HomeInstantiation)newObject).setType(homeImpl);
		((HomeInstantiation)newObject).setDeploymentUnit(impl);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.HOMEIINSTANCE, null, null,0));
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
    	List componentfiles=((ProcessCollocation)container).getAssembly().getComponentFile();
    	for (Iterator it=componentfiles.iterator();it.hasNext();){
    		impls.addAll(((ComponentFile)it.next()).getPackage().getImpl());
    	}
    	  
    	return impls;
    }
  
}
 

 