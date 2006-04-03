/*
 * Created on 20.10.2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.property;

 
import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.Contained;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
 
 

/**
 * @author Siegercn
 *
 * TODO To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class EventDefPropertySource extends ValueDefPropertySource {

    private EventDef event;
  
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public EventDefPropertySource(Contained element) {
        	super(element);
        	event=(EventDef) element;
        	 
       	  
       	   //allValues= mf.getAllContained(root,InterfaceDef.class);
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
       	String  cat="links";
    	 
          
    	PropertyDescriptor eventTyperelation = new  PropertyDescriptor(
                Integer.toString(105),
                "event_type of event_ports"  );
    	eventTyperelation.setCategory(cat);
        descriptors.add(eventTyperelation);
        
        
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	 
	    switch(Integer.parseInt( (String)id )){
	     
	    case 105:
	    	 List homeImpls=event.getEventPorts();
	         int size=homeImpls.size();
	         if(size==0)
	         	return "none";
	         String homeis=((EventPortDef)homeImpls.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	homeis=homeis+","+((EventPortDef)homeImpls.get(i)).getIdentifier();
	         }
			 return homeis;	
	      	 
	    
	    }
        return super.getPropertyValue(id);
    }
    
   

}
