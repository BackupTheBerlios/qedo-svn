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
import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.IDLType;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.ParameterMode;
import CCMModel.Typed;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;
import ccm.model.template.IDLTemplate;
import ccm.model.template.ParameterTemplate;
import ccm.propertyDescriptor.IDLtypePropertyDescriptor;
import ccm.propertyDescriptor.ParameterPropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author eduardw
 *
 */
public class OperationDefPropertySource extends ContainedPropertySource {

    
    private String[] values=new String[]{"false","true"};
    private String[] types;
    
    OperationDef abstObj;
   
    private ModelFactory mf=new ModelFactory();
    private CCMModelFactory factory =CCMModelManager.getFactory();
    private ModuleDef root;
    private IDLTemplate idlTemp;
    private List idlT=new LinkedList();
    private List idlTypeNames=new LinkedList();
    private List paras=new LinkedList();
    private boolean isSet=false;
    
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public OperationDefPropertySource( Contained element) {
        	super(element);
        	 
        	abstObj=(OperationDef) element;
        	root= mf.getRootModule(abstObj);
        	idlT.clear();
        	idlT.addAll(mf.getIDLTypes(root));
        	idlTypeNames=mf.getIDLTTypedNames(idlT);
        //	ModuleDef moduldef= mf.getRootModule(abstObj );
        //	idlT.addAll(mf.getIDLTypes(moduldef));
        	idlTemp=CCMConstants.getIDLTemplate(abstObj.getIDLType(),idlT);
        	List paraList = abstObj.getParameters();
        	paras.clear();
 			//List paraTemList= new ArrayList();
 			     for (Iterator it = paraList.iterator();it.hasNext();){
 			        	ParameterDef para =(ParameterDef)it.next();
 			        	ParameterMode paraMode=para.getDirection();
 			        	String paraName=para.getIdentifier();
 			        	IDLType paraType =para.getIDLType();
 			        	IDLTemplate paraTypetemplate=CCMConstants.getIDLTemplate(paraType,idlT); ;
 			        	ParameterTemplate paraTem= new ParameterTemplate(paraName,paraMode,paraTypetemplate);
 			        	paras.add(paraTem);
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
        PropertyDescriptor isOneway = new ComboBoxPropertyDescriptor(
                Integer.toString(CCMModelPackage.OPERATION_DEF__IS_ONEWAY),
                "is oneway ",values);
        isOneway.setCategory(cat);
        descriptors.add(isOneway);
        
        PropertyDescriptor context = new TextPropertyDescriptor(
				Integer.toString(CCMModelPackage.OPERATION_DEF__CONTEXT),
				"context ");
        context.setCategory(cat);
        descriptors.add(context);
        
        PropertyDescriptor idl = new IDLtypePropertyDescriptor(
				Integer.toString(CCMModelPackage.OPERATION_DEF__IDL_TYPE),
				"typed by",idlTemp,idlTypeNames) ;
        	
        idl.setCategory(cat);
        descriptors.add(idl);
        PropertyDescriptor parameters = new ParameterPropertyDescriptor(
				Integer.toString(CCMModelPackage.OPERATION_DEF__PARAMETERS),
				"parameters",paras, idlTypeNames) ;
        	
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
	    case CCMModelPackage.OPERATION_DEF__IS_ONEWAY:
	        if(abstObj.isIsOneway())return new Integer(1);
	        else return new Integer(0);
	    case CCMModelPackage.OPERATION_DEF__IDL_TYPE: 
	        return CCMConstants.getIDLName(idlTemp,mf.getIDLTTypedNames(idlT)); 
	    
      case CCMModelPackage.OPERATION_DEF__PARAMETERS: 
      	String paraNames=""; 
    	for(Iterator it =paras.iterator();it.hasNext();){
    		String paraname =((ParameterTemplate)it.next()).getIdentifier();
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
    
  
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.OPERATION_DEF__IS_ONEWAY:
	        int i=((Integer)value).intValue();
	    	if(i==0)abstObj.setIsOneway(false);
	    	else abstObj.setIsOneway(true);
	    	break;
	   case CCMModelPackage.OPERATION_DEF__IDL_TYPE:
	   	CCMConstants.setIDLTyped(abstObj,(IDLTemplate)value,root,idlT);
	        idlTemp=(IDLTemplate)value;
	 
	        break;
	   case CCMModelPackage.OPERATION_DEF__PARAMETERS: 
	   	    paras=(List)value;
	        List nodes = abstObj.getNode();
   	        for (Iterator itn = nodes.iterator();itn.hasNext();){
   		       Node opNode =(Node)itn.next();
   		       opNode.eNotify(new CCMNotificationImpl(opNode, Notification.SET,
				       CCMNotificationImpl.OPERATION_DEF, null, null,0));
    		 }
   	        addParameters();
	        break;
	    	 
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
    
  
    private void addParameters(){
		 
	//	Resource resource = operation.eResource();
		 
		EList paraList = abstObj.getParameters();
		for (Iterator it =paraList.iterator();it.hasNext();){
			Typed paramDef= (Typed )it.next();
			IDLType idlt = paramDef.getIDLType();
			if(idlt != null)
				idlt.getTyped().remove(paramDef);
		}
		paraList.clear();
	    
	    Iterator it=paras.iterator();
	    while(it.hasNext()){
	        ParameterTemplate p=(ParameterTemplate) it.next();
	        ParameterDef paramDef=factory.createParameterDef();
	   //     ParameterDef paramDef=(ParameterDef)(operation.getParameters().get(0));
	        paramDef.setDirection(p.getMode());
	        paramDef.setIdentifier(p.getIdentifier());
	        CCMConstants.setIDLTyped(paramDef,p.getIdlType(),root,idlT);
	        abstObj.getParameters().add(paramDef);
	    }
	}
}
