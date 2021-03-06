/*
 * Created on 20.01.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.treeedit;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.gef.editparts.AbstractTreeEditPart;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;

import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ComponentInstantiation;
import CCMModel.Composition;
import CCMModel.Contained;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.HomeInstantiation;
import CCMModel.InterfaceDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.View;
import ccm.ProjectResources;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class CCMViewTreeEditPart 	extends AbstractTreeEditPart implements  Adapter {
	
	private Notifier target;
	
	/**
	 * Constructor initializes this with the given model.
	 *
	 * @param model  Model for this.
	 */
	public CCMViewTreeEditPart(Object model) {
		super (model);
	}
	public View getCCMView(){
		return (View) getModel();
	}
	public void activate(){
		if (isActive())return;
		// start listening for changes in the model
		getCCMView().eAdapters().add(this);
		super.activate();
	}
	
	/* *//**
     * @see org.eclipse.gef.EditPart#getDragTracker(org.eclipse.gef.Request)
     *//*
    public DragTracker getDragTracker(Request req) {
        return new CCMDragTracker(this);
    }*/
	
	/**
	 * Creates and installs pertinent EditPolicies
	 * for this.
	 */
	protected void createEditPolicies() {}
	
	public void deactivate(){
		if (!isActive())return;
		// stop listening for changes in the model
		getCCMView().eAdapters().remove(this);
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
		Iterator i=getCCMView().getNode().iterator();
		while(i.hasNext()){
		    Node node=(Node) i.next();
			Contained o=node.getContained();
			if(o instanceof ModuleDef ||
				o instanceof InterfaceDef ||
				o instanceof ComponentDef ||
				o instanceof HomeDef||
				o instanceof HomeImplDef||
				o instanceof HomeInstantiation||
				o instanceof ComponentImplDef||
				o instanceof ComponentInstantiation||
				o instanceof Composition){
				list.add(node);
			}
		}
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
		if (getWidget() instanceof Tree){
			return;
		}
		ModuleDef cont = getCCMView().getModuleDef();
		Image image = ProjectResources.getIcon(cont);
		
		TreeItem item = (TreeItem)getWidget();
		if (image != null)
			image.setBackground(item.getParent().getBackground());
		setWidgetImage(image);
		if(cont!=null)
			setWidgetText(cont.getIdentifier());
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