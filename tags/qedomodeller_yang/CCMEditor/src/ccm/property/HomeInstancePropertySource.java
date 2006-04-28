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
import CCMModel.FinderServiceKind;
import CCMModel.HomeInstantiation;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class HomeInstancePropertySource extends ContainedPropertySource {

    protected HomeInstantiation homeInstance;
    private String[] values=new String[]{"HOMEFINDER","NAMING","TRADING","UNDEFINED"};
    private List services;
     
   
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public HomeInstancePropertySource(Contained element) {
        	super(element);
        	homeInstance=(HomeInstantiation) element;
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
    	PropertyDescriptor cardinality = new TextPropertyDescriptor(Integer.toString(107), "cardinality");
    	cardinality.setCategory(cat);
        descriptors.add(cardinality);
        PropertyDescriptor location = new TextPropertyDescriptor(Integer.toString(108), "regName");
    	location.setCategory(cat);
        descriptors.add(location);
        PropertyDescriptor action = new ComboBoxPropertyDescriptor(Integer.toString(109), "service",values);
        action.setCategory(cat);
        descriptors.add(action);
        cat="links";
        // Create a descriptor and set a category
       
       PropertyDescriptor derived = new  PropertyDescriptor(
            Integer.toString(110),
               "implemented by implementation " );
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
	    case 110:
	    	return homeInstance.getDeploymentUnit().getIdentifier();
	    case 107:
		       return  (new Long(homeInstance.getCardinality())).toString();
	    case 108:
	    	return homeInstance.getRegName();
	    case 109:
	    	return new Integer(services.indexOf(homeInstance.getService()));
	    
	    }
        return super.getPropertyValue(id);
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 107:
	    	int v=0;
	    	try{
				v= Integer.parseInt((String)value);
			}
			catch(NumberFormatException e){
				//MessageDialog.openError(Shell, "Error",  " the type of cardinality is Integer " ); 
			}
	        homeInstance.setCardinality(v); 
	        break;
	    case 108:
		   homeInstance.setRegName((String)value); 
		   break;
	    case 109:
	    	int i=((Integer)value).intValue();
		    homeInstance.setService((FinderServiceKind)services.get(i)); 
		    break;
		    	
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
 
