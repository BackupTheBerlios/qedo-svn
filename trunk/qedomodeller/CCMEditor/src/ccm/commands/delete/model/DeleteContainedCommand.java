/*
 * Created on 16.06.2005
 */
package ccm.commands.delete.model;

import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.gef.commands.Command;

import ccm.commands.delete.DeleteCommandFactory;
import ccm.commands.delete.visual.DeleteComponentCommand;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.editors.CCMEditor;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;

import CCMModel.AbstractInterfaceDef;
import CCMModel.CCM;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.Connection;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.Diagram;
import CCMModel.EmitsDef;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
import CCMModel.ExceptionDef;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.IDLType;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.OperationDef;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.Relation;
import CCMModel.SiSouDef;
import CCMModel.SinkDef;
import CCMModel.SourceDef;
import CCMModel.StructDef;
import CCMModel.Typed;
import CCMModel.UnionDef;
import CCMModel.UsesDef;
import CCMModel.ValueDef;
import CCMModel.View;

public class DeleteContainedCommand extends Command {

	protected static final String DeleteModel_Label = "DeleteModelCommand";
	protected Contained model;
	protected CCMEditor editor;
	
	
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteContainedCommand() {
		super( DeleteModel_Label );
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 */
	public DeleteContainedCommand(Contained model) {
		super();
		this.model=model;
	}
	/**
	 * Execution of this command deletes a classifierRole
	 * completely.
	 */
	public void execute() {

		// remove nodes and connections
		//if (model instanceof OperationDef) {
		//	Command cmd1 = new DeleteOperationDefCommand(model);
		//	cmd1.execute();
		//}
		Iterator nodes = (new Vector(model.getNode())).iterator(); // NEED TO COPY THE LIST!
		while (nodes.hasNext()) {
			Node node = (Node) nodes.next();
			System.out.println("************** node.contd*: "+node.getContained());
			Command cmd = null;
			if (model instanceof ComponentDef) cmd = new DeleteComponentCommand(node);
		
			else cmd = new DeleteNodeCommand(node, node.getView(), node.getContained());
			//if (cmd.canExecute()) 
			cmd.execute();
		}

		//deleteRelations(model);
	
		if(model instanceof Container) {
		
			// delete contents
			Iterator it = ((Container)model).getContents().iterator();
			
			while(it.hasNext()) {
				Contained contd = (Contained) it.next();
				 
				//deleteRelations(contd);

				Command cmd;				
				if(contd instanceof OperationDef)
					cmd = new DeleteOperationDefCommand(contd);
				else if(contd instanceof ExceptionDef)
					cmd = new DeleteExceptionDefCommand(contd);
				else if(contd instanceof StructDef)
					cmd = new DeleteStructDefCommand(contd);
				else if(contd instanceof UnionDef)
					cmd = new DeleteUnionDefCommand(contd);
				else
					cmd = new DeleteContainedCommand(contd);
				
				cmd.execute();
				it = ((Container)model).getContents().iterator();
			}
		}
		
		if (model instanceof Diagram) {
			
			if (editor!=null) editor.closeDiagramPage((Diagram) model);
			View v = ((Diagram) model).getView();
			
			if(v.eContainer() instanceof CCM)
				((CCM)v.eContainer()).getView().remove(v);
			v.setCCM(null);
			
			v.getModuleDef().getView().remove(v);
			v.setModuleDef(null);
			
			Iterator nodeIt = v.getNode().iterator();
			while(nodeIt.hasNext()) {
				Node n = (Node) nodeIt.next();
				DeleteCommandFactory dcf = new DeleteCommandFactory();
				Command cmd = dcf.getDeleteCommand(n);
				cmd.execute();
				
				nodeIt = v.getNode().iterator();
			}
			
			Iterator conIt = v.getConnection().iterator();
			while(conIt.hasNext()) {
				Connection n = (Connection) conIt.next();
				v.getConnection().remove(n);
				n.setView(null);
				if(n.getRelation() != null)
					n.getRelation().getConnection().remove(n);
				
				conIt = v.getConnection().iterator();
			}
		}
		
		if(model instanceof Typed) {
			IDLType idlt = ((Typed) model).getIDLType();
			if(idlt != null)
				idlt.getTyped().remove(model);
		}
		
		if(model instanceof Composition) {
			HomeImplDef homeImpl=((Composition)model).getHomeImpl();
			//System.out.println("homeImpl.getCompose()"+homeImpl.getCompose());
			if (homeImpl!=null){
				System.out.println("homeImpl.getCompose()"+homeImpl.getComposition());
				homeImpl.getComposition().remove(model);
				System.out.println("homeImpl.getCompose()"+homeImpl.getComposition());
			}
			
			//if (homeImpl!=null){
			//	ModelFactory factory= new ModelFactory();
			//    List views=	factory.getRootModule(homeImpl).getView();
			//    for (Iterator vit= views.iterator();vit.hasNext();){
			//    	View view=(View)vit.next();
			//    	List connects=view.getConnection();
			    	
			//    	 for (Iterator cit= connects.iterator();cit.hasNext();){
			//    	 	Connection connection=(Connection)cit.next();
			//  	 	if(connection.getSource().getContained().equals(model))
			//    	 		view.getConnection().remove(connection);
			//    	 	break;
			//    	 }
			    	
			//    }
				
			//}
			
		}
		if(model instanceof ComponentImplDef) {
			ComponentDef component =((ComponentImplDef)model).getComponent();
			if (component !=null)
				component .getComponentImpl().remove(model);
			List homeImpls=((ComponentImplDef)model).getHomeImpl();
			for (int i=0;i<homeImpls.size();i++){
				Object o=homeImpls.get(i);
			  ((HomeImplDef)o).setComponentImpl(null);
			}	
		}
		if(model instanceof HomeImplDef) {
			 
			ComponentImplDef componentImpl=((HomeImplDef)model).getComponentImpl();
			if (componentImpl!=null)
				componentImpl.getHomeImpl().remove(model);
			HomeDef home =((HomeImplDef)model).getHome();
			if (home!=null)
                   home.getHomeImpl().remove(model);
			List compositions=((HomeImplDef)model).getComposition();
			for (int i=0;i<compositions.size();i++){
				((Composition)compositions.get(i)).setHomeImpl(null);
			}	
		}
		if(model instanceof HomeDef) {
			List HomeSupports_itfs=((HomeDef)model).getHomeSupports_itf();
			for (int i=0;i<HomeSupports_itfs.size();i++){
				((InterfaceDef)HomeSupports_itfs.get(i)).getHomes().remove(model);
			}
			 
			 
			ValueDef  value= ((HomeDef)model).getPrimaryKey();
			if (value!=null)
				value.getHomeEnd().remove(model);
			ComponentDef component=((HomeDef)model).getComponent();
			if (component!=null)
				component.getHomes().remove(model);
			//HomeDef home =((HomeImplDef)model).getHome();
			//if (home!=null)
             //      home.getHomeImpl().remove(model);
			List homeImpls=((HomeDef)model).getHomeImpl();
			for (int i=0;i<homeImpls.size();i++){
				((HomeImplDef)homeImpls.get(i)).setHome(null);
			}	
		}
		if(model instanceof ComponentDef) {
			List componentImpls=((ComponentDef)model).getComponentImpl();
			for (Iterator sit =componentImpls.iterator();sit.hasNext(); ){
				((ComponentImplDef)sit.next()).setComponent(null);
			}
			List homes=((ComponentDef)model).getHomes();
			for (int i=0;i<homes.size();i++){
				((HomeDef)homes.get(i)).setComponent(null);
			}	
			
			List ComponentSupports_itfs= ((ComponentDef)model).getComponentSupports_itf();
			for (int i=0;i<ComponentSupports_itfs.size();i++){
				((InterfaceDef)ComponentSupports_itfs.get(i)).getComponents().remove(model);
			}	
			 
		}
			
		if(model instanceof InterfaceDef) {
				List components=((InterfaceDef)model).getComponents();
				for (int i=0;i<components.size();i++){
					((ComponentDef)components.get(i)).getComponentSupports_itf().remove(model);
				}	
				List homes=((InterfaceDef)model).getHomes();
				for (int i=0;i<homes.size();i++){
					((HomeDef)homes.get(i)).getHomeSupports_itf().remove(model);
				}	
				List values=((InterfaceDef)model).getValues();
				for (int i=0;i<values.size();i++){
					((ValueDef)values.get(i)).getValueSupports_itf().remove(model);
				}	
				List Facet_ports=((InterfaceDef)model).getFacet_port();
				for (int i=0;i<Facet_ports.size();i++){
					((ProvidesDef)Facet_ports.get(i)).setInterface(null);
				}	
				List Receptacle_ports=((InterfaceDef)model).getReceptacle_port();
				for (int i=0;i<Receptacle_ports.size();i++){
					((UsesDef)Receptacle_ports.get(i)).setInterface(null);
				}	
				
				
		}
		
		if(model instanceof AbstractInterfaceDef) {
			List BaseInterfaces= ((AbstractInterfaceDef)model).getBaseInterface();
			for (int i=0;i<BaseInterfaces.size();i++){
				((AbstractInterfaceDef)BaseInterfaces.get(i)).getDerivedInterface().remove(model);
			}	
			List DerivedInterfaces=((AbstractInterfaceDef)model).getDerivedInterface();
			for (int i=0;i<DerivedInterfaces.size();i++){
				((AbstractInterfaceDef)DerivedInterfaces.get(i)).getBaseInterface().remove(model);
			} 
			
		}
		if(model instanceof ValueDef) {
			 
			List AbstractBaseValues =((ValueDef)model).getAbstractBaseValue();
			for (int i=0;i<AbstractBaseValues.size();i++){
				((ValueDef)AbstractBaseValues.get(i)).getAbstractDerivedValue().remove(model);
			}	
			List AbstractDerivedValues =((ValueDef)model).getAbstractDerivedValue();
			for (int i=0;i<AbstractDerivedValues.size();i++){
				((ValueDef)AbstractDerivedValues.get(i)).getAbstractBaseValue().remove(model);
			}	
			ValueDef Basevalue =((ValueDef)model).getBasevalue();
			if (Basevalue!=null)
				Basevalue.getDerivedValue().remove(model);
			List DerivedValues =((ValueDef)model).getDerivedValue();
			for (int i=0;i<DerivedValues.size();i++){
				((ValueDef)DerivedValues.get(i)).setBasevalue(null);
			}	
			List homes =((ValueDef)model).getHomeEnd();
			for (int i=0;i<homes.size();i++){
				((HomeDef)homes.get(i)).setPrimaryKey(null);
			}	
			 
		}
		if(model instanceof EventDef) {
			 
			List eventPorts=((EventDef)model).getEventPorts();
			for (int i=0;i<eventPorts.size();i++){
				((EventDef)eventPorts.get(i)).getEventPorts().remove(model);
			}	
		}
		if(model instanceof EventPortDef) {
				 
			EventDef event=((EventPortDef)model).getEvent();	
			if (event!=null)
				event.getEventPorts().remove(model);
				 
		}
		if(model instanceof ProvidesDef){
			ComponentDef c=((ProvidesDef)model).getComp();
			c.getFacet().remove(model);
		}
		else if(model instanceof UsesDef){
			((UsesDef)model).getComp().getReceptacle().remove(model);
		}
		else if(model instanceof ConsumesDef){
			((ConsumesDef)model).getComp().getConsumess().remove(model);
		}
		else if(model instanceof EmitsDef){
			((EmitsDef)model).getComp().getEmitss().remove(model);
		}
		else if(model instanceof PublishesDef){
			((PublishesDef)model).getComp().getPublishesDef().remove(model);
		}
		else if(model instanceof SourceDef){
			((SourceDef)model).getComp().getPublishesDef().remove(model);
		}
		else if(model instanceof SinkDef){
			((SinkDef)model).getComp().getPublishesDef().remove(model);
		}
		else if(model instanceof SiSouDef){
			((SiSouDef)model).getComp().getPublishesDef().remove(model);
		}
		else{
		 Container container=model.getDefinedIn();
		 container.getContents().remove(model);
		}

	}
	
	/**
	 * Redoes an undo.
	 */
	public void redo() {
		model.getDefinedIn().getContents().remove(model);
	}
	
	/**
	 * Undoes an action done by this command
	 */
	public void undo() {
		model.getDefinedIn().getContents().add(model);
	}
	
	
	

	
	public boolean canExecute() {
				
		if (model instanceof ModuleDef && ((ModuleDef)model).getDefinedIn()==null) {
			return false;
		}		
		return true;
	}



	
	public Vector getRelations(Contained model) {

		Vector rel = new Vector();
		
		if (model instanceof AbstractInterfaceDef){
			rel.addAll(((AbstractInterfaceDef)model).getDerivedRelation());
			rel.addAll(((AbstractInterfaceDef)model).getBaseRelation());
		}
		if (model instanceof ModuleDef){
			rel.addAll(((ModuleDef)model).getRelations());
		}
		if (model instanceof InterfaceDef){
			rel.addAll(((InterfaceDef)model).getSupportsRelation());
			rel.addAll(((InterfaceDef)model).getInterfaceRelation());
		}
		if (model instanceof ComponentDef){
			rel.addAll(((ComponentDef)model).getSupportsRelation());
			rel.addAll(((ComponentDef)model).getCompHomeRelation());
			//rel.addAll(((ComponentDef)model).getCompHomeRelation());
		}
		if (model instanceof HomeDef){
			rel.addAll(((HomeDef)model).getSupportsRelation());
			rel.add(((HomeDef)model).getCompHomeRelation());
			//rel.add(((HomeDef)model).getIpmlementsRelation());
		}
		if (model instanceof ValueDef){
			rel.add(((ValueDef)model).getSupportsRelation());
			rel.add(((ValueDef)model).getBaseRelation());
			rel.add(((ValueDef)model).getDerivedRelation());
			rel.add(((ValueDef)model).getAbstractBaseRelation());
			rel.add(((ValueDef)model).getAbstractDerivedRelation());
		}
		if (model instanceof ProvidesDef) {
			rel.add(((ProvidesDef)model).getInterfaceRelation());
		}
		if (model instanceof PublishesDef) {
			rel.add(((PublishesDef)model).getEventPortEvent());
		}
		if (model instanceof EmitsDef) {
			rel.add(((EmitsDef)model).getEventPortEvent());
		}

		return rel;

	}

	
	private void deleteRelations(Contained model) {
		
		Iterator relations = getRelations(model).iterator();
		
		while (relations.hasNext()) {
			Relation rel = (Relation) relations.next();
			if (rel==null) continue;
			DeleteRelationCommand cmd = new DeleteRelationCommand(rel);
			if (cmd.canExecute()) {
				cmd.execute();
				
			}
		}

	}
	

	
	/**
	 * @return Returns the editor.
	 */
	public CCMEditor getEditor() {
		return editor;
	}
	
	
	/**
	 * @param editor The editor to set.
	 */
	public void setEditor(CCMEditor editor) {
		this.editor = editor;
	}



}