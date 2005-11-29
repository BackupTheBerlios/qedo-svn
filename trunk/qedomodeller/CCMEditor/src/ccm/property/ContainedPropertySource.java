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

import java.util.Iterator;
import java.util.Map;

import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertySource;
import org.eclipse.ui.views.properties.IPropertySource2;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import ccm.CCMConstants;
import ccm.model.CCMNotificationImpl;

import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.Node;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author eduardw
 *
 */
public class ContainedPropertySource implements IPropertySource2 {
	
	protected Contained object;
	protected CCMModelPackage ccmPackage;
	protected IPropertyDescriptor[] propertyDescriptors;
		
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public ContainedPropertySource(Contained element) {
    	Map registry = EPackage.Registry.INSTANCE;
		String navURI = CCMModelPackage.eNS_URI;
		ccmPackage = (CCMModelPackage) registry.get(navURI);
		object = element;
    }
	
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyDescriptors()
     */
    public IPropertyDescriptor[] getPropertyDescriptors() {
       if (propertyDescriptors == null) {
       		String cat="basic of ";
       		if(object!=null)cat=cat+ object.eClass().getName();
          // Create a descriptor and set a category
          PropertyDescriptor idDescriptor = new TextPropertyDescriptor(Integer.toString(CCMModelPackage.CONTAINED__IDENTIFIER), "identifier");
          idDescriptor.setCategory(cat);
          
          PropertyDescriptor fullIdDescriptor = new PropertyDescriptor(Integer.toString(CCMModelPackage.CONTAINED__ABSOLUTE_NAME), "absolute name");
          fullIdDescriptor.setCategory(cat);
          PropertyDescriptor ridDescriptor = new PropertyDescriptor(Integer.toString(CCMModelPackage.CONTAINED__REPOSITORY_ID), "repository id");
          ridDescriptor.setCategory(cat);
          PropertyDescriptor vDescriptor = new TextPropertyDescriptor(Integer.toString(CCMModelPackage.CONTAINED__VERSION),"version");
          vDescriptor.setCategory(cat);

          propertyDescriptors = new IPropertyDescriptor[] {
             idDescriptor,
             fullIdDescriptor,
             ridDescriptor,  
             vDescriptor};
          }
          return propertyDescriptors;
    }
	
	
	
	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#getEditableValue()
	 */
	public Object getEditableValue() {
		return object;
	}



	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
	 */
	public Object getPropertyValue(Object id) {
	    int i=Integer.parseInt( (String)id );
		if(i==CCMModelPackage.CONTAINED__ABSOLUTE_NAME)
		    return getAbsoluteName();
		if(i==CCMModelPackage.CONTAINED__IDENTIFIER)
		    return object.getIdentifier();
		if(i==CCMModelPackage.CONTAINED__REPOSITORY_ID)
		    return object.getRepositoryId();
		if(i==CCMModelPackage.CONTAINED__VERSION)
		    return object.getVersion();
		return null;
		//EStructuralFeature	feature = object.eClass().getEStructuralFeature(i);
		//Object result = object.eGet( feature );
		//return result != null ? result : "";
	}
	
	private String getAbsoluteName(){
	    String str=object.getAbsoluteName();
		if(str.trim().length()!=0)str=str + ":"+object.getIdentifier();
		else str=object.getIdentifier();
		return str;
	}

	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#isPropertySet(java.lang.Object)
	 */
	public boolean isPropertySet(Object id) {
		return false;
	}

	/**
	 * @see org.eclipse.ui.views.properties.IPropertySouce#resetPropertyValue(java.lang.Object)
	 */
	public void resetPropertyValue(Object id) {}

	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
	 */
	public void setPropertyValue(Object id, Object value) {
	    int i= Integer.parseInt( (String)id) ;
	    if(CCMModelPackage.CONTAINED__VERSION==i){
	        EStructuralFeature	feature = object.eClass().getEStructuralFeature(CCMModelPackage.CONTAINED__REPOSITORY_ID);
	        object.eSet( feature,CCMConstants.getRepositoryIdString(object.getAbsoluteName(),
	                												object.getIdentifier(),
	                												(String)value));
	    }
	    if(CCMModelPackage.CONTAINED__IDENTIFIER==i){
	 	        EStructuralFeature	feature = object.eClass().getEStructuralFeature(CCMModelPackage.CONTAINED__REPOSITORY_ID);
	 	        object.eSet( feature,CCMConstants.getRepositoryIdString(object.getAbsoluteName(),
	 	                												(String)value,
	 	                												object.getVersion()));
	 	}
		EStructuralFeature	feature = object.eClass().getEStructuralFeature(i);
		object.eSet( feature, value );
		notifyNode();
		 
	}
	
	protected void notifyNode(){
	    Iterator it=object.getNode().iterator();
	 
	    while(it.hasNext()){
	        Node node=(Node) it.next();
	        node.eNotify(new CCMNotificationImpl(node, Notification.SET,
				                                 CCMNotificationImpl.CONTAINED, null, null,0));
	    }
	}

	public boolean isPropertyResettable(Object id) {
		// TODO Auto-generated method stub
		return false;
	}

}
