/*
 * Created on 28.06.2005
*/
package ccm.commands.dnd;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.commands.Command;
import org.eclipse.swt.widgets.Shell;

import CCMModel.Assembly;
import CCMModel.AssemblyConnection;
import CCMModel.CCMModelFactory;
import CCMModel.ComponentDef;
import CCMModel.ComponentFeature;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.Connection;
import CCMModel.ConnectionsKind;
import CCMModel.Contained;
import CCMModel.ContainedFile;
import CCMModel.Container;
import CCMModel.DependentFile;
import CCMModel.Deploymentrequirement;
import CCMModel.Diagram;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
import CCMModel.ExceptionDef;
import CCMModel.Field;
import CCMModel.HomeDef;
import CCMModel.HomeInstantiation;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.PortLocation;
import CCMModel.PortNode;
import CCMModel.ProcessCollocation;
import CCMModel.Property;
import CCMModel.ProvidesDef;
import CCMModel.RegisterComponentInstance;
import CCMModel.Rule;
import CCMModel.SoftwarePackage;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.UsesDef;
import CCMModel.View;
import ccm.commands.connect.EventPortEventConnectCommand;
import ccm.commands.connect.HomeCreateComponentInstanceConnectCommand;
import ccm.commands.connect.ProvidesItfConnectCommand;
import ccm.commands.connect.Unit_CompositionConnectCommand;
import ccm.commands.connect.UsesItfConnectCommand;
import ccm.commands.constraints.PortConstraint;
import ccm.commands.create.visual.adds.AddPortCommand;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;

/**
 * @author Holger Kinscher
 */
public class AddModel2DiagramCommand extends Command {

	protected Diagram diagram;
	protected Contained contained;
	protected CCMModelFactory factory;
	protected Point location;
	protected  Shell shell;
    protected View view;
    protected Node n;
    protected List nodes;
    private ModelFactory mf=new ModelFactory();
    
	
	/**
	 * @param model
	 * @param newObject
	 */
	public AddModel2DiagramCommand(Contained model, Diagram diagram) {
		this.diagram = diagram;
		this.contained = model;
		factory = CCMModelManager.getFactory();
		location = new Point(50,50);
		view=diagram.getView();
		nodes=view.getNode();
	}
	
	

	public AddModel2DiagramCommand(Contained model, Diagram diagram, Point location ) {
		this.diagram = diagram;
		this.contained = model;
		factory = CCMModelManager.getFactory();
		view=diagram.getView();
		nodes=view.getNode();
		this.location = location;
		 
	}

	public boolean canExecute() {
		 
		nodes=view.getNode();
		for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node n=(Node)nit.next();
			if(n.getContained().equals(contained))
				return false;
			
		}
	 
			
		return super.canExecute();
	}

	public void execute() {
		View v=null;
		n= factory.createNode();
		n.setContained(contained);
		n.setView(view);
		n.setX(location.x);
		n.setY(location.y);
		if (contained instanceof HomeDef){
				n.setWidth(110);
				n.setHeight(65);
		}
		else if(contained instanceof SoftwarePackage){
			n.setWidth(150);
			n.setHeight(120);
		}
		else if(contained instanceof Assembly){
			n.setWidth(460);
			n.setHeight(320);
		}
		else{
				n.setWidth(90);
				n.setHeight(55);
			}
		if((contained instanceof ComponentDef)&&contained.getNode().size()>0){
			Node node= (Node)contained.getNode().get(0);
			v=node.getView();
			n.setX(node.getX());
			n.setY(node.getY());
			n.setWidth(node.getWidth());
			n.setHeight(node.getHeight());
		}
		contained.getNode().add(n);
		diagram.getView().getNode().add(n);
		addChildren(contained,n,v);
	}


	
	public void addChildren(Contained contained, Node n,View otherView) {
		
		if(contained instanceof Assembly){
			
			List aplist= ((Assembly)contained).getRules();
			for(Iterator pit=aplist.iterator();pit.hasNext();){
				Rule property=(Rule)pit.next();
				Node proNode=factory.createNode();
		    	property.getNode().add(proNode);
		    	proNode.setX(0);
		    	proNode.setY(0);
		    	proNode.setWidth(15);
		    	proNode.setHeight(8);
		    	n.getContents().add(proNode);
			}
			View v=((Node)contained.getNode().get(0)).getView();
			Map map= new HashMap();
			List processes= ((Assembly)contained).getProcessCollocation();
			int processSize=processes.size();
			for (int i=0;i<processSize;i++){
				ProcessCollocation process=(ProcessCollocation) processes.get(i);
				Node pNode=factory.createNode();
				process.getNode().add(pNode);
		    	pNode.setX(5+i*n.getWidth()/processSize);
		    	pNode.setY(15);
		    	pNode.setWidth(n.getWidth()/processSize-20);
		    	pNode.setHeight(n.getHeight()-30);
		    	n.getContents().add(pNode);
		    	
		    	List homeInstances=process.getHomeInstances();
		    	int homeSize=homeInstances.size();
		    	for (int j=0;j<homeSize;j++){
		    		HomeInstantiation homeInstance=(HomeInstantiation)homeInstances.get(j);
		    		Node hNode=factory.createNode();
		    		homeInstance.getNode().add(hNode);
			    	hNode.setX(5+j*pNode.getWidth()/homeSize);
			    	hNode.setY(18);
			    	hNode.setWidth(60);
			    	hNode.setHeight(40);
			    	pNode.getContents().add(hNode);
			    	map.put(homeInstance,hNode);
			    	
			    	List list=homeInstance.getPropertys();
					for(Iterator cit=list.iterator();cit.hasNext();){
						Property property=(Property)cit.next();
						Node proNode=factory.createNode();
				    	property.getNode().add(proNode);
				    	proNode.setX(0);
				    	proNode.setY(0);
				    	proNode.setWidth(hNode.getWidth());
				    	proNode.setHeight(8);
				    	hNode.getContents().add(proNode);
					}
					list=homeInstance.getRules();
					for(Iterator pit=list.iterator();pit.hasNext();){
						Rule property=(Rule)pit.next();
						Node proNode=factory.createNode();
				    	property.getNode().add(proNode);
				    	proNode.setX(0);
				    	proNode.setY(0);
				    	proNode.setWidth(hNode.getWidth());
				    	proNode.setHeight(8);
				    	hNode.getContents().add(proNode);
					}
			    	
			    	List componentInstances= homeInstance.getComp();
			    	for (Iterator cit=componentInstances.iterator();cit.hasNext();){
			    		ComponentInstantiation compInstance=(ComponentInstantiation)cit.next();
			    		Node cnode=factory.createNode();
			    		compInstance.getNode().add(cnode);
						//node.setContained(newObject);
						cnode.setX(hNode.getX()+70);
						cnode.setY(hNode.getY()+100);
						cnode.setWidth(60);
						cnode.setHeight(40);
						map.put(compInstance,cnode);
						
						List plist=compInstance.getRegistration();
						for(Iterator pit=list.iterator();pit.hasNext();){
							RegisterComponentInstance registerInstance=(RegisterComponentInstance)pit.next();
							Node rNode=factory.createNode();
					    	registerInstance.getNode().add(rNode);
					    	rNode.setX(0);
					    	rNode.setY(0);
					    	rNode.setWidth(30);
					    	rNode.setHeight(15);
					    	cnode.getContents().add(rNode);
						}
						plist=compInstance.getPropertys();
						for(Iterator pit=list.iterator();pit.hasNext();){
							Property property=(Property)pit.next();
							Node proNode=factory.createNode();
					    	property.getNode().add(proNode);
					    	proNode.setX(0);
					    	proNode.setY(0);
					    	proNode.setWidth(cnode.getWidth());
					    	proNode.setHeight(8);
					    	cnode.getContents().add(proNode);
						}
						
						plist=compInstance.getRules();
						for(Iterator pit=list.iterator();pit.hasNext();){
							Rule property=(Rule)pit.next();
							Node proNode=factory.createNode();
					    	property.getNode().add(proNode);
					    	proNode.setX(0);
					    	proNode.setY(0);
					    	proNode.setWidth(cnode.getWidth());
					    	proNode.setHeight(8);
					    	cnode.getContents().add(proNode);
						}
						
						pNode .getContents().add(cnode);
						 
						HomeCreateComponentInstanceConnectCommand connect= new HomeCreateComponentInstanceConnectCommand();
						connect.setSource(hNode);
						connect.setTarget(cnode);
						connect.setView(view);
						connect.setLabel("<<create>>");
						connect.execute();
						  
						ComponentDef comp=homeInstance.getDeploymentUnit().getComposition().getHomeImpl().getComponentImpl().getComponent();
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
							command.setContainer(compInstance);
							 
							command.setComponentNode(cnode);
							command.setRootModule(mf.getRootModule(contained));
							//command.setView(view);
							command.execute();
							map.put(con,command.getPortNode());
							
						}
			    	}
		    		
		    	}
		    	
				
			}
	//		if (contained.getNode().size()>1){
	//		List connections= v.getConnection();
	//		for (Iterator conit=connections.iterator();conit.hasNext();){
	//			Connection connection=(Connection)conit.next();
	//			if(connection.getConnectionDiscription().getLabel().equals(" ")){
	//				Node source=(Node)map.get(connection.getSource().getContained());
	//				Node target=(Node)map.get(connection.getTarget().getContained());
	//				Connection con =factory.createConnection();
	//			     
	//			    con.setConnectionDiscription(factory.createConnectionDiscription());
	//			    con.setConnectionKind(connection.getConnectionKind());
	//			    
	//			    source.getConSource().add(con);
	//			    target.getConnTarget().add(con);
	//			    view.getConnection().add(con);
	//			}
	//		}
	//		}
			aplist= ((Assembly)contained).getConnection();
			for (Iterator conit=aplist.iterator();conit.hasNext();){
				AssemblyConnection acon=(AssemblyConnection)conit.next();
				ComponentFeature tfeature=acon.getTarget().getFeature();
				ComponentFeature sfeature=acon.getSource().getFeature();
				Connection con =factory.createConnection();
			    con.setConnectionDiscription(factory.createConnectionDiscription());
			    con.setConnectionKind(ConnectionsKind.INSTANCECONNECTION_LITERAL);
			    Node source=(Node)map.get(tfeature);
			    Node target;
			    if (sfeature!=null)
			    	target=(Node)map.get(sfeature);
			    else
			    	target=(Node)map.get(acon.getSource().getInstance());
			    source.getConSource().add(con);
			    target.getConnTarget().add(con);
			    view.getConnection().add(con);
			    con.setAssemblyConnection(acon);
				
				
			}
			
			
			return;
		}
		
		if(contained instanceof SoftwarePackage){
			List impls=((SoftwarePackage)contained).getImpl();
			for (Iterator it =impls.iterator();it.hasNext();){
				Implementation impl=(Implementation)it.next();
				Composition composition=impl.getComposition();

		    	Node iNode=factory.createNode();
		    	impl.getNode().add(iNode);
		    	iNode.setX( 5);
		    	iNode.setY( 8);
		    	iNode.setWidth(60);
		    	iNode.setHeight(40);
		    	n.getContents().add(iNode);
		    	
		    	//View view=parentNode.getView();
		    	Unit_CompositionConnectCommand command =new Unit_CompositionConnectCommand();
				//List nodeList = view.getNode();
				command.setSource(iNode);
				command.setView(view);
				for (Iterator nit= nodes.iterator();nit.hasNext(); ){
					Node vn=(Node)nit.next();
					if(composition.equals(vn.getContained())){
						//command.setLabel("");
						command.setTarget(vn);
						
						//command.execute();
						//return;
					}
			    }
				if(command.getTarget()==null){
					Node vn = factory.createNode();
					vn.setContained(composition);
					vn.setX(n.getX()+180);
					vn.setY(n.getY()+160);
					vn.setWidth(100);
					vn.setHeight(60);
					vn.setView(view);
					composition.getNode().add(vn);
					view.getNode().add(vn);
					command.setTarget(vn);
				}	
				command.execute();
		    
				List list=impl.getContainedFile();
				for(Iterator cit=list.iterator();cit.hasNext();){
					ContainedFile file=(ContainedFile)cit.next();
					Node fNode=factory.createNode();
			    	file.getNode().add(fNode);
			    	iNode.getContents().add(fNode);
				}
				list=impl.getDependentFiles();
				for(Iterator cit=list.iterator();cit.hasNext();){
					DependentFile file=(DependentFile)cit.next();
					Node fNode=factory.createNode();
			    	file.getNode().add(fNode);
			    	iNode.getContents().add(fNode);
				}
				list=impl.getRequirment();
				for(Iterator cit=list.iterator();cit.hasNext();){
					Deploymentrequirement file=(Deploymentrequirement)cit.next();
					Node fNode=factory.createNode();
			    	file.getNode().add(fNode);
			    	iNode.getContents().add(fNode);
				}
				
				list=impl.getPropertys();
				for(Iterator cit=list.iterator();cit.hasNext();){
					Property property=(Property)cit.next();
					Node pNode=factory.createNode();
			    	property.getNode().add(pNode);
			    	pNode.setX(0);
			    	pNode.setY(0);
			    	pNode.setWidth(iNode.getWidth());
			    	pNode.setHeight(8);
			    	iNode.getContents().add(pNode);
				}
			}
			return;
		}
		if(contained instanceof UnionDef  ){
			List fields= ((UnionDef)contained).getUnionMembers();
			 
			for (Iterator fit =fields.iterator();fit.hasNext();){
				    UnionField f = (UnionField)fit.next();
				    Node node=factory.createNode();
			        f.getNodeFromTyped().add(node);
					node.setX(0);
					node.setY(0);
					node.setWidth(-1);
					node.setHeight(-1);
					n.getContents().add(node);
					n.eNotify(new CCMNotificationImpl(n, Notification.ADD,
						       							   CCMNotificationImpl.FIELD, null, null,0));	
				
			}
		return;	
		}
		if(contained instanceof ExceptionDef||contained instanceof StructDef ){
			List fields= new ArrayList();
			if (contained instanceof ExceptionDef)
				fields= ((ExceptionDef)contained).getMembers();
			if (contained instanceof StructDef)
				fields= ((StructDef)contained).getMembers();
			for (Iterator fit =fields.iterator();fit.hasNext();){
				    Field f = (Field)fit.next();
				    Node node=factory.createNode();
			        f.getNodeFromTyped().add(node);
					node.setX(0);
					node.setY(0);
					node.setWidth(-1);
					node.setHeight(-1);
					n.getContents().add(node);
					n.eNotify(new CCMNotificationImpl(n, Notification.ADD,
						       							   CCMNotificationImpl.FIELD, null, null,0));	
				
			}
		return;	
		}
		if (!(contained instanceof Container) || contained instanceof ModuleDef)
			return;
		List nodes=null;
		if (otherView!=null)
			nodes=otherView.getNode();
		
		
		if(contained instanceof ComponentDef){
			ComponentDef component = (ComponentDef)contained;
			List ports=new ArrayList();
			if(!component.getFacet().isEmpty())
				ports.addAll(component.getFacet());
			if(!component.getReceptacle().isEmpty())
				ports.addAll( component.getReceptacle());
			if(!component.getPublishesDef().isEmpty())
				ports.addAll(component.getPublishesDef());
			if(!component.getConsumess().isEmpty())
				ports.addAll(component.getConsumess());
			if(!component.getEmitss().isEmpty())
				ports.addAll(component.getEmitss());
			if(!ports.isEmpty())
				addPorts( n,ports,otherView);
			
			 
		}
		List containeds=((Container) contained).getContents();
		if(contained instanceof ComponentDef){
			containeds.removeAll(((ComponentDef) contained).getFacet());
			containeds.removeAll(((ComponentDef) contained).getReceptacle());
			containeds.removeAll(((ComponentDef) contained).getPublishesDef());
			containeds.removeAll(((ComponentDef) contained).getConsumess());
			containeds.removeAll(((ComponentDef) contained).getEmitss());
			containeds.removeAll(((ComponentDef) contained).getSinkss());
			containeds.removeAll(((ComponentDef) contained).getSiSouss());
			containeds.removeAll(((ComponentDef) contained).getSourcess());
		}
		Iterator it = containeds.iterator();
		 
				while(it.hasNext()) {
					Iterator nit;
					Contained c = (Contained) it.next();
					Node n1 = factory.createNode();
					n1.setContained(c);
					c.getNode().add(n1);
					diagram.getView().getNode().add(n1);
					n.getContents().add(n1);
					addChildren(c,n1,null);
						
					}
	}



	/**
	 * @param n
	 * @param ports
	 */
	private void addPorts( Node n, List ports,View otherView) {
		Iterator nit;
		for (int p=0;p<ports.size();p++){
		Contained c=(Contained)ports.get(p);
		 
		PortNode n1 = factory.createPortNode();
		n1.setContained(c);
		n1.setHostNode(n);
		c.getNode().add(n1);
		diagram.getView().getNode().add(n1);
		
		PortConstraint constraint=new PortConstraint(new Rectangle(n.getX(),n.getY(),
	        n.getWidth(),n.getHeight()));
			constraint.setPortLoc(new Point(n.getX(),n.getY()),c, PortLocation.TOP);
			Point loc=constraint.getXyPoint();
			n1.setX(loc.x);
			n1.setY(loc.y);
			 
			n1.setLocation(constraint.getPortLocation());
		List nodes=null;
		if (otherView!=null)
			nodes=otherView.getNode();
			//n1.setLocation(portLocation[( portSize++)%3]);
		for( nit =nodes.iterator();nit.hasNext(); ){
			Node node=(Node)nit.next();
			if(node.getContained().equals(c)){
				n1.setX(node.getX());
				n1.setY(node.getY());
				n1.setLocation(node.getLocation());
				//nodes.remove(node);
				break;	
			}
		}
		InterfaceDef supportItf;
		if(c instanceof ProvidesDef){
			 supportItf=((ProvidesDef)c).getInterface();
			 if (supportItf!=null){
			 for( nit =view.getNode().iterator();nit.hasNext(); ){
			 	Node node=(Node)nit.next();
				if(node.getContained().equals(supportItf)){
					ProvidesItfConnectCommand cmd= new ProvidesItfConnectCommand();
					cmd.setSource(n1);
					cmd.setTarget(node);
					cmd.setView(view);
					cmd.execute();
			
				}
			 }
			 }
			}
		else if(c instanceof UsesDef){
			supportItf=((UsesDef)c).getInterface();
			 if (supportItf!=null){
				 for( nit =view.getNode().iterator();nit.hasNext(); ){
				 	Node node=(Node)nit.next();
					if(node.getContained().equals(supportItf)){
						UsesItfConnectCommand cmd= new UsesItfConnectCommand();
						cmd.setSource(n1);
						cmd.setTarget(node);
						cmd.setView(view);
						cmd.execute();
				
					}
				 }
				
			}
			}
		else {
			EventPortDef eventPort = (EventPortDef)c;
			 EventDef event=eventPort.getEvent();
			 if (event!=null){
			 	for( nit =view.getNode().iterator();nit.hasNext(); ){
				 	Node node=(Node)nit.next();
					if(node.getContained().equals(event)){
						EventPortEventConnectCommand cmd= new EventPortEventConnectCommand();
						cmd.setSource(n1);
						cmd.setTarget(node);
						cmd.setView(view);
						cmd.execute();
				
					}
				 }
			 }
			  
			}
		
		//addChildren(c,n1,null);
		
		
	}
	}

}
