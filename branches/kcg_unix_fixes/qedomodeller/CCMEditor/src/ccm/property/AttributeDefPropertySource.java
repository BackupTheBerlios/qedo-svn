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
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

import org.eclipse.ui.views.properties.ComboBoxPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.AttributeDef;
import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.ModuleDef;
import ccm.CCMConstants;
import ccm.model.ModelFactory;
import ccm.model.template.IDLTemplate;
import ccm.propertyDescriptor.IDLtypePropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author eduardw
 *
 */
public class AttributeDefPropertySource extends ContainedPropertySource {

    
    private String[] values=new String[]{"false","true"};
    
    AttributeDef abstObj;
    private ModelFactory mf=new ModelFactory();
    private IDLTemplate idlTemp;
    private List idlT=new LinkedList();
    private List idlTypeNames=new LinkedList();
    private ModuleDef root;
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public AttributeDefPropertySource(Contained element) {
        	super(element);
        	abstObj=(AttributeDef) element;
        	root= mf.getRootModule(abstObj);
        	idlT.clear();
        	idlT.addAll(mf.getIDLTypes(abstObj));
        	idlTypeNames=mf.getIDLTTypedNames(idlT);
        	idlTemp=CCMConstants.getIDLTemplate(abstObj.getIDLType(),idlT);
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
        PropertyDescriptor isReadOnly = new ComboBoxPropertyDescriptor(
                Integer.toString(CCMModelPackage.ATTRIBUTE_DEF__IS_READONLY),
                "is read only ",values);
        isReadOnly.setCategory(cat);
        descriptors.add(isReadOnly);
        PropertyDescriptor idl = new IDLtypePropertyDescriptor(
				Integer.toString(CCMModelPackage.ATTRIBUTE_DEF__IDL_TYPE),
				"typed by",idlTemp,idlTypeNames) ;
        idl.setCategory(cat);
        descriptors.add(idl);
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.ATTRIBUTE_DEF__IS_READONLY:
	        if(abstObj.isIsReadonly())return new Integer(1);
	        else return new Integer(0);
	    case CCMModelPackage.ATTRIBUTE_DEF__IDL_TYPE: 
	        return CCMConstants.getIDLName(idlTemp,mf.getIDLTTypedNames(idlT)); 
	    }
        return super.getPropertyValue(id);
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#setPropertyValue(java.lang.Object, java.lang.Object)
     */
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.ATTRIBUTE_DEF__IS_READONLY:
	        int i=((Integer)value).intValue();
	    	if(i==0)abstObj.setIsReadonly(false);
	    	else abstObj.setIsReadonly(true);
	    	break;
	    case CCMModelPackage.ATTRIBUTE_DEF__IDL_TYPE:
	      	CCMConstants.setIDLTyped(abstObj,(IDLTemplate)value,root,idlT);
	        idlTemp=(IDLTemplate)value;
	 
	        break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
    
    
}
