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

import CCMModel.ComponentCategory;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.impl.HomeDefImpl;

import ccm.commands.connect.ImplConnectCommand;
import ccm.commands.connect.ManagesConnectCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;



public class CreateNodeForHomeImplCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForHomeImplCommand";
	
	private ComponentCategory category;
	//private HomeImplDef homeImpl;
	private HomeDef home; 
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForHomeImplCommand() {
		super();
		setLabel(CreateCommand_Label);
		 
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		super.execute();
		//((Composition)newObject).setCategory(category);
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		((HomeImplDef)newObject).setHome(home);
		//if(!home.getHomeImpl().contains((HomeImplDef)newObject))
		//     home.getHomeImpl().add((HomeImplDef)newObject);
		
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.HOMEIMPL, null, null,0));

		//List homeImpls=new ArrayList();
		//if(home.getComponentDef()==null)
		//	return;
		//List componentImpls=home.getComponentDef().getComponentImpl();
		//if(componentImpls.isEmpty()) return;
		
		//for (Iterator it =componentImpls.iterator();it.hasNext();){
		//	ComponentImplDef componentimpl=(ComponentImplDef)it.next();
		//	if(!componentimpl.getHomeImpl().contains((HomeImplDef)newObject))
        //           componentimpl.getHomeImpl().add((HomeImplDef)newObject);
		//	((HomeImplDef)newObject).setComponentImpl(componentimpl);
		//	 
		 //}
		 
		List nodeList = view.getNode();
		//for (Iterator nit= nodeList.iterator();nit.hasNext(); ){
		//	Node n=(Node)nit.next();
		//	if(componentImpls.contains(n.getContained())){
		//		ManagesConnectCommand command=new ManagesConnectCommand();
		//		command.setSource(node);
		//		//command.setLabel("");
		//		command.setTarget(n);
		//		command.setView(view);
		//		command.execute();
		//	}
		//}
		
		ImplConnectCommand command=new ImplConnectCommand("<<home_impl>>");
		command.setSource(node);
		command.setView(view);
		for (Iterator nit= nodeList.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(home.equals(vn.getContained())){
				//command.setLabel("");
				command.setTarget(vn);
				command.execute();
				return;
			}
	    }
		Node vn = factory.createNode();
		vn.setContained(home);
	    vn.setX(rectangle.x+220);
	    vn.setY(rectangle.y+80);
	    vn.setWidth(100);
	    vn.setHeight(60);
		vn.setView(view);
		home.getNode().add(vn);
		view.getNode().add(vn);
		command.setTarget(vn);
		command.execute();
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCategory(ComponentCategory category) {
        this.category = category;
    }
    public List getHomeDefs(){
    	 
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=this.getRootModule();
    	List homedefs=mf.getAllContained(root,HomeDef.class);
    	return homedefs;
    }


	/**
	 * @param home
	 */
	public void setHome(HomeDef home) {
		this.home=home;
		
	}
  
}
 
 
