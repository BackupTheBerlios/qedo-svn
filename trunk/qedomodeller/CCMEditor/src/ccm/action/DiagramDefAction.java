/*
 * Created on 19.05.2005
*/
package ccm.action;

import java.util.List;

import org.eclipse.gef.commands.Command;
import org.eclipse.gef.ui.actions.SelectionAction;
import org.eclipse.ui.IWorkbenchPart;

import CCMModel.CCMModelFactory;
import CCMModel.Container;
import CCMModel.ModuleDef;
import ccm.commands.create.visual.CreateDiagramCommand;
import ccm.editors.CCMEditor;
import ccm.model.CCMModelManager;
import ccm.request.AddDiagramRequest;
import ccm.treeedit.CCMModelTreeEditPart;

/**
 * @author Holger Kinscher
 */
public class DiagramDefAction extends SelectionAction {
	
//	 The command type as string value
    private final String commandType;

    // The name shown in the Context-Menu
    public static final String CLASSIFIER_PROPERTY = "create a diagram";
    
	protected CCMModelFactory factory=CCMModelManager.getFactory();

	private IWorkbenchPart part;
	
	/**
	 * @param part
	 */
	public DiagramDefAction(IWorkbenchPart part,String commandType) {
		super(part);
		this.part=part;
		this.commandType=commandType;
		setId(commandType);
        setText(commandType);
	}
	/* (non-Javadoc)
	 * @see org.eclipse.gef.ui.actions.WorkbenchPartAction#calculateEnabled()
	 */
	protected boolean calculateEnabled() {
		Command cmd = createDiagramCommand(getSelectedObjects());
        if (cmd == null)
            return false; 
        return cmd.canExecute();
	}
	/**
	 * @param selectedObjects
	 * @return
	 */
	private Command createDiagramCommand(List selectedObjects) {
//		 Feature is only available for 
        if (selectedObjects.size() != 1)
        	return null;
        
        // get the EditPart
        CCMModelTreeEditPart ep = null;
        
        // check the EditPart for
        // only allowed for ClassifierRoleEditPart 
        if (!(selectedObjects.get(0) instanceof CCMModelTreeEditPart)
        		|| !(((CCMModelTreeEditPart)selectedObjects.get(0)).getModel() instanceof ModuleDef))
        	return null;
        
        ep = (CCMModelTreeEditPart)selectedObjects.get(0);
        
        // Create the Request	
        AddDiagramRequest attributeReq = new AddDiagramRequest(getCommandType());
		// Create and return the command
        CreateDiagramCommand cmd = null;
		if (ep.understandsRequest(attributeReq)) {
			Command c = ep.getCommand(attributeReq);
			if (c instanceof CreateDiagramCommand) {
				cmd = (CreateDiagramCommand)c;
				cmd.setNewObject(factory.createDiagram());
				cmd.setContainer((Container) ep.getModel());
				cmd.setView(factory.createView());
				cmd.setEditor((CCMEditor) part);
			}
		}
		
		return cmd;
	}
	/**
	 * @return Returns the commandType.
	 */
	public String getCommandType() {
		return commandType;
	}
	/* (non-Javadoc)
	 * @see org.eclipse.jface.action.IAction#run()
	 */
	public void run() {
		execute(createDiagramCommand(getSelectedObjects()));
	}
}
