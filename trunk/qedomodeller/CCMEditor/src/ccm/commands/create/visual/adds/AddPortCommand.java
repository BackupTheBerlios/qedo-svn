/*
 * Created on 25.03.2005
*/
package ccm.commands.create.visual.adds;

import java.util.Iterator;

import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;

import CCMModel.CCMModelFactory;
import CCMModel.ComponentDef;
import CCMModel.ComponentInstantiation;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.EmitsDef;
import CCMModel.Node;
import CCMModel.PortNode;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.SiSouDef;
import CCMModel.SinkDef;
import CCMModel.SourceDef;
import CCMModel.UsesDef;
import CCMModel.View;
import ccm.commands.constraints.PortConstraint;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMModelManager;

/**
 * @author Holger Kinscher
 */
public class AddPortCommand extends CreateNodeForContainedCommand {
	
//	 Names for Label and Description of this Command
	protected String Command_Label = "";
	protected String Command_Description = "";
	

	protected CCMModelFactory mfc = CCMModelManager.getFactory();
	protected PortNode portNode = null;
	protected Contained portDef=null;
	protected View view=null;
	protected Node componentNode;
    protected boolean forInstance=false;
 
	
	/**
	 * Constructor, simply calls the superclass
	 * with the ConnectionLabel as parameter.
	 */
	public AddPortCommand(){
		super();
		setLabel(Command_Label);
	}
	public AddPortCommand(boolean forInstance){
		super();
		setLabel(Command_Label);
		this.forInstance=forInstance;
	}

	/**
	 * This method returns true, if a source (ClassifierRole, see class-members)
	 * is specified. 
	 */
	public boolean canExecute() {
		if (container==null || !(container instanceof ComponentDef)
				) return false;
		return true;
	}
	
	/**
	 * This method handles the execution of adding an Attribute or a Method
	 * to a class (ClassifierRole). Therefor it uses a NavExpModelFactory
	 * to create an Attribute or Method and sets the the corresponding
	 * references to the ClassifierRole.
	 * Finally the ClassifierRoleFigure is updated.
	 */
	public void execute() {
		this.setNewObject(portDef);
        if(!forInstance){
        	
        	super.execute();
        	ComponentDef component=(ComponentDef)container;
        	if(portDef instanceof ProvidesDef)
        		component.getFacet().add(portDef);
        	if(portDef instanceof UsesDef)
        		component.getReceptacle().add(portDef);
        	if(portDef instanceof PublishesDef)
        		component.getPublishesDef().add(portDef);
        	if(portDef instanceof ConsumesDef)
        		component.getConsumess().add(portDef);
        	if(portDef instanceof EmitsDef)
        		component.getEmitss().add(portDef);
        	if(portDef instanceof SinkDef)
				component.getSinkss().add(portDef);
        	if(portDef instanceof SourceDef)
        		component.getSourcess().add(portDef);
        	if(portDef instanceof SiSouDef)
        		component.getSiSouss().add(portDef);
        	
        	Iterator it = container.getNode().iterator();
    		while(it.hasNext()) {
    			componentNode = (Node) it.next();
    			 
    			if (componentNode!=null) {
    				
    				portNode = mfc.createPortNode();
    				portNode.setContained(portDef);
    				portNode.setHostNode(componentNode);
    				
    				PortConstraint constraint=new PortConstraint(new Rectangle(componentNode.getX(),componentNode.getY(),
    						componentNode.getWidth(),componentNode.getHeight()));
    				constraint.setPortLoc(new Point(componentNode.getX(),componentNode.getY()),newObject,0);
    				Point loc=constraint.getXyPoint();
    				portNode.setX(loc.x);
    				portNode.setY(loc.y);
    				portNode.setLocation(constraint.getPortLocation());
    				 
    				view = componentNode.getView();
    				view.getNode().add(portNode);
    				 
    				 
    			}
    		}
        }
        else{
        	ComponentInstantiation componentInstance=(ComponentInstantiation)container;
        	//ComponentDef component=(ComponentDef)container;
        	if(portDef instanceof ProvidesDef)
        		componentInstance.getFacet().add(portDef);
        	if(portDef instanceof UsesDef)
        		componentInstance.getReceptacle().add(portDef);
        	if(portDef instanceof PublishesDef)
        		componentInstance.getPublishesDef().add(portDef);
        	if(portDef instanceof ConsumesDef)
        		componentInstance.getConsumess().add(portDef);
        	if(portDef instanceof EmitsDef)
        		componentInstance.getEmitss().add(portDef);
        	if(portDef instanceof SinkDef)
        		componentInstance.getSinkss().add(portDef);
        	if(portDef instanceof SourceDef)
        		componentInstance.getSourcess().add(portDef);
        	if(portDef instanceof SiSouDef)
        		componentInstance.getSiSouss().add(portDef);
        	//container.getContents().add(portDef);
       
        	portNode = mfc.createPortNode();
			portNode.setContained(portDef);
			portNode.setHostNode(componentNode);
			
			PortConstraint constraint=new PortConstraint(new Rectangle(componentNode.getX(),componentNode.getY(),
					componentNode.getWidth(),componentNode.getHeight()));
			constraint.setPortLoc(new Point(componentNode.getX(),componentNode.getY()),newObject,0);
			Point loc=constraint.getXyPoint();
			portNode.setX(loc.x);
			portNode.setY(loc.y);
			portNode.setLocation(constraint.getPortLocation());
			 
			componentNode.getDefineIn().getContents().add(portNode);
		
        
        }
		//portDef.setDefinedIn(container);
		 
	
	}
	
	

	public void redo() {
		container.getContents().add(portDef);
		portDef.setDefinedIn(container);
		
		if (view!=null) {
			view.getNode().add(portNode);
		}
		super.redo();
	}

	
	public void undo() {
		container.getContents().remove(portDef);
		portDef.setDefinedIn(null);
		if (portNode!=null && view!=null) {
			portNode.setContained(null);
			view.getNode().remove(portNode);
		}
		super.undo();
	}
	/**
	 * @return Returns the container.
	 */
	public Container getContainer() {
		return container;
	}
	public void setContained(Contained con){
		portDef=con;
	}
	/**
	 * @param container The container to set.
	 */
	public void setContainer(Container container) {
		this.container = container;
	}
	/**
	 * @return Returns the node.
	 */
	public View getView() {
		return view;
	}
	/**
	 * @param node The node to set.
	 */
	public void setView(View view) {
		this.view = view;
	}
	public PortNode getPortNode() {
		return this.portNode;
	}
    /**
     * @param componentNode The componentNode to set.
     */
    public void setComponentNode(Node componentNode) {
        this.componentNode = componentNode;
    }
	/**
	 * @param processNode
	 */
	 
}
