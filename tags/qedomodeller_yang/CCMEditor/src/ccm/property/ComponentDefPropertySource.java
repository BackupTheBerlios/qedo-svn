package ccm.property;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

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
import ccm.commands.connect.ComponentSupportsConnectCommand;
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
public class ComponentDefPropertySource extends ContainedPropertySource  {

    
	private ComponentDef component;
	private String[]homeNames;
    private List homeList;
    private List values;
    private List allValues;
    private String[]supportItfNames;
    private ModelFactory mf=new ModelFactory();
    // private CCMModelFactory factory =CCMModelManager.getFactory();
    private ModuleDef root;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ComponentDefPropertySource(Contained element) {
        	super(element);
        	component=(ComponentDef) element;
        	 
        	values=new ArrayList(component.getComponentSupports_itf());
        	 
        	root= mf.getRootModule(component);
        	//components= mf.getAllContained(root,ComponentDef.class);
        	allValues= mf.getAllContained(root,InterfaceDef.class);
        	 
        	 
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
       PropertyDescriptor managesrelation = new  PropertyDescriptor(
            Integer.toString(104),
            "manages by homes "  );
       managesrelation.setCategory(cat);
       descriptors.add(managesrelation);
       
       PropertyDescriptor supports = new ListPropertyDescriptor(
			Integer.toString(105),
			"supports intefaces " 
			,values, allValues,"Select Support Interfaces") ;
    	
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
	    	List homes=component.getHomes();
	    	     size=homes.size();
		         if(size==0)
		         	return "none";
		         String homeis=((HomeDef)homes.get(0)).getIdentifier();
		         for (int i=1;i<size;i++){
		         	homeis=homeis+","+((HomeDef)homes.get(i)).getIdentifier();
		         }
				 return homeis;	
		    
	    case 105:
	         Interfaces=component.getComponentSupports_itf();
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
	    
	    case 105:     
	        List newvalues=((List)value) ;
	        int size = newvalues.size();
	        for (int j=0;j<size;j++){
	          InterfaceDef itf=(InterfaceDef)newvalues.get(j);
	          if(values.contains(itf))
	          	values.remove(itf);
	          else{
	          	//component.getHomeSupports_itf().add(itf);
	          	createSupportsConnection(itf);	
	          	
	          }
	        }
	        component.getComponentSupports_itf().removeAll(values);
	        removeSupportsConnection(values);
	        values=newvalues;
    		break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }

	/**
	 * @param values2
	 */
	private void removeSupportsConnection(List interfaces) {
	  for(Iterator it =interfaces.iterator();it.hasNext();){
		InterfaceDef itf=(InterfaceDef)it.next();
//		List views=mf.getAllViews(root);
    	List views=root.getView();
        	for(int j=0;j<views.size();j++){
        		View view=(View)views.get(j);
        		List connects=view.getConnection();
        		for(int k=0;k<connects.size();k++){
        			ConnectionImpl connect=(ConnectionImpl)connects.get(k);
        			if(((Node)connect.getSource()).getContained().equals(component)&&
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
    			if(n.getContained().equals(component))
    				source=n;
    			else if(n.getContained().equals(itf))
    				target=n;
    		}
    		if(source!=null&&target!=null){
    			ComponentSupportsConnectCommand command=new ComponentSupportsConnectCommand();
    			command.setSource(source);
    			command.setTarget(target);
    			command.setView(view);
    			command.execute();
    		}
       }
   }
		 	 
}

 
 