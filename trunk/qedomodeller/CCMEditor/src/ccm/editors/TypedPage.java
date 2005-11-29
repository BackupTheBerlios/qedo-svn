/*******************************************************************************
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0
 * which accompanies this distribution
 * Contributors:
 *     eddi
 *******************************************************************************/
package ccm.editors;

import java.util.Iterator;

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

import CCMModel.View;
import ccm.edit.GraphicalEditPartsFactory;

public class TypedPage extends AbstractCCMPage{


	private View ccmView=null;
	private RulerComposite rulerComp;
	

	 /**
     * Creates a new AbstractEditorPage instance.
     * @param parent the parent multi page editor
     * @param domain the edit domain
     */
    public TypedPage(CCMEditor parent){
        super(parent);
    }

    /* (non-Javadoc)
     * @see com.ibm.itso.sal330r.gefdemo.editor.AbstractEditorPage#getPageName()
     */
    protected String getPageName(){
        return "CCM-Component-Designer";
    }

	/* (non-Javadoc)
	 * @see org.eclipse.gef.ui.parts.GraphicalEditor#createGraphicalViewer(org.eclipse.swt.widgets.Composite)
	 */
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
	    
	    viewer.setContents(getCcmView());
        
		ContextMenuProvider provider = new CCMEditorMenuProvider(getGraphicalViewer(),
																this.getCCMEditor().getActionRegistry());
		getGraphicalViewer().setContextMenu(provider);
		getSite().registerContextMenu(provider,getGraphicalViewer());
	}
	
	protected Control getGraphicalControl() {
		return rulerComp;
	}
	

	public View getCcmView() {
		if(ccmView != null)return ccmView;
        Iterator it=getCCMEditor().getCCM().getView().iterator();
        while(it.hasNext()){
        	 View v=(View) it.next();
        	 if(v.getModuleDef()!=null)
        	 	if(v.getModuleDef().getIdentifier().equals("root"))
        	 		ccmView=v;
        }
		return ccmView;
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