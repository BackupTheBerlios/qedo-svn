/*
 * Created on 20.07.2005
 *
 */
package ccm.commands.dnd;

import org.eclipse.gef.commands.Command;

import CCMModel.CCMModelFactory;
import CCMModel.Contained;
import CCMModel.Diagram;



/**
 * @author christian
 */
public class AddRelation2DiagramCommand extends Command {

	private Diagram diagram;
	//private Relation relation;
	
	private Contained source;
	private Contained target;
	
	protected CCMModelFactory factory;

	
	
//	public AddRelation2DiagramCommand(Relation relation, Diagram diagram) {
//		this.diagram = diagram;
//		this.relation = relation;
//		source = CCMModelTreeEditPart.getRelationSource(relation);
//		target = CCMModelTreeEditPart.getRelationTarget(relation);
//		factory = CCMModelManager.getFactory();	
//	}
//
//
//	public boolean canExecute() {
//		return super.canExecute();
//	}
//	
//	public void execute() {
//
//		Vector source_nodes = new Vector();
//		Vector target_nodes = new Vector();
//				
//		// iterate all nodes in the diagramm
//		for (int i = 0; i < diagram.getView().getNode().size(); i++) {
//			Node n = (Node) diagram.getView().getNode().get(i);
//			if (n.getContained()==source) source_nodes.add(n);
//			if (n.getContained()==target) target_nodes.add(n);
//		}
//		
//		// delete existing connections
//		for (int i=0; i<diagram.getView().getConnection().size(); i++) {
//			Connection con = (Connection) diagram.getView().getConnection().get(i);
//			if (con.getRelation()==relation) {
//				relation.getConnection().remove(con);
//				con.getSource().getConSource().remove(con);
//				con.getTarget().getConnTarget().remove(con);
//				diagram.getView().getConnection().remove(con);
//				i--;
//			}
//		}
//
//		// add connections between source and target nodes
//		for (int i = 0; i < source_nodes.size(); i++) {
//			for (int j = 0; j < target_nodes.size(); j++) {
//
//				Connection connection = factory.createConnection();
//				ConnectionDiscription desc = factory.createConnectionDiscription();
//				desc.setLabel(CCMConstants.getRelationDescription(relation));
//
//				connection.setConnectionDiscription(desc);				
//				connection.setRelation(relation);
//				connection.setSource((Node) source_nodes.get(i));
//				connection.setTarget((Node) target_nodes.get(j));
//				((Node) source_nodes.get(i)).getConSource().add(connection);
//				((Node) target_nodes.get(j)).getConnTarget().add(connection);
//				
//				relation.getConnection().add(connection);
//				diagram.getView().getConnection().add(connection);
//			}
//		}		
//	}	
}
