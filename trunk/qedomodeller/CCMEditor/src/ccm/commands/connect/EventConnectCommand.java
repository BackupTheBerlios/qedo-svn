package ccm.commands.connect;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.gef.commands.Command;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Shell;

import CCMModel.Assembly;
import CCMModel.AssemblyConnection;
import CCMModel.CCMModelFactory;
import CCMModel.ComponentInstantiation;
import CCMModel.Connection;
import CCMModel.ConnectionDiscription;
import CCMModel.ConnectionEnd;
import CCMModel.ConnectionsKind;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.EmitsDef;
import CCMModel.EventDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.PortNode;
import CCMModel.ProcessCollocation;
import CCMModel.PublishesDef;
import CCMModel.View;
import ccm.dialogs.CreateContainedDialog;
import ccm.model.CCMModelManager;




/**
 * @author siegercn
 */
public class EventConnectCommand extends Command {
	private List otherviews =new ArrayList();
	private List connections =new ArrayList();
	protected Node source;
	protected Node target;
	protected Connection connection;
	protected View view;
	protected ConnectionDiscription description;
	private boolean singelConnetion=false;
	private Contained con;
	private ConsumesDef port;
	private AssemblyConnection aConnection;
	private EventDef event;
	private Assembly ass;
	private ProcessCollocation process;
	private CCMModelFactory factory=CCMModelManager.getFactory();
	private String identifier="";
	private String version="1.0";
	private String repositoryID="";
	private Shell shell;
	
	public void setIdentifier(String identifier){
		this.identifier=identifier;
	}
	public void setVersion(String version){
		this.version=version;
	}
	public void setRepositoryID(String repositoryID)
	{
		this.repositoryID=repositoryID;
	}
	public void setShell(Shell shell){
		this.shell=shell;
	}
	/**
	 * @see org.eclipse.gef.commands.Command
	 */			
	public EventConnectCommand() {
		super();
	}
	/**
	 * @see org.eclipse.gef.commands.Command
	 */			
	public EventConnectCommand(String s) {
		super(s);
	}
	
	/**
	* @see org.eclipse.gef.commands.Command#execute()
	*/
	public void execute() {
		CreateContainedDialog d=new CreateContainedDialog(shell,SWT.NULL); 
	    //createDialog.setVersion(component.getVersion());
	    d.setDiscription("Add a Connection ");
	    d.setVersion(version);
	    d.open();
        if(!d.isState() )
        	return ;
		
	    connection =factory.createConnection();
	    connection.setConnectionKind(ConnectionsKind.INSTANCECONNECTION_LITERAL);
	    description=factory.createConnectionDiscription();
        //  description.setLabel(CCMConstants.PROVIDES_INTERFACE_LABEL);
	    // port=(UsesDef) source.getContained();
	    // con= target.getContained();
	    //  moduleDef=view.getModuleDef();
	    ComponentInstantiation componentinstance=(ComponentInstantiation)((PortNode)source).getHostNode().getContained();
	    ass=(Assembly) source.getDefineIn().getDefineIn().getContained();
//Configuration config = ass.getConfig();
	    process=(ProcessCollocation) source.getDefineIn().getContained();
	    aConnection=factory.createAssemblyConnection();

	    aConnection.setIdentifier(d.getIdentifier());
	    aConnection.setVersion(d.getVersion());
	    aConnection.setRepositoryId(d.getRepositoryId());
	    
	    ConnectionEnd targetEnd=factory.createConnectionEnd();
	    targetEnd.setInstance(componentinstance);
	    targetEnd.setFeature(port);
	    aConnection.getConnection().add(connection);
	    ConnectionEnd sourceEnd=factory.createConnectionEnd();
	    if (con instanceof PublishesDef){
	    	ComponentInstantiation componentinstanceTarget=(ComponentInstantiation)((PortNode)target).getHostNode().getContained();
	    	sourceEnd.setInstance(componentinstanceTarget);
	    	sourceEnd.setFeature((PublishesDef)con);
	    	
	    	}
	    
	    if (con instanceof EmitsDef){
	    	ComponentInstantiation componentinstanceTarget=(ComponentInstantiation)((PortNode)target).getHostNode().getContained();
	    	sourceEnd.setInstance(componentinstanceTarget);
	    	sourceEnd.setFeature((EmitsDef)con);
	    	}	    
	    
	    aConnection.getContents().add(targetEnd);
	    aConnection.getContents().add(sourceEnd);
	    aConnection.setSource(sourceEnd);
        aConnection.setTarget(targetEnd);
        ass.getContents().add(aConnection);
        ass.getConnection().add(aConnection);
	    //aConnection.setConfig(config);
	   // aConnection.setDefinedIn(ass);
	    aConnection.setVersion(ass.getVersion());
	    aConnection.setRepositoryId(ass.getRepositoryId());
	    
		createConnection();
	}
	
	//connecting
	protected void createConnection(){	
		//port.setInterface(itf);
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
		    			 
	    				if(n.getContained().equals(target.getContained()))
	    					vTarget=n;
		    			
		    			if (n.getContained().equals(ass)){
		    			  List pnodes=n.getContents();
		    			  for (int k=0;k<pnodes.size();k++){
		    			  	Node pnode=(Node)pnodes.get(k);
		    			  	//if (pnode.getContained().equals(process)){
		    			  	List inodes=pnode.getContents();
		    			  	for (int l=0;l<inodes.size();l++){
		    			  		 	Node inode=(Node)inodes.get(l);
		    			  		 	if(inode.getContained().equals(source.getContained()))
		    	    					vSource=inode;
		    	    				if(inode.getContained().equals(target.getContained()))
		    	    					vTarget=inode;
		    			  		
		    			  	}
		    			  	
		    			  }
		    			//}	
		    		}
		    	}
	    	if(vSource!=null&&vTarget!=null){
	    		Connection con =factory.createConnection();
			    con.setConnectionDiscription(factory.createConnectionDiscription());
			    con.setConnectionKind(ConnectionsKind.INSTANCECONNECTION_LITERAL);
			    vSource.getConSource().add(con);
			    vTarget.getConnTarget().add(con);
			    v.getConnection().add(con);
			    con.setAssemblyConnection(aConnection);
    			
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
//	    port.setInterface(null);
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
        if(view!=null && source!=null && target!=null && !source.equals(target)&& ((PortNode)source).getHostNode().getContained() instanceof ComponentInstantiation){
            if(source.getContained()instanceof ConsumesDef){
            	port=(ConsumesDef)source.getContained();
            	event =port.getEvent();
            	if(port.getComponentInstance()!=null && event!=null){
            		//port.getComponentInstance();
            		if((target.getContained() instanceof PublishesDef && ((PortNode)target).getHostNode().getContained() instanceof ComponentInstantiation &&((PublishesDef)target.getContained()).getEvent().equals(event))
            		||(target.getContained() instanceof EmitsDef && ((PortNode)target).getHostNode().getContained() instanceof ComponentInstantiation &&((EmitsDef)target.getContained()).getEvent().equals(event))){
            			con=target.getContained();
            			return true;
            		}
            	}
            }
        }
        return false;
    }

    /**
     * @return Returns the source.
     */
    public Node getSource() {
        return source;
    }
} 
 
