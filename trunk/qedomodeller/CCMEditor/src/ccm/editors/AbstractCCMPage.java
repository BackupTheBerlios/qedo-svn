/*******************************************************************************
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0
 * which accompanies this distribution
 * 
 * Contributors:
 *     eddi
 *******************************************************************************/
package ccm.editors;

import org.eclipse.core.resources.IMarker;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.gef.DefaultEditDomain;
import org.eclipse.gef.EditPartViewer;
import org.eclipse.gef.GraphicalViewer;
import org.eclipse.gef.commands.CommandStack;
import org.eclipse.gef.dnd.TemplateTransferDragSourceListener;
import org.eclipse.gef.palette.PaletteRoot;
import org.eclipse.gef.ui.actions.CopyTemplateAction;
import org.eclipse.gef.ui.actions.GEFActionConstants;
import org.eclipse.gef.ui.palette.PaletteViewer;
import org.eclipse.gef.ui.palette.PaletteViewerProvider;
import org.eclipse.gef.ui.palette.FlyoutPaletteComposite.FlyoutPreferences;
import org.eclipse.gef.ui.parts.GraphicalEditorWithFlyoutPalette;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.action.IMenuListener;
import org.eclipse.jface.action.IMenuManager;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorSite;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.actions.ActionFactory;
import org.eclipse.ui.part.IPageSite;

import CCMModel.View;

import ccm.CCMEditorPlugin;

public abstract class AbstractCCMPage
	extends GraphicalEditorWithFlyoutPalette{


	protected PaletteRoot root;
    /** the parent multi page editor */
    private final CCMEditor parent;
    /** the edit domain */
    private final DefaultEditDomain domain;

	
	protected static final String PALETTE_DOCK_LOCATION = "Dock location"; //$NON-NLS-1$
	protected static final String PALETTE_SIZE = "Palette Size"; //$NON-NLS-1$
	protected static final String PALETTE_STATE = "Palette state"; //$NON-NLS-1$
	protected static final int DEFAULT_PALETTE_SIZE = 130;
	
	protected GraphicalViewer viewer;
	
	static {
		CCMEditorPlugin.getDefault().getPreferenceStore().setDefault(
				PALETTE_SIZE, DEFAULT_PALETTE_SIZE);
	}
	
	   /**
     * Creates a new AbstractEditorPage instance.
     * @param parent the parent multi page editor
     * @param domain the edit domain
     */
    public AbstractCCMPage(CCMEditor parent){
        super();
        this.parent = parent;
        this.domain = new DefaultEditDomain(this);
        setEditDomain(domain);
    }
	   /**
     * Returns the multi page workflow editor this editor page is contained in.
     * @return the parent multi page editor
     */
    protected final CCMEditor getCCMEditor(){
        return parent;
    }
    
    
    /* (non-Javadoc)
     * @see org.eclipse.ui.IEditorPart#init(org.eclipse.ui.IEditorSite, org.eclipse.ui.IEditorInput)
     */
    public void init(IEditorSite site, IEditorInput input)
        throws PartInitException
    {
        setSite(site);
        setInput(input);
        this.setPartName(input.getName() + ": " + getPageName());
    }	
    /**
     * Returns the <code>CommandStack</code> of this editor page.
     * @return the <code>CommandStack</code> of this editor page
     */
    protected final CommandStack getCommandStack(){
        return getEditDomain().getCommandStack();
    }
    
    /* (non-Javadoc)
     * @see com.ibm.itso.sal330r.gefdemo.editor.AbstractEditorPage#getGraphicalViewerForZoomSupport()
     */
    protected GraphicalViewer getGraphicalViewer(){
        return viewer;
    }
    /* (non-Javadoc)
     * @see com.ibm.itso.sal330r.gefdemo.editor.AbstractEditorPage#getPageName()
     */
    protected abstract String getPageName();
    

	protected void configureEditPartViewer(EditPartViewer viewer) {
        if (viewer.getKeyHandler() != null)
            viewer.getKeyHandler().setParent(
                getCCMEditor().getSharedKeyHandler());
	}
	
	
	  /**
     * Hooks a <code>EditPartViewer</code> to the rest of the Editor.
     * 
     * <p>By default, the viewer is added to the SelectionSynchronizer, 
     * which can be used to keep 2 or more EditPartViewers in sync.
     * The viewer is also registered as the ISelectionProvider
     * for the Editor's PartSite.
     * 
     * @param viewer the viewer to hook into the editor
     */
    protected void registerEditPartViewer(EditPartViewer viewer){
        // the multi page network editor keeps track of synchronizing
        getCCMEditor().getSelectionSynchronizer().addViewer(viewer);

        // add viewer as selection provider
        getSite().setSelectionProvider(viewer);
    }
	
	protected CustomPalettePage createPalettePage() {
		return new CustomPalettePage(getPaletteViewerProvider()) {
			public void init(IPageSite pageSite) {
				super.init(pageSite);
				IAction copy = getActionRegistry().getAction(ActionFactory.COPY.getId());
				pageSite.getActionBars().setGlobalActionHandler(
						ActionFactory.COPY.getId(), copy);
			}
		};
	}
	
	protected PaletteViewerProvider createPaletteViewerProvider() {
		return new PaletteViewerProvider(getEditDomain()) {
			private IMenuListener menuListener;
			protected void configurePaletteViewer(PaletteViewer viewer) {
				super.configurePaletteViewer(viewer);
				viewer.setCustomizer(new CCMPaletteCustomizer());
				viewer.addDragSourceListener(new TemplateTransferDragSourceListener(viewer));
			}
			protected void hookPaletteViewer(PaletteViewer viewer) {
				super.hookPaletteViewer(viewer);
				final CopyTemplateAction copy = (CopyTemplateAction)getActionRegistry()
						.getAction(ActionFactory.COPY.getId());
				// viewer.addSelectionChangedListener(copy);
				if (menuListener == null)
					menuListener = new IMenuListener() {
						public void menuAboutToShow(IMenuManager manager) {
							manager.appendToGroup(GEFActionConstants.GROUP_COPY, copy);
						}
					};
				viewer.getContextMenu().addMenuListener(menuListener);
			}
		};
	}
	
	
	public void doSave(IProgressMonitor progressMonitor) {
	       // our policy: delegate saving to the parent
        getCCMEditor().doSave(progressMonitor);
	}
	
	public void doSaveAs() {
	    // our policy: delegate saving to the parent
        getCCMEditor().doSaveAs();
	}
	
	
	protected FlyoutPreferences getPalettePreferences() {
		return new FlyoutPreferences() {
			public int getDockLocation() {
				return CCMEditorPlugin.getDefault().getPreferenceStore()
						.getInt(PALETTE_DOCK_LOCATION);
			}
			public int getPaletteState() {
				return CCMEditorPlugin.getDefault().getPreferenceStore().getInt(PALETTE_STATE);
			}
			public int getPaletteWidth() {
				return CCMEditorPlugin.getDefault().getPreferenceStore().getInt(PALETTE_SIZE);
			}
			public void setDockLocation(int location) {
				CCMEditorPlugin.getDefault().getPreferenceStore()
						.setValue(PALETTE_DOCK_LOCATION, location);
			}
			public void setPaletteState(int state) {
				CCMEditorPlugin.getDefault().getPreferenceStore()
						.setValue(PALETTE_STATE, state);
			}
			public void setPaletteWidth(int width) {
				CCMEditorPlugin.getDefault().getPreferenceStore()
						.setValue(PALETTE_SIZE, width);
			}
		};
	}
	
	/*protected  PaletteRoot getPaletteRoot(){
		if( root == null ){
			root = createPaletteRoot();
		}
		return root;
	}*/
	
	protected abstract PaletteRoot createPaletteRoot();
	protected abstract View getCcmView();
	
	public void gotoMarker(IMarker marker) {}
	
	public boolean isDirty() {
	      // our policy: delegate saving to the parent
        // note: this method shouldn't get called anyway
        return getCCMEditor().isDirty();
	}
	
	public boolean isSaveAsAllowed() {
	     // our policy: delegate saving to the parent
        return getCCMEditor().isSaveAsAllowed();
	}
	
	/**
	 * @return Returns the domain.
	 */
	public DefaultEditDomain getDomain() {
		return domain;
	}
}