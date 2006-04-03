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
import CCMModel.ExternalInstance;
import CCMModel.FinderServiceKind;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class ExternalInstancePropertySource extends ContainedPropertySource {

    protected ExternalInstance externalInstance;
    private String[] values=new String[]{"HOMEFINDER","NAMING","TRADING","UNDEFINED"};
    private List services;
     
   
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ExternalInstancePropertySource(Contained element) {
        	super(element);
        	externalInstance=(ExternalInstance) element;
        	services= new ArrayList();
        	services.add(FinderServiceKind.HOMEFINDER_LITERAL);
        	services.add(FinderServiceKind.NAMING_LITERAL);
        	services.add(FinderServiceKind.TRADING_LITERAL);
        	services.add(FinderServiceKind.UNDEFINED_LITERAL);
        	
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
    	PropertyDescriptor fileName = new TextPropertyDescriptor(Integer.toString(107), "objectRef");
    	fileName.setCategory(cat);
        descriptors.add(fileName);    
        PropertyDescriptor location = new TextPropertyDescriptor(Integer.toString(108), "regName");
    	location.setCategory(cat);
        descriptors.add(location);
        PropertyDescriptor action = new ComboBoxPropertyDescriptor(Integer.toString(109), "service",values);
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
	    	return externalInstance.getObjectRef();
	   
	    case 108:
	    	return externalInstance.getRegName();
	    case 109:
	    	return new Integer(services.indexOf(externalInstance.getService()));
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 107:
	       externalInstance.setObjectRef((String)value); 
	    	break;
	    case 108:
		   externalInstance.setRegName((String)value); 
		   break;
	    case 109:
	    	int i=((Integer)value).intValue();
		    externalInstance.setService((FinderServiceKind)services.get(i)); 
		    break;
		    	
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 
 
