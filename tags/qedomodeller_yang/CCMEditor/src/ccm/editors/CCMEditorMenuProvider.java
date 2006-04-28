/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * Contributors:
 *     	Eduard Weiss
 * 
 */
package ccm.editors;

import org.eclipse.gef.ContextMenuProvider;
import org.eclipse.gef.EditPartViewer;
import org.eclipse.gef.ui.actions.ActionRegistry;
import org.eclipse.gef.ui.actions.GEFActionConstants;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.action.IMenuManager;
import org.eclipse.jface.action.MenuManager;
import org.eclipse.ui.actions.ActionFactory;

import CCMModel.AliasDef;
import CCMModel.Assembly;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.ConstantDef;
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

/**
 * This is the context menu provider for our editor.
 * 
 */
public class CCMEditorMenuProvider extends ContextMenuProvider
{
	// the action registry
	private final ActionRegistry actionRegistry;
	
	/**
	 * Creates a new NavExpEditorMenuProvider instance.
	 * @param viewer - the viewer of the EditParts
	 * @param actionRegistry - a class where all actions are registered
	 */
	public CCMEditorMenuProvider(EditPartViewer viewer, ActionRegistry actionRegistry) {
		super(viewer);
		this.actionRegistry = actionRegistry;
	}
	
	/**
	 * Here, a contxt-menu is builded. This is done by adding
	 * the actions to specific groups.
	 */
	public void buildContextMenu(IMenuManager menuManager) {
		
		// Add the standard action groups
		GEFActionConstants.addStandardActionGroups(menuManager);
		
		// adding some of the actions (to different groups)
		appendActionToUndoGroup(menuManager, ActionFactory.UNDO.getId());
		appendActionToUndoGroup(menuManager, ActionFactory.REDO.getId());
		
		appendActionToEditGroup(menuManager, ActionFactory.COPY.getId());
		appendActionToEditGroup(menuManager, ActionFactory.PASTE.getId());
		appendActionToEditGroup(menuManager, ActionFactory.DELETE.getId());
		appendActionToEditGroup(menuManager,GEFActionConstants.DIRECT_EDIT);
		// Here, the AddAttributeAction is added (to Add-Group) 
		//      Here, the AddAttributeAction is added (to Add-Group)
		
		appendActionToAddGroup(
				menuManager,
				DiagramDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				ModuleDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				ComponentDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				HomeDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				InterfaceDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				ValueDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				EventDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				ExceptionDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				ConstantDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				EnumDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				ValueBoxDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				AliasDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				StructDef.class.getName());
		
		appendActionToAddGroup(
				menuManager,
				UnionDef.class.getName());
		
		
		
		appendActionToAddGroup(
				menuManager,
				OperationDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				FactoryDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				ConstantDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				ExceptionDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				EnumDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				AliasDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				ValueBoxDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				ValueMemberDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				UnionDefAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				StructDefAction.CLASSIFIER_PROPERTY);
		
		appendActionToAddGroup(
				menuManager,
				AttributeDefAction.CLASSIFIER_PROPERTY);
		
		appendActionToAddGroup(
				menuManager,
				AddFacetAction.CLASSIFIER_PROPERTY);
		
		appendActionToAddGroup(
				menuManager,
				AddReceptacleAction.CLASSIFIER_PROPERTY);
		
		appendActionToAddGroup(
				menuManager,
				AddEventSourceAction.CLASSIFIER_PROPERTY);
		
		appendActionToAddGroup(
				menuManager,
				AddEmitsSourceAction.CLASSIFIER_PROPERTY);
		
		appendActionToAddGroup(
				menuManager,
				AddEventSinkAction.CLASSIFIER_PROPERTY);
 
//*************************************
		appendActionToAddGroup(
				menuManager,
				AddComponentFileAction.CLASSIFIER_PROPERTY);
		
		//appendActionToAddGroup(
		//		menuManager,
		//		RuleAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				AddIDLFileAction.CLASSIFIER_PROPERTY);
		

		appendActionToAddGroup(
				menuManager,
				ContainedFileAction.CLASSIFIER_PROPERTY);

		appendActionToAddGroup(
				menuManager,
				DepententFileAction.CLASSIFIER_PROPERTY);

		appendActionToAddGroup(
				menuManager,
				DeploymentRequirementAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				RegisterComponentInstanceAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				PropertyAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				ComponentInstanceAction.CLASSIFIER_PROPERTY);
		 
//		******************************************+
		appendActionToAddGroup(
				menuManager,
				SoftwarePackage.class.getName());
		appendActionToAddGroup(
				menuManager,
				AddImplementationAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				Assembly.class.getName());
		appendActionToAddGroup(
				menuManager,
				AddProcessCollocationAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				AddHomeInstanceAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				ExternalInstance.class.getName());
		
		
		
		appendActionToAddGroup(
				menuManager,
				Composition.class.getName());
		appendActionToAddGroup(
				menuManager,
				ComponentImplDef.class.getName());
		appendActionToAddGroup(
				menuManager,
				HomeImplDef.class.getName());
		appendActionToAddGroup(
				menuManager,
				CloseDiagramAction.CLASSIFIER_PROPERTY);
		appendActionToAddGroup(
				menuManager,
				EditOperationAction.CLASSIFIER_PROPERTY);
		
       //******************************************+
		
		appendAlignmentSubmenu(menuManager);
		
		appendActionToMenu(
				menuManager,
				ActionFactory.SAVE.getId(),
				GEFActionConstants.GROUP_SAVE);
	}
	
	/**
	 * Appends the alignment submenu.
	 * @param menuManager
	 */
	private void appendAlignmentSubmenu(IMenuManager menuManager) {
		// Alignment Actions
		MenuManager submenu = new MenuManager("Align");
		
		IAction action =
			getActionRegistry().getAction(GEFActionConstants.ALIGN_LEFT);
		if (null != action && action.isEnabled())
			submenu.add(action);
		
		action = getActionRegistry().getAction(GEFActionConstants.ALIGN_CENTER);
		if (null != action && action.isEnabled())
			submenu.add(action);
		
		action = getActionRegistry().getAction(GEFActionConstants.ALIGN_RIGHT);
		if (null != action && action.isEnabled())
			submenu.add(action);
		
		action = getActionRegistry().getAction(GEFActionConstants.ALIGN_TOP);
		if (null != action && action.isEnabled())
			submenu.add(action);
		
		action = getActionRegistry().getAction(GEFActionConstants.ALIGN_MIDDLE);
		if (null != action && action.isEnabled())
			submenu.add(action);
		
		action = getActionRegistry().getAction(GEFActionConstants.ALIGN_BOTTOM);
		if (null != action && action.isEnabled())
			submenu.add(action);
		
		if (!submenu.isEmpty())
			menuManager.appendToGroup(GEFActionConstants.GROUP_REST, submenu);
	}
	
	/**
	 * Returns the action registry.
	 * @return the action registry
	 */
	protected ActionRegistry getActionRegistry() {
		return actionRegistry;
	}
	
	/**
	 * Appends the specified action to the specified menu group
	 * @param actionId
	 * @param menuGroup
	 */
	private void appendActionToMenu(IMenuManager menu, String actionId, String menuGroup) {
		IAction action = getActionRegistry().getAction(actionId);
		if (null != action && action.isEnabled())
			menu.appendToGroup(menuGroup, action);
	}
	
	/**
	 * Appends the specified action to the specified menu group
	 * @param actionId
	 * @param menuGroup
	 */
	private void appendActionToUndoGroup(IMenuManager menu, String actionId)
	{
		IAction action = getActionRegistry().getAction(actionId);
		if (null != action && action.isEnabled())
			menu.appendToGroup(GEFActionConstants.GROUP_UNDO, action);
	}
	
	/**
	 * Appends the specified action to the specified menu group
	 * @param actionId
	 * @param menuGroup
	 */
	private void appendActionToEditGroup(IMenuManager menu, String actionId)
	{
		IAction action = getActionRegistry().getAction(actionId);
		if (null != action && action.isEnabled())
			menu.appendToGroup(GEFActionConstants.GROUP_EDIT, action);
	}
	
	/**
	 * Appends the specified action to the specified menu group
	 * @param actionId
	 * @param menuGroup
	 */
	private void appendActionToAddGroup(IMenuManager menu, String actionId)
	{
		IAction action = getActionRegistry().getAction(actionId);
		if (null != action && action.isEnabled()) {
			menu.appendToGroup(GEFActionConstants.GROUP_ADD, action);
		}
	}
	
}
