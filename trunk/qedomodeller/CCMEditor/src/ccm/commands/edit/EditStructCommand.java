package ccm.commands.edit;
/**
 * @author Siegercn
 * 
 */
 


import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.util.EList;

import CCMModel.IDLType;
import CCMModel.Node;
import CCMModel.ParameterDef;
import CCMModel.StructDef;
import CCMModel.Typed;
import ccm.CCMConstants;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;
import ccm.model.template.ParameterTemplate;



public class EditStructCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "editStructCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private StructDef struct;
	
	private boolean isOneway = true;
	private String context = "";
	private List parameters = new LinkedList();
	private List editParameters = new LinkedList();
	private IDLTemplate idlTemplate = new IDLTemplate(IDLKind.IDL_LITERAL);
	//private OperationDef op;

	
	/**
	 * Constructor of this command, 
	 */
	public EditStructCommand() {
		
		super();
		//this.s=op;
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public StructDef getOperationDef(){
		return (StructDef)this.newObject;
		}
	public List getIDLTypes(){
		return this.idlTypes;
		}
	
	public boolean canExecute() {
		if (container!=null && newObject!=null) return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	   // super.execute();
	    //*****************************
	    newObject.setIdentifier(identifier);
		newObject.setVersion(version);
		/* modified by tri */
		newObject.setAbsoluteName(container.getAbsoluteName() +":" + identifier);
		
		/*
		if(container.getAbsoluteName().trim().length()!=0)
		    newObject.setAbsoluteName(container.getAbsoluteName() + ":" + container.getIdentifier());
		else
		    newObject.setAbsoluteName(container.getIdentifier());
		    
		*/
		
		// TODO
		newObject.setRepositoryId(CCMConstants.getRepositoryIdString(newObject.getAbsoluteName(),identifier,version));
	   // container.getContents().add(newObject);
	    //********************
	    struct = (StructDef) newObject;
//		struct.setIsOneway(isOneway);
//		struct.setContext(context);		
//		setIDLTyped(struct,idlTemplate);
		
		//addParameters();

		Iterator it = container.getNode().iterator();
	//    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	   // 	opNode=factory.createNode();
	//    	struct.getNode().add(opNode);
	    	/*opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);*/
	  //  	parentNode.getContents().add(opNode);
	  //  	parentNode.getContents();
	    	List nodes = struct.getNode();
	    	for (Iterator itn = nodes.iterator();itn.hasNext();){
	    		Node opNode =(Node)itn.next();
	    		opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
					       CCMNotificationImpl.OPERATION_DEF, null, null,0));
	    		//addparamNodes(opNode);
	    	}
	    	addParameters();
			
	    }
		
	//}
	
	
	
	private void addParameters(){
		 
	//	EList paraList = struct.getParameters();
		EList paraList = struct.getMembers();
		for (Iterator it =paraList.iterator();it.hasNext();){
			Typed field= (Typed )it.next();
			IDLType idlt = field.getIDLType();
			if(idlt != null)
				idlt.getTyped().remove(field);
		}
		paraList.clear();
	    
	    Iterator it=parameters.iterator();
	    while(it.hasNext()){
	        ParameterTemplate p=(ParameterTemplate) it.next();
	        ParameterDef paramDef=factory.createParameterDef();
	   //     ParameterDef paramDef=(ParameterDef)(struct.getParameters().get(0));
	        paramDef.setDirection(p.getMode());
	        paramDef.setIdentifier(p.getIdentifier());
	        setIDLTyped(paramDef,p.getIdlType());
//			struct.getParameters().add(paramDef);
	    }
	}
	
	 

	private void deleteParameters(){
	    Iterator it=struct.getMembers().iterator();
	    int i=0;
	    while(it.hasNext()){
	        ParameterDef paramDef=(ParameterDef) it.next();
	        ParameterTemplate p=(ParameterTemplate)parameters.get(i);
	        unSetIDLTyped(paramDef,p.getIdlType());
	        if (parentNode==null) continue;
	        opNode.getContents().removeAll(paramDef.getNodeFromTyped());
	        paramDef.getNodeFromTyped().clear();
	        i=i+1;
	    }
        if (parentNode!=null) {
 //       	struct.getParameters().clear();
        	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			       CCMNotificationImpl.OP_PARAMETERS, null, null,0));
        }
	}
	

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}
	
	public void setParentNode(Node parentNode) {
		this.parentNode = parentNode;
	}

	public String getContext() {
		return context;
	}
	

	public void setContext(String context) {
		this.context = context;
	}
	
	

	public boolean isOneway() {
		return isOneway;
	}

	public void setOneway(boolean isOneway) {
		this.isOneway = isOneway;
	}

    /**
     * @return Returns the parameters.
     */
    public List getParameters() {
        return parameters;
    }
    /**
     * @param parameters The parameters to set.
     */
    public void setParameters(List parameters) {
        this.parameters.clear();
        this.parameters.addAll(parameters);
    }
    public void setEditParameters(List parameters) {
        this.editParameters.clear();
        this.editParameters.addAll(parameters);
    }

    /**
     * @param idlTemplate The idlTemplate to set.
     */
    public void setIdlTemplate(IDLTemplate idlTemplate) {
        this.idlTemplate = idlTemplate;
    }
}

