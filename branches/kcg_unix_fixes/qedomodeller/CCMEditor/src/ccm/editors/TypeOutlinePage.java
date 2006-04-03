/*
 * Created on 20.01.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.editors;

import org.eclipse.core.runtime.IAdaptable;
import org.eclipse.draw2d.FigureCanvas;
import org.eclipse.draw2d.LightweightSystem;
import org.eclipse.draw2d.MarginBorder;
import org.eclipse.draw2d.Viewport;
import org.eclipse.draw2d.parts.ScrollableThumbnail;
import org.eclipse.draw2d.parts.Thumbnail;
import org.eclipse.gef.ContextMenuProvider;
import org.eclipse.gef.EditDomain;
import org.eclipse.gef.EditPartViewer;
import org.eclipse.gef.GraphicalViewer;
import org.eclipse.gef.LayerConstants;
import org.eclipse.gef.RootEditPart;
import org.eclipse.gef.editparts.ScalableFreeformRootEditPart;
import org.eclipse.gef.editparts.ZoomManager;
import org.eclipse.gef.ui.actions.ActionRegistry;
import org.eclipse.gef.ui.parts.ContentOutlinePage;
import org.eclipse.jface.action.Action;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.action.IToolBarManager;
import org.eclipse.jface.resource.ImageDescriptor;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.DisposeEvent;
import org.eclipse.swt.events.DisposeListener;
import org.eclipse.swt.widgets.Canvas;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Control;
import org.eclipse.ui.IActionBars;
import org.eclipse.ui.actions.ActionFactory;
import org.eclipse.ui.part.IPageSite;
import org.eclipse.ui.part.PageBook;

import CCMModel.CCM;
import CCMModel.ModuleDef;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;
import ccm.dragndrop.DiagramDragSourceListener;
import ccm.dragndrop.DiagramDropTargetListener;
import ccm.treeedit.TreePartFactory;


/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class TypeOutlinePage extends ContentOutlinePage implements IAdaptable{
	
	private PageBook pageBook;
	private Control outline;
	private Canvas overview;
	private IAction showOutlineAction, showOverviewAction;
	static final int ID_OUTLINE  = 0;
	static final int ID_OVERVIEW = 1;
	private Thumbnail thumbnail;
	private DisposeListener disposeListener;
	private ActionRegistry registry;
    private final EditDomain domain;
    
    private AbstractCCMPage editor;
    private CCMEditor ccmeditor;
    private ModuleDef module;
	private GraphicalViewer tpviewer;
	private CCM ccm;
    
	public TypeOutlinePage(EditPartViewer viewer,EditDomain domain){
		super(viewer);
		this.domain=domain;
	}
	public void init(IPageSite pageSite) {
		super.init(pageSite);
		registry = getActionRegistry();
		IActionBars bars = pageSite.getActionBars();
		String id = ActionFactory.UNDO.getId();
		bars.setGlobalActionHandler(id, registry.getAction(id));
		id = ActionFactory.REDO.getId();
		bars.setGlobalActionHandler(id, registry.getAction(id));
		id = ActionFactory.DELETE.getId();
		bars.setGlobalActionHandler(id, registry.getAction(id));
		bars.updateActionBars();
	}
	
	/**
	 * @return
	 */
	private ActionRegistry getActionRegistry() {
		return ccmeditor.getActionRegistry();
	}
	
	
	protected void configureOutlineViewer(){
		getViewer().setEditDomain(domain);
		getViewer().setEditPartFactory(new TreePartFactory());
		ContextMenuProvider provider = new CCMEditorMenuProvider(getViewer(), getActionRegistry());
		getViewer().setContextMenu(provider);
		getSite().registerContextMenu(
			"ccm.editors.outline.contextmenu", //$NON-NLS-1$
			provider, getSite().getSelectionProvider());
		getViewer().setKeyHandler(ccmeditor.getSharedKeyHandler());

		IToolBarManager tbm = getSite().getActionBars().getToolBarManager();
		showOutlineAction = new Action() {
			public void run() {
				showPage(ID_OUTLINE);
			}
		};
		showOutlineAction.setImageDescriptor(ImageDescriptor.createFromFile(
								CCMEditorPlugin.class,ProjectResources.OUTLINE)); //$NON-NLS-1$
		tbm.add(showOutlineAction);
		showOverviewAction = new Action() {
			public void run() {
				showPage(ID_OVERVIEW);
			}
		};
		showOverviewAction.setImageDescriptor(ImageDescriptor.createFromFile(
		        				CCMEditorPlugin.class,ProjectResources.OVERVIEW)); //$NON-NLS-1$
		tbm.add(showOverviewAction);
		
		getViewer().addDragSourceListener(new DiagramDragSourceListener(getViewer()));
		getViewer().addDropTargetListener(new DiagramDropTargetListener(getViewer()));
		showPage(ID_OUTLINE);
	}
	
	public void createControl(Composite parent){
		pageBook = new PageBook(parent, SWT.NONE);
		outline = getViewer().createControl(pageBook);
		overview = new Canvas(pageBook, SWT.NONE);
		pageBook.showPage(outline);
		configureOutlineViewer();
		hookOutlineViewer();
		initializeOutlineViewer();
	}
	
	public void dispose(){
		unhookOutlineViewer();
		if (thumbnail != null) {
			thumbnail.deactivate();
			thumbnail = null;
		}
		super.dispose();
	}
	
	public Object getAdapter(Class type) {
		if (type == ZoomManager.class)
			return tpviewer.getProperty(ZoomManager.class.toString());
		return null;
	}
	
	public Control getControl() {
		return pageBook;
	}
	
	protected void hookOutlineViewer(){
		ccmeditor.getSelectionSynchronizer().addViewer(getViewer());
	}
	
	protected void initializeOutlineViewer(){
		setContents(getCCM());
	}
	
	protected void initializeOverview() {
		LightweightSystem lws = new LightweightSystem(overview);
		RootEditPart rep = tpviewer.getRootEditPart();
		if (rep instanceof ScalableFreeformRootEditPart) {
			ScalableFreeformRootEditPart root = (ScalableFreeformRootEditPart)rep;
			thumbnail = new ScrollableThumbnail((Viewport)root.getFigure());
			thumbnail.setBorder(new MarginBorder(3));
			thumbnail.setSource(root.getLayer(LayerConstants.PRINTABLE_LAYERS));
			lws.setContents(thumbnail);
			disposeListener = new DisposeListener() {
				public void widgetDisposed(DisposeEvent e) {
					if (thumbnail != null) {
						thumbnail.deactivate();
						thumbnail = null;
					}
				}
			};
			getViewerCanvas().addDisposeListener(disposeListener);
			
		}
	}
	
	public void setContents(Object contents) {
		getViewer().setContents(contents);
	}
	
	protected void showPage(int id) {
		if (id == ID_OUTLINE) {
			showOutlineAction.setChecked(true);
			showOverviewAction.setChecked(false);
			pageBook.showPage(outline);
			if (thumbnail != null)
				thumbnail.setVisible(false);
		} else if (id == ID_OVERVIEW) {
			if (thumbnail == null)
				initializeOverview();
			showOutlineAction.setChecked(false);
			showOverviewAction.setChecked(true);
			pageBook.showPage(overview);
			thumbnail.setVisible(true);
		}
	}
	
	private FigureCanvas getViewerCanvas(){
		return (FigureCanvas)editor.getGraphicalViewer().getControl();
	}
	
	protected void unhookOutlineViewer(){
		ccmeditor.getSelectionSynchronizer().removeViewer(getViewer());
		if (disposeListener != null && getViewerCanvas() != null && !getViewerCanvas().isDisposed())
			getViewerCanvas().removeDisposeListener(disposeListener);
	}
	/**
	 * @param viewer The viewer to set.
	 */
	public void setViewer(GraphicalViewer viewer) {
		this.tpviewer = viewer;
	}
	/**
	 * @param editor The editor to set.
	 */
	public void setEditor(AbstractCCMPage editor) {
		this.editor = editor;
	}
	/**
	 * @param ccmeditor The ccmeditor to set.
	 */
	public CCMEditor getCCMEditor() {
		return ccmeditor;
	}
	/**
	 * @param ccmeditor The ccmeditor to set.
	 */
	public void setCCMEditor(CCMEditor ccmeditor) {
		this.ccmeditor = ccmeditor;
	}
	/**
	 * @return Returns the module.
	 */
	public ModuleDef getModule() {
		return module;
	}
	/**
	 * @param module The module to set.
	 */
	public void setModule(ModuleDef module) {
		this.module = module;
	}
	public void setCCM(CCM ccm){
		this.ccm=ccm;
	}
	public CCM getCCM(){
		return ccm;
	}
    /**
     * @return Returns the tpviewer.
     */
    public GraphicalViewer getTpviewer() {
        return tpviewer;
    }
    /**
     * @param tpviewer The tpviewer to set.
     */
    public void setTpviewer(GraphicalViewer tpviewer) {
        this.tpviewer = tpviewer;
    }
}