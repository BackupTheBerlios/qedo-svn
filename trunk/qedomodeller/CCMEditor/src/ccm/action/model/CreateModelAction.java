/*
 * Created on Jun 2, 2005
 *
 */
package ccm.action.model;

import java.util.List;

import org.eclipse.gef.commands.Command;
import org.eclipse.gef.ui.actions.SelectionAction;
import org.eclipse.ui.IWorkbenchPart;

import CCMModel.Container;
import ccm.commands.create.model.CreateModelCommand;
import ccm.request.model.CreateModelRequest;
import ccm.treeedit.CCMModelTreeEditPart;

/**
 * @author kinscher
 *
 */
public class CreateModelAction extends SelectionAction {

//	 The command type as string value
    private final Class commandType;

    // The name shown in the Context-Menu
    public static final String CLASSIFIER_PROPERTY = "add model";

    /**
     * Creates a new AttributeAction instance.
     * @param part 
     * @param commandType
     */
    public CreateModelAction(IWorkbenchPart part, Class commandType){
        super(part);
        this.commandType = commandType;
        setId(getCommandType().getName());
        setToolTipText(commandType.getName());
        String name = getCommandType().getName();
        name = name.substring(name.lastIndexOf(".")+1);
        setText("create "+name);
    }

   
    
    /**
     * Calculates if this action is enabled, i.e. if the user should
     * be able to execute this action. This is the case, if
     * a command for this action can be instanciated (createAddAttributeCommand)
     * and the command can be executed (cmd.canExecute()). 
     */
    protected boolean calculateEnabled()
    {
        Command cmd = createModelCommand(getSelectedObjects());
        if (cmd == null)
            return false; 
        return cmd.canExecute();
    }

    /**
     * Creates the coresponding command. This only is done, if one
     * ClassifierRoleEditPart is selected on the work-bench.
     * @param list - the list of selected edit-parts
     * @return - an PropertyCommand
     */
    protected Command createModelCommand(List selectedEditParts)
    {
    	// Feature is only available for 
        if (selectedEditParts.size() != 1)
        	return null;
        
        // get the EditPart
        CCMModelTreeEditPart ep = null;
        
        // check the EditPart for
        // only allowed for ClassifierRoleEditPart 
        if (!(selectedEditParts.get(0) instanceof CCMModelTreeEditPart))
        	return null;
        
        ep = (CCMModelTreeEditPart)selectedEditParts.get(0);
        
        if(!(ep.getModel() instanceof Container))
        	return null;
        
        // Create the Request	
        CreateModelRequest modelReq = new CreateModelRequest(getCommandType());
		// Create and return the command
		CreateModelCommand cmd = null;
		if (ep.understandsRequest(modelReq)) {
			Command c = ep.getCommand(modelReq);
			if (c instanceof CreateModelCommand) {
				cmd = (CreateModelCommand)c;
				cmd.setContainer((Container) ep.getModel());
			}
		}

        return cmd;
    }

    /**
     * Returns the command type.
     * @return the command type
     */
    public Class getCommandType()
    {
        return commandType;
    }

    /**
     * Simply calls this.execute()
     */
    public void run()
    {
        execute(createModelCommand(getSelectedObjects()));
    }

    /**
     * Initializes this action.
     */
    protected void init()
    {
        super.init();
       setEnabled(false);
    }

}
