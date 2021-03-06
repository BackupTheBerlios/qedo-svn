/*
 * Created on 19.10.2005
 */
package ccm.action;

import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.ui.actions.SelectionAction;
import org.eclipse.ui.IWorkbenchPart;

import CCMModel.CCMModelFactory;
import CCMModel.Container;
import CCMModel.HomeInstantiation;
import CCMModel.Node;
import ccm.commands.create.visual.adds.AddComponentInstanceCommand;
import ccm.edit.ContainerNodeEditPart;
import ccm.edit.HomeInstanceNodeEditPart;
import ccm.model.CCMModelManager;
import ccm.model.ModelFactory;
import ccm.treeedit.CCMModelTreeEditPart;

/**
 * @author siegercn
 */
public class ComponentInstanceAction extends SelectionAction {
	
//	The command type as string value
	private final String commandType;
	
	// The name shown in the Context-Menu
	public static final String CLASSIFIER_PROPERTY = "crate a component instance";
	
	protected CCMModelFactory factory=CCMModelManager.getFactory();
	
	/**
	 * Creates a new OperationAction instance.
	 * @param part 
	 * @param commandType
	 */
	public ComponentInstanceAction(IWorkbenchPart part, String commandType){
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
		Command cmd = createCommand(getSelectedObjects());
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
	protected Command createCommand(List selectedEditParts){
		
		if (selectedEditParts.size() != 1) return null;
		
		if(selectedEditParts.get(0) instanceof EditPart) {
			EditPart part = (EditPart) selectedEditParts.get(0);
			
			if ((part instanceof HomeInstanceNodeEditPart &&((HomeInstantiation)(((ContainerNodeEditPart) part).getModelNode()).getContained()).getType()!=null  
					&&((HomeInstantiation)(((ContainerNodeEditPart) part).getModelNode()).getContained()).getType().getComponentImpl()!=null) ||
					(part instanceof CCMModelTreeEditPart&& (part.getModel()instanceof HomeInstantiation)) && 
					((HomeInstantiation)part.getModel()).getType()!=null && 
					((HomeInstantiation)part.getModel()).getType().getComponentImpl()!=null) {
				
				//AddStructDefRequest req = new AddStructDefRequest(getCommandType());
				//if (!part.understandsRequest(req)) return null;
				//else {
					ModelFactory mf = new ModelFactory();
					AddComponentInstanceCommand command = new AddComponentInstanceCommand();
						//(AddStructDefCommand) part.getCommand(req);
					
					if (part instanceof ContainerNodeEditPart) {
						Node node = ((ContainerNodeEditPart) part).getModelNode();
						command.setView(node.getDefineIn().getDefineIn().getView());
						command.setContainer((Container) node.getContained());        			
						//command.setParentNode(node);
						command.setConstraint(new Rectangle(0,0,-1,-1));
						command.setRootModule(mf.getRootModule(node.getContained()));
						command.setType(((HomeInstantiation)node.getContained()).getType().getComponentImpl());
					} else {
						command.setContainer((Container) part.getModel());        			
						command.setRootModule(mf.getRootModule((Container) part.getModel()));
						command.setType(((HomeInstantiation) part.getModel()).getType().getComponentImpl());
					}
					
				//	command.setIdlTypes(mf.getIDLTypes(command.getRootModule()));
					command.setNewObject(factory.createComponentInstantiation());
					
					return command;
				}
				
			//}
			else { 
				return null;
			}
		}
		else return null;
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
		execute(createCommand(getSelectedObjects()));
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
  
