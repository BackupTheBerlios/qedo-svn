package ccm.property;

import java.util.Collection;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.Contained;
import CCMModel.ContainedFile;
 

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class ContainedFilePropertySource extends FilePropertySource {

    protected ContainedFile containedFile;
   
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ContainedFilePropertySource(Contained element) {
        	super(element);
        	containedFile=(ContainedFile) element;
        	 
        	
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
    	PropertyDescriptor fileName = new TextPropertyDescriptor(Integer.toString(102), "codeType");
    	fileName.setCategory(cat);
        descriptors.add(fileName);    
        PropertyDescriptor location = new TextPropertyDescriptor(Integer.toString(103), "entryPoint");
    	location.setCategory(cat);
        descriptors.add(location);
        PropertyDescriptor usage = new TextPropertyDescriptor(Integer.toString(104), "entryPointUsage");
    	usage.setCategory(cat);
        descriptors.add(usage);
        
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	 
    	String value;
	    switch(Integer.parseInt( (String)id )){
	    case 102:
	       return containedFile.getCodeType();
	   
	    case 103:
	    	 return containedFile.getEntryPoint();
	    case 104:
	    	 return containedFile.getUsage();
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 102:
	       containedFile.setCodeType((String)value); 
	    	break;
	    case 103:
		       containedFile.setEntryPoint((String)value); 
		    	break;
	    case 104:
		       containedFile.setUsage((String)value); 
		    	break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 
 