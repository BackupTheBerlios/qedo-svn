/**
 * (c) Copyright group ccm
 * 
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss

 * 
 */
package ccm.editors;


import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.EventObject;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IResourceChangeEvent;
import org.eclipse.core.resources.IResourceChangeListener;
import org.eclipse.core.resources.IResourceDelta;
import org.eclipse.core.resources.IResourceDeltaVisitor;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IAdaptable;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.NullProgressMonitor;
import org.eclipse.core.runtime.Status;
import org.eclipse.core.runtime.SubProgressMonitor;
import org.eclipse.draw2d.PositionConstants;
import org.eclipse.gef.GEFPlugin;
import org.eclipse.gef.GraphicalViewer;
import org.eclipse.gef.KeyHandler;
import org.eclipse.gef.KeyStroke;
import org.eclipse.gef.RootEditPart;
import org.eclipse.gef.commands.CommandStack;
import org.eclipse.gef.commands.CommandStackListener;
import org.eclipse.gef.editparts.ScalableFreeformRootEditPart;
import org.eclipse.gef.editparts.ScalableRootEditPart;
import org.eclipse.gef.editparts.ZoomManager;
import org.eclipse.gef.ui.actions.ActionRegistry;
import org.eclipse.gef.ui.actions.AlignmentAction;
import org.eclipse.gef.ui.actions.DeleteAction;
import org.eclipse.gef.ui.actions.EditorPartAction;
import org.eclipse.gef.ui.actions.GEFActionConstants;
import org.eclipse.gef.ui.actions.RedoAction;
import org.eclipse.gef.ui.actions.SaveAction;
import org.eclipse.gef.ui.actions.SelectionAction;
import org.eclipse.gef.ui.actions.StackAction;
import org.eclipse.gef.ui.actions.UndoAction;
import org.eclipse.gef.ui.actions.UpdateAction;
import org.eclipse.gef.ui.actions.ZoomInAction;
import org.eclipse.gef.ui.actions.ZoomOutAction;
import org.eclipse.gef.ui.parts.ContentOutlinePage;
import org.eclipse.gef.ui.parts.SelectionSynchronizer;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.dialogs.ErrorDialog;
import org.eclipse.jface.dialogs.ProgressMonitorDialog;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Control;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.IEditorSite;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.ISelectionListener;
import org.eclipse.ui.IWorkbenchPart;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.actions.ActionFactory;
import org.eclipse.ui.dialogs.SaveAsDialog;
import org.eclipse.ui.part.FileEditorInput;
import org.eclipse.ui.part.MultiPageEditorPart;
import org.eclipse.ui.views.contentoutline.IContentOutlinePage;
import org.eclipse.ui.views.properties.IPropertySheetPage;
import org.eclipse.ui.views.properties.PropertySheetPage;

import CCMModel.AliasDef;
import CCMModel.Assembly;
import CCMModel.CCM;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.Diagram;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.ExceptionDef;
import CCMModel.ExternalInstance;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.SoftwarePackage;
import CCMModel.StructDef;
import CCMModel.UnionDef;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;
import ccm.action.AddComponentFileAction;
import ccm.action.AddEmitsSourceAction;
import ccm.action.AddEventSinkAction;
import ccm.action.AddEventSourceAction;
import ccm.action.AddFacetAction;
import ccm.action.AddHomeInstanceAction;
import ccm.action.AddIDLFileAction;
import ccm.action.AddImplementationAction;
import ccm.action.AddProcessCollocationAction;
import ccm.action.AddReceptacleAction;
import ccm.action.AliasDefAction;
import ccm.action.AttributeDefAction;
import ccm.action.CloseDiagramAction;
import ccm.action.ComponentInstanceAction;
import ccm.action.ConstantDefAction;
import ccm.action.ContainedFileAction;
import ccm.action.DepententFileAction;
import ccm.action.DeploymentRequirementAction;
import ccm.action.DiagramDefAction;
import ccm.action.EditOperationAction;
import ccm.action.EnumDefAction;
import ccm.action.ExceptionDefAction;
import ccm.action.FactoryDefAction;
import ccm.action.OperationDefAction;
import ccm.action.PropertyAction;
import ccm.action.RegisterComponentInstanceAction;
import ccm.action.StructDefAction;
import ccm.action.UnionDefAction;
import ccm.action.ValueBoxDefAction;
import ccm.action.ValueMemberDefAction;
import ccm.action.model.CreateModelAction;
import ccm.editors.tools.DelegatingCommandStack;
import ccm.editors.tools.DelegatingZoomManager;
import ccm.model.CCMModelManager;


/**
 * 
 * This class is the multi page editor for our sample applicatios.
 * It shows how to start implementing your own multi page GEF editor.
 * 
 * <p>The design is really simple. We share the same model over all pages but
 * each page is an independed graphical editor and could be used seperatly.
 * 
 *
 */
public class CCMEditor extends MultiPageEditorPart implements IAdaptable
{

	/**
	 * This class listens for command stack changes of the pages
	 * contained in this editor and decides if the editor is dirty or not.
	 *  
	 * 
	 */
	private class MultiPageCommandStackListener implements CommandStackListener
	{

		/** the observed command stacks */
		private List commandStacks = new ArrayList(2);

		/**
		 * Adds a <code>CommandStack</code> to observe.
		 * @param commandStack
		 */
		public void addCommandStack(CommandStack commandStack)
		{
			commandStacks.add(commandStack);
			commandStack.addCommandStackListener(this);
		}

		/* (non-Javadoc)
		 * @see org.eclipse.gef.commands.CommandStackListener#commandStackChanged(java.util.EventObject)
		 */
		public void commandStackChanged(EventObject event)
		{
			if (((CommandStack) event.getSource()).isDirty())
			{
				// at least one command stack is dirty, 
				// so the multi page editor is dirty too
				setDirty(true);
			}
			else
			{
				// probably a save, we have to check all command stacks
				boolean oneIsDirty = false;
				for (Iterator stacks = commandStacks.iterator();
					stacks.hasNext();
					)
				{
					CommandStack stack = (CommandStack) stacks.next();
					if (stack.isDirty())
					{
						oneIsDirty = true;
						break;
					}
				}
				setDirty(oneIsDirty);
			}
		}

		/**
		 * Disposed the listener
		 */
		public void dispose()
		{
			for (Iterator stacks = commandStacks.iterator(); stacks.hasNext();)
			{
				((CommandStack) stacks.next()).removeCommandStackListener(this);
			}
			commandStacks.clear();
		}

		/**
		 * Marks every observed command stack beeing saved.
		 * This method should be called whenever the editor/model
		 * was saved.
		 */
		public void markSaveLocations()
		{
			for (Iterator stacks = commandStacks.iterator(); stacks.hasNext();)
			{
				CommandStack stack = (CommandStack) stacks.next();
				stack.markSaveLocation();
			}
		}
	}
	/**
	 * This class listens to changes to the file system in the workspace, and
	 * makes changes accordingly.
	 * 1) An open, saved file gets deleted -> close the editor
	 * 2) An open file gets renamed or moved -> change the editor's input accordingly
	 * 
	 * @author group vilapower
	 */
	private class ResourceTracker
		implements IResourceChangeListener, IResourceDeltaVisitor
	{
		/* (non-Javadoc)
		 * @see org.eclipse.core.resources.IResourceChangeListener#resourceChanged(org.eclipse.core.resources.IResourceChangeEvent)
		 */
		public void resourceChanged(IResourceChangeEvent event)
		{
			IResourceDelta delta = event.getDelta();
			try
			{
				if (delta != null)
					delta.accept(this);
			}
			catch (CoreException exception)
			{
			    CCMEditorPlugin.getDefault().getLog().log(exception.getStatus());
				exception.printStackTrace();
			}
		}

		/* (non-Javadoc)
		 * @see org.eclipse.core.resources.IResourceDeltaVisitor#visit(org.eclipse.core.resources.IResourceDelta)
		 */
		public boolean visit(IResourceDelta delta)
		{
			if (delta == null
				|| !delta.getResource().equals(
					((IFileEditorInput) getEditorInput()).getFile()))
				return true;

			if (delta.getKind() == IResourceDelta.REMOVED)
			{
				if ((IResourceDelta.MOVED_TO & delta.getFlags()) == 0)
				{
					// if the file was deleted
					// NOTE: The case where an open, unsaved file is deleted is being handled by the 
					// PartListener added to the Workbench in the initialize() method.
					if (!isDirty())
						closeEditor(false);
				}
				else
				{
					// else if it was moved or renamed
					final IFile newFile =
						ResourcesPlugin.getWorkspace().getRoot().getFile(
							delta.getMovedToPath());
					Display display = getSite().getShell().getDisplay();
					display.asyncExec(new Runnable()
					{
						public void run()
						{
							setInput(new FileEditorInput(newFile));
						}
					});
				}
			}
			return false;
		}
	}

	/** the editor's action registry */
	private ActionRegistry actionRegistry;

	/** id of the compound tasks page */
	private int compoundTasksPageID;

	/** the delegating CommandStack */
	private DelegatingCommandStack delegatingCommandStack;
	
	private ContentOutlinePage outline;

	/**
	 * The <code>CommandStackListener</code> that listens for
	 * changes of the <code>DelegatingCommandStack</code>.
	 */
	private CommandStackListener delegatingCommandStackListener =
		new CommandStackListener()
	{
		public void commandStackChanged(EventObject event)
		{
			updateActions(stackActionIDs);
		}
	};

	/** the list of action ids that are editor actions */
	private List editorActionIDs = new ArrayList();

	/** the list of action ids that are to EditPart actions */
	private List editPartActionIDs = new ArrayList();

	/** the multi page editor's dirty state */
	private boolean isDirty = false;

	/** the <code>CommandStackListener</code> */
	private MultiPageCommandStackListener multiPageCommandStackListener;



	/** the resource tracker instance */
	private ResourceTracker resourceTracker;

	/** the selection listener */
	private ISelectionListener selectionListener = new ISelectionListener()
	{
		public void selectionChanged(IWorkbenchPart part, ISelection selection)
		{
			updateActions(editPartActionIDs);
		}
	};

	/** the shared key handler */
	private KeyHandler sharedKeyHandler;

	/** the list of action ids that are to CommandStack actions */
	private List stackActionIDs = new ArrayList();

	/** the selection synchronizer for the edit part viewer */
	private SelectionSynchronizer synchronizer;

	/** the undoable <code>IPropertySheetPage</code> */
	private PropertySheetPage undoablePropertySheetPage;

	/** this is our container */
	private CCM ccm;

	/** id of the typedPage */
	private int typedPageID;
	
	/** id of the modulePage */
	private int modulePageID;
	
	/** ids of diagram-pages */
//	private HashMap diagramPageIDs = new HashMap();
	public HashMap diagramPages = new HashMap();

	/**
	 * Adds an action to this editor's <code>ActionRegistry</code>.
	 * (This is a helper method.)
	 * 
	 * @param action the action to add.
	 */
	protected void addAction(IAction action)
	{
		getActionRegistry().registerAction(action);
	}

	/**
	 * Adds an editor action to this editor.
	 * 
	 * <p><Editor actions are actions that depend
	 * and work on the editor.
	 * 
	 * @param action the editor action
	 */
	protected void addEditorAction(EditorPartAction action)
	{
		getActionRegistry().registerAction(action);
		editorActionIDs.add(action.getId());
	}

	/**
	 * Adds an <code>EditPart</code> action to this editor.
	 * 
	 * <p><code>EditPart</code> actions are actions that depend
	 * and work on the selected <code>EditPart</code>s.
	 * 
	 * @param action the <code>EditPart</code> action
	 */
	protected void addEditPartAction(SelectionAction action)
	{
		getActionRegistry().registerAction(action);
		editPartActionIDs.add(action.getId());
	}

	/**
	 * Adds an <code>CommandStack</code> action to this editor.
	 * 
	 * <p><code>CommandStack</code> actions are actions that depend
	 * and work on the <code>CommandStack</code>.
	 * 
	 * @param action the <code>CommandStack</code> action
	 */
	protected void addStackAction(StackAction action)
	{
		getActionRegistry().registerAction(action);
		stackActionIDs.add(action.getId());
	}

	/**
	 * Closes this editor.
	 * @param save
	 */
	void closeEditor(final boolean save)
	{
		getSite().getShell().getDisplay().syncExec(new Runnable()
		{
			public void run()
			{
				getSite().getPage().closeEditor(CCMEditor.this, save);
			}
		});
	}

	/**
	 * Creates actions and registers them to the ActionRegistry.
	 */
	protected void createActions(){
		addStackAction(new UndoAction(this));
		addStackAction(new RedoAction(this));
		
		DeleteAction delA = new DeleteAction((IWorkbenchPart) this);
		delA.setLazyEnablementCalculation(true);
		
		addEditPartAction(delA);
		addEditPartAction(new AlignmentAction((IWorkbenchPart) this, PositionConstants.LEFT));
		addEditPartAction(new AlignmentAction((IWorkbenchPart) this, PositionConstants.RIGHT));
		addEditPartAction(new AlignmentAction((IWorkbenchPart) this, PositionConstants.TOP));
		addEditPartAction(new AlignmentAction((IWorkbenchPart) this, PositionConstants.BOTTOM));
		addEditPartAction(new AlignmentAction((IWorkbenchPart) this, PositionConstants.CENTER));
		addEditPartAction(new AlignmentAction((IWorkbenchPart) this, PositionConstants.MIDDLE));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				Composition.class));
		addEditPartAction(new CreateModelAction(this, 
				ComponentImplDef.class));
		addEditPartAction(new CreateModelAction(this, 
				HomeImplDef.class));
		addEditPartAction(new CreateModelAction(this, 
				SoftwarePackage.class));
		
		//addEditPartAction(new CreateModelAction(this, 
		//		Implementation.class));
		addEditPartAction(new CreateModelAction(this, 
				Assembly.class));
		//addEditPartAction(new CreateModelAction(this, 
		//		ProcessCollocation.class));
		//addEditPartAction(new CreateModelAction(this, 
		//		HomeInstantiation.class));
		addEditPartAction(new CreateModelAction(this, 
				ExternalInstance.class));
		 
		//***************************************************
		
		addEditPartAction(new CreateModelAction(this, 
				ModuleDef.class));
		
//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				ComponentDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				HomeDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				InterfaceDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				ValueDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				EventDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				ExceptionDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				ConstantDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				EnumDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				ValueBoxDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				AliasDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				StructDef.class));

//		 the new Action for creating an ComponentDef
		addEditPartAction(new CreateModelAction(this, 
				UnionDef.class));

		// the new Action for adding an OperationDef
		addEditPartAction(new OperationDefAction(this, 
		        OperationDefAction.CLASSIFIER_PROPERTY));
		// the new Action for adding an OperationDef
		addEditPartAction(new FactoryDefAction(this, 
		        FactoryDefAction.CLASSIFIER_PROPERTY));
		
//		 the new Action for adding an DiagramDef
		addEditPartAction(new DiagramDefAction(this, 
				DiagramDefAction.CLASSIFIER_PROPERTY));
		
//		 the new Action for adding an OperationDef
		addEditPartAction(new ConstantDefAction(this, 
		        ConstantDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new ExceptionDefAction(this, 
		        ExceptionDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new ValueMemberDefAction(this, 
		        ValueMemberDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new AttributeDefAction(this, 
		        AttributeDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new UnionDefAction(this, 
		        UnionDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new StructDefAction(this, 
		        StructDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new EnumDefAction (this, 
		        EnumDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new AliasDefAction (this, 
		        AliasDefAction.CLASSIFIER_PROPERTY));
//		 the new Action for adding an OperationDef
		addEditPartAction(new ValueBoxDefAction (this, 
		        ValueBoxDefAction.CLASSIFIER_PROPERTY));
		//		 the new Action for adding a facet
		addEditPartAction(new AddFacetAction(this, 
				AddFacetAction.CLASSIFIER_PROPERTY));

		//		 the new Action for adding a facet
		addEditPartAction(new AddReceptacleAction(this, 
				AddReceptacleAction.CLASSIFIER_PROPERTY));
		
//		 the new Action for adding a facet
		addEditPartAction(new AddEventSourceAction(this, 
				AddEventSourceAction.CLASSIFIER_PROPERTY));

		//		 the new Action for adding a facet
		addEditPartAction(new AddEmitsSourceAction(this, 
				AddEmitsSourceAction.CLASSIFIER_PROPERTY));
		
//		 the new Action for adding a facet
		addEditPartAction(new AddEventSinkAction(this, 
				AddEventSinkAction.CLASSIFIER_PROPERTY));
		
//		***************************************************
		addEditPartAction(new CloseDiagramAction(this, 
				CloseDiagramAction.CLASSIFIER_PROPERTY));
	//	addEditPartAction(new RuleAction(this, 
	//			RuleAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new AddIDLFileAction(this, 
				AddIDLFileAction.CLASSIFIER_PROPERTY));
		
		addEditPartAction(new ContainedFileAction(this, 
				ContainedFileAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new DepententFileAction(this, 
				DepententFileAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new DeploymentRequirementAction(this, 
				DeploymentRequirementAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new RegisterComponentInstanceAction(this, 
				RegisterComponentInstanceAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new PropertyAction(this, 
				PropertyAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new ComponentInstanceAction(this, 
				ComponentInstanceAction.CLASSIFIER_PROPERTY));
		
		addEditPartAction(new AddImplementationAction(this, 
				AddImplementationAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new AddProcessCollocationAction(this, 
				AddProcessCollocationAction.CLASSIFIER_PROPERTY));
		addEditPartAction(new AddHomeInstanceAction(this, 
				AddHomeInstanceAction.CLASSIFIER_PROPERTY));
		  
		addEditPartAction(new AddComponentFileAction(this, 
				AddComponentFileAction.CLASSIFIER_PROPERTY));
		
		addEditPartAction(new EditOperationAction(this, 
				EditOperationAction.CLASSIFIER_PROPERTY));
//		***************************************************
		
		addEditorAction(new SaveAction(this));
		//addEditorAction(new PrintAction(this));

		IAction zoomIn = new ZoomInAction(getDelegatingZoomManager());
		IAction zoomOut = new ZoomOutAction(getDelegatingZoomManager());
		addAction(zoomIn);
		addAction(zoomOut);
		getSite().getKeyBindingService().registerAction(zoomIn);
		getSite().getKeyBindingService().registerAction(zoomOut);
	}


	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#createPages()
	 */

	protected void createPages(){
		//createTypedPage();
		createModulePage();
	}

	
	
	public void openDiagramPage(Diagram diagram){
		 
		try{
			// check whether this diagram has already its own page
			if (diagramPages.containsKey(diagram)) {
				DiagramPage page = (DiagramPage) diagramPages.get(diagram);
				int pageCount =getPageCount();
				for (int i =0;i<pageCount;i++ ){
					if (getEditor(i)==page){
						setActivePage(i);
						return;
					}
						
				}
				
				 
			}
			 
			// create new page
			DiagramPage page = new DiagramPage(this, diagram);	
		    int id = addPage(page, getEditorInput());
		    diagramPages.put(diagram,page);
		 
	//		diagramPageIDs.put(diagram, new Integer(id));
			page = (DiagramPage) geCCMAbstPage(id); 
			
			// set text + icon
			setPageText(id, page.getPageName());
			setPageImage(id, ProjectResources.getIcon(diagram));

			// add command stacks
			getMultiPageCommandStackListener().addCommandStack(page.getCommandStack());
			
			// activate delegating command stack
			getDelegatingCommandStack().setCurrentCommandStack(page.getCommandStack());

			// set active page
			setActivePage(id);
			
		} catch (PartInitException e) {
			ErrorDialog.openError(
				getSite().getShell(),
				"Open Error",
				"An error occured during opening the editor.",
				e.getStatus());
		}

	}

	

	
	public void closeDiagramPage(Diagram diagram){
		
		DiagramPage page = (DiagramPage) diagramPages.get(diagram);
		int pageCount =getPageCount();
		for (int i =0;i<pageCount;i++ ){
			if (getEditor(i)==page){
				removePage(i);
				diagramPages.remove(diagram);
			}
		}	 
	}

	
	public boolean diagramIsOpen(Diagram diagram){
		//return diagramPageIDs.containsKey(diagram);
		return diagramPages.containsKey(diagram);
	}
	
	
	
	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#createPages()
	 */
	
	protected void createTypedPage(){
		try{
			// create ccm page
			typedPageID = addPage(new TypedPage(this), getEditorInput());
			setPageText(typedPageID, geCCMAbstPage(typedPageID).getPageName());
			// add command stacks
			getMultiPageCommandStackListener().addCommandStack(
				geCCMAbstPage(typedPageID).getCommandStack());
			// activate delegating command stack
			getDelegatingCommandStack().setCurrentCommandStack(
				geCCMAbstPage(typedPageID).getCommandStack());

			// set active page
			setActivePage(typedPageID);
			
		}catch (PartInitException e){
			ErrorDialog.openError(
				getSite().getShell(),
				"Open Error",
				"En error occured during opening the editor.",
				e.getStatus());
		}

	}
	
	
	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#createPages()
	 */
	
	protected void createModulePage(){
		try{
			// create ccm page
			modulePageID = addPage(new IDLTypesPage(this), getEditorInput());
			setPageText(modulePageID, geCCMAbstPage(modulePageID).getPageName());
			// add command stacks
			getMultiPageCommandStackListener().addCommandStack(
				geCCMAbstPage(modulePageID).getCommandStack());		
		}catch (PartInitException e){
			ErrorDialog.openError(
				getSite().getShell(),
				"Open Error",
				"En error occured during opening the editor.",
				e.getStatus());
		}

	}
	
	
	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#dispose()
	 */
	public void dispose(){
		
		outline=null;
		// dispose multi page command stack listener
		getMultiPageCommandStackListener().dispose();

		// remove delegating CommandStackListener
		getDelegatingCommandStack().removeCommandStackListener(
			getDelegatingCommandStackListener());

		// remove selection listener
		getSite()
			.getWorkbenchWindow()
			.getSelectionService()
			.removeSelectionListener(
			getSelectionListener());

		// disposy the ActionRegistry (will dispose all actions)
		getActionRegistry().dispose();

		// important: always call super implementation of dispose
		super.dispose();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.EditorPart#doSave(org.eclipse.core.runtime.IProgressMonitor)
	 */
	public void doSave(IProgressMonitor monitor)
	{
		try
		{
			IFile file = ((IFileEditorInput) getEditorInput()).getFile();
			if (file.exists()
				/*|| MessageDialogWithToggle.openConfirm(
					getSite().getShell(),
					"Create File",
					"The file '"
						+ file.getName()
						+ "' doesn't exist. Click OK to create it.")*/)
			{   
				save(file, monitor);
				getMultiPageCommandStackListener().markSaveLocations();
				 
			}
		}
		catch (CoreException e)
		{   e.printStackTrace();
			ErrorDialog.openError(
				getSite().getShell(),
				"Error During Save",
				"The current ccm model could not be saved.",
				e.getStatus());
		}
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.ISaveablePart#doSaveAs()
	 */
	public void doSaveAs()
	{
		SaveAsDialog dialog = new SaveAsDialog(getSite().getShell());
		dialog.setOriginalFile(((IFileEditorInput) getEditorInput()).getFile());
		dialog.open();
		IPath path = dialog.getResult();

		if (path == null)
			return;

		ProgressMonitorDialog progressMonitorDialog =
			new ProgressMonitorDialog(getSite().getShell());
		IProgressMonitor progressMonitor =
			progressMonitorDialog.getProgressMonitor();

		try
		{
			save(
				ResourcesPlugin.getWorkspace().getRoot().getFile(path),
				progressMonitor);
			getMultiPageCommandStackListener().markSaveLocations();
		}
		catch (CoreException e)
		{
			ErrorDialog.openError(
				getSite().getShell(),
				"Error During Save2",
				"The current ccm model could not be saved.",
				e.getStatus());
		}
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.WorkbenchPart#firePropertyChange(int)
	 */
	protected void firePropertyChange(int propertyId)
	{
		super.firePropertyChange(propertyId);
		updateActions(editorActionIDs);
	}

	/**
	 * Returns the action registry of this editor.
	 * @return the action registry
	 */
	protected ActionRegistry getActionRegistry()
	{
		if (actionRegistry == null)
			actionRegistry = new ActionRegistry();

		return actionRegistry;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.core.runtime.IAdaptable#getAdapter(java.lang.Class)
	 */
	public Object getAdapter(Class type)
	{
		if (type == IPropertySheetPage.class)
			return getPropertySheetPage();
		else if (type == CommandStack.class)
			return getDelegatingCommandStack();
		else if (type == ActionRegistry.class)
			return getActionRegistry();
		else if (type == ZoomManager.class)
			return getDelegatingZoomManager();
		else if (type == IContentOutlinePage.class) {
		    CCMTreeViewer tv=new CCMTreeViewer();
			outline=new TypeOutlinePage(tv,getCurrentPage().getDomain());
			((TypeOutlinePage)outline).setCCMEditor(this);
			((TypeOutlinePage)outline).setEditor(getCurrentPage());
			((TypeOutlinePage)outline).setViewer(getCurrentPage().getGraphicalViewer());
			((TypeOutlinePage)outline).setCCM(ccm);
			tv.setToPage((TypeOutlinePage) outline);
			return outline;
		}
		return super.getAdapter(type);
	}

	/**
	 * Returns the current active page. 
	 * @return the current active page or <code>null</code>
	 */
	private AbstractCCMPage getCurrentPage(){
		if (getActivePage() == -1)
			return null;
		return (AbstractCCMPage) getEditor(getActivePage());
	}

	/** the delegating ZoomManager */
	private DelegatingZoomManager delegatingZoomManager;

	/**
	 * Returns the <code>DelegatingZoomManager</code> for this editor.
	 * @return the <code>DelegatingZoomManager</code>
	 */
	protected DelegatingZoomManager getDelegatingZoomManager()
	{
		if (null == delegatingZoomManager)
		{
			delegatingZoomManager = new DelegatingZoomManager();
			if (null != getCurrentPage()
				&& null != getCurrentPage().getGraphicalViewer())
				delegatingZoomManager.setCurrentZoomManager(
					getZoomManager(getCurrentPage().getGraphicalViewer()));
		}

		return delegatingZoomManager;
	}

	/**
	 * Returns the <code>CommandStack</code> for this editor.
	 * @return the <code>CommandStack</code>
	 */
	protected DelegatingCommandStack getDelegatingCommandStack()
	{
		if (null == delegatingCommandStack)
		{ 
			delegatingCommandStack = new DelegatingCommandStack(getSite().getShell());
			if (null != getCurrentPage())
				delegatingCommandStack.setCurrentCommandStack(
					getCurrentPage().getCommandStack());
		}

		return delegatingCommandStack;
	}

	/**
	 * Returns the <code>CommandStackListener</code> for 
	 * the <code>DelegatingCommandStack</code>.
	 * @return the <code>CommandStackListener</code>
	 */
	protected CommandStackListener getDelegatingCommandStackListener()
	{
		return delegatingCommandStackListener;
	}

	/**
	 * Returns the global command stack listener.
	 * @return the <code>CommandStackListener</code>
	 */
	protected MultiPageCommandStackListener getMultiPageCommandStackListener()
	{
		if (null == multiPageCommandStackListener)
			multiPageCommandStackListener = new MultiPageCommandStackListener();
		return multiPageCommandStackListener;
	}

	/**
	 * Returns the undoable <code>PropertySheetPage</code> for
	 * this editor.
	 * 
	 * @return the undoable <code>PropertySheetPage</code>
	 */
	protected PropertySheetPage getPropertySheetPage()
	{
		if (null == undoablePropertySheetPage)
		{
			undoablePropertySheetPage = new PropertySheetPage();
			undoablePropertySheetPage.setRootEntry(
				GEFPlugin.createUndoablePropertySheetEntry(
					getDelegatingCommandStack()));
		}

		return undoablePropertySheetPage;
	}

	/**
	 * Returns the resource tracker instance
	 * @return
	 */
	private ResourceTracker getResourceTracker()
	{
		if (resourceTracker == null)
		{
			resourceTracker = new ResourceTracker();

		}

		return resourceTracker;
	}

	/**
	 * Returns the selection listener.
	 * 
	 * @return the <code>ISelectionListener</code>
	 */
	protected ISelectionListener getSelectionListener()
	{
		return selectionListener;
	}

	/**
	 * Returns the selection syncronizer object. 
	 * The synchronizer can be used to sync the selection of 2 or more
	 * EditPartViewers.
	 * @return the syncrhonizer
	 */
	protected SelectionSynchronizer getSelectionSynchronizer()
	{
		if (synchronizer == null)
			synchronizer = new SelectionSynchronizer();
		return synchronizer;
	}

	/**
	 * Returns the shared KeyHandler that should be used for 
	 * all viewers.
	 * 
	 * @return the shared KeyHandler
	 */
	protected KeyHandler getSharedKeyHandler()
	{
		if (sharedKeyHandler == null)
		{
			sharedKeyHandler = new KeyHandler();

			// configure common keys for all viewers
			sharedKeyHandler.put(
				KeyStroke.getPressed(SWT.DEL, 127, 0),
				getActionRegistry().getAction(ActionFactory.DELETE.getId()));
			sharedKeyHandler.put(
				KeyStroke.getPressed(SWT.F2, 0),
				getActionRegistry().getAction(GEFActionConstants.DIRECT_EDIT));
		}
		return sharedKeyHandler;
	}

	/**
	 * Returns the modelelement used by this editor.
	 * @return the modelelement
	 */
	public CCM getCCM()
	{
		return ccm;
	}

	
	/**
	 * Returns the page for editing the modelelement.
	 * @return the page for editing the modelelement
	 */
	private AbstractCCMPage geCCMAbstPage(int id){
		return (AbstractCCMPage) getEditor(id);
	}
	
	/**
	 * Returns the zoom manager of the specified viewer.
	 * @param viewer the viewer to get the zoom manager from
	 * @return the zoom manager
	 */
	private ZoomManager getZoomManager(GraphicalViewer viewer)
	{
		// get zoom manager from root edit part
		RootEditPart rootEditPart = viewer.getRootEditPart();
		ZoomManager zoomManager = null;
		if (rootEditPart instanceof ScalableFreeformRootEditPart)
		{
			zoomManager =
				((ScalableFreeformRootEditPart) rootEditPart).getZoomManager();
		}
		else if (rootEditPart instanceof ScalableRootEditPart)
		{
			zoomManager =
				((ScalableRootEditPart) rootEditPart).getZoomManager();
		}
		return zoomManager;
	}


	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#init(org.eclipse.ui.IEditorSite, org.eclipse.ui.IEditorInput)
	 */
	public void init(IEditorSite site, IEditorInput input)
		throws PartInitException
	{
		// read ccm from input
		try
		{
			// we expect IFileEditorInput here, 
			// ClassCassException is catched to force PartInitException
			IFile file = ((IFileEditorInput) input).getFile();
			ccm = create(file);

			// validate NavExpContainer
			if (null == getCCM())
				throw new PartInitException("The specified input is not a valid ccm.");
		}
		catch (CoreException e)
		{
			throw new PartInitException(e.getStatus());
		}
		catch (ClassCastException e)
		{
			throw new PartInitException(
				"The specified input is not a valid ccm.",
				e);
		}

		// modelelement is ok         
		super.init(site, input);
		
		if (outline != null) {
			 ((TypeOutlinePage)outline).setContents(getCCM().getModuleDef());
		}

		// add delegating CommandStackListener
		getDelegatingCommandStack().addCommandStackListener(
			getDelegatingCommandStackListener());

		// add selection change listener
		getSite()
			.getWorkbenchWindow()
			.getSelectionService()
			.addSelectionListener(
			getSelectionListener());

		// initialize actions
		createActions();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#isDirty()
	 */
	public boolean isDirty()
	{
		return isDirty;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.EditorPart#isSaveAsAllowed()
	 */
	public boolean isSaveAsAllowed()
	{
		return true;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#pageChange(int)
	 */
	protected void pageChange(int newPageIndex)
	
	{   
		super.pageChange(newPageIndex);
		 
		// refresh content depending on current page
		currentPageChanged();
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#setActivePage(int)
	 */
	protected void setActivePage(int pageIndex)
	{   
		super.setActivePage(pageIndex);
		 
		// refresh content depending on current page
		currentPageChanged();
	}

	/**
	 * Indicates that the current page has changed.
	 * <p>
	 * We update the DelegatingCommandStack, OutlineViewer
	 * and other things here.
	 */
	protected void currentPageChanged()
	{
		// update delegating command stack
		getDelegatingCommandStack().setCurrentCommandStack(
			getCurrentPage().getCommandStack());

		// update zoom actions
		getDelegatingZoomManager().setCurrentZoomManager(
			getZoomManager(getCurrentPage().getGraphicalViewer()));
	}

	/**
	 * Changes the dirty state.
	 * @param dirty
	 */
	private void setDirty(boolean dirty)
	{
		if (isDirty != dirty)
		{
			isDirty = dirty;
			firePropertyChange(IEditorPart.PROP_DIRTY);
		}
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.EditorPart#setInput(org.eclipse.ui.IEditorInput)
	 */
	protected void setInput(IEditorInput input)
	{
		if (getEditorInput() != null)
		{
			IFile file = ((FileEditorInput) getEditorInput()).getFile();
			file.getWorkspace().removeResourceChangeListener(
				getResourceTracker());
		}

		super.setInput(input);

		if (getEditorInput() != null)
		{
			IFile file = ((FileEditorInput) getEditorInput()).getFile();
			file.getWorkspace().addResourceChangeListener(getResourceTracker());
			this.setPartName(file.getName());
		}
	}

	/**
	 * Updates the specified actions.
	 * 
	 * @param actionIds the list of ids of actions to update
	 */
	private void updateActions(List actionIds)
	{
		for (Iterator ids = actionIds.iterator(); ids.hasNext();)
		{
			IAction action = getActionRegistry().getAction(ids.next());
			if (null != action && action instanceof UpdateAction)
				 ((UpdateAction) action).update();

		}
	}

	/** the model manager */
	private CCMModelManager modelManager;

	/**
	 * Returns the modelelement object from the specified file.
	 * 
	 * @param file
	 * @return the modelelement object from the specified file
	 */
	private CCM create(IFile file) throws CoreException{
		CCM cont = null;
		modelManager = new CCMModelManager();
		 
		if (file.exists()){
			try{
				modelManager.load(file.getFullPath());
			}catch (Exception e){
				e.printStackTrace();
				modelManager.createModelView(file);
			}

			cont = modelManager.getModel();
			if (null == cont){
				throw new CoreException(
					new Status(
						IStatus.ERROR,
							CCMEditorPlugin.PLUGIN_ID,
						0,
						"Error loading the ccm.",
						null));
			}
		}
		return cont;
	}

	/**
	 * Saves the modelelement under the specified path.
	 * 
	 * @param modelelement
	 * @param path workspace relative path
	 * @param progressMonitor
	 */
	private void save(IFile file, IProgressMonitor progressMonitor)
		throws CoreException
	{

		if (null == progressMonitor)
			progressMonitor = new NullProgressMonitor();

		progressMonitor.beginTask("Saving " + file, 2);

		if (null == modelManager)
		{
			IStatus status =
				new Status(
					IStatus.ERROR,
					CCMEditorPlugin.PLUGIN_ID,
					0,
					"No model manager found for saving the file.",
					null);
			 
			throw new CoreException(status);
		}

		// save modelelement to file
		try
		{
			modelManager.save(file.getFullPath());

			progressMonitor.worked(1);
			file.refreshLocal(
				IResource.DEPTH_ZERO,
				new SubProgressMonitor(progressMonitor, 1));
			progressMonitor.done();
		}
		catch (FileNotFoundException e)
		{
			IStatus status =
				new Status(
					IStatus.ERROR,
					CCMEditorPlugin.PLUGIN_ID,
					0,
					"Error writing file.",
					e);
			 
			throw new CoreException(status);
		}
		catch (IOException e)
		{
			IStatus status =
				new Status(
					IStatus.ERROR,
					CCMEditorPlugin.PLUGIN_ID,
					0,
					"Error writing file.",
					e);
			 
			throw new CoreException(status);
		}
	}

	
	/* (non-Javadoc)
	 * @see org.eclipse.ui.part.MultiPageEditorPart#getControl(int)
	 */
	protected Control getControl(int pageIndex) {
		return super.getControl(pageIndex);
	}

}

