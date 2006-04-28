/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 * 
 */
package ccm.commands.create.visual.adds;


import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.ExceptionDef;
import CCMModel.Field;
import CCMModel.Node;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.FieldTemplate;




public class AddExceptionDefCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "CreateExceptionCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private ExceptionDef exceptionD;
	
	private String typeCode="";
	private List members=new LinkedList();

	
	/**
	 * Constructor of this command, 
	 */
	public AddExceptionDefCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container!=null &&	newObject!=null)return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    exceptionD=(ExceptionDef) newObject;
    	exceptionD.setTypeCode(typeCode);
    	addMembers();
    	
    	Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	exceptionD.getNode().add(opNode);
	    	opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.EXCEPTION_DEF, null, null,0));
			addMemberNodes(opNode);
	    }
	}
	
	private void addMembers(){
	    exceptionD.getMembers().clear();
	    Iterator it=members.iterator();
	    while(it.hasNext()){
	        FieldTemplate p=(FieldTemplate) it.next();
	        Field fld=factory.createField();
	        fld.setIdentifier(p.getIdentifier());
	        setIDLTyped(fld,p.getIdlType());
			exceptionD.getMembers().add(fld);
	    }
	}
			
	private void addMemberNodes(Node opNode){
		Iterator it = exceptionD.getMembers().iterator();
		while(it.hasNext()) {
			Field fld = (Field) it.next();
	        if (opNode==null) continue;
	        Node node=factory.createNode();
	        fld.getNodeFromTyped().add(node);
			node.setX(0);
			node.setY(0);
			node.setWidth(-1);
			node.setHeight(-1);
			opNode.getContents().add(node);
			node.eNotify(new CCMNotificationImpl(node, Notification.ADD,
				       							   CCMNotificationImpl.FIELD, null, null,0));	
	    }
	    if (parentNode!=null) {
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			                                   CCMNotificationImpl.EXCEP_FIELD, null, null,0));
	    }
	}

	private void deleteMembers(){
	    Iterator it=exceptionD.getMembers().iterator();
	    int i=0;
	    while(it.hasNext()){
	        Field fld=(Field) it.next();;
	        FieldTemplate p=(FieldTemplate)members.get(i);
	        unSetIDLTyped(fld,p.getIdlType());
	        if (parentNode==null) continue;
			opNode.getContents().removeAll(fld.getNodeFromTyped());
	        fld.getNodeFromTyped().clear();
		    i=i+1;
	    }
	    exceptionD.getMembers().clear();
	    if (parentNode!=null) {
	    opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			       CCMNotificationImpl.EXCEP_FIELD, null, null,0));
	    }
	}

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}
	

    /**
     * @return Returns the parameters.
     */
    public List getMembers() {
        return members;
    }
    /**
     * @param parameters The parameters to set.
     */
    public void setMembers(List parameters) {
        this.members.clear();
        this.members.addAll(parameters);
    }

    /**
     * @param typeCode The typeCode to set.
     */
    public void setTypeCode(String typeCode) {
        this.typeCode = typeCode;
    }
    /**
     * @param parentNode The parentNode to set.
     */
    public void setParentNode(Node parentNode) {
        this.parentNode = parentNode;
    }
}
