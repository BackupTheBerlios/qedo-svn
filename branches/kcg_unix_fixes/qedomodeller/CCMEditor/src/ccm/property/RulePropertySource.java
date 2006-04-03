package ccm.property;

import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.Contained;
import CCMModel.Rule;
 
 

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class RulePropertySource extends ContainedPropertySource {

    private Rule abstObj;
  
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public RulePropertySource(Contained element) {
        	super(element);
        	abstObj=(Rule) element;
        	
        	
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
   		
    	PropertyDescriptor licensekey = new TextPropertyDescriptor(Integer.toString(100), "name");
    	licensekey.setCategory(cat);
        descriptors.add(licensekey);
        
        PropertyDescriptor licenseTxtRef = new TextPropertyDescriptor(Integer.toString(101), "condition");
        licenseTxtRef.setCategory(cat);
        descriptors.add(licenseTxtRef);
        PropertyDescriptor tiltel = new TextPropertyDescriptor(Integer.toString(102), "language");
        tiltel.setCategory(cat);
      	descriptors.add(tiltel);
      	PropertyDescriptor autor = new TextPropertyDescriptor(Integer.toString(103), "action");
      	autor.setCategory(cat);
      	descriptors.add(autor);
      	
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
	       return abstObj.getName();
	    case 101:
	    	 return abstObj.getCondition();   
	   
	    case 102:
	    	 return abstObj.getLanguage();
	    case 103:
	    	 return abstObj.getAction();
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	       abstObj.setName((String)value);
	    	 
	    	break;
	    case 101:     
	    	 abstObj.setCondition((String)value);
    		break;
	    case 102:     
	    	 abstObj.setLanguage((String)value);
    		break;
	    case 103:     
	    	 abstObj.setAction((String)value);
   		break;
	     
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 
 