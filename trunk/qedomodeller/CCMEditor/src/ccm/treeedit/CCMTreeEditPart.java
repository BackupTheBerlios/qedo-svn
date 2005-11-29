/*
 * Created on 20.01.2005
 *
 */
package ccm.treeedit;

import java.util.LinkedList;
import java.util.List;

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.gef.editparts.AbstractTreeEditPart;

import CCMModel.CCM;

/**
 * @author eduardw
 *
 */
public class CCMTreeEditPart extends AbstractTreeEditPart implements  Adapter {
	
	private Notifier target;
	
	/**
	 * Constructor initializes this with the given model.
	 *
	 * @param model  Model for this.
	 */
	public CCMTreeEditPart(CCM model) {
		super (model);
	}
	public CCM getCCM(){
		return (CCM) getModel();
	}
	public void activate(){
		if (isActive())return;
		// start listening for changes in the model
		getCCM().eAdapters().add(this);
		super.activate();
	}
	
	/**
	 * Creates and installs pertinent EditPolicies
	 * for this.
	 */
	protected void createEditPolicies() {}
	
	public void deactivate(){
		if (!isActive())return;
		// stop listening for changes in the model
		getCCM().eAdapters().remove(this);
		super.deactivate();
	}
	
	
	/**
	 * Returns <code>null</code> as a Tree EditPart holds
	 * no children under it.
	 *
	 * @return <code>null</code>
	 */
	protected List getModelChildren() {
		LinkedList list=new LinkedList();
		/*Iterator it= ((CCM)getModel()).getView().iterator();
		while(it.hasNext()){
		    View view=(View) it.next();
		    if(view.getModuleDef()!=null)
				list.add(view); 
		}*/
		list.add(((CCM)getModel()).getModuleDef());
		return list;
	}
	
	/**
	 * Refreshes the Widget of this based on the property
	 * given to update. All major properties are updated
	 * irrespective of the property input.
	 *
	 * @param property  Property to be refreshed.
	 */
	protected void refreshVisuals(){
		return;
	}
	
	/**
	 * @see org.eclipse.emf.common.notify.Adapter#notifyChanged(org.eclipse.emf.common.notify.Notification)
	 */
	public void notifyChanged(Notification notification) {
		int type = notification.getEventType();
		switch( type ) {
			case Notification.ADD:
			case Notification.ADD_MANY:
			case Notification.REMOVE:
			case Notification.REMOVE_MANY:
				refreshChildren();
				refreshVisuals();
				break;
			case Notification.SET:
				refreshVisuals();
				break;
		}		
	}
	
	/**
	 * @see org.eclipse.emf.common.notify.Adapter#getTarget()
	 */
	public Notifier getTarget() {
		return target;
	}
	
	/**
	 * @see org.eclipse.emf.common.notify.Adapter#setTarget(org.eclipse.emf.common.notify.Notifier)
	 */
	public void setTarget(Notifier newTarget) {
		target = newTarget;	
	}
	
	/**
	 * @see org.eclipse.emf.common.notify.Adapter#isAdapterForType(java.lang.Object)
	 */
	public boolean isAdapterForType(Object type) {
		return type.equals( getModel().getClass() );
	}

}