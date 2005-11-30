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
import CCMModel.UsesDef;
import ccm.CCMEditorPlugin;
import ccm.ProjectResources;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class CCMNodeTreeEditPart 	extends AbstractTreeEditPart implements  Adapter {
	
	private Notifier target;
	
	/**
	 * Constructor initializes this with the given model.
	 *
	 * @param model  Model for this.
	 */
	public CCMNodeTreeEditPart(Object model) {
		super (model);
	}
	public Node getCCMNode(){
		return (Node) getModel();
	}
	public void activate(){
		if (isActive())return;
		// start listening for changes in the model
		getCCMNode().eAdapters().add(this);
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
		getCCMNode().eAdapters().remove(this);
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
		Iterator i=getCCMNode().getContents().iterator();
		while(i.hasNext()){
		    Node node=(Node) i.next();
			Contained o=node.getContained();
			if(o instanceof ModuleDef ||
				o instanceof InterfaceDef ||
				o instanceof ComponentDef ||
				o instanceof HomeDef){
				//list.add(node);
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
		String fName="";
		Contained cont=getCCMNode().getContained();
		if(cont instanceof ModuleDef)
		    fName=ProjectResources.MODULE_S;
		else if(cont instanceof InterfaceDef)
			    fName=ProjectResources.ITF_S;	     
		else if(cont instanceof ComponentDef)
			    fName=ProjectResources.COMPONENT_S;
		else if(cont instanceof HomeDef)
			    fName=ProjectResources.HOME_S;
		//*****************************************
		else if(cont instanceof HomeImplDef)
		    fName=ProjectResources.HOMEIMPL_S;
		else if(cont instanceof HomeInstantiation)
		    fName=ProjectResources.HOMEINSTANCE_S;
		else if(cont instanceof ComponentImplDef)
		    fName=ProjectResources.COMPONENTIMPL;
		else if(cont instanceof ComponentInstantiation)
		    fName=ProjectResources.COMPONRNTINSTANCE;
		else if(cont instanceof Composition)
		    fName=ProjectResources.COMPOSITION_S;
		 
		//*****************************************
		Image image = new Image(null,CCMEditorPlugin.class.getResourceAsStream(fName));
		TreeItem item = (TreeItem)getWidget();
		if (image != null)
			image.setBackground(item.getParent().getBackground());
		setWidgetImage(image);
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