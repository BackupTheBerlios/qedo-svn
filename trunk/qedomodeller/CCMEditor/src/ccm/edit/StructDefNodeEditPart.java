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
package ccm.edit;


import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.GraphicalEditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.CCMModelFactory;
import CCMModel.Field;
import CCMModel.IDLType;
import CCMModel.Node;
import CCMModel.StructDef;
import CCMModel.Typed;
import ccm.ProjectResources;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.edit.policy.ModelEditPolicy;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.figures.ContainedWithMembersFigure;
import ccm.model.CCMModelManager;
import ccm.model.CCMNotificationImpl;
import ccm.model.template.FieldTemplate;
import ccm.property.ContainedPropertySource;
import ccm.property.StructDefPropertySource;

/**
 * @author eduardw
 */
public class StructDefNodeEditPart
	extends CCMAbstractGraphicalEditPart{

    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {
        return getStructFigure().getPaneFigure();
    }
    
	private IPropertySource propertySource = null;
	private CCMModelFactory factory=CCMModelManager.getFactory();

	 /**
     * Creates a new  instance.
     * @param node
     */
    public StructDefNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public StructDefNodeEditPart(){}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
	}
	
	public StructDef getStruct(){
		return (StructDef) ((Node)getModel()).getContained();
	}
	
	/**
	* 
	* @param notification org.eclipse.emf.common.notify.Notification
	* 
	*/

	public void notifyChanged(Notification notification) {
		int featureId = notification.getFeatureID(CCMNotificationImpl.class);
		switch( featureId ) {
			case CCMNotificationImpl.STRUCT_DEF:
			case CCMNotificationImpl.CONTAINED:
				refreshVisuals();
				break;
			case CCMNotificationImpl.ST_FIELD:
				refreshVisuals();
				refreshChildren();
				break;    
		}		
		super.notifyChanged(notification);
	}
	
	
	
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#refreshVisuals()
	 */
	protected void refreshVisuals() {
		getStructFigure().setIdentifier(getStruct().getIdentifier());
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());	
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
//		refreshChildren();
//		List list=getModelChildren();
//		for (Iterator it =list.iterator();it.hasNext();)
//		{
//			Node n= (Node)it.next();
//			n.eNotify((new CCMNotificationImpl(n, Notification.SET,
//				                                 CCMNotificationImpl.CONTAINED, null, null,0)));
			
//		}
	}

	private ContainedWithMembersFigure getStructFigure(){
		return (ContainedWithMembersFigure) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		ContainedWithMembersFigure opFigure=new ContainedWithMembersFigure(getStruct().getIdentifier(),ProjectResources.STRUCT_S);
		return opFigure;
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#getModelChildren()
	 */
	protected List getModelChildren() {
		List	allChildren=super.getModelChildren();
		if(allChildren==null || allChildren.size()==0) 
			allChildren= new LinkedList();
		allChildren.addAll(getModelNode().getContents());
		return allChildren;
	}
	
	/**
	 * @see org.eclipse.core.runtime.IAdaptable#getAdapter(java.lang.Class)
	 */
	public Object getAdapter(Class key) {
		if (IPropertySource.class == key) {
			return getPropertySource();
		}
		return super.getAdapter( key );
	}
	
	/**
	 * returns IPropertySource for the EditPart
	 * @return IPropertySource 
	 */	
	protected IPropertySource getPropertySource() {
			propertySource = new StructDefPropertySource( getModelNode().getContained() );
		return propertySource;
	}
	
	
	public boolean understandsRequest(Request req) {
		if(req.getType().equals(RequestConstants.REQ_DELETE))
			return true;
	    else  
	        return super.understandsRequest(req);
	}

	
	public Command getCommand(Request request) {
		if(request.getType().equals(RequestConstants.REQ_DELETE))
			return new DeleteNodeCommand((Node) getModel(),((Node) getModel()).getView(),((Node) getModel()).getContained());
		else
		    return super.getCommand(request);
	}	

	
	private void addMemberNodes( ) {
		  List nodes =  getStruct().getNode();
		  for (Iterator nit=nodes.iterator();nit.hasNext();){
		    Node opNode = (Node)nit.next();
		  
	     Iterator it = getStruct().getMembers().iterator();
	     while(it.hasNext()) {
			Field fld = (Field) it.next();
	     	if (opNode==null) continue;
	        Node node=factory.createNode();
	        fld.getNodeFromTyped().add(node);
			node.setX(0);
			node.setY(0);
			node.setWidth(-1);
			node.setHeight(-1);
			opNode.getContents().add(node);
			node.eNotify(new CCMNotificationImpl(node, Notification.ADD,
				       							   CCMNotificationImpl.FIELD, null, null,0));	
	    }
	    if (opNode!=null) {
	    	opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
			                                   CCMNotificationImpl.ST_FIELD, null, null,0));
	    }
		  }
	}

	private void deleteMembers(){
	    Iterator it=getStruct().getMembers().iterator();
	    int i=0;
	    while(it.hasNext()){
	       
	    	Typed field= (Typed )it.next();
	    	Field fld=(Field) field;
			IDLType idlt = field.getIDLType();
			if(idlt != null)
				idlt.getTyped().remove(field);
	      
	  List nodes =  getStruct().getNode();
	  for (it =nodes.iterator();it.hasNext();){
	        Node node = (Node)it.next();
	        node.getContents().removeAll(fld.getNodeFromTyped());
	        fld.getNodeFromTyped().clear();
	        i=i+1;
	  } }  
	 //    structD.getMembers().clear();
	//    if (opNode!=null) {
	//    opNode.eNotify(new CCMNotificationImpl(opNode, Notification.ADD,
	//		       CCMNotificationImpl.OP_PARAMETERS, null, null,0));
	//    }
	}

	
	
}