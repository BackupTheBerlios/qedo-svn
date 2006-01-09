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

import java.util.Collection;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.util.EList;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.ExceptionDef;
import CCMModel.Field;
import CCMModel.IDLType;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.Typed;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;
import ccm.model.template.FieldTemplate;
import ccm.model.template.IDLTemplate;
import ccm.propertyDescriptor.FieldpropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author eduardw
 *
 */
public class ExceptionDefPropertySource extends ContainedPropertySource {
	
	 
    ExceptionDef exception;
    private ModelFactory mf=new ModelFactory();
    //private IDLTemplate idlTemp;
    private List idlT=new LinkedList();
    private CCMModelFactory factory =CCMModelManager.getFactory();
    private List idlTypeNames=new LinkedList();
    private List fieldTems=new LinkedList();
    private ModuleDef root;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ExceptionDefPropertySource(Contained element) {
        	super(element);
        	exception=(ExceptionDef) element;
        	root= mf.getRootModule(exception);
        	idlT.clear();
        	idlT.addAll(mf.getIDLTypes(exception));
        	idlTypeNames=mf.getIDLTTypedNames(idlT);
        	List fields= exception.getMembers();
        	fieldTems.clear();
        	 for (Iterator it = fields.iterator();it.hasNext();){
        	 	Field f =(Field)it.next();
		        	//ParameterMode paraMode=f.ggetDirection();
		        	String fName=f.getIdentifier();
		        	IDLType fType =f.getIDLType();
		        	IDLTemplate fTemplate=CCMConstants.getIDLTemplate(fType,idlT); ;
		        	FieldTemplate fTem= new FieldTemplate(fName,fTemplate);
		        	fieldTems.add(fTem);
		     }
        	
        	//idlTemp=CCMConstants.getIDLTemplate(exception.g.getIDLType(),idlT);
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
        PropertyDescriptor typeCode = new TextPropertyDescriptor(
                Integer.toString(CCMModelPackage.EXCEPTION_DEF__TYPE_CODE),
                "type code ");
        typeCode.setCategory(cat);
        descriptors.add(typeCode);
        PropertyDescriptor fields = new FieldpropertyDescriptor(
				Integer.toString(CCMModelPackage.EXCEPTION_DEF__MEMBERS),
				"fields",fieldTems,idlTypeNames) ;
        fields.setCategory(cat);
        descriptors.add(fields);
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    
	    
      case CCMModelPackage.EXCEPTION_DEF__MEMBERS: 
      	String fields=""; 
    	for(Iterator it =fieldTems.iterator();it.hasNext();){
    		String fieldname =((FieldTemplate)it.next()).getIdentifier();
    		if (fields.equals(""))
    			fields=fields+fieldname;
    		else
    			fields=fields+","+fieldname;
    		}
        return fields;
       // return CCMConstants.getIDLName(idlTemp,mf.getIDLTTypedNames(idlT)); 
    }
        return super.getPropertyValue(id);
    }
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    
	   case CCMModelPackage.EXCEPTION_DEF__MEMBERS: 
	   	fieldTems=(List)value;
	        List nodes = exception.getNode();
   	        for (Iterator itn = nodes.iterator();itn.hasNext();){
   		       Node opNode =(Node)itn.next();
   		       opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
				       CCMNotificationImpl.OPERATION_DEF, null, null,0));
    		 }
   	        addFilds();
   	        notifyNode();
	        break;
	    	 
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
    private void addFilds(){
		 
	//	Resource resource = operation.eResource();
		 
		EList fList = exception.getMembers();
		for (Iterator it =fList.iterator();it.hasNext();){
			Typed typed= (Typed )it.next();
			Field fld=(Field) typed;
			IDLType idlt = typed.getIDLType();
			if(idlt != null)
				idlt.getTyped().remove(typed);
//			**************************
			 List nodes =  exception.getNode();
			  for (Iterator Nit =nodes.iterator();Nit.hasNext();){
			        Node node = (Node)Nit.next();
			        node.getContents().removeAll(fld.getNodeFromTyped());
			        
			        node.eNotify(new CCMNotificationImpl(node, Notification.ADD,
			        		 		       CCMNotificationImpl.OP_PARAMETERS, null, null,0));
			        
			  }
			  fld.getNodeFromTyped().clear();
		}
	fList.clear();
	    
	    Iterator it=fieldTems.iterator();
	    while(it.hasNext()){
	    	FieldTemplate f=(FieldTemplate) it.next();
	        Field field=factory.createField();
	   //     ParameterDef paramDef=(ParameterDef)(operation.getParameters().get(0));
	        //field.setDirection(f.getMode());
	        field.setIdentifier(f.getIdentifier());
	        CCMConstants.setIDLTyped(field,f.getIdlType(),root,idlT);
	        exception.getMembers().add(field);
	        
//	      *****************************************
	        List nodes =  exception.getNode();
			  for (Iterator nit =nodes.iterator();nit.hasNext();){
			        Node opNode = (Node)nit.next();
			        Node node=factory.createNode();
			        field.getNodeFromTyped().add(node);
					node.setX(0);
					node.setY(0);
					node.setWidth(-1);
					node.setHeight(-1);
					opNode.getContents().add(node);
					opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
						       							   CCMNotificationImpl.FIELD, null, null,0));	
	        
	    }
	    }
	} 
  

}
