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
package ccm.commands.create.visual.adds;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Contained;
import CCMModel.HomeInstantiation;
import CCMModel.Node;
import CCMModel.ProcessCollocation;
import CCMModel.View;
import ccm.CCMConstants;
import ccm.commands.connect.HomeCreateComponentInstanceConnectCommand;
import ccm.commands.create.visual.CreateNodeForRuleOwnerCommand;
import ccm.model.CCMNotificationImpl;



public class AddComponentInstanceCommand extends CreateNodeForRuleOwnerCommand{
	
	private static final String	CreateCommand_Label = "AddComponentInstanceCommand";
	
	private int cardinality,startOder;
	private Node parentNode;
	private Rectangle constraint;

	private ComponentImplDef type;
	//private HomeInstantiation homeInstance;
	
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public AddComponentInstanceCommand() {
		super();
		setLabel(CreateCommand_Label);
	}

	public boolean canExecute() {
		if (container==null ||!(container instanceof HomeInstantiation)) return false;
		return true;
	}
	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		ProcessCollocation process= (ProcessCollocation)((HomeInstantiation)container).getDefinedIn();
				
		newObject.setIdentifier(identifier);
		newObject.setVersion(version);
		if(container.getAbsoluteName().trim().length()!=0)
		    newObject.setAbsoluteName(container.getAbsoluteName() + ":" + container.getIdentifier());
		else
		    newObject.setAbsoluteName(container.getIdentifier());
		newObject.setRepositoryId(CCMConstants.getRepositoryIdString(newObject.getAbsoluteName(),identifier,version));
	    
		container.getContents().add(newObject);
	    ((HomeInstantiation)container).getComp().add(newObject);
	    
	    List homeInstanceNodes=container.getNode();
		//List parentNodeList=process.getNode();
		for (Iterator it = homeInstanceNodes.iterator();it.hasNext();){
			Node homeInstanceNode=(Node)it.next();
			Node processNode=homeInstanceNode.getDefineIn();
			View aview=homeInstanceNode.getDefineIn().getDefineIn().getView();
			node=factory.createNode();
			newObject.getNode().add(node);
			node.setContained(newObject);
			node.setX(homeInstanceNode.getX()+70);
			node.setY(homeInstanceNode.getY()+100);
			node.setWidth(60);
			node.setHeight(40);
			
			homeInstanceNode.getDefineIn().getContents().add(node);
			 
			HomeCreateComponentInstanceConnectCommand connect= new HomeCreateComponentInstanceConnectCommand();
			connect.setSource(homeInstanceNode);
			connect.setTarget(node);
			connect.setView(aview);
			connect.setLabel("<<create>>");
			connect.execute();
			
			ComponentDef comp=((HomeInstantiation)container).getDeploymentUnit().getComposition().getHomeImpl().getComponentImpl().getComponent();
			List ports=new ArrayList();
			if (comp.getFacet()!=null)
				ports.addAll(comp.getFacet());
			if (comp.getReceptacle()!=null)
			    ports.addAll(comp.getReceptacle());
			if (comp.getConsumess()!=null)
				ports.addAll(comp.getConsumess());
			if (comp.getSinkss()!=null)
				ports.addAll(comp.getSinkss());
			if (comp.getPublishesDef()!=null)
				ports.addAll(comp.getPublishesDef());
			if (comp.getSiSouss()!=null)	
				ports.addAll(comp.getSiSouss());
			if (comp.getSourcess()!=null)
				ports.addAll(comp.getSourcess());
			if (comp.getEmitss()!=null)
				ports.addAll(comp.getEmitss());
			
			for (Iterator pit=ports.iterator();pit.hasNext();){
				Contained con=(Contained)pit.next();
				AddPortCommand command=new AddPortCommand(true);
				command.setContained(con);
				 
				command.setComponentNode(node);
				command.setContainer((ComponentInstantiation)newObject);
				command.setRootModule(getRootModule());
				//command.setView(aview);
				command.execute();
				
			}
			
		//view.getNode().add(node);
		}
		//super.execute();
		//container=homeInstance;
		((ComponentInstantiation)newObject).setCardinality(cardinality);
		((ComponentInstantiation)newObject).setStartOrder(startOder);
		((ComponentInstantiation)newObject).setType(type);
		
		
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.COMPONENTINSTACE, null, null,0));
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCardinality(int cardinality) {
        this.cardinality = cardinality;
    }
    public void setStartOder(int startOder) {
        this.startOder = startOder;
    }
    public void setType(ComponentImplDef type) {
        this.type = type;
    }
    public Node getParentNode() {
        return parentNode;
    }
    
    /**
     * @param parentNode The parentNode to set.
     */
  //  public void setParentNode(Node parentNode) {
  //      this.parentNode = parentNode;
  //  }
    public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}
}
 
 