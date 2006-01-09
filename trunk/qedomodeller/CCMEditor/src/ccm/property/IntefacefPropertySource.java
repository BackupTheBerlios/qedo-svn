 
package ccm.property;

import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.Contained;
import CCMModel.InterfaceDef;
 

/**
 * 
 * @author siegercn
 *
 */
public class IntefacefPropertySource extends AbstractIntefacefPropertySource {

    
 
    
    protected InterfaceDef itf;
    
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public IntefacefPropertySource(Contained element) {
        	super(element);
        	itf=( InterfaceDef) element;
        	  
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
        
        String cat="links";
        // Create a descriptor and set a category
        PropertyDescriptor supportsBycompents = new  PropertyDescriptor(
                Integer.toString(104),
                   "supports by components " );
        supportsBycompents.setCategory(cat);
           descriptors.add(supportsBycompents);
        PropertyDescriptor supportsByhomes = new  PropertyDescriptor(
                Integer.toString(105),
				 "supports by homes " );
        supportsByhomes.setCategory(cat);
           descriptors.add(supportsByhomes);
           PropertyDescriptor supportsByvalues = new  PropertyDescriptor(
                Integer.toString(106),
				 "supports by values " );
           supportsByvalues.setCategory(cat);
           descriptors.add(supportsByvalues);
           PropertyDescriptor uses = new  PropertyDescriptor(
                Integer.toString(107),
                   "uses by " );
           uses.setCategory(cat);
           descriptors.add(uses);
       PropertyDescriptor provides = new  PropertyDescriptor(
            Integer.toString(108),
               "provides by " );
       provides.setCategory(cat);
       descriptors.add(provides);
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	List values;
    	int size;
    	String value;
	    switch(Integer.parseInt( (String)id )){
	     
	    case 104:
	         values=itf.getComponents();
	         size= values.size();
	         if(size==0)
	         	return "none";
	         value=((Contained) values.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	value=value+","+((Contained) values.get(i)).getIdentifier();
	         }
			 return value;	
	    
	    
	    case 105:
	    	values=itf.getHomes();
	    	size= values.size();
	    	if(size==0)
	    		return "none";
	    	value=((Contained) values.get(0)).getIdentifier();
	    	for (int i=1;i<size;i++){
	    		value=value+","+((Contained) values.get(i)).getIdentifier();
	    	}
		 	return value;	
    
    
	    case 106:
	    	values=itf.getValues();
	    	size= values.size();
	    	if(size==0)
	    		return "none";
	    	value=((Contained) values.get(0)).getIdentifier();
	    	for (int i=1;i<size;i++){
	    		value=value+","+((Contained) values.get(i)).getIdentifier();
	    	}
	    	return value;	


	    case 107:
	    	values=itf.getReceptacle_port();
	    	size= values.size();
	    	if(size==0)
	    		return "none";
	    	value=((Contained) values.get(0)).getIdentifier();
	    	for (int i=1;i<size;i++){
	    		value=value+","+((Contained) values.get(i)).getIdentifier();
	    	}
	    	return value;	


	    case 108:
	    	values=itf.getFacet_port();
	    	size= values.size();
	    	if(size==0)
	    		return "none";
	    	value=((Contained) values.get(0)).getIdentifier();
	    	for (int i=1;i<size;i++){
	    		value=value+","+((Contained) values.get(i)).getIdentifier();
	    	}
	    	return value;	
	    }
        return super.getPropertyValue(id);
    }
    
    
}
 