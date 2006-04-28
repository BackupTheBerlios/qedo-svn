/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Point;

import CCMModel.Composition;
import CCMModel.Contained;
import CCMModel.Diagram;
import CCMModel.HomeImplDef;
import CCMModel.Node;
import ccm.commands.connect.CompositionConnectHomeImplCommand;

/**
 * @author siegercn
 */
public class  DragComposition2DiagramCommand extends AddModel2DiagramCommand{

	/**
	 * @param model
	 * @param diagram
	 */
	public  DragComposition2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		// TODO Auto-generated constructor stub
	}
	public  DragComposition2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		// TODO Auto-generated constructor stub
	}



	public void execute() {
		super.execute();
		 
		   List nodes=view.getNode();
		// homeImpl
		HomeImplDef homeImpl=((Composition)contained).getHomeImpl();
		if(homeImpl!=null){
			CompositionConnectHomeImplCommand command=new CompositionConnectHomeImplCommand();
			command.setSource(n);
			command.setView(view);
		    for (Iterator nit= nodes.iterator();nit.hasNext(); ){
		    	Node vn=(Node)nit.next();
		    	if(homeImpl.equals(vn.getContained())){
				//command.setLabel("");
				command.setTarget(vn);
				command.execute();
				
			}
		}
		//Node vn = factory.createNode();
		//vn.setContained(homeImpl);
	    //vn.setX(location.x+220);
	    //vn.setY(location.y-20);
	    //vn.setWidth(100);
	    //vn.setHeight(60);
		//vn.setView(view);
		//homeImpl.getNode().add(vn);
		//view.getNode().add(vn);
		//command.setTarget(vn);
		//command.execute();
		
		}
		 
		//addChildren(contained,n);
	}

 

}
 
