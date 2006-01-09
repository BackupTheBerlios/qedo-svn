package ccm.property;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.Contained;
import CCMModel.ElementName;
import CCMModel.Property;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class PropertyPropertySource extends ContainedPropertySource {

    protected Property property;
    private String[] values=new String[]{"SEQUENCE","SIMPLE","STRUCT","VALUETYPE"};
    private List elementNames;
     
   
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public PropertyPropertySource(Contained element) {
        	super(element);
        	property=(Property) element;
        	elementNames= new ArrayList();
        	elementNames.add(ElementName.SEQUENCE_EL_LITERAL);
        	elementNames.add(ElementName.SIMPLE_EL_LITERAL);
        	elementNames.add(ElementName.STRUCT_EL_LITERAL);
        	elementNames.add(ElementName.VALUETYPE_EL_LITERAL);
        	
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
    	PropertyDescriptor fileName = new TextPropertyDescriptor(Integer.toString(107), "value");
    	fileName.setCategory(cat);
        descriptors.add(fileName);    
        PropertyDescriptor location = new TextPropertyDescriptor(Integer.toString(108), "type");
    	location.setCategory(cat);
        descriptors.add(location);
        PropertyDescriptor action = new ComboBoxPropertyDescriptor(Integer.toString(109), "el_name",values);
        action.setCategory(cat);
        descriptors.add(action);
        
        
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
	    	return property.getValue();
	   
	    case 108:
	    	return property.getType();
	    case 109:
	    	return new Integer(elementNames.indexOf(property.getEl_name()));
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 107:
	       property.setValue((String)value); 
	    	break;
	    case 108:
		   property.setType((String)value); 
		   break;
	    case 109:
	    	int i=((Integer)value).intValue();
		    property.setEl_name((ElementName)elementNames.get(i)); 
		    break;
		    	
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 