/*
 * Created on 28.06.2005
*/
package ccm.commands.dnd;

import java.util.Iterator;
import java.util.List;

import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.draw2d.geometry.Point;
import org.eclipse.draw2d.geometry.Rectangle;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

import CCMModel.ComponentDef;
import CCMModel.Contained;
import CCMModel.Diagram;
import CCMModel.HomeDef;
import CCMModel.HomeImplDef;
import CCMModel.Node;
import CCMModel.ValueDef;
import ccm.commands.connect.ComponentHomeConnectCommand;
import ccm.commands.connect.HomeKeyConnectCommand;
import ccm.commands.connect.HomeSupportsConnectCommand;
import ccm.commands.connect.ImplConnectCommand;
import ccm.commands.create.visual.CreateNodeForHomeImplCommand;
import ccm.dialogs.CreateContainedDialog;
import ccm.dialogs.DragAndDropDialog;
import ccm.editors.tools.Execution;
import ccm.model.ModelFactory;

/**
 * @author Siegercn
 */
public class DragHome2DiagramCommand extends DragAbstInterface2DiagramCommand{

	 
    private boolean inquired=false;
	
	/**
	 * @param model
	 * @param newObject
	 */
	public DragHome2DiagramCommand(Contained model, Diagram diagram) {
		super(model, diagram);
		 
	}
	
	

	public DragHome2DiagramCommand(Contained model, Diagram diagram, Point location ) {
		super(model, diagram,location);
		 
		
		 
	}

	public boolean canExecute1() {
		if(inquired)
			return true;
		inquired=true;
		Display display = Display.getDefault();
		Shell shell = new Shell(display);
		DragAndDropDialog d = new DragAndDropDialog(shell, SWT.NULL);
		d.setDiscription("Home or Homeimpl");
		d.setslections(new String[]{"Home","HomImpl"});
		d.open();
		if(!d.isState()) return false;
		if (!d.getType()){
			HomeDef home= (HomeDef)contained;
			CreateNodeForHomeImplCommand command=new CreateNodeForHomeImplCommand();
			command.setRectangle(new Rectangle(location,new Dimension(165,95)));
			command.setView(view);
			command.setContainer(view.getModuleDef());
			HomeImplDef homeimpl= factory.createHomeImplDef();
			command.setNewObject(homeimpl);
			
			ModelFactory mf=new ModelFactory();
			command.setRootModule(mf.getRootModule(contained));
		    Execution excution = new Execution();
		    CreateContainedDialog createDialog=new CreateContainedDialog(shell,SWT.NULL);
		    createDialog.setRepositoryId(home.getAbsoluteName(),"",home.getVersion());
		    createDialog.setVersion(home.getVersion());
		    createDialog.setDiscription("Add HomeImpl for Home "+home.getIdentifier());
		    createDialog.open();
	        if(!d.isState() )
	        	return false;
	        command.setIdentifier(createDialog.getIdentifier());
	        command.setVersion(createDialog.getVersion());
	        command.setHome(home);
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
		 
		ComponentDef component=((HomeDef)contained).getComponent();
		if(component!=null)
				for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(component.equals(vn.getContained())){
					ComponentHomeConnectCommand command=new ComponentHomeConnectCommand();
					command.setSource(n);
					//command.setLabel("");
					command.setTarget(vn);
					command.setView(view);
					command.execute();
				}
			  }
			
		List support_itfs=((HomeDef)contained).getHomeSupports_itf();
		if(!support_itfs.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(support_itfs.contains(vn.getContained())){
					HomeSupportsConnectCommand command=new HomeSupportsConnectCommand();
					command.setSource(n);
					//command.setLabel("");
					command.setTarget(vn);
					command.setView(view);
					command.execute();
				}
			  }
		}
		List HomeImpls=((HomeDef)contained).getHomeImpl();
		if(!HomeImpls.isEmpty()){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(HomeImpls.contains(vn.getContained())){
					ImplConnectCommand command=new ImplConnectCommand();
					command.setSource(vn);
					//command.setLabel("");
					command.setTarget(n);
					command.setView(view);
					command.execute();
				}
			  }
		}
		ValueDef key=((HomeDef)contained).getPrimaryKey();
		if(key!=null){
			  for (Iterator nit= nodes.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(key.equals(vn.getContained())){
					HomeKeyConnectCommand command=new HomeKeyConnectCommand();
					command.setSource(n);
					//command.setLabel("");
					command.setTarget(vn);
					command.setView(view);
					command.execute();
				}
			  }
		}
		
	}
 
}
 
 
