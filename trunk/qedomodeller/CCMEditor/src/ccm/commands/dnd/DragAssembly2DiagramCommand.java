/*
 * Created on 28.09.2005
*/
package ccm.commands.dnd;

import org.eclipse.draw2d.geometry.Point;

import CCMModel.Contained;
import CCMModel.Diagram;
 

/**
 * @author siegercn
 */
public class DragAssembly2DiagramCommand extends AddModel2DiagramCommand{

	/**
	 * @param model
	 * @param diagram
	 */
	public DragAssembly2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		 
	}
	public DragAssembly2DiagramCommand(Contained model, Diagram diagram,Point location) {
		super(model, diagram,location);
		 
	}

	public void execute() {
		super.execute();

	}

}
  