package ccm.commands.delete.visual;

import org.eclipse.gef.commands.Command;
import org.eclipse.ui.IWorkbenchPart;

import CCMModel.Diagram;
import CCMModel.Node;
import CCMModel.View;
import ccm.editors.CCMEditor;

public class CloseDiagramCommand  extends Command {
	
	protected static final String DeleteCommand_Label = "close diagram Command";
	protected IWorkbenchPart editor;
	protected Diagram diagram=null;
 
	
	
	/**
	 * Constructor of this command - no parameters needed
	 */
	public CloseDiagramCommand() {
		super( DeleteCommand_Label );
	 
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 * @param part 
	 */
	public CloseDiagramCommand(IWorkbenchPart editor,Diagram diagram ) {
		super();
		this.editor = editor;
		this.diagram = diagram;
		 
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		//if(parent instanceof ViewImpl
		//	&& node.getConnTarget().isEmpty()
		//	&& node.getConSource().isEmpty())
			return true;
		//return false;
	}

	
	
	public void execute() {
		 System.out.println(">>>>execute>>>>DeleteDiagram");
		((CCMEditor)editor).closeDiagramPage(diagram);
		 
	}
	
	
	/**
	 * Execution of this command deletes a node
	 * completely.
	 */
	 

	
	
	/**
	 * Redos an undo.
	 */
	public void redo() {
		//parent.getNode().remove(node);
		//node.getContained().getNode().remove(node);
	}
	/**
	 * Undos an action done by this command
	 */
	public void undo() {
		//parent.getNode().add(node);
		//node.getContained().getNode().add(node);
	}
	
	/**
	 * Setter for the classifierNode
	 * @param cls - the new node
	 */
	public void setDelClassifier(Node cls) {
		//this.node = cls;
	}
	
	/**
	 * Setter for the container, where the node is placed in
	 * @param container
	 */
	public void setView(View container) {
		//this.parent = container;
		
	}
	
	/**
	 * @return Returns the delClassifier.
	 */
	public Node getDelClassifier() {
		return null;
	}
	public void setEditor(IWorkbenchPart editor) {
		this.editor = editor;
	
		
	}
	public void setDiagram(Diagram diagram) {
		this.diagram = diagram;
		
	}
}

