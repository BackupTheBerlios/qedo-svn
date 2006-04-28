/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 */

package ccm.commands.delete.visual;

import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import org.eclipse.gef.commands.Command;

import CCMModel.Contained;
import CCMModel.Node;
import CCMModel.PortNode;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;


/**
 * @author holger kinscher
 */
public class DeleteNodeCommand extends Command {
	
	protected static final String DeleteCommand_Label = "DeleteNodeCommand";
	protected Node node;
	protected View parent;
	
	
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteNodeCommand() {
		super( DeleteCommand_Label );
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 * @param part 
	 */
	public DeleteNodeCommand(Node delClassifier){
		super();
		this.node = delClassifier;
		this.parent = delClassifier.getView();
		}
	public DeleteNodeCommand(Node delClassifier, View parent, Contained model) {
		super();
		this.node = delClassifier;
		this.parent = parent;
	}
	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
	//	if(node.getContained() instanceof EventPortDef||
	//			node.getContained() instanceof ProvidesDef||
	//			node.getContained() instanceof UsesDef)
	//		return false;
		//if (parent instanceof ViewImpl) 
			return true;
		//else return false;
	}

	
	
	public void execute() {
		List nodeList=node.getContents();
		if(nodeList.size()>0){
		DeleteNodeCommand[]delNodes=new DeleteNodeCommand[nodeList.size()] ;
		for (int k=0;k<nodeList.size();k++){
			Node n=(Node)nodeList.get(k);
			delNodes[k]=new DeleteNodeCommand(n, n.getView(), n.getContained());
		}
		for (int k=0;k<delNodes.length;k++){
			delNodes[k].execute();
		}
		}
		execute(node);
	}
	
	
	/**
	 * Execution of this command deletes a node
	 * completely.
	 */
	public void execute(Node n) {
		
		// remove connections
		Vector connections = new Vector();
		connections.addAll(n.getConnTarget());
		connections.addAll(n.getConSource());
		
		Iterator it = connections.iterator();
		
		while (it.hasNext()) {
			ConnectionImpl con = (ConnectionImpl) it.next();
			DeleteConnectionCommand cmd = new DeleteConnectionCommand(con);
			if (cmd.canExecute()) cmd.execute();
		}
		
		//remove all children nodes
		if (n.getContents()!=null) {
			it = (new Vector(n.getContents())).iterator();
			while (it.hasNext()) {
				Node cont = (Node) it.next();
				execute(cont);
				//cont.getView().getNode().remove(cont);
				//cont.getContained().getNode().remove(cont);
			}
		}
		
		//remove all connections
		Iterator iIt = node.getConnTarget().iterator();
		while(iIt.hasNext()) {
			ConnectionImpl c = (ConnectionImpl) iIt.next();
			Command cmd = new DeleteConnectionCommand(c);
			cmd.execute();
			iIt = node.getConnTarget().iterator();
		}
		Iterator oIt = node.getConSource().iterator();
		while(oIt.hasNext()) {
			ConnectionImpl c = (ConnectionImpl) oIt.next();
			Command cmd = new DeleteConnectionCommand(c);
			cmd.execute();
			oIt = node.getConSource().iterator();
		}
		//List portnodes=new ArrayList();
		//List portnodes=n.getPortNode();
		//if(n.getContained() instanceof ComponentDef){
		//	List nodes=n.getView().getNode();
			 
		//	for (Iterator nit=nodes.iterator();nit.hasNext();){
		//		Node cnode= (Node)nit.next();
		//		if(cnode instanceof PortNode&&((PortNode)cnode).getHostNode().equals(n))
		//		{}//portnodes.add(cnode);
					//execute(cnode);
		//	}
			
		//}
		
		//remove node itself from view and parent
		if (n.getContained()!=null) n.getContained().getNode().remove(n);
		if (n instanceof PortNode) 
			((PortNode)n).getHostNode().getPortNode().remove(n);
		if (node.getView()!=null) node.getView().getNode().remove(n);
		if (n.getDefineIn()!=null) n.getDefineIn().getContents().remove(n);
		if (n.getTyped()!=null && n.getTyped().getNodeFromTyped()!=null) { 
			n.getTyped().getNodeFromTyped().remove(n);
		}
	//	for (Iterator pit= portnodes.iterator();pit.hasNext();){
	//		execute((Node)pit.next());
	//	}

	}

	
	
	/**
	 * Redos an undo.
	 */
	public void redo() {
		parent.getNode().remove(node);
		node.getContained().getNode().remove(node);
	}
	/**
	 * Undos an action done by this command
	 */
	public void undo() {
		parent.getNode().add(node);
		node.getContained().getNode().add(node);
	}
	
	/**
	 * Setter for the classifierNode
	 * @param cls - the new node
	 */
	public void setDelClassifier(Node cls) {
		this.node = cls;
	}
	
	/**
	 * Setter for the container, where the node is placed in
	 * @param container
	 */
	public void setView(View container) {
		this.parent = container;
		
	}
	
	/**
	 * @return Returns the delClassifier.
	 */
	public Node getDelClassifier() {
		return node;
	}
}
