
package ccm.property;

 
import java.util.Collection;
import java.util.List;
import java.util.Vector;
import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor; 
import CCMModel.CCMModelPackage;
import CCMModel.Contained; 
import CCMModel.HomeImplDef;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.ProvidesDef;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.connect.ProvidesItfConnectCommand;
import ccm.commands.delete.visual.DeleteConnectionCommand;
import ccm.model.ModelFactory;
 

/**
 * @author siegercn
 *
 */
public class FacetPropertySource extends ContainedPropertySource {

    private ProvidesDef abstObj;
    private InterfaceDef itf;
    private ModelFactory mf=new ModelFactory();
   // private CCMModelFactory factory =CCMModelManager.getFactory();
    private ModuleDef root;
    
   // private HomeImplDef[]homeImpls;
    private String[]interfacesNames;
    private List interfaces;
     
    private boolean isSet=false;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public FacetPropertySource( Contained element) {
        	super(element);
        	//HomeImplDef.
        	abstObj=(ProvidesDef) element;
        	itf=abstObj.getInterface();
        	root= mf.getRootModule(abstObj.getComp());
        	interfaces= mf.getAllContained(root,InterfaceDef.class);
        	//homeImpls=homeImplList.toArray();
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
       	String cat="links";
         // Create a descriptor and set a category
        PropertyDescriptor  relation = new ComboBoxPropertyDescriptor(
                Integer.toString(100),
                "provides_interface " ,interfacesNames);
        relation.setCategory(cat);
        descriptors.add( relation);
         
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	        if(itf!=null)return new Integer(interfaces.indexOf(itf)+1);
	        else return new Integer(0);
	    }
        return super.getPropertyValue(id);
    }
    
  
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	        int i=((Integer)value).intValue();
	        if (i==0){
	        	removeConnections();
	        	abstObj.setInterface(null);
	        	itf=null;
	        	
	        }
	        else{	
	          InterfaceDef newitf=(InterfaceDef) interfaces.get(i-1);
	          if(!newitf.equals(itf)){
	    	     abstObj.setInterface(newitf);
	    	     removeConnections();
	    	     itf=newitf;
	    	     createConnections();
	        }
		}
	    	break;
	 
	    	 
    	default:
    	    super.setPropertyValue(id, value);
	    }
    } 
	    
    private void removeConnections(){
    	//List views=mf.getAllViews(root);
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
        				//view.getConnection().remove(connect);
        			
        			   
        				
        		}
        	}
        		
    }
	private void createConnections(){
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
        			ProvidesItfConnectCommand command=new ProvidesItfConnectCommand();
        			command.setSource(source);
        			command.setTarget(target);
        			command.setView(view);
        			command.execute();
        		}
	    }
	  }
}
 