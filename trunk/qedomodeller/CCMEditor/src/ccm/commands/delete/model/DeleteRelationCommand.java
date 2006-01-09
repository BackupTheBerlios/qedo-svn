/*
 * Created on 24.06.2005
*/
package ccm.commands.delete.model;

import org.eclipse.gef.commands.Command;

public class DeleteRelationCommand extends Command {
	protected static final String DeleteRelation_Label = "DeleteRelationCommand";
	 
	
	/**
	 * Constructor of this command - no parameters needed
	 */
	public DeleteRelationCommand() {
		super( DeleteRelation_Label );
	}
	
	/**
	 * @param delClassifier
	 * @param parent
	 */
//	public DeleteRelationCommand(Relation model) {
//		super();
//		this.model=model;
//	}
//	/**
//	 * Execution of this command deletes a classifierRole
//	 * completely.
//	 */
//	public void execute() {
//
//		//Iterator nIt = model.getConnection().iterator();
//		List conns = model.getConnection() ;
//		for (int i= 0;i<conns.size();i++){
//			ConnectionImpl n =(ConnectionImpl)conns.get(i);
//			DeleteConnectionCommand cmd = new DeleteConnectionCommand(n);
//			if (cmd.canExecute()) cmd.execute();
//		}
//		//while(nIt.hasNext()) {
//		//	ConnectionImpl n = (ConnectionImpl) nIt.next();
//		//	DeleteConnectionCommand cmd = new DeleteConnectionCommand(n);
//		//	if (cmd.canExecute()) cmd.execute();
//			 
//		//}
//		disconnectFromEndpoints();
//		model.getModuleDef().getRelations().remove(model);
//	}
//	
//	// sets endpoint references to the relation to null
//	private void disconnectFromEndpoints() {
//		if(model instanceof SupportsRelation){
//			if(((HomeDefImpl)((SupportsRelation)model).getHomes()) != null)
//				((HomeDefImpl)((SupportsRelation)model).getHomes()).getSupportsRelation().clear();
//			else
//				((ComponentDefImpl)((SupportsRelation)model).getComponents()).getSupportsRelation().remove(model);
//			((InterfaceDefImpl)((SupportsRelation)model).getSupportsItf()).getSupportsRelation().clear();
//		}
//		else if(model instanceof CompHomeRelation) {
//			if(((CompHomeRelation)model).getComponentEnd() !=null)
//				((CompHomeRelation)model).getComponentEnd().getCompHomeRelation().remove(model);
//			((CompHomeRelation)model).getHomeEnd().setCompHomeRelation(null);
//		}
//		else if(model instanceof InterfaceRelation) {
//			((InterfaceRelation)model).getItf().getInterfaceRelation().remove(model);
//			if(((InterfaceRelation)model).getProvidesDef() != null)
//			((InterfaceRelation)model).getProvidesDef().setInterfaceRelation(null);
//			if(((InterfaceRelation)model).getUsesDef() != null)
//				((InterfaceRelation)model).getUsesDef().getInterfaceRelation().remove(model);
//		}
//		else if(model instanceof AbstractDerivedRelation) {
//			((AbstractDerivedRelation)model).getAbstractBase().getAbstractDerivedRelation().remove(model);
//			((AbstractDerivedRelation)model).getAbstractDerived().getAbstractDerivedRelation().remove(model);
//		}
//		else if(model instanceof AbstractItfDerivedRelation) {
//			((AbstractItfDerivedRelation)model).getBase().getDerivedRelation().remove(model);
//			((AbstractItfDerivedRelation)model).getDerived().getDerivedRelation().remove(model);
//		}
//		/*else if(model instanceof ValueDerivedRelation) {
//			((ValueDerivedRelation)model).getBase().get;
//			((ValueDerivedRelation)model).setDerived(null);
//		}*/
//		else if(model instanceof EventPortEventRelation) {
//			((EventPortEventRelation)model).setEnds(null);
//			((EventPortEventRelation)model).setType(null);
//		}
//	}
//
//	/**
//	 * Redos an undo.
//	 */
//	public void redo() {
//		model.getModuleDef().getContents().remove(model);
//	}
//	
//	/**
//	 * Undos an action done by this command
//	 */
//	public void undo() {
//		model.getModuleDef().getContents().add(model);
//	}
//	
	/* (non-Javadoc)
	 * @see org.eclipse.gef.commands.Command#canExecute()
	 */
	public boolean canExecute() {
		return true;
	}
}