/*
 * Created on 19.05.2005
*/
package ccm.commands.create.visual;

import CCMModel.Diagram;
import CCMModel.ModuleDef;
import CCMModel.View;
import ccm.CCMConstants;
import ccm.editors.CCMEditor;
import ccm.model.ModelFactory;

/**
 * @author Holger Kinscher
 */
public class CreateDiagramCommand extends CreateNodeForContainerCommand {
	
	private static final String	CreateCommand_Label = "CreateDiagramCommand";
	
	private View diagramView;

	private CCMEditor editor = null;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateDiagramCommand() {
		super();
		setLabel(CreateCommand_Label);
	}


	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {

//		super.execute();
		Diagram diagram = (Diagram) newObject;
		
		diagram.setIdentifier(identifier);
		diagram.setVersion(version);

		if(container.getAbsoluteName().trim().length()!=0) {
		    diagram.setAbsoluteName(container.getAbsoluteName() + ":" + container.getIdentifier());
		}
		else {
		    diagram.setAbsoluteName(container.getIdentifier());
		}
		diagram.setRepositoryId(CCMConstants.getRepositoryIdString(diagram.getAbsoluteName(),identifier,version));
	    container.getContents().add(diagram);
	       
	    diagramView = factory.createView();

	    ModelFactory mf=new ModelFactory();
	    mf.getRootModule(container).getCCM().getView().add(diagramView);
	    diagramView.setDiagram(diagram);
	    diagramView.setModuleDef((ModuleDef) container);
	    
	    diagram.setView(diagramView);
	    editor.openDiagramPage(diagram);
	    
		/*node.eNotify(new CCMNotificationImpl(node, Notification.SET,
			     CCMNotificationImpl.COMPONENT_DEF, null, null,0));*/
	}
	
	
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if(newObject!=null && container!=null)
			return true;
		return false;
	}

	
	
	
	/**
	 * @return Returns the editor.
	 */
	public CCMEditor getEditor() {
		return editor;
	}
	
	
	/**
	 * @param editor The editor to set.
	 */
	public void setEditor(CCMEditor editor) {
		this.editor = editor;
	}


}
