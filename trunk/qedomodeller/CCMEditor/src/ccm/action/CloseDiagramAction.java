package ccm.action;

import java.util.List;

import org.eclipse.core.internal.dtree.DeletedNode;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.ui.actions.SelectionAction;
import org.eclipse.swt.custom.CTabFolder;
import org.eclipse.swt.widgets.Item;
import org.eclipse.ui.IWorkbenchPart;

import CCMModel.Container;
import CCMModel.Diagram;
import CCMModel.Node;
import CCMModel.View;
//import ccm.commands.adds.AddEventSourceCommand;
//import ccm.commands.adds.AddFacetCommand;
import ccm.commands.delete.visual.CloseDiagramCommand;
import ccm.edit.ComponentDefNodeEditPart;
import ccm.edit.ContainerNodeEditPart;
import ccm.edit.StartPageEditPart;
//import ccm.edit.StartPageEditPart;
import ccm.edit.ViewEditPart;
import ccm.editors.AbstractCCMPage;
import ccm.editors.CCMEditor;
import ccm.editors.DiagramPage;
import ccm.editors.IDLTypesPage;
import ccm.model.ModelFactory;
import ccm.request.AddEventSourceRequest;
//import ccm.request.CloseDiagramRequest;
import ccm.treeedit.CCMModelTreeEditPart;

public class CloseDiagramAction extends SelectionAction {

//	 The command type as string value
   private final String commandType;

   // The name shown in the Context-Menu
   public static final String CLASSIFIER_PROPERTY = "close diagram";

   /**
    * Creates a new AttributeAction instance.
    * @param part 
    * @param commandType
    */
   public CloseDiagramAction(IWorkbenchPart part, String commandType){
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
       Command cmd = createCloseDiagramCommand(getSelectedObjects());
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
   protected Command createCloseDiagramCommand(List selectedEditParts)
   {
   	if (selectedEditParts.size() != 1) 
   		return null;
   // if(selectedEditParts.get(0) instanceof StartPageEditPart ) {
   // 	StartPageEditPart spart = (StartPageEditPart) selectedEditParts.get(0);
	//	 System.out.println(">>>>>>>>>++++++ vpart.getModel() : "+ spart.getModel());
	//	 CloseDiagramCommand  command = new CloseDiagramCommand () ;
	//	 command.setEditor(this.getWorkbenchPart());
	//	 return command;
    //	}
    if(selectedEditParts.get(0) instanceof ViewEditPart ) 
    {
		 ViewEditPart vpart = (ViewEditPart) selectedEditParts.get(0);  
		 View view = (View)vpart.getModel(); 
		 //CloseDiagramRequest request = new CloseDiagramRequest(getCommandType());
		 CloseDiagramCommand command = new CloseDiagramCommand() ;
		 command.setEditor(this.getWorkbenchPart());
		 command.setDiagram(view.getDiagram());
		 return command;
   }
    	
   if(selectedEditParts.get(0) instanceof CCMModelTreeEditPart) 
   {   
		CCMModelTreeEditPart part= (CCMModelTreeEditPart)selectedEditParts.get(0);
			
		if(part.getModel() instanceof Diagram){
		    //CloseDiagramRequest request = new CloseDiagramRequest(getCommandType()); 
			Diagram diagram =	(Diagram)part.getModel();
			CCMEditor ccmeditor =(CCMEditor)this.getWorkbenchPart();
			if (!ccmeditor.diagramIsOpen(diagram))
			   return null;
			CloseDiagramCommand command = new CloseDiagramCommand() ;
			command.setEditor(ccmeditor);
			command.setDiagram(diagram);
			return command;
	  
		 }
	     return null;
	}
    return null;	
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
       execute(createCloseDiagramCommand(getSelectedObjects()));
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


