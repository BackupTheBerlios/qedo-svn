/*
 * Created on 02.06.2005
 *
 */
package ccm.editors;

import org.eclipse.draw2d.ColorConstants;
import org.eclipse.gef.ContextMenuProvider;
import org.eclipse.gef.editparts.ScalableFreeformRootEditPart;
import org.eclipse.gef.palette.PaletteRoot;
import org.eclipse.gef.ui.parts.GraphicalViewerKeyHandler;
import org.eclipse.gef.ui.parts.ScrollingGraphicalViewer;
import org.eclipse.gef.ui.rulers.RulerComposite;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;

import CCMModel.Diagram;
import CCMModel.View;
import ccm.dragndrop.DiagramDropTargetListener;
import ccm.edit.GraphicalEditPartsFactory;


public class DiagramPage extends AbstractCCMPage{


	private View ccmView = null;
	private RulerComposite rulerComp;
	private Diagram diagram;

	 /**
     * Creates a new AbstractEditorPage instance.
     * @param parent the parent multi page editor
     * @param domain the edit domain
     */
    public DiagramPage(CCMEditor parent, Diagram diagram){
        super(parent);
        this.diagram = diagram;
    }

    public String getPageName(){
        return diagram.getIdentifier();
    }


	protected void createGraphicalViewer(Composite parent) {

		viewer = new ScrollingGraphicalViewer();
		ScalableFreeformRootEditPart root = new ScalableFreeformRootEditPart();
		
		rulerComp = new RulerComposite(parent, SWT.NONE);
		setGraphicalViewer(viewer);
		viewer.createControl(rulerComp);
		rulerComp.setGraphicalViewer((ScrollingGraphicalViewer) viewer); 
		viewer.getControl().setBackground(ColorConstants.listBackground);
	    viewer.setRootEditPart(root);
	    viewer.setKeyHandler(new GraphicalViewerKeyHandler(viewer));
	     
	    // hook the viewer into the editor
	    registerEditPartViewer(viewer);

	    // configure the viewer with drag and drop
	    configureEditPartViewer(viewer);
	    viewer.setEditPartFactory(new GraphicalEditPartsFactory());
	    
	    //viewer.setContents(getCcmView());
	    viewer.setContents(diagram.getView());
        
		ContextMenuProvider provider = new CCMEditorMenuProvider(getGraphicalViewer(),
																this.getCCMEditor().getActionRegistry());
		getGraphicalViewer().setContextMenu(provider);
		getSite().registerContextMenu(provider,getGraphicalViewer());
		
		viewer.addDropTargetListener(new DiagramDropTargetListener(viewer));
	}
	
	protected Control getGraphicalControl() {
		return rulerComp;
	}
	

	public View getCcmView() {
		return diagram.getView();
	}
	
	protected PaletteRoot createPaletteRoot() {
		return new CCMPaletteRoot();
	}
	
	protected  PaletteRoot getPaletteRoot(){
		if( root == null ){
			root = createPaletteRoot();
		}
		return root;
	}
}

