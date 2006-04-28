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

import org.eclipse.emf.common.notify.Notification;

import CCMModel.Field;
import CCMModel.Node;
import CCMModel.StructDef;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.FieldTemplate;



public class AddStructDefCommand 
extends AddTypedefDefCommand
{
    
	private static final String	CreateCommand_LabelSimple = "CreateParameterCommand";

	
	private StructDef structD;

	private List members=new LinkedList();
	
	/**
	 * Constructor of this command, 
	 */
	public AddStructDefCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    structD = (StructDef) newObject;
	    addMembers();
	    
	    Node parentNode;
	    Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	structD.getNode().add(opNode);
	    	opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.STRUCT_DEF, null, null,0));
			addMemberNodes(opNode);
	    }
	}
	
	
	
	private void addMembers(){
	    structD.getMembers().clear();
	    Iterator it=members.iterator();
	    while(it.hasNext()){
	        FieldTemplate p=(FieldTemplate) it.next();
	        Field fld=factory.createField();
	        fld.setIdentifier(p.getIdentifier());
	        this.setIDLTyped(fld,p.getIdlType());
			structD.getMembers().add(fld);
	    }
	}
			
	private void addMemberNodes(Node opNode) {
	     Iterator it = structD.getMembers().iterator();
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
	    if (opNode!=null) {
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			                                   CCMNotificationImpl.ST_FIELD, null, null,0));
	    }
	}

	private void deleteMembers(){
	    Iterator it=structD.getMembers().iterator();
	    int i=0;
	    while(it.hasNext()){
	        Field fld=(Field) it.next();
	        FieldTemplate p=(FieldTemplate)members.get(i);
	        unSetIDLTyped(fld,p.getIdlType());
	        if (opNode==null) continue;
			opNode.getContents().removeAll(fld.getNodeFromTyped());
	        fld.getNodeFromTyped().clear();
	        i=i+1;
	    }
	    structD.getMembers().clear();
	    if (opNode!=null) {
	    opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			       CCMNotificationImpl.OP_PARAMETERS, null, null,0));
	    }
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

}
