package ccm.property;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.AbstractInterfaceDef;
import CCMModel.ComponentDef;
import CCMModel.Contained;
import CCMModel.HomeDef;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.connect.ComponentHomeConnectCommand;
import ccm.commands.connect.HomeSupportsConnectCommand;
import ccm.commands.delete.visual.DeleteConnectionCommand;
import ccm.model.ModelFactory;
import ccm.propertyDescriptor.ListPropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class HomeDefPropertySource extends ContainedPropertySource  {

    
	private HomeDef home;
	private ComponentDef component;
    private List components;
    private String[]componentNames;
    private List itfs;
    private List allValues;
    private String[]supportItfNames;
    private ModelFactory mf=new ModelFactory();
    private ModuleDef root;
    // private CCMModelFactory factory =CCMModelManager.getFactory();
   // private ModuleDef root;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public HomeDefPropertySource(Contained element) {
        	super(element);
        	home=(HomeDef) element;
        	component=home.getComponent();
        	root= mf.getRootModule(home);
        	itfs=new ArrayList(home.getHomeSupports_itf()); 
        	//root= mf.getRootModule(home);
        	components= mf.getAllContained(root,ComponentDef.class);
        	allValues= mf.getAllContained(root,InterfaceDef.class);
        	 
        	int size=components.size(); 
        	componentNames= new String[size+1];
        	componentNames[0]="none";
        	
        	for (int i=0 ;i<size;i++){
        		 
        		componentNames[i+1]=((ComponentDef)components.get(i)).getIdentifier();
        	}
        	
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
         
       String cat="links";
        // Create a descriptor and set a category
       PropertyDescriptor manages = new ComboBoxPropertyDescriptor(
               Integer.toString(104),
               "manages component " ,componentNames);
       manages.setCategory(cat);
       descriptors.add(manages);
       PropertyDescriptor supports = new ListPropertyDescriptor(
			Integer.toString(105),
			   "supports interfaces "  
			,itfs, allValues,"Select Support Interfaces") ;
    	
       supports.setCategory(cat);
       descriptors.add(supports);
        
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	List Interfaces;
    	int size;
    	String value;
	    switch(Integer.parseInt( (String)id )){
	    
	    case 104:
	    	  if(component!=null)return new Integer(components.indexOf(component)+1);
		        else return new Integer(0);
		    
	    case 105:
	         Interfaces=home.getHomeSupports_itf();
	         size= Interfaces.size();
	         if(size==0)
	         	return "none";
	         value=((AbstractInterfaceDef) Interfaces.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	value=value+","+((AbstractInterfaceDef) Interfaces.get(i)).getIdentifier();
	         }
			 return value;	
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 104:
	        int i=((Integer)value).intValue();
	        if (i==0){
	        	removeManagesConnections();
	        	home.setComponent(null);
	        	component=null;
	        	
	        }
	        else{	
	        	ComponentDef newcomponent=(ComponentDef) components.get(i-1);
	          if(!newcomponent.equals(component)){
	    	     home.setComponent(newcomponent);
	    	     removeManagesConnections();
	    	     component=newcomponent;
	    	     createManagesConnections();
	        }
		}
	    	break;
	    case 105:     
	        List newvalues=((List)value) ;
	        int size = newvalues.size();
	        for (int j=0;j<size;j++){
	          InterfaceDef itf=(InterfaceDef)newvalues.get(j);
	          if(itfs.contains(itf))
	          	itfs.remove(itf);
	          else{
	          	//home.getHomeSupports_itf().add(itf);
	          	createSupportsConnection(itf);	
	          	
	          }
	        }
	        
	        home.getHomeSupports_itf().removeAll(itfs);
	        removeSupportsConnection(itfs);
	        itfs=newvalues;
    		break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }

	/**
	 * @param values2
	 */
	private void removeSupportsConnection(List interfaces) {
	  for (int i =0;i<interfaces.size();i++){	
	 // for(Iterator it =interfaces.iterator();it.hasNext();){
		InterfaceDef itf=(InterfaceDef)interfaces.get(i);
//		List views=mf.getAllViews(root);
    	List views=root.getView();
        	for(int j=0;j<views.size();j++){
        		View view=(View)views.get(j);
        		List connects=view.getConnection();
        		for(int k=0;k<connects.size();k++){
        			ConnectionImpl connect=(ConnectionImpl)connects.get(k);
        			if(((Node)connect.getSource()).getContained().equals(home)&&
        			((Node)connect.getTarget()).getContained().equals(itf)	){
        				DeleteConnectionCommand cmd = new DeleteConnectionCommand(connect);
        				if (cmd.canExecute()) 
        					cmd.execute();
        				 break;
        				//view.getConnection().remove(connect);
        				
        			}
        				 
        				
        		}
        	}
		}
	}

	/**
	 * @param itf
	 */
	private void createSupportsConnection(InterfaceDef itf) {
		List views=mf.getAllViews(root);
    	for(int j=0;j<views.size();j++){
    		View view=(View)views.get(j);
    		Node source=null;
    		Node target=null;
    		List nodes=view.getNode();
    		for(int k=0;k<nodes.size();k++){
    			Node n=(Node)nodes.get(k);
    			if(n.getContained().equals(home))
    				source=n;
    			else if(n.getContained().equals(itf))
    				target=n;
    		}
    		if(source!=null&&target!=null){
    			HomeSupportsConnectCommand command=new HomeSupportsConnectCommand();
    			command.setSource(source);
    			command.setTarget(target);
    			command.setView(view);
    			command.execute();
    		}
       }
  }
		 
		
	

	/**
	 * 
	 */
	private void createManagesConnections() {
		List views=mf.getAllViews(root);
    	for(int j=0;j<views.size();j++){
    		View view=(View)views.get(j);
    		Node source=null;
    		Node target=null;
    		List nodes=view.getNode();
    		for(int k=0;k<nodes.size();k++){
    			Node n=(Node)nodes.get(k);
    			if(n.getContained().equals(home))
    				source=n;
    			else if(n.getContained().equals(component))
    				target=n;
    		}
    		if(source!=null&&target!=null){
    			ComponentHomeConnectCommand command=new ComponentHomeConnectCommand();
    			command.setSource(source);
    			command.setTarget(target);
    			command.setView(view);
    			command.execute();
    		}
      }
  }
		
	

	/**
	 * 
	 */
	private void removeManagesConnections() {
//		List views=mf.getAllViews(root);
    	List views=root.getView();
        for(int j=0;j<views.size();j++){
        		View view=(View)views.get(j);
        		List connects=view.getConnection();
        		for(int k=0;k<connects.size();k++){
        			ConnectionImpl connect=(ConnectionImpl)connects.get(k);
        			if(((Node)connect.getTarget()).getContained().equals(home)&&
        			((Node)connect.getSource()).getContained().equals(component)){
        				DeleteConnectionCommand cmd = new DeleteConnectionCommand(connect);
        				if (cmd.canExecute()) 
        					cmd.execute();
        				 break;
        				//view.getConnection().remove(connect);
        				
        			}
        				//view.getConnection().remove(connect);
        			
        		}
        }
  }
}

 
