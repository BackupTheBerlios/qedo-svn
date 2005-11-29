/*
 * Created on 28.06.2005
*/
package ccm.commands.dnd;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.commands.Command;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

import ccm.commands.connect.EventPortEventConnectCommand;
import ccm.commands.connect.ProvidesItfConnectCommand;
import ccm.commands.connect.UsesItfConnectCommand;
import ccm.commands.constraints.PortConstraint;
import ccm.commands.create.visual.CreateNodeForComponentImplCommand;
import ccm.dialogs.CreateCompositionDialog;
import ccm.dialogs.DragAndDropDialog;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;

import CCMModel.CCMModelFactory;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.Diagram;
import CCMModel.EmitsDef;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
import CCMModel.ExceptionDef;
import CCMModel.Field;
import CCMModel.HomeDef;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.PortLocation;
import CCMModel.PortNode;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.UsesDef;
import CCMModel.View;

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
		 
		List nodes=view.getNode();
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
		Iterator it = ((Container) contained).getContents().iterator();
 
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
