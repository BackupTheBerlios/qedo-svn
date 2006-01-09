/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Point;

import CCMModel.ComponentImplDef;
import CCMModel.Contained;
import CCMModel.Diagram;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.Node;
import ccm.commands.connect.CompositionConnectHomeImplCommand;
import ccm.commands.connect.ImplConnectCommand;
import ccm.commands.connect.ManagesConnectCommand;
 

/**
 * @author siegercn
 */
public class DragHomeImpl2DiagramCommand extends AddModel2DiagramCommand{

	/**
	 * @param model
	 * @param diagram
	 */
	public DragHomeImpl2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		// TODO Auto-generated constructor stub
	}
	public DragHomeImpl2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		// TODO Auto-generated constructor stub
	}
    private List nodes;
	
	public void execute() {
		super.execute();
		nodes=view.getNode();
		//Compositions
		
		
		List compositions= ((HomeImplDef)contained).getComposition();
		if(!compositions.isEmpty()){
		  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(compositions.contains(vn.getContained())){
				CompositionConnectHomeImplCommand command=new CompositionConnectHomeImplCommand();
				command.setSource(vn);
				//command.setLabel("");
				command.setTarget(n);
				command.setView(view);
				command.execute();
			}
		  }
		}
		
		// componentImpl
		ComponentImplDef componentImpl= ((HomeImplDef)contained).getComponentImpl();
		if(componentImpl!=null){
			ManagesConnectCommand command=new ManagesConnectCommand();
			command.setSource(n);
			command.setView(view);
		    for (Iterator nit= nodes.iterator();nit.hasNext(); ){
		    	Node vn=(Node)nit.next();
		    	if(componentImpl.equals(vn.getContained())){
				//command.setLabel("");
				command.setTarget(vn);
				command.execute();
				connectHome();
				return;
				
			}
		}
		//Node vn = factory.createNode();
		//vn.setContained(componentImpl);
	    //vn.setX(location.x+220);
	    //vn.setY(location.y-40);
	    //vn.setWidth(90);
	    //vn.setHeight(55);
		//vn.setView(view);
		//componentImpl.getNode().add(vn);
		//view.getNode().add(vn);
		//command.setTarget(vn);
		//command.execute();
		
		
		}
		connectHome();
	}
	private void connectHome(){	
	//homeDef
		HomeDef home=((HomeImplDef)contained).getHome();
		if(home!=null){
			ImplConnectCommand command=new ImplConnectCommand("<<home_impl>>");
			command.setSource(n);
			command.setView(view);
			for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(home.equals(vn.getContained())){
					//command.setLabel("");
					command.setTarget(vn);
					command.execute();
					return;
				}
		    }
			Node vn = factory.createNode();
			vn.setContained(home);
		    vn.setX(location.x+220);
		    vn.setY(location.y+80);
		    vn.setWidth(100);
		    vn.setHeight(60);
			vn.setView(view);
			home.getNode().add(vn);
			view.getNode().add(vn);
			command.setTarget(vn);
			command.execute();
		}
		
		
		//addChildren(contained,n);
	}
}
 


 