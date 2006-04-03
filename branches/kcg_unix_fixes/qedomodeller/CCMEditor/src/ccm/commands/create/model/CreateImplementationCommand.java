/**
 * (c) Copyright group ccm
 *
 * All rights reserved. This program and the accompanying materials 
 * are made available under the terms of the Common Public License v1.0 
 * which accompanies this distribution
 * 
 * @author Siegercn
 * 
 */
package ccm.commands.create.model;

import java.util.Iterator;
import java.util.List;

import CCMModel.Composition;
import CCMModel.Implementation;
import CCMModel.ModuleDef;
import CCMModel.Node;
import CCMModel.SoftwarePackage;
import CCMModel.View;
import ccm.CCMConstants;
import ccm.commands.connect.Unit_CompositionConnectCommand;
import ccm.model.ModelFactory;

public class CreateImplementationCommand extends CreateModelCommand{
	
	 
	
	private String licenseKey;
	private String licenseTextRef;
	private String uuid;

	private Composition composition;
	private Node parentNode;
	private Node opNode;
	//private Node parentNode;
	//private boolean isLocal=false;
	
	/**
	 * Constructor of this command, 
	 */
	public CreateImplementationCommand() {
		super(Implementation.class);

	}
	
	public boolean canExecute() {
		if(!(container instanceof SoftwarePackage))
			return false;
		return true;
	}
	
	/**
	 * @see org.eclipse.gef.commands.Command#execute()
	 */
	public void execute() {
		
		//setNewObject(factory.createImplementation());
		
		//super.execute();
		newObject.setIdentifier(identifier);
		newObject.setVersion(version);
		if(container.getAbsoluteName().trim().length()!=0)
		    newObject.setAbsoluteName(container.getAbsoluteName() + ":" + container.getIdentifier());
		else
		    newObject.setAbsoluteName(container.getIdentifier());
		newObject.setRepositoryId(CCMConstants.getRepositoryIdString(newObject.getAbsoluteName(),identifier,version));
	     
	    	
	    container.getContents().add(newObject);
	    ((SoftwarePackage)container).getImpl().add(newObject);
		
		//((Implementation)newObject).setLicenseKey(licenseKey);
		//((Implementation)newObject).setLicenseTexRef(licenseTextRef);
		((Implementation)newObject).setUuid(uuid);
		((Implementation)newObject).setComposition(composition);
		
		Iterator it = container.getNode().iterator();
	    while(it.hasNext()) {
	    	parentNode = (Node) it.next();
	    	opNode=factory.createNode();
	    	((Implementation)newObject).getNode().add(opNode);
	    	opNode.setX( 5);
	    	opNode.setY( 8);
	    	opNode.setWidth(60);
	    	opNode.setHeight(40);
	    	parentNode.getContents().add(opNode);
	    	
	    	View view=parentNode.getView();
	    	Unit_CompositionConnectCommand command =new Unit_CompositionConnectCommand();
			List nodeList = view.getNode();
			command.setSource(opNode);
			command.setView(view);
			for (Iterator nit= nodeList.iterator();nit.hasNext(); ){
				Node vn=(Node)nit.next();
				if(composition.equals(vn.getContained())){
					//command.setLabel("");
					command.setTarget(vn);
					command.execute();
					return;
				}
		    }
			Node vn = factory.createNode();
			vn.setContained(composition);
		    vn.setX(parentNode.getX()+180);
		    vn.setY(parentNode.getY()+160);
		    vn.setWidth(100);
		    vn.setHeight(60);
			vn.setView(view);
			composition.getNode().add(vn);
			view.getNode().add(vn);
			command.setTarget(vn);
			command.execute();
	    }
		 
	}

    /**
     * @param isAbstract The isAbstract to set.
     */
    public void setUUID(String uuid) {
        this.uuid = uuid;
    }
    public List getCompositions(){
    	ModelFactory mf = new ModelFactory();
    	ModuleDef root=mf.getRootModule(container);
    	List compositions=mf.getAllContained(root,Composition.class);
    	return compositions;
    }
    public void setComposition(Composition composition) {
		this.composition=composition;
	}
   // public void setParentNode(Node node) {
  //      this.parentNode = node;
  //  }
    public void setLicenseKey(String licenseKey) {
        this.licenseKey = licenseKey;
    }
  
    public void setLicenseTextRef(String licensetextRef) {
        this.licenseTextRef = licensetextRef;
    }
    public SoftwarePackage getPackage(){
    	return (SoftwarePackage)container;
    }
    
}
 
 