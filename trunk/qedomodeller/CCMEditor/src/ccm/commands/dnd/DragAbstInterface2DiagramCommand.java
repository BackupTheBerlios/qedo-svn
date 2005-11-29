/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;
 
import org.eclipse.draw2d.geometry.Point;
 

import ccm.commands.connect.AbstItfDerivedConnectCommand;
 

import CCMModel.AbstractInterfaceDef;
 
import CCMModel.Contained;
 
import CCMModel.Diagram;
 
import CCMModel.Node;
 
 

/**
 * @author siegercn
 */
public class DragAbstInterface2DiagramCommand extends AddModel2DiagramCommand{

	/**
	 * @param model
	 * @param diagram
	 */
	public DragAbstInterface2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		// TODO Auto-generated constructor stub
	}
	public DragAbstInterface2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		// TODO Auto-generated constructor stub
	}
   
	
	public void execute() {
		super.execute();
		 
		 
		//Compositions
		
		
		List baseInterfaces= ((AbstractInterfaceDef)contained).getBaseInterface();
		if(!baseInterfaces.isEmpty()){
		  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(baseInterfaces.contains(vn.getContained())){
				AbstItfDerivedConnectCommand command=new AbstItfDerivedConnectCommand();
				command.setSource(n);
				//command.setLabel("");
				command.setTarget(vn);
				command.setView(view);
				command.execute();
			}
		  }
		}
		List derivedInterfaces= ((AbstractInterfaceDef)contained).getDerivedInterface();
		if(!derivedInterfaces.isEmpty()){
		  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(derivedInterfaces.contains(vn.getContained())){
				AbstItfDerivedConnectCommand command=new AbstItfDerivedConnectCommand();
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