/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * Contributors:
 *     	Eduard Weiss
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
import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.ValueDef;
import CCMModel.View;
import CCMModel.impl.ConnectionImpl;
import ccm.commands.connect.AbstractDerivedConnectCommand;
import ccm.commands.connect.ValueDerivedConnectCommand;
import ccm.commands.connect.ValueSupportsConnectCommand;
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
public class ValueDefPropertySource extends ContainedPropertySource {

    private ValueDef valueDef;
    private ModelFactory mf=new ModelFactory();
    private ModuleDef root;
    
    private ValueDef baseValue;
    private String[]baseValueNames;
    private List valueDefs;
    private List allInterfaces;
    private List interfaces;
    private List baseValues;
    private List abstractBasealues;
    
    private String[] values=new String[]{"false","true"};
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ValueDefPropertySource(Contained element) {
        	super(element);
        	valueDef=(ValueDef) element;
        	baseValue=valueDef.getBasevalue();
        	root= mf.getRootModule(valueDef);
        	valueDefs=new ArrayList( mf.getAllContained(root,ValueDef.class));
        	valueDefs.remove(valueDef);
            int size=valueDefs.size();
            baseValueNames= new String[size+1];
            baseValueNames[0]="none";
       	    for (int i=0 ;i<size;i++){
       		 
       		   baseValueNames[i+1]=((ValueDef)valueDefs.get(i)).getIdentifier();
       	    }
       	   allInterfaces= mf.getAllContained(root,InterfaceDef.class);
       	   interfaces= new ArrayList(valueDef.getValueSupports_itf());
       	 
        
       	abstractBasealues = new ArrayList(valueDef.getAbstractBaseValue()); 
      	   
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
       	String cat="local";
         // Create a descriptor and set a category
        PropertyDescriptor isAbstract = new ComboBoxPropertyDescriptor(
                									Integer.toString(CCMModelPackage.VALUE_DEF__IS_ABSTRACT),
                									"abstract",values);
        isAbstract.setCategory(cat);
        descriptors.add(isAbstract);
        PropertyDescriptor isCustom = new ComboBoxPropertyDescriptor(
                									Integer.toString(CCMModelPackage.VALUE_DEF__IS_CUSTOM),
                									"custom",values);
        isCustom.setCategory(cat);
        descriptors.add(isCustom);
        PropertyDescriptor isTruncat = new ComboBoxPropertyDescriptor(
                									Integer.toString(CCMModelPackage.VALUE_DEF__IS_TRUNCATABLE),
                									"truncatable",values);
        isTruncat.setCategory(cat);
        descriptors.add(isTruncat);
        
    	cat="links";
    	PropertyDescriptor supports = new ListPropertyDescriptor(
    			Integer.toString(100),
    			"supports interfaces " 
    			,interfaces, allInterfaces,"Select Support Interfaces") ;
    	supports.setCategory(cat);
        descriptors.add(supports);
          
    	PropertyDescriptor abstDerived = new ListPropertyDescriptor(
    			Integer.toString(101),
    			"abstBase values " 
    			,abstractBasealues, valueDefs,"Select Support Interfaces") ;
    	abstDerived.setCategory(cat);
          descriptors.add(abstDerived);
          
    	PropertyDescriptor manages = new ComboBoxPropertyDescriptor(
                Integer.toString(102),
                "base value " ,baseValueNames);
          manages.setCategory(cat);
          descriptors.add(manages);
          
    	PropertyDescriptor abstDerivedrelation = new  PropertyDescriptor(
                Integer.toString(103),
                "abstDerived values " );
    	abstDerivedrelation.setCategory(cat);
        descriptors.add(abstDerivedrelation);
        
        PropertyDescriptor baseDerivedrelation = new  PropertyDescriptor(
                Integer.toString(104),
                "baseDerived values " );
        baseDerivedrelation.setCategory(cat);
        descriptors.add(baseDerivedrelation);
        
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
    	 String value;
		 int size;
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.VALUE_DEF__IS_ABSTRACT:
	        if(valueDef.isIsAbstract())return new Integer(1);
	        else return new Integer(0);
	    case CCMModelPackage.VALUE_DEF__IS_CUSTOM:
	        if(valueDef.isIsCustom())return new Integer(1);
	        else return new Integer(0);
	    case CCMModelPackage.VALUE_DEF__IS_TRUNCATABLE:
	        if(valueDef.isIsTruncatable())return new Integer(1);
	        else return new Integer(0);  
	    case 103:
	    	 List homeImpls=valueDef.getAbstractDerivedValue();
	         size=homeImpls.size();
	         if(size==0)
	         	return "none";
	         String homeis=((ValueDef)homeImpls.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	homeis=homeis+","+((ValueDef)homeImpls.get(i)).getIdentifier();
	         }
			 return homeis;	
	    case 104:
	    	 List DerivedValues=valueDef.getDerivedValue();
	         size=DerivedValues.size();
	         if(size==0)
	         	return "none";
	         String DerivedValueNames=((ValueDef)DerivedValues.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	DerivedValueNames=DerivedValueNames+","+((ValueDef)DerivedValues.get(i)).getIdentifier();
	         }
			 return DerivedValueNames;	
	    case 102:
	    	  if(baseValue!=null)return new Integer(valueDefs.indexOf(baseValue)+1);
		        else return new Integer(0);	 
	    case 101:
	         //List AbstractBaseValues=valueDef.getAbstractBaseValue();
	         size= abstractBasealues.size();
	         if(size==0)
	         	return "none";
	         value=((ValueDef) abstractBasealues.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	value=value+","+((AbstractInterfaceDef) abstractBasealues.get(i)).getIdentifier();
	         }
			 return value;	
	    case 100:
	         //List Interfaces=valueDef.getValueSupports_itf();
	         size= interfaces.size();
	         if(size==0)
	         	return "none";
	         value=((AbstractInterfaceDef) interfaces.get(0)).getIdentifier();
	         for (int i=1;i<size;i++){
	         	value=value+","+((AbstractInterfaceDef) interfaces.get(i)).getIdentifier();
	         }
			 return value;		 
	    
	    }
        return super.getPropertyValue(id);
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
    	List newvalues;
    	int size;
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.VALUE_DEF__IS_ABSTRACT:
	        int i=((Integer)value).intValue();
	    	if(i==0)valueDef.setIsAbstract(false);
	    	else valueDef.setIsAbstract(true);
	    	break;
	    case CCMModelPackage.VALUE_DEF__IS_CUSTOM:     
	        int j=((Integer)value).intValue();
    		if(j==0)valueDef.setIsCustom(false);
    		else valueDef.setIsCustom(true);
    		break;
	    case CCMModelPackage.VALUE_DEF__IS_TRUNCATABLE:     
	        int z=((Integer)value).intValue();
    		if(z==0)valueDef.setIsTruncatable(false);
    		else valueDef.setIsTruncatable(true);
    		break;
    	
	    case 100:     
	        newvalues=((List)value) ;
	        size = newvalues.size();
	        for (int p=0;p<size;p++){
	          InterfaceDef itf=(InterfaceDef)newvalues.get(p);
	          if(interfaces.contains(itf))
	          	interfaces.remove(itf);
	          else{
	          	//abstObj.getHomeSupports_itf().add(itf);
	          	createConnection(itf,100);	
	          	
	          }
	        }
	        valueDef.getValueSupports_itf().removeAll(interfaces);
	        removeConnections(interfaces);
	        interfaces=newvalues;
    		break;	
	    case 101:     
	        newvalues=((List)value) ;
	        size = newvalues.size();
	        for (int q=0;q<size;q++){
	          ValueDef v=(ValueDef)newvalues.get(q);
	          if(abstractBasealues.contains(v))
	          	abstractBasealues.remove(v);
	          else{
	          	//abstObj.getHomeSupports_itf().add(itf);
	          	createConnection(v,101);	
	          	
	          }
	        }
	        valueDef.getAbstractBaseValue().removeAll(abstractBasealues);
	        removeConnections(abstractBasealues);
	        abstractBasealues=newvalues;
    		break;
	    case 102:
	        int r=((Integer)value).intValue();
	        if (r==0){
	        	removeConnection(baseValue);
	        	valueDef.setBasevalue(null);
	        	baseValue=null;
	        	
	        }
	        else{	
	        	ValueDef newValue=(ValueDef) valueDefs.get(r-1);
	          if(!newValue.equals(baseValue)){
	          	valueDef.setBasevalue(newValue);
	          	removeConnection(baseValue);
	    	    baseValue=newValue;
	    	    createConnection(baseValue,102);
	        }
		}
	    	break;	
    		
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
    
   

	 
	private void createConnection(Contained constained, int type) {
		List views=mf.getAllViews(root);
    	for(int j=0;j<views.size();j++){
    		View view=(View)views.get(j);
    		Node source=null;
    		Node target=null;
    		List nodes=view.getNode();
    		for(int k=0;k<nodes.size();k++){
    			Node n=(Node)nodes.get(k);
    			if(n.getContained().equals(valueDef))
    				source=n;
    			else if(n.getContained().equals(constained))
    				target=n;
    		}
    		if(source!=null&&target!=null){
    			 
    			if (type==101){
    				AbstractDerivedConnectCommand command=new AbstractDerivedConnectCommand();
    			    command.setSource(source);
    			    command.setTarget(target);
    			    command.setView(view);
    			    command.execute(); 
    		    }
    		    if (type==100){
    		    	ValueSupportsConnectCommand command=new ValueSupportsConnectCommand();
			        command.setSource(source);
			        command.setTarget(target);
			        command.setView(view);
			        command.execute(); 
		        }
    			if (type==102){
    				ValueDerivedConnectCommand command=new ValueDerivedConnectCommand();
    				command.setSource(source);
    				command.setTarget(target);
    				command.setView(view);
    				command.execute();
    			}
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
          			if(((Node)connect.getSource()).getContained().equals(valueDef)&&
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
