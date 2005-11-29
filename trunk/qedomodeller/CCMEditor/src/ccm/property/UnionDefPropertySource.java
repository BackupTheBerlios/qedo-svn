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

import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.IDLType;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.ParameterDef;
import CCMModel.ParameterMode;
import CCMModel.Typed;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;
import ccm.model.template.IDLTemplate;
import ccm.model.template.ParameterTemplate;
import ccm.model.template.UnionFieldTemplate;
import ccm.propertyDescriptor.IDLtypePropertyDescriptor;
import ccm.propertyDescriptor.ParameterPropertyDescriptor;
import ccm.propertyDescriptor.UnionFieldPropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author eduardw
 *
 */
public class UnionDefPropertySource extends ContainedPropertySource {

    
    UnionDef typedefObj;
    
    private ModelFactory mf=new ModelFactory();
    private IDLTemplate idlTemp;
    private List idlT=new LinkedList();
    
    private CCMModelFactory factory =CCMModelManager.getFactory();
    private ModuleDef root;
    
    
    private List idlTypeNames=new LinkedList();
    private List members=new LinkedList();
    //private boolean isSet=false;

	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public UnionDefPropertySource(Contained element) {
        	super(element);
        	typedefObj=(UnionDef) element;
        	root= mf.getRootModule(element);
        	idlT.clear();
        	idlT.addAll(mf.getIDLTypes(typedefObj));
        	idlTypeNames=mf.getIDLTTypedNames(idlT);
        	idlTemp=CCMConstants.getIDLTemplate(typedefObj.getDiscriminatorType(),idlT);
        	List paraList = typedefObj.getUnionMembers();
        	members.clear();
 			//List paraTemList= new ArrayList();
 			     for (Iterator it = paraList.iterator();it.hasNext();){
 			        	UnionField para =(UnionField)it.next();
 			        	String label=para.getLabel();
 			        	String paraName=para.getIdentifier();
 			        	IDLType paraType =para.getIDLType();
 			        	IDLTemplate paraTypetemplate=CCMConstants.getIDLTemplate(paraType,idlT); ;
 			        	UnionFieldTemplate uTem= new UnionFieldTemplate(paraName,label,paraTypetemplate);
 			        	members.add(uTem);
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
       	String cat="local";
         // Create a descriptor and set a category
        PropertyDescriptor idl = new IDLtypePropertyDescriptor(
                						Integer.toString(CCMModelPackage.UNION_DEF__DISCRIMINATOR_TYPE),
                						"descriminated by",idlTemp,idlTypeNames);
        idl.setCategory(cat);
        descriptors.add(idl);
        PropertyDescriptor parameters = new UnionFieldPropertyDescriptor(
				Integer.toString(CCMModelPackage.UNION_DEF__UNION_MEMBERS),
				"members",members, idlTypeNames) ;
        	
        parameters.setCategory(cat);
        descriptors.add(parameters);
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.UNION_DEF__DISCRIMINATOR_TYPE:
	        return CCMConstants.getIDLName(idlTemp,mf.getIDLTTypedNames(idlT));   
	    case CCMModelPackage.UNION_DEF__UNION_MEMBERS: 
  	        String paraNames=""; 
	        for(Iterator it =members.iterator();it.hasNext();){
		        String paraname =((UnionFieldTemplate)it.next()).getIdentifier();
		        if (paraNames.equals(""))
			        paraNames=paraNames+paraname;
		        else
		        	paraNames=paraNames+","+paraname;
		    }
	        return paraNames;
   // return CCMConstants.getIDLName(idlTemp,mf.getIDLTTypedNames(idlT)); 
	    }
      return super.getPropertyValue(id);
    }
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.UNION_DEF__DISCRIMINATOR_TYPE:
//	   	    CCMConstants.setIDLTyped(typedefObj,(IDLTemplate)value,root,idlT);
	        idlTemp=(IDLTemplate)value;
	    notifyNode();
	        break;
	    case CCMModelPackage.UNION_DEF__UNION_MEMBERS: 
	   	    members=(List)value;
	        List nodes = typedefObj.getNode();
   	        for (Iterator itn = nodes.iterator();itn.hasNext();){
   		       Node opNode =(Node)itn.next();
   		       opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
				       CCMNotificationImpl.OPERATION_DEF, null, null,0));
    		 }
   	        addParameters();
   	        notifyNode();
	        break;
	    	 
	    default:
    	    super.setPropertyValue(id, value);
	    }
    }
    
  
    private void addParameters(){
		 
	//	Resource resource = operation.eResource();
		 
		EList paraList = typedefObj.getUnionMembers();
		for (Iterator it =paraList.iterator();it.hasNext();){
			Typed paramDef= (Typed )it.next();
			UnionField fld=(UnionField)paramDef;
			IDLType idlt = paramDef.getIDLType();
			if(idlt != null)
				idlt.getTyped().remove(paramDef);
//			**************************
			 List nodes =  typedefObj.getNode();
			  for (Iterator Nit =nodes.iterator();Nit.hasNext();){
			        Node node = (Node)Nit.next();
			        node.getContents().removeAll(fld.getNodeFromTyped());
			       
			        node.eNotify(new CCMNotificationImpl(node, Notification.ADD,
			        		 		       CCMNotificationImpl.OP_PARAMETERS, null, null,0));
			        
			  }
			  fld.getNodeFromTyped().clear();
			}
		paraList.clear();
	    
	    Iterator it=members.iterator();
	    while(it.hasNext()){
	        UnionFieldTemplate p=(UnionFieldTemplate) it.next();
	        UnionField paramDef=factory.createUnionField();
	   //     ParameterDef paramDef=(ParameterDef)(operation.getParameters().get(0));
	        paramDef.setLabel(p.getLabel());
	        paramDef.setIdentifier(p.getIdentifier());
	        CCMConstants.setIDLTyped(paramDef,p.getIdlType(),root,idlT);
	        typedefObj.getUnionMembers().add(paramDef);
	        //*****************************************
	        List nodes =  typedefObj.getNode();
			  for (Iterator nit =nodes.iterator();nit.hasNext();){
			        Node opNode = (Node)nit.next();
			        Node node=factory.createNode();
			        paramDef.getNodeFromTyped().add(node);
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
