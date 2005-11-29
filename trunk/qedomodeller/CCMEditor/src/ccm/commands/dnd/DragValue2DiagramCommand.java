/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;
 
import org.eclipse.draw2d.geometry.Point;
 
 
import ccm.commands.connect.AbstractDerivedConnectCommand;
import ccm.commands.connect.ValueDerivedConnectCommand;
 
import CCMModel.ValueDef;
 
import CCMModel.Contained;
 
import CCMModel.Diagram;
 
import CCMModel.Node;
 
 

/**
 * @author siegercn
 */
public class DragValue2DiagramCommand extends AddModel2DiagramCommand{

	/**
	 * @param model
	 * @param diagram
	 */
	public DragValue2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		// TODO Auto-generated constructor stub
	}
	public DragValue2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		// TODO Auto-generated constructor stub
	}
   
	
	public void execute() {
		super.execute();
		 
		//Compositions
		
		ValueDef baseValue= ((ValueDef)contained).getBasevalue();
		if (baseValue!=null){
			for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(baseValue.equals(vn.getContained())){
					ValueDerivedConnectCommand command=new ValueDerivedConnectCommand();
					command.setSource(n);
					//command.setLabel("");
					command.setTarget(vn);
					command.setView(view);
					command.execute();
				}
			  }
		}
			
		
		List DerivedValues= ((ValueDef)contained).getDerivedValue();
		
		if(!DerivedValues.isEmpty()){
		  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node vn=(Node)nit.next();
			if(DerivedValues.contains(vn.getContained())){
				ValueDerivedConnectCommand command=new ValueDerivedConnectCommand();
				command.setSource(vn);
				//command.setLabel("");
				command.setTarget(n);
				command.setView(view);
				command.execute();
			}
		  }
		}
	    List AbstractBaseValues= ((ValueDef)contained).getAbstractBaseValue();
	    if(!AbstractBaseValues.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(AbstractBaseValues.contains(vn.getContained())){
					AbstractDerivedConnectCommand command=new AbstractDerivedConnectCommand();
					command.setSource(n);
					//command.setLabel("");
					command.setTarget(vn);
					command.setView(view);
					command.execute();
				}
			  }
			}
		List AbstractDerivedValues= ((ValueDef)contained).getAbstractDerivedValue();
		if(!AbstractDerivedValues.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(AbstractDerivedValues.contains(vn.getContained())){
					AbstractDerivedConnectCommand command=new AbstractDerivedConnectCommand();
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
 