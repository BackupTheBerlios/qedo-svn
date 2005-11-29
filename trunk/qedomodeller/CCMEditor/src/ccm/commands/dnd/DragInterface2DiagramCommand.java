/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;
 
import org.eclipse.draw2d.geometry.Point;
 

import ccm.commands.connect.AbstItfDerivedConnectCommand;
import ccm.commands.connect.ComponentSupportsConnectCommand;
import ccm.commands.connect.HomeSupportsConnectCommand;
import ccm.commands.connect.ProvidesItfConnectCommand;
import ccm.commands.connect.UsesItfConnectCommand;
import ccm.commands.connect.ValueSupportsConnectCommand;
 

import CCMModel.AbstractInterfaceDef;
import CCMModel.InterfaceDef;
 
import CCMModel.Contained;
 
import CCMModel.Diagram;
 
import CCMModel.Node;
 
 

/**
 * @author siegercn
 */
public class DragInterface2DiagramCommand extends DragAbstInterface2DiagramCommand {

	/**
	 * @param model
	 * @param diagram
	 */
	public DragInterface2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		// TODO Auto-generated constructor stub
	}
	public DragInterface2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		// TODO Auto-generated constructor stub
	}
   
	
	public void execute() {
		super.execute();
		 
		
		List Values= ((InterfaceDef)contained).getValues();
		if(!Values.isEmpty()){
		  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(Values.contains(vn.getContained())){
				ValueSupportsConnectCommand command=new ValueSupportsConnectCommand();
				command.setSource(vn);
				//command.setLabel("");
				command.setTarget(n);
				command.setView(view);
				command.execute();
			}
		  }
		}
		List Components= ((InterfaceDef)contained).getComponents();
		if(!Components.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(Components.contains(vn.getContained())){
					ComponentSupportsConnectCommand command=new ComponentSupportsConnectCommand();
					command.setSource(vn);
					//command.setLabel("");
					command.setTarget(n);
					command.setView(view);
					command.execute();
				}
			  }
			}
		List Facet_ports= ((InterfaceDef)contained).getFacet_port();
		if(!Facet_ports.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(Facet_ports.contains(vn.getContained())){
					ProvidesItfConnectCommand command=new ProvidesItfConnectCommand();
					command.setSource(vn);
					//command.setLabel("");
					command.setTarget(n);
					command.setView(view);
					command.execute();
				}
			  }
			}
		List Homes= ((InterfaceDef)contained).getHomes();
		if(!Homes.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(Homes.contains(vn.getContained())){
					HomeSupportsConnectCommand command=new HomeSupportsConnectCommand();
					command.setSource(vn);
					//command.setLabel("");
					command.setTarget(n);
					command.setView(view);
					command.execute();
				}
			  }
			}
		List Receptacle_ports= ((InterfaceDef)contained).getReceptacle_port();
		if(!Receptacle_ports.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(Receptacle_ports.contains(vn.getContained())){
					UsesItfConnectCommand command=new UsesItfConnectCommand();
					command.setSource(vn);
					//command.setLabel("");
					command.setTarget(n);
					command.setView(view);
					command.execute();
				}
			  }
			}
		 
	}
}
 
