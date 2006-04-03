/**
 * Created on 25.03.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.dragndrop;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.tools.DragTreeItemsTracker;

import CCMModel.Diagram;
import ccm.editors.CCMTreeViewer;
import ccm.request.AddDiagramRequest;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class CCMDragTracker extends DragTreeItemsTracker {

    
    private EditPart sourceEditPart;
    
    /**
     * @param sourceEditPart
     */
    public CCMDragTracker(EditPart sourceEditPart) {
        super(sourceEditPart);
        this.sourceEditPart=sourceEditPart;
    }

    /**
     * @see org.eclipse.gef.tools.AbstractTool#handleDoubleClick(int)
     */
    protected boolean handleDoubleClick(int button) {
    	 
    	if(sourceEditPart.getModel() instanceof Diagram) { 
    		CCMTreeViewer treeviewer = (CCMTreeViewer) getCurrentViewer();
    		treeviewer.getToPage().getCCMEditor().openDiagramPage((Diagram) sourceEditPart.getModel());
    		//treeviewer.setContentsToGraphical(((Diagram) sourceEditPart.getModel()).getView());
    	}
        return super.handleDoubleClick(button);
    }
    
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.TargetingTool#getTargetEditPart()
	 */
	protected EditPart getTargetEditPart() {
		return super.getTargetEditPart();
	}
	
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#handleDragStarted()
	 */
	protected boolean handleDragStarted() {
		createTargetRequest();
		return true;
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#handleDrag()
	 */
	protected boolean handleDrag() {
		return super.handleDrag();
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#handleDragInProgress()
	 */
	protected boolean handleDragInProgress() {
		return super.handleDragInProgress();
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#movedPastThreshold()
	 */
	protected boolean movedPastThreshold() {
		return super.movedPastThreshold();
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.Tool#activate()
	 */
	public void activate() {
		//setState(AbstractTool.STATE_DRAG_IN_PROGRESS);
		//setViewer(sourceEditPart.getViewer());		
		setTargetRequest(new AddDiagramRequest(null));
		super.activate();
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#handleViewerEntered()
	 */
	protected boolean handleViewerEntered() {
		return super.handleViewerEntered();
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.TargetingTool#handleEnteredEditPart()
	 */
	protected boolean handleEnteredEditPart() {
		return super.handleEnteredEditPart();
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.TargetingTool#handleEnteredEditPart()
	 */
	protected boolean handleExitedEditPart() {
		return super.handleEnteredEditPart();
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#handleButtonDown(int)
	 */
	protected boolean handleButtonDown(int button) {
		return super.handleButtonDown(button);
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.tools.AbstractTool#handleButtonUp(int)
	 */
	protected boolean handleButtonUp(int button) {
		setTargetRequest(createTargetRequest());
		return super.handleButtonUp(button);
	}
}
