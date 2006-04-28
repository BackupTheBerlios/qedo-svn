package ccm.property;

 
import java.util.Collection;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.ComponentInstantiation;
import CCMModel.Contained;


/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class ComponentInstancePropertySource extends ContainedPropertySource {

    protected ComponentInstantiation register;
     
     
   
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ComponentInstancePropertySource(Contained element) {
        	super(element);
        	register=(ComponentInstantiation) element;
        	 
        	
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
    	PropertyDescriptor cardinality = new TextPropertyDescriptor(Integer.toString(107), "cardinality");
    	cardinality.setCategory(cat);
        descriptors.add(cardinality);
        PropertyDescriptor location = new TextPropertyDescriptor(Integer.toString(108), "startOder");
    	location.setCategory(cat);
        descriptors.add(location);
        
        cat="links";
        // Create a descriptor and set a category
       
       PropertyDescriptor derived = new  PropertyDescriptor(
            Integer.toString(109),
               "instance of type" );
       derived.setCategory(cat);
       descriptors.add(derived);
        
        
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	 
    	String value;
	    switch(Integer.parseInt( (String)id )){
	    
	    case 107:
		       return  (new Integer(register.getCardinality())).toString();
	    case 108:
	    	return  (new Integer(register.getStartOrder())).toString();
	    case 109:
	    	if(register.getType()!=null)
	    		return register.getType().getIdentifier();
	    	else
	    		return "";
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
    	int v=0;
	    switch(Integer.parseInt( (String)id )){
	    case 107:
	    	
	    	try{
				v= Integer.parseInt((String)value);
			}
			catch(NumberFormatException e){
				//MessageDialog.openError(Shell, "Error",  " the type of cardinality is Integer " ); 
			}
	        register.setCardinality(v); 
	        break;
	    case 108:
	    	
	    	try{
				v= Integer.parseInt((String)value);
			}
			catch(NumberFormatException e){
				//MessageDialog.openError(Shell, "Error",  " the type of cardinality is Integer " ); 
			}
	        register.setStartOrder(v); 
	        break;
	   
		    	
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
  
