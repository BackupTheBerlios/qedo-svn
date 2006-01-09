package ccm.property;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.Contained;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.UsesDef;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.connect.UsesItfConnectCommand;
import ccm.commands.delete.visual.DeleteConnectionCommand;
import ccm.model.ModelFactory;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class ReceptaclePropertySource extends ContainedPropertySource  {

    
	private UsesDef abstObj;
	 
    private List values= new ArrayList();
    private String[] mutipelvalues=new String[]{"false","true"};
    
    private ModelFactory mf=new ModelFactory();
    // private CCMModelFactory factory =CCMModelManager.getFactory();
    private ModuleDef root;
    private String[]interfacesNames;
    private List interfaces;
    private InterfaceDef itf;
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ReceptaclePropertySource(Contained element) {
        	super(element);
        	abstObj=(UsesDef) element;
        	itf=abstObj.getInterface();
        	 
        	root= mf.getRootModule(abstObj.getComp());
        	 
        	interfaces= mf.getAllContained(root,InterfaceDef.class);
        	int size=interfaces.size();
        	//homeImpls=new HomeImplDef[size];
        	interfacesNames= new String[size+1];
        	interfacesNames[0]="none";
        	
        	for (int i=0 ;i<size;i++){
        		//homeImpls[i]=(HomeImplDef)homeImplList.get(i);
        		interfacesNames[i+1]=((InterfaceDef)interfaces.get(i)).getIdentifier();
        		 
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
         String cat="local";
    		//if(object!=null)cat=cat+ object.eClass().getName();
         
          // Create a descriptor and set a category
         PropertyDescriptor isAbstract = new ComboBoxPropertyDescriptor(Integer.toString(100), "is multiple",mutipelvalues);
         isAbstract.setCategory(cat);
         descriptors.add(isAbstract); 
        cat="links";
      
       PropertyDescriptor  relation = new ComboBoxPropertyDescriptor(
            Integer.toString(105),
            "uses_interface"  ,interfacesNames);
    	
       relation.setCategory(cat);
       descriptors.add(relation);
        
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
	    case 100:
	        if(abstObj.isMultipleItf())return new Integer(1);
	        else return new Integer(0);
		    
	    case 105:
	    	  if(itf!=null)return new Integer(interfaces.indexOf(itf)+1);
		        else return new Integer(0);
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
    	int i;
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	        i=((Integer)value).intValue();
	    	if(i==0)abstObj.setMultipleItf(false);
	    	else abstObj.setMultipleItf(true);
	    	notifyNode();
	    	break;
	    case 105:     
	    	i=((Integer)value).intValue();
		    if (i==0){
		        	removeConnection();
		        	abstObj.setInterface(null);
		        	itf=null;
		        	
		        }
		        else{	
		          InterfaceDef newitf=(InterfaceDef) interfaces.get(i-1);
		          if(!newitf.equals(itf)){
		    	     abstObj.setInterface(newitf);
		    	     removeConnection();
		    	     itf=newitf;
		    	     createConnection();
		        }
			}
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }

	/**
	 * @param values2
	 */
	private void removeConnection() {
	  
//		List views=mf.getAllViews(root);
    	List views=root.getView();
        	for(int j=0;j<views.size();j++){
        		View view=(View)views.get(j);
        		List connects=view.getConnection();
        		for(int k=0;k<connects.size();k++){
        			ConnectionImpl connect=(ConnectionImpl)connects.get(k);
        			if(((Node)connect.getSource()).getContained().equals(abstObj)&&
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

	/**
	 * @param itf
	 */
	private void createConnection() {
		List views=mf.getAllViews(root);
    	for(int j=0;j<views.size();j++){
    		View view=(View)views.get(j);
    		Node source=null;
    		Node target=null;
    		List nodes=view.getNode();
    		for(int k=0;k<nodes.size();k++){
    			Node n=(Node)nodes.get(k);
    			if(n.getContained().equals(abstObj))
    				source=n;
    			else if(n.getContained().equals(itf))
    				target=n;
    		}
    		if(source!=null&&target!=null){
    			UsesItfConnectCommand command=new UsesItfConnectCommand();
    			command.setSource(source);
    			command.setTarget(target);
    			command.setView(view);
    			command.execute();
    		}
       }
  }
		 
		
}