package ccm.dragndrop;

import org.eclipse.gef.EditPartViewer;
import org.eclipse.gef.Request;
import org.eclipse.gef.dnd.TemplateTransfer;
import org.eclipse.gef.dnd.TemplateTransferDropTargetListener;
import org.eclipse.gef.requests.CreateRequest;
import org.eclipse.gef.requests.CreationFactory;
import org.eclipse.swt.dnd.DND;

import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.Diagram;
import CCMModel.ModuleDef;
import CCMModel.Relation;
import ccm.edit.ViewEditPart;
import ccm.request.DragAndDropRequest;
import ccm.treeedit.CCMModelTreeEditPart;




/**
 * This listener handles model elements that are dropped onto
 * a diagram.
 * 
 */
public class DiagramDropTargetListener extends TemplateTransferDropTargetListener {

	EditPartViewer viewer = null;
	Object source = null;
	Object target = null;
	
	
	public DiagramDropTargetListener(EditPartViewer viewer) {
		super(viewer);
		this.viewer = viewer;
	}
	

	protected CreationFactory getFactory(Object template) {
		if ((template instanceof Contained
				&& ((Contained)template).getDefinedIn() instanceof ModuleDef)
				|| (template instanceof Relation)) {
			source = template;	// memorize source
			return new DropFactory(template);
		}
		
		return new DropFactory(source);
	}
	

	
	protected void handleDragOver() {

		super.handleDragOver();		
		getCurrentEvent().detail = DND.DROP_NONE;
		
		target = getTargetEditPart().getModel();

		if (getTargetEditPart() instanceof ViewEditPart) {
			if(!(source instanceof Diagram))
				getCurrentEvent().detail = DND.DROP_COPY;
		}
		
		if (getTargetEditPart() instanceof CCMModelTreeEditPart){
			
			getViewer().select(getTargetEditPart());		
			CCMModelTreeEditPart editpart = (CCMModelTreeEditPart) getTargetEditPart();
			
			// source and target must be different
			if (source == target) return;
			
			// cannot move a module into a submodule
			if (source instanceof ModuleDef && target instanceof ModuleDef) {
				Container current = (ModuleDef) target;
				while (current!=null){
					if (current==source) return;
					current = current.getDefinedIn();
				}
			}
	
			// model element has been dropped on a diagram
			if (target instanceof Diagram && !(source instanceof Diagram)) { 
				getCurrentEvent().detail = DND.DROP_COPY;
			}
				
			// model element has been dropped on a module
			if (target instanceof ModuleDef) {				
				getCurrentEvent().detail = DND.DROP_MOVE;
			}
				

		} 

	}



	protected Request createTargetRequest() {
		DragAndDropRequest request = new DragAndDropRequest();
		request.setFactory(getFactory(TemplateTransfer.getInstance().getTemplate()));
		
		if(getTargetEditPart() instanceof ViewEditPart)
			request.setLocation(getDropLocation());
		
		return request;
	}


	protected void updateTargetRequest() {
		((CreateRequest) getTargetRequest()).setLocation(getDropLocation());
	}
	
}
