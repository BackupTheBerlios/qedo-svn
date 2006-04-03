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
package ccm.commands.create.visual;


import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;

import CCMModel.ConstantDef;
import CCMModel.Node;
import CCMModel.View;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;



public class CreateNodeForConstantDefCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "CreateParameterCommand";

	private Node opNode;
	private View view;
	private Rectangle constraint;
	
	private ConstantDef constant;
	
	private String constValue="";
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public CreateNodeForConstantDefCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (view !=null &
			container !=null &
			newObject !=null)return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    constant=(ConstantDef) newObject;
		opNode=factory.createNode();
		constant.getNode().add(opNode);
		opNode.setX(constraint.x);
		opNode.setY(constraint.y);
		opNode.setWidth(constraint.width);
		opNode.setHeight(constraint.height);
		view.getNode().add(opNode);
		constant.setConstValue(constValue);
		setIDLTyped(constant,idlTemplate);
		opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
										       CCMNotificationImpl.CONSTANT_DEF, null, null,0));
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
		opNode.setContained(constant);
		view.getNode().add(opNode);
		super.redo();
		setIDLTyped(constant,idlTemplate);
	}
	
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {	
	    opNode.setContained(null);
		view.getNode().remove(opNode);
		unSetIDLTyped(constant,idlTemplate);
		super.undo();
	}

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}
	
	public void setView(View view) {
		this.view = view;
	}

	public String getConstValue() {
		return constValue;
	}
	

	public void setConstValue(String context) {
		this.constValue = context;
	}

    /**
     * @param idlTemplate The idlTemplate to set.
     */
    public void setIdlTemplate(IDLTemplate idlTemplate) {
        this.idlTemplate = idlTemplate;
    }
    /**
     * @return Returns the idlTemplate.
     */
    public IDLTemplate getIdlTemplate() {
        return idlTemplate;
    }
}
