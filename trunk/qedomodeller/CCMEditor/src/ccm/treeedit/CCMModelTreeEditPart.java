/*
 * Created on 20.01.2005
 *
 */
package ccm.treeedit;

import java.util.List;

import org.eclipse.emf.common.notify.Adapter;
import org.eclipse.emf.common.notify.Notification;
import org.eclipse.emf.common.notify.Notifier;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.gef.DragTracker;
import org.eclipse.gef.EditPart;
import org.eclipse.gef.Request;
import org.eclipse.gef.RequestConstants;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editparts.AbstractTreeEditPart;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Tree;
import org.eclipse.swt.widgets.TreeItem;
import org.eclipse.ui.views.properties.IPropertySource;

import CCMModel.AbstractDerivedRelation;
import CCMModel.AbstractItfDerivedRelation;
import CCMModel.AliasDef;
import CCMModel.AttributeDef;
import CCMModel.CompHomeRelation;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.Composition;
import CCMModel.ConstantDef;
import CCMModel.Contained;
import CCMModel.Diagram;
import CCMModel.EnumDef;
import CCMModel.EventDef;
import CCMModel.EventPortDef;
import CCMModel.EventPortEventRelation;
import CCMModel.ExceptionDef;
import CCMModel.Field;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.InterfaceDef;
import CCMModel.InterfaceRelation;
import CCMModel.ProvidesDef;
import CCMModel.UsesDef;
import CCMModel.View;
//import CCMModel.IpmlementsRelation;
import CCMModel.ImplRelation;
import CCMModel.ManagersRelation;
import CCMModel.ModuleDef;
import CCMModel.OperationDef;
import CCMModel.ParameterDef;
import CCMModel.Relation;
import CCMModel.StructDef;
import CCMModel.SupportsRelation;
import CCMModel.Typed;
import CCMModel.TypedefDef;
import CCMModel.UnionDef;
import CCMModel.UnionField;
import CCMModel.ValueBoxDef;
import CCMModel.ValueDef;
import CCMModel.ValueDerivedRelation;
import CCMModel.impl.RelationImpl;
import ccm.ProjectResources;
import ccm.commands.create.model.CreateAliasDefCommand;
import ccm.commands.create.model.CreateComponentDefCommand;
import ccm.commands.create.model.CreateComponentImplDefCommand;
import ccm.commands.create.model.CreateCompositionDefCommand;
import ccm.commands.create.model.CreateConstantDefCommand;
import ccm.commands.create.model.CreateEnumDefCommand;
import ccm.commands.create.model.CreateEventDefCommand;
import ccm.commands.create.model.CreateExceptionDefCommand;
import ccm.commands.create.model.CreateHomeDefCommand;
import ccm.commands.create.model.CreateHomeImplDefCommand;
import ccm.commands.create.model.CreateInterfaceDefCommand;
import ccm.commands.create.model.CreateModuleDefCommand;
import ccm.commands.create.model.CreateStructDefCommand;
import ccm.commands.create.model.CreateUnionDefCommand;
import ccm.commands.create.model.CreateValueBoxDefCommand;
import ccm.commands.create.model.CreateValueDefCommand;
import ccm.commands.create.visual.CreateDiagramCommand;
import ccm.commands.create.visual.adds.AddAliasDefCommand;
import ccm.commands.create.visual.adds.AddAttributeDefCommand;
import ccm.commands.create.visual.adds.AddConstantDefCommand;
import ccm.commands.create.visual.adds.AddEmitsSourceCommand;
import ccm.commands.create.visual.adds.AddEnumDefCommand;
import ccm.commands.create.visual.adds.AddEventSinkCommand;
import ccm.commands.create.visual.adds.AddEventSourceCommand;
import ccm.commands.create.visual.adds.AddExceptionDefCommand;
import ccm.commands.create.visual.adds.AddFacetCommand;
import ccm.commands.create.visual.adds.AddOperationDefCommand;
import ccm.commands.create.visual.adds.AddReceptacleCommand;
import ccm.commands.create.visual.adds.AddStructDefCommand;
import ccm.commands.create.visual.adds.AddUnionDefCommand;
import ccm.commands.create.visual.adds.AddValueMemberDefCommand;
import ccm.commands.delete.model.DeleteContainedCommand;
import ccm.commands.delete.model.DeleteExceptionDefCommand;
import ccm.commands.delete.model.DeleteOperationDefCommand;
import ccm.commands.delete.model.DeleteRelationCommand;
import ccm.commands.delete.model.DeleteStructDefCommand;
import ccm.commands.delete.model.DeleteUnionDefCommand;
import ccm.commands.dnd.AddModel2DiagramCommand;
import ccm.commands.dnd.AddRelation2DiagramCommand;
import ccm.commands.dnd.DragComponent2DiagramCommand;
import ccm.commands.dnd.DragComponentImpl2DiagramCommand;
import ccm.commands.dnd.DragComposition2DiagramCommand;
import ccm.commands.dnd.DragEvent2DiagramCommand;
import ccm.commands.dnd.DragHome2DiagramCommand;
import ccm.commands.dnd.DragHomeImpl2DiagramCommand;
import ccm.commands.dnd.DragInterface2DiagramCommand;
import ccm.commands.dnd.DragValue2DiagramCommand;
import ccm.commands.dnd.MoveModelCommand;
import ccm.dragndrop.CCMDragTracker;
import ccm.editors.CCMTreeViewer;
import ccm.property.AbstractIntefacefPropertySource;
import ccm.property.AttributeDefPropertySource;
import ccm.property.ComponentDefPropertySource;
import ccm.property.ComponentImplPropertySource;
import ccm.property.CompositionPropertySource;
import ccm.property.ConstantDefPropertySource;
import ccm.property.ContainedPropertySource;
import ccm.property.EnumPropertySource;
import ccm.property.EventDefPropertySource;
import ccm.property.EventPortDefPropertySource;
import ccm.property.ExceptionDefPropertySource;
import ccm.property.FacetPropertySource;
import ccm.property.HomeDefPropertySource;
import ccm.property.HomeImplPropertySource;
import ccm.property.IntefacefPropertySource;
import ccm.property.ModuleDefPropertySource;
import ccm.property.OperationDefPropertySource;
import ccm.property.ReceptaclePropertySource;
import ccm.property.RelationPropertySource;
import ccm.property.StructDefPropertySource;
import ccm.property.TypeDefPropertySource;
import ccm.property.TypedPropertySource;
import ccm.property.UnionDefPropertySource;
import ccm.property.ValueDefPropertySource;
import ccm.request.AddAliasDefRequest;
import ccm.request.AddAttributeDefRequest;
import ccm.request.AddConstantDefRequest;
import ccm.request.AddDiagramRequest;
import ccm.request.AddEmitsSourceRequest;
import ccm.request.AddEnumDefRequest;
import ccm.request.AddEventSinkRequest;
import ccm.request.AddEventSourceRequest;
import ccm.request.AddExceptionDefRequest;
import ccm.request.AddFacetRequest;
import ccm.request.AddFactoryRequest;
import ccm.request.AddOperationDefRequest;
import ccm.request.AddReceptacleRequest;
import ccm.request.AddStructDefRequest;
import ccm.request.AddUnionDefRequest;
import ccm.request.AddValueMembertDefRequest;
import ccm.request.DragAndDropRequest;
import ccm.request.model.CreateModelRequest;



public class CCMModelTreeEditPart extends AbstractTreeEditPart implements  Adapter {
	
	private Notifier target;

	
	/**
	 * Constructor initializes this with the given model.
	 * @param model  Model for this.
	 */
	public CCMModelTreeEditPart(EObject model) {
		super (model);
	}
	

	
	public Object getAdapter(Class key) {
		if (IPropertySource.class == key) {
			return getPropertySource();
		}
		return super.getAdapter(key);
	}

	
	
	private Object getPropertySource() {
		Object propertySource = null;
		//***************************************
		if(getModel() instanceof Composition)
			return new CompositionPropertySource((Contained) getModel());
		if(getModel() instanceof HomeImplDef)
			return new HomeImplPropertySource((Contained) getModel());
		if(getModel() instanceof ProvidesDef)
			return new FacetPropertySource((Contained) getModel());
		if(getModel() instanceof UsesDef)
			return new ReceptaclePropertySource((Contained) getModel());
		if(getModel() instanceof EventPortDef)
			return new EventPortDefPropertySource((Contained) getModel());
		if(getModel() instanceof EventDef)
			return new EventDefPropertySource((Contained) getModel());
		if(getModel() instanceof ValueDef)
			return new ValueDefPropertySource((Contained) getModel());
		
		if(getModel() instanceof ComponentDef)
			return new ComponentDefPropertySource((Contained) getModel());

		if(getModel() instanceof InterfaceDef)
			return new IntefacefPropertySource((Contained) getModel());
		
		if(getModel() instanceof HomeDef)
			return new HomeDefPropertySource((Contained) getModel());
		//if(getModel() instanceof Composition)
		//	return new CompositionPropertySource((Contained) getModel());
		
		//***************************************
		
		if(getModel() instanceof InterfaceDef || getModel() instanceof ComponentDef)
			return new AbstractIntefacefPropertySource( (Contained) getModel() );
		if(getModel() instanceof AttributeDef)
			return new AttributeDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof ConstantDef)
			return new ConstantDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof ExceptionDef)
			return new ExceptionDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof StructDef)
			return new StructDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof ModuleDef)
			return new ModuleDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof OperationDef)
			return new OperationDefPropertySource((Contained) getModel() );
		if(getModel() instanceof UnionDef)
			return  new UnionDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof EnumDef)
			return  new EnumPropertySource( (Contained) getModel() );
		if(getModel() instanceof ValueDef)
			return new ValueDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof TypedefDef)
			return new TypeDefPropertySource( (Contained) getModel() );
		if(getModel() instanceof Relation)
			return new RelationPropertySource( (Relation) getModel() );
		if(getModel() instanceof Typed && !(getModel() instanceof Contained))
			return new TypedPropertySource( (Typed) getModel() );
		if( propertySource == null ) {
			propertySource = new ContainedPropertySource( (Contained) getModel());
		}
		return propertySource;
	}


	
	public Command getCommand(Request request) {
		//****************************************
		if(request instanceof CreateModelRequest
				&& request.getType().equals(Composition.class))
				return new CreateCompositionDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(ComponentImplDef.class))
				return new CreateComponentImplDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(HomeImplDef.class))
				return new CreateHomeImplDefCommand();
		//******************************************
		if(request instanceof CreateModelRequest
			&& request.getType().equals(ModuleDef.class))
			return new CreateModuleDefCommand();
		if(request instanceof CreateModelRequest
			&& request.getType().equals(ComponentDef.class))
			return new CreateComponentDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(HomeDef.class))
			return new CreateHomeDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(InterfaceDef.class))
			return new CreateInterfaceDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(ValueDef.class))
			return new CreateValueDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(EventDef.class))
			return new CreateEventDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(AliasDef.class))
			return new CreateAliasDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(UnionDef.class))
			return new CreateUnionDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(StructDef.class))
			return new CreateStructDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(ExceptionDef.class))
			return new CreateExceptionDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(ConstantDef.class))
			return new CreateConstantDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(EnumDef.class))
			return new CreateEnumDefCommand();
		if(request instanceof CreateModelRequest
				&& request.getType().equals(ValueBoxDef.class))
			return new CreateValueBoxDefCommand();
		if(request instanceof AddDiagramRequest)
			return new CreateDiagramCommand();
		if(request.getType().equals(RequestConstants.REQ_DELETE)){
			if (getModel() instanceof Diagram) {
				DeleteContainedCommand cmd = new DeleteContainedCommand((Contained) getModel());
				cmd.setEditor(((CCMTreeViewer) getRoot().getViewer()).getToPage().getCCMEditor());
				return cmd;
			}
			if(getModel() instanceof UnionDef)
				return new DeleteUnionDefCommand((Contained) getModel());
			if(getModel() instanceof StructDef)
				return new DeleteStructDefCommand((Contained) getModel());
			if(getModel() instanceof ExceptionDef)
				return new DeleteExceptionDefCommand((Contained) getModel());
			if(getModel() instanceof OperationDef)
				return new DeleteOperationDefCommand((Contained) getModel());
			if(getModel() instanceof Contained)
				return new DeleteContainedCommand((Contained) getModel());
			if(getModel() instanceof Relation)
				return new DeleteRelationCommand((Relation)getModel());
		}

		// handle drag and drop requests
		if (request instanceof DragAndDropRequest) {
			
			DragAndDropRequest req = (DragAndDropRequest) request;

	//******************************************************
			if (getModel() instanceof Diagram &&req.getNewObject() instanceof ComponentDef) {
				return new DragComponent2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			if (getModel() instanceof Diagram &&req.getNewObject() instanceof HomeDef) {
				return new DragHome2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			
			
			if (getModel() instanceof Diagram &&req.getNewObject() instanceof InterfaceDef) {
				return new DragInterface2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			if (getModel() instanceof Diagram &&req.getNewObject() instanceof ValueDef) {
				return new DragValue2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			if (getModel() instanceof Diagram &&req.getNewObject() instanceof EventDef) {
				return new DragEvent2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			
			
			
			if (getModel() instanceof Diagram &&req.getNewObject() instanceof HomeImplDef) {
				return new DragHomeImpl2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			if (getModel() instanceof Diagram &&req.getNewObject() instanceof Composition) {
				return new DragComposition2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			//DragComposition2DiagramCommand
			
			if (getModel() instanceof Diagram && req.getNewObject() instanceof ComponentImplDef) {
				return new DragComponentImpl2DiagramCommand( (Contained) req.getNewObject(),
						(Diagram) getModel());
			}
			
	//***********************************************************
			// model element has been dropped on a diagram
			if (getModel() instanceof Diagram && req.getNewObject() instanceof Contained) {
				return new AddModel2DiagramCommand( (Contained) req.getNewObject(), (Diagram) getModel() );
			}
			
			// relation has been dropped on a diagram
			if (getModel() instanceof Diagram && req.getNewObject() instanceof Relation) {
				return new AddRelation2DiagramCommand( (Relation) req.getNewObject(), (Diagram) getModel() );
			}
			
			// model element has been dropped on a module
			if (getModel() instanceof ModuleDef && req.getNewObject() instanceof Contained) {
				return new MoveModelCommand( (ModuleDef) getModel(), (Contained) req.getNewObject() );
			}
		}
		if (request instanceof AddOperationDefRequest) return new AddOperationDefCommand();
		if (request instanceof AddConstantDefRequest) return new AddConstantDefCommand();
		if (request instanceof AddExceptionDefRequest) return new AddExceptionDefCommand();
		if (request instanceof AddEnumDefRequest) return new AddEnumDefCommand();
		if (request instanceof AddAliasDefRequest) return new AddAliasDefCommand();
		if (request instanceof AddUnionDefRequest) return new AddUnionDefCommand();
		if (request instanceof AddStructDefRequest) return new AddStructDefCommand();
		if (request instanceof AddAttributeDefRequest) return new AddAttributeDefCommand();
		if (request instanceof AddValueMembertDefRequest) return new AddValueMemberDefCommand();
		if (request instanceof AddFacetRequest) return new AddFacetCommand();
		if (request instanceof AddReceptacleRequest) return new AddReceptacleCommand();
		if (request instanceof AddEventSourceRequest) return new AddEventSourceCommand();
		if (request instanceof AddEmitsSourceRequest) return new AddEmitsSourceCommand();
		if (request instanceof AddEventSinkRequest) return new AddEventSinkCommand();
		if (request instanceof AddFactoryRequest) return new AddOperationDefCommand();
		
		return super.getCommand(request);
	}
	
	public EObject getEObject(){
		return (EObject) getModel();
	}
	public void activate(){
		if (isActive())return;
		// start listening for changes in the model
		getEObject().eAdapters().add(this);
		super.activate();
	}
	
	/**
	 * Creates and installs pertinent EditPolicies
	 * for this.
	 */
	protected void createEditPolicies() {
		/*installEditPolicy(EditPolicy.LAYOUT_ROLE, new ContainedNodeXYLayoutEditPolicy());
		installEditPolicy(EditPolicy.CONTAINER_ROLE, new ModelEditPolicy());	
		installEditPolicy( EditPolicy.GRAPHICAL_NODE_ROLE, new DiagramTreeEditPolicy() );*/
	}
	
	public void deactivate(){
		if (!isActive())return;
		// stop listening for changes in the model
		getEObject().eAdapters().remove(this);
		super.deactivate();
	}
	
	 /**
     * @see org.eclipse.gef.EditPart#getDragTracker(org.eclipse.gef.Request)
     */
    public DragTracker getDragTracker(Request req) {
    	//if(getModel() instanceof Diagram)
    		return new CCMDragTracker(this);
    	//return super.getDragTracker(req);
    }

	
	/**
	 * Returns <code>null</code> as a Tree EditPart holds
	 * no children under it.
	 *
	 * @return <code>null</code>
	 */
	protected List getModelChildren() {
		return getEObject().eContents();	
	}
	
	/**
	 * Refreshes the Widget of this based on the property
	 * given to update. All major properties are updated
	 * irrespective of the property input.
	 *
	 * @param property  Property to be refreshed.
	 */
	protected void refreshVisuals(){

		Object m = getModel();
		
		if ((getWidget() instanceof Tree) || m==null) {
			return;
		}

		if (m instanceof RelationImpl) {
			
			Contained source = getRelationSource((RelationImpl) m); 
			Contained target = getRelationTarget((RelationImpl) m);
			
			if (source!=null && target!=null) {
				setWidgetText(source.getIdentifier() + " -> " + target.getIdentifier());
			}
			else {
				setWidgetText("unknown source/target");
			}
			
		}
		else if (m instanceof Contained) setWidgetText(((Contained) m).getIdentifier());
		else if (m instanceof UnionField) setWidgetText(((UnionField) m).getIdentifier());
		else if (m instanceof Field) setWidgetText(((Field) m).getIdentifier());
		else if (m instanceof ParameterDef) setWidgetText(((ParameterDef) m).getIdentifier());
		else setWidgetText(m.getClass().getName());
			
		Image image = ProjectResources.getIcon(getEObject());	
		TreeItem item = (TreeItem) getWidget();

		if (image != null) {
			image.setBackground(item.getParent().getBackground());
			setWidgetImage(image);
		}

	}
	
	
	/**
	 * Returns the target if current item is a relation, otherwise <code>null</null>.
	 * @return target of relation.
	 */
	public static Contained getRelationSource(Relation rel) {

		if (rel instanceof CompHomeRelation) return ((CompHomeRelation) rel).getComponentEnd();
		if (rel instanceof SupportsRelation) {
			if(((SupportsRelation) rel).getHomes() != null)
				return ((SupportsRelation) rel).getHomes();
			else
				return ((SupportsRelation) rel).getComponents();
		}
		if (rel instanceof EventPortEventRelation) return ((EventPortEventRelation) rel).getType();
		if (rel instanceof ManagersRelation) return ((ManagersRelation) rel).getHome_impl();
		if (rel instanceof AbstractItfDerivedRelation) return ((AbstractItfDerivedRelation) rel).getDerived();
//		if (rel instanceof ImplRelation) return ((ImplRelation) rel).getImpl();
		if (rel instanceof ValueDerivedRelation) return ((ValueDerivedRelation) rel).getBase();
		if (rel instanceof AbstractDerivedRelation) return ((AbstractDerivedRelation) rel).getAbstractDerived();

		if (rel instanceof InterfaceRelation) {

			/*List provides = ((InterfaceRelation) rel).getProvidesDef();
			List uses = ((InterfaceRelation) rel).getUsesDef();
			if (provides!=null && !provides.isEmpty()) return (Contained) provides.get(0);
			if (uses!=null && !uses.isEmpty()) return (Contained) uses.get(0);*/
			if (((InterfaceRelation) rel).getProvidesDef()!=null)
				return ((InterfaceRelation) rel).getProvidesDef();
			if (((InterfaceRelation) rel).getUsesDef()!=null)
				return ((InterfaceRelation) rel).getUsesDef();
		}

		return null;
	}
	
	
	/**
	 * Returns the target if current item is a relation, otherwise <code>null</null>.
	 * @return target of relation.
	 */
	public static Contained getRelationTarget(Relation rel) {

		if (rel instanceof CompHomeRelation) return ((CompHomeRelation) rel).getHomeEnd();
		if (rel instanceof SupportsRelation) return ((SupportsRelation) rel).getSupportsItf();
		if (rel instanceof EventPortEventRelation) return ((EventPortEventRelation) rel).getEnds();
		if (rel instanceof ManagersRelation) return ((ManagersRelation) rel).getComponent_impl();
		if (rel instanceof AbstractItfDerivedRelation) return ((AbstractItfDerivedRelation) rel).getBase();
//		if (rel instanceof IpmlementsRelation) return ((IpmlementsRelation) rel).getComponentEnd();
		if (rel instanceof ValueDerivedRelation) return ((ValueDerivedRelation) rel).getDerived();
		if (rel instanceof AbstractDerivedRelation) return ((AbstractDerivedRelation) rel).getAbstractBase();
		if (rel instanceof InterfaceRelation) return ((InterfaceRelation) rel).getItf();

		return null;
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

	
	
	public boolean understandsRequest(Request req) {
		
		if (req instanceof AddDiagramRequest) return true;
		if (req instanceof CreateModelRequest) return true;
		if (req instanceof DragAndDropRequest) {
			Object model = ((DragAndDropRequest)req).getNewObject();
			if (model instanceof ModuleDef || model instanceof Diagram)
				return true;
		}
		if (req instanceof AddOperationDefRequest && 
				(getModel() instanceof InterfaceDef ||
				 getModel() instanceof ValueDef)) return true;
		if (req instanceof AddConstantDefRequest && getModel() instanceof InterfaceDef) return true;
		if (req instanceof AddExceptionDefRequest && getModel() instanceof InterfaceDef) return true;
		if (req instanceof AddEnumDefRequest && getModel() instanceof InterfaceDef) return true;
		if (req instanceof AddAliasDefRequest && getModel() instanceof InterfaceDef) return true;
		if (req instanceof AddUnionDefRequest && getModel() instanceof InterfaceDef) return true;
		if (req instanceof AddStructDefRequest && getModel() instanceof InterfaceDef) return true;
		if (req instanceof AddAttributeDefRequest && 
				(getModel() instanceof InterfaceDef ||
				 getModel() instanceof ValueDef ||
				 getModel() instanceof ComponentDef)) return true;
		if (req instanceof AddValueMembertDefRequest && getModel() instanceof ValueDef) return true;
		if (req instanceof AddFacetRequest && getModel() instanceof ComponentDef) return true;
		if (req instanceof AddReceptacleRequest && getModel() instanceof ComponentDef) return true;
		if (req instanceof AddEventSourceRequest && getModel() instanceof ComponentDef) return true;
		if (req instanceof AddEmitsSourceRequest && getModel() instanceof ComponentDef) return true;
		if (req instanceof AddEventSinkRequest && getModel() instanceof ComponentDef) return true;
		if (req instanceof AddFactoryRequest && getModel() instanceof HomeDef) return true; 
		return super.understandsRequest(req);
	}


	
	public EditPart getTargetEditPart(Request request) {
		if (request instanceof DragAndDropRequest) return this;
		else return super.getTargetEditPart(request);
	}
}

