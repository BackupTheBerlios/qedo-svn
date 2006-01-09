/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;

import org.eclipse.draw2d.geometry.Point;

import CCMModel.ComponentDef;
import CCMModel.Contained;
import CCMModel.Diagram;
import CCMModel.Node;
import CCMModel.SoftwarePackage;
import ccm.commands.connect.ImplConnectCommand;
 

/**
 * @author siegercn
 */
public class DragSoftwarePackage2DiagramCommand extends AddModel2DiagramCommand{

	/**
	 * @param model
	 * @param diagram
	 */
	public DragSoftwarePackage2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		 
	}
	public DragSoftwarePackage2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		 
	}

	public void execute() {
		super.execute();
		
		//List nodeList=view.getNode();
		//homeimpls
		
		
		ComponentDef component= ((SoftwarePackage)contained).getComponent();
		ImplConnectCommand command=new ImplConnectCommand("<<realized_comp>>");
		command.setSource(n);
		command.setView(view);
		for (Iterator nit= nodes.iterator();nit.hasNext(); ){
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
	    vn.setX(location.x+220);
	    vn.setY(location.y+120);
	    vn.setWidth(100);
	    vn.setHeight(60);
		vn.setView(view);
		component.getNode().add(vn);
		view.getNode().add(vn);
		command.setTarget(vn);
		command.execute();
		
		 
	}

 

}
 