package ccm.property;

import java.util.Collection;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.Contained;
import CCMModel.ProcessCollocation;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class ProcessCollocationPropertySource extends ContainedPropertySource {

    protected ProcessCollocation abstObj;
   
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ProcessCollocationPropertySource(Contained element) {
        	super(element);
        	abstObj=(ProcessCollocation) element;
        	 
        	
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
    	PropertyDescriptor fileName = new TextPropertyDescriptor(Integer.toString(100), "cardinality");
    	fileName.setCategory(cat);
        descriptors.add(fileName);    
        PropertyDescriptor location = new TextPropertyDescriptor(Integer.toString(101), "destination");
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
	       return  (new Long(abstObj.getCardinality())).toString();
	   
	    case 101:
	    	 return abstObj.getDestination();
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	    	long v=0;
	    	try{
				v= Long.parseLong((String)value);
			}
			catch(NumberFormatException e){
				//MessageDialog.openError(Shell, "Error",  " the type of cardinality is Integer " ); 
			}
	        abstObj.setCardinality(v); 
	        break;
	    case 101:
		       abstObj.setDestination((String)value); 
		    	break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
  
