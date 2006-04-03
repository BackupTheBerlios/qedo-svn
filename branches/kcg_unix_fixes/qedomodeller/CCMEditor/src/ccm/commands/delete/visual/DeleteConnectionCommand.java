/*
 * Created on 14.05.2005
*/
package ccm.commands.delete.visual;

import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import org.eclipse.gef.commands.Command;

import CCMModel.AbstractInterfaceDef;
import CCMModel.AssemblyConnection;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.ImplDef;
import CCMModel.Implementation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.ProvidesDef;
import CCMModel.SiSouDef;
import CCMModel.SinkDef;
import CCMModel.SoftwarePackage;
import CCMModel.UsesDef;
import CCMModel.ValueDef;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.CCMConstants;

/**
 * @author Holger Kinscher
 *  modifyed siegercn
 */
public class DeleteConnectionCommand extends Command {

	private ConnectionImpl connection;
	private View view;
	private ModuleDef root;
	private Contained  sourceModel;
	private Contained  targetModel;
	private boolean deleteRelation=false;
	private String connectionsLabel;
	/**
	 * 
	 */
	public DeleteConnectionCommand(ConnectionImpl n) {
		setConnectionModel(n);
		setView(n.getView());
		root=view.getModuleDef();
		sourceModel=n.getSource().getContained();
		targetModel=n.getTarget().getContained();
		connectionsLabel=connection.getConnectionDiscription().getLabel();
		
	}
	public DeleteConnectionCommand(ConnectionImpl n, boolean deleteRelation) {
		this(n);
		this.deleteRelation=deleteRelation;
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		//if(connection.getRelation()!=null)
		//  connection.getRelation().getConnection().remove(connection);
		connection.getSource().getConSource().remove(connection);
		connection.getTarget().getConnTarget().remove(connection);
		view.getConnection().remove(connection);
		List views=root.getView();
		
		for (int i=0;i<views.size();i++){
			 
			View v= (View) views.get(i);
			if (!v.equals(view)){
				//List cs=new ArrayList();
				List connections= v.getConnection();
				for (Iterator it = new Vector(connections).iterator();it.hasNext();){
					ConnectionImpl c= (ConnectionImpl) it.next();
					if(((Contained)c.getSource().getContained()).equals(sourceModel)
					   && ((Contained)c.getTarget().getContained()).equals(targetModel)){
						c .getSource().getConSource().remove(c);
						c .getTarget().getConnTarget().remove(c);
						v .getConnection().remove(c );
						//cs.add(c);
					}
					 
					
				}
				//v .getConnection().removeAll(cs );
				
			}
		}
		if(deleteRelation)
		   deleteralation();
		//view.eNotify(new CCMNotificationImpl(view, Notification.REMOVE,
        //        CCMNotificationImpl.CONNECTION, null, null,0));
		//connection.eNotify(new CCMNotificationImpl(connection, Notification.REMOVE,
        //        CCMNotificationImpl.CONNECTION, null, null,0));
	}
	/**
	 * 
	 */
	private void deleteralation() {
		if (sourceModel instanceof AbstractInterfaceDef){
			AbstractInterfaceDef abstitf=(AbstractInterfaceDef)sourceModel;
			if(connectionsLabel==CCMConstants.DERIVED_LABEL){
				abstitf.getBaseInterface().remove(targetModel);	
			}	
			return;
		}
		if (sourceModel instanceof HomeDef){
			HomeDef home=(HomeDef)sourceModel;
			if(connectionsLabel==CCMConstants.SUPPORT_LABEL){
				home.getHomeSupports_itf().remove(targetModel);	
			}
			
			if(connectionsLabel==CCMConstants.HOME_KEY_LABEL){
				home.setPrimaryKey(null);	
			}
			return;	
		}
		if (sourceModel instanceof ComponentDef){
			ComponentDef component=(ComponentDef)sourceModel;
			if(connectionsLabel==CCMConstants.SUPPORT_LABEL){
				component.getComponentSupports_itf().remove(targetModel);	
			}
			 
			if(connectionsLabel==CCMConstants.MANAGES_LABEL){
				component.getHomes().remove(targetModel);	
			}
			return;
		}
	//	if (sourceModel instanceof InterfaceDef){
			
	//	}
		if (sourceModel instanceof ValueDef){
			ValueDef value=(ValueDef)sourceModel;
			if(connectionsLabel==CCMConstants.SUPPORT_LABEL){
				value.getValueSupports_itf().remove(targetModel);	
			}
			 
			if(connectionsLabel==CCMConstants.ABSTRACT_DERIVED_LABEL){
				value.getAbstractBaseValue().remove(targetModel);	
			}
			if(connectionsLabel==CCMConstants.DERIVED_LABEL){
				value.setBasevalue(null);	
			}
			return;
		}
	//	if (sourceModel instanceof EventDef){
			
	//	}
		if (sourceModel instanceof EventPortDef && targetModel instanceof EventDef){
			EventPortDef eventPort=(EventPortDef)sourceModel;
			if(connectionsLabel==CCMConstants.EVENTPORT_EVENT_LABEL){
				eventPort.setEvent(null);	
			}
			return;
		}
		if (sourceModel instanceof ProvidesDef && targetModel instanceof InterfaceDef){
			ProvidesDef facet=(ProvidesDef)sourceModel;
			if(connectionsLabel==CCMConstants.PROVIDES_INTERFACE_LABEL){
				facet.setInterface(null);	
			}
			return;
		}
		
		if (sourceModel instanceof UsesDef && targetModel instanceof InterfaceDef){
			UsesDef receptacle=(UsesDef)sourceModel;
			if(connectionsLabel==CCMConstants.USES_INTERFACE_LABEL){
				receptacle.setInterface(null);	
			}
			return;
		}
		if (sourceModel instanceof UsesDef || sourceModel instanceof SinkDef
				|| sourceModel instanceof SiSouDef|| sourceModel instanceof ConsumesDef){
			AssemblyConnection aConnection=connection.getAssemblyConnection();
			aConnection.getTarget().setInstance(null);
			aConnection.getTarget().setFeature(null);
			aConnection.getSource().setInstance(null);
			aConnection.getSource().setFeature(null);
			//connetion.getSource().setInstance(null);
			aConnection.setAssembly(null);
			aConnection.setDefinedIn(null);
			aConnection.getConnection().clear();
			 
			//connection.getAssemblyConnection().getConnection().clear();
			
		}
		
		if (sourceModel instanceof ComponentImplDef){
			
		}
		if (sourceModel instanceof HomeImplDef){
			HomeImplDef homeImpl=(HomeImplDef)sourceModel;
			if(connectionsLabel==CCMConstants.MANAGES_LABEL){
				homeImpl.setComponentImpl(null);	
			}
			return;
		}
		if (sourceModel instanceof Composition){
			Composition composition=(Composition)sourceModel;
			if(connectionsLabel==CCMConstants.COMPOSITION_HOME_LABEL){
				composition.setHomeImpl(null);	
			}
			return;
		}
		 
		
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(sourceModel instanceof ImplDef &&targetModel instanceof AbstractInterfaceDef)
			return false;
		if(sourceModel instanceof Implementation &&targetModel instanceof Composition)
			return false;
		if(sourceModel instanceof SoftwarePackage&&targetModel instanceof ComponentDef)
			return false;
		return super.canExecute();
	}
	/**
	 * @return Returns the connection.
	 */
	public ConnectionImpl getConnectionModel() {
		return connection;
	}
	/**
	 * @param connection The connection to set.
	 */
	public void setConnectionModel(ConnectionImpl connection) {
		this.connection = connection;
	}
	/**
	 * @return Returns the view.
	 */
	public View getView() {
		return view;
	}
	/**
	 * @param view The view to set.
	 */
	public void setView(View view) {
		this.view = view;
	}
}
