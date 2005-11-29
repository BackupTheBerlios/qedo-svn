/*
 * Created on 16.06.2005
 *
 */
package ccm.property;

import java.util.Map;

import org.eclipse.emf.ecore.EPackage;
import org.eclipse.ui.views.properties.IPropertyDescriptor;
import org.eclipse.ui.views.properties.IPropertySource;
import org.eclipse.ui.views.properties.PropertyDescriptor;

import CCMModel.CCMModelPackage;
import CCMModel.IDLType;
import CCMModel.PrimitiveDef;
import CCMModel.Typed;



public class TypedPropertySource implements IPropertySource {
	
	protected Typed typed;	
	protected CCMModelPackage ccmPackage;
	protected IPropertyDescriptor[] propertyDescriptors;

	
	public TypedPropertySource(Typed typed) {

		Map registry = EPackage.Registry.INSTANCE;
		String navURI = CCMModelPackage.eNS_URI;
		ccmPackage = (CCMModelPackage) registry.get(navURI);
		this.typed = typed;

	}
	

    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyDescriptors()
     */
    public IPropertyDescriptor[] getPropertyDescriptors() {

    	if (propertyDescriptors != null) {
            return propertyDescriptors;
    	}
    	
    	PropertyDescriptor typeDescriptor;
		
    	String cat="basic of ";
       	if (typed!=null) cat = cat + typed.eClass().getName();

       	typeDescriptor = new PropertyDescriptor(Integer.toString(CCMModelPackage.IDL_TYPE), "IDL type");
       	typeDescriptor.setCategory(cat);
       	
       	propertyDescriptors = new IPropertyDescriptor[] { typeDescriptor };
        return propertyDescriptors;
    }
	
	
	
	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#getEditableValue()
	 */
	public Object getEditableValue() {
		return typed;
	}



	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
	 */
	public Object getPropertyValue(Object idO) {

		int id = Integer.parseInt((String) idO);
		String value = null;
		
		if (id == CCMModelPackage.IDL_TYPE) {
			IDLType type = typed.getIDLType();
			if (type instanceof PrimitiveDef) 
				value = ((PrimitiveDef) type).getKind().getName();
		}
//		if (id == CCMModelPackage.FIELD__IDENTIFIER) {
//			value = field.getIdentifier();
//		}
	
		if (value!=null) return value;
		else return "unknown";
	}
		
		
	
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
/*	    int i= Integer.parseInt( (String)id) ;
		notifyNode();
*/	}
	
/*	private void notifyNode(){
	    Iterator it = relation.getNode().iterator();
	    while(it.hasNext()){
	        Node node=(Node) it.next();
	        node.eNotify(new CCMNotificationImpl(node, Notification.SET,
				                                 CCMNotificationImpl.CONTAINED, null, null,0));
	    }
	}*/

}
