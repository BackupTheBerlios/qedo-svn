/*
 * Created on 05.02.2005
*/
package ccm.action;

import java.util.List;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.ui.actions.SelectionAction;
import org.eclipse.ui.IWorkbenchPart;

import CCMModel.Container;
import CCMModel.Node;
import ccm.commands.create.visual.adds.AddEventSourceCommand;
import ccm.edit.ComponentDefNodeEditPart;
import ccm.edit.ContainerNodeEditPart;
import ccm.model.ModelFactory;
import ccm.request.AddEventSourceRequest;
import ccm.treeedit.CCMModelTreeEditPart;

/**
 * @author Holger Kinscher
 */
public class AddEventSourceAction extends SelectionAction {

//	 The command type as string value
    private final String commandType;

    // The name shown in the Context-Menu
    public static final String CLASSIFIER_PROPERTY = "add event source";

    /**
     * Creates a new AttributeAction instance.
     * @param part 
     * @param commandType
     */
    public AddEventSourceAction(IWorkbenchPart part, String commandType){
        super(part);
        this.commandType = commandType;
        setId(commandType);
        setText(commandType);
    }

    /**
     * Calculates if this action is enabled, i.e. if the user should
     * be able to execute this action. This is the case, if
     * a command for this action can be instanciated (createAddAttributeCommand)
     * and the command can be executed (cmd.canExecute()). 
     */
    protected boolean calculateEnabled()
    {
        Command cmd = createEventSourceCommand(getSelectedObjects());
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
    protected Command createEventSourceCommand(List selectedEditParts)
    {
    	if (selectedEditParts.size() != 1) return null;
		
		if(selectedEditParts.get(0) instanceof EditPart) {
    	EditPart part = (EditPart) selectedEditParts.get(0);
     
        if (!(part instanceof ComponentDefNodeEditPart) &&
        	!(part instanceof CCMModelTreeEditPart)) return null;

        	
        AddEventSourceRequest req = new AddEventSourceRequest(getCommandType());
    	if (!part.understandsRequest(req)) return null;

    	ModelFactory mf = new ModelFactory();
    	AddEventSourceCommand command = (AddEventSourceCommand) part.getCommand(req);

        if (part instanceof ContainerNodeEditPart) {
        	Node node = ((ContainerNodeEditPart) part).getModelNode();
        	command.setView(node.getView());
        	command.setComponentNode(node);
        	command.setContainer((Container) node.getContained());        			
        	command.setRootModule(mf.getRootModule(node.getContained()));
        } else {
         	command.setContainer((Container) part.getModel());        			
        	command.setRootModule(mf.getRootModule((Container) part.getModel()));
        }
        return command;  	
    }
		else return null;
    }

    
    /**
     * Returns the command type.
     * @return the command type
     */
    public String getCommandType()
    {
        return commandType;
    }

    /**
     * Simply calls this.execute()
     */
    public void run()
    {
        execute(createEventSourceCommand(getSelectedObjects()));
    }

    /**
     * Initializes this action.
     */
    protected void init()
    {
        super.init();
        setText(getCommandType());
        setToolTipText(getCommandType());
        setId(getCommandType());
        setEnabled(false);
    }
}
