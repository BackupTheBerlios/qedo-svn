package ccm.edit;


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

import CCMModel.Node;
import CCMModel.Property;
import ccm.ProjectResources;
import ccm.commands.delete.visual.DeleteNodeCommand;
import ccm.edit.policy.ContainedNodeXYLayoutEditPolicy;
import ccm.edit.policy.ModelEditPolicy;
import ccm.figures.ContainedWithMembersFigure;
import ccm.model.CCMNotificationImpl;
import ccm.property.PropertyPropertySource;

/**
 * @author siegercn
 */
public class PropertyNodeEditPart
	extends CCMAbstractGraphicalEditPart{

    /**
     * @see org.eclipse.gef.GraphicalEditPart#getContentPane()
     */
    public IFigure getContentPane() {
        return getRequirmentFigure().getPaneFigure();
    }
    
	private IPropertySource propertySource = null;

	 /**
     * Creates a new  instance.
     * @param node
     */
    public PropertyNodeEditPart(Node clr){
		setModel(clr);
    }
	
    public PropertyNodeEditPart(){}

	/**
	 * @see org.eclipse.gef.editparts.AbstractEditPart#createEditPolicies()
	 */
	protected void createEditPolicies() {
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());
		installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
	}
	
	public Property getProperty(){
		return (Property) ((Node)getModel()).getContained();
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
		getRequirmentFigure().setIdentifier(getProperty().getIdentifier());
		Rectangle r;
		Point loc = new Point( getModelNode().getX(), getModelNode().getY() );
		Dimension dim=new Dimension(getModelNode().getWidth(),getModelNode().getHeight());	
		r = new Rectangle(loc ,dim);
		((GraphicalEditPart) getParent()).setLayoutConstraint(this,getFigure(),r);
	}

	private ContainedWithMembersFigure getRequirmentFigure(){
		return (ContainedWithMembersFigure) getFigure();
	}
	/**
	 * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
	 */
	protected IFigure createFigure() {
		ContainedWithMembersFigure opFigure=new ContainedWithMembersFigure(getProperty().getIdentifier(),ProjectResources.PROPERTY);
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
			propertySource = new PropertyPropertySource( getModelNode().getContained() );
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

	
	
}
 