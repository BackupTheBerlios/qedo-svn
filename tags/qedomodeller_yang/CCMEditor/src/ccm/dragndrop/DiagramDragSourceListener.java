package ccm.dragndrop;

import java.util.List;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.EditPartViewer;
import org.eclipse.gef.dnd.AbstractTransferDragSourceListener;
import org.eclipse.gef.dnd.TemplateTransfer;
import org.eclipse.swt.dnd.DragSourceEvent;

import CCMModel.Contained;
import CCMModel.ModuleDef;
import ccm.treeedit.CCMModelTreeEditPart;

public class DiagramDragSourceListener extends AbstractTransferDragSourceListener {

	public DiagramDragSourceListener(EditPartViewer viewer) {
		super(viewer,TemplateTransfer.getInstance());
	}

	public void dragSetData(DragSourceEvent event) {
		event.data = getTemplate();
	}
	
	/**
	 * Cancels the drag if the selected item does not represent a PaletteTemplateEntry.
	 * @see org.eclipse.swt.dnd.DragSourceListener#dragStart(DragSourceEvent)
	 */
	public void dragStart(DragSourceEvent event) {
		Object template = getTemplate();
		if (!(template instanceof Contained
						&& ((Contained)template).getDefinedIn() instanceof ModuleDef)
	//					&& !(template instanceof Relation)
						)
			event.doit = false;
		
		TemplateTransfer.getInstance().setTemplate(template);
	}
	
	/**
	 * @see AbstractTransferDragSourceListener#dragFinished(DragSourceEvent)
	 */
	public void dragFinished(DragSourceEvent event) {
		TemplateTransfer.getInstance().setTemplate(getTemplate());
	}

	/**
	 * A helper method that returns <code>null</code> or the <i>template</i> Object from the
	 * currently selected EditPart.
	 * @return the template
	 */
	protected Object getTemplate() {
		List selection = getViewer().getSelectedEditParts();
		if (selection.size() == 1) {
			EditPart editpart = (EditPart)getViewer().getSelectedEditParts().get(0);
			if(editpart instanceof CCMModelTreeEditPart){
				Object model = editpart.getModel(); 
				return model;
			}
		}
		return null;
	}
}
