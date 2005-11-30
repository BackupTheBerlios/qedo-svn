/*
 * Created on 30.09.2005
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
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

import CCMModel.AttributeDef;
import CCMModel.CCMModelFactory;
import CCMModel.CCMModelPackage;
import CCMModel.Contained;
import CCMModel.EnumDef;
import CCMModel.Field;
import CCMModel.IDLType;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.StructDef;
import CCMModel.Typed;
import ccm.CCMConstants;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;
import ccm.model.ModelFactory;
import ccm.model.template.FieldTemplate;
import ccm.model.template.IDLTemplate;
import ccm.propertyDescriptor.EnummMumberPropertyDescriptor;
import ccm.propertyDescriptor.FieldpropertyDescriptor;
import ccm.propertyDescriptor.IDLtypePropertyDescriptor;

/**
 * This class is intended to be a generic property source for all the objects in
 * the application's model. It currently only supports String and boolean types,
 * and doesn't support reset or nested properties. It uses information in the EMF
 * EAttribute and EDataType classes to get the id, display name, and type information.
 * 
 * @author siegercn
 *
 */
public class EnumPropertySource  extends ContainedPropertySource {

    
    
    
    EnumDef enum;
    private ModelFactory mf=new ModelFactory();
    private CCMModelFactory factory =CCMModelManager.getFactory();
     
    private List memberList=new LinkedList();
    private ModuleDef root;
   // String members="";
	 /**
     * Creates a new ButtonElementPropertySource.
     *
     * @param element  the element whose properties this instance represents
     */
    public EnumPropertySource (Contained element) {
        	super(element);
        	enum=(EnumDef)element;
        	root= mf.getRootModule(enum);
        	 
        	memberList= enum.getMembers();
        	 
        	 
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
         
        PropertyDescriptor fields = new EnummMumberPropertyDescriptor(
				Integer.toString(CCMModelPackage.ENUM_DEF__MEMBERS),
				"mumbers",memberList) ;
        fields.setCategory(cat);
        descriptors.add(fields);
        fields.setCategory(cat);
        descriptors.add(fields);
        propertyDescriptors=(IPropertyDescriptor[])descriptors.toArray( new IPropertyDescriptor[] {} );
        return propertyDescriptors;
    }
    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
     */
    public Object getPropertyValue(Object id) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.ENUM_DEF__MEMBERS: 
      	String members="";
      	for(Iterator it =memberList.iterator();it.hasNext();){
    		String fieldname =(String)it.next();
    		if (members.equals(""))
    			members=members+fieldname;
    		else
    			members=members+","+fieldname;
    		}
      	return members;
	    }
        return super.getPropertyValue(id);
    }
    public void setPropertyValue(Object id, Object value) {
	    switch(Integer.parseInt( (String)id )){
	    case CCMModelPackage.ENUM_DEF__MEMBERS: 
	    	memberList=(List)value;
	    	enum.getMembers().clear();
	    	enum.getMembers().addAll(memberList); 
	    	notifyNode();
	        break;
	    	 
    	default:
    	    super.setPropertyValue(id, value);
	    }
    }
    
     
}
 