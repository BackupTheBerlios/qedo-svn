/*
 * Created on 28.06.2005
*/
package ccm.request;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.requests.CreateRequest;
import org.eclipse.gef.requests.CreationFactory;

/**
 * @author Holger Kinscher
 */
public class DragAndDropRequest extends CreateRequest {

	//private CreationFactory factory;
	private EditPart part;
	/**
	 * @param factory
	 */
	public void setFactory(CreationFactory factory) {
		super.setFactory(factory);
	}
	/**
	 * @param targetEditPart
	 */
	public void setTargetEditPart(EditPart targetEditPart) {
		this.part=targetEditPart;
	}
	
	public Object getNewObject() {
		return getFactory().getNewObject();
	}
	
}
