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
import CCMModel.Relation;
import ccm.treeedit.CCMModelTreeEditPart;



public class RelationPropertySource implements IPropertySource {
	
	protected Relation relation;	
	protected CCMModelPackage ccmPackage;
	protected IPropertyDescriptor[] propertyDescriptors;

	
	public RelationPropertySource(Relation rel) {

		Map registry = EPackage.Registry.INSTANCE;
		String navURI = CCMModelPackage.eNS_URI;
		ccmPackage = (CCMModelPackage) registry.get(navURI);
		relation = rel;

	}
	

    /**
     * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyDescriptors()
     */
    public IPropertyDescriptor[] getPropertyDescriptors() {

    	if (propertyDescriptors != null) {
            return propertyDescriptors;
    	}
    	
    	PropertyDescriptor sourceDescriptor, targetDescriptor;
		
    	String cat="basic of ";
       	if (relation!=null) cat = cat + relation.eClass().getName();

       	sourceDescriptor = new PropertyDescriptor(Integer.toString(CCMModelPackage.CONNECTION__SOURCE), "source");
       	targetDescriptor = new PropertyDescriptor(Integer.toString(CCMModelPackage.CONNECTION__TARGET), "target");     	
       	
       	sourceDescriptor.setCategory(cat);
       	targetDescriptor.setCategory(cat);
       	
       	propertyDescriptors = new IPropertyDescriptor[] 
			{ sourceDescriptor, targetDescriptor };
        
        return propertyDescriptors;
    }
	
	
	
	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#getEditableValue()
	 */
	public Object getEditableValue() {
		return relation;
	}



	/**
	 * @see org.eclipse.ui.views.properties.IPropertySource#getPropertyValue(java.lang.Object)
	 */
	public Object getPropertyValue(Object idO) {

		int id = Integer.parseInt((String) idO);
		String value = null;
		
		if (id == CCMModelPackage.CONNECTION__SOURCE) {
			value = CCMModelTreeEditPart.getRelationSource(relation).getIdentifier();
		}
		else if (id == CCMModelPackage.CONNECTION__TARGET) {
			value = CCMModelTreeEditPart.getRelationTarget(relation).getIdentifier();
		}
	
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
	}
*/
}
