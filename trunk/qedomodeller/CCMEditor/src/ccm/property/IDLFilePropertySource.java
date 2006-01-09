package ccm.property;

import java.util.Collection;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.IDLFile;
 

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class IDLFilePropertySource extends FilePropertySource {

    protected IDLFile idlFile;
    
 //   private Aktionkind[]actions= new Aktionkind[]{Aktionkind.ASSERT_LITERAL,Aktionkind.INSTALL_LITERAL};
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public IDLFilePropertySource(Contained element) {
        	super(element);
        	idlFile=(IDLFile) element;
        	 
        	
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
   		PropertyDescriptor action =  new TextPropertyDescriptor(Integer.toString(100), "location");
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
	    
	    case 100:
	        idlFile.getLocation(); 
	    
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:     
	    	 
	    	idlFile.setLocation((String)value);
	    	break;
	    case CCMModelPackage.CONTAINED__IDENTIFIER:
	    	idlFile.setName((String)value);
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 
 
