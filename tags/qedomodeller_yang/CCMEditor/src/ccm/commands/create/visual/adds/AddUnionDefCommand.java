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

import CCMModel.ArrayDef;
import CCMModel.FixedDef;
import CCMModel.IDLType;
import CCMModel.Node;
import CCMModel.SequenceDef;
import CCMModel.StringDef;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.WstringDef;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;
import ccm.model.template.UnionFieldTemplate;



public class AddUnionDefCommand extends AddTypedefDefCommand{
    
	private static final String	CreateCommand_LabelSimple = "CreateParameterCommand";

	
	private UnionDef unionD;

	private List unionMembers=new LinkedList();
	private IDLTemplate discrType=new IDLTemplate(IDLKind.IDL_LITERAL);


	
	/**
	 * Constructor of this command, 
	 */
	public AddUnionDefCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    unionD=(UnionDef) newObject;
	    setIDL();
	    
	    addMembers();
	    
	    Node parentNode;
	    Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	unionD.getNode().add(opNode);
	    	opNode.setX(constraint.x);
	    	opNode.setY(constraint.y);
	    	opNode.setWidth(constraint.width);
	    	opNode.setHeight(constraint.height);
	    	parentNode.getContents().add(opNode);
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.ATTRIBUTE_DEF, null, null,0));
			addMemberNodes(opNode);
	    }
	}
	
	private void setIDL(){
	    switch(discrType.getIdlKind().getValue()){
	    case IDLKind.IDL:
	        unionD.setDiscriminatorType((IDLType)idlTypes.get(discrType.getIndexOfIDLType()));
	    	break;
	    case IDLKind.WSTRING:
	        WstringDef wstring=factory.createWstringDef();
	    	wstring.setBound(discrType.getBound());
	    	getRootModule().getCCM().getIdlContainer().getWstrings().add(wstring);
	    	unionD.setDiscriminatorType(wstring);
	    	break;
	    case IDLKind.ARRAY:
	        ArrayDef arr=factory.createArrayDef();
    		arr.setBound(discrType.getBound());
    		getRootModule().getCCM().getIdlContainer().getArrays().add(arr);
    		unionD.setDiscriminatorType(arr);
    		break;
	    case IDLKind.STRING:
	        StringDef string=factory.createStringDef();
    		string.setBound(discrType.getBound());
    		getRootModule().getCCM().getIdlContainer().getStrings().add(string);
    		unionD.setDiscriminatorType(string);
    		break;
	    case IDLKind.FIXED:
	        FixedDef fixed=factory.createFixedDef();
    		fixed.setDigits((new Integer(discrType.getDigits())).shortValue());
    		fixed.setScale((new Integer(discrType.getScale())).shortValue());
    		getRootModule().getCCM().getIdlContainer().getFixeds().add(fixed);
    		unionD.setDiscriminatorType(fixed);
    		break;
	    case IDLKind.SEQUENCE:
	        SequenceDef seq=factory.createSequenceDef();
    		seq.setBound(discrType.getBound());
    		getRootModule().getCCM().getIdlContainer().getSequences().add(seq);
    		unionD.setDiscriminatorType(seq);
	    }
	}
	
	
	private void unSetIDL(){
	    switch(discrType.getIdlKind().getValue()){
	    case IDLKind.WSTRING:
	    	getRootModule().getCCM().getIdlContainer().getWstrings().remove(unionD.getDiscriminatorType());
	    	break;
	    case IDLKind.ARRAY:
    		getRootModule().getCCM().getIdlContainer().getArrays().remove(unionD.getDiscriminatorType());
    		break;
	    case IDLKind.STRING:
    		getRootModule().getCCM().getIdlContainer().getStrings().remove(unionD.getDiscriminatorType());
    		break;
	    case IDLKind.FIXED:
    		getRootModule().getCCM().getIdlContainer().getFixeds().remove(unionD.getDiscriminatorType());
    		break;
	    case IDLKind.SEQUENCE:
    		getRootModule().getCCM().getIdlContainer().getSequences().remove(unionD.getDiscriminatorType());
	    }
	    unionD.setDiscriminatorType(null);
	}
	
	private void addMembers(){
	    unionD.getUnionMembers().clear();
	    Iterator it=unionMembers.iterator();
	    while(it.hasNext()){
	        UnionFieldTemplate p=(UnionFieldTemplate) it.next();
	        UnionField fld=factory.createUnionField();
	        fld.setIdentifier(p.getIdentifier());
	        this.setIDLTyped(fld,p.getIdlType());
	        fld.setLabel(p.getLabel());
			unionD.getUnionMembers().add(fld);
	    }
	}
	
	private void addMemberNodes(Node opNode) {
		Iterator it = unionD.getUnionMembers().iterator();
		while(it.hasNext()) {
			UnionField fld = (UnionField) it.next();
	        if (opNode==null) continue;
	        Node node=factory.createNode();
	        fld.getNodeFromTyped().add(node);
			node.setX(0);
			node.setY(0);
			node.setWidth(-1);
			node.setHeight(-1);
			opNode.getContents().add(node);
			node.eNotify(new CCMNotificationImpl(node, Notification.ADD,
				       							   CCMNotificationImpl.UNION_FIELD, null, null,0));	
	    }

	    if (opNode!=null) {
	    opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			                                   CCMNotificationImpl.UN_UN_FIELD, null, null,0));
	    }
	}

	private void deleteMembers(){
	    Iterator it=unionD.getUnionMembers().iterator();
	    int i=0;
	    while(it.hasNext()){
	        UnionField fld=(UnionField) it.next();
	        UnionFieldTemplate p=(UnionFieldTemplate)unionMembers.get(i);
	        unSetIDLTyped(fld,p.getIdlType());
	        if (opNode==null) continue;
			opNode.getContents().removeAll(fld.getNodeFromTyped());
	        fld.getNodeFromTyped().clear();
	        i=i+1;
	    }
	    unionD.getUnionMembers().clear();
	    if (opNode!=null) {
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			       CCMNotificationImpl.UN_UN_FIELD, null, null,0));
	    }
	}
	
	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
		/*super.redo();
	    setIDL();
		addMembers();*/
	}
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {	
//		deleteMembers();
//	    unSetIDL();
//		super.undo();
	}

    /**
     * @return Returns the parameters.
     */
    public List getUnionMembers() {
        return unionMembers;
    }
    
    /**
     * @param parameters The parameters to set.
     */
    public void setUnionMembers(List parameters) {
        this.unionMembers.clear();
        this.unionMembers.addAll(parameters);
    }

    /**
     * @param discrType The discrType to set.
     */
    public void setDiscrType(IDLTemplate discrType) {
        this.discrType = discrType;
    }
}
