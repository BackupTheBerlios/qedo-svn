package ccm.property;

 
import java.util.Collection;
import java.util.List;
import java.util.Vector;
import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.ComponentImplDef;
import CCMModel.Contained;
import CCMModel.HomeImplDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl; 
import ccm.commands.connect.CompositionConnectHomeImplCommand;
import ccm.commands.connect.ManagesConnectCommand;
import ccm.commands.delete.visual.DeleteConnectionCommand; 
import ccm.model.CCMModelManager;
import ccm.model.ModelFactory;
 
/**
 * @author siegercn
 *
 */
  
public class HomeImplPropertySource extends ContainedPropertySource {

	    
	    HomeImplDef abstObj;
	    //private HomeDef home;
	    private ComponentImplDef componentImpl; 
	    private ModelFactory mf=new ModelFactory();
	    private CCMModelFactory factory =CCMModelManager.getFactory();
	    private ModuleDef root;
	   
	    private List componentImpls;
	    private String[]componentImplNames;
	    //private List componentImpls;
	     
	    private boolean isSet=false;
	    
		 /**
	     * Creates a new ButtonElementPropertySource.
	     *
	     * @param element  the element whose properties this instance represents
	     */
	    public HomeImplPropertySource( Contained element) {
	        	super(element);
	        	//HomeImplDef.
	        	abstObj=(HomeImplDef) element;
	        	componentImpl=abstObj.getComponentImpl();
	        	root= mf.getRootModule(abstObj);
	        	componentImpls= mf.getAllContained(root,ComponentImplDef.class);
	        	//homeImpls=componentImpls.toArray();
	        	int size=componentImpls.size();
	        	//homeImpls=new HomeImplDef[size];
	        	componentImplNames= new String[size+1];
	        	componentImplNames[0]="none";
	        	
	        	for (int i=0 ;i<size;i++){
	        		//homeImpls[i]=(HomeImplDef)componentImpls.get(i);
	        		componentImplNames[i+1]=((ComponentImplDef)componentImpls.get(i)).getIdentifier();
	        		 
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
	         // Create a descriptor and set a category
	        PropertyDescriptor typerelation = new  PropertyDescriptor(
	                Integer.toString(CCMModelPackage.HOME_IMPL_DEF__HOME),
	                "implements home " );
	        typerelation.setCategory(cat);
	        descriptors.add(typerelation);
	        PropertyDescriptor managesrelation = new ComboBoxPropertyDescriptor(
	                Integer.toString(CCMModelPackage.HOME_IMPL_DEF__COMPONENT_IMPL),
	                "manages component_impl" ,componentImplNames);
	        managesrelation.setCategory(cat);
	        descriptors.add(managesrelation);
	         
	        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
	        return propertyDescriptors;
	    }
	    /**
	     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
	     */
	    public Object getPropertyValue(Object id) {
		    switch(Integer.parseInt( (String)id )){
		    case CCMModelPackage.HOME_IMPL_DEF__COMPONENT_IMPL:
		        if(componentImpl!=null)return new Integer(componentImpls.indexOf(componentImpl)+1);
		        else return new Integer(0);
		    case CCMModelPackage.HOME_IMPL_DEF__HOME:
		    	return abstObj.getHome().getIdentifier();
		    }
	        return super.getPropertyValue(id);
	    }
	    
	  
	    /**
	     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
	     */
	    
	    public void setPropertyValue(Object id, Object value) {
		    switch(Integer.parseInt( (String)id )){
		    case CCMModelPackage.HOME_IMPL_DEF__COMPONENT_IMPL:
		        int i=((Integer)value).intValue();
		        if (i==0){
		        	removeConnections();
		        	abstObj.setComponentImpl(null);
		        	componentImpl=null;
		        }
		        else{	
		          ComponentImplDef newcomponentImpl=(ComponentImplDef) componentImpls.get(i-1);
		          if(!newcomponentImpl.equals(componentImpl)){
		    	     abstObj.setComponentImpl(newcomponentImpl);
		    	     removeConnections();
		    	     componentImpl=newcomponentImpl;
		    	     createConnections();
		        }
			}
		    	break;
		 
		    	 
	    	default:
	    	    super.setPropertyValue(id, value);
		    }
	    } 
		    
	    private void removeConnections(){
	    	List views=mf.getAllViews(root);
	        	for(int j=0;j<views.size();j++){
	        		View view=(View)views.get(j);
	        		List connects=view.getConnection();
	        		for(int k=0;k<connects.size();k++){
	        			ConnectionImpl connect=(ConnectionImpl)connects.get(k);
	        			if(((Node)connect.getSource()).getContained().equals(abstObj)&&
	        			((Node)connect.getTarget()).getContained().equals(componentImpl)	){
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
	        			else if(n.getContained().equals(componentImpl))
	        				target=n;
	        		}
	        		if(source!=null&&target!=null){
	        			ManagesConnectCommand command=new ManagesConnectCommand();
	        			command.setSource(source);
	        			command.setTarget(target);
	        			command.setView(view);
	        			command.execute();
	        		}
		    }
		  }
	}
	 
