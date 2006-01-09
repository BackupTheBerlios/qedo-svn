package ccm.property;

import java.util.Collection;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.Contained;
import CCMModel.Deploymentrequirement;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class DeploymentRequirementPropertySource extends ContainedPropertySource {

    protected Deploymentrequirement abstObj;
   
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public DeploymentRequirementPropertySource(Contained element) {
        	super(element);
        	abstObj=(Deploymentrequirement) element;
        	 
        	
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
    	PropertyDescriptor fileName = new TextPropertyDescriptor(Integer.toString(100), "kind");
    	fileName.setCategory(cat);
        descriptors.add(fileName);    
        PropertyDescriptor location = new TextPropertyDescriptor(Integer.toString(101), "reqVersion");
    	location.setCategory(cat);
        descriptors.add(location);
        
        
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	 
    	String value;
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	       return abstObj.getKind();
	   
	    case 101:
	    	 return abstObj.getReqVersion();
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	       abstObj.setKind((String)value); 
	    	break;
	    case 101:
		       abstObj.setReqVersion((String)value); 
		    	break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 