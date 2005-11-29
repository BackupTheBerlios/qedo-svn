/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;
import org.eclipse.draw2d.geometry.Point; 
import ccm.commands.connect.EventPortEventConnectCommand;
import CCMModel.EventDef; 
import CCMModel.Contained; 
import CCMModel.Diagram; 
import CCMModel.Node;

/**
 * @author siegercn
 */
public class DragEvent2DiagramCommand extends DragValue2DiagramCommand  {

	/**
	 * @param model
	 * @param diagram
	 */
	public DragEvent2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		// TODO Auto-generated constructor stub
	}
	public DragEvent2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		// TODO Auto-generated constructor stub
	}
   
	
	public void execute() {
		super.execute();
		 
		//Compositions
		
		List EventPorts= ((EventDef)contained).getEventPorts();
		
		if(!EventPorts.isEmpty()){
		  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(EventPorts.contains(vn.getContained())){
				EventPortEventConnectCommand command=new EventPortEventConnectCommand();
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
 
 