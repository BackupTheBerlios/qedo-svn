/*
 * Created on 14.01.2005
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
package ccm.model;

import CCMModel.CCM;
import CCMModel.CCMModelFactory;
import CCMModel.IDLTypeContainer;
import CCMModel.ModuleDef;
import CCMModel.PrimitiveDef;
import CCMModel.PrimitiveKind;
//import CCMModel.ViewKind;

/**
 * @author eduardw
 *
 * Window - Preferences - Java - Code Style - Code Templates
 */
public class InitilizeModel {
	
	private CCM ccm=null;
	private ModuleDef rootmodule=null;
	private IDLTypeContainer icontainer=null;
	
	private String version="";

	/**
	 * 
	 */
	public InitilizeModel(CCM ccm) {
		this.ccm=ccm;
	}
	
	/**
	 * 
	 */
	public InitilizeModel(CCM ccm,String version) {
		this.ccm=ccm;
		this.version=version;
	}
	
	public void createRootModule(CCMModelFactory ccmFactory,String rootName){
		rootmodule=ccmFactory.createModuleDef();
		//View view=ccmFactory.createView();
		//ccm.getView().add(view);
		//view.setKind(ViewKind.TYPE_LITERAL);
		//view.setModuleDef(rootmodule);
		//rootmodule.getView().add(view);
		rootmodule.setIdentifier(rootName);
		rootmodule.setRepositoryId("IDL:" + rootName +":" + version);
		rootmodule.setVersion(version);
		rootmodule.setAbsoluteName("");
		ccm.setModuleDef(rootmodule);	
	}
	
	public void initType(CCMModelFactory ccmFactory){
		if(rootmodule==null)return;
		icontainer=ccmFactory.createIDLTypeContainer();
		ccm.setIdlContainer(icontainer);
		//View view=ccmFactory.createView();
		//ccm.getView().add(view);
		//view.setKind(ViewKind.TYPE_LITERAL);
		//view.setIDLC(icontainer);
		createTypes(ccmFactory);
	}
	
	private void createTypes(CCMModelFactory ccmFactory){
		if(icontainer==null)return;
		PrimitiveDef pr=null;
		//int x=5;
		//int y=5;
		for(int i=0;i<=18;i++){
			pr=ccmFactory.createPrimitiveDef();
			pr.setKind(PrimitiveKind.get(i));
			icontainer.getPrimitiveTypes().add(pr);
			//Node node=ccmFactory.createNode();
			//node.setX(x);
			//node.setY(y);
			//node.setWidth(-1);
			//node.setHeight(-1);
			//icontainer.getIdlView().getNode().add(node);
			//pr.getNodeFromIDL().add(node);
			//if(i==13){x=x+100;y=5;}
			//else y=y+25;
		}
	}
}

