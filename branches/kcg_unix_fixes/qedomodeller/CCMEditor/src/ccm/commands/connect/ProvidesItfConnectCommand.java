/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 *      siegercn

 * 
 */
package ccm.commands.connect;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.gef.commands.Command;

import CCMModel.CCMModelFactory;
import CCMModel.Connection;
import CCMModel.ConnectionDiscription;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.ProvidesDef;
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
public class ProvidesItfConnectCommand extends Command {
	private List otherviews =new ArrayList();
	private List connections =new ArrayList();
	protected Node source;
	protected Node target;
	protected Connection connection;
	protected View view;
	protected ConnectionDiscription description;
	private boolean singelConnetion=false;
	private InterfaceDef itf;
	private ProvidesDef port;
	//private ModuleDef moduleDef;
	//private InterfaceRelation relation;
	
	
	private CCMModelFactory factory=CCMModelManager.getFactory();
	/**
	 * @see org.eclipse.gef.commands.Command
	 */			
	public ProvidesItfConnectCommand() {
		super();
	}
	/**
	 * @see org.eclipse.gef.commands.Command
	 */			
	public ProvidesItfConnectCommand(String s) {
		super(s);
	}
	
	/**
	* @see org.eclipse.gef.commands.Command#execute()
	*/
	public void execute() {
	    connection =factory.createConnection();
	  //  relation=factory.createInterfaceRelation();
	    description=factory.createConnectionDiscription();
	    description.setLabel(CCMConstants.PROVIDES_INTERFACE_LABEL);
	    port=(ProvidesDef) source.getContained();
	    itf=(InterfaceDef) target.getContained();
	  //  moduleDef=view.getModuleDef();
		createConnection();
	}
	
	//connecting
	protected void createConnection(){	
		port.setInterface(itf);
	  //  itf.getInterfaceRelation().add(relation);
	  //  port.setInterfaceRelation(relation);
	    connection.setConnectionDiscription(description);
	  //  relation.getConnection().add(connection);
	    source.getConSource().add(connection);
	    target.getConnTarget().add(connection);
	    view.getConnection().add(connection);
	   // moduleDef.getRelations().add(relation);	
	    if(!singelConnetion) 
		   	   createConnections();
		   
		}
		
	public void setSingle(){
			singelConnetion=true;
		}
		
	private void createConnections(){  
	    ModuleDef root=view.getModuleDef();
	    List views=root.getView();
	    
	    for (int i=0;i<views.size();i++){
	    	View v= (View)views.get(i);
	    	 if(!v.equals(view)){
	    	Node vSource=null,vTarget=null;
	    	List nodes=v.getNode();
	    	for (int j=0;j<nodes.size();j++){
	    		Node n=(Node)nodes.get(j);
	    		if(n.getContained().equals(source.getContained()))
	    			vSource=n;
	    		if(n.getContained().equals(target.getContained()))
	    			vTarget=n;
	    	}
	    	if(vSource!=null&&vTarget!=null){
	    		ProvidesItfConnectCommand command=new ProvidesItfConnectCommand();
    			command.setSource(vSource);
    			command.setTarget(vTarget);
    			command.setView(v);
    			command.setSingle();
    			command.execute();
    			connections.add(command.getConnection());
    			otherviews.add(v);
    			
    		}
	    	 }
	    }
	     		
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
	    port.setInterface(null);
	   // moduleDef.getRelations().remove(relation);
	    
	   // itf.getInterfaceRelation().remove(relation);
	   // port.setInterfaceRelation(null);
	  //  relation.getConnection().remove(connection);
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