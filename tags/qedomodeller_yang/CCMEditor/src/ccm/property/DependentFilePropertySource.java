package ccm.property;

import java.util.Collection;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.Aktionkind;
import CCMModel.Contained;
import CCMModel.DependentFile;
 

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class DependentFilePropertySource extends FilePropertySource {

    protected DependentFile dependentFile;
    private String[] values=new String[]{"ASSERT","INSTALL"};
 //   private Aktionkind[]actions= new Aktionkind[]{Aktionkind.ASSERT_LITERAL,Aktionkind.INSTALL_LITERAL};
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public DependentFilePropertySource(Contained element) {
        	super(element);
        	dependentFile=(DependentFile) element;
        	 
        	
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
    	  PropertyDescriptor action = new ComboBoxPropertyDescriptor(Integer.toString(102), "action",values);
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
	    
	    case 102:
	        if(dependentFile.getAction()==Aktionkind.ASSERT_LITERAL)return new Integer(0);
	        else return new Integer(1);
	    
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 102:     
	    	int i=((Integer)value).intValue();
	    	if(i==0)dependentFile.setAction(Aktionkind.ASSERT_LITERAL);
	    	else dependentFile.setAction(Aktionkind.INSTALL_LITERAL);
	    	break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 
  
