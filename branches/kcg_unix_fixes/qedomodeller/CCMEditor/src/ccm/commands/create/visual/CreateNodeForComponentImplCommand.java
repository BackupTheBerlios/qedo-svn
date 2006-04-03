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
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import ccm.commands.connect.ImplConnectCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;



public class CreateNodeForComponentImplCommand extends CreateNodeForContainerCommand{
	
	private static final String	CreateCommand_Label = "CreateNodeForComponentImplCommand";
	
	private ComponentCategory category;
	//private ComponentImplDef componentImpl;
	private ComponentDef component;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForComponentImplCommand() {
		super();
		setLabel(CreateCommand_Label);
		//componentImpl=(ComponentImplDef)newObject; 
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
	 
		super.execute();
		
		((ComponentImplDef)newObject).setCategory(category);
		((ComponentImplDef)newObject).setComponent(component);
		//if(!component.getComponentImpl().contains((ComponentImplDef)newObject))
		//    component.getComponentImpl().add((ComponentImplDef)newObject);
		
		//((InterfaceDef)newObject).setIsLocal(isLocal);
		node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.COMPONENTIMPL, null, null,0));
		
		//List homeImpls=new ArrayList();
		//if(component.getHomes()==null) return;
		//for (Iterator it =component.getHomes().iterator();it.hasNext();){
		//	HomeDef home=(HomeDef)it.next();
		//	List homeimpls=home.getHomeImpl();
		//	for (Iterator hit=homeimpls.iterator();hit.hasNext();){
		//		HomeImplDef homeImpl=(HomeImplDef)hit.next();
		//		homeImpls.add(homeImpl);
		//		homeImpl.setComponentImpl((ComponentImplDef)newObject);
		//		if(!((ComponentImplDef)newObject).getHomeImpl().contains(homeImpl))
		//		   ((ComponentImplDef)newObject).getHomeImpl().add(homeImpl);
		//	}
		//}
		
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
			ImplConnectCommand command=new ImplConnectCommand("<<component_impl>>");
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
		
		
		
	}
     
    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setCategory(ComponentCategory category) {
        this.category = category;
    }
    
    public List getComponentDefs(){
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=this.getRootModule();
    	List componentdefs=mf.getAllContained(root,ComponentDef.class);
    	return componentdefs;
    }
    public void setComponent(ComponentDef component) {
		this.component=component;
		
	}
  
}
 
