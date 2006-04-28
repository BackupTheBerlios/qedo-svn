/*
 * Created on 19.03.2005
*/
package ccm.action;

import java.util.List;

import org.eclipse.gef.EditPart;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.ui.actions.SelectionAction;
import org.eclipse.ui.IWorkbenchPart;

import CCMModel.CCMModelFactory;
import CCMModel.Container;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.OperationDef;
import ccm.commands.edit.EditOperationCommand;
import ccm.edit.OperationDefNodeEditPart;
import ccm.model.CCMModelManager;
import ccm.model.ModelFactory;
import ccm.treeedit.CCMModelTreeEditPart;

/**
 * @author Siegercn
 */
public class EditOperationAction extends SelectionAction {

//	 The command type as string value
    private final String commandType;

    // The name shown in the Context-Menu
    public static final String CLASSIFIER_PROPERTY = "Edit";
    
	protected CCMModelFactory factory=CCMModelManager.getFactory();

    /**
     * Creates a new OperationAction instance.
     * @param part 
     * @param commandType
     */
    public EditOperationAction(IWorkbenchPart part, String commandType){
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
        Command cmd = createOperatonCommand(getSelectedObjects());
        if (cmd == null)
            return false; 
        return cmd.canExecute();
    }

    /**
     * Creates the coresponding command. This only is done, if one
     * InterfaceDefNodeEditPart or ValueDefNodeEditPart is selected on the work-bench.
     * @param list - the list of selected edit-parts
     * @return - an PropertyCommand
     */
    protected Command createOperatonCommand(List selectedEditParts){
 
    	if (selectedEditParts.size() != 1) return null;
		
		if(selectedEditParts.get(0) instanceof EditPart) {
    	  EditPart part = (EditPart) selectedEditParts.get(0);
    	  if (part instanceof OperationDefNodeEditPart){
    		 Node opNode= (Node )part.getModel();
    		 OperationDef op =(OperationDef)opNode.getContained();
    		 Container container =(Container)op.eContainer();
    		 
    		 EditOperationCommand command = new EditOperationCommand();
    		 ModelFactory mf = new ModelFactory();
    		 ModuleDef moduldef= mf.getRootModule(op );
    		 command.setRootModule(moduldef);
    		 command.setIdlTypes(mf.getIDLTypes(moduldef));
    		 command.setNewObject(op);
    		 command.setContainer(container);
    		 //  ViewEditPart vep=(ViewEditPart)((OperationDefNodeEditPart) part).getParent().getParent();
             //   Shell shell=vep.getViewer().getControl().getShell(); 
    	     return command;
    	   }
    	  if(part instanceof CCMModelTreeEditPart && part.getModel() instanceof OperationDef){
    	  	 OperationDef op =(OperationDef)part.getModel();
    		 Container container =(Container)op.eContainer();
    		 
    		 EditOperationCommand command = new EditOperationCommand();
    		 ModelFactory mf = new ModelFactory();
    		 ModuleDef moduldef= mf.getRootModule(op);
    		 command.setRootModule(moduldef);
    		 command.setIdlTypes(mf.getIDLTypes(moduldef));
    		 command.setNewObject(op);
    		 command.setContainer(container);
    		 
    	     return command;
    	  	
    	  }
		}
		return null;
     
        
    }

   
    /**
     * Returns the command type.
     * @return the command type
     */
    public String getCommandType(){
        return commandType;
    }

    /**
     * Simply calls this.execute()
     */
    public void run(){
        execute(createOperatonCommand(getSelectedObjects()));
    }

    /**
     * Initializes this action.
     */
    protected void init(){
        super.init();
        setText(getCommandType());
        setToolTipText(getCommandType());
        setId(getCommandType());
        setEnabled(false);
    }
}
