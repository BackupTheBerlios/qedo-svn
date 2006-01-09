package ccm.property;


import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.ComponentImplDef;
import CCMModel.Contained;
import CCMModel.HomeImplDef;
import CCMModel.ModuleDef;
import ccm.model.CCMModelManager;
import ccm.model.ModelFactory;

/**
* @author siegercn
*
*/
 
public class ComponentImplPropertySource extends ContainedPropertySource {

	    
	    ComponentImplDef abstObj;
	    //private HomeDef home;
	     
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
	    public ComponentImplPropertySource( Contained element) {
	        	super(element);
	        	//HomeImplDef.
	        	abstObj=(ComponentImplDef) element;
	        	 
	        	 
	        	 
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
	                Integer.toString(CCMModelPackage.HOME_IMPL_DEF__COMPONENT_IMPL),
	                "manages by home_impls"  );
	        managesrelation.setCategory(cat);
	        descriptors.add(managesrelation);
	        
	        PropertyDescriptor typerelation = new  PropertyDescriptor(
	                Integer.toString(CCMModelPackage.HOME_IMPL_DEF__HOME),
	                "implements home"  );
	        typerelation.setCategory(cat);
	        descriptors.add(typerelation);
	         
	        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
	        return propertyDescriptors;
	    }
	    /**
	     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
	     */
	    public Object getPropertyValue(Object id) {
		    switch(Integer.parseInt( (String)id )){
		    case CCMModelPackage.HOME_IMPL_DEF__COMPONENT_IMPL:
		         List homeImpls=abstObj.getHomeImpl();
		         int size=homeImpls.size();
		         if(size==0)
		         	return "none";
		         String homeis=((HomeImplDef)homeImpls.get(0)).getIdentifier();
		         for (int i=1;i<size;i++){
		         	homeis=homeis+","+((HomeImplDef)homeImpls.get(i)).getIdentifier();
		         }
				 return homeis;	
		    case CCMModelPackage.HOME_IMPL_DEF__HOME:
		    	return abstObj.getComponent().getIdentifier();
		    }
	        return super.getPropertyValue(id);
	    }
	    
	  
	  
	}
	 
 