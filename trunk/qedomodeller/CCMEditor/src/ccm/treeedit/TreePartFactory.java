/*
 * Created on 20.01.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.treeedit;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPartFactory;

import CCMModel.CCM;
import CCMModel.Node;
import CCMModel.View;


/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class TreePartFactory implements EditPartFactory{

	public EditPart createEditPart(EditPart context, Object model) {
		if (model instanceof CCM)
			return new CCMTreeEditPart((CCM) model);
		else if (model instanceof View)
			return new CCMViewTreeEditPart(model);
		else if (model instanceof Node)
			return new CCMNodeTreeEditPart(model);
		else
			return new CCMModelTreeEditPart((EObject) model);
	}

}
