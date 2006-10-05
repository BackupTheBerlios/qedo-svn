
package ccm.property;

 
import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.CCMModelPackage;
import CCMModel.ComponentCategory;
import CCMModel.Composition;
import CCMModel.Contained;
import CCMModel.HomeImplDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.connect.CompositionConnectHomeImplCommand;
import ccm.commands.delete.visual.DeleteConnectionCommand;
import ccm.model.ModelFactory;

/**
 * @author siegercn
 *
 */
public class CompositionPropertySource extends ContainedPropertySource {

    private Composition abstObj;
    private HomeImplDef homeImpl;
    private ComponentCategory category;
    private ModelFactory mf=new ModelFactory();
   // private CCMModerylFactory factory =CCMModelManager.getFactory();
    private ModuleDef root;
    
   // private HomeImplDef[]homeImpls;
    private String[]homeImplNames;
    private List homeImplList;
    private String[]categoryNames={"PROCESS","SESSION","ENTITY","SERVICE", "EXTENSION"};
   // private List category=new util.ArrayList( {ComponentCategory.PROCESS_LITERAL,
   // 		ComponentCategory.SESSION_LITERAL,ComponentCategory.ENTITY_LITERAL,ComponentCategory.SERVICE_LITERAL});
     
    private boolean isSet=false;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public CompositionPropertySource( Contained element) {
        	super(element);
        	//HomeImplDef.
        	abstObj=(Composition) element;
        	homeImpl=abstObj.getHomeImpl();
        	category= abstObj.getCategory();
        	root= mf.getRootModule(abstObj);
        	 homeImplList= mf.getAllContained(root,HomeImplDef.class);
        	//homeImpls=homeImplList.toArray();
        	int size=homeImplList.size();
        	//homeImpls=new HomeImplDef[size];
        	homeImplNames= new String[size+1];
        	homeImplNames[0]="none";
        	
        	for (int i=0 ;i<size;i++){
        		//homeImpls[i]=(HomeImplDef)homeImplList.get(i);
        		homeImplNames[i+1]=((HomeImplDef)homeImplList.get(i)).getIdentifier();
        		 
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
        PropertyDescriptor catagory = new ComboBoxPropertyDescriptor(
                Integer.toString(CCMModelPackage.COMPOSITION__CATEGORY),
                "catogory" ,categoryNames);
        catagory.setCategory(cat);
        descriptors.add(catagory);
        cat="links";
         // Create a descriptor and set a category
        PropertyDescriptor compositionrelation = new ComboBoxPropertyDescriptor(
                Integer.toString(CCMModelPackage.COMPOSITION__HOME_IMPL),
                "composits home_impl" ,homeImplNames);
        compositionrelation.setCategory(cat);
        descriptors.add(compositionrelation);
         
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.COMPOSITION__HOME_IMPL:
	        if(homeImpl!=null)return new Integer(homeImplList.indexOf(homeImpl)+1);
	        else return new Integer(0);
	    case CCMModelPackage.COMPOSITION__CATEGORY:
	        if(category==ComponentCategory.PROCESS_LITERAL)return new Integer(0);
	        else if(category==ComponentCategory.SESSION_LITERAL)return new Integer(1);
	        else if(category==ComponentCategory.ENTITY_LITERAL)return new Integer(2);
	        else  return new Integer(3);
	    
	    }
        return super.getPropertyValue(id);
    }
    
  
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.COMPOSITION__HOME_IMPL:
	        int i=((Integer)value).intValue();
	        if (i==0){
	        	removeConnections();
	        	abstObj.setHomeImpl(null);
	        	homeImpl=null;
	        	
	        }
	        else{	
	          HomeImplDef newHomeImpl=(HomeImplDef) homeImplList.get(i-1);
	          if(!newHomeImpl.equals(homeImpl)){
	    	     abstObj.setHomeImpl(newHomeImpl);
	    	     removeConnections();
	    	     homeImpl=newHomeImpl;
	    	     createConnections();
	        }
		}
	    	break;
	 
	    case CCMModelPackage.COMPOSITION__CATEGORY:
	        	i=((Integer)value).intValue();	
	    		if (i==0&&category!=ComponentCategory.PROCESS_LITERAL){
	    			category= ComponentCategory.PROCESS_LITERAL;
	    			abstObj.setCategory(ComponentCategory.PROCESS_LITERAL);
	    			notifyNode();
	    		}
	    		if (i==1&&category!=ComponentCategory.SESSION_LITERAL){
	    			category= ComponentCategory.SESSION_LITERAL;
	    			abstObj.setCategory(ComponentCategory.SESSION_LITERAL);
	    			notifyNode();
	    		}
	    		if (i==2&&category!=ComponentCategory.ENTITY_LITERAL){
	    			category= ComponentCategory.ENTITY_LITERAL;
	    			abstObj.setCategory(ComponentCategory.ENTITY_LITERAL);
	    			notifyNode();
	    		}
	    		if (i==3&&category!=ComponentCategory.SERVICE_LITERAL){
	    			category= ComponentCategory.SERVICE_LITERAL;
	    			abstObj.setCategory(ComponentCategory.SERVICE_LITERAL);
	    			notifyNode();
	    		}
	    		if (i==4&&category!=ComponentCategory.EXTENSION_LITERAL){
	    			category= ComponentCategory.EXTENSION_LITERAL;
	    			abstObj.setCategory(ComponentCategory.EXTENSION_LITERAL);
	    			notifyNode();
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
        			((Node)connect.getTarget()).getContained().equals(homeImpl)	){
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
        			else if(n.getContained().equals(homeImpl))
        				target=n;
        		}
        		if(source!=null&&target!=null){
        			CompositionConnectHomeImplCommand command=new CompositionConnectHomeImplCommand();
        			command.setSource(source);
        			command.setTarget(target);
        			command.setView(view);
        			command.execute();
        		}
	    }
	  }
}
 
