/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 @author Siegercn
 * 
 */
package ccm.commands.create.visual.adds;


import java.util.Iterator;

import org.eclipse.draw2d.geometry.Rectangle;

import CCMModel.Assembly;
import CCMModel.ComponentInstantiation;
import CCMModel.HomeInstantiation;
import CCMModel.Node;
import CCMModel.Rule;
import ccm.commands.create.visual.CreateNodeForContainedCommand;
import ccm.model.template.IDLKind;
import ccm.model.template.IDLTemplate;



public class AddRuleCommand extends CreateNodeForContainedCommand{
    
	private static final String	CreateCommand_LabelSimple = "AddRuleCommand";

	private Node opNode;
	private Node parentNode;
	private Rectangle constraint;
	
	private Rule rule;
	
	private String name,condition,action,language;
	private IDLTemplate idlTemplate=new IDLTemplate(IDLKind.IDL_LITERAL);

	
	/**
	 * Constructor of this command, 
	 */
	public AddRuleCommand() {
		super();
		setLabel(CreateCommand_LabelSimple);
	}

	/**
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		if (container instanceof Assembly
				||container instanceof ComponentInstantiation
				||container instanceof HomeInstantiation)
			return true;
		return false;
	}
	/**
	 * The execution of this command creates a new ClassifierNode
	 * (Simple or Collection)
	 */
	public void execute() {
	    super.execute();
	    
	    if (container instanceof Assembly)
	    	((Assembly)container).getRules().add(newObject);
	    if (container instanceof ComponentInstantiation)
	    	((ComponentInstantiation)container).getRules().add(newObject);
	    if (container instanceof HomeInstantiation)
	    	((HomeInstantiation)container).getRules().add(newObject);
	    rule = (Rule) newObject;
		rule.setName(name);
		rule.setCondition(condition);
		rule.setAction(action);
		rule.setLanguage(language) ;
		if (!(container instanceof Assembly)){
			Iterator it = container.getNode().iterator();
			while(it.hasNext()) {
				parentNode = (Node) it.next();
				opNode=factory.createNode();
				rule.getNode().add(opNode);
				opNode.setX(constraint.x);
				opNode.setY(constraint.y);
				opNode.setWidth(constraint.width);
				opNode.setHeight(constraint.height);
				parentNode.getContents().add(opNode);
			}
	    }
	}

	/**
	 * Redos a previously made undo of this command
	 */
	public void redo() {
	    if (parentNode!=null) {
	    	opNode.setContained(rule);
	    	parentNode.getContents().add(opNode);
	    }
		super.redo();
		 
	}
	
	
	/**
	 * Invalidates the actions done by this command
	 */
	public void undo() {	
	    if (parentNode!=null) {
	    	opNode.setContained(null);
	    	parentNode.getContents().remove(opNode);
	    }
		 
		super.undo();
	}

	public void setConstraint(Rectangle constraint) {
		this.constraint = constraint;
	}

	public void setName(String name) {
		this.name = name;
	}
	public void setCondition(String condition) {
		this.condition = condition;
	}
	public void setAction(String action) {
		this.action =action;
	}
	public void setLanguage(String language) {
		this.language =language;
	}
    /**
     * @return Returns the parentNode.
     */
    public Node getParentNode() {
        return parentNode;
    }
    /**
     * @param parentNode The parentNode to set.
     */
    public void setParentNode(Node parentNode) {
        this.parentNode = parentNode;
    }
    /**
     * @return Returns the idlTemplate.
     */
    
}
  