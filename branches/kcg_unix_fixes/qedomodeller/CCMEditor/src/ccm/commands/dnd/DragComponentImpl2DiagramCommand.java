/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Point;

import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Contained;
import CCMModel.Diagram;
import CCMModel.Node;
import ccm.commands.connect.ImplConnectCommand;
import ccm.commands.connect.ManagesConnectCommand;
 

/**
 * @author siegercn
 */
public class DragComponentImpl2DiagramCommand extends AddModel2DiagramCommand{

	/**
	 * @param model
	 * @param diagram
	 */
	public DragComponentImpl2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		 
	}
	public DragComponentImpl2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		 
	}

	public void execute() {
		super.execute();
		List nodes=view.getNode();
		//homeimpls
		List homeImpls= ((ComponentImplDef)contained).getHomeImpl();
		if(!homeImpls.isEmpty()){
		  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(homeImpls.contains(vn.getContained())){
				ManagesConnectCommand command=new ManagesConnectCommand();
				command.setSource(vn);
				//command.setLabel("");
				command.setTarget(n);
				command.setView(view);
				command.execute();
			}
		  }
		}
		//component
		ComponentDef component=((ComponentImplDef)contained).getComponent();
		if(component!=null){
			ImplConnectCommand command=new ImplConnectCommand("<<component_impl>>");
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
		    vn.setY(location.y+20);
		    vn.setWidth(90);
		    vn.setHeight(55);
			vn.setView(view);
			component.getNode().add(vn);
			view.getNode().add(vn);
			command.setTarget(vn);
			command.execute();
		}
		
		
		//addChildren(contained,n);
	}

 

}
 
