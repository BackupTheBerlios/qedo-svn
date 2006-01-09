
package ccm.property;

 
import java.util.Collection;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.EmitsDef;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.PublishesDef;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.connect.EventPortEventConnectCommand;
import ccm.commands.delete.visual.DeleteConnectionCommand;
import ccm.model.ModelFactory;
 

/**
 * @author siegercn
 *
 */
public class EventPortDefPropertySource extends ContainedPropertySource {

    private EventPortDef abstObj;
    private EventDef event;
    private ModelFactory mf=new ModelFactory();
   // private CCMModelFactory factory =CCMModelManager.getFactory();
    private ModuleDef root;
    
   // private HomeImplDef[]homeImpls;
    private String[]eventsNames;
    private List events;
     
    private boolean isSet=false;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public EventPortDefPropertySource( Contained element) {
        	super(element);
        	//HomeImplDef.
        	abstObj=(EventPortDef) element;
        	event=abstObj.getEvent();
        	if(abstObj instanceof PublishesDef)
        		root= mf.getRootModule(((PublishesDef)abstObj).getComp());
        	if(abstObj instanceof ConsumesDef)
        		root= mf.getRootModule(((ConsumesDef)abstObj).getComp());
        	if(abstObj instanceof EmitsDef)
        		root= mf.getRootModule(((EmitsDef)abstObj).getComp());
        	events= mf.getAllContained(root,EventDef.class);
        	//homeImpls=homeImplList.toArray();
        	int size=events.size();
        	//homeImpls=new HomeImplDef[size];
        	eventsNames= new String[size+1];
        	eventsNames[0]="none";
        	
        	for (int i=0 ;i<size;i++){
        		//homeImpls[i]=(HomeImplDef)homeImplList.get(i);
        		eventsNames[i+1]=((EventDef)events.get(i)).getIdentifier();
        		 
        	}
        	 
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
        PropertyDescriptor event_typerelation = new ComboBoxPropertyDescriptor(
                Integer.toString(100),
                "event_type " ,eventsNames);
        event_typerelation.setCategory(cat);
        descriptors.add(event_typerelation);
         
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	        if(event!=null)return new Integer(events.indexOf(event)+1);
	        else return new Integer(0);
	    }
        return super.getPropertyValue(id);
    }
    
  
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	        int i=((Integer)value).intValue();
	        if (i==0){
	        	removeConnections();
	        	abstObj.setEvent(null);
	        	event=null;
	        	
	        }
	        else{	
	          EventDef newEvent=(EventDef) events.get(i-1);
	          if(!newEvent.equals(event)){
	    	     abstObj.setEvent(newEvent);
	    	     removeConnections();
	    	     event=newEvent;
	    	     createConnections();
	        }
		}
	    	break;
	 
	    	 
    	default:
    	    super.setPropertyValue(id, value);
	    }
    } 
	    
    private void removeConnections(){
    	//List views=mf.getAllViews(root);
    	List views=root.getView();
        	for(int j=0;j<views.size();j++){
        		View view=(View)views.get(j);
        		List connects=view.getConnection();
        		for(int k=0;k<connects.size();k++){
        			ConnectionImpl connect=(ConnectionImpl)connects.get(k);
        			if(((Node)connect.getSource()).getContained().equals(abstObj)&&
        			((Node)connect.getTarget()).getContained().equals(event)	){
        				DeleteConnectionCommand cmd = new DeleteConnectionCommand(connect);
        				if (cmd.canExecute()) 
        					cmd.execute();
        				 break;
        				//view.getConnection().remove(connect);
        				
        			}
        				//view.getConnection().remove(connect);
        			
        			   
        				
        		}
        	}
        		
    }
	private void createConnections(){
		List views=mf.getAllViews(root);
        	for(int j=0;j<views.size();j++){
        		View view=(View)views.get(j);
        		Node source=null;
        		Node target=null;
        		List nodes=view.getNode();
        		for(int k=0;k<nodes.size();k++){
        			Node n=(Node)nodes.get(k);
        			if(n.getContained().equals(abstObj))
        				source=n;
        			else if(n.getContained().equals(event))
        				target=n;
        		}
        		if(source!=null&&target!=null){
        			EventPortEventConnectCommand command=new EventPortEventConnectCommand();
        			command.setSource(source);
        			command.setTarget(target);
        			command.setView(view);
        			command.execute();
        		}
	    }
	  }
}
 
 