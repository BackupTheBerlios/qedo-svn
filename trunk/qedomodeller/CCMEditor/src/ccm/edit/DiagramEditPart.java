/*
 * Created on 20.05.2005
*/
package ccm.edit;

import org.eclipse.draw2d.IFigure;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.editparts.AbstractGraphicalEditPart;

/**
 * @author Holger Kinscher
 */
public class DiagramEditPart extends AbstractGraphicalEditPart implements
		EditPart {
	
	/**
     * Creates a new  instance.
     * @param node
     */
    public DiagramEditPart(Object clr){
		setModel(clr);
    }

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		return null;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
	}

}
