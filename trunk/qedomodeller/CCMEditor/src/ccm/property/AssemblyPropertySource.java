package ccm.property;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.Assembly;
import CCMModel.AssemblyConnection;
import CCMModel.CCMModelFactory;
import CCMModel.ComponentDef;
import CCMModel.ComponentFeature;
import CCMModel.ComponentFile;
import CCMModel.Connection;
import CCMModel.ConnectionsKind;
import CCMModel.Contained;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.Rule;
import CCMModel.SoftwarePackage;
import CCMModel.View;
import ccm.model.CCMModelManager;
import ccm.model.ModelFactory;
import ccm.propertyDescriptor.ComponentFilePropertyDescriptor;
import ccm.propertyDescriptor.ConnectionPropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class AssemblyPropertySource extends ContainedPropertySource {

    protected Assembly abstObj;
    private List packages;
    private ModuleDef root;
    private CCMModelFactory factory=CCMModelManager.getFactory();
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public AssemblyPropertySource(Contained element) {
        	super(element);
        	abstObj=(Assembly) element;
        	ModelFactory mf = new ModelFactory();
        	root=mf.getRootModule(abstObj);
        	packages=mf.getAllContained(root,SoftwarePackage.class);
        	 
        	 
          
        	
    }
	
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyDescriptors()
     */
    public IPropertyDescriptor[] getPropertyDescriptors() {
    	 propertyDescriptors=super.getPropertyDescriptors();
         Collection	descriptors = new Vector();
        
         for(int i=0;i<propertyDescriptors.length;i++){
             descriptors.add(propertyDescriptors[i]);
         }
         
    	String cat="local";
   		//if(object!=null)cat=cat+ object.eClass().getName();
        
         // Create a descriptor and set a category
    	PropertyDescriptor uuid = new TextPropertyDescriptor(Integer.toString(100), "uuid");
    	uuid.setCategory(cat);
        descriptors.add(uuid);       
        
       
        // Create a descriptor and set a category
        PropertyDescriptor parameters = new ComponentFilePropertyDescriptor(
				Integer.toString(101),
				"componentFiles", abstObj.getConfig().getComponentFile(), packages) ;
        	
        parameters.setCategory(cat);
        descriptors.add(parameters);
        
        PropertyDescriptor containedPackage = new  PropertyDescriptor(
            Integer.toString(102),
               "contained package" );
       containedPackage.setCategory(cat);
       descriptors.add(containedPackage);

  //     PropertyDescriptor rules= new RulePropertyDescriptor(
  //				Integer.toString(103),
  //				"rules", abstObj.getRules() ) ;
       	
  //     rules.setCategory(cat);
  //     descriptors.add(rules);
       

       PropertyDescriptor connection= new ConnectionPropertyDescriptor(
				Integer.toString(104),
				"connections", abstObj) ;
       	
       connection.setCategory(cat);
       descriptors.add(connection);
       
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	 
    	String paraNames="";
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	       return abstObj.getUuid();
	   
	    case 101:
	    	 
	    	for(Iterator it =abstObj.getConfig().getComponentFile().iterator();it.hasNext();){
	    		String paraname =((ComponentFile)it.next()).getIdentifier();
	    		if (paraNames.equals(""))
	    			paraNames=paraNames+paraname;
	    		else
	    			paraNames=paraNames+","+paraname;
	    		}
	        return paraNames;
    case 102:
    	for(Iterator it =abstObj.getSoftwarePackage().iterator();it.hasNext();){
    		String paraname =((SoftwarePackage)it.next()).getIdentifier();
    		if (paraNames.equals(""))
    			paraNames=paraNames+paraname;
    		else
    			paraNames=paraNames+","+paraname;
    		}
        return paraNames;
    case 103:
    	for(Iterator it =abstObj.getRules().iterator();it.hasNext();){
    		String paraname =((Rule)it.next()).getIdentifier();
    		if (paraNames.equals(""))
    			paraNames=paraNames+paraname;
    		else
    			paraNames=paraNames+","+paraname;
    		}
        return paraNames;
    case 104:
    	for(Iterator it =abstObj.getConnection().iterator();it.hasNext();){
    		String paraname =((AssemblyConnection)it.next()).getIdentifier();
    		if (paraNames.equals(""))
    			paraNames=paraNames+paraname;
    		else
    			paraNames=paraNames+","+paraname;
    		}
        return paraNames;
        
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	        abstObj.setUuid((String)value); 
	        break;
	    case 101:
	   	    addComponenFiles((List)value);
		    break;
		case 103:
			addRules((List)value);
			break;
		case 104:
			addConnections((List)value);
			break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
    /**
	 * @param list
	 */
	private void addConnections(List acons) {
		List aconList= abstObj.getConnection();
		for (Iterator it =aconList.iterator();it.hasNext();){
			AssemblyConnection acon =(AssemblyConnection)it.next();
			acon.setDefinedIn(null);
			List cons= acon.getConnection();
			for (Iterator cit=cons.iterator();cit.hasNext();){
				Connection con=(Connection)cit.next();
				con.setView(null);
				con.setSource(null);
				con.setTarget(null);
			}
			cons.clear();
			if(!acons.contains(acon)){
				acon.getTarget().setInstance(null);
				acon.getTarget().setFeature(null);
				acon.getSource().setInstance(null);
				acon.getSource().setFeature(null);
			}
		}
		aconList.clear();
		abstObj.getContents().addAll(acons);
		abstObj.getConnection().addAll(acons);
		for (Iterator it =acons.iterator();it.hasNext();){
			AssemblyConnection acon =(AssemblyConnection)it.next();
			Contained source;
			Contained target=(Contained)acon.getTarget().getFeature();
			ComponentFeature sourceFeature=acon.getSource().getFeature();
			if(sourceFeature!=null
				&& !(sourceFeature instanceof ComponentDef)){
			 	
				source=(Contained)sourceFeature;	
				 
			}
			else
				source=(Contained)acon.getSource().getInstance();
			createConnections(source,target,acon);
			
		}
		
		
	}

	/**
	 * @param rules
	 */
	private void addRules(List rules) {
		List ruleList= abstObj.getRules();
		for (Iterator it =ruleList.iterator();it.hasNext();){
			Rule rule =(Rule)it.next();
			rule.setDefinedIn(null);
		}
		ruleList.clear();
		for (Iterator it =rules.iterator();it.hasNext();){
	 		Rule rule =(Rule)it.next();
			rule.setDefinedIn(abstObj);
			rule.setRuleOwner(abstObj);
	 }
		
	}

	private void addComponenFiles(List componentFiles){
		 
	//	Resource resource = operation.eResource();
		 
		 
		 
    	List conFList=abstObj.getConfig().getComponentFile();
		for (Iterator it =conFList.iterator();it.hasNext();){
			ComponentFile comFile= (ComponentFile )it.next();
			if(!componentFiles.contains(comFile))
				comFile.setPackage(null);
			//comFile.setAssembly(null);
			comFile.setDefinedIn(null);
			 
		}
		conFList.clear(); 
		abstObj.getSoftwarePackage().clear();
		 
	    //Iterator it=componentFiles.iterator();
	    for (Iterator it =componentFiles.iterator();it.hasNext();){
			ComponentFile comFile = (ComponentFile)it.next();
			if (comFile.getLocation()==""||comFile.getLocation()==null)
				abstObj.getSoftwarePackage().add(comFile.getPackage());
			
		}
	    if( componentFiles.size()>0){
	    	abstObj.getContents().addAll(componentFiles);
	    	abstObj.getConfig().getComponentFile().addAll(componentFiles);
	    }
    }
	private void createConnections(Contained source,Contained target, AssemblyConnection acon){  
	    
	    List views=root.getView();
	    for (int i=0;i<views.size();i++){
	    		View v= (View)views.get(i);
	    		Node vSource=null,vTarget=null;
	    		List nodes=v.getNode();
	    		for (int j=0;j<nodes.size();j++){
	    			Node n=(Node)nodes.get(j);
	    			 
    				if(n.getContained().equals(target))
    					vTarget=n;
	    			
	    			if (n.getContained().equals(abstObj)){
	    			  List pnodes=n.getContents();
	    			  for (int k=0;k<pnodes.size();k++){
	    			  	Node pnode=(Node)pnodes.get(k);
	    			  	//if (pnode.getContained().equals(process)){
	    			  	List inodes=pnode.getContents();
	    			  	for (int l=0;l<inodes.size();l++){
	    			  		 	Node inode=(Node)inodes.get(l);
	    			  		 	if(inode.getContained().equals(source ))
	    	    					vSource=inode;
	    	    				if(inode.getContained().equals(target))
	    	    					vTarget=inode;
	    			  		
	    			  	}
	    			  	
	    			  }
	    			//}	
	    		}
	    	}
	    	if(vSource!=null&&vTarget!=null){
	    	//	InterfaceConnectCommand command=new InterfaceConnectCommand();
    		//	command.setSource(vSource);
    		//	command.setTarget(vTarget);
    		//	command.setView(v);
    		//	command.setSingle();
    		//	command.execute();
    		//	connections.add(command.getConnection());
    		//	otherviews.add(v);
	    		Connection con =factory.createConnection();
			    con.setConnectionDiscription(factory.createConnectionDiscription());
			    con.setConnectionKind(ConnectionsKind.INSTANCECONNECTION_LITERAL);
			    vSource.getConSource().add(con);
			    vTarget.getConnTarget().add(con);
			    v.getConnection().add(con);
			    con.setAssemblyConnection(acon);
    			
    		}
	    
	  }
	     		
	}	
}
 
 
 