/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * @author Siegercn
 * 
 */
package ccm.commands.connect;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.gef.commands.Command;

import CCMModel.CCMModelFactory;
import CCMModel.ComponentInstantiation;
import CCMModel.Connection;
import CCMModel.ConnectionDiscription;
import CCMModel.HomeInstantiation;
import CCMModel.Node;
import CCMModel.View;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;




/**
 * Class       :ConnectCommand<br/>
 * Package     : <br/>
 * Project     : <br/>
 * Created On  : 22.05.2004<br/>
 * Description : Command to connect two nodes with edge
 * <br/>
 * @author vilapower
 */
public class HomeCreateComponentInstanceConnectCommand extends Command {
	
	protected Node source;
	protected Node target;
	protected Connection connection;
	protected View view;
	protected ConnectionDiscription description;
	private boolean singelConnetion=false;
	private ComponentInstantiation componentInstance;
	private HomeInstantiation homeInstance;
	//private ModuleDef moduleDef;
	//private CompHomeRelation relation;
	private List otherviews =new ArrayList();
	private List connections =new ArrayList();
	
	private CCMModelFactory factory=CCMModelManager.getFactory();
	/**
	 * @see org.eclipse.gef.commands.Command
	 */			
	public HomeCreateComponentInstanceConnectCommand() {
		super();
	}
	/**
	 * @see org.eclipse.gef.commands.Command
	 */			
	public HomeCreateComponentInstanceConnectCommand(String s) {
		super(s);
	}
	
	/**
	* @see org.eclipse.gef.commands.Command#execute()
	*/
	public void execute() {
	    connection =factory.createConnection();
	    //connection.setConnectionKind(ConnectionsKind.COMPOSITION_LITERAL);
	    //relation=factory.createCompHomeRelation();
	    description=factory.createConnectionDiscription();
	    description.setLabel(CCMConstants.CREATE);
//	    componentInstance=(ComponentInstantiation) target.getContained();
//	    homeInstance=(HomeInstantiation) source.getContained();
	    //moduleDef=view.getModuleDef();
		createConnection();
	}
	
	//connecting
	protected void createConnection(){
		//unitEnd.setComposition(compositionEnd);
		//compositionEnd.setHomeImpl(homeImplEnd);
		//homeImplEnd.getComposition().add(compositionEnd);
	    //homeEnd.setCompHomeRelation(relation);
	    //componentEnd.getCompHomeRelation().add(relation);
	    connection.setConnectionDiscription(description);
	   // relation.getConnection().add(connection);
	    source.getConSource().add(connection);
	    target.getConnTarget().add(connection);
	    view.getConnection().add(connection);
	   // moduleDef.getRelations().add(relation);	
	    
		}
		
		public void setSingle(){
			singelConnetion=true;
		}
		
		 
	private void removeConnections(){
		for (int i=0;i<otherviews.size();i++){
			((View)otherviews.get(i)).getConnection().remove(connections.get(i));
		}
	}
	public Connection getConnection(){
		return connection;
	}
	/**
	* @see org.eclipse.gef.commands.Command#redo()
	*/
	public void redo() {
	    createConnection();	
	}

	/**
	* @see org.eclipse.gef.commands.Command#undo()
	*/	
	public void undo() {
	    source.getConSource().remove(connection);
	    target.getConnTarget().remove(connection);
	    view.getConnection().remove(connection);
	    //moduleDef.getRelations().remove(relation);
	   // compositionEnd.setHomeImpl(null);
//		homeImplEnd.getComposition().remove(compositionEnd);
	    //homeEnd.setCompHomeRelation(null);
	    //componentEnd.getCompHomeRelation().remove(relation);
	    //relation.getConnection().remove(connection);
	    connection.setConnectionDiscription(null);
	    removeConnections();
	}

    /**
     * @param source The source to set.
     */
    public void setSource(Node source) {
        this.source = source;
    }
    
    /**
     * @param target The target to set.
     */
    public void setTarget(Node target) {
        this.target = target;
    }
    
    /**
     * @param view The view to set.
     */
    public void setView(View view) {
        this.view = view;
    }
    
    /**
     * @see org.eclipse.gef.commands.Command#canExecute()
     */
    public boolean canExecute() {
        if(view!=null && source!=null && target!=null)
            if(source.getContained()!=target.getContained())
                return true;
        return false;
    }

    /**
     * @return Returns the source.
     */
    public Node getSource() {
        return source;
    }
}
  