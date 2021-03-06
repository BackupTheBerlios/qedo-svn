/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * Contributors:
 *     	Eduard Weiss
 * 
 */
package ccm.model;

import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.Vector;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EDataType;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EStructuralFeature;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertySource;
import org.eclipse.ui.views.properties.PropertyDescriptor;
import org.eclipse.ui.views.properties.TextPropertyDescriptor;

import CCMModel.CCMModelPackage;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author ddean
 *
 */
public class EObjectPropertySource implements IPropertySource {
	private EObject object;
	private CCMModelPackage ccmPackage;
		
	public EObjectPropertySource( EObject obj ) {
		this.object = obj;

		Map registry = EPackage.Registry.INSTANCE;
		String navURI = CCMModelPackage.eNS_URI;
		ccmPackage = (CCMModelPackage) registry.get(navURI);
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.views.properties.IPropertySource#getEditableValue()
	 */
	public Object getEditableValue() {
		return object;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyDescriptors()
	 */
	public IPropertyDescriptor[] getPropertyDescriptors() {
		Iterator	it;
		EClass		cls = object.eClass();
		Collection	descriptors = new Vector();
		 
		it = cls.getEAllAttributes().iterator();
		while( it.hasNext() ) {
			EAttribute	attr = (EAttribute)it.next();
			
			EDataType	type = attr.getEAttributeType();
			if( attr.isID() ) {
				// shouldn't be editable
				descriptors.add( new PropertyDescriptor( Integer.toString( attr.getFeatureID() ),
															 attr.getName() ) );
			}
			else if( type.getInstanceClass() == String.class ) {
				descriptors.add( new TextPropertyDescriptor( Integer.toString( attr.getFeatureID() ),
															 attr.getName() ) );
			}
			else if( type.getInstanceClass() == boolean.class ) {
			//	descriptors.add( new CheckboxPropertyDescriptor( Integer.toString( attr.getFeatureID() ),
				//												 attr.getName() ) );
			}
			else if(type.getInstanceClass()==int.class){
				descriptors.add( new TextPropertyDescriptor( Integer.toString( attr.getFeatureID() ),
															 attr.getName() ) );
			}
		}
		
		return (IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
	 */
	public Object getPropertyValue(Object id) {
		EStructuralFeature	feature = object.eClass().getEStructuralFeature( Integer.parseInt( (String)id ) );
		
		Object result = object.eGet( feature );
		return result != null ? result : "";
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.views.properties.IPropertySource#isPropertySet(java.lang.Object)
	 */
	public boolean isPropertySet(Object id) {
		return false;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.views.properties.IPropertySouce#resetPropertyValue(java.lang.Object)
	 */
	public void resetPropertyValue(Object id) {}

	/* (non-Javadoc)
	 * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
	 */
	public void setPropertyValue(Object id, Object value) {
		EStructuralFeature	feature = object.eClass().getEStructuralFeature( Integer.parseInt( (String)id ) );
		object.eSet( feature, value );
	}

}
