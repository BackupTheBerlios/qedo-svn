/*
 * Created on 28.06.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.gef.commands.Command;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

import ccm.commands.connect.AbstItfDerivedConnectCommand;
import ccm.commands.connect.ComponentHomeConnectCommand;
import ccm.commands.connect.ComponentSupportsConnectCommand;
import ccm.commands.connect.ImplConnectCommand;
import ccm.commands.constraints.PortConstraint;
import ccm.commands.create.visual.CreateNodeForComponentImplCommand;
import ccm.dialogs.CreateCompositionDialog;
import ccm.dialogs.CreateContainedDialog;
import ccm.dialogs.DragAndDropDialog;
import ccm.editors.tools.Execution;
import ccm.model.CCMModelManager;
import ccm.model.ModelFactory;

import CCMModel.AbstractInterfaceDef;
import CCMModel.CCMModelFactory;
import CCMModel.ComponentDef;
import CCMModel.ComponentImplDef;
import CCMModel.ConsumesDef;
import CCMModel.Contained;
import CCMModel.Container;
import CCMModel.Diagram;
import CCMModel.EmitsDef;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.PortNode;
import CCMModel.ProvidesDef;
import CCMModel.PublishesDef;
import CCMModel.UsesDef;
import CCMModel.View;

/**
 * @author Siegercn
 */
public class DragComponent2DiagramCommand extends DragAbstInterface2DiagramCommand {

	 
    private boolean inquired=false;
	
	/**
	 * @param model
	 * @param newObject
	 */
	public DragComponent2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
	}
	
	

	public DragComponent2DiagramCommand(Contained model, Diagram diagram, Point location ) {
		super(model, diagram,location);
		
		 
	}

	public boolean canExecute1() {
		if(inquired)
			return true;
		inquired=true;
		Display display = Display.getDefault();
		Shell shell = new Shell(display);
		DragAndDropDialog d = new DragAndDropDialog(shell, SWT.NULL);
		d.setDiscription("Component or ComponentImpl");
		d.setslections(new String[]{"Component","ComponentImpl"});
		d.open();
		if(!d.isState()) return false;
		if (!d.getType()){
			ComponentDef component= (ComponentDef)contained;
			CreateNodeForComponentImplCommand command=new CreateNodeForComponentImplCommand();
			command.setRectangle(new Rectangle(location,new Dimension(90,50)));
			command.setView(view);
			command.setContainer(view.getModuleDef());
			ComponentImplDef componentimpl= factory.createComponentImplDef();
			command.setNewObject(componentimpl);
			
			ModelFactory mf=new ModelFactory();
			command.setRootModule(mf.getRootModule(contained));
		    Execution excution = new Execution();
		    CreateContainedDialog createDialog=new CreateContainedDialog(shell,SWT.NULL);
		    createDialog.setRepositoryId(command.getAbsoluteName(),"",command.getVersion());
		    createDialog.setVersion(command.getVersion());
		    createDialog.setDiscription("Add ComponentImpl for Component "+component.getIdentifier());
		    createDialog.open();
	        if(!d.isState() )
	        	return false;
	        command.setIdentifier(createDialog.getIdentifier());
	        command.setVersion(createDialog.getVersion());
	        command.setComponent(component);
	        command.setRectangle(new Rectangle(location,new Dimension(90,60)));
		   	command.execute();
		   return false;
			
		}
		List nodes=view.getNode();
		for (Iterator nit= nodes.iterator();nit.hasNext(); ){
			Node n=(Node)nit.next();
			if(n.getContained().equals(contained))
				return false;
			
		}
			
	   return super.canExecute();
	}

	public void execute() {
		super.execute();
		List Homes= ((ComponentDef)contained).getHomes();
		if(!Homes.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(Homes.contains(vn.getContained())){
					ComponentHomeConnectCommand command=new ComponentHomeConnectCommand();
					command.setSource(n);
					//command.setLabel("");
					command.setTarget(vn);
					command.setView(view);
					command.execute();
				}
			  }
			}
		List Supports_itfs= ((ComponentDef)contained).getComponentSupports_itf();
		if(!Supports_itfs.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(Supports_itfs.contains(vn.getContained())){
					ComponentSupportsConnectCommand command=new ComponentSupportsConnectCommand();
					command.setSource(n);
					//command.setLabel("");
					command.setTarget(vn);
					command.setView(view);
					command.execute();
				}
			  }
			}
		List ComponentImpls= ((ComponentDef)contained).getComponentImpl();
		if(!ComponentImpls.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(ComponentImpls.contains(vn.getContained())){
					ImplConnectCommand command=new ImplConnectCommand();
					command.setSource(vn);
					//command.setLabel("");
					command.setTarget(n);
					command.setView(view);
					command.execute();
				}
			  }
			}
	}

 
}
 
