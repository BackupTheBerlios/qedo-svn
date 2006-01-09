/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * Contributors:
 *     	Eduard Weiss
 *      siegercn
 * 
 */
package ccm.property;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.AbstractInterfaceDef;
import CCMModel.Contained;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.connect.AbstItfDerivedConnectCommand;
import ccm.commands.delete.visual.DeleteConnectionCommand;
import ccm.model.ModelFactory;
import ccm.propertyDescriptor.ListPropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author eduardw
 *
 */
public class AbstractIntefacefPropertySource extends ContainedPropertySource {

    
    private String[] values=new String[]{"false","true"};
    
    protected AbstractInterfaceDef abstObj;
    private List absItfs ;
    private List allItfs;
    private String[]absItfNames;
    private ModelFactory mf=new ModelFactory();
    // private CCMModelFactory factory =CCMModelManager.getFactory();
    protected ModuleDef root;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public AbstractIntefacefPropertySource(Contained element) {
        	super(element);
        	abstObj=(InterfaceDef) element;
        	root= mf.getRootModule(abstObj);
        	allItfs= new ArrayList(mf.getAllContained(root,InterfaceDef.class));
        	allItfs.remove(abstObj); 
        	absItfs=new ArrayList(abstObj.getBaseInterface());
          
         	    
        	//absItfs= mf.getAllContained(root,AbstractInterfaceDef.class);
        	//absItfs.remove(abstObj);
        	//int size=absItfs.size();
        	//homeImpls=new HomeImplDef[size];
        	//homeImplNames= new String[size+1];
        	//homeImplNames[0]="none";
        	
        	//for (int i=0 ;i<size;i++){
        		//homeImpls[i]=(HomeImplDef)homeImplList.get(i);
        		//homeImplNames[i+1]=((HomeImplDef)homeImplList.get(i)).getIdentifier();
        		 
        	//}
        	
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
        PropertyDescriptor isAbstract = new ComboBoxPropertyDescriptor(Integer.toString(100), "is abstract",values);
        isAbstract.setCategory(cat);
        descriptors.add(isAbstract);
        
        PropertyDescriptor isLocal = new ComboBoxPropertyDescriptor(Integer.toString(101), "is local",values);
        isLocal.setCategory(cat);
        descriptors.add(isLocal);
        
        
        cat="links";
        // Create a descriptor and set a category
       PropertyDescriptor base = new ListPropertyDescriptor(
               Integer.toString(102),
               "base  interfaces " ,absItfs,allItfs,"Select Base Abst.Interfaces");
       base.setCategory(cat);
       descriptors.add(base);
       PropertyDescriptor derived = new  PropertyDescriptor(
            Integer.toString(103),
               "derived interfaces " );
       derived.setCategory(cat);
       descriptors.add(derived);
       propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
       return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	List Interfaces;
    	int size;
    	String value;
	    switch(Integer.parseInt( (String)id )){
	    case 100:
	        if(abstObj.isIsAbstract())return new Integer(1);
	        else return new Integer(0);
	    case 101:
	        if(abstObj.isIsLocal())return new Integer(1);
	        else return new Integer(0);     
	   
	    case 102:
	    	//Interfaces=abstObj.getBaseInterface();
	        size=absItfs.size();
	         if(size==0)
	         	return "none";
	         value=((AbstractInterfaceDef)absItfs.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	value=value+","+((AbstractInterfaceDef)absItfs.get(i)).getIdentifier();
	         }
			 return value;	
	    case 103:
	         Interfaces=abstObj.getDerivedInterface();
	         size= Interfaces.size();
	         if(size==0)
	         	return "none";
	         value=((AbstractInterfaceDef) Interfaces.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	value=value+","+((AbstractInterfaceDef) Interfaces.get(i)).getIdentifier();
	         }
			 return value;	
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
	    	if(i==0)abstObj.setIsAbstract(false);
	    	else abstObj.setIsAbstract(true);
	    	break;
	    case 101:     
	        int j=((Integer)value).intValue();
    		if(j==0)abstObj.setIsLocal(false);
    		else abstObj.setIsLocal(true);
    		break;
	    case 102:     
	        List newvalues=((List)value) ;
	        int size = newvalues.size();
	        for (int q=0;q<size;q++){
	          AbstractInterfaceDef v=(AbstractInterfaceDef)newvalues.get(q);
	          if(absItfs.contains(v))
	          	absItfs.remove(v);
	          else{
	          	//abstObj.getHomeSupports_itf().add(itf);
	          	createConnection(v);	
	          	
	          }
	        }
	        abstObj.getBaseInterface().removeAll( absItfs);
	        removeConnections(absItfs);
	        absItfs=newvalues;
    		break;	
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
    private void createConnection(Contained constained) {
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
    			else if(n.getContained().equals(constained))
    				target=n;
    		}
    		if(source!=null&&target!=null){
    			 
    			 
    				AbstItfDerivedConnectCommand command=new AbstItfDerivedConnectCommand();
    			    command.setSource(source);
    			    command.setTarget(target);
    			    command.setView(view);
    			    command.execute(); 
    		  
    		    
	    }
    		
       }
		
	}

	 
    private void removeConnections(List list) {
  	  for(Iterator it =list.iterator();it.hasNext();){
  	  Contained contained=(Contained)it.next();
  	  removeConnection(contained);
 
  		}
    }
    private void removeConnection(Contained contained) {  
      	List views=root.getView();
          	for(int j=0;j<views.size();j++){
          		View view=(View)views.get(j);
          		List connects=view.getConnection();
          		for(int k=0;k<connects.size();k++){
          			ConnectionImpl connect=(ConnectionImpl)connects.get(k);
          			if(((Node)connect.getSource()).getContained().equals(abstObj)&&
          			((Node)connect.getTarget()).getContained().equals(contained)	){
          				DeleteConnectionCommand cmd = new DeleteConnectionCommand(connect);
          				if (cmd.canExecute()) 
          					cmd.execute();
          				 break;
          				//view.getConnection().remove(connect);
          				
          			}
          				 
          				
          		}
          	}
  	}
  	  
}