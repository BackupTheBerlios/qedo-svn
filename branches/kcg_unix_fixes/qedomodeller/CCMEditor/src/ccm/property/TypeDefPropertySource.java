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

import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.ModuleDef;
import CCMModel.Typed;
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
public class TypeDefPropertySource extends ContainedPropertySource {
	
	protected Typed typed;
	protected CCMModelPackage ccmPackage;
	protected IPropertyDescriptor[] propertyDescriptors;
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
    public TypeDefPropertySource(Contained element) {
        super(element);
	    typed=(Typed) object;
	    root= mf.getRootModule(element);
	    idlT.clear();
	    idlT.addAll(mf.getIDLTypes(element));
	    idlTypeNames=mf.getIDLTTypedNames(idlT);
	    idlTemp=CCMConstants.getIDLTemplate(typed.getIDLType(),idlT);
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
        PropertyDescriptor idltype = new IDLtypePropertyDescriptor(
				Integer.toString(CCMModelPackage.TYPED__IDL_TYPE),
				"typed by",idlTemp,idlTypeNames) ;
        idltype.setCategory(cat);
        descriptors.add(idltype);
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.TYPED__IDL_TYPE: 
	        return CCMConstants.getIDLName(idlTemp,mf.getIDLTTypedNames(idlT)); 
	    }
        return super.getPropertyValue(id);
    }
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    
	    case CCMModelPackage.TYPED__IDL_TYPE:
	      	CCMConstants.setIDLTyped(typed,(IDLTemplate)value,root,idlT);
	        idlTemp=(IDLTemplate)value;
	 
	        break;
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
}
